#!/usr/bin/env python3
"""Carry the late var_f20 value through calls with coalescible float copies."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
START = """\
        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&
"""
UNK = """\
    if (racer->unk1D2 != 0) {
"""
ASSIGN = """\
        var_f20 = obj->x_velocity;
"""


def make(host: str, form: str) -> str:
    source = BASE
    start = START
    if form in ("replace_arg", "source_host", "self_chain"):
        start = start.replace("var_f20 * updateRateF", f"{host} * updateRateF")
    if form == "source_host":
        source = source.replace(
            ASSIGN,
            ASSIGN.replace("var_f20", host),
            1,
        )
        prefix = ""
    elif form == "self_chain":
        prefix = f"        {host} = var_f20 = var_f20;\n"
    else:
        prefix = f"        {host} = var_f20;\n"
    source = source.replace(START, prefix + start, 1)
    if form == "restore_comma":
        source = source.replace(
            UNK,
            UNK.rstrip("\n") + f"\n        var_f20 = ({host}, {host});\n",
            1,
        )
    else:
        source = source.replace(
            UNK,
            UNK.rstrip("\n") + f"\n        var_f20 = {host};\n",
            1,
        )
    return source


def evaluate(case: tuple[str, str]) -> tuple:
    host, form = case
    tag = f"{host}_{form}"
    source = make(*case)
    path = f"/tmp/codex_factor_alias_callspan_{tag}.c"
    trace = f"/tmp/codex_factor_alias_callspan_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_factor_alias_callspan_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_factor_alias_callspan_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    metrics = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if (
                    "RACER-FVAR" in line
                    and ("addr=-44 " in line or "addr=-56 " in line)
                ):
                    match = re.search(
                        r"bit=(\\d+).*addr=(-?\\d+).*adjsave=([0-9.-]+) "
                        r"uses=(\\d+).*c14=([0-9.-]+)",
                        line,
                    )
                    if match:
                        metrics.append("/".join(match.groups()))
    return tag, result, metrics, proc.returncode


def main() -> None:
    cases = [
        (host, form)
        for host in ("spCC", "var_f6", "segmentXVelocity")
        for form in (
            "keep_arg",
            "replace_arg",
            "source_host",
            "self_chain",
            "restore_comma",
        )
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            abs(row[1].get("insns", 9999) - 2625),
            row[1].get("norm", 9999),
        )
    )
    for tag, result, metrics, returncode in rows:
        print(
            tag,
            "rc",
            returncode,
            "metrics",
            metrics,
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[1].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
