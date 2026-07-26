#!/usr/bin/env python3
"""Combine the natural f20 trigger with the best exact-length GPR topology."""

from __future__ import annotations

import pathlib
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
TARGET = ORACLE["TARGET_INSNS"]
BASE = pathlib.Path("/tmp/codex_gpr_topology_048.c").read_text(encoding="utf-8")
OLD_SQRT = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
NEW_SQRT = """\
    var_f20 = (obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
              (obj->y_velocity * obj->y_velocity);
    var_f20 = sqrtf(var_f20) - 2.0;
"""
OLD_SPIN = """\
        xRotationOffset = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (xRotationOffset > 0x8000) {
            xRotationOffset -= 0xFFFF;
        }
        if (xRotationOffset < -0x8000) {
            xRotationOffset += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (xRotationOffset * updateRate) >> 4;
"""
NEW_SPIN = """\
        var_v1 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v1 * updateRate) >> 4;
"""


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def main() -> None:
    if BASE.count(OLD_SQRT) != 1 or BASE.count(OLD_SPIN) != 1:
        raise ValueError("canonical replacement anchor is not unique")
    source = BASE.replace(OLD_SQRT, NEW_SQRT, 1).replace(
        OLD_SPIN, NEW_SPIN, 1
    )
    path = pathlib.Path("/tmp/codex_gpr_natural_combined.c")
    obj = path.with_suffix(".o")
    path.write_text(source, encoding="utf-8")
    result = ORACLE["evaluate"](source, keep=str(obj))
    _, candidate = ORACLE["dump_object"](str(obj))
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    word_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if expected[0] != actual[0]
    ]
    asm_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if expected[1] != actual[1]
    ]
    print(ORACLE["concise"](result), result.get("fp"))
    print("reg_bad", len(reg_bad), reg_bad)
    print("asm_bad", len(asm_bad), asm_bad)
    print("word_bad", len(word_bad), word_bad)
    print(path, obj)


if __name__ == "__main__":
    main()
