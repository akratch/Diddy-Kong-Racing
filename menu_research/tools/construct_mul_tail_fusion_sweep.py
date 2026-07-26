#!/usr/bin/env python3
"""Fuse the subtract/shift tail after the exact-t3 first stage.

Stage splitting proved the first `trackY << 2` can land in t3, but separate
SSA statements put the subtract and final shift in t8/t9.  These forms make
the tail one expression tree (or put the live conversion tree inside the
arithmetic expression) so Ugen can propagate a single destination hint
through all remaining operations.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_postbranch_index_sequence_sweep as post


MASK_STMT = "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL;"

TAILS: dict[str, list[str]] = {
    "sub-shift-tree": [
        "new_var = (new_var - trackY) << 1;",
    ],
    "compound-sub-shift-tree": [
        "new_var = (new_var -= trackY) << 1;",
    ],
    "assign-sub-shift-tree": [
        "new_var = (new_var = new_var - trackY) << 1;",
    ],
    "sub-mul2-tree": [
        "new_var = (new_var - trackY) * 2;",
    ],
    "sub-double-tree": [
        "new_var = (new_var - trackY) + (new_var - trackY);",
    ],
    "sub-then-double": [
        "new_var -= trackY;",
        "new_var += new_var;",
    ],
    "assign-sub-then-double": [
        "new_var = new_var - trackY;",
        "new_var = new_var + new_var;",
    ],
    "sub-then-mul2": [
        "new_var -= trackY;",
        "new_var *= 2;",
    ],
}


def finish(lines: list[str]) -> str:
    result = [
        *lines,
        "cur->trackName = level_name("
        "trackMenuIds[new_var + trackX]);",
    ]
    return "\n".join(f"                    {line}" for line in result)


CASES: list[tuple[str, int, int, str]] = []

# The first-stage statement has already demonstrated an exact t3 result.
for pre_count in range(0, 15):
    for post_count in range(0, 15):
        total = pre_count + post_count
        if total < 9 or total > 16:
            continue
        prefix = [
            "new_var = trackY << 2;",
            *([MASK_STMT] * pre_count),
        ]
        suffix = [MASK_STMT] * post_count
        for label, tail in TAILS.items():
            CASES.append(
                (
                    f"separate-{label}",
                    pre_count,
                    post_count,
                    finish([*prefix, *tail, *suffix]),
                )
            )

# Put the pair-producing tree around the first shift inside the same arithmetic
# expression.  The explicit s32 truncation restores the intended 32-bit
# subtraction before the final shift.
for inner_count in range(0, 15):
    expression = "trackY << 2"
    for _ in range(inner_count):
        expression = (
            f"({expression}) & 0xFFFFFFFFFFFFFFFFLL"
        )
    narrowed = f"(s32)({expression})"
    trees = {
        "nested-sub-shift": f"({narrowed} - trackY) << 1",
        "nested-sub-mul2": f"({narrowed} - trackY) * 2",
        "nested-double-sub": (
            f"({narrowed} - trackY) + ({narrowed} - trackY)"
        ),
        "nested-outer-cast": (
            f"(s32)(s64)(({narrowed} - trackY) << 1)"
        ),
    }
    for post_count in range(0, 15):
        total = inner_count + post_count
        if total < 9 or total > 16:
            continue
        for label, tree in trees.items():
            CASES.append(
                (
                    label,
                    inner_count,
                    post_count,
                    finish(
                        [
                            f"new_var = {tree};",
                            *([MASK_STMT] * post_count),
                        ]
                    ),
                )
            )

# A comma expression retains explicit sequence points while keeping the whole
# producer under one outer assignment destination.
for middle_count in range(0, 15):
    comma_parts = ["new_var = trackY << 2"]
    comma_parts.extend(
        "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL"
        for _ in range(middle_count)
    )
    comma_parts.append("(new_var - trackY) << 1")
    comma_tree = ", ".join(comma_parts)
    for post_count in range(0, 15):
        total = middle_count + post_count
        if total < 9 or total > 16:
            continue
        CASES.append(
            (
                "comma-sequence",
                middle_count,
                post_count,
                finish(
                    [
                        f"new_var = ({comma_tree});",
                        *([MASK_STMT] * post_count),
                    ]
                ),
            )
        )


def evaluate(
    case: tuple[str, int, int, str]
) -> tuple[int, int, int, str, int, int, str, tuple[int, ...]]:
    label, first_count, post_count, replacement = case
    source = post.SOURCE.replace(post.OLD_CALL, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-tail-fusion-") as tmp:
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
                9999,
                -1,
                -1,
                label,
                first_count,
                post_count,
                proc.stderr[-800:],
                (),
            )
        got = core.words(obj)
    diffs = tuple(
        i
        for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    )
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (
        full,
        first,
        len(got),
        label,
        first_count,
        post_count,
        replacement,
        diffs,
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(
        key=lambda row: (
            row[0],
            -row[1],
            row[3],
            row[4],
            row[5],
        )
    )
    print(f"cases={len(results)}")
    for (
        full,
        first,
        length,
        label,
        first_count,
        post_count,
        replacement,
        diffs,
    ) in results[:300]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{label} first={first_count} post={post_count} "
            f"diffs={diffs}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
