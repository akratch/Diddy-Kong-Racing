#!/usr/bin/env python3
"""Distribute the three retained f64 stages across existing final-block CFG."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()

ASSIGNMENTS = (
    "        d0 = racer->velocity * 0.05;\n",
    "        d1 = racer->forwardVel + d0;\n",
    "        d2 = d1 * 0.125;\n",
)
ANCHORS = (
    "        if (racer->trickType == 1 || racer->trickType == -1) {\n",
    "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n",
    "        if (racer->unk34 < 0.0f) {\n",
    "        var_f20 += 4.0f * (racer->unk34 * spD0);\n",
    "        racer->forwardVel = d3;\n",
)


def make(positions: tuple[int, int, int]) -> str:
    source = BASE
    for assignment in ASSIGNMENTS:
        source = source.replace(assignment, "", 1)
    insertions: dict[int, str] = {}
    for assignment, position in zip(ASSIGNMENTS, positions):
        insertions[position] = insertions.get(position, "") + assignment
    for position, lines in insertions.items():
        anchor = ANCHORS[position]
        if position in (0, 1, 2):
            source = source.replace(anchor, lines + anchor, 1)
        elif position == 3:
            source = source.replace(anchor, anchor + lines, 1)
        else:
            final_anchor = "        d3 = racer->forwardVel - d2;\n"
            source = source.replace(final_anchor, lines + final_anchor, 1)
    return source


def main() -> None:
    rows = []
    for positions in itertools.combinations_with_replacement(range(5), 3):
        source = make(positions)
        tag = "".join(map(str, positions))
        result = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_f64place_{tag}.o"
        )
        with open(f"/tmp/codex_f64place_{tag}.c", "w", encoding="utf-8") as output:
            output.write(source)
        rows.append((positions, result))
    for positions, result in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_insns") != 69,
            abs(row[1].get("f18", 0) - 190),
            row[1].get("norm", 9999),
        ),
    ):
        print("".join(map(str, positions)), ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
