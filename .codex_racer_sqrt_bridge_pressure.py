#!/usr/bin/env python3
"""Keep sqrt input subexpressions notionally live into the factor web."""

from __future__ import annotations

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
OLD = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
    if (racer->vehicleID >= VEHICLE_BOSSES) {
"""

HOST_SETS = (
    ("spCC", "var_f6", "segmentXVelocity", "var_f0", "var_f2"),
    ("spCC", "var_f6", "segmentXVelocity", "spD4", "spD0"),
    ("spCC", "var_f6", "segmentXVelocity", "spD8", "var_f14"),
    ("press0", "press1", "press2", "press3", "press4"),
)


def prelude(hosts: tuple[str, ...], topology: str) -> tuple[str, tuple[str, ...]]:
    a, b, c, d, e = hosts
    x = "obj->x_velocity"
    z = "obj->z_velocity"
    y = "obj->y_velocity"
    if topology == "inputs3":
        return (
            f"    {a} = {x};\n"
            f"    {b} = {z};\n"
            f"    {c} = {y};\n"
            f"    var_f20 = sqrtf(({a} * {a}) + ({b} * {b}) + ({c} * {c})) - 2.0;\n",
            (a, b, c),
        )
    if topology == "squares3":
        return (
            f"    {a} = {x} * {x};\n"
            f"    {b} = {z} * {z};\n"
            f"    {c} = {y} * {y};\n"
            f"    var_f20 = sqrtf({a} + {b} + {c}) - 2.0;\n",
            (a, b, c),
        )
    if topology == "squares_sum1":
        return (
            f"    {a} = {x} * {x};\n"
            f"    {b} = {z} * {z};\n"
            f"    {c} = {y} * {y};\n"
            f"    {d} = {a} + {b};\n"
            f"    var_f20 = sqrtf({d} + {c}) - 2.0;\n",
            (a, b, c, d),
        )
    if topology == "squares_sum2":
        return (
            f"    {a} = {x} * {x};\n"
            f"    {b} = {z} * {z};\n"
            f"    {c} = {y} * {y};\n"
            f"    {d} = {a} + {b};\n"
            f"    {e} = {d} + {c};\n"
            f"    var_f20 = sqrtf({e}) - 2.0;\n",
            (a, b, c, d, e),
        )
    if topology == "inputs_sums":
        return (
            f"    {a} = {x};\n"
            f"    {b} = {z};\n"
            f"    {c} = {y};\n"
            f"    {d} = ({a} * {a}) + ({b} * {b});\n"
            f"    {e} = {d} + ({c} * {c});\n"
            f"    var_f20 = sqrtf({e}) - 2.0;\n",
            (a, b, c, d, e),
        )
    raise ValueError(topology)


def fake(values: tuple[str, ...], form: str) -> str:
    comparisons = [f"({value} > 0.0f)" for value in values]
    if form == "sum_cmp":
        return f"    spA3 = ({' + '.join(comparisons)}) * 0;\n"
    if form == "sum_value":
        return f"    spA3 = (({' + '.join(values)}) > 0.0f) * 0;\n"
    if form == "comma":
        return f"    spA3 = ({', '.join(comparisons)}, 0);\n"
    if form == "empty":
        return "".join(f"    if ({comparison}) {{}}\n" for comparison in comparisons)
    if form == "factor_zero":
        return f"    var_f20 += (f32) (({' + '.join(comparisons)}) * 0);\n"
    raise ValueError(form)


def make(hosts: tuple[str, ...], topology: str, form: str, scope: str) -> str:
    code, values = prelude(hosts, topology)
    declaration = ""
    close = ""
    source = BASE
    if scope == "block":
        declaration = (
            "    {\n"
            + "".join(f"        f32 {value};\n" for value in hosts)
        )
        code = "".join("    " + line for line in code.splitlines(True))
        close = "    }\n"
    elif scope == "function":
        source = source.replace(
            "    f32 segmentXVelocity;\n",
            "    f32 segmentXVelocity;\n"
            + "".join(f"    f32 {value};\n" for value in hosts),
            1,
        )
    elif scope != "existing":
        raise ValueError(scope)
    replacement = declaration + code + fake(values, form)
    if form == "empty":
        replacement += "    spA3 = FALSE;\n"
    replacement += close + "    if (racer->vehicleID >= VEHICLE_BOSSES) {\n"
    if source.count(OLD) != 1:
        raise ValueError("sqrt block not unique")
    return source.replace(OLD, replacement, 1)


def trace_metrics(path: pathlib.Path) -> str:
    rows = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if "FACTOR-CHOICE" in line or "RACER-COLOR bit=284 " in line:
            rows.append(line.strip())
    return " | ".join(rows)


def main() -> None:
    existing_cases = list(
        itertools.product(
            range(len(HOST_SETS) - 1),
            ("inputs3", "squares3", "squares_sum1", "squares_sum2", "inputs_sums"),
            ("sum_cmp", "sum_value", "comma", "empty", "factor_zero"),
            ("existing",),
        )
    )
    fresh_cases = list(
        itertools.product(
            (len(HOST_SETS) - 1,),
            ("inputs3", "squares3", "squares_sum1", "squares_sum2", "inputs_sums"),
            ("sum_cmp", "sum_value", "comma", "empty", "factor_zero"),
            ("block", "function"),
        )
    )
    cases = existing_cases + fresh_cases
    for serial, (host_index, topology, form, scope) in enumerate(cases):
        tag = f"{serial:03d}_h{host_index}_{topology}_{form}_{scope}"
        source = make(HOST_SETS[host_index], topology, form, scope)
        path = pathlib.Path(f"/tmp/codex_sqrt_bridge_{tag}.c")
        obj = path.with_suffix(".o")
        trace = path.with_suffix(".trace")
        path.write_text(source, encoding="utf-8")
        natural = ORACLE["evaluate"](source, keep=str(obj))
        metrics = ""
        if natural.get("f20_operands", 0) > 0:
            proc = subprocess.run(
                [ANALYSIS, str(path), str(path.with_name(path.stem + "_analysis.o")), str(trace)],
                check=False,
                capture_output=True,
                text=True,
            )
            if proc.returncode == 0:
                metrics = trace_metrics(trace)
        print(
            tag,
            ORACLE["concise"](natural),
            natural.get("fp"),
            metrics,
            path,
        )


if __name__ == "__main__":
    main()
