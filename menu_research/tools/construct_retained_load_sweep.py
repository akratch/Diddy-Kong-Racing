#!/usr/bin/env python3
"""Retain the original track-ID load until the branch predicate consumes it.

Trace of the FW35 basin shows the exact target queue can be obtained if the
pool-loaded t2 has two logical references: the widening/mask chain consumes
the first, and the branch predicate consumes the second after the three pair
events.  Its final death then appends t2 behind t3, leaving t3/t4/t5 for the
index exactly as in the ROM.

These cases capture the required load in an existing local as part of the
widening expression, and vary where the predicate is formed relative to the
already-required hubName store.  All retained values have semantic uses.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_condition_sweep as conditions
import construct_index_sweep as core


SOURCE = conditions.SOURCE
LOAD = "gTrackSelectIDs[pad][trackX]"
LOAD_Y = "gTrackSelectIDs[trackY][trackX]"
OLD_REGION = """\
                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFF;
                pad = pad & 0xFFFFFFFFFFFFFFFF;
                cur->hubName = trackName;
                if ((pad != -1)) {"""
if SOURCE.count(OLD_REGION) != 1:
    raise RuntimeError("expected one original load/condition region")

MASK2 = [
    "pad = pad & 0xFFFFFFFFFFFFFFFFULL;",
    "pad = pad & 0xFFFFFFFFFFFFFFFFULL;",
]

LOAD_FORMS: dict[str, list[str]] = {
    "baseline": [
        f"pad = ({LOAD}) & 0xFFFFFFFFFFFFFFFFLL;",
    ],
    "capture-inside-and": [
        f"pad = (pad2 = {LOAD}) & 0xFFFFFFFFFFFFFFFFLL;",
    ],
    "capture-inside-cast-and": [
        f"pad = ((s64)(pad2 = {LOAD})) & 0xFFFFFFFFFFFFFFFFLL;",
    ],
    "capture-wide-result-chain": [
        f"pad = pad2 = ({LOAD}) & 0xFFFFFFFFFFFFFFFFLL;",
    ],
    "capture-wide-result-nested": [
        f"pad = (pad2 = (({LOAD}) & 0xFFFFFFFFFFFFFFFFLL));",
    ],
    "capture-first-separate": [
        f"pad2 = {LOAD};",
        "pad = pad2 & 0xFFFFFFFFFFFFFFFFLL;",
    ],
    "capture-first-comma": [
        f"pad = (pad2 = {LOAD}, pad2 & 0xFFFFFFFFFFFFFFFFLL);",
    ],
    "capture-roundtrip": [
        f"pad = (pad2 = (s32)(s64)({LOAD}));",
    ],
    "capture-roundtrip-and": [
        f"pad = (pad2 = (s32)(s64)({LOAD})) & 0xFFFFFFFFFFFFFFFFLL;",
    ],
    "capture-after-wide-comma": [
        f"pad = (({LOAD}) & 0xFFFFFFFFFFFFFFFFLL);",
        "pad2 = pad;",
    ],
    "tracky-baseline": [
        f"pad = ({LOAD_Y}) & 0xFFFFFFFFFFFFFFFFLL;",
    ],
}


# (lines before hubName store, hubName/condition lines)
TAIL_FORMS: dict[str, tuple[list[str], list[str]]] = {
    "store-cast-pad": (
        [],
        [
            "cur->hubName = trackName;",
            "if (((s32)(s64)pad != -1)) {",
        ],
    ),
    "store-plain-pad": (
        ["pad = (s32)(s64)pad;"],
        [
            "cur->hubName = trackName;",
            "if ((pad != -1)) {",
        ],
    ),
    "store-captured-pad2": (
        [],
        [
            "cur->hubName = trackName;",
            "if (((s32)(s64)pad2 != -1)) {",
        ],
    ),
    "store-captured-pad2-plain": (
        [],
        [
            "cur->hubName = trackName;",
            "if ((pad2 != -1)) {",
        ],
    ),
    "prevalue-pad2": (
        ["pad2 = (s32)(s64)pad;"],
        [
            "cur->hubName = trackName;",
            "if ((pad2 != -1)) {",
        ],
    ),
    "prevalue-pad": (
        ["pad = (s32)(s64)pad;"],
        [
            "cur->hubName = trackName;",
            "if ((pad != -1)) {",
        ],
    ),
    "prebool-pad2": (
        ["pad2 = ((s32)(s64)pad != -1);"],
        [
            "cur->hubName = trackName;",
            "if ((pad2)) {",
        ],
    ),
    "prebool-temp-from-pad": (
        ["temp = ((s32)(s64)pad != -1);"],
        [
            "cur->hubName = trackName;",
            "if ((temp)) {",
        ],
    ),
    "prebool-temp-from-capture": (
        ["temp = ((s32)(s64)pad2 != -1);"],
        [
            "cur->hubName = trackName;",
            "if ((temp)) {",
        ],
    ),
    "bool-in-store-rhs": (
        [],
        [
            "cur->hubName = (temp = ((s32)(s64)pad != -1), trackName);",
            "if ((temp)) {",
        ],
    ),
    "capture-bool-in-store-rhs": (
        [],
        [
            "cur->hubName = (temp = ((s32)(s64)pad2 != -1), trackName);",
            "if ((temp)) {",
        ],
    ),
    "store-in-if-comma-pad": (
        [],
        [
            "if ((cur->hubName = trackName, (s32)(s64)pad != -1)) {",
        ],
    ),
    "store-in-if-comma-capture": (
        [],
        [
            "if ((cur->hubName = trackName, (s32)(s64)pad2 != -1)) {",
        ],
    ),
    "bool-and-store-in-if-pad": (
        [],
        [
            "if ((temp = ((s32)(s64)pad != -1), "
            "cur->hubName = trackName, temp)) {",
        ],
    ),
    "bool-and-store-in-if-capture": (
        [],
        [
            "if ((temp = ((s32)(s64)pad2 != -1), "
            "cur->hubName = trackName, temp)) {",
        ],
    ),
    "raw-tracky-prevalue-pad2": (
        [f"pad2 = {LOAD_Y};"],
        [
            "cur->hubName = trackName;",
            "if ((pad2 != -1)) {",
        ],
    ),
    "raw-tracky-prevalue-temp": (
        [f"temp = {LOAD_Y};"],
        [
            "cur->hubName = trackName;",
            "if ((temp != -1)) {",
        ],
    ),
    "raw-tracky-prebool-pad2": (
        [f"pad2 = ({LOAD_Y} != -1);"],
        [
            "cur->hubName = trackName;",
            "if ((pad2)) {",
        ],
    ),
    "raw-tracky-prebool-temp": (
        [f"temp = ({LOAD_Y} != -1);"],
        [
            "cur->hubName = trackName;",
            "if ((temp)) {",
        ],
    ),
    "raw-tracky-value-in-store": (
        [],
        [
            f"cur->hubName = (pad2 = {LOAD_Y}, trackName);",
            "if ((pad2 != -1)) {",
        ],
    ),
    "raw-tracky-bool-in-store": (
        [],
        [
            f"cur->hubName = (pad2 = ({LOAD_Y} != -1), trackName);",
            "if ((pad2)) {",
        ],
    ),
    "raw-tracky-value-and-store-in-if": (
        [],
        [
            f"if ((pad2 = {LOAD_Y}, cur->hubName = trackName, "
            "pad2 != -1)) {",
        ],
    ),
    "raw-tracky-bool-and-store-in-if": (
        [],
        [
            f"if ((pad2 = ({LOAD_Y} != -1), "
            "cur->hubName = trackName, pad2)) {",
        ],
    ),
    "raw-condition-store-add-zero": (
        [],
        [
            f"if ((({LOAD_Y} != -1) + "
            "(cur->hubName = trackName, 0))) {",
        ],
    ),
    "raw-condition-store-sub-zero": (
        [],
        [
            f"if ((({LOAD_Y} != -1) - "
            "(cur->hubName = trackName, 0))) {",
        ],
    ),
    "raw-condition-store-xor-zero": (
        [],
        [
            f"if ((({LOAD_Y} != -1) ^ "
            "(cur->hubName = trackName, 0))) {",
        ],
    ),
    "raw-condition-store-or-zero": (
        [],
        [
            f"if ((({LOAD_Y} != -1) | "
            "(cur->hubName = trackName, 0))) {",
        ],
    ),
    "raw-condition-store-and-one": (
        [],
        [
            f"if ((({LOAD_Y} != -1) & "
            "(cur->hubName = trackName, 1))) {",
        ],
    ),
    "raw-condition-store-mul-one": (
        [],
        [
            f"if ((({LOAD_Y} != -1) * "
            "(cur->hubName = trackName, 1))) {",
        ],
    ),
    "store-zero-add-raw-condition": (
        [],
        [
            f"if (((cur->hubName = trackName, 0) + "
            f"({LOAD_Y} != -1))) {{",
        ],
    ),
    "store-zero-xor-raw-condition": (
        [],
        [
            f"if (((cur->hubName = trackName, 0) ^ "
            f"({LOAD_Y} != -1))) {{",
        ],
    ),
    "store-zero-or-raw-condition": (
        [],
        [
            f"if (((cur->hubName = trackName, 0) | "
            f"({LOAD_Y} != -1))) {{",
        ],
    ),
    "store-one-and-raw-condition": (
        [],
        [
            f"if (((cur->hubName = trackName, 1) & "
            f"({LOAD_Y} != -1))) {{",
        ],
    ),
    "store-one-mul-raw-condition": (
        [],
        [
            f"if (((cur->hubName = trackName, 1) * "
            f"({LOAD_Y} != -1))) {{",
        ],
    ),
    "raw-condition-ternary-store": (
        [],
        [
            f"if (({LOAD_Y} != -1) ? "
            "(cur->hubName = trackName, 1) : "
            "(cur->hubName = trackName, 0)) {",
        ],
    ),
    "raw-equal-ternary-store": (
        [],
        [
            f"if (({LOAD_Y} == -1) ? "
            "(cur->hubName = trackName, 0) : "
            "(cur->hubName = trackName, 1)) {",
        ],
    ),
}


def render(load_lines: list[str], tail: tuple[list[str], list[str]]) -> str:
    before_store, ending = tail
    lines = [*load_lines, *MASK2, *before_store, *ending]
    return "\n".join(f"                {line}" for line in lines)


CASES = [
    (
        f"{load_label}-{tail_label}",
        render(load_lines, tail),
    )
    for load_label, load_lines in LOAD_FORMS.items()
    for tail_label, tail in TAIL_FORMS.items()
]

# Keep the entire mask/predicate DAG in one full expression.  This can retain
# the ILOD as an expression temporary instead of promoting it to a colored
# local web, which is what the statement-separated duplicate-load forms do.
GIANT_PREDICATES = {
    "raw-add-store-zero": (
        f"({LOAD_Y} != -1) + (cur->hubName = trackName, 0)"
    ),
    "raw-sub-store-zero": (
        f"({LOAD_Y} != -1) - (cur->hubName = trackName, 0)"
    ),
    "raw-xor-store-zero": (
        f"({LOAD_Y} != -1) ^ (cur->hubName = trackName, 0)"
    ),
    "raw-or-store-zero": (
        f"({LOAD_Y} != -1) | (cur->hubName = trackName, 0)"
    ),
    "raw-mul-store-one": (
        f"({LOAD_Y} != -1) * (cur->hubName = trackName, 1)"
    ),
    "store-zero-add-raw": (
        f"(cur->hubName = trackName, 0) + ({LOAD_Y} != -1)"
    ),
    "store-zero-xor-raw": (
        f"(cur->hubName = trackName, 0) ^ ({LOAD_Y} != -1)"
    ),
    "store-zero-or-raw": (
        f"(cur->hubName = trackName, 0) | ({LOAD_Y} != -1)"
    ),
    "store-one-mul-raw": (
        f"(cur->hubName = trackName, 1) * ({LOAD_Y} != -1)"
    ),
    "raw-ternary-store": (
        f"({LOAD_Y} != -1) ? "
        "(cur->hubName = trackName, 1) : "
        "(cur->hubName = trackName, 0)"
    ),
    "pad-add-store-zero": (
        "(s32)(s64)pad != -1) + (cur->hubName = trackName, 0"
    ),
}
for label, predicate in GIANT_PREDICATES.items():
    # The pad predicate entry is written without its exterior parens above so
    # it can use the same formatting as the raw predicate entries.
    if label == "pad-add-store-zero":
        predicate = (
            "((s32)(s64)pad != -1) + "
            "(cur->hubName = trackName, 0)"
        )
    replacement = "\n".join(
        [
            "                if ((",
            f"                    pad = ({LOAD_Y}) & 0xFFFFFFFFFFFFFFFFLL,",
            "                    pad = pad & 0xFFFFFFFFFFFFFFFFULL,",
            "                    pad = pad & 0xFFFFFFFFFFFFFFFFULL,",
            f"                    ({predicate})",
            "                )) {",
        ]
    )
    CASES.append((f"giant-{label}", replacement))


def evaluate(case: tuple[str, str]) -> tuple[int, int, int, str, str]:
    label, replacement = case
    source = SOURCE.replace(OLD_REGION, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-retained-load-") as tmp:
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
