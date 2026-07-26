#!/usr/bin/env python3
"""Partition the four disjoint var_f20 regions into coalescible C locals."""

from __future__ import annotations

import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

NAMES = ("var_f20", "spCC", "var_f6", "segmentXVelocity")
MARKERS = (
    (
        "                var_f20 = racer->velocity * var_t0 * 0.00015;\n",
        "                obj->z_velocity -= racer->oz3 * var_f20;\n",
    ),
    (
        "            var_f20 = racer->velocity * spD8 * 8.0f;\n",
        "        obj->z_velocity -= racer->oz2 * var_f20;\n",
    ),
    (
        "        var_f20 = obj->x_velocity;\n",
        "    obj->x_velocity = var_f20;\n",
    ),
)


def partitions(length: int) -> list[tuple[int, ...]]:
    rows = []
    for labels in itertools.product(range(length), repeat=length):
        if labels[0] != 0:
            continue
        seen = 0
        valid = True
        for label in labels:
            if label > seen + 1:
                valid = False
                break
            seen = max(seen, label)
        if valid:
            rows.append(labels)
    return rows


def rename_interval(
    source: str,
    start_marker: str,
    end_marker: str,
    replacement: str,
) -> str:
    start = source.index(start_marker)
    end = source.index(end_marker, start) + len(end_marker)
    region = source[start:end].replace("var_f20", replacement)
    return source[:start] + region + source[end:]


def make(labels: tuple[int, ...]) -> str:
    source = BASE
    # Region zero is the initial factor.  The three later disjoint regions
    # are renamed from the end backwards so marker offsets remain irrelevant.
    for region_index in range(3, 0, -1):
        label = labels[region_index]
        if label == 0:
            continue
        start, end = MARKERS[region_index - 1]
        source = rename_interval(source, start, end, NAMES[label])
    return source


def evaluate(labels: tuple[int, ...]) -> tuple:
    tag = "".join(map(str, labels))
    source = make(labels)
    path = f"/tmp/codex_factor_partition_{tag}.c"
    trace = f"/tmp/codex_factor_partition_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_factor_partition_{tag}.o"
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_factor_partition_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    choices = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "RACER-COLOR bit" not in line or "type=3 addr=" not in line:
                    continue
                match = re.search(
                    r"bit=(\d+).*reg=(\d+).*adjsave=([0-9.-]+) "
                    r"uses=(\d+) cost=([0-9.-]+).*addr=(-?\d+)",
                    line,
                )
                if match:
                    bit, reg, save, uses, cost, addr = match.groups()
                    if reg == "30" or addr in ("-44", "-48", "-52", "-100"):
                        choices.append(
                            f"{bit}:{reg}:{save}:{uses}:{cost}:{addr}"
                        )
    return tag, labels, source, result, choices, proc.returncode


def main() -> None:
    cases = partitions(4)
    rows = [evaluate(labels) for labels in cases]
    rows.sort(
        key=lambda row: (
            row[3].get("f20_operands", 0) == 0,
            row[3].get("mismatch", 999999),
            abs(row[3].get("insns", 9999) - 2625),
            row[3].get("norm", 9999),
            row[0],
        )
    )
    for tag, labels, source, result, choices, returncode in rows:
        print(
            tag,
            "rc",
            returncode,
            "choices",
            ";".join(choices),
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
