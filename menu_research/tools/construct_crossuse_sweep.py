#!/usr/bin/env python3
"""Search shared index/trophy carriers.

Unlike spelling sweeps, these cases change the lifetime graph: a value widened
while constructing the track-menu index is also the value that determines the
trophy shift.  This can keep the pair/cast carrier across the trophy diamond
instead of freeing register 11 at the index boundary.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core


OLD_TROPHY = "settings->trophies >> (trackY * 2)"
if core.SOURCE.count(OLD_TROPHY) != 1:
    raise RuntimeError("trophy expression was not unique")


# label, declarations, first index, second index, shift count
SHAPES: list[tuple[str, str, str, str, str]] = []
for wide_type in ("s64", "u64", "long long", "unsigned long long"):
    decl = f"    {wide_type} wide;"
    SHAPES.extend(
        [
            (
                f"{wide_type}-y",
                decl,
                "(s32)(wide = trackY) * 6 + trackX",
                "(s32)wide * 6 + trackX",
                "(s32)wide * 2",
            ),
            (
                f"{wide_type}-2y",
                decl,
                "(s32)(wide = trackY * 2) * 3 + trackX",
                "(s32)wide * 3 + trackX",
                "(s32)wide",
            ),
            (
                f"{wide_type}-6y-div3",
                decl,
                "(s32)(wide = trackY * 6) + trackX",
                "(s32)wide + trackX",
                "(s32)(wide / 3)",
            ),
            (
                f"{wide_type}-6y-remul",
                decl,
                "(s32)(wide = trackY * 6) + trackX",
                "(s32)wide + trackX",
                "((s32)wide / 6) * 2",
            ),
            (
                f"{wide_type}-y-comma",
                decl,
                "(wide = trackY, (s32)wide * 6 + trackX)",
                "(s32)wide * 6 + trackX",
                "(s32)wide * 2",
            ),
            (
                f"{wide_type}-2y-add",
                decl,
                "(s32)(wide = trackY + trackY) * 3 + trackX",
                "(s32)wide * 3 + trackX",
                "(s32)wide",
            ),
        ]
    )

# Keep separate 32-bit and wide values live for genuinely different consumers.
for wide_type in ("s64", "u64"):
    for order in ("idx-wide", "wide-idx"):
        declarations = (
            f"    s32 idx;\n    {wide_type} wide;"
            if order == "idx-wide"
            else f"    {wide_type} wide;\n    s32 idx;"
        )
        SHAPES.extend(
            [
                (
                    f"{wide_type}-{order}-idx6-widey",
                    declarations,
                    "(wide = trackY, (idx = (s32)wide * 6) + trackX)",
                    "idx + trackX",
                    "(s32)wide * 2",
                ),
                (
                    f"{wide_type}-{order}-idx6-wide2y",
                    declarations,
                    "(wide = trackY * 2, (idx = (s32)wide * 3) + trackX)",
                    "idx + trackX",
                    "(s32)wide",
                ),
                (
                    f"{wide_type}-{order}-wide6-idx",
                    declarations,
                    "(wide = (idx = trackY * 6), idx + trackX)",
                    "idx + trackX",
                    "(s32)(wide / 3)",
                ),
            ]
        )

CASES = [
    (mask_count, *shape)
    for mask_count in range(1, 7)
    for shape in SHAPES
]


def evaluate(
    case: tuple[int, str, str, str, str, str]
) -> tuple[int, int, int, int, str, str, str, str, str]:
    mask_count, label, declarations, first, second, shift = case
    source = core.SOURCE
    source = source.replace(core.OLD_DECL, declarations, 1)
    source = source.replace(core.OLD_MASK, core.mask_source(mask_count), 1)
    source = source.replace(core.OLD_FIRST, f"trackMenuIds[{first}]", 1)
    source = source.replace(core.OLD_SECOND, f"trackMenuIds[{second}]", 1)
    source = source.replace(
        OLD_TROPHY, f"settings->trophies >> ({shift})", 1
    )
    with tempfile.TemporaryDirectory(prefix="menu-crossuse-") as tmp:
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
                mask_count,
                label,
                declarations,
                first,
                second,
                proc.stderr[-500:],
            )
        got = core.words(obj)
    diffs = [i for i, (left, right) in enumerate(zip(got, core.WANT)) if left != right]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first_diff = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (
        full,
        first_diff,
        len(got),
        mask_count,
        label,
        declarations,
        first,
        second,
        shift,
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4]))
    print(f"cases={len(results)}")
    for result in results[:120]:
        full, first, length, masks, label, declarations, index1, index2, shift = result
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"MASKS={masks} {label} :: shift={shift}"
        )
        if full == 0:
            print(declarations, index1, index2, sep="\n")


if __name__ == "__main__":
    main()
