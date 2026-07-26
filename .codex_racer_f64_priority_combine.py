#!/usr/bin/env python3
"""Combine spEC priority merges with discrete f64 blocker priority states."""

from __future__ import annotations

import concurrent.futures
import itertools
import os
import runpy


MERGE = runpy.run_path(".codex_racer_f64_spEC_fake_merge.py")
ORACLE = MERGE["ORACLE"]

MERGES = (
    (),
    ("whole_varf0",),
    ("whole_varf0", "wave_height", "wave_speed", "steer", "trick"),
    ("top_factor",),
    ("top_factor", "wave_height", "wave_speed", "trick"),
    ("speed_fraction", "top_factor", "wave_height", "wave_speed"),
    ("speed_fraction", "top_factor", "wave_speed", "trick"),
    ("speed_fraction", "top_factor", "steer", "trick"),
    ("top_factor", "wave_height", "wave_speed"),
    ("top_factor", "wave_speed", "steer", "trick"),
    ("speed_fraction", "top_factor", "wave_height", "trick"),
    ("top_factor", "steer", "trick"),
)

ANCHORS = {
    "d0": "        d0 = racer->velocity * 0.05;\n",
    "d1": "        d1 = racer->forwardVel + d0;\n",
    "d2": "        d2 = d1 * 0.125;\n",
}

IDENTITIES = {
    "self": "{v} = {v};",
    "plus": "{v} = +{v};",
    "comma": "{v} = ({v}, {v});",
    "addzero": "{v} = {v} + 0.0;",
    "subzero": "{v} = {v} - 0.0;",
    "negneg": "{v} = -(-{v});",
}


def make(
    merge_names: tuple[str, ...],
    identity: str,
    variables: tuple[str, ...],
    count: int,
) -> str:
    source = MERGE["make"](merge_names)
    for variable in variables:
        anchor = ANCHORS[variable]
        addition = "".join(
            "        " + IDENTITIES[identity].format(v=variable) + "\n"
            for _ in range(count)
        )
        source = source.replace(anchor, anchor + addition, 1)
    return source


def evaluate(case: tuple) -> tuple:
    merge_names, identity, variables, count = case
    merge_tag = "-".join(merge_names) if merge_names else "base"
    tag = f"{merge_tag}_{identity}_{''.join(variables)}_{count}"
    source = make(merge_names, identity, variables, count)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_f64_priority_combine_{tag}.o"
    )
    return tag, source, result


def main() -> None:
    cases = [
        (merge_names, identity, variables, count)
        for merge_names in MERGES
        for identity in IDENTITIES
        for size in (1, 2, 3)
        for variables in itertools.combinations(("d0", "d1", "d2"), size)
        for count in (1, 2)
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))

    ranked = sorted(
        rows,
        key=lambda row: (
            row[2].get("f20_operands", 0) == 0,
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        ),
    )
    for tag, source, result in ranked[:120]:
        if result.get("f20_operands", 0) > 0 and (
            result.get("f18", 0) > 80 or result.get("insns") <= 2628
        ):
            with open(
                f"/tmp/codex_f64_priority_combine_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(tag, ORACLE["concise"](result), result.get("fp"))
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[2].get("f20_operands", 0) > 0 for row in rows),
        "scratch_like",
        sum(
            row[2].get("f20_operands", 0) > 0
            and row[2].get("f18", 0) > 100
            for row in rows
        ),
    )


if __name__ == "__main__":
    main()
