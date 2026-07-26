#!/usr/bin/env python3
"""Combine two small one-shot loops to put factor call cost just above 60."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
FIRST_START = """\
    if (racer->zipperDirCorrection != 0 && racer->spinout_timer == 0) {
"""
FIRST_END = """\
    if (racer->spinout_timer != 0) {
"""
SECOND_START = """\
        if (racer->groundedWheels != 0 && ((xRotationOffset > 0x6000 && racer->x_rotation_offset <= 0x6000) ||
"""
SECOND_END = """\
        gCurrentRacerInput &= ~(A_BUTTON | Z_TRIG);
"""
ZERO_FORMS = {
    "mul": "(var_f20 > 0.0f) * 0",
    "and": "(var_f20 > 0.0f) & 0",
    "comma": "(var_f20 > 0.0f, 0)",
    "ternary": "(var_f20 > 0.0f) ? 0 : 0",
    "notnot": "!!(var_f20 > 0.0f) * 0",
}
LOOP_FORMS = {
    "for": (
        "    {counter} = 0;\n    for (; {counter} < 1; {counter}++) {{\n",
        "        {counter} += {zero};\n    }}\n",
    ),
    "while": (
        "    {counter} = 1;\n    while ({counter}) {{\n",
        "        {counter} += {zero};\n"
        "        {counter} = 0;\n"
        "    }}\n",
    ),
}


def wrap(
    source: str,
    start: str,
    end: str,
    loop_form: str,
    counter: str,
    zero_form: str,
) -> str:
    if source.count(start) != 1 or source.count(end) != 1:
        raise ValueError((source.count(start), source.count(end)))
    if source.index(start) >= source.index(end):
        raise ValueError("bad interval")
    opening, closing = LOOP_FORMS[loop_form]
    opening = opening.format(counter=counter, zero=ZERO_FORMS[zero_form])
    closing = closing.format(counter=counter, zero=ZERO_FORMS[zero_form])
    source = source.replace(start, opening + start, 1)
    source = source.replace(end, closing + end, 1)
    return source


def make(
    first_loop: str,
    first_zero: str,
    second_loop: str,
    second_zero: str,
) -> str:
    source = wrap(
        BASE,
        FIRST_START,
        FIRST_END,
        first_loop,
        "pad5",
        first_zero,
    )
    return wrap(
        source,
        SECOND_START,
        SECOND_END,
        second_loop,
        "pad7",
        second_zero,
    )


def evaluate(case: tuple[str, str, str, str]) -> tuple:
    first_loop, first_zero, second_loop, second_zero = case
    tag = f"{first_loop}_{first_zero}_{second_loop}_{second_zero}"
    source = make(*case)
    path = f"/tmp/codex_dual_loop_cost_{tag}.c"
    trace = f"/tmp/codex_dual_loop_cost_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_dual_loop_cost_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_dual_loop_cost_{tag}_analysis.o",
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
        (first_loop, first_zero, second_loop, second_zero)
        for first_loop in LOOP_FORMS
        for first_zero in ZERO_FORMS
        for second_loop in LOOP_FORMS
        for second_zero in ZERO_FORMS
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
                f"/tmp/codex_dual_loop_cost_promising_{tag}.c",
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
