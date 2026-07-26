#!/usr/bin/env python3
"""Use an existing zero store to extend late field-load webs ahead of spEC."""

from __future__ import annotations

import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = "/tmp/codex_pressure_spEC_safe.c"
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
ANCHOR = """\
    } else {
        racer->boostTimer = 0;
    }
    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {
"""

FIELDS = (
    "racer->ox2",
    "racer->oy2",
    "racer->oz2",
    "racer->unk34",
    "racer->velocity",
    "racer->lateral_velocity",
    "obj->x_velocity",
    "obj->y_velocity",
    "obj->z_velocity",
)


def expression(fields: tuple[str, ...], form: str) -> str:
    comparisons = [f"({field} > 0.0f)" for field in fields]
    if form == "sum":
        return f"({' + '.join(comparisons)}) * 0"
    if form == "mul":
        return f"({' * '.join(comparisons)}) * 0"
    if form == "comma":
        return f"({', '.join(comparisons)}, 0)"
    raise ValueError(form)


def make(fields: tuple[str, ...], form: str) -> str:
    source = open(BASE_PATH, encoding="utf-8").read()
    if source.count(ANCHOR) != 1:
        raise ValueError("boostTimer zero anchor is not unique")
    replacement = (
        "    } else {\n"
        "        racer->boostTimer = "
        + expression(fields, form)
        + ";\n"
        "    }\n"
        "    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {\n"
    )
    return source.replace(ANCHOR, replacement, 1)


def trace_summary(path: str) -> str:
    colors: list[str] = []
    with open(path, encoding="utf-8") as input_file:
        for line in input_file:
            match = re.search(
                r"RACER-COLOR bit=(\d+).* reg=(\d+) "
                r"adjsave=([0-9.]+).*?(?:addr=(-?\\d+)|opc=(....))",
                line,
            )
            if match and float(match.group(3)) >= 0.9:
                colors.append("/".join(part or "-" for part in match.groups()))
    return ",".join(colors)


def main() -> None:
    cases: list[tuple[tuple[str, ...], str]] = [
        ((field,), form)
        for field in FIELDS
        for form in ("sum", "comma")
    ]
    for fields in itertools.combinations(FIELDS[:6], 2):
        cases.extend((fields, form) for form in ("sum", "mul", "comma"))
    rows = []
    for fields, form in cases:
        field_tag = "-".join(
            field.replace("->", "_").replace("obj_", "o_")
            for field in fields
        )
        tag = f"{form}_{field_tag}"
        source = make(fields, form)
        path = f"/tmp/codex_pressure_field_fake_{tag}.c"
        trace = f"/tmp/codex_pressure_field_fake_{tag}.trace"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        result = ORACLE["evaluate"](
            source,
            keep=f"/tmp/codex_pressure_field_fake_{tag}.o",
        )
        subprocess.run(
            [
                ANALYSIS,
                path,
                f"/tmp/codex_pressure_field_fake_{tag}_analysis.o",
                trace,
            ],
            check=True,
            capture_output=True,
            text=True,
        )
        rows.append((tag, result, trace_summary(trace)))

    rows.sort(
        key=lambda row: (
            abs(row[1].get("f18", 0) - 190),
            abs(row[1].get("insns", 9999) - 2625),
            row[1].get("norm", 9999),
        )
    )
    for tag, result, trace in rows:
        print(tag, ORACLE["concise"](result), result.get("fp"), trace)
    print("tested", len(rows))


if __name__ == "__main__":
    main()
