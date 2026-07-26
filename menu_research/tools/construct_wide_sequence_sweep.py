#!/usr/bin/env python3
"""Enumerate the zero-instruction wide-conversion state machine.

The FW35 basin proved that chains of 32<->64 conversions can independently
shape Ugen's FIFO while as1 erases their moves.  This searches normalized
signed/unsigned sequences beyond the two-post limit of the earlier condition
sweep, including sinks that either allocate an anonymous scalar result or
write it back to the existing pad web.
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


SOURCE = conditions.SOURCE
LOAD = "gTrackSelectIDs[pad][trackX]"
OLD_REGION = """\
                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFF;
                pad = pad & 0xFFFFFFFFFFFFFFFF;
                cur->hubName = trackName;
                if ((pad != -1)) {"""
if SOURCE.count(OLD_REGION) != 1:
    raise RuntimeError("expected original condition region")

INITIALS = {
    "and-ll": f"pad = ({LOAD}) & 0xFFFFFFFFFFFFFFFFLL;",
    "and-ull": f"pad = ({LOAD}) & 0xFFFFFFFFFFFFFFFFULL;",
    "s64-roundtrip": f"pad = (s32)(s64)({LOAD});",
    "u64-roundtrip": f"pad = (s32)(u64)({LOAD});",
}
POSTS = {
    "S": "pad = pad & 0xFFFFFFFFFFFFFFFFLL;",
    "U": "pad = pad & 0xFFFFFFFFFFFFFFFFULL;",
}
SINKS: dict[str, tuple[list[str], str]] = {
    "s64-anon": ([], "(s32)(s64)pad != -1"),
    "u64-anon": ([], "(s32)(u64)pad != -1"),
    "s64-assign": (["pad = (s32)(s64)pad;"], "pad != -1"),
    "u64-assign": (["pad = (s32)(u64)pad;"], "pad != -1"),
    "s64-cond-assign": ([], "(pad = (s32)(s64)pad) != -1"),
    "u64-cond-assign": ([], "(pad = (s32)(u64)pad) != -1"),
    "plain": ([], "pad != -1"),
}

sequences: set[str] = {""}
for length in range(1, 7):
    sequences.update("".join(bits) for bits in itertools.product("SU", repeat=length))
for length in range(7, 15):
    sequences.add("S" * length)
    sequences.add("U" * length)
    sequences.add(("SU" * ((length + 1) // 2))[:length])
    sequences.add(("US" * ((length + 1) // 2))[:length])
SEQUENCES = sorted(sequences, key=lambda value: (len(value), value))


def render(initial: str, sequence: str, sink: tuple[list[str], str]) -> str:
    before_condition, condition = sink
    lines = [initial]
    lines.extend(POSTS[token] for token in sequence)
    lines.extend(before_condition)
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
        sequence or "-",
        sink_label,
        render(initial, sequence, sink),
    )
    for initial_label, initial in INITIALS.items()
    for sequence in SEQUENCES
    for sink_label, sink in SINKS.items()
]


def evaluate(
    case: tuple[str, str, str, str]
) -> tuple[int, int, int, str, str, str, str]:
    initial, sequence, sink, replacement = case
    source = SOURCE.replace(OLD_REGION, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-wide-sequence-") as tmp:
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
                9999, -1, -1, initial, sequence, sink, proc.stderr[-800:]
            )
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), initial, sequence, sink, replacement)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4], row[5]))
    print(f"cases={len(results)} sequences={len(SEQUENCES)}")
    for full, first, length, initial, sequence, sink, replacement in results[:180]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{initial} posts={sequence} sink={sink}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
