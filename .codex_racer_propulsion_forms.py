#!/usr/bin/env python3
"""Recover the propulsion-factor source form after top-speed alignment."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_chain_y1_temp_f0_assign.c", encoding="utf-8"
).read()
OLD = "        var_f0 = racerThrottle * var_f14;\n"

FORMS = {
    "original": OLD,
    "reverse": "        var_f0 = var_f14 * racerThrottle;\n",
    "split_compound": """\
        var_f0 = racerThrottle;
        var_f0 *= var_f14;
""",
    "split_assign": """\
        var_f0 = racerThrottle;
        var_f0 = var_f0 * var_f14;
""",
    "split_reverse": """\
        var_f0 = racerThrottle;
        var_f0 = var_f14 * var_f0;
""",
    "assign_expr": """\
        var_f0 = (var_f0 = racerThrottle) * var_f14;
""",
    "comma": """\
        var_f0 = (var_f0 = racerThrottle, var_f0 * var_f14);
""",
}


def main() -> None:
    rows = []
    for tag, form in FORMS.items():
        if BASE.count(OLD) != 1:
            raise ValueError("propulsion expression missing")
        source = BASE.replace(OLD, form, 1)
        path = f"/tmp/codex_propulsion_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_propulsion_{tag}_natural.o"
        )
        forced = STICK["forced"](path, f"propulsion_{tag}")
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
