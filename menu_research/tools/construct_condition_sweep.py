#!/usr/bin/env python3
"""Enumerate pair-allocation topologies for the branch-feeding load.

The downstream index is deliberately 32-bit.  A match therefore needs a
load-deferring wrapper whose temporary pair activity returns the FIFO to the
same order it had immediately after the `lh t2` pop.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core


SOURCE = core.SOURCE
SOURCE = SOURCE.replace(core.OLD_DECL, "    s32 new_var;", 1)
SOURCE = SOURCE.replace(
    core.OLD_FIRST,
    "trackMenuIds[(new_var = trackY * 6) + trackX]",
    1,
)
SOURCE = SOURCE.replace(
    core.OLD_SECOND,
    "trackMenuIds[new_var + trackX]",
    1,
)

LOAD = "gTrackSelectIDs[pad][trackX]"
OLD_COND = """\
                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFF;
                pad = pad & 0xFFFFFFFFFFFFFFFF;
                cur->hubName = trackName;
                if ((pad != -1)) {"""
if SOURCE.count(OLD_COND) != 1:
    raise RuntimeError("expected one condition construction")

WRAPS = {
    "s64-cast": f"(s64)({LOAD})",
    "u64-cast": f"(u64)({LOAD})",
    "s64-roundtrip": f"(s32)(s64)({LOAD})",
    "u64-roundtrip": f"(s32)(u64)({LOAD})",
    "and-ull": f"({LOAD}) & 0xFFFFFFFFFFFFFFFFULL",
    "and-ll": f"({LOAD}) & 0xFFFFFFFFFFFFFFFFLL",
    "and-ull-32": f"({LOAD}) & 0xFFFFFFFFULL",
    "and-ll-32": f"({LOAD}) & 0xFFFFFFFFLL",
    "or-ull-0": f"({LOAD}) | 0ULL",
    "or-ll-0": f"({LOAD}) | 0LL",
    "xor-ull-0": f"({LOAD}) ^ 0ULL",
    "xor-ll-0": f"({LOAD}) ^ 0LL",
    "plus-ull-0": f"({LOAD}) + 0ULL",
    "plus-ll-0": f"({LOAD}) + 0LL",
    "minus-ull-0": f"({LOAD}) - 0ULL",
    "minus-ll-0": f"({LOAD}) - 0LL",
    "mul-ull-1": f"({LOAD}) * 1ULL",
    "mul-ll-1": f"({LOAD}) * 1LL",
    "shl-ull-0": f"({LOAD}) << 0ULL",
    "shl-ll-0": f"({LOAD}) << 0LL",
    "shr-ull-0": f"((u64)({LOAD})) >> 0",
    "shr-ll-0": f"((s64)({LOAD})) >> 0",
    "and-u64-neg1": f"((u64)({LOAD})) & (u64)-1",
    "and-s64-neg1": f"((s64)({LOAD})) & (s64)-1",
}

POSTS = {
    "none": [],
    "s64": ["                pad = (s64)pad;"],
    "u64": ["                pad = (u64)pad;"],
    "s64-roundtrip": ["                pad = (s32)(s64)pad;"],
    "u64-roundtrip": ["                pad = (s32)(u64)pad;"],
    "and-ull": ["                pad = pad & 0xFFFFFFFFFFFFFFFFULL;"],
    "and-ll": ["                pad = pad & 0xFFFFFFFFFFFFFFFFLL;"],
    "and2-ull": [
        "                pad = pad & 0xFFFFFFFFFFFFFFFFULL;",
        "                pad = pad & 0xFFFFFFFFFFFFFFFFULL;",
    ],
    "cast2": [
        "                pad = (s32)(s64)pad;",
        "                pad = (s32)(u64)pad;",
    ],
}

CONDS = {
    "plain": "pad != -1",
    "reverse": "-1 != pad",
    "s64": "(s64)pad != -1LL",
    "u64": "(u64)pad != (u64)-1",
    "s64-castback": "(s32)(s64)pad != -1",
    "u64-castback": "(s32)(u64)pad != -1",
    "s64-castback-not-eq": "!((s32)(s64)pad == -1)",
    "u64-castback-not-eq": "!((s32)(u64)pad == -1)",
    "s64-plus1": "((s32)(s64)pad + 1) != 0",
    "u64-plus1": "((s32)(u64)pad + 1) != 0",
    "s64-plus1-truth": "((s32)(s64)pad + 1)",
    "u64-plus1-truth": "((s32)(u64)pad + 1)",
    "s64-subneg1": "((s32)(s64)pad - (-1)) != 0",
    "u64-subneg1": "((s32)(u64)pad - (-1)) != 0",
    "s64-compl": "~((s32)(s64)pad)",
    "u64-compl": "~((s32)(u64)pad)",
    "s64-xor": "((s32)(s64)pad ^ -1) != 0",
    "u64-xor": "((s32)(u64)pad ^ -1) != 0",
    "s64-unsigned-lt": "(u32)(s32)(s64)pad < 0xFFFFFFFFU",
    "u64-unsigned-lt": "(u32)(s32)(u64)pad < 0xFFFFFFFFU",
    "s64-unsigned-plus": "(u32)((s32)(s64)pad + 1) > 0",
    "u64-unsigned-plus": "(u32)((s32)(u64)pad + 1) > 0",
}

CASES = [
    (wrap_name, post_name, cond_name, wrap, post, condition)
    for wrap_name, wrap in WRAPS.items()
    for post_name, post in POSTS.items()
    for cond_name, condition in CONDS.items()
]


def evaluate(
    case: tuple[str, str, str, str, list[str], str]
) -> tuple[int, int, int, str, str, str, str]:
    wrap_name, post_name, cond_name, wrap, post, condition = case
    lines = [f"                pad = {wrap};", *post]
    replacement = (
        "\n".join(lines)
        + "\n                cur->hubName = trackName;"
        + f"\n                if (({condition})) {{"
    )
    source = SOURCE.replace(OLD_COND, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-condition-") as tmp:
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
                wrap_name,
                post_name,
                cond_name,
                proc.stderr[-500:],
            )
        got = core.words(obj)
    diffs = [i for i, (left, right) in enumerate(zip(got, core.WANT)) if left != right]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), wrap_name, post_name, cond_name, replacement)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4], row[5]))
    print(f"cases={len(results)}")
    for full, first, length, wrap, post, condition, replacement in results[:160]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{wrap} + {post} + {condition}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
