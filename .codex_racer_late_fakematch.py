#!/usr/bin/env python3
"""Probe optimizer-erased FP uses on zero stores after the final drag block."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
BASE_SHA = "28ae550756b5"
FLOATS = (
    "spEC",
    "spE8",
    "spE4",
    "spE0",
    "var_f14",
    "spD8",
    "spD4",
    "spD0",
    "var_f20",
    "racerThrottle",
    "racerBrake",
    "var_f0",
    "spCC",
    "var_f2",
    "racerVelocity",
    "var_f6",
    "segmentXVelocity",
)


def late_zero_lines() -> list[int]:
    lines = BASE.splitlines(keepends=True)
    start = next(
        i for i, line in enumerate(lines) if "racer->unk10C = 0;" in line
    )
    return [
        i
        for i in range(start, len(lines))
        if re.search(r"=\s*(?:0|FALSE);\s*$", lines[i])
        and "0.0" not in lines[i]
    ]


def replace(source: str, line_index: int, expression: str) -> str:
    lines = source.splitlines(keepends=True)
    lines[line_index] = re.sub(
        r"=\s*(?:0|FALSE);[ \t]*\n?$",
        f"= {expression};\n",
        lines[line_index],
    )
    return "".join(lines)


def fake(values: tuple[str, ...], form: str) -> str:
    comparisons = [f"({value} > 0.0f)" for value in values]
    if form == "sum":
        return f"({' + '.join(comparisons)}) * 0"
    if form == "mul":
        return f"({' * '.join(comparisons)}) * 0"
    if form == "comma":
        return f"({', '.join(comparisons)}, 0)"
    raise ValueError(form)


def evaluate(line_index: int, values: tuple[str, ...], form: str) -> tuple:
    lhs = BASE.splitlines()[line_index].split("=", 1)[0].strip()
    lhs_tag = re.sub(r"\W+", "-", lhs).strip("-")
    tag = f"l{line_index + 1}_{lhs_tag}_{form}_{'-'.join(values)}"
    source = replace(BASE, line_index, fake(values, form))
    path = f"/tmp/codex_late_fakematch_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_late_fakematch_{tag}.o"
    )
    return tag, result


def main() -> None:
    rows = []
    effective: set[tuple[int, str]] = set()
    for line_index in late_zero_lines():
        for value in FLOATS:
            row = evaluate(line_index, (value,), "sum")
            rows.append(row)
            if row[1].get("sha1") != BASE_SHA:
                effective.add((line_index, value))

    # Only combine values whose single fake survived the optimizer at this site.
    for line_index in late_zero_lines():
        values = sorted(
            value for index, value in effective if index == line_index
        )
        for count in (2, 3, 4):
            for group in itertools.combinations(values, count):
                for form in ("sum", "mul", "comma"):
                    rows.append(evaluate(line_index, group, form))

    for tag, result in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            abs(row[1].get("insns", 9999) - len(ORACLE["TARGET_INSNS"])),
            row[1].get("norm", 9999),
            row[0],
        ),
    ):
        if result.get("f20_operands", 0) > 0 or result.get("sha1") != BASE_SHA:
            print(tag, ORACLE["concise"](result), result.get("fp"))
    print(
        "tested",
        len(rows),
        "sites",
        [index + 1 for index in late_zero_lines()],
        "effective",
        sorted((index + 1, value) for index, value in effective),
        "promoted",
        sum(result.get("f20_operands", 0) > 0 for _, result in rows),
    )


if __name__ == "__main__":
    main()
