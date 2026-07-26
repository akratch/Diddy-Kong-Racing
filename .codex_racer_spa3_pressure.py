#!/usr/bin/env python3
"""Carry short FP ranges to the real spA3 zero store, without a fake FP add."""

from __future__ import annotations

import itertools
import pathlib
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
SQRT_END = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
STORE = "    spA3 = FALSE;\n"
FIELDS = (
    "obj->x_velocity",
    "obj->z_velocity",
    "obj->y_velocity",
    "obj->trans.x_position",
    "obj->trans.y_position",
    "obj->trans.z_position",
    "racer->velocity",
    "racer->ox1",
)


def zero_expr(names: tuple[str, ...], form: str) -> str:
    comparisons = [f"({name} > 0.0f)" for name in names]
    if form == "sum_mul":
        return f"({' + '.join(comparisons)}) * 0"
    if form == "sum_and":
        return f"({' + '.join(comparisons)}) & 0"
    if form == "comma":
        return f"({', '.join(comparisons)}, FALSE)"
    if form == "ternary":
        condition = " || ".join(comparisons)
        return f"({condition}) ? FALSE : FALSE"
    raise ValueError(form)


def fresh_case(count: int, scope: str, form: str, source_values: str) -> str:
    names = tuple(f"press{i}" for i in range(count))
    declarations = "".join(f"        f32 {name};\n" for name in names)
    if source_values == "post_fields":
        assignments = "".join(
            f"        {name} = {FIELDS[i]};\n"
            for i, name in enumerate(names)
        )
        insertion = assignments
    elif source_values == "pre_inputs":
        assignments = "".join(
            f"        {name} = {FIELDS[i % 3]};\n"
            for i, name in enumerate(names)
        )
        insertion = assignments
    else:
        raise ValueError(source_values)

    source = BASE
    if scope == "block":
        if source_values == "post_fields":
            source = source.replace(
                SQRT_END,
                SQRT_END + "    {\n" + declarations + insertion,
                1,
            )
        else:
            source = source.replace(
                SQRT_END,
                "    {\n" + declarations + insertion + SQRT_END.replace(
                    "    ", "        "
                ),
                1,
            )
        source = source.replace(
            STORE,
            f"        spA3 = {zero_expr(names, form)};\n"
            "    }\n",
            1,
        )
    elif scope == "function":
        source = source.replace(
            "    f32 segmentXVelocity;\n",
            "    f32 segmentXVelocity;\n"
            + "".join(f"    f32 {name};\n" for name in names),
            1,
        )
        if source_values == "post_fields":
            source = source.replace(SQRT_END, SQRT_END + insertion.replace("        ", "    "), 1)
        else:
            source = source.replace(SQRT_END, insertion.replace("        ", "    ") + SQRT_END, 1)
        source = source.replace(
            STORE,
            f"    spA3 = {zero_expr(names, form)};\n",
            1,
        )
    else:
        raise ValueError(scope)
    return source


def main() -> None:
    rows = []
    cases = itertools.product(
        range(1, 9),
        ("block", "function"),
        ("sum_mul", "sum_and", "comma", "ternary"),
        ("post_fields", "pre_inputs"),
    )
    for serial, (count, scope, form, source_values) in enumerate(cases):
        tag = f"{serial:03d}_{count}_{scope}_{form}_{source_values}"
        source = fresh_case(count, scope, form, source_values)
        path = pathlib.Path(f"/tmp/codex_spa3_pressure_{tag}.c")
        path.write_text(source, encoding="utf-8")
        result = ORACLE["evaluate"](source, keep=str(path.with_suffix(".o")))
        rows.append(
            (
                not bool(result.get("f20_operands", 0)),
                int(result.get("norm", 9999)),
                abs(int(result.get("insns", 9999)) - 2625),
                tag,
                result,
                path,
            )
        )
    for _, _, _, tag, result, path in sorted(rows):
        print(tag, ORACLE["concise"](result), result.get("fp"), path)


if __name__ == "__main__":
    main()
