#!/usr/bin/env python3
"""Seed f20 with erased pressure that dies before the real factor web."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
VALUES = (
    "obj->x_velocity * obj->x_velocity",
    "obj->y_velocity * obj->y_velocity",
    "obj->z_velocity * obj->z_velocity",
    "racer->velocity * racer->velocity",
    "racer->lateral_velocity * racer->lateral_velocity",
)
HOST_SETS = (
    ("spCC", "var_f6", "segmentXVelocity"),
    ("spCC", "var_f6", "segmentXVelocity", "spD4"),
    ("spCC", "var_f6", "segmentXVelocity", "spD4", "spD0"),
    ("spCC", "var_f6", "segmentXVelocity", "spD4", "spD0", "spD8"),
)


def anchor_occurrences() -> list[tuple[str, int, str]]:
    specs = (
        ("drift", "            racer->drift_direction = 0;\n"),
        ("spa2", "            spA2 = FALSE;\n"),
        ("d550", "    D_8011D550 = 0;\n"),
        ("d558", "    D_8011D558 = 0;\n"),
    )
    anchors = []
    for name, line in specs:
        count = BASE.count(line)
        for occurrence in range(count):
            anchors.append((f"{name}{occurrence}", occurrence, line))
    return anchors


def replace_occurrence(
    source: str, line: str, occurrence: int, replacement: str
) -> str:
    parts = source.split(line)
    if occurrence >= len(parts) - 1:
        raise ValueError((line, occurrence))
    return line.join(parts[: occurrence + 1]) + replacement + line.join(
        parts[occurrence + 1 :]
    )


def expression(hosts: tuple[str, ...], form: str) -> str:
    assignments = [
        f"{host} = {VALUES[index % len(VALUES)]}"
        for index, host in enumerate(hosts)
    ]
    sum_l = " + ".join(hosts)
    if form == "comma":
        return f"({', '.join(assignments)}, ({sum_l}) > 0.0f) * 0"
    if form == "embedded":
        terms = [
            f"({host} = {VALUES[index % len(VALUES)]})"
            for index, host in enumerate(hosts)
        ]
        return f"(({' + '.join(terms)}) > 0.0f) * 0"
    if form == "weighted":
        repeated = " + ".join(
            host for host in hosts for _ in range(4)
        )
        return f"({', '.join(assignments)}, ({repeated}) > 0.0f) * 0"
    raise ValueError(form)


def make(anchor: tuple[str, int, str], hosts: tuple[str, ...], form: str) -> str:
    _, occurrence, line = anchor
    lhs = line.split("=", 1)[0]
    replacement = f"{lhs}= {expression(hosts, form)};\n"
    return replace_occurrence(BASE, line, occurrence, replacement)


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    rows = []
    for anchor in anchor_occurrences():
        for hosts in HOST_SETS:
            orders = [hosts]
            if len(hosts) <= 4:
                orders = list(itertools.permutations(hosts))
            for order in orders:
                for form in ("comma", "embedded", "weighted"):
                    tag = (
                        f"{anchor[0]}_{form}_{'-'.join(order)}"
                    )
                    source = make(anchor, order, form)
                    path = f"/tmp/codex_prefactor_phantom_{tag}.c"
                    with open(path, "w", encoding="utf-8") as output:
                        output.write(source)
                    natural = ORACLE["evaluate"](
                        source, keep=f"/tmp/codex_prefactor_phantom_{tag}.o"
                    )
                    prefix = fp_prefix(
                        f"/tmp/codex_prefactor_phantom_{tag}.o"
                    ) if natural.get("ok") else -1
                    rows.append((tag, natural, prefix))

    for tag, result, prefix in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[1].get("f18", 0),
            -row[2],
            abs(row[1].get("insns", 9999) - len(TARGET)),
            row[0],
        ),
    ):
        if result.get("f20_operands", 0) > 0 or result.get("f18", 0) > 100:
            print(
                tag,
                "prefix",
                prefix,
                ORACLE["concise"](result),
                result.get("fp"),
            )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(result.get("f20_operands", 0) > 0 for _, result, _ in rows),
    )


if __name__ == "__main__":
    main()
