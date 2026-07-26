#!/usr/bin/env python3
"""Tune the multiply-by-six producer in the post-branch FW3 basin.

All residual words are the expansion of `trackY * 6`: the post-conversion
copy retargets only its last shift to t3.  Equivalent expression and
statement trees can make Ugen/as1 assign the producer itself to t3 while the
known 12-pair cycle keeps every later allocation exact.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_postbranch_index_sequence_sweep as post


EXPRESSIONS = {
    "mul6": "trackY * 6",
    "mul6-reverse": "6 * trackY",
    "mul3-shl1": "(trackY * 3) << 1",
    "shl1-mul3": "(trackY << 1) * 3",
    "shl2-plus-shl1": "(trackY << 2) + (trackY << 1)",
    "shl3-minus-shl1": "(trackY << 3) - (trackY << 1)",
    "sub3-shl1": "((trackY << 2) - trackY) << 1",
    "mul4-sub-shl1": "((trackY * 4) - trackY) << 1",
    "double-mul3": "(trackY + trackY) * 3",
    "mul4-plus-double": "(trackY * 4) + (trackY + trackY)",
    "mul8-minus-double": "(trackY * 8) - (trackY + trackY)",
    "mul5-plus": "(trackY * 5) + trackY",
    "mul7-minus": "(trackY * 7) - trackY",
}

# Each entry finishes with new_var == trackY * 6.
STATEMENT_FORMS = {
    "assign-mul6": ["new_var = trackY * 6;"],
    "seed-compound": ["new_var = trackY;", "new_var *= 6;"],
    "mul3-shift": ["new_var = trackY * 3;", "new_var <<= 1;"],
    "double-mul3": ["new_var = trackY + trackY;", "new_var *= 3;"],
    "shift-sub-shift": [
        "new_var = trackY << 2;",
        "new_var -= trackY;",
        "new_var <<= 1;",
    ],
    "shift-add": [
        "new_var = trackY << 2;",
        "new_var += trackY << 1;",
    ],
    "shift-sub": [
        "new_var = trackY << 3;",
        "new_var -= trackY << 1;",
    ],
}


def render(lines: list[str], post_count: int, initial_wide: bool) -> str:
    result = list(lines)
    if initial_wide:
        # Wrap the final producer assignment, preserving its statement shape.
        final = result[-1]
        if final.startswith("new_var = ") and final.endswith(";"):
            rhs = final[len("new_var = ") : -1]
            result[-1] = (
                "new_var = (" + rhs + ") & 0xFFFFFFFFFFFFFFFFLL;"
            )
        else:
            # Compound final producers cannot be wrapped without changing the
            # operation; add the first live roundtrip as its own statement.
            result.append(
                "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL;"
            )
            post_count -= 1
    result.extend(
        "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL;"
        for _ in range(max(post_count, 0))
    )
    result.append(
        "cur->trackName = level_name("
        "trackMenuIds[new_var + trackX]);"
    )
    return "\n".join(f"                    {line}" for line in result)


CASES: list[tuple[str, int, bool, str]] = []
for label, expression in EXPRESSIONS.items():
    lines = [f"new_var = {expression};"]
    for post_count in range(9, 15):
        for initial_wide in (False, True):
            CASES.append(
                (
                    f"expr-{label}",
                    post_count,
                    initial_wide,
                    render(lines, post_count, initial_wide),
                )
            )
for label, lines in STATEMENT_FORMS.items():
    for post_count in range(9, 15):
        for initial_wide in (False, True):
            CASES.append(
                (
                    f"stmt-{label}",
                    post_count,
                    initial_wide,
                    render(lines, post_count, initial_wide),
                )
            )

# Put the known conversion cycle between two arithmetic stages.
for post_count in range(9, 15):
    masks = [
        "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL;"
        for _ in range(post_count)
    ]
    split_forms = {
        "split-mul3-then-shift": [
            "new_var = trackY * 3;",
            *masks,
            "new_var <<= 1;",
        ],
        "split-double-then-mul3": [
            "new_var = trackY + trackY;",
            *masks,
            "new_var *= 3;",
        ],
        "split-shift-sub-then-shift": [
            "new_var = (trackY << 2) - trackY;",
            *masks,
            "new_var <<= 1;",
        ],
        "split-shift-then-add": [
            "new_var = trackY << 2;",
            *masks,
            "new_var += trackY << 1;",
        ],
    }
    for label, lines in split_forms.items():
        lines = [
            *lines,
            "cur->trackName = level_name("
            "trackMenuIds[new_var + trackX]);",
        ]
        replacement = "\n".join(
            f"                    {line}" for line in lines
        )
        CASES.append((label, post_count, False, replacement))


def evaluate(
    case: tuple[str, int, bool, str]
) -> tuple[int, int, int, str, int, bool, str]:
    label, post_count, initial_wide, replacement = case
    source = post.SOURCE.replace(post.OLD_CALL, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-fw3-mul-") as tmp:
        directory = Path(tmp)
        src = directory / "candidate.c"
        obj = directory / "candidate.o"
        src.write_text(source)
        obj.touch()
        proc = subprocess.run(
            ["bash", core.COMPILE, src, "-o", obj],
            cwd=core.ROOT,
            capture_output=True,
            text=True,
        )
        if proc.returncode:
            return (
                9999, -1, -1, label, post_count, initial_wide,
                proc.stderr[-800:]
            )
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (
        full, first, len(got), label, post_count, initial_wide, replacement
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4], row[5]))
    print(f"cases={len(results)}")
    for full, first, length, label, count, initial, replacement in results:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{label} posts={count} initial_wide={int(initial)}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
