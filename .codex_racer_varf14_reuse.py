#!/usr/bin/env python3
"""Merge disjoint float lifetimes into var_f14 and test natural allocation."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]


def rename_region(
    source: str,
    start_marker: str,
    end_marker: str,
    old: str,
) -> str:
    start = source.index(start_marker)
    end = source.index(end_marker, start)
    region = source[start:end]
    if old not in region:
        raise ValueError(f"{old} absent from selected region")
    return source[:start] + re.sub(rf"\b{old}\b", "var_f14", region) + source[end:]


def wave_height(source: str) -> str:
    return rename_region(
        source,
        "        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;\n",
        "        // previously var_f0\n",
        "var_f2",
    )


def wave_velocity(source: str) -> str:
    return rename_region(
        source,
        "        // previously var_f0\n",
        "    D_8011D550 = 0;\n",
        "racerVelocity",
    )


def steer_divisor(source: str) -> str:
    return rename_region(
        source,
        "    if (racer->trickType != 0) {\n",
        "    racer->steerAngle += var_v1;\n",
        "var_f2",
    )


def drag_sp_ec(source: str) -> str:
    return rename_region(
        source,
        "        spEC = racer->velocity * racer->velocity;\n",
        "    var_f20 = racer->lateral_velocity * racer->lateral_velocity * spD4;\n",
        "spEC",
    )


def lateral_factor(source: str) -> str:
    return rename_region(
        source,
        "    var_f20 = racer->lateral_velocity * racer->lateral_velocity * spD4;\n",
        "        racer->forwardVel -= ",
        "var_f20",
    )


def move_x(source: str) -> str:
    return rename_region(
        source,
        "        var_f20 = obj->x_velocity;\n",
        "    gCurrentRacerTransform.rotation.y_rotation =",
        "var_f20",
    )


def move_z(source: str) -> str:
    return rename_region(
        source,
        "        var_f20 = obj->x_velocity;\n",
        "    gCurrentRacerTransform.rotation.y_rotation =",
        "spEC",
    )


def final_inv_rate(source: str) -> str:
    return rename_region(
        source,
        "        var_f0 = 1.0f / updateRateF;\n",
        "    gCurrentRacerTransform.rotation.y_rotation =",
        "var_f0",
    )


def final_x(source: str) -> str:
    return rename_region(
        source,
        "        var_f0 = 1.0f / updateRateF;\n",
        "    gCurrentRacerTransform.rotation.y_rotation =",
        "var_f20",
    )


def final_z(source: str) -> str:
    return rename_region(
        source,
        "        var_f0 = 1.0f / updateRateF;\n",
        "    gCurrentRacerTransform.rotation.y_rotation =",
        "spEC",
    )


TRANSFORMS = {
    "wave_height": wave_height,
    "wave_velocity": wave_velocity,
    "steer_divisor": steer_divisor,
    "drag_sp_ec": drag_sp_ec,
    "lateral_factor": lateral_factor,
    "move_x": move_x,
    "move_z": move_z,
    "final_inv_rate": final_inv_rate,
    "final_x": final_x,
    "final_z": final_z,
}


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def evaluate(selected: tuple[str, ...]) -> tuple:
    source = BASE
    for name in selected:
        source = TRANSFORMS[name](source)
    tag = "_".join(selected)
    path = f"/tmp/codex_varf14_reuse_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_varf14_reuse_{tag}_natural.o"
    )
    forced = STICK["forced"](path, f"varf14_reuse_{tag}")
    obj = f"/tmp/codex_stickform_varf14_reuse_{tag}_forced.o"
    prefix = fp_prefix(obj) if forced.get("ok") else -1
    return tag, natural, forced, prefix


def main() -> None:
    rows = [evaluate((name,)) for name in TRANSFORMS]
    exact_singletons = [
        (tag,) for tag, _, forced, prefix in rows
        if prefix == len(TARGET) and forced.get("insns") == len(TARGET)
    ]
    exact_names = tuple(tag[0] for tag in exact_singletons)
    for count in range(2, min(5, len(exact_names)) + 1):
        for selected in itertools.combinations(exact_names, count):
            rows.append(evaluate(selected))
    for tag, natural, forced, prefix in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[3],
            row[2].get("mismatch", 9999),
            row[0],
        ),
    ):
        print(
            tag,
            "prefix",
            prefix,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced,
        )


if __name__ == "__main__":
    main()
