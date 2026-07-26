#!/usr/bin/env python3
"""Put high-priority spEC webs ahead of the three final-drag pressure webs."""

from __future__ import annotations

import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
PRESSURE = runpy.run_path(".codex_racer_pressure_exact.py")
PRESEED = runpy.run_path(".codex_racer_spEC_preseed.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

GROUPS = (
    tuple(PRESEED["RANGES"]),
    tuple(
        name
        for name in PRESEED["RANGES"]
        if name not in {"speed_curve", "top_scale"}
    ),
)


def pressure_source() -> str:
    old_delta = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += racer->unk34 * spD0 * 4.0f;
"""
    new_delta = """\
        var_f2 = racer->unk34 * spD0;
        var_f20 = racer->unk34 * var_f2;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += var_f2 * 4.0f;
"""
    if BASE.count(old_delta) != 1:
        raise ValueError("current unk34 block is not unique")
    source = BASE.replace(old_delta, new_delta, 1)
    return PRESSURE["shape"](
        source,
        "products",
        ("spCC", "var_f6", "segmentXVelocity"),
    )


def merge(source: str, selected: tuple[str, ...]) -> str:
    replacements: list[tuple[int, int]] = []
    for name in selected:
        start_marker, end_marker, old = PRESEED["RANGES"][name]
        start = source.index(start_marker)
        end = source.index(end_marker, start) + len(end_marker)
        for match in re.finditer(rf"\b{re.escape(old)}\b", source):
            if start <= match.start() < end:
                replacements.append((match.start(), match.end()))
    for start, end in sorted(set(replacements), reverse=True):
        source = source[:start] + "spEC" + source[end:]
    return source


def metrics(path: str) -> list[str]:
    output: list[str] = []
    with open(path, encoding="utf-8") as input_file:
        for line in input_file:
            if (
                "RACER-COLOR bit" in line
                or "FACTOR before-cost" in line
                or "FACTOR-CHOICE" in line
            ):
                output.append(line.strip())
    return output


def main() -> None:
    for selected in GROUPS:
        base_tag = "all" if len(selected) == len(PRESEED["RANGES"]) else "safe"
        merged = merge(pressure_source(), selected)
        cases = ((base_tag, merged),)
        if base_tag == "safe":
            f64_spEC = merged.replace(
                "    f32 spEC;\n",
                "    f64 spEC;\n",
                1,
            )
            cases += (
                (
                    "safe_f64_spEC",
                    f64_spEC,
                ),
                (
                    "safe_f64_spEC_splitheld",
                    f64_spEC.replace(
                        "        var_f20 += var_f2 * 4.0f;\n",
                        "        var_f20 += racer->unk34 * spD0 * 4.0f;\n",
                        1,
                    ),
                ),
            )
        for tag, source in cases:
            path = f"/tmp/codex_pressure_spEC_{tag}.c"
            trace = f"/tmp/codex_pressure_spEC_{tag}.trace"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            result = ORACLE["evaluate"](
                source,
                keep=f"/tmp/codex_pressure_spEC_{tag}.o",
            )
            subprocess.run(
                [
                    ANALYSIS,
                    path,
                    f"/tmp/codex_pressure_spEC_{tag}_analysis.o",
                    trace,
                ],
                check=True,
                capture_output=True,
                text=True,
            )
            print(tag, ORACLE["concise"](result), result.get("fp"))
            for line in metrics(trace):
                print(" ", line)


if __name__ == "__main__":
    main()
