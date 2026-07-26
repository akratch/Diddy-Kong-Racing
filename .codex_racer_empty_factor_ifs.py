#!/usr/bin/env python3
"""Extend var_f20 with optimizer-erased empty conditions across calls."""

from __future__ import annotations

import concurrent.futures
import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
CALLS = (
    """\
        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectMoved = TRUE;
        }
""",
    """\
        racer_approach_object(obj, racer, updateRateF);
""",
    """\
            onscreen_ai_racer_physics(obj, racer, updateRate);
""",
    """\
        func_80054FD0(obj, racer, updateRate);
""",
    """\
        racer_play_sound(obj, SOUND_CRASH);
""",
)
FORMS = {
    "not": "!var_f20",
    "value": "var_f20",
    "gt0": "var_f20 > 0.0f",
    "eq0": "var_f20 == 0.0f",
    "cast": "(s32) var_f20",
    "impossible": "(var_f20 > 0.0f) && (var_f20 < 0.0f)",
}


def add_empty_if(source: str, call: str, expression: str) -> str:
    if source.count(call) == 0:
        raise ValueError(call)
    indent = re.match(r"[ \t]*", call).group(0)
    replacement = call + f"{indent}if ({expression}) {{}}\n"
    if source.count(call) == 1:
        return source.replace(call, replacement, 1)
    before, after = source.rsplit(call, 1)
    return before + replacement + after


def make(selected: tuple[int, ...], form: str) -> str:
    source = BASE
    for index in selected:
        source = add_empty_if(source, CALLS[index], FORMS[form])
    return source


def trace_metrics(trace: str) -> dict[str, str]:
    result: dict[str, str] = {}
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "FVAR " in line and "addr=-44 " in line:
                match = re.search(
                    r"adjsave=([0-9.-]+) uses=(\d+).*c14=([0-9.-]+)",
                    line,
                )
                if match:
                    result["factor"] = "/".join(match.groups())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    result["choice"] = "/".join(match.groups())
    return result


def evaluate(case: tuple[tuple[int, ...], str]) -> tuple:
    selected, form = case
    tag = f"{form}_c{''.join(map(str, selected))}"
    source = make(selected, form)
    obj = f"/tmp/codex_empty_factor_ifs_{tag}.o"
    natural = ORACLE["evaluate"](source, keep=obj)
    path = f"/tmp/codex_empty_factor_ifs_{tag}.c"
    trace = f"/tmp/codex_empty_factor_ifs_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    proc = subprocess.run(
        [ANALYSIS, path, obj + ".analysis", trace],
        check=False,
        capture_output=True,
        text=True,
    )
    metrics = trace_metrics(trace) if proc.returncode == 0 else {}
    return tag, natural, metrics


def main() -> None:
    selections = [
        selected
        for count in range(1, len(CALLS) + 1)
        for selected in itertools.combinations(range(len(CALLS)), count)
    ]
    cases = [
        (selected, form)
        for form in FORMS
        for selected in selections
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            row[1].get("sha1") != "28ae550756b5",
            -float(row[2].get("factor", "0/0/0").split("/")[-1]),
            row[1].get("norm", 9999),
        )
    )
    for tag, natural, metrics in rows:
        print(
            tag,
            metrics,
            ORACLE["concise"](natural),
            natural.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "exact-natural",
        sum(row[1].get("sha1") == "28ae550756b5" for row in rows),
        "promoted",
        sum(row[1].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
