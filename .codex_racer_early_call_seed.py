#!/usr/bin/env python3
"""Seed f20 with one pre-factor range whose caller-save cost exceeds 60."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
END = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
STARTS = {
    "entry_calls": """\
    if (func_8000E138()) {
""",
    "item_calls": """\
    handle_racer_items(obj, racer, updateRate);
""",
    "matrix_calls": """\
    mtxf_from_transform((MtxF *) &sp60, &gCurrentRacerTransform);
""",
}
OPS = (">", "<", "!=", ">=", "<=", "==")
CONSTANTS = ("0.0f", "1.0f", "-1.0f", "2.0f", "-2.0f", "4.0f")


def make(start_name: str, repetitions: int, sink: str) -> str:
    source = BASE
    start = STARTS[start_name]
    if source.count(start) != 1 or source.count(END) != 1:
        raise ValueError((start_name, source.count(start), source.count(END)))
    source = source.replace(
        start,
        "    {\n"
        "        f32 early_call_seed = obj->x_velocity;\n"
        + start,
        1,
    )
    terms = [
        f"(early_call_seed {OPS[index % len(OPS)]} {index}.0f)"
        for index in range(repetitions)
    ]
    expression = " + ".join(terms)
    if sink == "integer":
        close = f"    var_v0 += ({expression}) * 0;\n    }}\n"
    elif sink == "float":
        close = (
            f"    spEC += ({expression}) * 0.0f;\n"
            "    }\n"
        )
    else:
        close = (
            "    for (var_a0 = 0; var_a0 < 1; var_a0++) {\n"
            f"        var_a0 += ({expression}) * 0;\n"
            "    }\n"
            "    }\n"
        )
    return source.replace(END, close + END, 1)


def evaluate(case: tuple[str, int, str]) -> tuple:
    start_name, repetitions, sink = case
    tag = f"{start_name}_r{repetitions}_{sink}"
    source = make(*case)
    path = f"/tmp/codex_early_call_seed_{tag}.c"
    trace = f"/tmp/codex_early_call_seed_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_early_call_seed_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_early_call_seed_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    metrics: dict[str, str] = {}
    f20_rows = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "RACER-FVAR" in line and "addr=-172 " in line:
                    match = re.search(
                        r"adjsave=([0-9.-]+) uses=(\\d+).*"
                        r"c14=([0-9.-]+) c20=([0-9.-]+)",
                        line,
                    )
                    if match:
                        metrics["seed"] = "/".join(match.groups())
                elif "FACTOR-COST reg=30 " in line:
                    match = re.search(
                        r"cost=([0-9.-]+).*first-used=(\\d+)", line
                    )
                    if match:
                        metrics["factor_f20"] = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\\d+) cost=([0-9.-]+)", line)
                    if match:
                        metrics["factor"] = "/".join(match.groups())
                elif "RACER-COLOR bit" in line and "reg=30 " in line:
                    f20_rows.append(line.strip())
    return tag, source, result, metrics, f20_rows, proc.returncode


def main() -> None:
    cases = [
        (start_name, repetitions, sink)
        for start_name in STARTS
        for repetitions in (8, 16, 24, 32, 48, 64, 80, 96)
        for sink in ("loop",)
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[3].get("factor", "99").split("/")[0] != "30",
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
        )
    )
    for tag, source, result, metrics, f20_rows, returncode in rows:
        if metrics.get("factor", "").startswith("30"):
            with open(
                f"/tmp/codex_early_call_seed_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
            "metrics",
            metrics,
            "f20colors",
            len(f20_rows),
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].get("factor", "").startswith("30") for row in rows),
    )


if __name__ == "__main__":
    main()
