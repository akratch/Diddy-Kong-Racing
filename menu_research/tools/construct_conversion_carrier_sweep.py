#!/usr/bin/env python3
"""Vary the scalar web carrying the erased 32<->64 conversion chain.

The seven-post FW2 state has the exact allocator queue, but as1 renames the
initial `lh t2` to `lh t3` because the erased pair cycle later writes t2 as a
sign-extension high word.  Alternating the live scalar value between `pad`
and the existing unused `pad2` changes the move/copy graph while retaining
the same number and order of pair allocations.
"""

from __future__ import annotations

import concurrent.futures
import itertools
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_wide_sequence_sweep as wide


VARS = ("pad", "pad2")
KINDS = {
    "S": "0xFFFFFFFFFFFFFFFFLL",
    "U": "0xFFFFFFFFFFFFFFFFULL",
}
SINK_TYPES = {
    "s64": "s64",
    "u64": "u64",
}


def other(name: str) -> str:
    return "pad2" if name == "pad" else "pad"


def render(
    first_dest: str,
    switches: str,
    kinds: str,
    sink_type: str,
    sink_assign: bool,
) -> str:
    current = first_dest
    lines = [
        f"{current} = (gTrackSelectIDs[pad][trackX]) & {KINDS[kinds[0]]};"
    ]
    for switch, kind in zip(switches, kinds[1:]):
        destination = other(current) if switch == "1" else current
        lines.append(
            f"{destination} = {current} & {KINDS[kind]};"
        )
        current = destination
    if sink_assign:
        lines.append(f"{current} = (s32)({sink_type}){current};")
        condition = f"{current} != -1"
    else:
        condition = f"(s32)({sink_type}){current} != -1"
    lines.extend(
        [
            "cur->hubName = trackName;",
            f"if (({condition})) {{",
        ]
    )
    return "\n".join(f"                {line}" for line in lines)


# Eight widening statements total: initial + seven posts.  Exhaust every
# same-web/switch-web path.  Signedness is tested on the all-signed cycle and
# on each single unsigned edge, enough to expose copy-orientation differences.
KIND_PATTERNS = ["S" * 8, "U" * 8]
for position in range(8):
    KIND_PATTERNS.append("S" * position + "U" + "S" * (7 - position))
KIND_PATTERNS = sorted(set(KIND_PATTERNS))

CASES = [
    (
        first_dest,
        switches,
        kinds,
        sink_label,
        sink_assign,
        render(
            first_dest,
            switches,
            kinds,
            sink_type,
            sink_assign,
        ),
    )
    for first_dest in VARS
    for switches_tuple in itertools.product("01", repeat=7)
    for switches in ["".join(switches_tuple)]
    for kinds in KIND_PATTERNS
    for sink_label, sink_type in SINK_TYPES.items()
    for sink_assign in (False, True)
]


def evaluate(
    case: tuple[str, str, str, str, bool, str]
) -> tuple[int, int, int, str, str, str, str, bool, str]:
    first_dest, switches, kinds, sink, sink_assign, replacement = case
    source = wide.SOURCE.replace(wide.OLD_REGION, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-conversion-carrier-") as tmp:
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
                9999, -1, -1, first_dest, switches, kinds, sink,
                sink_assign, proc.stderr[-800:]
            )
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (
        full, first, len(got), first_dest, switches, kinds, sink,
        sink_assign, replacement
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(
        key=lambda row: (
            row[0], -row[1], row[3], row[4], row[5], row[6], row[7]
        )
    )
    print(f"cases={len(results)} kind_patterns={len(KIND_PATTERNS)}")
    for (
        full, first, length, first_dest, switches, kinds, sink,
        sink_assign, replacement
    ) in results[:200]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"first={first_dest} switches={switches} kinds={kinds} "
            f"sink={sink} assign={int(sink_assign)}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
