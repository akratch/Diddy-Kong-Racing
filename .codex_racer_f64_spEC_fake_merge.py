#!/usr/bin/env python3
"""Merge the erased early var_f0 comparison into spEC on the f64 family."""

from __future__ import annotations

import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

for unused in (
    "    f32 spCC;\n",
    "    f32 var_f6;\n",
    "    f32 segmentXVelocity;\n",
    "    s32 pad4;\n",
):
    BASE = BASE.replace(unused, "", 1)
BASE = BASE.replace(
    "    Object_Boost *boostObj;\n",
    "    Object_Boost *boostObj;\n"
    "    f64 d0;\n"
    "    f64 d1;\n"
    "    f64 d2;\n"
    "    f64 d3;\n",
    1,
)
BASE = BASE.replace(
    "        racer->forwardVel -= "
    "(racer->forwardVel + (racer->velocity * 0.05)) * 0.125;\n",
    "        d0 = racer->velocity * 0.05;\n"
    "        d1 = racer->forwardVel + d0;\n"
    "        d2 = d1 * 0.125;\n"
    "        d3 = racer->forwardVel - d2;\n"
    "        racer->forwardVel = d3;\n",
    1,
)

FAKE = "    gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;\n"
FIRST_SPEC = "        spEC = racer->velocity * racer->velocity;\n"

RANGES = {
    "speed_fraction": (
        "    var_f0 = racer->velocity;\n",
        "              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));\n",
        "var_f0",
    ),
    "top_factor": (
        "    var_f0 = handle_racer_top_speed(obj, racer);\n",
        "    var_f14 = var_f14 * var_f0;\n",
        "var_f0",
    ),
    "wave_height": (
        "        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;\n",
        "            obj->trans.y_position += ((38 - var_f2) * updateRateF * racerVelocity) / 8;\n",
        "var_f2",
    ),
    "wave_speed": (
        "        racerVelocity = -racer->velocity;\n",
        "            obj->trans.y_position += ((38 - var_f2) * updateRateF * racerVelocity) / 8;\n",
        "racerVelocity",
    ),
    "steer": (
        "    if (racer->trickType != 0) {\n",
        "    var_v1 = var_v0 * updateRateF / var_f2;\n",
        "var_f2",
    ),
    "trick": (
        "            var_f2 = -racer->velocity;\n",
        "            var_t0 *= var_f2;\n",
        "var_f2",
    ),
}


def make(selected: tuple[str, ...]) -> str:
    intervals: list[tuple[int, int, str]] = []
    if "fake" in selected:
        start = BASE.index(FAKE)
        intervals.append((start, start + len(FAKE), "var_f0"))
    if "whole_varf0" in selected:
        begin = BASE.index("\n\n    if (func_8000E138())")
        end = BASE.index(FIRST_SPEC, begin)
        intervals.append((begin, end, "var_f0"))
    for name in selected:
        if name not in RANGES:
            continue
        start_marker, end_marker, old = RANGES[name]
        start = BASE.index(start_marker)
        end = BASE.index(end_marker, start) + len(end_marker)
        intervals.append((start, end, old))

    replacements: list[tuple[int, int]] = []
    for start, end, old in intervals:
        for match in re.finditer(rf"\b{re.escape(old)}\b", BASE):
            if start <= match.start() < end:
                replacements.append((match.start(), match.end()))
    source = BASE
    for start, end in sorted(set(replacements), reverse=True):
        source = source[:start] + "spEC" + source[end:]
    return source


def metrics(path: str) -> dict[str, str]:
    result: dict[str, str] = {}
    with open(path, encoding="utf-8") as input_file:
        for line in input_file:
            if "RACER-FVAR" in line and "addr=-12 " in line:
                match = re.search(r"adjsave=([0-9.-]+) uses=(\d+)", line)
                if match:
                    result["spEC"] = "/".join(match.groups())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    result["factor"] = "/".join(match.groups())
    return result


def main() -> None:
    names = ("fake",) + tuple(RANGES)
    selected_sets = [
        combo
        for count in range(1, 5)
        for combo in itertools.combinations(names, count)
    ]
    selected_sets += [
        ("whole_varf0",),
        ("whole_varf0", "wave_height"),
        ("whole_varf0", "wave_speed"),
        ("whole_varf0", "steer"),
        ("whole_varf0", "trick"),
        ("whole_varf0", "wave_height", "wave_speed", "steer", "trick"),
    ]
    rows = []
    for selected in selected_sets:
        tag = "_".join(selected)
        source = make(selected)
        path = f"/tmp/codex_f64_spEC_fake_{tag}.c"
        trace = f"/tmp/codex_f64_spEC_fake_{tag}.trace"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_f64_spEC_fake_{tag}.o"
        )
        proc = subprocess.run(
            [
                ANALYSIS,
                path,
                f"/tmp/codex_f64_spEC_fake_{tag}_analysis.o",
                trace,
            ],
            capture_output=True,
            text=True,
        )
        rows.append((tag, natural, metrics(trace) if proc.returncode == 0 else {}))

    for tag, natural, trace_data in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -float(row[2].get("spEC", "0/0").split("/")[0]),
            abs(row[1].get("insns", 9999) - 2625),
            row[1].get("norm", 9999),
        ),
    ):
        print(tag, trace_data, ORACLE["concise"](natural), natural.get("fp"))
    print("tested", len(rows))


if __name__ == "__main__":
    main()
