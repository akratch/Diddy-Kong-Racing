#!/usr/bin/env python3
"""Combine direct interpolation interference with a retained copy web."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_unk34_left_associative.c", encoding="utf-8"
).read()
TARGET = ORACLE["TARGET_INSNS"]
DIRECT = """\
    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
"""
EXPR = """\
(gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0))
"""

FORMS = {
    "direct_roundtrip": """\
    var_f14 = {expr};
    spCC = var_f14;
    var_f14 = spCC;
""",
    "chain_copy": """\
    spCC = var_f14 = {expr};
    var_f14 = spCC;
""",
    "nested_copy": """\
    spCC = (var_f14 = {expr});
    var_f14 = spCC;
""",
    "direct_nested_roundtrip": """\
    var_f14 = {expr};
    var_f14 = (spCC = var_f14);
""",
    "double_chain": """\
    spCC = var_f14 = {expr};
    spCC = var_f14 = spCC;
""",
    "comma_chain": """\
    var_f14 = (spCC = (var_f14 = {expr}), spCC);
""",
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
    if BASE.count(DIRECT) != 1:
        raise ValueError("direct interpolation missing")
    rows = []
    for form_tag, form in FORMS.items():
        for count in range(1, 17):
            source_form = form.format(expr=EXPR)
            if count > 1:
                source_form += (
                    "    spCC = var_f14;\n"
                    "    var_f14 = spCC;\n"
                ) * (count - 1)
            tag = f"{form_tag}_{count}"
            source = BASE.replace(DIRECT, source_form, 1)
            path = f"/tmp/codex_varf14_chain_copy_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_varf14_chain_copy_{tag}_natural.o"
            )
            forced = STICK["forced"](path, f"varf14_chain_copy_{tag}")
            obj = f"/tmp/codex_stickform_varf14_chain_copy_{tag}_forced.o"
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
