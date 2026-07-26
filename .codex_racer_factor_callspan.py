#!/usr/bin/env python3
"""Raise factor caller-save cost with erased uses spanning existing calls."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
Z = "0 + ((var_f20 > 0.0f) * 0)"
EDITS = (
    (
        "drag",
        "            if (!(gCurrentRacerInput & R_TRIG) || racer->groundedWheels == 0 || racer->zipperDirCorrection != 0) {\n",
        f"            if (!(gCurrentRacerInput & R_TRIG) || racer->groundedWheels == 0 || racer->zipperDirCorrection != {Z}) {{\n",
    ),
    (
        "particles",
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->velocity < -4.0f) {\n",
        f"    if (gCurrentPlayerIndex != PLAYER_COMPUTER + {Z} && racer->velocity < -4.0f) {{\n",
    ),
    (
        "boost",
        "    if (racer->boostTimer > 0) {\n",
        f"    if (racer->boostTimer > {Z}) {{\n",
    ),
    (
        "propulsion",
        "    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {\n",
        f"    if (racer->zipperDirCorrection == {Z} && gRaceStartTimer == 0) {{\n",
    ),
    (
        "magnet",
        "    if (racer->magnetTimer != 0) {\n",
        f"    if (racer->magnetTimer != {Z}) {{\n",
    ),
    (
        "approach",
        "    if (racer->approachTarget == NULL) {\n",
        f"    if (racer->approachTarget == NULL + {Z}) {{\n",
    ),
    (
        "computer",
        "    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {\n",
        f"    if (gCurrentPlayerIndex == PLAYER_COMPUTER + {Z}) {{\n",
    ),
    (
        "landed",
        "    if (var_t0 == 0 && racer->groundedWheels != 0 && racer->spinout_timer != 0) {\n",
        f"    if (var_t0 == {Z} && racer->groundedWheels != 0 && racer->spinout_timer != 0) {{\n",
    ),
    (
        "unk1d2",
        "    if (racer->unk1D2 != 0) {\n",
        f"    if (racer->unk1D2 != {Z}) {{\n",
    ),
    (
        "race100",
        "    if (gRaceStartTimer == 100) {\n",
        f"    if (gRaceStartTimer == 100 + {Z}) {{\n",
    ),
    (
        "attach",
        "    if (obj->attachPoints != NULL && obj->attachPoints->count >= 3) {\n",
        f"    if (obj->attachPoints != NULL + {Z} && obj->attachPoints->count >= 3) {{\n",
    ),
    (
        "viewport",
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {\n",
        f"    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == {Z} && gNumViewports < 2) {{\n",
    ),
    (
        "vehicle",
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES) {\n",
        f"    if (racer->vehicleIDPrev < VEHICLE_BOSSES + {Z}) {{\n",
    ),
    (
        "moved",
        "    if (playerObjectMoved != FALSE) {\n",
        f"    if (playerObjectMoved != FALSE + {Z}) {{\n",
    ),
)


def apply_edits(indices: tuple[int, ...]) -> str:
    source = BASE
    for index in indices:
        _, old, new = EDITS[index]
        if old not in source:
            raise ValueError((index, old))
        # Several anchors repeat; the relevant call-spanning point is the last.
        before, after = source.rsplit(old, 1)
        source = before + new + after
    return source


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def evaluate(indices: tuple[int, ...]) -> tuple:
    tag = "-".join(EDITS[index][0] for index in indices)
    source = apply_edits(indices)
    path = f"/tmp/codex_factor_callspan_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_factor_callspan_{tag}.o"
    )
    prefix = fp_prefix(
        f"/tmp/codex_factor_callspan_{tag}.o"
    ) if natural.get("ok") else -1
    return tag, natural, prefix


def main() -> None:
    rows = [evaluate((index,)) for index in range(len(EDITS))]
    rows += [
        evaluate(tuple(range(end)))
        for end in range(2, len(EDITS) + 1)
    ]
    # Cover the likely independent spans without an unrestricted powerset.
    focus = (0, 2, 3, 5, 7, 8, 10, 11, 12, 13)
    rows += [
        evaluate(group)
        for count in (2, 3, 4)
        for group in itertools.combinations(focus, count)
    ]

    unique = {}
    for row in rows:
        unique[row[0]] = row
    rows = list(unique.values())
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
        if result.get("f20_operands", 0) > 0 or prefix > 580:
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
