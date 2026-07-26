#!/usr/bin/env python3
"""Finish the allocator cycle on the real index after the branch.

The FW35 pre-branch construction preserves the target `lh t2` but enters the
true arm with t2/t3 swapped.  A branch boundary prevents as1 from propagating
later pair clobbers back into that load.  These candidates form the required
`trackY * 6` index, run value-preserving 32<->64 conversions on it, and then
use it for both required table lookups.  The conversions therefore carry a
real live value rather than a dead register burner.
"""

from __future__ import annotations

import concurrent.futures
import itertools
import os
import subprocess
import tempfile
from pathlib import Path

import construct_condition_sweep as conditions
import construct_index_sweep as core


COND35_REPLACEMENT = """\
                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFFLL;
                pad = pad & 0xFFFFFFFFFFFFFFFFULL;
                pad = pad & 0xFFFFFFFFFFFFFFFFULL;
                cur->hubName = trackName;
                if (((s32)(s64)pad != -1)) {"""
SOURCE = conditions.SOURCE.replace(
    conditions.OLD_COND, COND35_REPLACEMENT, 1
)
OLD_CALL = (
    "                    cur->trackName = "
    "level_name(trackMenuIds[(new_var = trackY * 6) + trackX]);"
)
if SOURCE.count(OLD_CALL) != 1:
    raise RuntimeError("expected first track-name call")

OPS = {
    "S": "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL;",
    "U": "new_var = new_var & 0xFFFFFFFFFFFFFFFFULL;",
}
INITIALS = {
    "plain": "new_var = trackY * 6;",
    "and-ll": "new_var = (trackY * 6) & 0xFFFFFFFFFFFFFFFFLL;",
    "and-ull": "new_var = (trackY * 6) & 0xFFFFFFFFFFFFFFFFULL;",
    "s64-roundtrip": "new_var = (s32)(s64)(trackY * 6);",
    "u64-roundtrip": "new_var = (s32)(u64)(trackY * 6);",
}
CALL_USES = {
    "plain": "new_var + trackX",
    "s64-cast": "(s32)(s64)new_var + trackX",
    "u64-cast": "(s32)(u64)new_var + trackX",
    "s64-sum": "(s32)(s64)(new_var + trackX)",
    "u64-sum": "(s32)(u64)(new_var + trackX)",
}

sequences: set[str] = {""}
for length in range(1, 7):
    sequences.update(
        "".join(bits) for bits in itertools.product("SU", repeat=length)
    )
for length in range(7, 15):
    sequences.add("S" * length)
    sequences.add("U" * length)
    sequences.add(("SU" * ((length + 1) // 2))[:length])
    sequences.add(("US" * ((length + 1) // 2))[:length])
SEQUENCES = sorted(sequences, key=lambda value: (len(value), value))


def render(initial: str, sequence: str, call_use: str) -> str:
    lines = [initial]
    lines.extend(OPS[token] for token in sequence)
    lines.append(
        "cur->trackName = level_name("
        f"trackMenuIds[{call_use}]);"
    )
    return "\n".join(f"                    {line}" for line in lines)


CASES = [
    (
        initial_label,
        sequence or "-",
        use_label,
        render(initial, sequence, call_use),
    )
    for initial_label, initial in INITIALS.items()
    for sequence in SEQUENCES
    for use_label, call_use in CALL_USES.items()
]


def evaluate(
    case: tuple[str, str, str, str]
) -> tuple[int, int, int, str, str, str, str]:
    initial, sequence, use, replacement = case
    source = SOURCE.replace(OLD_CALL, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-postbranch-index-") as tmp:
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
                9999, -1, -1, initial, sequence, use, proc.stderr[-800:]
            )
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), initial, sequence, use, replacement)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4], row[5]))
    print(f"cases={len(results)} sequences={len(SEQUENCES)}")
    for full, first, length, initial, sequence, use, replacement in results[:200]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{initial} posts={sequence} use={use}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
