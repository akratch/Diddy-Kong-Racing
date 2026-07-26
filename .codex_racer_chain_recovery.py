#!/usr/bin/env python3
"""Walk the first FP divergence forward on the structurally exact source."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_stickform_reverse.c", encoding="utf-8").read()

OLD_Y = "            obj->y_velocity = racer->oy1 * racer->velocity;\n"
NEW_Y = "            obj->y_velocity = racer->velocity * racer->oy1;\n"
OLD_TOP = "    var_f14 = (var_f14 * handle_racer_top_speed(obj, racer)) * 1.8;\n"

TOP_FORMS = {
    "original": OLD_TOP,
    "split_compound": """\
    var_f14 *= handle_racer_top_speed(obj, racer);
    var_f14 *= 1.8;
""",
    "split_assign_compound": """\
    var_f14 = var_f14 * handle_racer_top_speed(obj, racer);
    var_f14 *= 1.8;
""",
    "split_assign": """\
    var_f14 = var_f14 * handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * 1.8;
""",
    "compound_product": """\
    var_f14 *= handle_racer_top_speed(obj, racer) * 1.8;
""",
    "call_first": """\
    var_f14 = (handle_racer_top_speed(obj, racer) * var_f14) * 1.8;
""",
    "call_first_split": """\
    var_f14 = handle_racer_top_speed(obj, racer) * var_f14;
    var_f14 *= 1.8;
""",
    "temp_f0_assign": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
""",
    "temp_f0_compound": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 *= var_f0;
    var_f14 *= 1.8;
""",
    "temp_f0_expr": """\
    var_f14 = var_f14 * (var_f0 = handle_racer_top_speed(obj, racer));
    var_f14 *= 1.8;
""",
    "temp_f2_assign": """\
    var_f2 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f2;
    var_f14 *= 1.8;
""",
    "temp_f2_expr": """\
    var_f14 = var_f14 * (var_f2 = handle_racer_top_speed(obj, racer));
    var_f14 *= 1.8;
""",
    "temp_spcc_assign": """\
    spCC = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * spCC;
    var_f14 *= 1.8;
""",
    "temp_spcc_expr": """\
    var_f14 = var_f14 * (spCC = handle_racer_top_speed(obj, racer));
    var_f14 *= 1.8;
""",
    "temp_f0_combined": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = (var_f14 * var_f0) * 1.8;
""",
    "temp_f0_compound_product": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 *= var_f0 * 1.8;
""",
    "temp_f0_comma_split": """\
    var_f14 =
        (var_f0 = handle_racer_top_speed(obj, racer),
         var_f14 * var_f0);
    var_f14 *= 1.8;
""",
    "temp_f0_comma_compound": """\
    var_f14 =
        (var_f0 = handle_racer_top_speed(obj, racer),
         var_f14 *= var_f0);
    var_f14 *= 1.8;
""",
    "temp_f0_comma_all": """\
    var_f14 =
        (var_f0 = handle_racer_top_speed(obj, racer),
         (var_f14 * var_f0) * 1.8);
""",
    "temp_f0_reverse_combined": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = (var_f0 * var_f14) * 1.8;
""",
}


def main() -> None:
    rows = []
    for reverse_y in (False, True):
        for top_tag, top in TOP_FORMS.items():
            tag = f"y{int(reverse_y)}_{top_tag}"
            source = BASE
            if reverse_y:
                if source.count(OLD_Y) != 1:
                    raise ValueError("y expression missing")
                source = source.replace(OLD_Y, NEW_Y, 1)
            if source.count(OLD_TOP) != 1:
                raise ValueError("top-speed expression missing")
            source = source.replace(OLD_TOP, top, 1)
            path = f"/tmp/codex_chain_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_chain_{tag}_natural.o"
            )
            forced = STICK["forced"](path, f"chain_{tag}")
            rows.append((forced.get("mismatch", 9999), tag, natural, forced))
    for _, tag, natural, forced in sorted(rows):
        print(
            tag,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced,
        )


if __name__ == "__main__":
    main()
