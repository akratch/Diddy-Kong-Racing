#!/usr/bin/env python3
"""Test equivalent duplicated-call CFGs for late tail merging.

If two syntactic call blocks are merged only after global allocation, the
factor can be charged for both while emitted instructions remain canonical.
"""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
CANONICAL_SHA = "28ae550756b5"

STATEMENTS = {
    "apply": """\
    apply_vehicle_rotation_offset(racer, updateRate, 0, var_t0, 0);
""",
    "top_speed": """\
    var_f0 = handle_racer_top_speed(obj, racer);
""",
    "approach": """\
        racer_approach_object(obj, racer, updateRateF);
""",
    "ai": """\
            onscreen_ai_racer_physics(obj, racer, updateRate);
""",
    "physics": """\
        func_80054FD0(obj, racer, updateRate);
""",
    "camera": """\
    second_racer_camera_update(obj, racer, 1, updateRateF);
""",
}

CONDITIONS = {
    "stick": "gCurrentStickX != 0",
    "grounded": "racer->groundedWheels != 0",
    "player": "gCurrentPlayerIndex != PLAYER_COMPUTER",
    "target": "racer->approachTarget == NULL",
    "factor": "var_f20 > 0.0f",
    "rate": "updateRate != 0",
    "vehicle": "racer->vehicleID != VEHICLE_CARPET",
    "timer": "gRaceStartTimer != 0",
}

FORMS = {
    "if_else": """\
{indent}if ({condition}) {{
{body}{indent}}} else {{
{body}{indent}}}
""",
    "ternary": """\
{indent}{condition} ? (void) ({expression}) : (void) ({expression});
""",
}


def add_indent(text: str, spaces: int) -> str:
    prefix = " " * spaces
    return "".join(prefix + line if line.strip() else line for line in text.splitlines(True))


def as_expression(statement: str) -> str | None:
    stripped = statement.strip()
    if "\n" in stripped or not stripped.endswith(";"):
        return None
    return stripped[:-1]


def wrap(source: str, name: str, condition: str, form: str) -> str:
    statement = STATEMENTS[name]
    if source.count(statement) != 1:
        raise ValueError((name, source.count(statement)))
    indent = statement[: len(statement) - len(statement.lstrip())]
    body = add_indent(statement, 4)
    expression = as_expression(statement)
    if form == "ternary" and expression is None:
        raise ValueError((name, form))
    replacement = FORMS[form].format(
        indent=indent,
        body=body,
        condition=CONDITIONS[condition],
        expression=expression,
    )
    return source.replace(statement, replacement, 1)


def cost_from_trace(trace: str) -> tuple[float | None, str | None]:
    caller = None
    choice = None
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "FACTOR-COST reg=27 " in line:
                match = re.search(r"cost=([0-9.-]+)", line)
                if match:
                    caller = float(match.group(1))
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    choice = "/".join(match.groups())
    return caller, choice


def evaluate(case: tuple[str, str, str]) -> tuple:
    name, condition, form = case
    tag = f"{name}_{condition}_{form}"
    source = wrap(BASE, name, condition, form)
    path = f"/tmp/codex_duplicate_call_{tag}.c"
    trace = f"/tmp/codex_duplicate_call_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](source, keep=f"/tmp/codex_duplicate_call_{tag}.o")
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_duplicate_call_{tag}_analysis.o", trace],
        check=False,
        capture_output=True,
        text=True,
    )
    cost = cost_from_trace(trace) if proc.returncode == 0 else (None, None)
    exact = natural.get("sha1") == CANONICAL_SHA
    return tag, source, natural, cost, exact, proc.returncode


def main() -> None:
    cases = []
    for name, statement in STATEMENTS.items():
        forms = ("if_else",)
        if as_expression(statement) is not None:
            forms += ("ternary",)
        cases.extend(
            (name, condition, form)
            for condition in CONDITIONS
            for form in forms
        )
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[4],
            -(row[3][0] or -1),
            row[2].get("f20_operands", 0) == 0,
            row[2].get("norm", 9999),
        )
    )
    for tag, source, natural, cost, exact, returncode in rows:
        if exact and cost[0] != 21.0:
            with open(
                f"/tmp/codex_duplicate_call_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
            "exact",
            exact,
            "cost",
            cost,
            ORACLE["concise"](natural),
            natural.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "exact",
        sum(row[4] for row in rows),
        "exact_cost_changed",
        sum(row[4] and row[3][0] != 21.0 for row in rows),
        "promoted",
        sum(row[2].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
