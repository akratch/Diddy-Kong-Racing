#!/usr/bin/env python3
"""Raise only the factor's call cost in a mostly-integer one-shot loop."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
STARTS = {
    "rotation": """\
    if (racer->zipperDirCorrection != 0 && racer->spinout_timer == 0) {
""",
    "spinout": """\
    if (racer->spinout_timer != 0) {
""",
}
ENDS = {
    "spinout": """\
    if (racer->spinout_timer != 0) {
""",
    "crash_call": """\
        gCurrentRacerInput &= ~(A_BUTTON | Z_TRIG);
""",
    "tricks": """\
        } else {
            racerSteerAngle = racer->steerAngle;
""",
    "drag": """\
            if (!(gCurrentRacerInput & R_TRIG) || racer->groundedWheels == 0 || racer->zipperDirCorrection != 0) {
""",
    "top": """\
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->velocity < -4.0f) {
""",
}
ZERO_FORMS = {
    "mul": "(var_f20 > 0.0f) * 0",
    "and": "(var_f20 > 0.0f) & 0",
    "comma": "(var_f20 > 0.0f, 0)",
    "ternary": "(var_f20 > 0.0f) ? 0 : 0",
    "notnot": "!!(var_f20 > 0.0f) * 0",
}
LOOPS = {
    "for": (
        "    pad5 = 0;\n    for (; pad5 < 1; pad5++) {\n",
        "        pad5 += {zero};\n    }\n",
    ),
    "do": (
        "    pad5 = 0;\n    do {\n",
        "        pad5 += {zero};\n    } while (++pad5 < 1);\n",
    ),
}


def make(
    start_name: str,
    end_name: str,
    loop_name: str,
    zero_name: str,
) -> str:
    source = BASE
    start = STARTS[start_name]
    end = ENDS[end_name]
    if source.count(start) != 1 or source.count(end) != 1:
        raise ValueError(
            (start_name, end_name, source.count(start), source.count(end))
        )
    if source.index(start) >= source.index(end):
        raise ValueError((start_name, end_name))
    opening, closing = LOOPS[loop_name]
    closing = closing.replace("{zero}", ZERO_FORMS[zero_name])
    source = source.replace(start, opening + start, 1)
    source = source.replace(end, closing + end, 1)
    return source


def evaluate(case: tuple[str, str, str, str]) -> tuple:
    start_name, end_name, loop_name, zero_name = case
    tag = f"{start_name}_{end_name}_{loop_name}_{zero_name}"
    source = make(*case)
    path = f"/tmp/codex_narrow_loop_cost_{tag}.c"
    trace = f"/tmp/codex_narrow_loop_cost_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_narrow_loop_cost_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_narrow_loop_cost_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    metrics: dict[str, str] = {}
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FACTOR-COST reg=27 " in line:
                    match = re.search(r"cost=([0-9.-]+)", line)
                    if match:
                        metrics["caller"] = match.group(1)
                elif "FACTOR-COST reg=30 " in line:
                    match = re.search(
                        r"cost=([0-9.-]+).*first-used=(\\d+)", line
                    )
                    if match:
                        metrics["callee"] = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\\d+) cost=([0-9.-]+)", line)
                    if match:
                        metrics["choice"] = "/".join(match.groups())
    return tag, source, result, metrics, proc.returncode


def main() -> None:
    cases = [
        (start_name, end_name, loop_name, zero_name)
        for start_name in STARTS
        for end_name in ENDS
        for loop_name in LOOPS
        for zero_name in ZERO_FORMS
        if BASE.index(STARTS[start_name]) < BASE.index(ENDS[end_name])
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[2].get("f20_operands", 0) == 0,
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, metrics, returncode in rows:
        if result.get("f20_operands", 0) > 0:
            with open(
                f"/tmp/codex_narrow_loop_cost_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
            "metrics",
            metrics,
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[2].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
