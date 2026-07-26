#!/usr/bin/env python3
"""Raise the spinout original-rotation web priority with late-folded zero uses."""

from __future__ import annotations

import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path(
    "/tmp/codex_gpr_combined_001_spin_offset_var_v1.c"
).read_text(encoding="utf-8")
TARGET = ORACLE["TARGET_INSNS"]
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"
OLD = """\
        var_v1 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v1 * updateRate) >> 4;
"""
ROT = "obj->trans.rotation.x_rotation"


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def body(zero: str, position: str, repetitions: int) -> str:
    zero_sum = " + ".join(f"({zero})" for _ in range(repetitions))
    masked = f"({ROT} & 0xFFFF)"
    high = "0x8000"
    low = "-0x8000"
    product = "(var_v1 * updateRate) >> 4"
    if position == "masked_add":
        masked = f"({masked} + ({zero_sum}))"
    elif position == "masked_sub":
        masked = f"({masked} - ({zero_sum}))"
    elif position == "high":
        high = f"(0x8000 + ({zero_sum}))"
    elif position == "low":
        low = f"(-0x8000 + ({zero_sum}))"
    elif position == "final_add":
        product = f"({product} + ({zero_sum}))"
    elif position == "final_sub":
        product = f"({product} - ({zero_sum}))"
    else:
        raise ValueError(position)
    return f"""\
        var_v1 = 0xD800 - {masked};
        if (var_v1 > {high}) {{
            var_v1 -= 0xFFFF;
        }}
        if (var_v1 < {low}) {{
            var_v1 += 0xFFFF;
        }}
        {ROT} += {product};
"""


def main() -> None:
    zeros = {
        "gt_mul": f"({ROT} > 0) * 0",
        "lt_mul": f"({ROT} < 0) * 0",
        "eq_mul": f"({ROT} == 0) * 0",
        "ne_mul": f"({ROT} != 0) * 0",
        "and_zero": f"{ROT} & 0",
        "xor_self": f"{ROT} ^ {ROT}",
        "sub_self": f"{ROT} - {ROT}",
        "comma": f"({ROT}, 0)",
        "ternary": f"({ROT} > 0) ? 0 : 0",
    }
    rows = []
    serial = 0
    for zero_name, zero in zeros.items():
        for position in (
            "masked_add",
            "masked_sub",
            "high",
            "low",
            "final_add",
            "final_sub",
        ):
            for repetitions in (1, 2, 3, 4, 6, 8):
                tag = f"{serial:03d}_{zero_name}_{position}_n{repetitions}"
                serial += 1
                if BASE.count(OLD) != 1:
                    raise ValueError("spinout block not unique")
                source = BASE.replace(
                    OLD, body(zero, position, repetitions), 1
                )
                path = pathlib.Path(f"/tmp/codex_spin_priority_{tag}.c")
                obj = path.with_suffix(".o")
                trace = path.with_suffix(".trace")
                path.write_text(source, encoding="utf-8")
                proc = subprocess.run(
                    [FORCED_RUNNER, str(path), str(obj), str(trace)],
                    check=False,
                    capture_output=True,
                    text=True,
                )
                if proc.returncode != 0:
                    rows.append((9999, 9999, tag, "compile", path))
                    continue
                _, candidate = ORACLE["dump_object"](str(obj))
                reg_bad = [
                    index
                    for index, (expected, actual) in enumerate(
                        zip(TARGET, candidate)
                    )
                    if registers(expected[1]) != registers(actual[1])
                ]
                spin_bad = [
                    index for index in reg_bad if 1160 <= index <= 1210
                ]
                total = len(reg_bad) + abs(len(TARGET) - len(candidate))
                rows.append(
                    (
                        total,
                        len(spin_bad),
                        tag,
                        f"insns={len(candidate)} spin={spin_bad}",
                        path,
                    )
                )
    for total, spin_count, tag, detail, path in sorted(rows):
        print(tag, "reg_bad", total, "spin_bad", spin_count, detail, path)


if __name__ == "__main__":
    main()
