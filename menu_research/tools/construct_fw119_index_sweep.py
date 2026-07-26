#!/usr/bin/env python3
"""Search index/address topologies from the exact-condition FW119 basin.

This basin already has the target lh/li/beq/store and target t3 multiply.  Its
queue is [t3,t2,t4,t5,...] at index entry, so one move-only conversion on the
address DAG could consume t2 and make the existing address result/base load
land in target t4/t5.  Pointer/int conversions are especially interesting:
they are representation-preserving on MIPS32 but can survive CFE as typed
Ucode nodes.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_condition_sweep as conditions
import construct_index_sweep as core


FW119_REPLACEMENT = """\
                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFFLL;
                pad = pad & 0xFFFFFFFFFFFFFFFFULL;
                pad = pad & 0xFFFFFFFFFFFFFFFFULL;
                pad = (s32)(s64)pad;
                cur->hubName = trackName;
                if ((pad != -1)) {"""
SOURCE = conditions.SOURCE.replace(
    conditions.OLD_COND, FW119_REPLACEMENT, 1
)
OLD_DECL = "    s32 new_var;"
OLD_FIRST = "trackMenuIds[(new_var = trackY * 6) + trackX]"
OLD_SECOND = "trackMenuIds[new_var + trackX]"
for needle in (OLD_DECL, OLD_FIRST, OLD_SECOND):
    if SOURCE.count(needle) != 1:
        raise RuntimeError(f"expected one occurrence of {needle!r}")


# Start with the broad, previously useful index-lifetime catalogue.
SHAPES: list[tuple[str, str, str, str]] = list(core.unique_shapes)

# Same 32-bit arithmetic, expressed through representation-preserving typed
# boundaries.  `first` and `second` are complete byte-producing expressions.
base_exprs = {
    "base": "(new_var = trackY * 6) + trackX",
    "base-reverse": "trackX + (new_var = trackY * 6)",
    "whole": "(new_var = trackY * 6 + trackX)",
    "comma": "(new_var = trackY * 6, new_var + trackX)",
}
second_exprs = {
    "base": "new_var + trackX",
    "reverse": "trackX + new_var",
}
casts = {
    "plain": "{}",
    "s32": "(s32)({})",
    "u32": "(u32)({})",
    "ptr-s32": "(s32)(void *)({})",
    "ptr-u32": "(u32)(void *)({})",
    "s32-ptr-s32": "(s32)(void *)(s32)({})",
    "u32-ptr-u32": "(u32)(void *)(u32)({})",
    "charptr-s32": "(s32)(char *)({})",
}
for base_label, first in base_exprs.items():
    for second_label, second in second_exprs.items():
        for cast_label, cast in casts.items():
            SHAPES.append(
                (
                    f"typed-index-{base_label}-{second_label}-{cast_label}",
                    "    s32 new_var;",
                    cast.format(first),
                    cast.format(second),
                )
            )

# Complete load expressions allow typed conversions on the pointer base, not
# just on the integer subscript.
BASE_WRAPS = {
    "plain": "trackMenuIds",
    "void": "(s8 *)(void *)trackMenuIds",
    "s32": "(s8 *)(s32)trackMenuIds",
    "u32": "(s8 *)(u32)trackMenuIds",
    "s32-roundtrip": "(s8 *)(s32)(void *)trackMenuIds",
    "u32-roundtrip": "(s8 *)(u32)(void *)trackMenuIds",
    "char-roundtrip": "(s8 *)(char *)trackMenuIds",
    "const-roundtrip": "(s8 *)(const s8 *)trackMenuIds",
}
LOAD_SHAPES: list[tuple[str, str, str, str]] = []
for base_label, base in BASE_WRAPS.items():
    LOAD_SHAPES.extend(
        [
            (
                f"basewrap-{base_label}-subscript",
                "    s32 new_var;",
                f"{base}[(new_var = trackY * 6) + trackX]",
                f"{base}[new_var + trackX]",
            ),
            (
                f"basewrap-{base_label}-deref",
                "    s32 new_var;",
                f"*({base} + ((new_var = trackY * 6) + trackX))",
                f"*({base} + (new_var + trackX))",
            ),
            (
                f"basewrap-{base_label}-reverse-deref",
                "    s32 new_var;",
                f"*(((new_var = trackY * 6) + trackX) + {base})",
                f"*((new_var + trackX) + {base})",
            ),
        ]
    )


def evaluate_index(
    case: tuple[str, str, str, str]
) -> tuple[int, int, int, str, str, str, str]:
    label, declaration, first, second = case
    source = SOURCE.replace(OLD_DECL, declaration, 1)
    source = source.replace(
        OLD_FIRST, f"trackMenuIds[{first}]", 1
    )
    source = source.replace(
        OLD_SECOND, f"trackMenuIds[{second}]", 1
    )
    return evaluate_source(label, declaration, first, second, source)


def evaluate_load(
    case: tuple[str, str, str, str]
) -> tuple[int, int, int, str, str, str, str]:
    label, declaration, first, second = case
    source = SOURCE.replace(OLD_DECL, declaration, 1)
    source = source.replace(OLD_FIRST, first, 1)
    source = source.replace(OLD_SECOND, second, 1)
    return evaluate_source(label, declaration, first, second, source)


def evaluate_source(
    label: str,
    declaration: str,
    first: str,
    second: str,
    source: str,
) -> tuple[int, int, int, str, str, str, str]:
    with tempfile.TemporaryDirectory(prefix="menu-fw119-index-") as tmp:
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
                9999, -1, -1, label, declaration, first, proc.stderr[-800:]
            )
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first_diff = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (
        full, first_diff, len(got), label, declaration, first, second
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        index_results = list(executor.map(evaluate_index, SHAPES))
        load_results = list(executor.map(evaluate_load, LOAD_SHAPES))
    results = [*index_results, *load_results]
    results.sort(key=lambda row: (row[0], -row[1], row[3]))
    print(
        f"cases={len(results)} index={len(SHAPES)} "
        f"load={len(LOAD_SHAPES)}"
    )
    for full, first, length, label, declaration, one, two in results[:160]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} {label} "
            f":: {one} / {two}"
        )
        if full == 0:
            print(declaration)


if __name__ == "__main__":
    main()
