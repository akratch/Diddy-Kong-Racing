#!/usr/bin/env python3
"""Split late spEC computation ranges while retaining the f64 pressure chain."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()

APPROACH = """\
    if (racer->approachTarget == NULL) {
        var_f20 = obj->x_velocity;
        spEC = obj->z_velocity;
        if (racer->unk1D2 != 0) {
            var_f20 += racer->unk11C * 0.5;
            spEC += racer->unk120 * 0.5;
        }
        if (gRacerInputBlocked) {
            if (var_f20 > 0.5 || var_f20 < -0.5) {
                var_f20 *= 0.65;
            } else {
                var_f20 = 0.0f;
            }
            if (spEC > 0.5 || spEC < -0.5) {
                spEC *= 0.65;
            } else {
                spEC = 0.0f;
            }
        } else {
            var_f20 += racer->unk84;
            spEC += racer->unk88;
        }
        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectMoved = TRUE;
        }
    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
"""

LATE = """\
    if (racer->unk1D2 != 0) {
        racer->unk1D2 -= updateRate;
        if (racer->unk1D2 < 0) {
            racer->unk1D2 = 0;
        }
    } else {
        var_f0 = 1.0f / updateRateF;
        var_f20 = (obj->trans.x_position - spE8 - D_8011D548) * var_f0;
        obj->y_velocity = (obj->trans.y_position - spE4) * var_f0;
        spEC = (obj->trans.z_position - spE0 - D_8011D54C) * var_f0;
    }
"""


def make(*, split_approach: bool, split_late: bool, same: bool) -> str:
    source = BASE
    declarations = "    f32 zMove;\n"
    if not same:
        declarations += "    f32 zFinal;\n"
    source = source.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n" + declarations,
        1,
    )
    if split_approach:
        approach = APPROACH.replace("spEC", "zMove")
        approach = approach.replace(
            "        }\n    } else {\n        racer_approach_object",
            "        }\n        spEC = zMove;\n    } else {\n        racer_approach_object",
            1,
        )
        source = source.replace(APPROACH, approach, 1)
    if split_late:
        host = "zMove" if same else "zFinal"
        late = LATE.replace(
            "        spEC = (obj->trans.z_position",
            f"        {host} = (obj->trans.z_position",
            1,
        ).replace(
            "        obj->y_velocity = (obj->trans.y_position - spE4) * var_f0;\n"
            f"        {host} = (obj->trans.z_position - spE0 - D_8011D54C) * var_f0;\n"
            "    }\n",
            "        obj->y_velocity = (obj->trans.y_position - spE4) * var_f0;\n"
            f"        {host} = (obj->trans.z_position - spE0 - D_8011D54C) * var_f0;\n"
            f"        spEC = {host};\n"
            "    }\n",
            1,
        )
        source = source.replace(LATE, late, 1)
    return source


def main() -> None:
    for split_approach in (False, True):
        for split_late in (False, True):
            for same in (False, True):
                if not split_approach and not split_late:
                    continue
                tag = f"a{int(split_approach)}l{int(split_late)}s{int(same)}"
                source = make(
                    split_approach=split_approach,
                    split_late=split_late,
                    same=same,
                )
                result = ORACLE["evaluate"](
                    source, keep=f"/tmp/codex_spEClate_{tag}.o"
                )
                with open(f"/tmp/codex_spEClate_{tag}.c", "w", encoding="utf-8") as output:
                    output.write(source)
                print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
