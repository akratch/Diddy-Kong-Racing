#!/usr/bin/env python3
"""Place the real hubName store inside the erased wide-copy chain.

The full conversion cycle restores the target FIFO but as1 propagates copies
across a later t2 high-word definition and renames `lh t2` to `lh t3`.
`cur->hubName = trackName` is an existing required instruction, independent
of every local conversion.  Moving it to the copy edge can split as1's
forward-substitution region while still allowing the store to fill the branch
delay slot.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_wide_sequence_sweep as wide


STORE = "cur->hubName = trackName;"
INITIAL = (
    "pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFFLL;"
)
POST = "pad = pad & 0xFFFFFFFFFFFFFFFFLL;"
CONDITION = "if (((s32)(s64)pad != -1)) {"


def standalone(count: int, position: int) -> str:
    conversions = [INITIAL, *([POST] * count)]
    lines = [
        *conversions[:position],
        STORE,
        *conversions[position:],
        CONDITION,
    ]
    return "\n".join(f"                {line}" for line in lines)


def fused(count: int, position: int, style: str) -> str:
    conversions = [INITIAL, *([POST] * count)]
    if style == "store-before":
        if position == 0:
            conversions[0] = (
                "pad = (cur->hubName = trackName, "
                "(gTrackSelectIDs[pad][trackX]) & "
                "0xFFFFFFFFFFFFFFFFLL);"
            )
        else:
            conversions[position] = (
                "pad = (cur->hubName = trackName, "
                "pad & 0xFFFFFFFFFFFFFFFFLL);"
            )
    elif style == "store-after":
        if position == 0:
            conversions[0] = (
                "cur->hubName = "
                "(pad = (gTrackSelectIDs[pad][trackX]) & "
                "0xFFFFFFFFFFFFFFFFLL, trackName);"
            )
        else:
            conversions[position] = (
                "cur->hubName = "
                "(pad = pad & 0xFFFFFFFFFFFFFFFFLL, trackName);"
            )
    else:
        raise ValueError(style)
    return "\n".join(
        f"                {line}" for line in [*conversions, CONDITION]
    )


CASES: list[tuple[int, str, int, str]] = []
for count in (2, 7, 12):
    conversions = count + 1
    for position in range(conversions + 1):
        CASES.append(
            (count, "standalone", position, standalone(count, position))
        )
    for position in range(conversions):
        for style in ("store-before", "store-after"):
            CASES.append(
                (count, style, position, fused(count, position, style))
            )


def evaluate(
    case: tuple[int, str, int, str]
) -> tuple[int, int, int, int, str, int, str]:
    count, style, position, replacement = case
    source = wide.SOURCE.replace(wide.OLD_REGION, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-store-barrier-") as tmp:
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
                9999, -1, -1, count, style, position, proc.stderr[-800:]
            )
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), count, style, position, replacement)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4], row[5]))
    print(f"cases={len(results)}")
    for full, first, length, count, style, position, replacement in results:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"posts={count} {style} pos={position}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
