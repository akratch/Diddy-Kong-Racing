#!/usr/bin/env python3
"""Combine f64 temporary reuse with the strongest spEC web shapes."""

from __future__ import annotations

import concurrent.futures
import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
MERGE = runpy.run_path(".codex_racer_f64_spEC_fake_merge.py")

CHAIN = """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
"""

MERGES = (
    (),
    ("whole_varf0",),
    ("top_factor", "steer", "trick"),
    ("speed_fraction", "top_factor", "steer", "trick"),
    ("top_factor", "wave_height", "wave_speed", "trick"),
    (
        "whole_varf0",
        "wave_height",
        "wave_speed",
        "steer",
        "trick",
    ),
)

NAMES = ("d0", "d1", "d2", "d3")


def make(selected: tuple[str, ...], pattern: tuple[str, ...]) -> str:
    source = MERGE["make"](selected)
    h0, h1, h2, h3 = pattern
    replacement = f"""\
        {h0} = racer->velocity * 0.05;
        {h1} = racer->forwardVel + {h0};
        {h2} = {h1} * 0.125;
        {h3} = racer->forwardVel - {h2};
        racer->forwardVel = {h3};
"""
    if source.count(CHAIN) != 1:
        raise ValueError("f64 chain anchor is not unique")
    return source.replace(CHAIN, replacement, 1)


def evaluate(case: tuple[tuple[str, ...], tuple[str, ...]]) -> tuple:
    selected, pattern = case
    source = make(selected, pattern)
    result = ORACLE["evaluate"](source)
    return selected, pattern, source, result


def main() -> None:
    cases = list(itertools.product(MERGES, itertools.product(NAMES, repeat=4)))
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))

    promoted = [
        row
        for row in rows
        if row[3].get("f20_insns") == 69
    ]
    ranked = sorted(
        promoted,
        key=lambda row: (
            abs(row[3].get("f18", 0) - 190),
            abs(row[3].get("insns", 9999) - 2625),
            row[3].get("norm", 9999),
        ),
    )
    for index, (selected, pattern, source, result) in enumerate(ranked[:100]):
        merge_tag = "-".join(selected) or "none"
        pattern_tag = "".join(name[-1] for name in pattern)
        tag = f"{merge_tag}_{pattern_tag}"
        if index < 25 or result.get("f18", 0) > 100:
            with open(
                f"/tmp/codex_f64_reuse_combine_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(tag, ORACLE["concise"](result), result.get("fp"))
    print(
        "tested",
        len(rows),
        "promoted",
        len(promoted),
        "scratch_like",
        sum(row[3].get("f18", 0) > 100 for row in promoted),
    )


if __name__ == "__main__":
    main()
