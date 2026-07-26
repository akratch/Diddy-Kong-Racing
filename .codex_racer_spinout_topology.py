#!/usr/bin/env python3
"""Recover the three-register topology of the spinout rotation block."""

from __future__ import annotations

import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
TARGET = ORACLE["TARGET_INSNS"]
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"
DECL = "    s32 xRotationOffset;\n"
OLD = """\
        xRotationOffset = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (xRotationOffset > 0x8000) {
            xRotationOffset -= 0xFFFF;
        }
        if (xRotationOffset < -0x8000) {
            xRotationOffset += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (xRotationOffset * updateRate) >> 4;
"""


def offset_form(name: str) -> str:
    return f"""\
        {name} = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if ({name} > 0x8000) {{
            {name} -= 0xFFFF;
        }}
        if ({name} < -0x8000) {{
            {name} += 0xFFFF;
        }}
        obj->trans.rotation.x_rotation += ({name} * updateRate) >> 4;
"""


def offset_condition_form(
    name: str,
    high_condition: str,
    high_update: str,
    low_condition: str,
    low_update: str,
    final_expression: str = "({name} * updateRate) >> 4",
) -> str:
    return f"""\
        {name} = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if ({high_condition.format(name=name)}) {{
            {high_update.format(name=name)};
        }}
        if ({low_condition.format(name=name)}) {{
            {low_update.format(name=name)};
        }}
        obj->trans.rotation.x_rotation += {final_expression.format(name=name)};
"""


