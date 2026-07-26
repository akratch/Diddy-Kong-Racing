#!/usr/bin/env python3
"""Restore and place the historical segmentZVelocity interpolation temporary."""

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
NEW = """\
    segmentZVelocity = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
                       (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
    var_f14 = segmentZVelocity;
"""

ANCHORS = {
    "after_var_f14": "    f32 var_f14;\n",
    "before_pad2": "    s32 pad2;\n",
    "after_racer_misc": "    s32 racerMiscAssetIdx;\n",
    "after_var_f0": "    f32 var_f0;\n",
    "before_sp60": "    f32 sp60[4]; // Should be MtxF, but produces a worse score.\n",
    "before_boost": "    Object_Boost *boostObj;\n",
}

HOSTS = {
    "segment": ("segmentZVelocity", "    f32 segmentZVelocity;\n"),
    "spec": ("spEC", ""),
    "spcc": ("spCC", ""),
    "racer_velocity": ("racerVelocity", ""),
    "var_f6": ("var_f6", ""),
    "segment_x": ("segmentXVelocity", ""),
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
        raise ValueError("interpolation expression missing")
    rows = []
    entries = []
    for host, (name, declaration) in HOSTS.items():
        if declaration:
            for anchor_tag, anchor in ANCHORS.items():
                entries.append((f"{host}_{anchor_tag}", name, declaration, anchor))
        else:
            entries.append((host, name, "", ""))

    for tag, name, declaration, anchor in entries:
        source = BASE.replace(
            OLD,
            NEW.replace("segmentZVelocity", name),
            1,
        )
        if declaration:
            if source.count(anchor) != 1:
                raise ValueError(f"declaration anchor missing: {anchor!r}")
            if tag.endswith("before_pad2") or tag.endswith("before_sp60") or tag.endswith("before_boost"):
                source = source.replace(anchor, declaration + anchor, 1)
            else:
                source = source.replace(anchor, anchor + declaration, 1)
        path = f"/tmp/codex_segment_z_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_segment_z_{tag}_natural.o"
        )
        forced = STICK["forced"](path, f"segment_z_{tag}")
        obj = f"/tmp/codex_stickform_segment_z_{tag}_forced.o"
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
