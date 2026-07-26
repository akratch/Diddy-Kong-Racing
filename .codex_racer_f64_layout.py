#!/usr/bin/env python3
"""Recover frame/layout around the promising four-stage f64 expression."""

from __future__ import annotations

import itertools
import runpy
import re
import collections


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = "/tmp/codex_layout_exact.c"
TARGET_STACK = collections.Counter(
    (
        assembly.split()[0],
        tuple(int(value) for value in re.findall(r"(-?\d+)\((?:\$)?sp\)", assembly)),
    )
    for _, assembly in ORACLE["TARGET_INSNS"]
    if re.search(r"(-?\d+)\((?:\$)?sp\)", assembly)
)

OLD_EXPR = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""
NEW_EXPR = """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
"""

REPLACED = (
    "spCC",
    "var_f6",
    "segmentXVelocity",
    "pad4",
)
REMOVABLE = (
    "pad5",
    "pad7",
    "newSpinoutTimer",
    "pad2",
    "zRotationOffset",
    "var_t9",
    "racerTrickType",
)


def remove_declaration(source: str, name: str) -> str:
    pattern = rf"^    [^\n;]*\b{re.escape(name)};\n"
    source, count = re.subn(pattern, "", source, count=1, flags=re.MULTILINE)
    if count != 1:
        raise ValueError(f"could not remove declaration for {name}")
    return source


def base_without(names: tuple[str, ...]) -> str:
    source = open(BASE_PATH, encoding="utf-8").read()
    for name in REPLACED + names:
        source = remove_declaration(source, name)
    if source.count(OLD_EXPR) != 1:
        raise ValueError("forwardVel expression not unique")
    return source.replace(OLD_EXPR, NEW_EXPR, 1)


def declaration_lines(source: str) -> list[str]:
    function = source[source.index("void func_80049794"):]
    head = function[:function.index("\n\n    if (func_8000E138())")]
    return [
        line + "\n"
        for line in head.splitlines()[1:]
        if re.match(r"^    [A-Za-z_]", line)
    ]


def insert_after(source: str, anchor: str) -> str:
    declaration = "    f64 d0;\n    f64 d1;\n    f64 d2;\n    f64 d3;\n"
    if source.count(anchor) != 1:
        raise ValueError(f"anchor not unique: {anchor!r}")
    return source.replace(anchor, anchor + declaration, 1)


def metric(source: str, tag: str) -> dict[str, object]:
    obj = f"/tmp/codex_f64layout_{tag}.o"
    result = ORACLE["evaluate"](source, keep=obj)
    if result.get("ok"):
        _, instructions = ORACLE["dump_object"](obj)
        candidate_stack = collections.Counter(
            (
                assembly.split()[0],
                tuple(
                    int(value)
                    for value in re.findall(r"(-?\d+)\((?:\$)?sp\)", assembly)
                ),
            )
            for _, assembly in instructions
            if re.search(r"(-?\d+)\((?:\$)?sp\)", assembly)
        )
        result["stack_distance"] = sum(
            (TARGET_STACK - candidate_stack).values()
        ) + sum((candidate_stack - TARGET_STACK).values())
    with open(f"/tmp/codex_f64layout_{tag}.c", "w", encoding="utf-8") as output:
        output.write(source)
    return result


def main() -> None:
    rows = []
    for names in itertools.combinations(REMOVABLE, 6):
        source = base_without(names)
        for index, anchor in enumerate(declaration_lines(source)):
            tag = "remove_" + "_".join(names) + f"_anchor{index}"
            candidate = insert_after(source, anchor)
            result = metric(candidate, tag)
            rows.append((result.get("stack_distance", 10**9), tag, anchor, result))
    for stack_distance, tag, anchor, result in sorted(rows)[:30]:
        print(
            tag,
            "after", anchor.strip(),
            ORACLE["concise"](result),
            f"stack_distance={stack_distance}",
        )


if __name__ == "__main__":
    main()
