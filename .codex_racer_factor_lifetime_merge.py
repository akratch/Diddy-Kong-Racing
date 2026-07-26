#!/usr/bin/env python3
"""Broaden disjoint source lifetimes merged into the long factor web."""

from __future__ import annotations

import itertools
import os
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

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
    "top_suffix": (
        "    var_f14 = var_f14 * var_f0;\n",
        "            obj->z_velocity += racer->oz1 * racerBrake;\n",
        "var_f14",
    ),
    "inverse_rate": (
        "        var_f0 = 1.0f / updateRateF;\n",
        "        spEC = (obj->trans.z_position - spE0 - D_8011D54C) * var_f0;\n",
        "var_f0",
    ),
}

BLOCK_FORMS = {
    "propulsion": (
        """\
        racerThrottle = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
""",
        """\
        var_f20 = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * var_f20;
        obj->y_velocity -= racer->oy1 * var_f20;
        obj->z_velocity -= racer->oz1 * var_f20;
""",
    ),
    "braking": (
        """\
            racerBrake *= var_f14 / 2;
            obj->x_velocity += racer->ox1 * racerBrake;
            obj->y_velocity += racer->oy1 * racerBrake;
            obj->z_velocity += racer->oz1 * racerBrake;
""",
        """\
            var_f20 = racerBrake * var_f14 / 2;
            obj->x_velocity += racer->ox1 * var_f20;
            obj->y_velocity += racer->oy1 * var_f20;
            obj->z_velocity += racer->oz1 * var_f20;
""",
    ),
}


def make_source(selected: tuple[str, ...]) -> str:
    intervals: list[tuple[int, int, str]] = []
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
        source = source[:start] + "var_f20" + source[end:]
    for name in selected:
        if name in BLOCK_FORMS:
            old, new = BLOCK_FORMS[name]
            if source.count(old) != 1:
                raise ValueError(name)
            source = source.replace(old, new, 1)
    return source


def parse_trace(path: str) -> dict[str, str]:
    metrics: dict[str, str] = {}
    with open(path, encoding="utf-8") as input_file:
        for line in input_file:
            if "FACTOR-COST reg=27 " in line:
                match = re.search(r"cost=([0-9.-]+)", line)
                if match:
                    metrics["caller"] = match.group(1)
            elif "FACTOR-COST reg=30 " in line:
                match = re.search(r"cost=([0-9.-]+)", line)
                if match:
                    metrics["callee"] = match.group(1)
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    metrics["choice"] = "/".join(match.groups())
            elif "RACER-COLOR bit=284 " in line:
                match = re.search(r"adjsave=([0-9.-]+) uses=(\d+)", line)
                if match:
                    metrics["web"] = "/".join(match.groups())
    return metrics


def evaluate(selected: tuple[str, ...]) -> tuple:
    tag = "_".join(selected)
    source = make_source(selected)
    path = f"/tmp/codex_factor_lifetime_{tag}.c"
    trace = f"/tmp/codex_factor_lifetime_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_factor_lifetime_{tag}.o"
    )
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_factor_lifetime_{tag}_analysis.o", trace],
        capture_output=True,
        text=True,
    )
    metrics = parse_trace(trace) if proc.returncode == 0 else {"error": str(proc.returncode)}
    forced = STICK["forced"](path, f"factor_lifetime_{tag}")
    return tag, selected, natural, forced, metrics


def main() -> None:
    names = tuple(RANGES) + tuple(BLOCK_FORMS)
    selected_sets = [(name,) for name in names]
    selected_sets += [tuple(RANGES)]
    rows = [evaluate(selected) for selected in selected_sets]
    viable = [
        name
        for name in names
        if any(
            row[1] == (name,)
            and row[2].get("ok")
            and float(row[4].get("caller", "0")) >= 21.0
            for row in rows
        )
    ]
    for count in range(2, min(6, len(viable) + 1)):
        for selected in itertools.combinations(viable, count):
            if "top_suffix" in selected and (
                "propulsion" in selected or "braking" in selected
            ):
                continue
            rows.append(evaluate(selected))

    for tag, selected, natural, forced, metrics in sorted(
        rows,
        key=lambda row: (
            row[4].get("choice", "99").split("/")[0] != "30",
            -float(row[4].get("caller", "0")),
            row[3].get("mismatch", 9999),
            row[0],
        ),
    ):
        print(
            tag,
            "cost",
            metrics,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced,
        )
    print("tested", len(rows), "viable", ",".join(viable))


if __name__ == "__main__":
    main()
