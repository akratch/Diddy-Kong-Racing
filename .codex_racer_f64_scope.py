#!/usr/bin/env python3
"""Test block scope and initializer forms for the four-stage f64 chain."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()

OLD_EXPR = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""
SEPARATE = """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
"""

VARIANTS = {
    "local_separate": """\
        f64 d0;
        f64 d1;
        f64 d2;
        f64 d3;
""" + SEPARATE,
    "local_init": """\
        f64 d0 = racer->velocity * 0.05;
        f64 d1 = racer->forwardVel + d0;
        f64 d2 = d1 * 0.125;
        f64 d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
""",
    "nested_separate": """\
        {
            f64 d0;
            f64 d1;
            f64 d2;
            f64 d3;
            d0 = racer->velocity * 0.05;
            d1 = racer->forwardVel + d0;
            d2 = d1 * 0.125;
            d3 = racer->forwardVel - d2;
            racer->forwardVel = d3;
        }
""",
    "nested_init": """\
        {
            f64 d0 = racer->velocity * 0.05;
            f64 d1 = racer->forwardVel + d0;
            f64 d2 = d1 * 0.125;
            f64 d3 = racer->forwardVel - d2;
            racer->forwardVel = d3;
        }
""",
    "nested_cascade": """\
        {
            f64 d0 = racer->velocity * 0.05;
            {
                f64 d1 = racer->forwardVel + d0;
                {
                    f64 d2 = d1 * 0.125;
                    {
                        f64 d3 = racer->forwardVel - d2;
                        racer->forwardVel = d3;
                    }
                }
            }
        }
""",
    "array": """\
        {
            f64 d[4];
            d[0] = racer->velocity * 0.05;
            d[1] = racer->forwardVel + d[0];
            d[2] = d[1] * 0.125;
            d[3] = racer->forwardVel - d[2];
            racer->forwardVel = d[3];
        }
""",
    "struct": """\
        {
            struct {
                f64 d0;
                f64 d1;
                f64 d2;
                f64 d3;
            } d;
            d.d0 = racer->velocity * 0.05;
            d.d1 = racer->forwardVel + d.d0;
            d.d2 = d.d1 * 0.125;
            d.d3 = racer->forwardVel - d.d2;
            racer->forwardVel = d.d3;
        }
""",
    "union": """\
        {
            union {
                f64 d[4];
                struct {
                    f64 d0;
                    f64 d1;
                    f64 d2;
                    f64 d3;
                } s;
            } d;
            d.d[0] = racer->velocity * 0.05;
            d.d[1] = racer->forwardVel + d.d[0];
            d.d[2] = d.d[1] * 0.125;
            d.d[3] = racer->forwardVel - d.d[2];
            racer->forwardVel = d.d[3];
        }
""",
}


def main() -> None:
    for tag, expression in VARIANTS.items():
        if BASE.count(OLD_EXPR) != 1:
            raise ValueError("forward expression is not unique")
        source = BASE.replace(OLD_EXPR, expression, 1)
        result = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_f64scope_{tag}.o"
        )
        with open(f"/tmp/codex_f64scope_{tag}.c", "w", encoding="utf-8") as output:
            output.write(source)
        print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
