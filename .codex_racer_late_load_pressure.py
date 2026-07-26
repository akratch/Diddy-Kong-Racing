#!/usr/bin/env python3
"""Create optimizer-erased, co-live direct-load webs across the factor range."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
ANCHORS = (
    "    gCurrentRacerTransform.rotation.z_rotation = 0;\n",
    "    gCurrentRacerTransform.x_position = 0.0f;\n",
)
GROUPS = {
    "objvel": ("obj->x_velocity", "obj->y_velocity", "obj->z_velocity"),
    "objpos": (
        "obj->trans.x_position",
        "obj->trans.y_position",
        "obj->trans.z_position",
    ),
    "basis1": ("racer->ox1", "racer->oy1", "racer->oz1"),
    "basis2": ("racer->ox2", "racer->oy2", "racer->oz2"),
    "basis3": ("racer->ox3", "racer->oy3", "racer->oz3"),
    "motion": (
        "racer->velocity",
        "racer->lateral_velocity",
        "racer->forwardVel",
    ),
    "rot": (
        "(f32) racer->x_rotation_vel",
        "(f32) racer->y_rotation_vel",
        "(f32) racer->z_rotation_vel",
    ),
}
HOSTS = ("spCC", "var_f6", "segmentXVelocity")


def forms(values: tuple[str, str, str]) -> dict[str, str]:
    a, b, c = values
    h0, h1, h2 = HOSTS
    return {
        "sum_l": f"((({a} + {b}) + {c}) > 0.0f) * 0",
        "sum_r": f"(({a} + ({b} + {c})) > 0.0f) * 0",
        "mul_l": f"((({a} * {b}) * {c}) > 0.0f) * 0",
        "mul_r": f"(({a} * ({b} * {c})) > 0.0f) * 0",
        "squares_l": (
            f"((({a} * {a}) + ({b} * {b}) + ({c} * {c})) > 0.0f) * 0"
        ),
        "squares_r": (
            f"((({a} * {a}) + (({b} * {b}) + ({c} * {c}))) > 0.0f) * 0"
        ),
        "assign_sum": (
            f"({h0} = {a}, {h1} = {b}, {h2} = {c}, "
            f"(({h0} + {h1}) + {h2}) > 0.0f) * 0"
        ),
        "assign_products": (
            f"({h0} = {a} * {a}, {h1} = {b} * {b}, {h2} = {c} * {c}, "
            f"(({h0} + {h1}) + {h2}) > 0.0f) * 0"
        ),
        "embedded_products": (
            f"((({h0} = {a} * {a}) + ({h1} = {b} * {b}) + "
            f"({h2} = {c} * {c})) > 0.0f) * 0"
        ),
    }


def make(anchor: str, expression: str) -> str:
    lhs = anchor.split("=", 1)[0]
    replacement = f"{lhs}= {expression};\n"
    if BASE.count(anchor) < 1:
        raise ValueError(anchor)
    before, after = BASE.rsplit(anchor, 1)
    return before + replacement + after


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    rows = []
    for anchor in ANCHORS:
        anchor_tag = "rot" if "rotation" in anchor else "pos"
        for group_name, group in GROUPS.items():
            for order in itertools.permutations(group):
                for form_name, expression in forms(order).items():
                    tag = f"{anchor_tag}_{group_name}_{form_name}_{group.index(order[0])}{group.index(order[1])}{group.index(order[2])}"
                    source = make(anchor, expression)
                    path = f"/tmp/codex_late_load_pressure_{tag}.c"
                    with open(path, "w", encoding="utf-8") as output:
                        output.write(source)
                    natural = ORACLE["evaluate"](
                        source, keep=f"/tmp/codex_late_load_pressure_{tag}.o"
                    )
                    prefix = fp_prefix(
                        f"/tmp/codex_late_load_pressure_{tag}.o"
                    ) if natural.get("ok") else -1
                    rows.append((tag, natural, prefix))

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
        if result.get("f20_operands", 0) > 0 or prefix > 580:
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
