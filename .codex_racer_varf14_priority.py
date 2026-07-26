#!/usr/bin/env python3
"""Tune the restored interpolation copy's var_f14 live-range priority."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_segment_z_spcc.c", encoding="utf-8").read()
ANCHOR = "    var_f14 = spCC;\n"

PATTERNS = {
    "self_assign": "    var_f14 = var_f14;\n",
    "unary_plus": "    var_f14 = +var_f14;\n",
    "cast": "    var_f14 = (f32) var_f14;\n",
    "mul_one": "    var_f14 *= 1.0f;\n",
    "mul_int_one": "    var_f14 *= 1;\n",
    "add_zero": "    var_f14 += 0.0f;\n",
    "roundtrip": "    spCC = var_f14;\n    var_f14 = spCC;\n",
    "temp_self": "    spCC = spCC;\n",
    "void": "    (void) var_f14;\n",
    "ifzero": "    if (0) { var_f14 = 0.0f; }\n",
    "ternary": "    var_f14 = 1 ? var_f14 : spCC;\n",
    "comma": "    var_f14 = (var_f14, var_f14);\n",
}


def main() -> None:
    if BASE.count(ANCHOR) != 1:
        raise ValueError("interpolation copy missing")
    rows = []
    for pattern_tag, pattern in PATTERNS.items():
        for count in range(1, 25):
            tag = f"{pattern_tag}_{count}"
            source = BASE.replace(ANCHOR, ANCHOR + pattern * count, 1)
            path = f"/tmp/codex_varf14_priority_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_varf14_priority_{tag}_natural.o"
            )
            if (
                natural.get("f20_operands", 0) > 0
                or natural.get("insns") != 2640
                or count in (1, 2, 4, 8, 12, 16, 20, 24)
            ):
                forced = STICK["forced"](path, f"varf14_priority_{tag}")
                rows.append(
                    (
                        natural.get("f20_operands", 0) == 0,
                        abs(natural.get("insns", 9999) - 2625),
                        natural.get("norm", 9999),
                        tag,
                        natural,
                        forced,
                    )
                )
    for _, _, _, tag, natural, forced in sorted(rows):
        print(
            tag,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced,
        )


if __name__ == "__main__":
    main()
