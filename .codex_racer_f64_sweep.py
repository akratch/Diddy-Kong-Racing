#!/usr/bin/env python3
"""Probe double-precision temporaries in the final forwardVel expression."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = "/tmp/codex_layout_exact.c"

OLD_EXPR = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""

FORMS = {
    "d0": """\
        d0 = racer->velocity * 0.05;
        racer->forwardVel -= (racer->forwardVel + d0) * 0.125;
""",
    "d01": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        racer->forwardVel -= d1 * 0.125;
""",
    "d012": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        racer->forwardVel -= d2;
""",
    "d012_assign": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        racer->forwardVel = racer->forwardVel - d2;
""",
    "d0123": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
""",
}


def replace_once(source: str, old: str, new: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"expected one occurrence, found {count}: {old!r}")
    return source.replace(old, new, 1)


def source_for(order: tuple[str, ...], form: str) -> str:
    source = open(BASE_PATH, encoding="utf-8").read()
    source = replace_once(source, "    f32 spCC;\n", "")
    source = replace_once(source, "    f32 var_f6;\n", "")
    source = replace_once(source, "    f32 segmentXVelocity;\n", "")
    if "d3" in order:
        source = replace_once(source, "    s32 pad4;\n", "")
    declaration = "".join(f"    f64 {name};\n" for name in order)
    source = replace_once(source, "    Object_Boost *boostObj;\n",
                          "    Object_Boost *boostObj;\n" + declaration)
    source = replace_once(source, OLD_EXPR, FORMS[form])
    return source


def main() -> None:
    for form in FORMS:
        names = ("d0", "d1", "d2", "d3") if form == "d0123" else ("d0", "d1", "d2")
        for order in itertools.permutations(names):
            tag = f"{form}_{''.join(order)}"
            source = source_for(order, form)
            result = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_f64_{tag}.o"
            )
            with open(f"/tmp/codex_f64_{tag}.c", "w", encoding="utf-8") as output:
                output.write(source)
            print(tag, ORACLE["concise"](result))


if __name__ == "__main__":
    main()
