#!/usr/bin/env python3
"""Factorial recovery of the remaining integer-register source topology."""

from __future__ import annotations

import itertools
import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = pathlib.Path("/tmp/codex_unk34_left_associative.c")
BASE = BASE_PATH.read_text(encoding="utf-8")
TARGET = ORACLE["TARGET_INSNS"]
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"


WAVE_OLD = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""

WAVE_NEW = """\
        var_v1 = gRacerWaveCount - 1;
        for (var_a0 = var_v1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""

SPINOUT_OLD = """\
        xRotationOffset = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (xRotationOffset > 0x8000) {
            xRotationOffset -= 0xFFFF;
        }
        if (xRotationOffset < -0x8000) {
            xRotationOffset += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (xRotationOffset * updateRate) >> 4;
"""

SPINOUT_NEW = """\
        var_v1 = obj->trans.rotation.x_rotation;
        var_v0 = 0xD800 - (var_v1 & 0xFFFF);
        if (var_v0 > 0x8000) {
            var_v0 -= 0xFFFF;
        }
        if (var_v0 < -0x8000) {
            var_v0 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation = var_v1 + ((var_v0 * updateRate) >> 4);
"""

STEER_OLD = """\
            racerSteerAngle = racer->steerAngle;
            spA1 = FALSE;
"""

STEER_NEW = """\
            var_a0 = racer->steerAngle;
            spA1 = FALSE;
"""

AIR_OLD = """\
                var_v1 = obj->trans.rotation.x_rotation;
                xRotationOffset = 0;
                var_t0 = racerSteerAngle;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    xRotationOffset = var_v1 - 0x3000;
                    if (xRotationOffset > 0x1000) {
                        xRotationOffset = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    xRotationOffset = var_v1 + 0x3000;
                    if (xRotationOffset < -0x1000) {
                        xRotationOffset = -0x1000;
                    }
                    xRotationOffset = -xRotationOffset;
                }
                var_t0 *= (f32) (1.0 - ((f32) xRotationOffset / 4096));
"""

AIR_NEW = """\
                var_v1 = obj->trans.rotation.x_rotation;
                var_t0 = var_a0;
                var_a0 = 0;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    var_a0 = var_v1 - 0x3000;
                    if (var_a0 > 0x1000) {
                        var_a0 = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    var_a0 = var_v1 + 0x3000;
                    if (var_a0 < -0x1000) {
                        var_a0 = -0x1000;
                    }
                    var_a0 = -var_a0;
                }
                var_t0 *= (f32) (1.0 - ((f32) var_a0 / 4096));
"""

GROUND_OLD = """\
                if (gCurrentRacerInput & R_TRIG) {
                    var_t0 = racerSteerAngle * 6;
                } else {
                    var_t0 = racerSteerAngle * 4;
                }
"""

GROUND_NEW = """\
                if (gCurrentRacerInput & R_TRIG) {
                    var_t0 = var_a0 * 6;
                } else {
                    var_t0 = var_a0 * 4;
                }
"""

ROTATION_OLD = """\
            if (!(gCurrentRacerInput & R_TRIG)) {
                obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }
"""

ROTATION_NEW = """\
            if (!(gCurrentRacerInput & R_TRIG)) {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }
"""


TRANSFORMS = {
    "wave": [(WAVE_OLD, WAVE_NEW)],
    "computer_eq": [
        (
            "    if ((var_v0 == PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {\n",
            "    if ((PLAYER_COMPUTER == var_v0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {\n",
        )
    ],
    "spinout": [(SPINOUT_OLD, SPINOUT_NEW)],
    "steer": [
        (STEER_OLD, STEER_NEW),
        (AIR_OLD, AIR_NEW),
        (GROUND_OLD, GROUND_NEW),
    ],
    "rotation": [(ROTATION_OLD, ROTATION_NEW)],
}


def transform(source: str, names: tuple[str, ...]) -> str:
    for name in names:
        for old, new in TRANSFORMS[name]:
            if source.count(old) != 1:
                raise ValueError(f"{name}: expected one source fragment, found {source.count(old)}")
            source = source.replace(old, new, 1)
    return source


def regs(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def forced_metrics(obj: pathlib.Path) -> dict[str, object]:
    _, candidate = ORACLE["dump_object"](str(obj))
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if regs(expected[1]) != regs(actual[1])
    ]
    fp_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if re.findall(r"\$f\d+", expected[1])
        != re.findall(r"\$f\d+", actual[1])
    ]
    return {
        "insns": len(candidate),
        "regs": len(reg_bad) + abs(len(TARGET) - len(candidate)),
        "fp": len(fp_bad) + abs(len(TARGET) - len(candidate)),
        "reg_bad": reg_bad,
    }


def main() -> None:
    names = tuple(TRANSFORMS)
    results = []
    for mask in range(1 << len(names)):
        selected = tuple(name for bit, name in enumerate(names) if mask & (1 << bit))
        tag = "+".join(selected) or "baseline"
        source = transform(BASE, selected)
        source_path = pathlib.Path(f"/tmp/codex_gpr_{mask:02x}.c")
        forced_obj = pathlib.Path(f"/tmp/codex_gpr_{mask:02x}_forced.o")
        trace = forced_obj.with_suffix(".trace")
        source_path.write_text(source, encoding="utf-8")
        natural = ORACLE["evaluate"](source)
        proc = subprocess.run(
            [FORCED_RUNNER, str(source_path), str(forced_obj), str(trace)],
            check=False,
            capture_output=True,
            text=True,
        )
        forced = (
            forced_metrics(forced_obj)
            if proc.returncode == 0
            else {"error": proc.stderr[-1000:]}
        )
        results.append((forced.get("regs", 100000), tag, natural, forced, source_path))
        print(
            tag,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            {key: value for key, value in forced.items() if key != "reg_bad"},
        )
    print("\nBEST")
    for _, tag, natural, forced, source_path in sorted(results)[:12]:
        print(tag, ORACLE["concise"](natural), forced, source_path)


if __name__ == "__main__":
    main()
