#!/usr/bin/env python3
"""Create instruction-erased FP pressure at var_f20's final basic block.

The final var_f20 use and several required zero stores share one straight-line
block.  IDO retains some compare-to-zero expression ranges for allocation even
when multiplication by zero erases their machine instructions.  Build trees
there to forbid caller-saved FP colors without adding a persistent FP local.
"""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

DESTINATIONS = {
    "rotation_z": (
        "    gCurrentRacerTransform.rotation.z_rotation = 0;\n",
        "    gCurrentRacerTransform.rotation.z_rotation = {zero};\n",
    ),
    "position_x": (
        "    gCurrentRacerTransform.x_position = 0.0f;\n",
        "    gCurrentRacerTransform.x_position = (f32) {zero};\n",
    ),
    "position_y": (
        "    gCurrentRacerTransform.y_position = 0.0f;\n",
        "    gCurrentRacerTransform.y_position = (f32) {zero};\n",
    ),
    "position_z": (
        "    gCurrentRacerTransform.z_position = 0.0f;\n",
        "    gCurrentRacerTransform.z_position = (f32) {zero};\n",
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
    "spD4",
    "spD0",
    "spD8",
    "updateRateF",
)


def balanced(terms: list[str]) -> str:
    if len(terms) == 1:
        return terms[0]
    midpoint = len(terms) // 2
    return f"({balanced(terms[:midpoint])} + {balanced(terms[midpoint:])})"


def expression(form: str, count: int, offset: int = 0) -> str:
    values = [VALUES[(offset + index) % len(VALUES)] for index in range(count)]
    comparisons = [f"({value} > 0.0f)" for value in values]
    if form == "compare_left":
        tree = " + ".join(comparisons)
        return f"(({tree}) * 0)"
    if form == "compare_balanced":
        return f"({balanced(comparisons)} * 0)"
    if form == "raw_left":
        tree = " + ".join(f"({value})" for value in values)
        return f"((({tree}) > 0.0f) * 0)"
    if form == "raw_balanced":
        tree = balanced([f"({value})" for value in values])
        return f"((({tree}) > 0.0f) * 0)"
    if form == "square_left":
        tree = " + ".join(f"(({value}) * ({value}))" for value in values)
        return f"((({tree}) > 0.0f) * 0)"
    if form == "square_balanced":
        tree = balanced([f"(({value}) * ({value}))" for value in values])
        return f"((({tree}) > 0.0f) * 0)"
    if form == "compare_and_zero":
        tree = " + ".join(comparisons)
        return f"(({tree}) & 0)"
    if form == "compare_ternary":
        tree = " + ".join(comparisons)
        return f"(({tree}) ? 0 : 0)"
    raise ValueError(form)


def make(
    destination_names: tuple[str, ...],
    form: str,
    count: int,
) -> str:
    source = BASE
    for index, name in enumerate(destination_names):
        old, new = DESTINATIONS[name]
        if source.count(old) < 1:
            raise ValueError((name, source.count(old)))
        zero = expression(form, count, index)
        before, after = source.rsplit(old, 1)
        source = before + new.replace("{zero}", zero) + after
    return source


def evaluate(case: tuple[tuple[str, ...], str, int]) -> tuple:
    destinations, form, count = case
    tag = f"{'-'.join(destinations)}_{form}_n{count}"
    source = make(*case)
    path = f"/tmp/codex_tail_zero_pressure_{tag}.c"
    trace = f"/tmp/codex_tail_zero_pressure_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_tail_zero_pressure_{tag}.o"
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_tail_zero_pressure_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    factor_row = "-"
    f20_colors = 0
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
                    match = re.search(
                        r"reg=(\d+) cost=([0-9.-]+).*", line
                    )
                    if match:
                        factor = "/".join(match.groups())
                elif "RACER-COLOR bit" in line and "reg=30 " in line:
                    f20_colors += 1
    return (
        tag,
        source,
        result,
        factor,
        factor_row,
        f20_colors,
        proc.returncode,
    )


def main() -> None:
    forms = (
        "compare_left",
        "compare_balanced",
        "raw_left",
        "raw_balanced",
        "square_left",
        "square_balanced",
        "compare_and_zero",
        "compare_ternary",
    )
    destination_sets = [
        (name,) for name in DESTINATIONS
    ] + [
        ("rotation_z", "position_x"),
        ("rotation_z", "position_x", "position_y"),
        tuple(DESTINATIONS),
    ]
    cases = [
        (destinations, form, count)
        for destinations in destination_sets
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
        returncode,
    ) in rows:
        if result.get("mismatch") == 0:
            with open(
                f"/tmp/codex_tail_zero_pressure_exact_{tag}.c",
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
