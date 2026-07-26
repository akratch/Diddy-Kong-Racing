#!/usr/bin/env python3
"""Test whether earlier disjoint float ranges can make spEC preseed f20."""

from __future__ import annotations

import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
FIRST_SPEC = "        spEC = racer->velocity * racer->velocity;\n"

RANGES = {
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
    "steer_divisor": (
        "    if (racer->trickType != 0) {\n",
        "    var_v1 = var_v0 * updateRateF / var_f2;\n",
        "var_f2",
    ),
    "height_factor": (
        "    var_f2 = (gCurrentCourseHeight - 50.0) - obj->trans.y_position;\n",
        "        spA3 = TRUE;\n",
        "var_f2",
    ),
    "speed_curve": (
        "    var_f14 = racer->velocity;\n",
        "              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));\n",
        "var_f14",
    ),
    "speed_fraction": (
        "    var_f0 = racer->velocity;\n",
        "              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));\n",
        "var_f0",
    ),
    "buoyancy": (
        "        var_f2 = racer->buoyancy - 20.0f;\n",
        "        var_f20 -= var_f2 / 10;\n",
        "var_f2",
    ),
    "trick_clamp": (
        "            var_f2 = -racer->velocity;\n",
        "            var_t0 *= var_f2;\n",
        "var_f2",
    ),
    "top_factor": (
        "    var_f0 = handle_racer_top_speed(obj, racer);\n",
        "    var_f14 = var_f14 * var_f0;\n",
        "var_f0",
    ),
    "top_scale": (
        "    var_f0 = handle_racer_top_speed(obj, racer);\n",
        "            racerBrake *= var_f14 / 2;\n",
        "var_f14",
    ),
}


def make_source(selected: tuple[str, ...]) -> str:
    intervals: list[tuple[int, int, str]] = []
    for name in selected:
        start_marker, end_marker, old = RANGES[name]
        start = BASE.index(start_marker)
        end = BASE.index(end_marker, start) + len(end_marker)
        intervals.append((start, end, old))

    replacements: list[tuple[int, int]] = []
    for start, end, old in intervals:
        for match in re.finditer(rf"\b{re.escape(old)}\b", BASE):
            if start <= match.start() < end:
                replacements.append((match.start(), match.end()))
    if not replacements:
        raise ValueError(selected)

    source = BASE
    for start, end in sorted(set(replacements), reverse=True):
        source = source[:start] + "spEC" + source[end:]
    return source


def parse_trace(path: str) -> dict[str, str]:
    data: dict[str, str] = {}
    with open(path, encoding="utf-8") as input_file:
        for line in input_file:
            if "RACER-COLOR" in line and "addr=-12 " in line:
                match = re.search(
                    r"reg=(\d+) adjsave=([0-9.-]+) uses=(\d+) "
                    r"cost=([0-9.-]+)",
                    line,
                )
                if match:
                    data["spEC"] = "/".join(match.groups())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    data["factor"] = "/".join(match.groups())
    return data


def evaluate(tag: str, selected: tuple[str, ...]) -> tuple:
    source = make_source(selected)
    path = f"/tmp/codex_spEC_preseed_{tag}.c"
    obj = f"/tmp/codex_spEC_preseed_{tag}.o"
    trace = f"/tmp/codex_spEC_preseed_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](source, keep=obj)
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_spEC_preseed_{tag}_analysis.o", trace],
        capture_output=True,
        text=True,
    )
    metrics = parse_trace(trace) if proc.returncode == 0 else {"error": str(proc.returncode)}
    return tag, selected, natural, metrics


def main() -> None:
    groups = [(name,) for name in RANGES]
    groups += [
        tuple(RANGES),
        tuple(name for name in RANGES if name not in {"speed_curve", "top_scale"}),
        ("wave_height", "wave_speed"),
        ("speed_curve", "speed_fraction"),
        ("height_factor", "buoyancy", "trick_clamp", "steer_divisor"),
        ("speed_curve", "top_scale"),
        ("wave_speed", "speed_curve", "speed_fraction", "top_scale"),
    ]
    rows = []
    seen: set[tuple[str, ...]] = set()
    for selected in groups:
        selected = tuple(dict.fromkeys(selected))
        if selected in seen:
            continue
        seen.add(selected)
        rows.append(evaluate("_".join(selected), selected))

    promising = [
        name
        for name in RANGES
        if any(
            row[1] == (name,)
            and float(row[3].get("spEC", "0/0/0/0").split("/")[1]) >= 0.75
            for row in rows
        )
    ]
    for count in range(2, min(5, len(promising) + 1)):
        for selected in itertools.combinations(promising, count):
            if selected not in seen:
                seen.add(selected)
                rows.append(evaluate("_".join(selected), selected))

    for tag, selected, natural, metrics in sorted(
        rows,
        key=lambda row: (
            row[3].get("factor", "99").split("/")[0] != "30",
            -float(row[3].get("spEC", "0/0/0/0").split("/")[1]),
            row[0],
        ),
    ):
        print(
            tag,
            "spEC",
            metrics.get("spEC", "-"),
            "factor",
            metrics.get("factor", "-"),
            ORACLE["concise"](natural),
            natural.get("fp"),
        )
    print("tested", len(rows), "promising", ",".join(promising))


if __name__ == "__main__":
    main()
