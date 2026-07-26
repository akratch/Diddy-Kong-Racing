#!/usr/bin/env python3
"""Focused natural-allocation experiments for the remaining racer GPR diffs."""

from __future__ import annotations

import collections
import concurrent.futures
import os
import pathlib
import re
import runpy
import sys


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
TARGET = ORACLE["TARGET_INSNS"]
BASE_PATH = pathlib.Path(
    os.environ.get("CODEX_GPR_BASE", "/tmp/codex_gpr_natural_combined.c")
)
BASE = BASE_PATH.read_text(encoding="utf-8")
EXPECTED_FP = {
    "f0": 131,
    "f2": 66,
    "f4": 188,
    "f6": 188,
    "f8": 187,
    "f10": 188,
    "f12": 62,
    "f14": 50,
    "f16": 8,
    "f18": 190,
    "f20": 74,
    "f21": 2,
}
REGISTER_RE = re.compile(
    r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)"
)


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"replacement anchor occurs {count} times:\n{old}")
    return source.replace(old, new, 1)


def evaluate(name: str, source: str, *, keep: bool = False) -> dict[str, object]:
    obj_path = f"/tmp/codex_gpr_final_{name}.o"
    result = ORACLE["evaluate"](source, keep=obj_path)
    if not result.get("ok"):
        print(name, ORACLE["concise"](result))
        return result
    if keep:
        pathlib.Path(f"/tmp/codex_gpr_final_{name}.c").write_text(
            source, encoding="utf-8"
        )
    _, candidate = ORACLE["dump_object"](obj_path)
    result["reg_bad"] = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    result["word_bad"] = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if expected[0] != actual[0]
    ]
    result["fp_exact"] = result.get("fp") == EXPECTED_FP
    print(
        name,
        ORACLE["concise"](result),
        f"fp_exact={result['fp_exact']}",
        f"reg={len(result['reg_bad'])}",
        (
            result["reg_bad"]
            if len(result["reg_bad"]) <= 100
            else result["reg_bad"][:20] + ["..."]
        ),
    )
    return result
