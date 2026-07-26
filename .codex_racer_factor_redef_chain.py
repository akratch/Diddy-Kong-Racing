#!/usr/bin/env python3
"""Join disjoint factor definitions with optimizer-erased old-value reads."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
LINES = (
    "                var_f20 = racer->velocity * var_t0 * 0.00015;\n",
    "            var_f20 = racer->velocity * spD8 * 8.0f;\n",
    "            var_f20 = spEC * spD8;\n",
    "    var_f20 = racer->lateral_velocity * racer->lateral_velocity * spD4;\n",
    "            var_f20 = coss_f(racer->x_rotation_vel) * spEC * racer->trickType;\n",
    "            var_f20 = sins_f(racer->x_rotation_vel) * spEC * racer->trickType * 1.5;\n",
    "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n",
    "        var_f20 = obj->x_velocity;\n",
    "        var_f20 = (obj->trans.x_position - spE8 - D_8011D548) * var_f0;\n",
)
FORMS = (
    "add_after",
    "add_before",
    "ternary",
    "comma",
    "comma_zero",
    "self_comma",
    "mul_one",
)


def rewrite(line: str, form: str) -> str:
    match = re.fullmatch(r"(\s*)var_f20 = (.+);\n", line)
    if not match:
        raise ValueError(line)
    indent, expression = match.groups()
    comparison = "(var_f20 > 0.0f)"
    zero = f"({comparison} * 0)"
    if form == "add_after":
        rhs = f"({expression}) + {zero}"
    elif form == "add_before":
        rhs = f"{zero} + ({expression})"
    elif form == "ternary":
        rhs = f"{comparison} ? ({expression}) : ({expression})"
    elif form == "comma":
        rhs = f"({comparison}, ({expression}))"
    elif form == "comma_zero":
        rhs = f"({zero}, ({expression}))"
    elif form == "self_comma":
        rhs = f"(var_f20 = var_f20, ({expression}))"
    elif form == "mul_one":
        rhs = f"({expression}) * (1.0f + {zero})"
    else:
        raise ValueError(form)
    return f"{indent}var_f20 = {rhs};\n"


def apply(indices: tuple[int, ...], form: str) -> str:
    source = BASE
    for index in indices:
        line = LINES[index]
        if source.count(line) != 1:
            raise ValueError((index, source.count(line), line))
        source = source.replace(line, rewrite(line, form), 1)
    return source


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def evaluate(indices: tuple[int, ...], form: str) -> tuple:
    tag = f"{form}_{'-'.join(map(str, indices))}"
    source = apply(indices, form)
    path = f"/tmp/codex_factor_redef_chain_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_factor_redef_chain_{tag}.o"
    )
    forced = STICK["forced"](path, f"factor_redef_chain_{tag}")
    obj = f"/tmp/codex_stickform_factor_redef_chain_{tag}_forced.o"
    prefix = fp_prefix(obj) if forced.get("ok") else -1
    return tag, natural, forced, prefix


def main() -> None:
    cases = []
    for form in FORMS:
        cases += [((index,), form) for index in range(len(LINES))]
        cases += [
            (tuple(range(end)), form)
            for end in range(2, len(LINES) + 1)
        ]
    # Focused cross-call joins: the first definition, the top-speed boundary,
    # and the three call-return definitions in the final drag/tail.
    unique = {}
    for indices, form in cases:
        unique[(indices, form)] = evaluate(indices, form)
    rows = list(unique.values())
    for tag, natural, forced, prefix in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[3],
            row[2].get("mismatch", 9999),
            abs(row[1].get("insns", 9999) - len(TARGET)),
            row[0],
        ),
    ):
        if (
            natural.get("f20_operands", 0) > 0
            or prefix == len(TARGET)
            or natural.get("f18", 0) > 100
        ):
            print(
                tag,
                "prefix",
                prefix,
                "natural",
                ORACLE["concise"](natural),
                natural.get("fp"),
                "forced",
                forced,
            )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[1].get("f20_operands", 0) > 0 for row in rows),
        "forced_exact",
        sum(row[3] == len(TARGET) for row in rows),
    )


if __name__ == "__main__":
    main()
