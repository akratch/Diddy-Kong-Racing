#!/usr/bin/env python3
"""Combine pre-node and post-node spEC splits around the f64 chain."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
SPLIT_F64 = runpy.run_path(
    "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/.codex_racer_split_f64.py"
)
MARKER = "        racer->forwardVel = d3;\n"


def make(value: str, shape: str) -> str:
    source = SPLIT_F64["make"](value, shape)
    source = source.replace(
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n    f32 carryZ;\n",
        1,
    )
    if source.count(MARKER) != 1:
        raise ValueError("forward marker is not unique")
    before, after = source.split(MARKER, 1)
    after = after.replace("spEC", "carryZ")
    return before + MARKER + "        carryZ = spEC;\n" + after


def main() -> None:
    for value in SPLIT_F64["SPLIT"]["VALUES"]:
        for shape in ("after_drag", "before_sin", "direct_value", "after_cos"):
            tag = f"{value}_{shape}"
            source = make(value, shape)
            result = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_spECtwo_{tag}.o"
            )
            with open(f"/tmp/codex_spECtwo_{tag}.c", "w", encoding="utf-8") as output:
                output.write(source)
            print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
