#!/usr/bin/env python3
"""Test switch/goto control-flow spellings for the last equality operand."""

from __future__ import annotations

import pathlib
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
TARGET = ORACLE["TARGET_INSNS"]
BASE_PATH = pathlib.Path("/tmp/codex_gpr_final_spinoffset_var_v0.c")
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
OLD = """\
    var_v0 = racer->playerIndex;
    if ((var_v0 == PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
"""


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


CASES = {
    "baseline": OLD,
    "switch_case": """\
    var_v0 = racer->playerIndex;
    switch (var_v0) {
        case PLAYER_COMPUTER:
            if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
                gCurrentRacerHandlingStat = 1.4f;
            }
            break;
    }
""",
    "switch_default": """\
    var_v0 = racer->playerIndex;
    switch (var_v0) {
        default:
            break;
        case PLAYER_COMPUTER:
            if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
                gCurrentRacerHandlingStat = 1.4f;
            }
            break;
    }
""",
    "switch_direct": """\
    switch (racer->playerIndex) {
        case PLAYER_COMPUTER:
            if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
                gCurrentRacerHandlingStat = 1.4f;
            }
            break;
    }
""",
    "goto_skip": """\
    var_v0 = racer->playerIndex;
    if (var_v0 != PLAYER_COMPUTER) {
        goto handling_skip;
    }
    if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        gCurrentRacerHandlingStat = 1.4f;
    }
handling_skip:
""",
    "goto_enter": """\
    var_v0 = racer->playerIndex;
    if (var_v0 == PLAYER_COMPUTER) {
        goto handling_enter;
    }
    goto handling_skip;
handling_enter:
    if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        gCurrentRacerHandlingStat = 1.4f;
    }
handling_skip:
""",
    "two_if_continue": """\
    var_v0 = racer->playerIndex;
    if (var_v0 == PLAYER_COMPUTER) {
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCurrentRacerHandlingStat = 1.4f;
        }
    }
""",
    "ternary_void": """\
    var_v0 = racer->playerIndex;
    (var_v0 == PLAYER_COMPUTER && gCurrentPlayerIndex != PLAYER_COMPUTER)
        ? (gCurrentRacerHandlingStat = 1.4f)
        : (void) 0;
""",
}


def main() -> None:
    rows = []
    for tag, replacement in CASES.items():
        source = replace_once(BASE, OLD, replacement)
        obj = pathlib.Path(f"/tmp/codex_eqswitch_{tag}.o")
        result = ORACLE["evaluate"](source, keep=str(obj))
        if not result.get("ok"):
            rows.append((tag, result, []))
            continue
        _, candidate = ORACLE["dump_object"](str(obj))
        reg_bad = [
            index
            for index, (expected, actual) in enumerate(zip(TARGET, candidate))
            if registers(expected[1]) != registers(actual[1])
        ]
        if result.get("fp") == EXPECTED_FP and len(reg_bad) < 28:
            pathlib.Path(f"/tmp/codex_eqswitch_{tag}.c").write_text(
                source, encoding="utf-8"
            )
        else:
            obj.unlink(missing_ok=True)
        rows.append((tag, result, reg_bad))
    rows.sort(key=lambda row: (len(row[2]) if row[2] else 10000, row[0]))
    for tag, result, reg_bad in rows:
        print(
            tag,
            ORACLE["concise"](result),
            f"fp_exact={result.get('fp') == EXPECTED_FP}",
            f"reg={len(reg_bad)}",
            reg_bad[:100],
        )


if __name__ == "__main__":
    main()
