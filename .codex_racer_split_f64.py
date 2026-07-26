#!/usr/bin/env python3
"""Combine explicit spEC-range splits with the target-opcode f64 chain."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
SPLIT = runpy.run_path("/tmp/codex_racer_spEC_split.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()

OLD_EXPR = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""
NEW_EXPR = """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
"""


def make(value: str, shape: str) -> str:
    source = SPLIT["shape_source"](value, shape, base=BASE)
    declaration = "    f64 d0;\n    f64 d1;\n    f64 d2;\n    f64 d3;\n"
    source = source.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n" + declaration,
        1,
    )
    if source.count(OLD_EXPR) != 1:
        raise ValueError("forward expression is not unique")
    return source.replace(OLD_EXPR, NEW_EXPR, 1)


def main() -> None:
    for value in SPLIT["VALUES"]:
        for shape in ("after_drag", "before_sin", "direct_value", "after_cos"):
            tag = f"{value}_{shape}"
            source = make(value, shape)
            result = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_splitf64_{tag}.o"
            )
            with open(f"/tmp/codex_splitf64_{tag}.c", "w", encoding="utf-8") as output:
                output.write(source)
            print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
