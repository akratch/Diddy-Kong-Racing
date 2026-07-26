#!/usr/bin/env python3
"""Search index-width/lifetime constructions in the two-mask basin.

This enumerates ucode-distinct ways to keep a 32-bit index base live while a
64-bit value performs the pair allocations needed by the later trophy block.
Every candidate retains real uses in both track-name lookups; there are no
dead register burners.
"""

from __future__ import annotations

import concurrent.futures
import os
import re
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "menu_research" / "tools"
BASE = (TOOLS / "base.c").read_text()
VARIANT = (
    ROOT / "menu_research" / "variants" / "v_scratch.txt"
).read_text().rstrip()
TARGET = TOOLS / "target.o"
OBJDUMP = ROOT / "tools" / "binutils" / "mips64-elf-objdump"
COMPILE = TOOLS / "compile.sh"


def build_variant(base: str, variant: str) -> str:
    _, rest = variant.split("===FROM===\n", 1)
    start, rest = rest.split("\n===TO===\n", 1)
    end, code = rest.split("\n===CODE===\n", 1)
    i = base.index(start)
    j = base.index(end, i) + len(end)
    return base[:i] + code + base[j:]


SOURCE = build_variant(BASE, VARIANT)
OLD_DECL = "    long long new_var;"
OLD_MASK = """\
                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFF;
                pad = pad & 0xFFFFFFFFFFFFFFFF;"""
OLD_FIRST = "trackMenuIds[(new_var = trackY * 6) + trackX]"
OLD_SECOND = "trackMenuIds[new_var + trackX]"
for needle in (OLD_DECL, OLD_MASK, OLD_FIRST, OLD_SECOND):
    if SOURCE.count(needle) != 1:
        raise RuntimeError(f"expected one occurrence of {needle!r}")


def reloc_masks(path: Path) -> dict[int, int]:
    output = subprocess.run(
        [OBJDUMP, "-r", path], check=True, capture_output=True, text=True
    ).stdout
    masks: dict[int, int] = {}
    for line in output.splitlines():
        match = re.match(r"([0-9a-f]+)\s+(R_MIPS_\S+)", line)
        if not match:
            continue
        offset = int(match.group(1), 16)
        kind = match.group(2)
        if kind in {"R_MIPS_LO16", "R_MIPS_HI16", "R_MIPS_GOT16", "R_MIPS_CALL16"}:
            masks[offset] = 0xFFFF0000
        elif kind == "R_MIPS_26":
            masks[offset] = 0xFC000000
    return masks


