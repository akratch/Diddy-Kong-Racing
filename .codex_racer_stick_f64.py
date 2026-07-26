#!/usr/bin/env python3
"""Retain double webs in the target's grounded-wheel stick scaling block."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()
OLD = "        gCurrentStickY = (1.0 - var_f20) * ((f32) gCurrentStickY);\n"

FORMS = {
    "a": """\
        d0 = (f32) gCurrentStickY;
        d1 = 1.0 - var_f20;
        d2 = d1 * d0;
        d3 = d2;
        gCurrentStickY = d3;
""",
    "b": """\
        d0 = 1.0 - var_f20;
        d1 = (f32) gCurrentStickY;
        d2 = d0 * d1;
        d3 = d2;
        gCurrentStickY = d3;
""",
    "c": """\
        d0 = (f32) gCurrentStickY;
        d1 = 1.0 - var_f20;
        d2 = d1 * d0;
        gCurrentStickY = d2;
""",
    "d": """\
        d0 = (f32) gCurrentStickY;
        d1 = 1.0 - var_f20;
        gCurrentStickY = d1 * d0;
""",
}


def make(form: str, order: tuple[str, ...]) -> str:
    source = BASE.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n"
        + "".join(f"    f64 {name};\n" for name in order),
        1,
    )
    return source.replace(OLD, FORMS[form], 1)


def main() -> None:
    for form in FORMS:
        for order in itertools.permutations(("d0", "d1", "d2", "d3")):
            tag = f"{form}_{''.join(name[-1] for name in order)}"
            source = make(form, order)
            result = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_stickf64_{tag}.o"
            )
            if (
                result.get("f20_insns")
                or result.get("f18", 0) > 100
                or result.get("insns") != 2655
            ):
                with open(f"/tmp/codex_stickf64_{tag}.c", "w", encoding="utf-8") as output:
                    output.write(source)
                print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
