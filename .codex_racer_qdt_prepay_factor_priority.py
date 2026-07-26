#!/usr/bin/env python3
"""Combine pre-factor f20 prepayment with weighted factor priority."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = (
    "/tmp/codex_wave_loop_qdt_prepay_"
    "n6_height_sum_loop_block_nested.c"
)
BASE = open(BASE_PATH, encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
ANCHOR = """\
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
        }
"""


def zero_expression(form: str) -> str:
    if form == "compare":
        return "(var_f20 > 0.0f) * 0"
    if form == "square":
        return "((var_f20 * var_f20) > 0.0f) * 0"
    if form == "self_sub":
        return "(s32) (var_f20 - var_f20)"
    if form == "product_zero":
        return "(s32) (var_f20 * 0.0f)"
    if form == "mixed":
        return (
            "(((var_f20 * var_f20) + (racer->velocity * racer->velocity)) "
            "> 0.0f) * 0"
        )
    raise ValueError(form)


def make(form: str, repeat: int, use_shape: str) -> str:
    mutations = {
        "mut_add": "var_f20 += 0.0f;",
        "mut_mul": "var_f20 *= 1.0f;",
        "mut_negneg": "var_f20 = -(-var_f20);",
        "mut_double": "var_f20 = (f32) ((f64) var_f20);",
    }
    is_mutation = form in mutations
    zero = "0" if is_mutation else zero_expression(form)
    repeated = "".join(
        (
            f"            {mutations[form]}\n"
            if is_mutation
            else f"            i += {zero};\n"
        )
        for _ in range(repeat)
    )
    branch_extra = (
        f"                {mutations[form]}\n"
        if is_mutation
        else f"                i += {zero};\n"
    )
    old_body = """\
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
"""
    if use_shape == "before":
        new_body = repeated + old_body
    elif use_shape == "both":
        new_body = repeated + old_body + repeated
    elif use_shape == "branch":
        new_body = (
            repeated
            + "            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && "
            "i < racer->wheel_surfaces[var_t0]) {\n"
            + f"                i = racer->wheel_surfaces[var_t0] + {zero};\n"
            + (branch_extra if is_mutation else "")
            + "            } else {\n"
            + branch_extra
            + "            }\n"
            + repeated
        )
    elif use_shape == "nested":
        new_body = (
            repeated
            + "            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE) {\n"
            + "                if (i < racer->wheel_surfaces[var_t0]) {\n"
            + f"                    i = racer->wheel_surfaces[var_t0] + {zero};\n"
            + (branch_extra if is_mutation else "")
            + "                } else {\n"
            + branch_extra.replace("                ", "                    ", 1)
            + "                }\n"
            + "            } else {\n"
            + (
                branch_extra
                if is_mutation
                else f"                i -= {zero};\n"
            )
            + "            }\n"
            + repeated
        )
    else:
        raise ValueError(use_shape)
    if BASE.count(ANCHOR) != 1:
        raise ValueError(BASE.count(ANCHOR))
    return BASE.replace(ANCHOR, ANCHOR.replace(old_body, new_body), 1)


def evaluate(case: tuple[str, int, str]) -> tuple:
    form, repeat, use_shape = case
    tag = f"{form}_r{repeat}_{use_shape}"
    source = make(*case)
    path = f"/tmp/codex_qdt_prepay_factor_priority_{tag}.c"
    trace = f"/tmp/codex_qdt_prepay_factor_priority_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_qdt_prepay_factor_priority_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_qdt_prepay_factor_priority_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    factor_row = "-"
    qdt_regs: list[int] = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "RACER-FVAR" in line and "addr=-44 " in line:
                    match = re.search(
                        r"adjsave=([0-9.-]+) uses=(\d+).*c14=([0-9.-]+)",
                        line,
                    )
                    if match:
                        factor_row = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
                elif "RACER-COLOR " in line and " size=8" in line:
                    match = re.search(r"reg=(\d+)", line)
                    if match:
                        qdt_regs.append(int(match.group(1)))
    return tag, source, result, factor, factor_row, qdt_regs, proc.returncode


def main() -> None:
    cases = [
        (form, repeat, use_shape)
        for form in (
            "compare",
            "square",
            "self_sub",
            "product_zero",
            "mixed",
            "mut_add",
            "mut_mul",
            "mut_negneg",
            "mut_double",
        )
        for repeat in (1, 2, 4, 8, 16)
        for use_shape in ("before", "both", "branch", "nested")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[3].startswith("30/"),
            abs(row[2].get("insns", 9999) - 2625),
            abs(row[2].get("f18", 0) - 190),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, factor, factor_row, qdt_regs, returncode in rows:
        if factor.startswith("30/"):
            with open(
                f"/tmp/codex_qdt_prepay_factor_priority_promising_{tag}.c",
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
            "qdt",
            ",".join(map(str, qdt_regs)) or "-",
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_f20",
        sum(row[3].startswith("30/") for row in rows),
    )


if __name__ == "__main__":
    main()
