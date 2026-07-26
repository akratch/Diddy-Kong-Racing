#!/usr/bin/env python3
"""Raise spEC ahead of the three f64 blocker webs using weighted loop forms."""

from __future__ import annotations

import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

WHEEL_TOP = "        for (var_t0 = 0; var_t0 < 4; var_t0++) {\n"
WHEEL_ASSIGN = "                i = racer->wheel_surfaces[var_t0];\n"
WAVE_LOOP = """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}
"""

STATEMENTS = {
    "self": "spEC = spEC;",
    "plus": "spEC = +spEC;",
    "zero": "spEC = 0.0f;",
    "velocity": "spEC = racer->velocity;",
    "load": "(void) spEC;",
    "izero": "i += (spEC > 0.0f) * 0;",
    "vzero": "var_t0 += (spEC > 0.0f) * 0;",
    "assign_izero": "i += (spEC = racer->velocity, spEC > 0.0f) * 0;",
    "assign_vzero": "var_t0 += (spEC = racer->velocity, spEC > 0.0f) * 0;",
    "round_izero": "i += (spEC = +spEC, spEC > 0.0f) * 0;",
    "round_vzero": "var_t0 += (spEC = +spEC, spEC > 0.0f) * 0;",
}


def make(location: str, statement: str, count: int) -> str:
    repeated = "\n".join("            " + statement for _ in range(count))
    if location == "wheel_top":
        return BASE.replace(WHEEL_TOP, WHEEL_TOP + repeated + "\n", 1)
    if location == "wheel_assign":
        repeated = "\n".join("                " + statement for _ in range(count))
        return BASE.replace(WHEEL_ASSIGN, repeated + "\n" + WHEEL_ASSIGN, 1)
    if location == "wave_body":
        repeated = "\n".join("            " + statement for _ in range(count))
        block = WAVE_LOOP[:-3] + "{\n" + repeated + "\n        }\n"
        return BASE.replace(WAVE_LOOP, block, 1)
    raise ValueError(location)


def trace_metrics(path: str) -> dict[str, str]:
    metrics: dict[str, str] = {}
    with open(path, encoding="utf-8") as input_file:
        for line in input_file:
            if "RACER-FVAR" in line and "addr=-12 " in line:
                match = re.search(r"adjsave=([0-9.-]+) uses=(\d+)", line)
                if match:
                    metrics["spEC"] = "/".join(match.groups())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    metrics["factor"] = "/".join(match.groups())
    return metrics


def main() -> None:
    rows = []
    for location in ("wheel_top", "wheel_assign", "wave_body"):
        for form, statement in STATEMENTS.items():
            for count in (1, 2, 4, 8):
                if location == "wave_body" and statement.startswith(("i ", "i+")):
                    continue
                tag = f"{location}_{form}_{count}"
                source = make(location, statement, count)
                path = f"/tmp/codex_f64_spEC_loop_{tag}.c"
                obj = f"/tmp/codex_f64_spEC_loop_{tag}.o"
                trace = f"/tmp/codex_f64_spEC_loop_{tag}.trace"
                with open(path, "w", encoding="utf-8") as output:
                    output.write(source)
                natural = ORACLE["evaluate"](source, keep=obj)
                proc = subprocess.run(
                    [ANALYSIS, path, f"/tmp/codex_f64_spEC_loop_{tag}_analysis.o", trace],
                    capture_output=True,
                    text=True,
                )
                metrics = trace_metrics(trace) if proc.returncode == 0 else {}
                rows.append((tag, natural, metrics))

    for tag, natural, metrics in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -float(row[2].get("spEC", "0/0").split("/")[0]),
            abs(row[1].get("insns", 9999) - 2625),
            row[1].get("norm", 9999),
        ),
    ):
        if (
            natural.get("f20_operands", 0) > 0
            or float(metrics.get("spEC", "0/0").split("/")[0]) != 0.944444
        ):
            print(tag, metrics, ORACLE["concise"](natural), natural.get("fp"))
    print("tested", len(rows))


if __name__ == "__main__":
    main()
