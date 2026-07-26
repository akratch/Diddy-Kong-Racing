#!/usr/bin/env python3
"""Recover the unk34 restoring-force expression topology."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_throttle_reuse_throttle_assign.c", encoding="utf-8"
).read()
TARGET = ORACLE["TARGET_INSNS"]
OLD = "        var_f20 += 4.0f * (racer->unk34 * spD0);\n"

FORMS = {
    "constant_first": OLD,
    "product_first": "        var_f20 += (racer->unk34 * spD0) * 4.0f;\n",
    "left_associative": "        var_f20 += racer->unk34 * spD0 * 4.0f;\n",
    "constant_left_assoc": "        var_f20 += 4.0f * racer->unk34 * spD0;\n",
    "sp_first": "        var_f20 += (spD0 * racer->unk34) * 4.0f;\n",
    "sp_constant_first": "        var_f20 += 4.0f * (spD0 * racer->unk34);\n",
    "nested_right": "        var_f20 += racer->unk34 * (spD0 * 4.0f);\n",
    "nested_constant": "        var_f20 += spD0 * (racer->unk34 * 4.0f);\n",
}


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
        raise ValueError("unk34 expression missing")
    rows = []
    for tag, form in FORMS.items():
        source = BASE.replace(OLD, form, 1)
        path = f"/tmp/codex_unk34_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_unk34_{tag}_natural.o"
        )
        forced = STICK["forced"](path, f"unk34_{tag}")
        obj = f"/tmp/codex_stickform_unk34_{tag}_forced.o"
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
