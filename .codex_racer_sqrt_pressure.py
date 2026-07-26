#!/usr/bin/env python3
"""Recover the three short FP ranges implied by target sqrt allocation."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
OLD = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
COMPONENTS = {
    "x": "obj->x_velocity",
    "z": "obj->z_velocity",
    "y": "obj->y_velocity",
}
HOST_SETS = (
    ("spCC", "var_f6", "segmentXVelocity"),
    ("spCC", "var_f0", "var_f6"),
    ("racerVelocity", "var_f6", "segmentXVelocity"),
    ("var_f2", "var_f6", "segmentXVelocity"),
)


def product_lines(mapping: dict[str, str], order: tuple[str, ...]) -> str:
    return "".join(
        f"    {mapping[axis]} = {COMPONENTS[axis]} * {COMPONENTS[axis]};\n"
        for axis in order
    )


def axis_lines(mapping: dict[str, str], order: tuple[str, ...]) -> str:
    return "".join(
        f"    {mapping[axis]} = {COMPONENTS[axis]};\n"
        for axis in order
    )


def sum_expr(mapping: dict[str, str]) -> str:
    return f"({mapping['x']} + {mapping['z']}) + {mapping['y']}"


def forms(
    mapping: dict[str, str],
    order: tuple[str, ...],
) -> dict[str, str]:
    products = product_lines(mapping, order)
    axes = axis_lines(mapping, order)
    x, z, y = (mapping[axis] for axis in ("x", "z", "y"))
    xv, zv, yv = (COMPONENTS[axis] for axis in ("x", "z", "y"))
    return {
        "products": products + f"    var_f20 = sqrtf({sum_expr(mapping)}) - 2.0;\n",
        "axes": axes
        + f"    var_f20 = sqrtf(({x} * {x}) + ({z} * {z}) + ({y} * {y})) - 2.0;\n",
        "embedded_products": (
            "    var_f20 = sqrtf("
            f"(({x} = {xv} * {xv}) + ({z} = {zv} * {zv})) + "
            f"({y} = {yv} * {yv})) - 2.0;\n"
        ),
        "comma_products": (
            "    var_f20 = sqrtf(("
            f"{x} = {xv} * {xv}, "
            f"{z} = {zv} * {zv}, "
            f"{y} = {yv} * {yv}, "
            f"({x} + {z}) + {y})) - 2.0;\n"
        ),
        "two_products": (
            f"    {x} = {xv} * {xv};\n"
            f"    {z} = {zv} * {zv};\n"
            f"    var_f20 = sqrtf(({x} + {z}) + ({yv} * {yv})) - 2.0;\n"
        ),
        "sum_in_y": (
            f"    {x} = {xv} * {xv};\n"
            f"    {z} = {zv} * {zv};\n"
            f"    {y} = {x} + {z};\n"
            f"    var_f20 = sqrtf({y} + ({yv} * {yv})) - 2.0;\n"
        ),
        "rolling_sum": (
            f"    {x} = {xv} * {xv};\n"
            f"    {x} += {zv} * {zv};\n"
            f"    {x} += {yv} * {yv};\n"
            f"    var_f20 = sqrtf({x}) - 2.0;\n"
        ),
    }


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    if BASE.count(OLD) != 1:
        raise ValueError("sqrt expression missing")
    rows = []
    for hosts in HOST_SETS:
        for mapping_order in itertools.permutations(hosts):
            mapping = dict(zip(("x", "z", "y"), mapping_order))
            for statement_order in itertools.permutations(("x", "z", "y")):
                for form_name, block in forms(mapping, statement_order).items():
                    if form_name not in ("products", "axes") and statement_order != (
                        "x",
                        "z",
                        "y",
                    ):
                        continue
                    tag = (
                        f"{form_name}_{'-'.join(mapping_order)}_"
                        f"{''.join(statement_order)}"
                    )
                    source = BASE.replace(OLD, block, 1)
                    path = f"/tmp/codex_sqrt_pressure_{tag}.c"
                    with open(path, "w", encoding="utf-8") as output:
                        output.write(source)
                    result = ORACLE["evaluate"](
                        source, keep=f"/tmp/codex_sqrt_pressure_{tag}.o"
                    )
                    prefix = (
                        fp_prefix(f"/tmp/codex_sqrt_pressure_{tag}.o")
                        if result.get("ok")
                        else -1
                    )
                    rows.append((tag, result, prefix))
    for tag, result, prefix in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[2],
            abs(row[1].get("insns", 9999) - len(TARGET)),
            row[1].get("norm", 9999),
            row[0],
        ),
    ):
        if (
            result.get("f20_operands", 0) > 0
            or prefix > 580
            or result.get("norm", 9999) < 800
        ):
            print(
                tag,
                "prefix",
                prefix,
                ORACLE["concise"](result),
                result.get("fp"),
            )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(result.get("f20_operands", 0) > 0 for _, result, _ in rows),
    )


if __name__ == "__main__":
    main()
