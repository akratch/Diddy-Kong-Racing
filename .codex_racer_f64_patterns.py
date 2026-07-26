#!/usr/bin/env python3
"""Exhaust f64 source-variable reuse patterns in the forwardVel chain."""

from __future__ import annotations

import concurrent.futures
import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()
OLD_EXPR = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""
NAMES = ("d0", "d1", "d2", "d3")


def make(pattern: tuple[str, str, str, str]) -> str:
    h0, h1, h2, h3 = pattern
    source = BASE.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n"
        "    f64 d0;\n    f64 d1;\n    f64 d2;\n    f64 d3;\n",
        1,
    )
    expression = f"""\
        {h0} = racer->velocity * 0.05;
        {h1} = racer->forwardVel + {h0};
        {h2} = {h1} * 0.125;
        {h3} = racer->forwardVel - {h2};
        racer->forwardVel = {h3};
"""
    return source.replace(OLD_EXPR, expression, 1)


def evaluate(pattern: tuple[str, str, str, str]) -> tuple:
    source = make(pattern)
    return pattern, source, ORACLE["evaluate"](source)


def main() -> None:
    patterns = list(itertools.product(NAMES, repeat=4))
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, patterns))
    ranked = sorted(
        rows,
        key=lambda row: (
            row[2].get("f20_insns") != 69,
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        ),
    )
    print("tested", len(rows))
    for pattern, source, result in ranked[:80]:
        tag = "".join(name[-1] for name in pattern)
        if result.get("f20_insns") == 69:
            with open(f"/tmp/codex_f64pattern_{tag}.c", "w", encoding="utf-8") as output:
                output.write(source)
        print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
