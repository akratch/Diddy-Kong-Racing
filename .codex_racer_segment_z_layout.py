#!/usr/bin/env python3
"""Test whether the exact early f32 slot belongs to segmentZVelocity, not var_f14."""

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
EXPRESSION = """\
(gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
                       (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0))
"""

FORMS = {
    "two_lines": """\
    segmentZVelocity = {expression};
    var_f14 = segmentZVelocity;
""",
    "chain": """\
    var_f14 = segmentZVelocity = {expression};
""",
    "chain_reverse": """\
    segmentZVelocity = var_f14 = {expression};
""",
    "nested": """\
    var_f14 = (segmentZVelocity = {expression});
""",
    "comma": """\
    var_f14 = (segmentZVelocity = {expression}, segmentZVelocity);
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


def declaration_layout(source: str, late_anchor: str) -> str:
    source = source.replace(
        "    f32 var_f14;\n",
        "    f32 segmentZVelocity;\n",
        1,
    )
    if source.count(late_anchor) != 1:
        raise ValueError(f"late anchor missing: {late_anchor!r}")
    return source.replace(late_anchor, late_anchor + "    f32 var_f14;\n", 1)


def main() -> None:
    if BASE.count(DIRECT) != 1:
        raise ValueError("direct interpolation missing")
    anchors = {
        "after_player": "    s8 playerObjectMoved;\n",
        "after_boost": "    Object_Boost *boostObj;\n",
        "after_sp60": "    f32 sp60[4]; // Should be MtxF, but produces a worse score.\n",
        "after_segment_x": "    f32 segmentXVelocity;\n",
    }
    rows = []
    for anchor_tag, anchor in anchors.items():
        laid_out = declaration_layout(BASE, anchor)
        for form_tag, form in FORMS.items():
            source = laid_out.replace(
                DIRECT,
                form.format(expression=EXPRESSION),
                1,
            )
            for ifzero in (False, True):
                variant = source
                suffix = ""
                if ifzero:
                    old = """\
    if (var_f14 < 0) {
        var_f14 = -var_f14;
    }
"""
                    new = """\
    if (var_f14 < 0) {
        var_f14 = -var_f14;
        if (0) {}
    }
"""
                    if variant.count(old) != 1:
                        raise ValueError("absolute-value branch missing")
                    variant = variant.replace(old, new, 1)
                    suffix = "_ifzero"
                tag = f"{anchor_tag}_{form_tag}{suffix}"
                path = f"/tmp/codex_segment_z_layout_{tag}.c"
                with open(path, "w", encoding="utf-8") as output:
                    output.write(variant)
                natural = ORACLE["evaluate"](
                    variant,
                    keep=f"/tmp/codex_segment_z_layout_{tag}_natural.o",
                )
                forced = STICK["forced"](path, f"segment_z_layout_{tag}")
                obj = f"/tmp/codex_stickform_segment_z_layout_{tag}_forced.o"
                prefix = fp_prefix(obj) if forced.get("ok") else -1
                rows.append(
                    (-prefix, forced.get("mismatch", 9999), tag, natural, forced)
                )
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
