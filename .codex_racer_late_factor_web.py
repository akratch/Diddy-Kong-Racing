#!/usr/bin/env python3
"""Split the late propulsion coefficient into its own source web."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_unk34_left_associative.c", encoding="utf-8"
).read()
TARGET = ORACLE["TARGET_INSNS"]
OLD = """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1;
            var_f14 = 2.0f;
            racer->boostTimer -= updateRate;
            obj->particleEmittersEnabled |= OBJ_EMIT_7 | OBJ_EMIT_8;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {
        if (racer->groundedWheels == 0 && racerThrottle < 0.4 && racer->vehicleID != VEHICLE_CARPET) {
            racerThrottle = 0.4f;
        }
        racerThrottle = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
        if (racer->groundedWheels >= 3 || racer->velocity < 1.0 || racer->vehicleID == VEHICLE_CARPET) {
            if (racer->groundedWheels == 0) {
                racerBrake /= 2;
            }
            racerBrake *= var_f14 / 2;
"""

FORMS = {
    "product": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    {t} = var_f14 * var_f0;
    {t} *= 1.8;
""",
    "copy_before": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    {t} = var_f14;
    {t} = {t} * var_f0;
    {t} *= 1.8;
""",
    "copy_before_compound": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    {t} = var_f14;
    {t} *= var_f0;
    {t} *= 1.8;
""",
    "after_product": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    {t} = var_f14;
    {t} *= 1.8;
""",
    "after_scale": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
    {t} = var_f14;
""",
}

TAIL = """\
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1;
            {t} = 2.0f;
            racer->boostTimer -= updateRate;
            obj->particleEmittersEnabled |= OBJ_EMIT_7 | OBJ_EMIT_8;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {
        if (racer->groundedWheels == 0 && racerThrottle < 0.4 && racer->vehicleID != VEHICLE_CARPET) {
            racerThrottle = 0.4f;
        }
        racerThrottle = racerThrottle * {t};
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
        if (racer->groundedWheels >= 3 || racer->velocity < 1.0 || racer->vehicleID == VEHICLE_CARPET) {
            if (racer->groundedWheels == 0) {
                racerBrake /= 2;
            }
            racerBrake *= {t} / 2;
"""

HOSTS = ("spCC", "var_f6", "segmentXVelocity")


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(
            r"\$f\d+\b", actual
        ):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    if BASE.count(OLD) != 1:
        raise ValueError("late coefficient block missing")
    rows = []
    for form_tag, head in FORMS.items():
        for host in HOSTS:
            tag = f"{form_tag}_{host}"
            replacement = head.replace("{t}", host) + TAIL.replace("{t}", host)
            source = BASE.replace(OLD, replacement, 1)
            path = f"/tmp/codex_late_factor_web_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_late_factor_web_{tag}_natural.o"
            )
            forced = STICK["forced"](path, f"late_factor_web_{tag}")
            obj = f"/tmp/codex_stickform_late_factor_web_{tag}_forced.o"
            prefix = fp_prefix(obj) if forced.get("ok") else -1
            rows.append(
                (
                    natural.get("f20_operands", 0) == 0,
                    abs(natural.get("insns", 9999) - 2625),
                    -prefix,
                    forced.get("mismatch", 9999),
                    tag,
                    natural,
                    forced,
                )
            )
    for _, _, neg_prefix, _, tag, natural, forced in sorted(rows):
        print(
            tag,
            "prefix",
            -neg_prefix,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced,
        )


if __name__ == "__main__":
    main()
