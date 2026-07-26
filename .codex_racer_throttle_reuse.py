#!/usr/bin/env python3
"""Test whether the propulsion product naturally reuses racerThrottle's web."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_chain_y1_temp_f0_assign.c", encoding="utf-8"
).read()
OLD = """\
        var_f0 = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * var_f0;
        obj->y_velocity -= racer->oy1 * var_f0;
        obj->z_velocity -= racer->oz1 * var_f0;
"""

FORMS = {
    "baseline": OLD,
    "throttle_compound": """\
        racerThrottle *= var_f14;
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
""",
    "throttle_assign": """\
        racerThrottle = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
""",
    "throttle_reverse": """\
        racerThrottle = var_f14 * racerThrottle;
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
""",
    "f2_product": """\
        var_f2 = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * var_f2;
        obj->y_velocity -= racer->oy1 * var_f2;
        obj->z_velocity -= racer->oz1 * var_f2;
""",
    "f14_product": """\
        var_f14 *= racerThrottle;
        obj->x_velocity -= racer->ox1 * var_f14;
        obj->y_velocity -= racer->oy1 * var_f14;
        obj->z_velocity -= racer->oz1 * var_f14;
""",
}


def main() -> None:
    if BASE.count(OLD) != 1:
        raise ValueError("propulsion block missing")
    rows = []
    for tag, form in FORMS.items():
        source = BASE.replace(OLD, form, 1)
        path = f"/tmp/codex_throttle_reuse_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_throttle_reuse_{tag}_natural.o"
        )
        forced = STICK["forced"](path, f"throttle_reuse_{tag}")
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
