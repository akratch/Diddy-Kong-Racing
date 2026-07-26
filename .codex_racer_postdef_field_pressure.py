#!/usr/bin/env python3
"""Extend existing FP field-load webs across var_f20's first definition."""

from __future__ import annotations

import concurrent.futures
import itertools
import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
ANCHOR = """\
    if (var_f20 > 4.0) {
        var_f20 = 4;
    }
    spA3 = FALSE;
"""
PREFIX = """\
    if (var_f20 > 4.0) {
        var_f20 = 4;
    }
"""

CORE_FIELDS = (
    "obj->x_velocity",
    "obj->z_velocity",
    "obj->y_velocity",
)
EXTRA_FIELDS = (
    "racer->velocity",
    "racer->lateral_velocity",
    "racer->forwardVel",
    "racer->ox1",
    "racer->oy1",
    "racer->oz1",
    "racer->ox2",
    "racer->oy2",
    "racer->oz2",
    "racer->ox3",
    "racer->oy3",
    "racer->oz3",
    "racer->unk34",
    "racer->buoyancy",
)


def zero_expression(fields: tuple[str, ...], form: str) -> str:
    comparisons = [f"({field} > 0.0f)" for field in fields]
    if form == "sum_cmp":
        return f"({' + '.join(comparisons)}) * 0"
    if form == "mul_cmp":
        return f"({' * '.join(comparisons)}) * 0"
    if form == "sum_value_cmp":
        return f"(({' + '.join(fields)}) > 0.0f) * 0"
    if form == "comma_cmp":
        return f"({', '.join(comparisons)}, 0)"
    if form == "and_zero":
        return f"(({' + '.join(comparisons)}) & 0)"
    raise ValueError(form)


def make(fields: tuple[str, ...], form: str, sink: str) -> str:
    if BASE.count(ANCHOR) != 1:
        raise ValueError("post-definition anchor not unique")
    zero = zero_expression(fields, form)
    if sink == "spa3":
        replacement = PREFIX + f"    spA3 = {zero};\n"
    elif sink == "empty_if":
        replacement = PREFIX + f"    if ({zero}) {{}}\n    spA3 = FALSE;\n"
    elif sink == "self_add":
        replacement = (
            PREFIX
            + f"    var_f20 += (f32) {zero};\n"
            + "    spA3 = FALSE;\n"
        )
    else:
        raise ValueError(sink)
    return BASE.replace(ANCHOR, replacement, 1)


def trace_metrics(path: pathlib.Path) -> dict[str, str]:
    result: dict[str, str] = {}
    with path.open(encoding="utf-8", errors="replace") as input_file:
        for line in input_file:
            if "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    result["choice"] = "/".join(match.groups())
            elif "RACER-COLOR bit=284 " in line:
                match = re.search(
                    r"forb=([0-9a-f:]+).*adjsave=([0-9.-]+).*uses=(\d+)",
                    line,
                )
                if match:
                    result["factor"] = "/".join(match.groups())
    return result


def evaluate(case: tuple[tuple[str, ...], str, str, int]) -> tuple:
    fields, form, sink, serial = case
    tag = f"{serial:04d}_{form}_{sink}"
    source = make(fields, form, sink)
    path = pathlib.Path(f"/tmp/codex_postdef_field_{tag}.c")
    obj = path.with_suffix(".o")
    trace = path.with_suffix(".trace")
    path.write_text(source, encoding="utf-8")
    natural = ORACLE["evaluate"](source, keep=str(obj))
    metrics: dict[str, str] = {}
    if natural.get("f20_operands", 0) > 0 or serial < 12:
        proc = subprocess.run(
            [ANALYSIS, str(path), str(path.with_name(path.stem + "_analysis.o")), str(trace)],
            check=False,
            capture_output=True,
            text=True,
        )
        if proc.returncode == 0:
            metrics = trace_metrics(trace)
    return tag, fields, form, sink, natural, metrics, path


def cases() -> list[tuple[tuple[str, ...], str, str, int]]:
    field_sets: list[tuple[str, ...]] = []
    for count in range(0, 3):
        for extras in itertools.combinations(EXTRA_FIELDS, count):
            field_sets.append(CORE_FIELDS + extras)
    raw = [
        (fields, form, sink)
        for fields in field_sets
        for form in ("sum_cmp", "mul_cmp", "sum_value_cmp", "comma_cmp", "and_zero")
        for sink in ("spa3", "empty_if", "self_add")
    ]
    return [(*case, serial) for serial, case in enumerate(raw)]


def main() -> None:
    work = cases()
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, work))
    rows.sort(
        key=lambda row: (
            row[4].get("f20_operands", 0) == 0,
            abs(row[4].get("insns", 9999) - 2625),
            abs(row[4].get("f18", 0) - 190),
            row[4].get("norm", 9999),
        )
    )
    for tag, fields, form, sink, natural, metrics, path in rows:
        if natural.get("f20_operands", 0) > 0 or metrics:
            print(
                tag,
                "fields",
                ",".join(fields),
                "metrics",
                metrics,
                ORACLE["concise"](natural),
                natural.get("fp"),
                path,
            )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[4].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
