#!/usr/bin/env python3
"""Use explicit double intermediates to compress post-sqrt FP pressure."""

from __future__ import annotations

import itertools
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
    if (racer->vehicleID >= VEHICLE_BOSSES) {
"""
CALL = """sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                         (obj->y_velocity * obj->y_velocity))"""
FIELDS = (
    "obj->x_velocity",
    "obj->z_velocity",
    "obj->y_velocity",
    "obj->trans.x_position",
)


def clean_forms() -> dict[str, str]:
    return {
        "result_assign": (
            "    {\n"
            "        f64 pressD;\n"
            f"        pressD = {CALL};\n"
            "        var_f20 = pressD - 2.0;\n"
            "    }\n"
        ),
        "result_init": (
            "    {\n"
            f"        f64 pressD = {CALL};\n"
            "        var_f20 = pressD - 2.0;\n"
            "    }\n"
        ),
        "adjusted_assign": (
            "    {\n"
            "        f64 pressD;\n"
            f"        pressD = {CALL} - 2.0;\n"
            "        var_f20 = pressD;\n"
            "    }\n"
        ),
        "split_compound": (
            "    {\n"
            "        f64 pressD;\n"
            f"        pressD = {CALL};\n"
            "        pressD -= 2.0;\n"
            "        var_f20 = pressD;\n"
            "    }\n"
        ),
        "two_stage": (
            "    {\n"
            "        f64 pressD0;\n"
            "        f64 pressD1;\n"
            f"        pressD0 = {CALL};\n"
            "        pressD1 = pressD0 - 2.0;\n"
            "        var_f20 = pressD1;\n"
            "    }\n"
        ),
        "cast_expression": (
            f"    var_f20 = (f64) {CALL} - 2.0;\n"
        ),
    }


def pressure_form(double_count: int, float_count: int, placement: str) -> str:
    declarations = "".join(
        f"        f64 pressD{i};\n" for i in range(double_count)
    ) + "".join(f"        f32 pressF{i};\n" for i in range(float_count))
    values: list[str] = []
    assignments = ""
    field_index = 0
    for i in range(double_count):
        values.append(f"pressD{i}")
        assignments += f"        pressD{i} = {FIELDS[field_index % len(FIELDS)]};\n"
        field_index += 1
    for i in range(float_count):
        values.append(f"pressF{i}")
        assignments += f"        pressF{i} = {FIELDS[field_index % len(FIELDS)]};\n"
        field_index += 1
    comparisons = " + ".join(f"({value} > 0.0)" for value in values)
    sqrt = (
        f"        var_f20 = {CALL} - 2.0;\n"
    )
    fake = f"        var_f20 += (f32) (({comparisons}) * 0);\n"
    if placement == "before":
        body = assignments + sqrt + fake
    else:
        body = sqrt + assignments + fake
    return "    {\n" + declarations + body + "    }\n"


def main() -> None:
    forms = clean_forms()
    for double_count, float_count, placement in itertools.product(
        range(1, 5), range(0, 5), ("before", "after")
    ):
        forms[f"pressure_d{double_count}_f{float_count}_{placement}"] = pressure_form(
            double_count, float_count, placement
        )

    rows = []
    for serial, (name, body) in enumerate(forms.items()):
        replacement = body + "    if (racer->vehicleID >= VEHICLE_BOSSES) {\n"
        if BASE.count(OLD) != 1:
            raise ValueError("sqrt block not unique")
        source = BASE.replace(OLD, replacement, 1)
        path = pathlib.Path(f"/tmp/codex_sqrt_f64_{serial:03d}_{name}.c")
        path.write_text(source, encoding="utf-8")
        result = ORACLE["evaluate"](source, keep=str(path.with_suffix(".o")))
        rows.append(
            (
                not bool(result.get("f20_operands", 0)),
                int(result.get("norm", 9999)),
                abs(int(result.get("insns", 9999)) - 2625),
                name,
                result,
                path,
            )
        )
    for _, _, _, name, result, path in sorted(rows):
        print(name, ORACLE["concise"](result), result.get("fp"), path)


if __name__ == "__main__":
    main()
