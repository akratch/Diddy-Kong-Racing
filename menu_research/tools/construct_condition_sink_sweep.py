#!/usr/bin/env python3
"""Search destinations for the final zero-cost 64->32 condition conversion.

In the FW35 construction, the final Ucvt currently gets an anonymous pool
destination.  It consumes t3, when the target queue needs t3 left at the head
and the earlier t2 value moved to the tail.  This sweep gives that conversion
or its comparison result a real C-level destination, including an otherwise
unused existing local, so Ugen can coalesce it with a retained register rather
than allocating the FIFO head.
"""

from __future__ import annotations

import concurrent.futures
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
OLD_HEAD = "                if (((s32)(s64)pad != -1)) {"
if SOURCE.count(OLD_HEAD) != 1:
    raise RuntimeError("expected one condition head")

OLD_PAD2_DECL = "    s32 pad2;"
if SOURCE.count(OLD_PAD2_DECL) < 1:
    raise RuntimeError("expected pad2 declaration")


def make_head(lines: list[str], condition: str) -> str:
    prefix = "".join(f"                {line}\n" for line in lines)
    return prefix + f"                if (({condition})) {{"


CASE_BODIES: list[tuple[str, list[str], str]] = [
    ("baseline", [], "(s32)(s64)pad != -1"),
    ("assign-pad2-then-plain", ["pad2 = (s32)(s64)pad;"], "pad2 != -1"),
    (
        "assign-pad2-then-cast",
        ["pad2 = (s32)(s64)pad;"],
        "(s32)(s64)pad2 != -1",
    ),
    ("assign-pad-then-plain", ["pad = (s32)(s64)pad;"], "pad != -1"),
    (
        "assign-pad-then-cast",
        ["pad = (s32)(s64)pad;"],
        "(s32)(s64)pad != -1",
    ),
    ("condition-assign-pad2", [], "(pad2 = (s32)(s64)pad) != -1"),
    ("condition-assign-pad", [], "(pad = (s32)(s64)pad) != -1"),
    (
        "condition-comma-pad2",
        [],
        "(pad2 = (s32)(s64)pad, pad2) != -1",
    ),
    (
        "condition-comma-pad",
        [],
        "(pad = (s32)(s64)pad, pad) != -1",
    ),
    (
        "condition-chain-pad2-pad",
        [],
        "(pad2 = pad = (s32)(s64)pad) != -1",
    ),
    (
        "condition-chain-pad-pad2",
        [],
        "(pad = pad2 = (s32)(s64)pad) != -1",
    ),
    (
        "assign-chain-then-pad2",
        ["pad2 = pad = (s32)(s64)pad;"],
        "pad2 != -1",
    ),
    (
        "assign-chain-then-pad",
        ["pad2 = pad = (s32)(s64)pad;"],
        "pad != -1",
    ),
    (
        "assign-bool-then-truth",
        ["pad2 = ((s32)(s64)pad != -1);"],
        "pad2",
    ),
    (
        "condition-bool-assign",
        [],
        "(pad2 = ((s32)(s64)pad != -1))",
    ),
    (
        "condition-bool-comma",
        [],
        "(pad2 = ((s32)(s64)pad != -1), pad2)",
    ),
    (
        "condition-double-assign",
        [],
        "(pad2 = (pad = (s32)(s64)pad)) != -1",
    ),
    (
        "condition-self-assignment",
        [],
        "(pad2 = (s32)(s64)pad, pad2 = pad2) != -1",
    ),
    (
        "assign-pad2-self-then",
        ["pad2 = (s32)(s64)pad;", "pad2 = pad2;"],
        "pad2 != -1",
    ),
    (
        "assign-pad2-through-temp",
        ["pad2 = (s32)(s64)pad;", "temp = pad2;"],
        "temp != -1",
    ),
    (
        "assign-temp-through-pad2",
        ["temp = (s32)(s64)pad;", "pad2 = temp;"],
        "pad2 != -1",
    ),
    (
        "condition-temp-pad2-chain",
        [],
        "(temp = pad2 = (s32)(s64)pad) != -1",
    ),
    (
        "condition-pad2-temp-chain",
        [],
        "(pad2 = temp = (s32)(s64)pad) != -1",
    ),
]

DECLARATIONS = {
    "s32": "    s32 pad2;",
    "register-s32": "    register s32 pad2;",
    "u32": "    u32 pad2;",
    "register-u32": "    register u32 pad2;",
    "enum": "    enum { PAD2_NEG = -1, PAD2_ZERO } pad2;",
    "s64": "    s64 pad2;",
    "u64": "    u64 pad2;",
    "s16": "    s16 pad2;",
    "u16": "    u16 pad2;",
}

CASES = [
    (f"{decl_label}-{body_label}", declaration, make_head(lines, condition))
    for decl_label, declaration in DECLARATIONS.items()
    for body_label, lines, condition in CASE_BODIES
]


def evaluate(
    case: tuple[str, str, str]
) -> tuple[int, int, int, str, str]:
    label, declaration, replacement = case
    source = SOURCE.replace(OLD_PAD2_DECL, declaration, 1)
    source = source.replace(OLD_HEAD, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-condition-sink-") as tmp:
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
            return (9999, -1, -1, label, proc.stderr[-800:])
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), label, replacement)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3]))
    print(f"cases={len(results)}")
    for full, first, length, label, replacement in results[:120]:
        print(f"FW={full:4d} FIRST={first:3d} LEN={length:3d} {label}")
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
