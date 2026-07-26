#!/usr/bin/env python3
"""Change the copy orientation of the one t2/t3 pair in the FW2 cycle.

Seven post-conversions restore every downstream allocation, but the fifth
pair writes the sign/zero extension into even t2 while carrying the scalar in
odd t3.  as1 therefore preserves the original load in t3.  A value-preserving
64-bit construction with the scalar in the high/even half may keep `lh t2`
while retaining the same pair-allocation cycle.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_wide_sequence_sweep as wide


NORMAL = "pad = pad & 0xFFFFFFFFFFFFFFFFLL;"
SPECIALS = {
    "normal": NORMAL,
    "signed-shift-roundtrip": (
        "pad = (s32)(((s64)pad << 32) >> 32);"
    ),
    "unsigned-shift-roundtrip": (
        "pad = (s32)(((u64)(u32)pad << 32) >> 32);"
    ),
    "signed-mul-shift": (
        "pad = (s32)(((s64)pad * 0x100000000LL) >> 32);"
    ),
    "unsigned-mul-shift": (
        "pad = (s32)(((u64)(u32)pad * 0x100000000ULL) >> 32);"
    ),
    "signed-shift-div": (
        "pad = (s32)(((s64)pad << 32) / 0x100000000LL);"
    ),
    "unsigned-shift-div": (
        "pad = (s32)(((u64)(u32)pad << 32) / 0x100000000ULL);"
    ),
    "signed-add-shift": (
        "pad = (s32)((((s64)pad << 32) + 0LL) >> 32);"
    ),
    "unsigned-or-shift": (
        "pad = (s32)((((u64)(u32)pad << 32) | 0ULL) >> 32);"
    ),
    "signed-double-cast": (
        "pad = (s32)(s64)(s32)(s64)pad;"
    ),
    "unsigned-double-cast": (
        "pad = (s32)(u64)(u32)(u64)(u32)pad;"
    ),
    "mixed-double-cast": (
        "pad = (s32)(s64)(u32)(u64)(s32)pad;"
    ),
}

SINKS = {
    "s64-anon": wide.SINKS["s64-anon"],
    "u64-anon": wide.SINKS["u64-anon"],
}


def render(
    initial: str,
    position: int,
    special: str,
    sink: tuple[list[str], str],
) -> str:
    before_condition, condition = sink
    posts = [NORMAL] * 7
    if position >= 0:
        posts[position] = special
    lines = [initial, *posts, *before_condition]
    lines.extend(
        [
            "cur->hubName = trackName;",
            f"if (({condition})) {{",
        ]
    )
    return "\n".join(f"                {line}" for line in lines)


CASES = [
    (
        initial_label,
        position,
        special_label,
        sink_label,
        render(initial, position, special, sink),
    )
    for initial_label, initial in wide.INITIALS.items()
    for position in range(7)
    for special_label, special in SPECIALS.items()
    for sink_label, sink in SINKS.items()
]


def evaluate(
    case: tuple[str, int, str, str, str]
) -> tuple[int, int, int, str, int, str, str, str]:
    initial, position, special, sink, replacement = case
    source = wide.SOURCE.replace(wide.OLD_REGION, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-pair-orientation-") as tmp:
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
                9999, -1, -1, initial, position, special, sink,
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
        full, first, len(got), initial, position, special, sink, replacement
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(
        key=lambda row: (row[0], -row[1], row[3], row[4], row[5], row[6])
    )
    print(f"cases={len(results)}")
    for full, first, length, initial, position, special, sink, replacement in results[:180]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{initial} pos={position} {special} sink={sink}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