def words(path: Path) -> list[int]:
    output = subprocess.run(
        [OBJDUMP, "-d", path], check=True, capture_output=True, text=True
    ).stdout
    masks = reloc_masks(path)
    active = False
    result: list[int] = []
    for line in output.splitlines():
        if "<func_8008FF1C>:" in line:
            active = True
            continue
        if not active:
            continue
        match = re.match(r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+", line)
        if match:
            offset = int(match.group(1), 16)
            result.append(int(match.group(2), 16) & masks.get(offset, 0xFFFFFFFF))
        elif not line.strip():
            break
    return result


WANT = words(TARGET)


def mask_source(count: int) -> str:
    lines = [
        "                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFF;"
    ]
    lines.extend(
        "                pad = pad & 0xFFFFFFFFFFFFFFFF;" for _ in range(count - 1)
    )
    return "\n".join(lines)


# label, declarations, first subscript body, second subscript body
SHAPES: list[tuple[str, str, str, str]] = []

for typename in ("s32", "u32", "s64", "u64", "long long", "unsigned long long"):
    decl = f"    {typename} new_var;"
    SHAPES.extend(
        [
            (
                f"{typename}-base",
                decl,
                "(new_var = trackY * 6) + trackX",
                "new_var + trackX",
            ),
            (
                f"{typename}-cast-base",
                decl,
                "(s32)(new_var = trackY * 6) + trackX",
                "(s32)new_var + trackX",
            ),
            (
                f"{typename}-cast-sum",
                decl,
                "(s32)((new_var = trackY * 6) + trackX)",
                "(s32)(new_var + trackX)",
            ),
            (
                f"{typename}-whole",
                decl,
                "(new_var = trackY * 6 + trackX)",
                "new_var",
            ),
            (
                f"{typename}-cast-whole",
                decl,
                "(s32)(new_var = trackY * 6 + trackX)",
                "(s32)new_var",
            ),
            (
                f"{typename}-comma",
                decl,
                "(new_var = trackY * 6, (s32)new_var + trackX)",
                "(s32)new_var + trackX",
            ),
        ]
    )

SHAPES.extend(
    [
        (
            "natural",
            "    s32 new_var;",
            "(trackY * 6) + trackX",
            "(trackY * 6) + trackX",
        ),
        (
            "variable-free-s64-cast",
            "    s64 new_var;",
            "(s32)(s64)(trackY * 6) + trackX",
            "(s32)(s64)(trackY * 6) + trackX",
        ),
        (
            "variable-free-u64-cast",
            "    u64 new_var;",
            "(s32)(u64)(trackY * 6) + trackX",
            "(s32)(u64)(trackY * 6) + trackX",
        ),
        (
            "s64-wide-and-raw",
            "    s64 new_var;",
            "(new_var = trackY * 6, trackY * 6 + trackX)",
            "(s32)new_var + trackX",
        ),
        (
            "s64-wide-and-raw-second-raw",
            "    s64 new_var;",
            "(new_var = trackY * 6, trackY * 6 + trackX)",
            "trackY * 6 + trackX",
        ),
        (
            "u64-wide-and-raw",
            "    u64 new_var;",
            "(new_var = trackY * 6, trackY * 6 + trackX)",
            "(s32)new_var + trackX",
        ),
        (
            "u64-wide-and-raw-second-raw",
            "    u64 new_var;",
            "(new_var = trackY * 6, trackY * 6 + trackX)",
            "trackY * 6 + trackX",
        ),
        (
            "s64-wide-and-raw-cast",
            "    s64 new_var;",
            "(new_var = trackY * 6, (s32)(trackY * 6) + trackX)",
            "(s32)new_var + trackX",
        ),
        (
            "u64-wide-and-raw-cast",
            "    u64 new_var;",
            "(new_var = trackY * 6, (s32)(trackY * 6) + trackX)",
            "(s32)new_var + trackX",
        ),
    ]
)

two_var_shapes = [
    (
        "idx-from-wide",
        "(idx = (s32)(wide = trackY * 6)) + trackX",
        "idx + trackX",
    ),
    (
        "wide-from-idx-use-idx",
        "(wide = (idx = trackY * 6), idx + trackX)",
        "(s32)wide + trackX",
    ),
    (
        "wide-from-idx-use-wide",
        "(wide = (idx = trackY * 6), (s32)wide + trackX)",
        "idx + trackX",
    ),
    (
        "wide-from-idx-both-wide",
        "(wide = (idx = trackY * 6), (s32)wide + trackX)",
        "(s32)wide + trackX",
    ),
    (
        "idx-from-wide-use-wide",
        "(idx = (s32)(wide = trackY * 6)) + trackX",
        "(s32)wide + trackX",
    ),
    (
        "whole-wide-idx",
        "(wide = (idx = trackY * 6) + trackX, idx + trackX)",
        "(s32)wide",
    ),
    (
        "whole-idx-wide",
        "(idx = (s32)(wide = trackY * 6 + trackX))",
        "idx",
    ),
]
for wide_type in ("s64", "u64"):
    for order in ("idx-wide", "wide-idx"):
        decls = (
            f"    s32 idx;\n    {wide_type} wide;"
            if order == "idx-wide"
            else f"    {wide_type} wide;\n    s32 idx;"
        )
        for label, first, second in two_var_shapes:
            SHAPES.append(
                (f"{wide_type}-{order}-{label}", decls, first, second)
            )

# Preserve insertion order while quotienting identical source triples.
unique_shapes: list[tuple[str, str, str, str]] = []
seen_shapes: set[tuple[str, str, str]] = set()
for label, declarations, first, second in SHAPES:
    key = (declarations, first, second)
    if key not in seen_shapes:
        seen_shapes.add(key)
        unique_shapes.append((label, declarations, first, second))

CASES = [
    (mask_count, label, declarations, first, second)
    for mask_count in range(1, 7)
    for label, declarations, first, second in unique_shapes
]


def evaluate(
    case: tuple[int, str, str, str, str]
) -> tuple[int, int, int, int, str, str, str, str]:
    mask_count, label, declarations, first, second = case
    source = SOURCE
    source = source.replace(OLD_DECL, declarations, 1)
    source = source.replace(OLD_MASK, mask_source(mask_count), 1)
    source = source.replace(OLD_FIRST, f"trackMenuIds[{first}]", 1)
    source = source.replace(OLD_SECOND, f"trackMenuIds[{second}]", 1)
    with tempfile.TemporaryDirectory(prefix="menu-index-") as tmp:
        directory = Path(tmp)
        src = directory / "candidate.c"
        obj = directory / "candidate.o"
        src.write_text(source)
        obj.touch()
        proc = subprocess.run(
            ["bash", COMPILE, src, "-o", obj],
            cwd=ROOT,
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
                proc.stderr[-500:],
            )
        got = words(obj)
    diffs = [i for i, (left, right) in enumerate(zip(got, WANT)) if left != right]
    full = len(diffs) + abs(len(got) - len(WANT))
    first_diff = diffs[0] if diffs else min(len(got), len(WANT))
    return (
        full,
        first_diff,
        len(got),
        mask_count,
        label,
        declarations,
        first,
        second,
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3], row[4]))
    print(f"cases={len(results)} shapes={len(unique_shapes)}")
    for result in results[:100]:
        full, first_diff, length, masks, label, declarations, first, second = result
        print(
            f"FW={full:4d} FIRST={first_diff:3d} LEN={length:3d} "
            f"MASKS={masks} {label} :: [{first}] / [{second}]"
        )
        if full == 0:
            print(declarations)
    late = [row for row in results if row[1] >= 120]
    print(f"first_diff>=120: {len(late)}")
    for result in late[:100]:
        print(
            f"LATE FW={result[0]:4d} FIRST={result[1]:3d} LEN={result[2]:3d} "
            f"MASKS={result[3]} {result[4]}"
        )


if __name__ == "__main__":
    main()