def two_value_form(original: str, offset: str, final: str) -> str:
    statement = (
        "obj->trans.rotation.x_rotation = "
        f"{original} + (({offset} * updateRate) >> 4);"
        if final == "assign"
        else "obj->trans.rotation.x_rotation += "
        f"({offset} * updateRate) >> 4;"
    )
    return f"""\
        {original} = obj->trans.rotation.x_rotation;
        {offset} = 0xD800 - ({original} & 0xFFFF);
        if ({offset} > 0x8000) {{
            {offset} -= 0xFFFF;
        }}
        if ({offset} < -0x8000) {{
            {offset} += 0xFFFF;
        }}
        {statement}
"""


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def make_cases() -> list[tuple[str, str]]:
    rows = [("baseline", BASE)]
    for offset in (
        "pad5",
        "pad7",
        "racerMiscAssetIdx",
        "racerSteerAngle",
        "var_v0",
        "var_v1",
        "var_a0",
        "var_t0",
        "temp_t7",
        "pad2",
        "i",
        "var_t9",
        "racerTrickType",
        "pad4",
        "steerVisualRotationOffset",
        "zRotationOffset",
    ):
        rows.append((f"offset_{offset}", BASE.replace(OLD, offset_form(offset), 1)))

    for tag, high_condition, high_update, low_condition, low_update in (
        (
            "reversed_comparisons",
            "0x8000 < {name}",
            "{name} -= 0xFFFF",
            "-0x8000 > {name}",
            "{name} += 0xFFFF",
        ),
        (
            "inclusive_thresholds",
            "{name} >= 0x8001",
            "{name} -= 0xFFFF",
            "{name} <= -0x8001",
            "{name} += 0xFFFF",
        ),
        (
            "negated_thresholds",
            "!({name} < 0x8001)",
            "{name} -= 0xFFFF",
            "!({name} >= -0x8000)",
            "{name} += 0xFFFF",
        ),
        (
            "negative_updates",
            "{name} > 0x8000",
            "{name} += -0xFFFF",
            "{name} < -0x8000",
            "{name} -= -0xFFFF",
        ),
    ):
        rows.append(
            (
                f"offset_var_v1_{tag}",
                BASE.replace(
                    OLD,
                    offset_condition_form(
                        "var_v1",
                        high_condition,
                        high_update,
                        low_condition,
                        low_update,
                    ),
                    1,
                ),
            )
        )

    for tag, final_expression in (
        ("multiply_reversed", "(updateRate * {name}) >> 4"),
        ("multiply_parenthesized", "(({name}) * (updateRate)) >> 4"),
        ("shift_product_parenthesized", "(({name} * updateRate) >> 4)"),
    ):
        rows.append(
            (
                f"offset_var_v1_{tag}",
                BASE.replace(
                    OLD,
                    offset_condition_form(
                        "var_v1",
                        "{name} > 0x8000",
                        "{name} -= 0xFFFF",
                        "{name} < -0x8000",
                        "{name} += 0xFFFF",
                        final_expression,
                    ),
                    1,
                ),
            )
        )

    rows.append(
        (
            "offset_var_v1_explicit_final",
            BASE.replace(
                OLD,
                offset_form("var_v1").replace(
                    "obj->trans.rotation.x_rotation += (var_v1 * updateRate) >> 4;",
                    "obj->trans.rotation.x_rotation = obj->trans.rotation.x_rotation + "
                    "((var_v1 * updateRate) >> 4);",
                ),
                1,
            ),
        )
    )
    rows.append(
        (
            "offset_var_v1_self_use",
            BASE.replace(
                OLD,
                offset_form("var_v1").replace(
                    "        if (var_v1 > 0x8000) {",
                    "        var_v1 = +var_v1;\n"
                    "        if (var_v1 > 0x8000) {",
                ),
                1,
            ),
        )
    )
    for tag, fake in (
        ("empty_if_zero", "if (!var_v1) {}"),
        ("empty_if_nonzero", "if (var_v1) {}"),
        ("empty_if_positive", "if (var_v1 > 0) {}"),
        ("empty_if_negative", "if (var_v1 < 0) {}"),
        ("void_use", "(void) var_v1;"),
        ("self_assign_statement", "var_v1 = var_v1;"),
        ("self_add_zero_statement", "var_v1 += 0;"),
        ("conditional_self_add", "if (var_v1 > 0) { var_v1 += 0; }"),
    ):
        for position, needle in (
            (
                "after_definition",
                "        if (var_v1 > 0x8000) {\n",
            ),
            (
                "before_low",
                "        if (var_v1 < -0x8000) {\n",
            ),
            (
                "before_final",
                "        obj->trans.rotation.x_rotation += "
                "(var_v1 * updateRate) >> 4;\n",
            ),
        ):
            rows.append(
                (
                    f"offset_var_v1_{tag}_{position}",
                    BASE.replace(
                        OLD,
                        offset_form("var_v1").replace(
                            needle,
                            f"        {fake}\n" + needle,
                            1,
                        ),
                        1,
                    ),
                )
            )

    for tag, fake in (
        ("rotation_empty_if_zero", "if (!obj->trans.rotation.x_rotation) {}"),
        ("rotation_empty_if_nonzero", "if (obj->trans.rotation.x_rotation) {}"),
        (
            "rotation_empty_if_positive",
            "if (obj->trans.rotation.x_rotation > 0) {}",
        ),
        (
            "rotation_empty_if_negative",
            "if (obj->trans.rotation.x_rotation < 0) {}",
        ),
        ("rotation_void_use", "(void) obj->trans.rotation.x_rotation;"),
    ):
        for position, needle in (
            (
                "before_definition",
                "        var_v1 = 0xD800 - "
                "(obj->trans.rotation.x_rotation & 0xFFFF);\n",
            ),
            (
                "after_definition",
                "        if (var_v1 > 0x8000) {\n",
            ),
            (
                "before_final",
                "        obj->trans.rotation.x_rotation += "
                "(var_v1 * updateRate) >> 4;\n",
            ),
        ):
            rows.append(
                (
                    f"offset_var_v1_{tag}_{position}",
                    BASE.replace(
                        OLD,
                        offset_form("var_v1").replace(
                            needle,
                            f"        {fake}\n" + needle,
                            1,
                        ),
                        1,
                    ),
                )
            )

    fresh_function = BASE.replace(DECL, DECL + "    s32 spinOffset;\n", 1)
    rows.append(
        (
            "offset_fresh_function",
            fresh_function.replace(OLD, offset_form("spinOffset"), 1),
        )
    )
    rows.append(
        (
            "offset_fresh_block",
            BASE.replace(
                OLD,
                "        {\n            s32 spinOffset;\n"
                + offset_form("spinOffset").replace("        ", "            ")
                + "        }\n",
                1,
            ),
        )
    )

    originals = ("var_v0", "var_v1", "var_a0", "var_t0", "temp_t7")
    offsets = ("xRotationOffset", "var_v0", "var_v1", "var_a0")
    for original in originals:
        for offset in offsets:
            if original == offset:
                continue
            for final in ("assign", "compound"):
                rows.append(
                    (
                        f"two_{original}_{offset}_{final}",
                        BASE.replace(
                            OLD,
                            two_value_form(original, offset, final),
                            1,
                        ),
                    )
                )

    for scope in ("function", "block"):
        for final in ("assign", "compound"):
            if scope == "function":
                source = BASE.replace(
                    DECL,
                    DECL + "    s32 spinOriginal;\n    s32 spinOffset;\n",
                    1,
                ).replace(
                    OLD,
                    two_value_form("spinOriginal", "spinOffset", final),
                    1,
                )
            else:
                body = two_value_form("spinOriginal", "spinOffset", final)
                source = BASE.replace(
                    OLD,
                    "        {\n"
                    "            s32 spinOriginal;\n"
                    "            s32 spinOffset;\n"
                    + body.replace("        ", "            ")
                    + "        }\n",
                    1,
                )
            rows.append((f"fresh_{scope}_{final}", source))
    return rows


def main() -> None:
    for serial, (tag, source) in enumerate(make_cases()):
        path = pathlib.Path(f"/tmp/codex_spinout_topology_{serial:03d}_{tag}.c")
        obj = path.with_suffix(".o")
        trace = path.with_suffix(".trace")
        path.write_text(source, encoding="utf-8")
        proc = subprocess.run(
            [FORCED_RUNNER, str(path), str(obj), str(trace)],
            check=False,
            capture_output=True,
            text=True,
        )
        if proc.returncode != 0:
            print(tag, "compile", proc.returncode)
            continue
        _, candidate = ORACLE["dump_object"](str(obj))
        reg_bad = [
            index
            for index, (expected, actual) in enumerate(zip(TARGET, candidate))
            if registers(expected[1]) != registers(actual[1])
        ]
        region_bad = [
            index for index in reg_bad if 1160 <= index <= 1210
        ]
        print(
            tag,
            "insns",
            len(candidate),
            "reg_bad",
            len(reg_bad) + abs(len(TARGET) - len(candidate)),
            "spin_bad",
            len(region_bad),
            "spin_indices",
            ",".join(map(str, region_bad)) or "-",
        )


if __name__ == "__main__":
    main()
