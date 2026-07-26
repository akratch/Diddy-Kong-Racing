#!/usr/bin/env python3
"""Sweep same-size integer declaration slots against target GPR allocation."""

from __future__ import annotations

import itertools
import pathlib
import random
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
TARGET = ORACLE["TARGET_INSNS"]
BASE = pathlib.Path("/tmp/codex_gpr_topology_039.c").read_text(encoding="utf-8")
RUNNER = "/tmp/codex_run_analysis.sh"

FUNCTION = BASE.index("void func_80049794")
BODY = BASE.index("\n\n    if (func_8000E138())", FUNCTION)
PREFIX = BASE[:FUNCTION]
DECL_REGION = BASE[FUNCTION:BODY]
SUFFIX = BASE[BODY:]

DECL_PATTERN = re.compile(r"^    s32 ([A-Za-z_][A-Za-z0-9_]*);$", re.MULTILINE)
NAMES = DECL_PATTERN.findall(DECL_REGION)


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def metrics(obj: pathlib.Path) -> dict[str, object]:
    _, candidate = ORACLE["dump_object"](str(obj))
    if len(candidate) != len(TARGET):
        return {"insns": len(candidate), "regs": 100000, "fp": 100000}
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    fp_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if re.findall(r"\$f\d+", expected[1])
        != re.findall(r"\$f\d+", actual[1])
    ]
    return {
        "insns": len(candidate),
        "regs": len(reg_bad),
        "fp": len(fp_bad),
        "reg_bad": reg_bad,
    }


def source_for(order: tuple[str, ...]) -> str:
    iterator = iter(order)
    declarations = DECL_PATTERN.sub(lambda _: f"    s32 {next(iterator)};", DECL_REGION)
    return PREFIX + declarations + SUFFIX


def cases() -> list[tuple[str, tuple[str, ...]]]:
    original = tuple(NAMES)
    result = [("baseline", original)]
    for left, right in itertools.combinations(range(len(original)), 2):
        order = list(original)
        order[left], order[right] = order[right], order[left]
        result.append((f"swap_{original[left]}_{original[right]}", tuple(order)))

    rng = random.Random(0x80049794)
    for index in range(100):
        order = list(original)
        rng.shuffle(order)
        result.append((f"random_{index:03d}", tuple(order)))
    return result


def main() -> None:
    print("integer declarations", len(NAMES), NAMES)
    results = []
    for serial, (tag, order) in enumerate(cases()):
        source = source_for(order)
        source_path = pathlib.Path(f"/tmp/codex_idecl_{serial:03d}.c")
        obj_path = pathlib.Path(f"/tmp/codex_idecl_{serial:03d}.o")
        source_path.write_text(source, encoding="utf-8")
        proc = subprocess.run(
            [RUNNER, str(source_path), str(obj_path), str(obj_path) + ".trace"],
            check=False,
            capture_output=True,
            text=True,
        )
        result = metrics(obj_path) if proc.returncode == 0 else {
            "regs": 100000,
            "fp": 100000,
            "error": proc.stderr[-600:],
        }
        results.append((result["regs"], result["fp"], tag, serial, order, result))
        if serial % 25 == 0 or result["regs"] < 45 or result["fp"] != 0:
            print(serial, tag, {key: value for key, value in result.items() if key != "reg_bad"}, flush=True)

    print("\nBEST")
    for row in sorted(results)[:20]:
        reg_count, fp_count, tag, serial, order, result = row
        source = source_for(order)
        natural = ORACLE["evaluate"](source)
        print(
            reg_count,
            fp_count,
            tag,
            serial,
            ORACLE["concise"](natural),
            result.get("reg_bad"),
            order,
        )


if __name__ == "__main__":
    main()