def equality_campaign() -> None:
    old = """\
    var_v0 = racer->playerIndex;
    if ((var_v0 == PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
"""
    variants = {
        "base": old,
        "equal_reverse": """\
    var_v0 = racer->playerIndex;
    if ((PLAYER_COMPUTER == var_v0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "not_equal_false": """\
    var_v0 = racer->playerIndex;
    if (!(var_v0 != PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "not_equal_reverse_false": """\
    var_v0 = racer->playerIndex;
    if (!(PLAYER_COMPUTER != var_v0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "direct": """\
    if ((racer->playerIndex == PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "direct_reverse": """\
    if ((PLAYER_COMPUTER == racer->playerIndex) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "direct_not_equal_false": """\
    if (!(racer->playerIndex != PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "direct_not_equal_reverse_false": """\
    if (!(PLAYER_COMPUTER != racer->playerIndex) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "demorgan": """\
    var_v0 = racer->playerIndex;
    if (!((var_v0 != PLAYER_COMPUTER) || (gCurrentPlayerIndex == PLAYER_COMPUTER))) {
""",
        "sub_zero": """\
    var_v0 = racer->playerIndex;
    if (((var_v0 - PLAYER_COMPUTER) == 0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "reverse_sub_zero": """\
    var_v0 = racer->playerIndex;
    if (((PLAYER_COMPUTER - var_v0) == 0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
        "xor_zero": """\
    var_v0 = racer->playerIndex;
    if (((var_v0 ^ PLAYER_COMPUTER) == 0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
""",
    }
    for name, replacement in variants.items():
        evaluate(name, replace_once(BASE, old, replacement), keep=True)
    whole_old = old + """\
        gCurrentRacerHandlingStat = 1.4f;
    }
"""
    whole_variants = {
        "nested": """\
    var_v0 = racer->playerIndex;
    if (var_v0 == PLAYER_COMPUTER) {
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCurrentRacerHandlingStat = 1.4f;
        }
    }
""",
        "nested_no_brace": """\
    var_v0 = racer->playerIndex;
    if (var_v0 == PLAYER_COMPUTER)
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCurrentRacerHandlingStat = 1.4f;
        }
""",
        "else_form": """\
    var_v0 = racer->playerIndex;
    if (var_v0 != PLAYER_COMPUTER) {
    } else if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    }
    for name, replacement in whole_variants.items():
        evaluate(name, replace_once(BASE, whole_old, replacement), keep=True)


def wave_campaign() -> None:
    old = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""
    declaration_anchor = "    s32 pad4;\n"
    declaration_sets = {
        "one": "    s32 waveEnd;\n",
        "two": "    s32 waveEnd;\n    s32 waveIndex;\n",
        "two_reverse": "    s32 waveIndex;\n    s32 waveEnd;\n",
    }
    bodies = {
        "end_for_cached": """\
        waveEnd = gRacerWaveCount - 1;
        for (var_a0 = waveEnd;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == waveEnd) {
            var_a0--;
        }
""",
        "end_for_reload": """\
        waveEnd = gRacerWaveCount - 1;
        for (var_a0 = waveEnd;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "end_chain_left": """\
        waveEnd = var_a0 = gRacerWaveCount - 1;
        for (;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == waveEnd) {
            var_a0--;
        }
""",
        "end_chain_right": """\
        var_a0 = waveEnd = gRacerWaveCount - 1;
        for (;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == waveEnd) {
            var_a0--;
        }
""",
        "index_for_reload": """\
        for (waveIndex = gRacerWaveCount - 1;
             waveIndex >= 0 && gRacerCurrentWave[waveIndex]->waveHeight < obj->trans.y_position + 5; waveIndex--) {}

        if (waveIndex == gRacerWaveCount - 1) {
            waveIndex--;
        }
""",
        "two_for_cached": """\
        waveEnd = gRacerWaveCount - 1;
        for (waveIndex = waveEnd;
             waveIndex >= 0 && gRacerCurrentWave[waveIndex]->waveHeight < obj->trans.y_position + 5; waveIndex--) {}

        if (waveIndex == waveEnd) {
            waveIndex--;
        }
""",
        "two_chain_left": """\
        waveEnd = waveIndex = gRacerWaveCount - 1;
        for (;
             waveIndex >= 0 && gRacerCurrentWave[waveIndex]->waveHeight < obj->trans.y_position + 5; waveIndex--) {}

        if (waveIndex == waveEnd) {
            waveIndex--;
        }
""",
        "two_chain_right": """\
        waveIndex = waveEnd = gRacerWaveCount - 1;
        for (;
             waveIndex >= 0 && gRacerCurrentWave[waveIndex]->waveHeight < obj->trans.y_position + 5; waveIndex--) {}

        if (waveIndex == waveEnd) {
            waveIndex--;
        }
""",
    }
    for declaration_name, declarations in declaration_sets.items():
        for body_name, body in bodies.items():
            if "waveIndex" in body and declaration_name == "one":
                continue
            if "waveIndex" not in body and declaration_name != "one":
                continue
            source = replace_once(
                BASE,
                declaration_anchor,
                declaration_anchor + declarations,
            )
            source = replace_once(source, old, body)
            if "waveIndex" in body:
                source = replace_once(
                    source,
                    "        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;\n",
                    "        var_f2 = gRacerCurrentWave[waveIndex + 1]->waveHeight;\n",
                )
            evaluate(f"wave_{declaration_name}_{body_name}", source, keep=True)


def wave_host_campaign() -> None:
    old = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""
    loop_template = """\
        {prefix}for ({initial};
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{}}

        if ({comparison}) {{
            var_a0--;
        }}
"""
    hosts = (
        "pad5",
        "pad7",
        "racerMiscAssetIdx",
        "racerSteerAngle",
        "var_t0",
        "var_v0",
        "var_v1",
        "temp_t7",
        "pad2",
        "xRotationOffset",
        "zRotationOffset",
        "i",
        "var_t9",
        "racerTrickType",
        "steerVisualRotationOffset",
        "pad4",
    )
    shapes = {
        "nested_reload": (
            "",
            "var_a0 = ({host} = gRacerWaveCount - 1)",
            "var_a0 == gRacerWaveCount - 1",
        ),
        "nested_cached": (
            "",
            "var_a0 = ({host} = gRacerWaveCount - 1)",
            "var_a0 == {host}",
        ),
        "chain_host_first_reload": (
            "",
            "{host} = var_a0 = gRacerWaveCount - 1",
            "var_a0 == gRacerWaveCount - 1",
        ),
        "chain_host_first_cached": (
            "",
            "{host} = var_a0 = gRacerWaveCount - 1",
            "var_a0 == {host}",
        ),
        "chain_counter_first_reload": (
            "",
            "var_a0 = {host} = gRacerWaveCount - 1",
            "var_a0 == gRacerWaveCount - 1",
        ),
        "chain_counter_first_cached": (
            "",
            "var_a0 = {host} = gRacerWaveCount - 1",
            "var_a0 == {host}",
        ),
        "split_reload": (
            "{host} = gRacerWaveCount - 1;\n        ",
            "var_a0 = {host}",
            "var_a0 == gRacerWaveCount - 1",
        ),
        "split_cached": (
            "{host} = gRacerWaveCount - 1;\n        ",
            "var_a0 = {host}",
            "var_a0 == {host}",
        ),
        "compare_assign": (
            "",
            "var_a0 = gRacerWaveCount - 1",
            "var_a0 == ({host} = gRacerWaveCount - 1)",
        ),
    }
    for host in hosts:
        for shape_name, (prefix, initial, comparison) in shapes.items():
            body = loop_template.format(
                prefix=prefix.format(host=host),
                initial=initial.format(host=host),
                comparison=comparison.format(host=host),
            )
            source = replace_once(BASE, old, body)
            evaluate(f"wavehost_{host}_{shape_name}", source)


def wave_syntax_campaign() -> None:
    old = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""
    variants = {
        "while_and": """\
        var_a0 = gRacerWaveCount - 1;
        while (var_a0 >= 0 &&
               gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5) {
            var_a0--;
        }

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "for_body": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5;) {
            var_a0--;
        }

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "for_predec": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; --var_a0) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "while_reverse_float": """\
        var_a0 = gRacerWaveCount - 1;
        while (var_a0 >= 0 &&
               obj->trans.y_position + 5 > gRacerCurrentWave[var_a0]->waveHeight) {
            var_a0--;
        }

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "for_reverse_float": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && obj->trans.y_position + 5 > gRacerCurrentWave[var_a0]->waveHeight; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "while_break": """\
        var_a0 = gRacerWaveCount - 1;
        while (var_a0 >= 0) {
            if (!(gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5)) {
                break;
            }
            var_a0--;
        }

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "while_break_reverse": """\
        var_a0 = gRacerWaveCount - 1;
        while (var_a0 >= 0) {
            if (gRacerCurrentWave[var_a0]->waveHeight >= obj->trans.y_position + 5) {
                break;
            }
            var_a0--;
        }

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
    }
    for name, body in variants.items():
        evaluate(f"wavesyntax_{name}", replace_once(BASE, old, body), keep=True)


def wave_erased_use_campaign() -> None:
    old = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""
    end = "gRacerWaveCount - 1"
    empty_uses = {
        "truth": f"if ({end}) {{}}",
        "false": f"if (!({end})) {{}}",
        "eq_counter": f"if (({end}) == var_a0) {{}}",
        "ne_counter": f"if (({end}) != var_a0) {{}}",
        "self_eq": f"if (({end}) == ({end})) {{}}",
        "comma_truth": f"if ((({end}), 0)) {{}}",
        "void": f"(void) ({end});",
        "zero_mul": f"var_a0 += ({end}) * 0;",
        "zero_and": f"var_a0 += ({end}) & 0;",
        "zero_sub": f"var_a0 += ({end}) - ({end});",
        "zero_eq": f"var_a0 += (({end}) == ({end})) - 1;",
        "self_assign": "var_a0 = var_a0;",
    }
    templates = {
        "before": """\
        {use}
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{}}

        if (var_a0 == gRacerWaveCount - 1) {{
            var_a0--;
        }}
""",
        "body": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{
            {use}
        }}

        if (var_a0 == gRacerWaveCount - 1) {{
            var_a0--;
        }}
""",
        "after": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{}}

        {use}
        if (var_a0 == gRacerWaveCount - 1) {{
            var_a0--;
        }}
""",
        "inside": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{}}

        if (var_a0 == gRacerWaveCount - 1) {{
            {use}
            var_a0--;
        }}
""",
    }
    for placement, template in templates.items():
        for form, use in empty_uses.items():
            body = template.format(use=use)
            evaluate(
                f"waveerase_{placement}_{form}",
                replace_once(BASE, old, body),
                keep=True,
            )

    expression_variants = {
        "init_comma_duplicate": """\
        for (var_a0 = ((gRacerWaveCount - 1), (gRacerWaveCount - 1));
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "update_comma": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5;
             var_a0--, (gRacerWaveCount - 1)) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "condition_comma": """\
        for (var_a0 = gRacerWaveCount - 1;
             ((gRacerWaveCount - 1), var_a0 >= 0) &&
                 gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
        "compare_comma": """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (((gRacerWaveCount - 1), var_a0) == gRacerWaveCount - 1) {
            var_a0--;
        }
""",
    }
    for form, body in expression_variants.items():
        evaluate(
            f"waveerase_{form}",
            replace_once(BASE, old, body),
            keep=True,
        )


def wave_priority_source_campaign() -> None:
    old = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""
    comparisons = {
        "stick": "(gRacerWaveCount - 1) == gCurrentStickX",
        "steer": "(gRacerWaveCount - 1) == racerSteerAngle",
        "varv0": "(gRacerWaveCount - 1) == var_v0",
        "player": "(gRacerWaveCount - 1) == racer->playerIndex",
        "current": "(gRacerWaveCount - 1) == gCurrentPlayerIndex",
        "waveptr": "gRacerCurrentWave[var_a0] == NULL",
        "waveheight": (
            "gRacerCurrentWave[var_a0]->waveHeight == "
            "obj->trans.y_position"
        ),
    }
    for name, condition in comparisons.items():
        for count in range(1, 7):
            uses = "\n".join(
                f"            if ({condition}) {{}}" for _ in range(count)
            )
            body = f"""\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{
{uses}
        }}

        if (var_a0 == gRacerWaveCount - 1) {{
            var_a0--;
        }}
"""
            evaluate(
                f"wavepriority_{name}_{count}",
                replace_once(BASE, old, body),
                keep=True,
            )

    for end_count in range(1, 7):
        for wave_count in range(1, 4):
            uses = [
                "            if ((gRacerWaveCount - 1) == gCurrentStickX) {}"
            ] * end_count
            uses.extend(
                "            if (gRacerCurrentWave[var_a0] == NULL) {}"
                for _ in range(wave_count)
            )
            body = f"""\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{
{chr(10).join(uses)}
        }}

        if (var_a0 == gRacerWaveCount - 1) {{
            var_a0--;
        }}
"""
            evaluate(
                f"wavepriority_mix_{end_count}_{wave_count}",
                replace_once(BASE, old, body),
                keep=True,
            )


def steer_campaign() -> None:
    old = """\
                var_v1 = obj->trans.rotation.x_rotation;
                var_t0 = racerSteerAngle;
                racerSteerAngle = 0;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    racerSteerAngle = var_v1 - 0x3000;
                    if (racerSteerAngle > 0x1000) {
                        racerSteerAngle = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    racerSteerAngle = var_v1 + 0x3000;
                    if (racerSteerAngle < -0x1000) {
                        racerSteerAngle = -0x1000;
                    }
                    racerSteerAngle = -racerSteerAngle;
                }
                var_t0 *= (f32) (1.0 - ((f32) racerSteerAngle / 4096));
"""
    statement_orders = {
        "lmz": (
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
            "                var_t0 = racerSteerAngle;\n"
            "                racerSteerAngle = 0;\n"
        ),
        "mlz": (
            "                var_t0 = racerSteerAngle;\n"
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
            "                racerSteerAngle = 0;\n"
        ),
        "mzl": (
            "                var_t0 = racerSteerAngle;\n"
            "                racerSteerAngle = 0;\n"
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
        ),
    }
    conditions = {
        "field": "obj->trans.rotation.x_rotation > 0x3000",
        "local": "var_v1 > 0x3000",
        "local_reverse": "0x3000 < var_v1",
    }
    for order_name, statements in statement_orders.items():
        for condition_name, condition in conditions.items():
            body = statements + f"""\
                if ({condition}) {{
                    racerSteerAngle = var_v1 - 0x3000;
                    if (racerSteerAngle > 0x1000) {{
                        racerSteerAngle = 0x1000;
                    }}
                }} else if (var_v1 < -0x3000) {{
                    racerSteerAngle = var_v1 + 0x3000;
                    if (racerSteerAngle < -0x1000) {{
                        racerSteerAngle = -0x1000;
                    }}
                    racerSteerAngle = -racerSteerAngle;
                }}
                var_t0 *= (f32) (1.0 - ((f32) racerSteerAngle / 4096));
"""
            evaluate(
                f"steer_{order_name}_{condition_name}",
                replace_once(BASE, old, body),
                keep=True,
            )
    direct_orders = {
        "mz": (
            "                var_t0 = racerSteerAngle;\n"
            "                racerSteerAngle = 0;\n"
        ),
        "zm": (
            "                racerSteerAngle = 0;\n"
            "                var_t0 = racerSteerAngle;\n"
        ),
    }
    for order_name, statements in direct_orders.items():
        body = statements + """\
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    racerSteerAngle = obj->trans.rotation.x_rotation - 0x3000;
                    if (racerSteerAngle > 0x1000) {
                        racerSteerAngle = 0x1000;
                    }
                } else if (obj->trans.rotation.x_rotation < -0x3000) {
                    racerSteerAngle = obj->trans.rotation.x_rotation + 0x3000;
                    if (racerSteerAngle < -0x1000) {
                        racerSteerAngle = -0x1000;
                    }
                    racerSteerAngle = -racerSteerAngle;
                }
                var_t0 *= (f32) (1.0 - ((f32) racerSteerAngle / 4096));
"""
        evaluate(
            f"steer_direct_{order_name}",
            replace_once(BASE, old, body),
            keep=True,
        )
        grounded_local_source = replace_once(BASE, old, body)
        grounded_local_source = replace_once(
            grounded_local_source,
            "            if (racer->groundedWheels < 2) {\n",
            "            var_v1 = racer->groundedWheels;\n"
            "            if (var_v1 < 2) {\n",
        )
        evaluate(
            f"steer_groundlocal_direct_{order_name}",
            grounded_local_source,
            keep=True,
        )
    grounded_local_source = replace_once(
        BASE,
        "            if (racer->groundedWheels < 2) {\n",
        "            var_v1 = racer->groundedWheels;\n"
        "            if (var_v1 < 2) {\n",
    )
    evaluate("steer_groundlocal_explicit", grounded_local_source, keep=True)


def rotation_campaign() -> None:
    old = """\
            // Note: The following if/else has messed up t registers
            if (!(gCurrentRacerInput & R_TRIG)) {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }
"""
    damping_forms = {
        "explicit_assign": (
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
            "                obj->trans.rotation.x_rotation = "
            "var_v1 - ((var_v1 * updateRate) >> 4);\n"
        ),
        "explicit_compound": (
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
            "                obj->trans.rotation.x_rotation -= "
            "(var_v1 * updateRate) >> 4;\n"
        ),
        "direct_compound": (
            "                obj->trans.rotation.x_rotation -= "
            "(obj->trans.rotation.x_rotation * updateRate) >> 4;\n"
        ),
        "direct_assign": (
            "                obj->trans.rotation.x_rotation = "
            "obj->trans.rotation.x_rotation - "
            "((obj->trans.rotation.x_rotation * updateRate) >> 4);\n"
        ),
        "local_mutate": (
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
            "                var_v1 -= (var_v1 * updateRate) >> 4;\n"
            "                obj->trans.rotation.x_rotation = var_v1;\n"
        ),
        "local_result": (
            "                var_v1 = obj->trans.rotation.x_rotation - "
            "((obj->trans.rotation.x_rotation * updateRate) >> 4);\n"
            "                obj->trans.rotation.x_rotation = var_v1;\n"
        ),
    }
    steering_forms = {
        "compound": (
            "                obj->trans.rotation.x_rotation -= "
            "((var_t0 >> 1) * {amount} * updateRate) >> 1;\n"
        ),
        "assign": (
            "                obj->trans.rotation.x_rotation = "
            "obj->trans.rotation.x_rotation - "
            "(((var_t0 >> 1) * {amount} * updateRate) >> 1);\n"
        ),
        "reverse_sub": (
            "                obj->trans.rotation.x_rotation = "
            "-(((var_t0 >> 1) * {amount} * updateRate) >> 1) + "
            "obj->trans.rotation.x_rotation;\n"
        ),
    }
    for damping_name, damping in damping_forms.items():
        for steering_name, steering in steering_forms.items():
            body = (
                "            if (!(gCurrentRacerInput & R_TRIG)) {\n"
                + damping
                + steering.format(amount=19)
                + "            } else {\n"
                + damping
                + steering.format(amount=30)
                + "            }\n"
            )
            evaluate(
                f"rotation_{damping_name}_{steering_name}",
                replace_once(BASE, old, body),
                keep=True,
            )


def original_topology_campaign() -> None:
    steer_old = """\
                var_t0 = racerSteerAngle;
                racerSteerAngle = 0;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    racerSteerAngle = obj->trans.rotation.x_rotation - 0x3000;
                    if (racerSteerAngle > 0x1000) {
                        racerSteerAngle = 0x1000;
                    }
                } else if (obj->trans.rotation.x_rotation < -0x3000) {
                    racerSteerAngle = obj->trans.rotation.x_rotation + 0x3000;
                    if (racerSteerAngle < -0x1000) {
                        racerSteerAngle = -0x1000;
                    }
                    racerSteerAngle = -racerSteerAngle;
                }
                var_t0 *= (f32) (1.0 - ((f32) racerSteerAngle / 4096));
"""
    steer_forms = {
        "direct_racer": steer_old,
        "saved_racer_field": """\
                var_v1 = obj->trans.rotation.x_rotation;
                var_t0 = racerSteerAngle;
                racerSteerAngle = 0;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    racerSteerAngle = var_v1 - 0x3000;
                    if (racerSteerAngle > 0x1000) {
                        racerSteerAngle = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    racerSteerAngle = var_v1 + 0x3000;
                    if (racerSteerAngle < -0x1000) {
                        racerSteerAngle = -0x1000;
                    }
                    racerSteerAngle = -racerSteerAngle;
                }
                var_t0 *= (f32) (1.0 - ((f32) racerSteerAngle / 4096));
""",
        "saved_racer_local": """\
                var_v1 = obj->trans.rotation.x_rotation;
                var_t0 = racerSteerAngle;
                racerSteerAngle = 0;
                if (var_v1 > 0x3000) {
                    racerSteerAngle = var_v1 - 0x3000;
                    if (racerSteerAngle > 0x1000) {
                        racerSteerAngle = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    racerSteerAngle = var_v1 + 0x3000;
                    if (racerSteerAngle < -0x1000) {
                        racerSteerAngle = -0x1000;
                    }
                    racerSteerAngle = -racerSteerAngle;
                }
                var_t0 *= (f32) (1.0 - ((f32) racerSteerAngle / 4096));
""",
        "original_xoff_field": """\
                var_v1 = obj->trans.rotation.x_rotation;
                xRotationOffset = 0;
                var_t0 = racerSteerAngle;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    xRotationOffset = var_v1 - 0x3000;
                    if (xRotationOffset > 0x1000) {
                        xRotationOffset = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    xRotationOffset = var_v1 + 0x3000;
                    if (xRotationOffset < -0x1000) {
                        xRotationOffset = -0x1000;
                    }
                    xRotationOffset = -xRotationOffset;
                }
                var_t0 *= (f32) (1.0 - ((f32) xRotationOffset / 4096));
""",
        "original_xoff_local": """\
                var_v1 = obj->trans.rotation.x_rotation;
                xRotationOffset = 0;
                var_t0 = racerSteerAngle;
                if (var_v1 > 0x3000) {
                    xRotationOffset = var_v1 - 0x3000;
                    if (xRotationOffset > 0x1000) {
                        xRotationOffset = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    xRotationOffset = var_v1 + 0x3000;
                    if (xRotationOffset < -0x1000) {
                        xRotationOffset = -0x1000;
                    }
                    xRotationOffset = -xRotationOffset;
                }
                var_t0 *= (f32) (1.0 - ((f32) xRotationOffset / 4096));
""",
    }
    rotation_old = """\
            // Note: The following if/else has messed up t registers
            if (!(gCurrentRacerInput & R_TRIG)) {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }
"""
    damping_forms = {
        "explicit_assign": (
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
            "                obj->trans.rotation.x_rotation = "
            "var_v1 - ((var_v1 * updateRate) >> 4);\n"
        ),
        "explicit_compound": (
            "                var_v1 = obj->trans.rotation.x_rotation;\n"
            "                obj->trans.rotation.x_rotation -= "
            "(var_v1 * updateRate) >> 4;\n"
        ),
        "direct_compound": (
            "                obj->trans.rotation.x_rotation -= "
            "(obj->trans.rotation.x_rotation * updateRate) >> 4;\n"
        ),
        "direct_assign": (
            "                obj->trans.rotation.x_rotation = "
            "obj->trans.rotation.x_rotation - "
            "((obj->trans.rotation.x_rotation * updateRate) >> 4);\n"
        ),
    }
    spin_old = """\
        var_v0 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v0 > 0x8000) {
            var_v0 -= 0xFFFF;
        }
        if (var_v0 < -0x8000) {
            var_v0 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v0 * updateRate) >> 4;
"""
    spin_hosts = ("var_v0", "xRotationOffset", "var_v1")
    for steer_name, steer in steer_forms.items():
        for damping_name, damping in damping_forms.items():
            rotation = (
                "            // Note: The following if/else has messed up t registers\n"
                "            if (!(gCurrentRacerInput & R_TRIG)) {\n"
                + damping
                + "                obj->trans.rotation.x_rotation -= "
                "((var_t0 >> 1) * 19 * updateRate) >> 1;\n"
                "            } else {\n"
                + damping
                + "                obj->trans.rotation.x_rotation -= "
                "((var_t0 >> 1) * 30 * updateRate) >> 1;\n"
                "            }\n"
            )
            for spin_host in spin_hosts:
                spin = f"""\
        {spin_host} = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if ({spin_host} > 0x8000) {{
            {spin_host} -= 0xFFFF;
        }}
        if ({spin_host} < -0x8000) {{
            {spin_host} += 0xFFFF;
        }}
        obj->trans.rotation.x_rotation += ({spin_host} * updateRate) >> 4;
"""
                source = replace_once(BASE, steer_old, steer)
                source = replace_once(source, rotation_old, rotation)
                source = replace_once(source, spin_old, spin)
                evaluate(
                    f"original_{steer_name}_{damping_name}_{spin_host}",
                    source,
                    keep=True,
                )


def spin_campaign() -> None:
    old = """\
        var_v1 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v1 * updateRate) >> 4;
"""
    hosts = (
        "pad5",
        "pad7",
        "racerMiscAssetIdx",
        "racerSteerAngle",
        "var_t0",
        "var_v0",
        "var_v1",
        "var_a0",
        "temp_t7",
        "pad2",
        "xRotationOffset",
        "zRotationOffset",
        "i",
        "var_t9",
        "racerTrickType",
        "steerVisualRotationOffset",
        "pad4",
    )
    for original in hosts:
        for offset in hosts:
            if original == offset:
                continue
            for final in ("assign", "compound"):
                statement = (
                    "obj->trans.rotation.x_rotation = "
                    f"{original} + (({offset} * updateRate) >> 4);"
                    if final == "assign"
                    else "obj->trans.rotation.x_rotation += "
                    f"({offset} * updateRate) >> 4;"
                )
                body = f"""\
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
                evaluate(
                    f"spin_{original}_{offset}_{final}",
                    replace_once(BASE, old, body),
                )


def spin_offset_host_campaign() -> None:
    old = """\
        var_v1 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v1 * updateRate) >> 4;
"""
    hosts = (
        "pad5",
        "pad7",
        "racerMiscAssetIdx",
        "racerSteerAngle",
        "var_t0",
        "var_v0",
        "var_v1",
        "var_a0",
        "temp_t7",
        "pad2",
        "xRotationOffset",
        "zRotationOffset",
        "i",
        "var_t9",
        "racerTrickType",
        "steerVisualRotationOffset",
        "pad4",
    )
    for host in hosts:
        body = f"""\
        {host} = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if ({host} > 0x8000) {{
            {host} -= 0xFFFF;
        }}
        if ({host} < -0x8000) {{
            {host} += 0xFFFF;
        }}
        obj->trans.rotation.x_rotation += ({host} * updateRate) >> 4;
"""
        evaluate(
            f"spinoffset_{host}",
            replace_once(BASE, old, body),
            keep=True,
        )


def spin_nested_campaign() -> None:
    old = """\
        var_v1 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v1 * updateRate) >> 4;
"""
    originals = (
        "pad5",
        "pad7",
        "racerMiscAssetIdx",
        "racerSteerAngle",
        "var_t0",
        "var_v0",
        "var_a0",
        "temp_t7",
        "pad2",
        "xRotationOffset",
        "zRotationOffset",
        "i",
        "var_t9",
        "racerTrickType",
        "steerVisualRotationOffset",
        "pad4",
    )
    offsets = ("var_v1", "xRotationOffset", "var_v0", "var_a0")
    for original in originals:
        for offset in offsets:
            if original == offset:
                continue
            for final in ("assign", "compound"):
                statement = (
                    "obj->trans.rotation.x_rotation = "
                    f"{original} + (({offset} * updateRate) >> 4);"
                    if final == "assign"
                    else "obj->trans.rotation.x_rotation += "
                    f"({offset} * updateRate) >> 4;"
                )
                body = f"""\
        {offset} = 0xD800 - (({original} = obj->trans.rotation.x_rotation) & 0xFFFF);
        if ({offset} > 0x8000) {{
            {offset} -= 0xFFFF;
        }}
        if ({offset} < -0x8000) {{
            {offset} += 0xFFFF;
        }}
        {statement}
"""
                evaluate(
                    f"spinnested_{original}_{offset}_{final}",
                    replace_once(BASE, old, body),
                )


def register_storage_campaign() -> None:
    names = (
        "pad5",
        "pad7",
        "racerMiscAssetIdx",
        "racerSteerAngle",
        "var_t0",
        "var_v0",
        "var_v1",
        "var_a0",
        "temp_t7",
        "pad2",
        "xRotationOffset",
        "zRotationOffset",
        "i",
        "var_t9",
        "racerTrickType",
        "steerVisualRotationOffset",
        "pad4",
    )
    variants: list[tuple[str, tuple[str, ...]]] = [
        (f"register_{name}", (name,)) for name in names
    ]
    variants.extend(
        (
            f"register_{left}_{right}",
            (left, right),
        )
        for index, left in enumerate(names)
        for right in names[index + 1 :]
    )
    variants.append(("register_core_wave", ("var_v1", "var_a0")))
    for tag, selected in variants:
        source = BASE
        for name in selected:
            source = replace_once(
                source,
                f"    s32 {name};\n",
                f"    register s32 {name};\n",
            )
        evaluate(tag, source)


def integer_fake_campaign() -> None:
    old = "            if ((!racerSteerAngle)) {}\n"
    names = (
        "pad5",
        "pad7",
        "racerMiscAssetIdx",
        "racerSteerAngle",
        "var_t0",
        "var_v0",
        "var_v1",
        "var_a0",
        "temp_t7",
        "pad2",
        "xRotationOffset",
        "zRotationOffset",
        "i",
        "var_t9",
        "racerTrickType",
        "steerVisualRotationOffset",
        "pad4",
    )
    evaluate("intfake_remove", replace_once(BASE, old, ""), keep=True)
    forms = {
        "not": "            if ((!{name})) {{}}\n",
        "value": "            if ({name}) {{}}\n",
        "eqzero": "            if ({name} == 0) {{}}\n",
        "nezero": "            if ({name} != 0) {{}}\n",
        "self": "            {name} = {name};\n",
        "comma": "            if (({name}, 0)) {{}}\n",
    }
    for form, template in forms.items():
        for name in names:
            replacement = template.format(name=name)
            evaluate(
                f"intfake_{form}_{name}",
                replace_once(BASE, old, replacement),
                keep=True,
            )


def integer_fake_placement_campaign() -> None:
    lines = BASE.splitlines(True)
    start = next(
        index
        for index, line in enumerate(lines)
        if "if (racer->spinout_timer != 0)" in line
    )
    end = next(
        index
        for index, line in enumerate(lines[start:], start)
        if "The following if/else has messed up t registers" in line
    )
    names = (
        "racerSteerAngle",
        "var_t0",
        "var_v0",
        "var_v1",
        "xRotationOffset",
        "updateRate",
        "gCurrentRacerInput",
    )
    cases: list[tuple[str, str, str]] = []
    balance = 0
    for index in range(start, end):
        line = lines[index]
        clean = re.sub(r"//.*", "", line)
        balance += clean.count("(") - clean.count(")")
        stripped = clean.strip()
        if balance != 0 or not (
            stripped.endswith(";")
            or stripped.endswith("{}")
            or stripped == "}"
        ):
            continue
        indent = re.match(r"[ \t]*", line).group(0)
        for name in names:
            fake = f"{indent}if ((!{name})) {{}}\n"
            source = "".join(lines[: index + 1] + [fake] + lines[index + 1 :])
            cases.append(
                (
                    f"fakeplace_p{index + 1:04d}_{name}",
                    source,
                    stripped[-70:],
                )
            )

    def worker(case: tuple[str, str, str]) -> tuple:
        tag, source, context = case
        obj = pathlib.Path(f"/tmp/codex_gpr_final_{tag}.o")
        result = ORACLE["evaluate"](source, keep=str(obj))
        if not result.get("ok"):
            return tag, context, result, []
        _, candidate = ORACLE["dump_object"](str(obj))
        reg_bad = [
            index
            for index, (expected, actual) in enumerate(zip(TARGET, candidate))
            if registers(expected[1]) != registers(actual[1])
        ]
        if (
            len(reg_bad) < 28
            and result.get("insns") == 2625
            and result.get("fp") == EXPECTED_FP
        ):
            pathlib.Path(f"/tmp/codex_gpr_final_{tag}.c").write_text(
                source, encoding="utf-8"
            )
        else:
            obj.unlink(missing_ok=True)
        return tag, context, result, reg_bad

    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(worker, cases))
    rows.sort(
        key=lambda row: (
            len(row[3]) if row[3] else 10000,
            row[2].get("norm", 10000),
            row[0],
        )
    )
    seen: set[tuple] = set()
    shown = 0
    for tag, context, result, reg_bad in rows:
        fingerprint = (result.get("sha1"), tuple(reg_bad))
        if fingerprint in seen:
            continue
        seen.add(fingerprint)
        print(
            tag,
            repr(context),
            ORACLE["concise"](result),
            f"fp_exact={result.get('fp') == EXPECTED_FP}",
            f"reg={len(reg_bad)}",
            reg_bad[:80],
        )
        shown += 1
        if shown >= 80:
            break
    print(f"tested={len(rows)} unique={len(seen)}")


def detail(path: pathlib.Path, start: int, end: int) -> None:
    _, candidate = ORACLE["dump_object"](str(path))
    for index in range(start, end):
        target_word, target_asm = TARGET[index]
        candidate_word, candidate_asm = candidate[index]
        marker = "!" if registers(target_asm) != registers(candidate_asm) else " "
        print(
            f"{marker}{index:4d} T {target_word} {target_asm}\n"
            f" {index:4d} C {candidate_word} {candidate_asm}"
        )


def score_object(path: pathlib.Path) -> None:
    _, candidate = ORACLE["dump_object"](str(path))
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    word_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if expected[0] != actual[0]
    ]
    print(f"register_mismatches={len(reg_bad)} {reg_bad}")
    print(f"word_mismatches={len(word_bad)} {word_bad}")


def main() -> None:
    command = sys.argv[1] if len(sys.argv) > 1 else "equality"
    if command == "equality":
        equality_campaign()
    elif command == "wave":
        wave_campaign()
    elif command == "wave_hosts":
        wave_host_campaign()
    elif command == "wave_syntax":
        wave_syntax_campaign()
    elif command == "wave_erased":
        wave_erased_use_campaign()
    elif command == "wave_priority":
        wave_priority_source_campaign()
    elif command == "steer":
        steer_campaign()
    elif command == "rotation":
        rotation_campaign()
    elif command == "original_topology":
        original_topology_campaign()
    elif command == "spin":
        spin_campaign()
    elif command == "spin_offset_hosts":
        spin_offset_host_campaign()
    elif command == "spin_nested":
        spin_nested_campaign()
    elif command == "register_storage":
        register_storage_campaign()
    elif command == "integer_fake":
        integer_fake_campaign()
    elif command == "fake_placements":
        integer_fake_placement_campaign()
    elif command == "detail":
        detail(pathlib.Path(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4]))
    elif command == "score_object":
        score_object(pathlib.Path(sys.argv[2]))
    else:
        raise SystemExit(f"unknown command: {command}")


if __name__ == "__main__":
    main()
