#!/usr/bin/env python3
"""Extend the factor web across existing tail calls with erased comparisons."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
ANCHORS = {
    "boost": (
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {\n",
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == {zero} && gNumViewports < 2) {\n",
    ),
    "player": (
        "    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {\n",
        "    if (gCurrentPlayerIndex == PLAYER_COMPUTER + {zero}) {\n",
    ),
    "unk201": (
        "    if (racer->unk201 == 0) {\n",
        "    if (racer->unk201 == {zero}) {\n",
    ),
    "vehicle": (
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES) {\n",
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES + {zero}) {\n",
    ),
    "spa1": (
        "    if (spA1 != FALSE) {\n",
        "    if (spA1 != FALSE + {zero}) {\n",
    ),
    "moved": (
        "    if (playerObjectMoved != FALSE) {\n",
        "    if (playerObjectMoved != FALSE + {zero}) {\n",
    ),
}
ZERO_FORMS = {
    "gt_mul": "(var_f20 > 0.0f) * 0",
    "lt_mul": "(var_f20 < 0.0f) * 0",
    "eq_mul": "(var_f20 == 0.0f) * 0",
    "ne_mul": "(var_f20 != 0.0f) * 0",
    "gt_and": "(var_f20 > 0.0f) & 0",
    "gt_shift": "(var_f20 > 0.0f) >> 1",
    "gt_mod": "(var_f20 > 0.0f) % 1",
    "comma": "(var_f20 > 0.0f, 0)",
}


def replace_last(source: str, old: str, new: str) -> str:
    if old not in source:
        raise ValueError(old)
    before, after = source.rsplit(old, 1)
    return before + new + after


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    rows = []
    for anchor_name, (old, template) in ANCHORS.items():
        for form_name, zero in ZERO_FORMS.items():
            source = replace_last(BASE, old, template.replace("{zero}", zero))
            tag = f"{anchor_name}_{form_name}"
            path = f"/tmp/codex_factor_tail_cost_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_factor_tail_cost_{tag}.o"
            )
            prefix = fp_prefix(
                f"/tmp/codex_factor_tail_cost_{tag}.o"
            ) if natural.get("ok") else -1
            rows.append((tag, natural, prefix))

    for tag, result, prefix in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[2],
            abs(row[1].get("insns", 9999) - len(TARGET)),
            row[1].get("norm", 9999),
            row[0],
        ),
    ):
        print(
            tag,
            "prefix",
            prefix,
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(result.get("f20_operands", 0) > 0 for _, result, _ in rows),
    )


if __name__ == "__main__":
    main()
