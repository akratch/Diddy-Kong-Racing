#!/usr/bin/env python3
"""Seed f20 with block-scoped FP webs erased by an integer-zero expression."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
ANCHOR = "    D_8011D558 = 0;\n"

VALUES = (
    "obj->x_velocity",
    "obj->y_velocity",
    "obj->z_velocity",
    "racer->velocity",
    "racer->lateral_velocity",
    "racer->forwardVel",
    "racer->ox1",
    "racer->oy1",
)


def make(count: int, repeats: int, value_form: str, expression_form: str) -> str:
    names = [f"seed_f{index}" for index in range(count)]
    declarations = "".join(f"        f32 {name};\n" for name in names)
    assignments = []
    for index, name in enumerate(names):
        value = VALUES[index]
        if value_form == "raw":
            rhs = value
        elif value_form == "square":
            rhs = f"{value} * {value}"
        else:
            raise ValueError(value_form)
        assignments.append(f"{name} = {rhs}")

    terms = [name for name in names for _ in range(repeats)]
    if expression_form == "sum":
        condition = "(" + " + ".join(terms) + ") > 0.0f"
    elif expression_form == "comparisons":
        condition = " + ".join(f"({term} > 0.0f)" for term in terms)
    else:
        raise ValueError(expression_form)

    replacement = (
        "    {\n"
        + declarations
        + "        D_8011D558 = ("
        + ", ".join(assignments)
        + f", ({condition})) * 0;\n"
        + "    }\n"
    )
    if BASE.count(ANCHOR) != 1:
        raise ValueError("D_8011D558 zero anchor is not unique")
    return BASE.replace(ANCHOR, replacement, 1)


def evaluate(case: tuple[int, int, str, str]) -> tuple:
    count, repeats, value_form, expression_form = case
    tag = f"n{count}_r{repeats}_{value_form}_{expression_form}"
    source = make(*case)
    path = f"/tmp/codex_callee_seed_{tag}.c"
    trace = f"/tmp/codex_callee_seed_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_callee_seed_{tag}.o",
    )
    subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_callee_seed_{tag}_analysis.o",
            trace,
        ],
        check=True,
        capture_output=True,
        text=True,
    )
    seed_colors: list[str] = []
    factor = "-"
    first_used = "-"
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "RACER-COLOR bit" in line and "reg=30 " in line:
                match = re.search(
                    r"bit=(\d+).*adjsave=([0-9.]+) uses=(\d+).*"
                    r"(?:addr=(-?\d+)|opc=(....))",
                    line,
                )
                seed_colors.append(
                    "/".join(part or "-" for part in match.groups())
                    if match
                    else line.strip()
                )
            elif "FACTOR-COST reg=30 " in line:
                match = re.search(r"cost=([0-9.]+).*first-used=(\d+)", line)
                if match:
                    first_used = "/".join(match.groups())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.]+)", line)
                if match:
                    factor = "/".join(match.groups())
    return tag, source, result, seed_colors, first_used, factor


def main() -> None:
    cases = [
        (count, repeats, value_form, expression_form)
        for count in (5, 6, 7, 8)
        for repeats in (1, 4, 8, 16, 32, 64)
        for value_form in ("raw", "square")
        for expression_form in ("sum", "comparisons")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[5].split("/")[0] != "30",
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, seeds, first_used, factor in rows:
        if factor.startswith("30") or seeds:
            with open(
                f"/tmp/codex_callee_seed_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "factor",
            factor,
            "f20cost",
            first_used,
            "seeds",
            ",".join(seeds) or "-",
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[5].startswith("30") for row in rows),
    )


if __name__ == "__main__":
    main()
