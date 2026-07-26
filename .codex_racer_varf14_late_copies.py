#!/usr/bin/env python3
"""Raise var_f14 priority with late temporary-to-var_f14 copies."""

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
"""

FORMS = {
    "product_copy": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    {t} = var_f14 * var_f0;
    var_f14 = {t};
    var_f14 *= 1.8;
""",
    "scale_copy": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    {t} = var_f14 * 1.8;
    var_f14 = {t};
""",
    "full_copy": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    {t} = (var_f14 * var_f0) * 1.8;
    var_f14 = {t};
""",
    "full_split_copy": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    {t} = var_f14 * var_f0;
    {t} *= 1.8;
    var_f14 = {t};
""",
    "call_copy": """\
    {t} = handle_racer_top_speed(obj, racer);
    var_f0 = {t};
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
""",
    "call_direct_copy": """\
    {t} = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * {t};
    var_f14 *= 1.8;
""",
    "roundtrip_before": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    {t} = var_f14;
    var_f14 = {t};
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
""",
    "roundtrip_after": """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
    {t} = var_f14;
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
        raise ValueError("top-speed block missing")
    rows = []
    for form_tag, template in FORMS.items():
        for host in HOSTS:
            tag = f"{form_tag}_{host}"
            source = BASE.replace(OLD, template.replace("{t}", host), 1)
            path = f"/tmp/codex_varf14_late_copies_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_varf14_late_copies_{tag}_natural.o"
            )
            forced = STICK["forced"](path, f"varf14_late_copies_{tag}")
            obj = f"/tmp/codex_stickform_varf14_late_copies_{tag}_forced.o"
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
