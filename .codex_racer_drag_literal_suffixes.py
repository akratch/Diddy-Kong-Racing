#!/usr/bin/env python3
"""Exhaust float/double suffix topology for the four drag constants."""

from __future__ import annotations

import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
SITES = (
    ("d4_air", "    spD4 = 0.01f;\n", "    spD4 = 0.01;\n"),
    ("d0_air", "    spD0 = 0.02f;\n", "    spD0 = 0.02;\n"),
    ("d8_air", "    spD8 = 0.004f;\n", "    spD8 = 0.004;\n"),
    ("d4_ground", "        spD4 = 0.02f;\n", "        spD4 = 0.02;\n"),
)


def make(bits: tuple[bool, ...]) -> tuple[str, str]:
    source = BASE
    names = []
    for enabled, (name, old, new) in zip(bits, SITES):
        if enabled:
            if source.count(old) != 1:
                raise ValueError((name, source.count(old)))
            source = source.replace(old, new, 1)
            names.append(name)
    return ("_".join(names) if names else "all_f32"), source


def trace_choice(path: str) -> tuple[float | None, str | None]:
    caller = None
    choice = None
    with open(path, encoding="utf-8") as input_file:
        for line in input_file:
            if "FACTOR-COST reg=27 " in line:
                match = re.search(r"cost=([0-9.-]+)", line)
                if match:
                    caller = float(match.group(1))
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    choice = "/".join(match.groups())
    return caller, choice


def main() -> None:
    rows = []
    for bits in itertools.product((False, True), repeat=len(SITES)):
        tag, source = make(bits)
        path = f"/tmp/codex_drag_suffixes_{tag}.c"
        trace = f"/tmp/codex_drag_suffixes_{tag}.trace"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_drag_suffixes_{tag}_natural.o"
        )
        proc = subprocess.run(
            [
                "/tmp/codex_run_analysis_natural.sh",
                path,
                f"/tmp/codex_drag_suffixes_{tag}_analysis.o",
                trace,
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        rows.append(
            (
                tag,
                bits,
                source,
                natural,
                trace_choice(trace) if proc.returncode == 0 else (None, None),
            )
        )
    rows.sort(
        key=lambda row: (
            row[3].get("f20_operands", 0) == 0,
            abs(row[3].get("f18", 0) - 190),
            abs(row[3].get("insns", 9999) - 2625),
            row[3].get("norm", 9999),
        )
    )
    for tag, bits, source, natural, cost in rows:
        print(tag, "cost", cost, ORACLE["concise"](natural), natural.get("fp"))


if __name__ == "__main__":
    main()
