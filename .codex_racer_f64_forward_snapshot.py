#!/usr/bin/env python3
"""Probe retained forwardVel snapshots in the final double expression."""

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
FORMS = {
    "snapshot_full": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel;
        d2 = d1 + d0;
        d3 = d2 * 0.125;
        d4 = d1 - d3;
        racer->forwardVel = d4;
""",
    "snapshot_direct": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel;
        d2 = d1 + d0;
        d3 = d2 * 0.125;
        racer->forwardVel = d1 - d3;
""",
    "snapshot_compound": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel;
        d2 = d1 + d0;
        d3 = d2 * 0.125;
        d1 -= d3;
        racer->forwardVel = d1;
""",
    "snapshot_reversed": """\
        d1 = racer->forwardVel;
        d0 = racer->velocity * 0.05;
        d2 = d0 + d1;
        d3 = d2 * 0.125;
        d4 = d1 - d3;
        racer->forwardVel = d4;
""",
    "snapshot_d3_direct": """\
        d1 = racer->forwardVel;
        d0 = racer->velocity * 0.05;
        d2 = d0 + d1;
        d3 = d1 - (d2 * 0.125);
        racer->forwardVel = d3;
""",
    "snapshot_product_inline": """\
        d1 = racer->forwardVel;
        d0 = racer->velocity * 0.05;
        d2 = d0 + d1;
        d4 = d1 - (d2 * 0.125);
        racer->forwardVel = d4;
""",
}


def make(form: str, declaration_order: str) -> str:
    source = BASE
    for name in ("spCC", "var_f6", "segmentXVelocity"):
        source = re.sub(
            rf"^    f32 {name};\n",
            "",
            source,
            count=1,
            flags=re.MULTILINE,
        )
    source = re.sub(
        r"^    s32 pad4;\n",
        "",
        source,
        count=1,
        flags=re.MULTILINE,
    )
    names = declaration_order.split("_")
    declaration = "".join(f"    f64 {name};\n" for name in names)
    source = source.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n" + declaration,
        1,
    )
    return source.replace(OLD, FORMS[form], 1)


def evaluate(case: tuple[str, str]) -> tuple:
    form, declaration_order = case
    tag = f"{form}_{declaration_order.replace('_', '')}"
    source = make(*case)
    path = f"/tmp/codex_f64_forward_snapshot_{tag}.c"
    trace = f"/tmp/codex_f64_forward_snapshot_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_f64_forward_snapshot_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_f64_forward_snapshot_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    ranges = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "RACER-FVAR" in line and "size=8" not in line:
                    match = re.search(
                        r"addr=(-?\\d+) adjsave=([0-9.-]+) uses=(\\d+)",
                        line,
                    )
                    if match and int(match.group(1)) <= -140:
                        ranges.append("/".join(match.groups()))
    return tag, result, ranges, proc.returncode


def main() -> None:
    orders = (
        "d0_d1_d2_d3_d4",
        "d1_d0_d2_d3_d4",
        "d4_d3_d2_d1_d0",
        "d0_d2_d4_d1_d3",
    )
    cases = [(form, order) for form in FORMS for order in orders]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            abs(row[1].get("f18", 0) - 190),
            abs(row[1].get("insns", 9999) - 2625),
            row[1].get("norm", 9999),
        )
    )
    for tag, result, ranges, returncode in rows:
        print(
            tag,
            "rc",
            returncode,
            "ranges",
            ranges,
            ORACLE["concise"](result),
            result.get("fp"),
        )


if __name__ == "__main__":
    main()
