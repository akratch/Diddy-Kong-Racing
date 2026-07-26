#!/usr/bin/env python3
"""Use the existing unk34 sign branch to lower f64 temporary web priority."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = "/tmp/codex_f64_d0123_d0d1d2d3.c"

OLD_BRANCH = """\
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""

OLD_CHAIN = """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
"""

ASSIGNMENTS = (
    "        d0 = racer->velocity * 0.05;\n",
    "        d1 = racer->forwardVel + d0;\n",
    "        d2 = d1 * 0.125;\n",
)


def variant(count: int, placement: str) -> str:
    source = open(BASE_PATH, encoding="utf-8").read()
    moved = "".join(ASSIGNMENTS[:count])
    remainder = "".join(ASSIGNMENTS[count:]) + """\
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
"""
    if placement == "before":
        branch = moved + OLD_BRANCH
    elif placement == "arms":
        arm_lines = "".join("    " + line for line in moved.splitlines(True))
        branch = """\
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
""" + arm_lines + """\
        } else {
""" + arm_lines + """\
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    elif placement == "arms_after":
        arm_lines = "".join("    " + line for line in moved.splitlines(True))
        branch = """\
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
        if (racer->unk34 < 0.0f) {
""" + arm_lines + """\
        } else {
""" + arm_lines + """\
        }
"""
    else:
        raise ValueError(placement)
    if source.count(OLD_BRANCH) != 1 or source.count(OLD_CHAIN) != 1:
        raise ValueError("source anchors are not unique")
    source = source.replace(OLD_BRANCH, branch, 1)
    return source.replace(OLD_CHAIN, remainder, 1)


def main() -> None:
    for placement in ("before", "arms", "arms_after"):
        for count in (1, 2, 3):
            tag = f"{placement}_{count}"
            source = variant(count, placement)
            obj = f"/tmp/codex_f64cfg_{tag}.o"
            result = ORACLE["evaluate"](source, keep=obj)
            with open(f"/tmp/codex_f64cfg_{tag}.c", "w", encoding="utf-8") as output:
                output.write(source)
            print(tag, ORACLE["concise"](result))


if __name__ == "__main__":
    main()
