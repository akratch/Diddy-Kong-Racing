#!/usr/bin/env python3
"""Join an erased pre-factor read to var_f20's first real definition."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
INITIAL = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
EXPRESSION = """\
sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0"""
PREUSES = {
    "steer": (
        "    gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;\n",
        "    gCurrentCarSteerVel = {zero};\n",
    ),
    "d550": (
        "    D_8011D550 = 0;\n",
        "    D_8011D550 = {zero};\n",
    ),
    "d558": (
        "    D_8011D558 = 0;\n",
        "    D_8011D558 = {zero};\n",
    ),
}
ZERO_TEMPLATES = {
    "gt_mul": "(var_f20 > 0.0f) * 0",
    "lt_mul": "(var_f20 < 0.0f) * 0",
    "eq_mul": "(var_f20 == 0.0f) * 0",
    "ne_mul": "(var_f20 != 0.0f) * 0",
    "gt_and": "(var_f20 > 0.0f) & 0",
    "comma": "(var_f20 > 0.0f, 0)",
    "ternary": "(var_f20 > 0.0f) ? 0 : 0",
}


def definition(form: str, zero: str) -> str:
    expression = EXPRESSION
    if form == "add_after":
        rhs = f"({expression}) + {zero}"
    elif form == "add_before":
        rhs = f"{zero} + ({expression})"
    elif form == "comma":
        rhs = f"(var_f20, ({expression}))"
    elif form == "comma_zero":
        rhs = f"({zero}, ({expression}))"
    elif form == "ternary":
        rhs = f"(var_f20 > 0.0f) ? ({expression}) : ({expression})"
    elif form == "mul_one":
        rhs = f"({expression}) * (1.0f + {zero})"
    elif form == "self_comma":
        rhs = f"(var_f20 = var_f20, ({expression}))"
    else:
        raise ValueError(form)
    return f"    var_f20 = {rhs};\n"


def make(preuse: str, zero_name: str, form: str) -> str:
    source = BASE
    old, new = PREUSES[preuse]
    zero = ZERO_TEMPLATES[zero_name]
    if (
        source.count(old) != 1
        or source.count(INITIAL) != 1
    ):
        raise ValueError(
            (preuse, source.count(old), source.count(INITIAL))
        )
    source = source.replace(old, new.replace("{zero}", zero), 1)
    return source.replace(INITIAL, definition(form, zero), 1)


def evaluate(case: tuple[str, str, str]) -> tuple:
    preuse, zero_name, form = case
    tag = f"{preuse}_{zero_name}_{form}"
    source = make(*case)
    path = f"/tmp/codex_initial_factor_chain_{tag}.c"
    trace = f"/tmp/codex_initial_factor_chain_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_initial_factor_chain_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_initial_factor_chain_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    factor_row = "-"
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "RACER-FVAR" in line and "addr=-44 " in line:
                    match = re.search(
                        r"adjsave=([0-9.-]+) uses=(\d+).*"
                        r"c14=([0-9.-]+)",
                        line,
                    )
                    if match:
                        factor_row = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
    return tag, source, result, factor, factor_row, proc.returncode


def main() -> None:
    forms = (
        "add_after",
        "add_before",
        "comma",
        "comma_zero",
        "ternary",
        "mul_one",
        "self_comma",
    )
    cases = [
        (preuse, zero_name, form)
        for preuse in PREUSES
        for zero_name in ZERO_TEMPLATES
        for form in forms
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[2].get("mismatch", 999999),
            not row[3].startswith("30/"),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, factor, factor_row, returncode in rows:
        if result.get("mismatch") == 0:
            with open(
                f"/tmp/codex_initial_factor_chain_exact_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
            "factor",
            factor,
            "row",
            factor_row,
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].startswith("30/") for row in rows),
        "exact",
        sum(row[2].get("mismatch") == 0 for row in rows),
    )


if __name__ == "__main__":
    main()
