#!/usr/bin/env python3
"""Use the early zero stores as optimizer-erased FP allocator pressure."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
TARGET = ORACLE["TARGET_INSNS"]
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANCHORS = (
    "    D_8011D550 = 0;\n",
    "    D_8011D558 = 0;\n",
)
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


def make(assignments: tuple[str | None, str | None]) -> str:
    source = BASE
    for anchor, value in zip(ANCHORS, assignments):
        if value is not None:
            source = source.replace(
                anchor,
                anchor.replace("0;", f"({value} > 0.0f) * 0;"),
                1,
            )
    return source


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def evaluate(assignments: tuple[str | None, str | None]) -> tuple:
    tag = "_".join(value or "plain" for value in assignments)
    source = make(assignments)
    path = f"/tmp/codex_early_fakematch_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_early_fakematch_{tag}_natural.o"
    )
    forced = STICK["forced"](path, f"early_fakematch_{tag}")
    obj = f"/tmp/codex_stickform_early_fakematch_{tag}_forced.o"
    prefix = fp_prefix(obj) if forced.get("ok") else -1
    return tag, natural, forced, prefix


def main() -> None:
    assignments = [(value, None) for value in FLOATS]
    assignments += [(None, value) for value in FLOATS]
    rows = [evaluate(item) for item in assignments]
    changed = {
        value
        for item, (_, natural, _, _) in zip(assignments, rows)
        for value in item
        if value is not None and natural.get("sha1") != "28ae550756b5"
    }
    if not changed:
        changed = set(FLOATS)
    for pair in itertools.product(sorted(changed), repeat=2):
        rows.append(evaluate(pair))
    for tag, natural, forced, prefix in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[3],
            row[2].get("mismatch", 9999),
            row[0],
        ),
    ):
        if (
            natural.get("f20_operands", 0) > 0
            or prefix == len(TARGET)
            or natural.get("sha1") != "28ae550756b5"
        ):
            print(
                tag,
                "prefix",
                prefix,
                "natural",
                ORACLE["concise"](natural),
                "forced",
                forced,
            )
    print("tested", len(rows), "changed", sorted(changed))


if __name__ == "__main__":
    main()
