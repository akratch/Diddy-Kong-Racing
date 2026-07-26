#!/usr/bin/env python3
"""Extend var_f20 through real tail calls using an eventually-zero expression."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

ANCHORS = {
    "boost": (
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {\n",
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == {zero} && gNumViewports < 2) {\n",
    ),
    "computer": (
        "    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {\n",
        "    if (gCurrentPlayerIndex == PLAYER_COMPUTER + {zero}) {\n",
    ),
    "unk201": (
        "    if (racer->unk201 == 0) {\n",
        "    if (racer->unk201 == {zero}) {\n",
    ),
    "vehicle": (
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES) {\n",
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES + {zero}) {\n",
    ),
    "spa1": (
        "    if (spA1 != FALSE) {\n",
        "    if (spA1 != FALSE + {zero}) {\n",
    ),
    "camera_arg": (
        "    second_racer_camera_update(obj, racer, 1, updateRateF);\n",
        "    second_racer_camera_update(obj, racer, 1 + {zero}, updateRateF);\n",
    ),
    "moved": (
        "    if (playerObjectMoved != FALSE) {\n",
        "    if (playerObjectMoved != FALSE + {zero}) {\n",
    ),
}

VALUES = (
    "var_f20",
    "spEC",
    "obj->x_velocity",
    "obj->y_velocity",
    "obj->z_velocity",
    "racer->velocity",
    "racer->lateral_velocity",
    "racer->forwardVel",
)


def balanced(terms: list[str]) -> str:
    if len(terms) == 1:
        return terms[0]
    midpoint = len(terms) // 2
    return f"({balanced(terms[:midpoint])} + {balanced(terms[midpoint:])})"


def expression(form: str, count: int) -> str:
    values = [VALUES[index % len(VALUES)] for index in range(count)]
    if form == "compare":
        return f"(({' + '.join(f'({v} > 0.0f)' for v in values)}) * 0)"
    if form == "raw":
        return f"((({' + '.join(values)}) > 0.0f) * 0)"
    if form == "raw_balanced":
        return f"(({balanced(values)} > 0.0f) * 0)"
    squares = [f"(({value}) * ({value}))" for value in values]
    if form == "square":
        return f"((({' + '.join(squares)}) > 0.0f) * 0)"
    if form == "square_balanced":
        return f"(({balanced(squares)} > 0.0f) * 0)"
    if form == "product_zero":
        return f"((s32) ({balanced(squares)} * 0.0f))"
    if form == "self_sub":
        return f"((s32) (({balanced(values)}) - ({balanced(values)})))"
    raise ValueError(form)


def replace_last(source: str, old: str, new: str) -> str:
    if old not in source:
        raise ValueError(old)
    before, after = source.rsplit(old, 1)
    return before + new + after


def make(anchor: str, form: str, count: int) -> str:
    old, new = ANCHORS[anchor]
    return replace_last(
        BASE,
        old,
        new.replace("{zero}", expression(form, count)),
    )


def evaluate(case: tuple[str, str, int]) -> tuple:
    anchor, form, count = case
    tag = f"{anchor}_{form}_n{count}"
    source = make(*case)
    path = f"/tmp/codex_tail_call_factor_use_{tag}.c"
    trace = f"/tmp/codex_tail_call_factor_use_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_tail_call_factor_use_{tag}.o"
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_tail_call_factor_use_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    factor_row = "-"
    f20_colors = 0
    f18_colors = 0
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
                elif "RACER-COLOR bit" in line:
                    f20_colors += "reg=30 " in line
                    f18_colors += "reg=29 " in line
    return (
        tag,
        source,
        result,
        factor,
        factor_row,
        f20_colors,
        f18_colors,
        proc.returncode,
    )


def main() -> None:
    forms = (
        "compare",
        "raw",
        "raw_balanced",
        "square",
        "square_balanced",
        "product_zero",
        "self_sub",
    )
    cases = [
        (anchor, form, count)
        for anchor in ANCHORS
        for form in forms
        for count in (1, 2, 3, 4, 5, 6, 8, 10, 12)
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[3].startswith("30/"),
            row[2].get("mismatch", 999999),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
            row[0],
        )
    )
    for (
        tag,
        source,
        result,
        factor,
        factor_row,
        f20_colors,
        f18_colors,
        returncode,
    ) in rows:
        if result.get("mismatch") == 0:
            with open(
                f"/tmp/codex_tail_call_factor_use_exact_{tag}.c",
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
            "f20colors",
            f20_colors,
            "f18colors",
            f18_colors,
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
