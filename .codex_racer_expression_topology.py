#!/usr/bin/env python3
"""Test assignment-expression topology for zero-opcode allocation pressure."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()
OLD_FORWARD = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""
OLD_DRAG = """\
        obj->x_velocity -= racer->ox2 * var_f20;
        obj->y_velocity -= racer->oy2 * var_f20;
        obj->z_velocity -= racer->oz2 * var_f20;
"""

F64_FORMS = {
    "comma": """\
        racer->forwardVel =
            (d0 = racer->velocity * 0.05,
             d1 = racer->forwardVel + d0,
             d2 = d1 * 0.125,
             d3 = racer->forwardVel - d2);
""",
    "nested": """\
        racer->forwardVel =
            (d3 = racer->forwardVel -
                  (d2 = (d1 = racer->forwardVel +
                               (d0 = racer->velocity * 0.05)) * 0.125));
""",
    "nested_no_d3": """\
        racer->forwardVel =
            racer->forwardVel -
            (d2 = (d1 = racer->forwardVel +
                         (d0 = racer->velocity * 0.05)) * 0.125);
""",
    "comma_no_d3": """\
        racer->forwardVel =
            (d0 = racer->velocity * 0.05,
             d1 = racer->forwardVel + d0,
             d2 = d1 * 0.125,
             racer->forwardVel - d2);
""",
    "pairs": """\
        d1 = (d0 = racer->velocity * 0.05) + racer->forwardVel;
        d3 = racer->forwardVel - (d2 = d1 * 0.125);
        racer->forwardVel = d3;
""",
}

F32_FORMS = {
    "axes_comma": """\
        obj->x_velocity -=
            (spCC = racer->ox2,
             var_f6 = racer->oy2,
             segmentXVelocity = racer->oz2,
             spCC) * var_f20;
        obj->y_velocity -= var_f6 * var_f20;
        obj->z_velocity -= segmentXVelocity * var_f20;
""",
    "products_comma": """\
        obj->x_velocity -=
            (spCC = racer->ox2 * var_f20,
             var_f6 = racer->oy2 * var_f20,
             segmentXVelocity = racer->oz2 * var_f20,
             spCC);
        obj->y_velocity -= var_f6;
        obj->z_velocity -= segmentXVelocity;
""",
    "results_comma": """\
        obj->x_velocity =
            (spCC = obj->x_velocity - (racer->ox2 * var_f20),
             var_f6 = obj->y_velocity - (racer->oy2 * var_f20),
             segmentXVelocity =
                 obj->z_velocity - (racer->oz2 * var_f20),
             spCC);
        obj->y_velocity = var_f6;
        obj->z_velocity = segmentXVelocity;
""",
    "embedded_axes": """\
        obj->x_velocity -= (spCC = racer->ox2) * var_f20;
        obj->y_velocity -= (var_f6 = racer->oy2) * var_f20;
        obj->z_velocity -=
            (segmentXVelocity = racer->oz2) * var_f20;
""",
    "embedded_products": """\
        obj->x_velocity -= (spCC = racer->ox2 * var_f20);
        obj->y_velocity -= (var_f6 = racer->oy2 * var_f20);
        obj->z_velocity -=
            (segmentXVelocity = racer->oz2 * var_f20);
""",
}


def add_f64_declarations(source: str) -> str:
    return source.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n"
        "    f64 d0;\n"
        "    f64 d1;\n"
        "    f64 d2;\n"
        "    f64 d3;\n",
        1,
    )


def main() -> None:
    for tag, block in F64_FORMS.items():
        source = add_f64_declarations(BASE).replace(OLD_FORWARD, block, 1)
        result = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_expr_f64_{tag}.o"
        )
        with open(f"/tmp/codex_expr_f64_{tag}.c", "w", encoding="utf-8") as output:
            output.write(source)
        print("F64", tag, ORACLE["concise"](result), result.get("fp"))

    for tag, block in F32_FORMS.items():
        source = BASE.replace(OLD_DRAG, block, 1)
        result = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_expr_f32_{tag}.o"
        )
        with open(f"/tmp/codex_expr_f32_{tag}.c", "w", encoding="utf-8") as output:
            output.write(source)
        print("F32", tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
