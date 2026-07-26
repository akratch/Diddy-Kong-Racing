#!/usr/bin/env python3
"""Search one-pass landing-call loop spellings using already-dead locals."""

from __future__ import annotations

import concurrent.futures
import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()

CALL = "        racer_play_sound(obj, SOUND_CRASH);\n"
BLOCK = """\
    if (var_t0 == 0 && racer->groundedWheels != 0 && racer->spinout_timer != 0) {
        racer_play_sound(obj, SOUND_CRASH);
        if (racer->playerIndex != PLAYER_COMPUTER) {
            gCameraObject->shakeMagnitude = 6.0f;
        }
    }
"""

COUNTERS = (
    "pad5",
    "pad7",
    "pad2",
    "pad4",
    "var_v0",
    "var_v1",
    "var_a0",
    "var_t9",
    "racerMiscAssetIdx",
    "racerSteerAngle",
    "temp_t7",
    "xRotationOffset",
    "zRotationOffset",
    "i",
)


def indent(text: str, spaces: int) -> str:
    prefix = " " * spaces
    return "".join(
        prefix + line if line.strip() else line
        for line in text.splitlines(True)
    )


def call_wrapper(form: str, outer: str, inner: str) -> str:
    body = indent(CALL, 8)
    if form == "for_up":
        return (
            f"        {outer} = 0;\n"
            f"        for (; {outer} < 1; {outer}++) {{\n"
            f"            {inner} = 0;\n"
            f"            for (; {inner} < 1; {inner}++) {{\n"
            f"{body}"
            f"            }}\n"
            f"        }}\n"
        )
    if form == "for_down":
        return (
            f"        {outer} = 1;\n"
            f"        for (; {outer} > 0; {outer}--) {{\n"
            f"            {inner} = 1;\n"
            f"            for (; {inner} > 0; {inner}--) {{\n"
            f"{body}"
            f"            }}\n"
            f"        }}\n"
        )
    if form == "while_up":
        return (
            f"        {outer} = 0;\n"
            f"        while ({outer} < 1) {{\n"
            f"            {inner} = 0;\n"
            f"            while ({inner} < 1) {{\n"
            f"{body}"
            f"                {inner}++;\n"
            f"            }}\n"
            f"            {outer}++;\n"
            f"        }}\n"
        )
    if form == "while_flag":
        return (
            f"        {outer} = TRUE;\n"
            f"        while ({outer}) {{\n"
            f"            {inner} = TRUE;\n"
            f"            while ({inner}) {{\n"
            f"{body}"
            f"                {inner} = FALSE;\n"
            f"            }}\n"
            f"            {outer} = FALSE;\n"
            f"        }}\n"
        )
    if form == "do_post":
        return (
            f"        {outer} = 0;\n"
            f"        do {{\n"
            f"            {inner} = 0;\n"
            f"            do {{\n"
            f"{body}"
            f"            }} while ({inner}++ < 0);\n"
            f"        }} while ({outer}++ < 0);\n"
        )
    if form == "do_flag":
        return (
            f"        {outer} = TRUE;\n"
            f"        do {{\n"
            f"            {inner} = TRUE;\n"
            f"            do {{\n"
            f"{body}"
            f"                {inner} = FALSE;\n"
            f"            }} while ({inner});\n"
            f"            {outer} = FALSE;\n"
            f"        }} while ({outer});\n"
        )
    raise ValueError(form)


def block_wrapper(form: str, outer: str, inner: str) -> str:
    condition = (
        "var_t0 == 0 && racer->groundedWheels != 0 && "
        "racer->spinout_timer != 0"
    )
    body = """\
        racer_play_sound(obj, SOUND_CRASH);
        if (racer->playerIndex != PLAYER_COMPUTER) {
            gCameraObject->shakeMagnitude = 6.0f;
        }
"""
    if form == "outer_while":
        return (
            f"    while ({condition}) {{\n"
            f"{body}"
            f"        var_t0 = 1;\n"
            f"    }}\n"
        )
    if form == "outer_inner_while":
        return (
            f"    while ({condition}) {{\n"
            f"        {inner} = TRUE;\n"
            f"        while ({inner}) {{\n"
            f"{indent(body, 4)}"
            f"            {inner} = FALSE;\n"
            f"        }}\n"
            f"        var_t0 = 1;\n"
            f"    }}\n"
        )
    if form == "outer_inner_for":
        return (
            f"    while ({condition}) {{\n"
            f"        {inner} = 0;\n"
            f"        for (; {inner} < 1; {inner}++) {{\n"
            f"{indent(body, 4)}"
            f"        }}\n"
            f"        var_t0 = 1;\n"
            f"    }}\n"
        )
    raise ValueError(form)


def make(kind: str, form: str, outer: str, inner: str) -> str:
    if kind == "call":
        if BASE.count(CALL) != 2:
            raise ValueError(BASE.count(CALL))
        before, after = BASE.rsplit(CALL, 1)
        return before + call_wrapper(form, outer, inner) + after
    if BASE.count(BLOCK) != 1:
        raise ValueError(BASE.count(BLOCK))
    return BASE.replace(BLOCK, block_wrapper(form, outer, inner), 1)


def evaluate(case: tuple[str, str, str, str]) -> tuple:
    kind, form, outer, inner = case
    tag = f"{kind}_{form}_{outer}_{inner}"
    source = make(*case)
    path = f"/tmp/codex_landing_loop_topology_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_landing_loop_topology_{tag}.o"
    )
    return tag, source, result


def main() -> None:
    pairs = list(itertools.permutations(COUNTERS, 2))
    cases = [
        ("call", form, outer, inner)
        for form in (
            "for_up",
            "for_down",
            "while_up",
            "while_flag",
            "do_post",
            "do_flag",
        )
        for outer, inner in pairs
    ]
    cases += [
        ("block", form, outer, inner)
        for form in (
            "outer_while",
            "outer_inner_while",
            "outer_inner_for",
        )
        for outer, inner in pairs
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[2].get("f20_operands", 0) == 0,
            row[2].get("mismatch", 999999),
            abs(row[2].get("insns", 9999) - 2625),
            abs(row[2].get("f18", 0) - 190),
            row[2].get("norm", 9999),
            row[0],
        )
    )
    for tag, source, result in rows:
        if (
            result.get("f20_operands", 0) > 0
            or result.get("insns") == 2625
            or result.get("norm", 9999) < 800
        ):
            print(
                tag,
                ORACLE["concise"](result),
                result.get("fp"),
            )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[2].get("f20_operands", 0) > 0 for row in rows),
        "exact",
        sum(row[2].get("mismatch") == 0 for row in rows),
    )


if __name__ == "__main__":
    main()
