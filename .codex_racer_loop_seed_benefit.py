#!/usr/bin/env python3
"""Raise a sixth short-lived loop range above f20's first-use threshold."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
ANCHOR = """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}
"""
VALUES = (
    "obj->x_velocity",
    "obj->y_velocity",
    "obj->z_velocity",
    "racer->velocity",
    "racer->lateral_velocity",
    "racer->forwardVel",
)
OPS = (">", "<", "!=", ">=", "<=", "==")
CONSTANTS = ("0.0f", "1.0f", "-1.0f", "2.0f", "-2.0f", "4.0f")


def seed_block(repetitions: int, layout: str) -> str:
    names = [f"loop_seed_f{index}" for index in range(6)]
    declarations = "".join(f"            f32 {name};\n" for name in names)
    assignments = ", ".join(
        f"{name} = {value}" for name, value in zip(names, VALUES)
    )
    if layout == "by_name":
        terms = [
            f"({name} {OPS[index % len(OPS)]} "
            f"{CONSTANTS[index % len(CONSTANTS)]})"
            for name in names
            for index in range(repetitions)
        ]
    else:
        terms = [
            f"({name} {OPS[index % len(OPS)]} "
            f"{CONSTANTS[index % len(CONSTANTS)]})"
            for index in range(repetitions)
            for name in names
        ]
    expression = " + ".join(terms)
    return (
        declarations
        + f"            var_a0 += ({assignments}, ({expression})) * 0;\n"
    )


def make(repetitions: int, layout: str) -> str:
    if BASE.count(ANCHOR) != 1:
        raise ValueError(BASE.count(ANCHOR))
    replacement = ANCHOR.replace(
        "var_a0--) {}\n",
        "var_a0--) {\n"
        + seed_block(repetitions, layout)
        + "        }\n",
        1,
    )
    return BASE.replace(ANCHOR, replacement, 1)


def evaluate(case: tuple[int, str]) -> tuple:
    repetitions, layout = case
    tag = f"r{repetitions}_{layout}"
    source = make(*case)
    path = f"/tmp/codex_loop_seed_benefit_{tag}.c"
    trace = f"/tmp/codex_loop_seed_benefit_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_loop_seed_benefit_{tag}.o",
    )
    subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_loop_seed_benefit_{tag}_analysis.o",
            trace,
        ],
        check=True,
        capture_output=True,
        text=True,
    )
    seed_rows = []
    colors = []
    factor = "-"
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "RACER-FVAR" in line:
                match = re.search(
                    r"addr=(-\\d+) adjsave=([0-9.]+) uses=(\\d+)", line
                )
                if match and -240 < int(match.group(1)) <= -172:
                    seed_rows.append("/".join(match.groups()))
            elif "RACER-COLOR bit" in line and "reg=30 " in line:
                colors.append(line.strip())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\\d+) cost=([0-9.]+)", line)
                if match:
                    factor = "/".join(match.groups())
    return tag, source, result, seed_rows, colors, factor


def main() -> None:
    cases = [
        (repetitions, layout)
        for repetitions in (2, 3, 4, 5, 6, 8, 10, 12, 16)
        for layout in ("by_name", "interleaved")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[5].split("/")[0] != "30",
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
        )
    )
    for tag, source, result, seeds, colors, factor in rows:
        if factor.startswith("30") or colors:
            with open(
                f"/tmp/codex_loop_seed_benefit_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "factor",
            factor,
            "seeds",
            ",".join(seeds),
            "f20colors",
            len(colors),
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[5].startswith("30") for row in rows),
        "has_f20",
        sum(bool(row[4]) for row in rows),
    )


if __name__ == "__main__":
    main()
