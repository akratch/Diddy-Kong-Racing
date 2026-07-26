#!/usr/bin/env python3
"""Rotate the true-arm queue before, rather than after, multiplying by six.

The post-multiply conversion cycle reaches FW3: its final copy retargets only
the last instruction of as1's multiply-by-six expansion to t3.  Converting the
live `trackY` value first should make Ugen allocate the multiply itself in t3,
so all three expansion words use the target register.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_postbranch_index_sequence_sweep as post


INITIALS = {
    "plain": "new_var = trackY;",
    "and-ll": "new_var = trackY & 0xFFFFFFFFFFFFFFFFLL;",
    "and-ull": "new_var = trackY & 0xFFFFFFFFFFFFFFFFULL;",
    "s64-roundtrip": "new_var = (s32)(s64)trackY;",
    "u64-roundtrip": "new_var = (s32)(u64)trackY;",
}
FINALS = {
    "separate-assign": (
        "new_var = new_var * 6;",
        "new_var + trackX",
    ),
    "separate-compound": (
        "new_var *= 6;",
        "new_var + trackX",
    ),
    "call-assign": (
        "",
        "(new_var = new_var * 6) + trackX",
    ),
    "call-compound": (
        "",
        "(new_var *= 6) + trackX",
    ),
}


def render(
    initial: str,
    sequence: str,
    final: tuple[str, str],
) -> str:
    final_statement, call_use = final
    lines = [initial]
    lines.extend(post.OPS[token] for token in sequence)
    if final_statement:
        lines.append(final_statement)
    lines.append(
        "cur->trackName = level_name("
        f"trackMenuIds[{call_use}]);"
    )
    return "\n".join(f"                    {line}" for line in lines)


CASES = [
    (
        initial_label,
        sequence or "-",
        final_label,
        render(initial, sequence, final),
    )
    for initial_label, initial in INITIALS.items()
    for sequence in post.SEQUENCES
    for final_label, final in FINALS.items()
]


def evaluate(
    case: tuple[str, str, str, str]
) -> tuple[int, int, int, str, str, str, str]:
    initial, sequence, final, replacement = case
    source = post.SOURCE.replace(post.OLD_CALL, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-preconverted-index-") as tmp:
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
                9999, -1, -1, initial, sequence, final, proc.stderr[-800:]
            )
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), initial, sequence, final, replacement)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4], row[5]))
    print(f"cases={len(results)}")
    for full, first, length, initial, sequence, final, replacement in results[:200]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{initial} posts={sequence} final={final}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
