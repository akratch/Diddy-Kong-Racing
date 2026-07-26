#!/usr/bin/env python3
"""Test instruction-neutral one-shot loop metadata around the factor web."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
STARTS = {
    "factor": """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
""",
    "weighted": """\
    var_f20 *= gCurrentRacerWeightStat;
""",
    "rotation": """\
    if (racer->zipperDirCorrection != 0 && racer->spinout_timer == 0) {
""",
    "drag": """\
    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {
""",
}
ENDS = {
    "position": """\
    obj->x_velocity = var_f20;
""",
    "inverse": """\
    mtxf_from_inverse_transform((MtxF *) &sp60, &gCurrentRacerTransform);
""",
    "tail": """\
    if (playerObjectMoved != FALSE) {
""",
}
WRAPPERS = {
    "do_zero": ("    do {\n", "    } while (0);\n"),
    "do_false": ("    do {\n", "    } while (FALSE);\n"),
    "while_break": ("    while (TRUE) {\n", "        break;\n    }\n"),
    "for_break": ("    for (;;) {\n", "        break;\n    }\n"),
    "do_assign_zero": (
        "    do {\n",
        "    } while (var_t9 = 0);\n",
    ),
    "for_one": (
        "    var_t9 = 0;\n    for (; var_t9 < 1; var_t9++) {\n",
        "    }\n",
    ),
    "while_one": (
        "    var_t9 = 1;\n    while (var_t9) {\n",
        "        var_t9 = 0;\n    }\n",
    ),
    "do_increment_one": (
        "    var_t9 = 0;\n    do {\n",
        "    } while (++var_t9 < 1);\n",
    ),
    "for_pad5_one": (
        "    pad5 = 0;\n    for (; pad5 < 1; pad5++) {\n",
        "    }\n",
    ),
    "do_pad5_one": (
        "    pad5 = 0;\n    do {\n",
        "    } while (++pad5 < 1);\n",
    ),
    "while_pad5_one": (
        "    pad5 = 1;\n    while (pad5) {\n",
        "        pad5 = 0;\n    }\n",
    ),
}


def make(start_name: str, end_name: str, wrapper_name: str) -> str:
    source = BASE
    start = STARTS[start_name]
    end = ENDS[end_name]
    if source.count(start) != 1 or source.count(end) != 1:
        raise ValueError(
            (start_name, end_name, source.count(start), source.count(end))
        )
    opening, closing = WRAPPERS[wrapper_name]
    source = source.replace(start, opening + start, 1)
    source = source.replace(end, closing + end, 1)
    return source


def evaluate(case: tuple[str, str, str]) -> tuple:
    start_name, end_name, wrapper_name = case
    tag = f"{start_name}_{end_name}_{wrapper_name}"
    source = make(*case)
    path = f"/tmp/codex_loop_metadata_{tag}.c"
    trace = f"/tmp/codex_loop_metadata_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_loop_metadata_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_loop_metadata_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    metrics: dict[str, str] = {}
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FACTOR-COST reg=27 " in line:
                    match = re.search(r"cost=([0-9.-]+)", line)
                    if match:
                        metrics["caller"] = match.group(1)
                elif "FACTOR-COST reg=30 " in line:
                    match = re.search(
                        r"cost=([0-9.-]+).*first-used=(\\d+)", line
                    )
                    if match:
                        metrics["callee"] = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\\d+) cost=([0-9.-]+)", line)
                    if match:
                        metrics["choice"] = "/".join(match.groups())
    return tag, source, result, metrics, proc.returncode


def main() -> None:
    cases = [
        (start_name, end_name, wrapper_name)
        for start_name in STARTS
        for end_name in ENDS
        for wrapper_name in WRAPPERS
        if BASE.index(STARTS[start_name]) < BASE.index(ENDS[end_name])
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[3].get("choice", "99").split("/")[0] != "30",
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, metrics, returncode in rows:
        if metrics.get("choice", "").startswith("30"):
            with open(
                f"/tmp/codex_loop_metadata_promising_{tag}.c",
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
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].get("choice", "").startswith("30") for row in rows),
    )


if __name__ == "__main__":
    main()
