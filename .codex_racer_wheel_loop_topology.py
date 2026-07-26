#!/usr/bin/env python3
"""Recover the source topology of the four-wheel surface scan loop."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
OLD = """\
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
        }
"""
BODY = """\
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {{
                i = racer->wheel_surfaces[var_t0];
            }}
"""
BODY_FOR = BODY.replace("{{", "{").replace("}}", "}")
FORMS = {
    "for_lt_post": """\
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
{body}        }
""",
    "for_ne_post": """\
        for (var_t0 = 0; var_t0 != 4; var_t0++) {
{body}        }
""",
    "for_le_post": """\
        for (var_t0 = 0; var_t0 <= 3; var_t0++) {
{body}        }
""",
    "for_lt_pre": """\
        for (var_t0 = 0; var_t0 < 4; ++var_t0) {
{body}        }
""",
    "for_ne_pre": """\
        for (var_t0 = 0; var_t0 != 4; ++var_t0) {
{body}        }
""",
    "while_lt_post": """\
        var_t0 = 0;
        while (var_t0 < 4) {
{body}            var_t0++;
        }
""",
    "while_ne_post": """\
        var_t0 = 0;
        while (var_t0 != 4) {
{body}            var_t0++;
        }
""",
    "do_lt_tail": """\
        var_t0 = 0;
        do {
{body}        } while (++var_t0 < 4);
""",
    "do_ne_tail": """\
        var_t0 = 0;
        do {
{body}        } while (++var_t0 != 4);
""",
    "do_split_lt": """\
        var_t0 = 0;
        do {
{body}            var_t0++;
        } while (var_t0 < 4);
""",
    "do_split_ne": """\
        var_t0 = 0;
        do {
{body}            var_t0++;
        } while (var_t0 != 4);
""",
}


def make(tag: str) -> str:
    if BASE.count(OLD) != 1:
        raise ValueError(BASE.count(OLD))
    return BASE.replace(OLD, FORMS[tag].replace("{body}", BODY_FOR), 1)


def metrics(trace: str) -> dict[str, str]:
    result: dict[str, str] = {}
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "FACTOR-COST reg=27 " in line and "caller" not in result:
                match = re.search(r"cost=([0-9.-]+)", line)
                if match:
                    result["caller"] = match.group(1)
            elif "FACTOR-CHOICE" in line and "choice" not in result:
                match = re.search(r"reg=(\\d+) cost=([0-9.-]+)", line)
                if match:
                    result["choice"] = "/".join(match.groups())
    return result


def evaluate(tag: str) -> tuple:
    source = make(tag)
    path = f"/tmp/codex_wheel_loop_{tag}.c"
    trace = f"/tmp/codex_wheel_loop_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_wheel_loop_{tag}.o",
    )
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_wheel_loop_{tag}_analysis.o", trace],
        check=False,
        capture_output=True,
        text=True,
    )
    return tag, source, natural, metrics(trace) if proc.returncode == 0 else {}


def main() -> None:
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, FORMS))
    rows.sort(
        key=lambda row: (
            row[2].get("f20_operands", 0) == 0,
            row[2].get("insns") != 2625,
            abs(row[2].get("f18", 0) - 190),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, natural, costs in rows:
        if natural.get("f20_operands", 0) > 0:
            with open(f"/tmp/codex_wheel_loop_promising_{tag}.c", "w", encoding="utf-8") as output:
                output.write(source)
        print(tag, costs, ORACLE["concise"](natural), natural.get("fp"))


if __name__ == "__main__":
    main()
