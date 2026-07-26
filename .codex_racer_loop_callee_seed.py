#!/usr/bin/env python3
"""Seed f20 with mutually interfering, loop-weighted, short FP webs."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

ANCHORS = {
    "wheel": """\
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
""",
    "wave": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}
""",
}

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


def block(
    count: int,
    value_form: str,
    expression_form: str,
    counter: str,
) -> str:
    names = [f"loop_seed_f{index}" for index in range(count)]
    declarations = "".join(f"            f32 {name};\n" for name in names)
    assignments = []
    for index, name in enumerate(names):
        value = VALUES[index]
        rhs = value if value_form == "raw" else f"{value} * {value}"
        assignments.append(f"{name} = {rhs}")
    if expression_form == "sum":
        condition = "(" + " + ".join(names) + ") > 0.0f"
    else:
        condition = " + ".join(f"({name} > 0.0f)" for name in names)
    return (
        declarations
        + f"            {counter} += ("
        + ", ".join(assignments)
        + f", ({condition})) * 0;\n"
    )


def make(
    anchor_name: str,
    count: int,
    value_form: str,
    expression_form: str,
) -> str:
    source = BASE
    anchor = ANCHORS[anchor_name]
    if source.count(anchor) != 1:
        raise ValueError((anchor_name, source.count(anchor)))
    if anchor_name == "wheel":
        replacement = anchor.replace(
            "            if (",
            block(count, value_form, expression_form, "var_t0")
            + "            if (",
            1,
        )
    else:
        # Turn the empty wave-loop body into a block without changing the loop.
        replacement = anchor.replace(
            "var_a0--) {}\n",
            "var_a0--) {\n"
            + block(count, value_form, expression_form, "var_a0")
            + "        }\n",
            1,
        )
    return source.replace(anchor, replacement, 1)


def evaluate(case: tuple[str, int, str, str]) -> tuple:
    anchor_name, count, value_form, expression_form = case
    tag = f"{anchor_name}_n{count}_{value_form}_{expression_form}"
    source = make(*case)
    path = f"/tmp/codex_loop_callee_seed_{tag}.c"
    trace = f"/tmp/codex_loop_callee_seed_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_loop_callee_seed_{tag}.o",
    )
    subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_loop_callee_seed_{tag}_analysis.o",
            trace,
        ],
        check=True,
        capture_output=True,
        text=True,
    )
    f20_colors: list[str] = []
    factor = "-"
    first_used = "-"
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "RACER-COLOR bit" in line and "reg=30 " in line:
                f20_colors.append(line.strip())
            elif "FACTOR-COST reg=30 " in line:
                match = re.search(r"cost=([0-9.]+).*first-used=(\d+)", line)
                if match:
                    first_used = "/".join(match.groups())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.]+)", line)
                if match:
                    factor = "/".join(match.groups())
    return tag, source, result, f20_colors, first_used, factor


def main() -> None:
    cases = [
        (anchor_name, count, value_form, expression_form)
        for anchor_name in ANCHORS
        for count in (5, 6, 7)
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
    for tag, source, result, colors, first_used, factor in rows:
        if factor.startswith("30") or colors:
            with open(
                f"/tmp/codex_loop_callee_seed_promising_{tag}.c",
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
            "colors",
            len(colors),
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[5].startswith("30") for row in rows),
        "early_f20",
        sum(bool(row[3]) for row in rows),
    )


if __name__ == "__main__":
    main()
