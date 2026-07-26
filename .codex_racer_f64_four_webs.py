#!/usr/bin/env python3
"""Retain all four double stages of the existing forwardVel arithmetic."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
OLD = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""
PREFIX = """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
"""
FORMS = {
    "canonical_chain": """\
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
""",
    "result_snapshot_compound": """\
        d3 = racer->forwardVel;
        d3 -= d2;
        racer->forwardVel = d3;
""",
    "result_snapshot_binary": """\
        d3 = racer->forwardVel;
        d3 = d3 - d2;
        racer->forwardVel = d3;
""",
    "product_copy_binary": """\
        d3 = d2;
        d3 = racer->forwardVel - d3;
        racer->forwardVel = d3;
""",
    "product_copy_compound": """\
        d3 = d2;
        d3 *= -1.0;
        d3 += racer->forwardVel;
        racer->forwardVel = d3;
""",
    "product_copy_neg": """\
        d3 = -d2;
        d3 += racer->forwardVel;
        racer->forwardVel = d3;
""",
    "embedded_self": """\
        d3 = racer->forwardVel - (d2 = d2);
        racer->forwardVel = d3;
""",
    "embedded_plus": """\
        d3 = racer->forwardVel - (d2 = +d2);
        racer->forwardVel = d3;
""",
    "embedded_mul1": """\
        d3 = racer->forwardVel - (d2 = d2 * 1.0);
        racer->forwardVel = d3;
""",
    "embedded_div1": """\
        d3 = racer->forwardVel - (d2 = d2 / 1.0);
        racer->forwardVel = d3;
""",
    "embedded_comma": """\
        d3 = racer->forwardVel - (d2, d2);
        racer->forwardVel = d3;
""",
    "embedded_void_comma": """\
        d3 = racer->forwardVel - ((void) d2, d2);
        racer->forwardVel = d3;
""",
    "embedded_cond": """\
        d3 = racer->forwardVel - (d2 ? d2 : d2);
        racer->forwardVel = d3;
""",
    "store_comma": """\
        d3 = racer->forwardVel - d2;
        racer->forwardVel = (d2, d3);
""",
    "store_void_comma": """\
        d3 = racer->forwardVel - d2;
        racer->forwardVel = ((void) d2, d3);
""",
    "store_cond": """\
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d2 ? d3 : d3;
""",
    "store_self_then": """\
        d3 = racer->forwardVel - d2;
        d2 = d2;
        racer->forwardVel = d3;
""",
    "post_expr": """\
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
        d2;
""",
    "post_void": """\
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
        (void) d2;
""",
    "two_stage_result": """\
        d3 = racer->forwardVel;
        d4 = d3 - d2;
        racer->forwardVel = d4;
""",
    "product_copy_result": """\
        d3 = d2;
        d4 = racer->forwardVel - d3;
        racer->forwardVel = d4;
""",
    "two_copies": """\
        d3 = d2;
        d4 = racer->forwardVel;
        d4 -= d3;
        racer->forwardVel = d4;
""",
}


def make(tag: str) -> str:
    names = ("d0", "d1", "d2", "d3", "d4")
    declarations = "".join(f"    f64 {name};\n" for name in names)
    source = BASE.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n" + declarations,
        1,
    )
    if source.count(OLD) != 1:
        raise ValueError(source.count(OLD))
    return source.replace(OLD, PREFIX + FORMS[tag], 1)


def read_ranges(trace: str) -> tuple[list[tuple[int, int, float]], str | None]:
    ranges = []
    choice = None
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "RACER-COLOR " in line and "size=8" in line:
                match = re.search(
                    r"reg=(\d+) adjsave=([0-9.-]+).*addr=(-?\d+) size=8",
                    line,
                )
                if match:
                    reg, save, addr = match.groups()
                    ranges.append((int(addr), int(reg), float(save)))
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    choice = "/".join(match.groups())
    return ranges, choice


def evaluate(tag: str) -> tuple:
    source = make(tag)
    path = f"/tmp/codex_f64_four_webs_{tag}.c"
    trace = f"/tmp/codex_f64_four_webs_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](source, keep=f"/tmp/codex_f64_four_webs_{tag}.o")
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_f64_four_webs_{tag}_analysis.o", trace],
        check=False,
        capture_output=True,
        text=True,
    )
    details = read_ranges(trace) if proc.returncode == 0 else ([], None)
    return tag, source, natural, details


def main() -> None:
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, FORMS))
    rows.sort(
        key=lambda row: (
            row[2].get("f20_operands", 0) == 0,
            -len(row[3][0]),
            abs(row[2].get("f18", 0) - 190),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, natural, details in rows:
        print(
            tag,
            "ranges",
            details[0],
            "choice",
            details[1],
            ORACLE["concise"](natural),
            natural.get("fp"),
        )


if __name__ == "__main__":
    main()
