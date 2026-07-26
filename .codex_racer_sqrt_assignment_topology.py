#!/usr/bin/env python3
"""Test whether statement boundaries join sqrtf's result to the factor web."""

from __future__ import annotations

import pathlib
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
OLD = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
CALL = """sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity))"""


def forms() -> dict[str, str]:
    result: dict[str, str] = {
        "split_compound": f"    var_f20 = {CALL};\n    var_f20 -= 2.0;\n",
        "split_assign": (
            f"    var_f20 = {CALL};\n"
            "    var_f20 = var_f20 - 2.0;\n"
        ),
        "split_sub_rev": (
            f"    var_f20 = {CALL};\n"
            "    var_f20 = -(2.0 - var_f20);\n"
        ),
        "seed_sub": (
            "    var_f20 = 2.0;\n"
            f"    var_f20 = {CALL} - var_f20;\n"
        ),
        "seed_neg_add": (
            "    var_f20 = -2.0;\n"
            f"    var_f20 += {CALL};\n"
        ),
        "seed_neg_assign": (
            "    var_f20 = -2.0;\n"
            f"    var_f20 = var_f20 + {CALL};\n"
        ),
        "comma_split": (
            f"    var_f20 = ({CALL}, 0.0f);\n"
            f"    var_f20 = {CALL} - 2.0;\n"
        ),
    }
    for host in (
        "spEC",
        "spE8",
        "spE4",
        "spE0",
        "var_f14",
        "spD8",
        "spD4",
        "spD0",
        "var_f0",
        "var_f2",
        "spCC",
        "var_f6",
        "segmentXVelocity",
        "racerVelocity",
    ):
        result[f"host_{host}_expression"] = (
            f"    {host} = {CALL};\n"
            f"    var_f20 = {host} - 2.0;\n"
        )
        result[f"host_{host}_compound"] = (
            f"    {host} = {CALL};\n"
            f"    {host} -= 2.0;\n"
            f"    var_f20 = {host};\n"
        )
    return result


def main() -> None:
    rows = []
    for serial, (name, replacement) in enumerate(forms().items()):
        if BASE.count(OLD) != 1:
            raise ValueError("sqrt block not unique")
        source = BASE.replace(OLD, replacement, 1)
        path = pathlib.Path(f"/tmp/codex_sqrt_assignment_{serial:03d}_{name}.c")
        path.write_text(source, encoding="utf-8")
        result = ORACLE["evaluate"](source, keep=str(path.with_suffix(".o")))
        rows.append((not bool(result.get("f20_operands", 0)), int(result.get("norm", 9999)), name, result, path))
    for _, _, name, result, path in sorted(rows):
        print(name, ORACLE["concise"](result), result.get("fp"), path)


if __name__ == "__main__":
    main()
