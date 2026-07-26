#!/usr/bin/env python3
"""Recover the 0.4 throttle-clamp assignment's web identity."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_chain_y1_temp_f0_assign.c", encoding="utf-8"
).read()
TARGET = ORACLE["TARGET_INSNS"]
OLD = "            racerThrottle = 0.4f;\n"

FORMS = {
    "original": OLD,
    "double": "            racerThrottle = 0.4;\n",
    "cast": "            racerThrottle = (f32) 0.4;\n",
    "fraction": "            racerThrottle = 2.0f / 5.0f;\n",
    "self_assign": "            racerThrottle = (racerThrottle = 0.4f);\n",
    "temp_f0_expr": "            racerThrottle = (var_f0 = 0.4f);\n",
    "temp_f2_expr": "            racerThrottle = (var_f2 = 0.4f);\n",
    "temp_spcc_expr": "            racerThrottle = (spCC = 0.4f);\n",
    "temp_f0_lines": """\
            var_f0 = 0.4f;
            racerThrottle = var_f0;
""",
    "temp_f2_lines": """\
            var_f2 = 0.4f;
            racerThrottle = var_f2;
""",
    "temp_spcc_lines": """\
            spCC = 0.4f;
            racerThrottle = spCC;
""",
    "add_delta": "            racerThrottle += 0.4f - racerThrottle;\n",
}


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$(f\d+)\b", target) != re.findall(
            r"\$(f\d+)\b", actual
        ):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    rows = []
    for tag, form in FORMS.items():
        if BASE.count(OLD) != 1:
            raise ValueError("throttle assignment missing")
        source = BASE.replace(OLD, form, 1)
        path = f"/tmp/codex_throttle_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_throttle_{tag}_natural.o"
        )
        forced = STICK["forced"](path, f"throttle_{tag}")
        obj = f"/tmp/codex_stickform_throttle_{tag}_forced.o"
        prefix = fp_prefix(obj) if forced.get("ok") else -1
        rows.append((-prefix, forced.get("mismatch", 9999), tag, natural, forced))
    for neg_prefix, _, tag, natural, forced in sorted(rows):
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
