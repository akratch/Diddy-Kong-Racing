#!/usr/bin/env python3
"""Apply recovered source-order corrections to the latest public scratch."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
CONTEXT = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()
PREFIX = CONTEXT[: CONTEXT.index("void func_80049794")]
FUNCTION = open("/tmp/codex_decomp_oR9oG.c", encoding="utf-8").read()

CORRECTIONS = {
    "stick": (
        "    gCurrentStickY = (1.0 - var_f20) * ((f32) gCurrentStickY);\n",
        "    gCurrentStickY = ((f32) gCurrentStickY) * (1.0 - var_f20);\n",
    ),
    "velocity_y": (
        "    obj->y_velocity = racer->oy1 * racer->velocity;\n",
        "    obj->y_velocity = racer->velocity * racer->oy1;\n",
    ),
    "top_speed": (
        "  var_f14 = (var_f14 * handle_racer_top_speed(obj, racer)) * 1.8;\n",
        "  var_f0 = handle_racer_top_speed(obj, racer);\n"
        "  var_f14 = var_f14 * var_f0;\n"
        "  var_f14 *= 1.8;\n",
    ),
    "throttle": (
        """\
    var_f0 = racerThrottle * var_f14;
    obj->x_velocity -= racer->ox1 * var_f0;
    obj->y_velocity -= racer->oy1 * var_f0;
    obj->z_velocity -= racer->oz1 * var_f0;
""",
        """\
    racerThrottle = racerThrottle * var_f14;
    obj->x_velocity -= racer->ox1 * racerThrottle;
    obj->y_velocity -= racer->oy1 * racerThrottle;
    obj->z_velocity -= racer->oz1 * racerThrottle;
""",
    ),
    "unk34": (
        "    var_f20 += 4.0f * (racer->unk34 * spD0);\n",
        "    var_f20 += (racer->unk34 * spD0) * 4.0f;\n",
    ),
}


def main() -> None:
    rows = []
    names = tuple(CORRECTIONS)
    for count in range(len(names) + 1):
        for selected in itertools.combinations(names, count):
            function = FUNCTION
            for name in selected:
                old, new = CORRECTIONS[name]
                if function.count(old) != 1:
                    raise ValueError(f"correction site missing: {name}")
                function = function.replace(old, new, 1)
            source = PREFIX + function
            tag = "none" if not selected else "_".join(selected)
            result = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_latest_corrections_{tag}.o"
            )
            with open(
                f"/tmp/codex_latest_corrections_{tag}.c", "w", encoding="utf-8"
            ) as output:
                output.write(source)
            rows.append(
                (
                    result.get("f20_operands", 0) == 0,
                    abs(result.get("insns", 9999) - 2625),
                    result.get("norm", 9999),
                    tag,
                    result,
                )
            )
    for _, _, _, tag, result in sorted(rows):
        print(tag, ORACLE["concise"](result))


if __name__ == "__main__":
    main()
