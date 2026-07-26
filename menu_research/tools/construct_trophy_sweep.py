#!/usr/bin/env python3
"""Search decision-distinct trophy expressions in the v_zz1 construction basin."""

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
VARIANT = (ROOT / "menu_research" / "variants" / "v_zz1.txt").read_text().rstrip()
TARGET = TOOLS / "target.o"
OBJDUMP = ROOT / "tools" / "binutils" / "mips64-elf-objdump"
COMPILE = TOOLS / "compile.sh"


def build_variant(base: str, variant: str) -> str:
    if not variant.startswith("===FROM==="):
        raise ValueError("construction sweep expects a whole-function variant")
    _, rest = variant.split("===FROM===\n", 1)
    start, rest = rest.split("\n===TO===\n", 1)
    end, code = rest.split("\n===CODE===\n", 1)
    i = base.index(start)
    j = base.index(end, i) + len(end)
    return base[:i] + code + base[j:]


SOURCE = build_variant(BASE, VARIANT)
OLD = "((settings->trophies >> (trackY * 2)) & 3) == 3"
if SOURCE.count(OLD) != 1:
    raise RuntimeError(f"expected one trophy expression, got {SOURCE.count(OLD)}")


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


def unique(items: list[tuple[str, str]]) -> list[tuple[str, str]]:
    seen: set[str] = set()
    result: list[tuple[str, str]] = []
    for label, expression in items:
        if expression not in seen:
            seen.add(expression)
            result.append((label, expression))
    return result


counts = {
    "mul": "(trackY * 2)",
    "shl": "(trackY << 1)",
    "add": "(trackY + trackY)",
    "rmul": "(2 * trackY)",
    "uadd": "((u32) trackY + (u32) trackY)",
}
loads = {
    "field": "settings->trophies",
    "deref": "(*((u16 *) ((u8 *) settings + 0xE)))",
    "index": "((u16 *) settings)[7]",
}
items: list[tuple[str, str]] = []
for count_name, count in counts.items():
    for load_name, load in loads.items():
        shift = f"({load} >> {count})"
        low = f"({shift} & 3)"
        items.extend(
            [
                (f"{count_name}-{load_name}-plain", f"{low} == 3"),
                (f"{count_name}-{load_name}-reverse", f"3 == {low}"),
                (f"{count_name}-{load_name}-u3", f"({shift} & 3U) == 3U"),
                (f"{count_name}-{load_name}-and-reverse", f"(3 & {shift}) == 3"),
                (f"{count_name}-{load_name}-mod", f"({shift} % 4) == 3"),
                (f"{count_name}-{load_name}-ge", f"{low} >= 3"),
                (f"{count_name}-{load_name}-gt", f"{low} > 2"),
                (f"{count_name}-{load_name}-xor-not", f"!({low} ^ 3)"),
                (f"{count_name}-{load_name}-ne-not", f"!({low} != 3)"),
            ]
        )
        for typename in ("s32", "u32", "s16", "u16", "s8", "u8"):
            items.extend(
                [
                    (
                        f"{count_name}-{load_name}-cast-shift-{typename}",
                        f"((( {typename}) {shift}) & 3) == 3",
                    ),
                    (
                        f"{count_name}-{load_name}-cast-low-{typename}",
                        f"(({typename}) {low}) == 3",
                    ),
                    (
                        f"{count_name}-{load_name}-cast-compare-{typename}",
                        f"{low} == ({typename}) 3",
                    ),
                ]
            )
        identities = {
            "plus0": f"({shift} + 0)",
            "minus0": f"({shift} - 0)",
            "or0": f"({shift} | 0)",
            "xor0": f"({shift} ^ 0)",
            "mul1": f"({shift} * 1)",
            "andm1": f"({shift} & -1)",
            "and32": f"({shift} & 0xFFFFFFFF)",
            "maskull": f"((s32) ({shift} & 0xFFFFFFFFFFFFFFFF))",
            "maskll": f"((s32) ({shift} & 0xFFFFFFFFFFFFFFFFLL))",
            "widenull": f"((s32) (unsigned long long) {shift})",
            "widenll": f"((s32) (long long) {shift})",
        }
        for identity_name, identity in identities.items():
            items.append(
                (
                    f"{count_name}-{load_name}-{identity_name}",
                    f"({identity} & 3) == 3",
                )
            )
        items.extend(
            [
                (
                    f"{count_name}-{load_name}-mask-after-low-ull",
                    f"((s32) ({low} & 0xFFFFFFFFFFFFFFFF)) == 3",
                ),
                (
                    f"{count_name}-{load_name}-mask-after-low-ll",
                    f"((s32) ({low} & 0xFFFFFFFFFFFFFFFFLL)) == 3",
                ),
                (
                    f"{count_name}-{load_name}-ternary",
                    f"({low} ? {low} : {low}) == 3",
                ),
                (
                    f"{count_name}-{load_name}-comma",
                    f"(0, {low}) == 3",
                ),
            ]
        )

CASES = unique(items)


def evaluate(case: tuple[str, str]) -> tuple[int, int, int, str, str]:
    label, expression = case
    source = SOURCE.replace(OLD, expression, 1)
    with tempfile.TemporaryDirectory(prefix="menu-trophy-") as tmp:
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
            return (9999, -1, -1, label, proc.stderr[-500:])
        got = words(obj)
    diffs = [i for i, (left, right) in enumerate(zip(got, WANT)) if left != right]
    full = len(diffs) + abs(len(got) - len(WANT))
    first = diffs[0] if diffs else min(len(got), len(WANT))
    return (full, first, len(got), label, expression)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3]))
    print(f"cases={len(results)}")
    for result in results[:80]:
        print(
            f"FW={result[0]:4d} FIRST={result[1]:3d} LEN={result[2]:3d} "
            f"{result[3]} :: {result[4]}"
        )
    late = [row for row in results if row[1] >= 120]
    print(f"first_diff>=120: {len(late)}")
    for result in late[:120]:
        print(
            f"LATE FW={result[0]:4d} FIRST={result[1]:3d} LEN={result[2]:3d} "
            f"{result[3]} :: {result[4]}"
        )
    matches = [row for row in results if row[0] == 0 and row[2] == len(WANT)]
    if matches:
        print("MATCHES")
        for result in matches:
            print(result)


if __name__ == "__main__":
    main()
