#!/usr/bin/env python3
"""Join the incoming and real var_f20 webs via an erased true branch."""

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
PREUSES = {
    "steer": (
        "    gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;\n",
        "    gCurrentCarSteerVel = (var_f20 > 0.0f) * 0;\n",
    ),
    "d550": (
        "    D_8011D550 = 0;\n",
        "    D_8011D550 = (var_f20 > 0.0f) * 0;\n",
    ),
    "d558": (
        "    D_8011D558 = 0;\n",
        "    D_8011D558 = (var_f20 > 0.0f) * 0;\n",
    ),
}
CONDITIONS = {
    "obj_self": "obj == obj",
    "racer_self": "racer == racer",
    "player_self": "gCurrentPlayerIndex == gCurrentPlayerIndex",
    "timer_self": "gRaceStartTimer == gRaceStartTimer",
    "obj_tautology": "(obj == NULL) || (obj != NULL)",
    "player_tautology": (
        "(gCurrentPlayerIndex == 0) || (gCurrentPlayerIndex != 0)"
    ),
    "timer_tautology": "(gRaceStartTimer < 0) || (gRaceStartTimer >= 0)",
    "factor_or_one": "(var_f20 > 0.0f) || 1",
    "factor_zero": "((var_f20 > 0.0f) * 0) == 0",
    "assigned_one": "(var_t9 = 1)",
    "address": "&gCurrentPlayerIndex != NULL",
}


def make(preuse: str, condition_name: str, form: str) -> str:
    source = BASE
    old, new = PREUSES[preuse]
    condition = CONDITIONS[condition_name]
    if source.count(old) != 1 or source.count(INITIAL) != 1:
        raise ValueError(
            (preuse, source.count(old), source.count(INITIAL))
        )
    source = source.replace(old, new, 1)
    body = "".join(
        "    " + line if line.strip() else line
        for line in INITIAL.splitlines(True)
    )
    if form == "if":
        replacement = f"    if ({condition}) {{\n{body}    }}\n"
    elif form == "if_else_empty":
        replacement = (
            f"    if ({condition}) {{\n{body}    }} else {{\n    }}\n"
        )
    elif form == "if_else_self":
        replacement = (
            f"    if ({condition}) {{\n{body}    }} else {{\n"
            "        var_f20 = var_f20;\n"
            "    }\n"
        )
    else:
        raise ValueError(form)
    return source.replace(INITIAL, replacement, 1)


def evaluate(case: tuple[str, str, str]) -> tuple:
    preuse, condition_name, form = case
    tag = f"{preuse}_{condition_name}_{form}"
    source = make(*case)
    path = f"/tmp/codex_first_def_condition_{tag}.c"
    trace = f"/tmp/codex_first_def_condition_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_first_def_condition_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_first_def_condition_{tag}_analysis.o",
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
    cases = [
        (preuse, condition_name, form)
        for preuse in PREUSES
        for condition_name in CONDITIONS
        for form in ("if", "if_else_empty", "if_else_self")
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
                f"/tmp/codex_first_def_condition_exact_{tag}.c",
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
