#!/usr/bin/env python3
"""Name existing f32-to-f64 conversions to create a fourth transient web."""

from __future__ import annotations

import concurrent.futures
import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
OLD = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""
VELOCITY = {
    "inline": "        d0 = racer->velocity * 0.05;\n",
    "snapshot": """\
        dv = racer->velocity;
        d0 = dv * 0.05;
""",
    "cast_snapshot": """\
        dv = (f64) racer->velocity;
        d0 = dv * 0.05;
""",
}
FORWARD = {
    "reload": """\
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
""",
    "snapshot": """\
        df = racer->forwardVel;
        d1 = df + d0;
        d2 = d1 * 0.125;
        d3 = df - d2;
        racer->forwardVel = d3;
""",
    "cast_snapshot": """\
        df = (f64) racer->forwardVel;
        d1 = df + d0;
        d2 = d1 * 0.125;
        d3 = df - d2;
        racer->forwardVel = d3;
""",
    "snapshot_late": """\
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        df = racer->forwardVel;
        d3 = df - d2;
        racer->forwardVel = d3;
""",
}
RESULTS = {
    "direct": "{forward}",
    "compound": None,
}


def result_block(forward_name: str, result_name: str) -> str:
    forward = FORWARD[forward_name]
    if result_name == "direct":
        return forward
    if forward_name == "reload":
        return """\
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel;
        d3 -= d2;
        racer->forwardVel = d3;
"""
    if forward_name in ("snapshot", "cast_snapshot"):
        cast = "(f64) " if forward_name == "cast_snapshot" else ""
        return f"""\
        df = {cast}racer->forwardVel;
        d1 = df + d0;
        d2 = d1 * 0.125;
        d3 = df;
        d3 -= d2;
        racer->forwardVel = d3;
"""
    return """\
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        df = racer->forwardVel;
        df -= d2;
        racer->forwardVel = df;
"""


def make(case: tuple[str, str, str, str]) -> str:
    velocity_name, forward_name, result_name, order = case
    declarations = "".join(
        f"    f64 {name};\n" for name in ("dv", "df", "d0", "d1", "d2", "d3")
    )
    source = BASE.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n" + declarations,
        1,
    )
    velocity = VELOCITY[velocity_name]
    forward = result_block(forward_name, result_name)
    if order == "velocity_first":
        block = velocity + forward
    elif forward_name in ("snapshot", "cast_snapshot"):
        # Hoist only the forward snapshot; retain the arithmetic order.
        cast = "(f64) " if forward_name == "cast_snapshot" else ""
        snapshot = f"        df = {cast}racer->forwardVel;\n"
        block = snapshot + velocity + forward.replace(snapshot, "", 1)
    else:
        block = velocity + forward
    return source.replace(OLD, block, 1)


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


def evaluate(case: tuple[str, str, str, str]) -> tuple:
    tag = "_".join(case)
    source = make(case)
    path = f"/tmp/codex_f64_input_snapshots_{tag}.c"
    trace = f"/tmp/codex_f64_input_snapshots_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_f64_input_snapshots_{tag}.o"
    )
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_f64_input_snapshots_{tag}_analysis.o", trace],
        check=False,
        capture_output=True,
        text=True,
    )
    details = read_ranges(trace) if proc.returncode == 0 else ([], None)
    return tag, source, natural, details


def main() -> None:
    cases = list(
        itertools.product(
            VELOCITY,
            FORWARD,
            RESULTS,
            ("velocity_first", "forward_first"),
        )
    )
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
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
