#!/usr/bin/env python3
"""Pay the f20 save cost with a short web after var_f20's final use."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
ANCHOR = "    obj->z_velocity = spEC;\n"
VALUES = (
    "obj->x_velocity",
    "obj->y_velocity",
    "obj->z_velocity",
    "racer->velocity",
    "racer->lateral_velocity",
    "racer->forwardVel",
    "racer->ox1",
    "racer->oy1",
    "racer->oz1",
)


def make(count: int, repeats: int, value_form: str, expression_form: str) -> str:
    names = [f"post_seed_f{index}" for index in range(count)]
    declarations = "".join(f"        f32 {name};\n" for name in names)
    assignments = []
    for index, name in enumerate(names):
        value = VALUES[index]
        rhs = value if value_form == "raw" else f"{value} * {value}"
        assignments.append(f"{name} = {rhs}")
    terms = [name for name in names for _ in range(repeats)]
    if expression_form == "sum":
        condition = "(" + " + ".join(terms) + ") > 0.0f"
    else:
        condition = " + ".join(f"({term} > 0.0f)" for term in terms)
    block = (
        ANCHOR
        + "    {\n"
        + declarations
        + "        D_8011D558 = ("
        + ", ".join(assignments)
        + f", ({condition})) * 0;\n"
        + "    }\n"
    )
    if BASE.count(ANCHOR) != 1:
        raise ValueError(BASE.count(ANCHOR))
    return BASE.replace(ANCHOR, block, 1)


def evaluate(case: tuple[int, int, str, str]) -> tuple:
    count, repeats, value_form, expression_form = case
    tag = f"n{count}_r{repeats}_{value_form}_{expression_form}"
    source = make(*case)
    path = f"/tmp/codex_postfactor_callee_seed_{tag}.c"
    trace = f"/tmp/codex_postfactor_callee_seed_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_postfactor_callee_seed_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_postfactor_callee_seed_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    f20_rows = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
                elif "RACER-COLOR bit" in line and "reg=30 " in line:
                    f20_rows.append(line.strip())
    return tag, result, factor, f20_rows, proc.returncode


def main() -> None:
    cases = [
        (count, repeats, value_form, expression_form)
        for count in (6, 7, 8, 9)
        for repeats in (1, 64)
        for value_form in ("raw", "square")
        for expression_form in ("sum", "comparisons")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[2].startswith("30/"),
            abs(row[1].get("insns", 9999) - 2625),
            row[1].get("norm", 9999),
        )
    )
    for tag, result, factor, f20_rows, returncode in rows:
        print(
            tag,
            "rc",
            returncode,
            "factor",
            factor,
            "f20colors",
            len(f20_rows),
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[2].startswith("30/") for row in rows),
    )


if __name__ == "__main__":
    main()
