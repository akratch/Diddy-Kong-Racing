#!/usr/bin/env python3
"""Prepay f20 with Qdt webs in the real loop before factor definition."""

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


def zero_expression(names: list[str], form: str) -> str:
    if form == "sum":
        return "((" + " + ".join(names) + ") > 0.0) * 0"
    if form == "compare":
        return "(" + " + ".join(f"({name} > 0.0)" for name in names) + ") * 0"
    raise ValueError(form)


def make(
    count: int,
    value_form: str,
    zero_form: str,
    scope: str,
    use_shape: str,
) -> str:
    names = [f"wave_q{index}" for index in range(count)]
    block_declarations = "".join(f"            f64 {name};\n" for name in names)
    function_declarations = "".join(f"    f64 {name};\n" for name in names)
    if value_form == "index":
        value = "(f64) var_a0"
    elif value_form == "height":
        value = "(f64) gRacerCurrentWave[var_a0]->waveHeight"
    elif value_form == "position":
        value = "(f64) obj->trans.y_position"
    else:
        raise ValueError(value_form)
    definitions = "".join(f"            {name} = {value};\n" for name in names)
    zero = zero_expression(names, zero_form)
    if use_shape == "single":
        uses = f"            var_a0 += {zero};\n"
    elif use_shape == "branch":
        uses = (
            f"            var_a0 += {zero};\n"
            "            if (var_a0 != 0) {\n"
            f"                var_a0 += {zero};\n"
            "            } else {\n"
            f"                var_a0 -= {zero};\n"
            "            }\n"
            f"            var_a0 += {zero};\n"
        )
    elif use_shape == "nested":
        uses = (
            f"            var_a0 += {zero};\n"
            "            if (var_a0 != 0) {\n"
            "                if (gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position) {\n"
            f"                    var_a0 += {zero};\n"
            "                } else {\n"
            f"                    var_a0 -= {zero};\n"
            "                }\n"
            "            } else {\n"
            f"                var_a0 += {zero};\n"
            "            }\n"
            f"            var_a0 += {zero};\n"
        )
    else:
        raise ValueError(use_shape)
    body = (
        "        {\n"
        + (block_declarations if scope == "loop_block" else "")
        + definitions
        + uses
        + "        }\n"
    )
    replacement = ANCHOR[:-3] + body
    source = BASE
    if scope == "function":
        source = source.replace(
            "    Object_Boost *boostObj;\n",
            "    Object_Boost *boostObj;\n" + function_declarations,
            1,
        )
    if source.count(ANCHOR) != 1:
        raise ValueError(source.count(ANCHOR))
    return source.replace(ANCHOR, replacement, 1)


def evaluate(case: tuple[int, str, str, str, str]) -> tuple:
    count, value_form, zero_form, scope, use_shape = case
    tag = f"n{count}_{value_form}_{zero_form}_{scope}_{use_shape}"
    source = make(*case)
    path = f"/tmp/codex_wave_loop_qdt_prepay_{tag}.c"
    trace = f"/tmp/codex_wave_loop_qdt_prepay_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_wave_loop_qdt_prepay_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_wave_loop_qdt_prepay_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    factor_forbidden = "-"
    qdt_colors: list[tuple[int, int, float, int]] = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
                elif "FACTOR-DUMP phase=before-cost" in line:
                    match = re.search(r"forbidden=([0-9a-f:]+)", line)
                    if match:
                        factor_forbidden = match.group(1)
                elif "RACER-COLOR " in line and " size=8" in line:
                    match = re.search(
                        r"bit=(\d+).*reg=(\d+).*adjsave=([0-9.-]+).*uses=(\d+)",
                        line,
                    )
                    if match:
                        qdt_colors.append(
                            (
                                int(match.group(1)),
                                int(match.group(2)),
                                float(match.group(3)),
                                int(match.group(4)),
                            )
                        )
    return (
        tag,
        source,
        result,
        factor,
        factor_forbidden,
        qdt_colors,
        proc.returncode,
    )


def main() -> None:
    cases = [
        (count, value_form, zero_form, scope, use_shape)
        for count in range(5, 9)
        for value_form in ("height",)
        for zero_form in ("sum", "compare")
        for scope in ("function", "loop_block")
        for use_shape in ("branch", "nested")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[3].startswith("30/"),
            not any(reg == 30 for _, reg, _, _ in row[5]),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, factor, forbidden, colors, returncode in rows:
        if factor.startswith("30/") and any(reg == 30 for _, reg, _, _ in colors):
            with open(
                f"/tmp/codex_wave_loop_qdt_prepay_promising_{tag}.c",
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
            "forb",
            forbidden,
            "qdt",
            ",".join(
                f"{bit}/{reg}/{save:g}/{uses}"
                for bit, reg, save, uses in colors
            )
            or "-",
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_f20",
        sum(row[3].startswith("30/") for row in rows),
        "qdt_f20",
        sum(any(reg == 30 for _, reg, _, _ in row[5]) for row in rows),
        "prepaid",
        sum(
            row[3].startswith("30/")
            and any(reg == 30 for _, reg, _, _ in row[5])
            for row in rows
        ),
    )


if __name__ == "__main__":
    main()
