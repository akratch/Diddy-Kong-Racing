#!/usr/bin/env python3
"""Sweep commutative operand order through the first propulsion block."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_chain_y1_temp_f0_assign.c", encoding="utf-8"
).read()

PAIRS = (
    (
        "        var_f0 = racerThrottle * var_f14;\n",
        "        var_f0 = var_f14 * racerThrottle;\n",
    ),
    (
        "        obj->x_velocity -= racer->ox1 * var_f0;\n",
        "        obj->x_velocity -= var_f0 * racer->ox1;\n",
    ),
    (
        "        obj->y_velocity -= racer->oy1 * var_f0;\n",
        "        obj->y_velocity -= var_f0 * racer->oy1;\n",
    ),
    (
        "        obj->z_velocity -= racer->oz1 * var_f0;\n",
        "        obj->z_velocity -= var_f0 * racer->oz1;\n",
    ),
)


def main() -> None:
    rows = []
    for bits in itertools.product((0, 1), repeat=len(PAIRS)):
        tag = "".join(map(str, bits))
        source = BASE
        for bit, (original, reverse) in zip(bits, PAIRS):
            if source.count(original) != 1:
                raise ValueError(f"expression missing: {original!r}")
            source = source.replace(original, reverse if bit else original, 1)
        path = f"/tmp/codex_proporder_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_proporder_{tag}_natural.o"
        )
        forced = STICK["forced"](path, f"proporder_{tag}")
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
