#!/usr/bin/env python3
"""Split the var_f14 interpolation at each expression boundary."""

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
    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
"""
A = "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1]"
B = "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx]"
V = "var_f0"

FORMS = {
    "direct_compound_a": """\
    var_f14 = {a} * {v};
    var_f14 += {b} * (1.0 - {v});
""",
    "direct_compound_b": """\
    var_f14 = {b} * (1.0 - {v});
    var_f14 += {a} * {v};
""",
    "temp_a": """\
    {t} = {a} * {v};
    var_f14 = {t} + ({b} * (1.0 - {v}));
""",
    "temp_a_reverse_add": """\
    {t} = {a} * {v};
    var_f14 = ({b} * (1.0 - {v})) + {t};
""",
    "temp_b": """\
    {t} = {b} * (1.0 - {v});
    var_f14 = ({a} * {v}) + {t};
""",
    "temp_b_reverse_add": """\
    {t} = {b} * (1.0 - {v});
    var_f14 = {t} + ({a} * {v});
""",
    "temp_factor": """\
    {t} = 1.0 - {v};
    var_f14 = ({a} * {v}) + ({b} * {t});
""",
    "temp_factor_reverse": """\
    {t} = 1.0 - {v};
    var_f14 = ({b} * {t}) + ({a} * {v});
""",
    "temp_a_compound": """\
    {t} = {a} * {v};
    {t} += {b} * (1.0 - {v});
    var_f14 = {t};
""",
    "temp_b_compound": """\
    {t} = {b} * (1.0 - {v});
    {t} += {a} * {v};
    var_f14 = {t};
""",
    "temp_load_a": """\
    {t} = {a};
    var_f14 = ({t} * {v}) + ({b} * (1.0 - {v}));
""",
    "temp_load_b": """\
    {t} = {b};
    var_f14 = ({a} * {v}) + ({t} * (1.0 - {v}));
""",
    "temp_sum_chain": """\
    {t} = ({a} * {v}) + ({b} * (1.0 - {v}));
    var_f14 = {t};
""",
}

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
        raise ValueError("interpolation missing")
    rows = []
    for form_tag, template in FORMS.items():
        hosts = ("spCC",) if "{t}" not in template else HOSTS
        for host in hosts:
            tag = f"{form_tag}_{host}"
            form = template.format(a=A, b=B, v=V, t=host)
            source = BASE.replace(OLD, form, 1)
            path = f"/tmp/codex_interpolation_split_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_interpolation_split_{tag}_natural.o"
            )
            forced = STICK["forced"](path, f"interpolation_split_{tag}")
            obj = f"/tmp/codex_stickform_interpolation_split_{tag}_forced.o"
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
