#!/usr/bin/env python3
"""Recover the operand order of the PLAYER_COMPUTER branch at instruction 523."""

from __future__ import annotations

import pathlib
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"
OLD = """\
    var_v0 = racer->playerIndex;
    if ((var_v0 == PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
"""

FORMS = {
    "and_var_first": OLD,
    "and_const_first": """\
    var_v0 = racer->playerIndex;
    if ((PLAYER_COMPUTER == var_v0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "nested_var_first": """\
    var_v0 = racer->playerIndex;
    if (var_v0 == PLAYER_COMPUTER) {
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCurrentRacerHandlingStat = 1.4f;
        }
    }
""",
    "nested_const_first": """\
    var_v0 = racer->playerIndex;
    if (PLAYER_COMPUTER == var_v0) {
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
            gCurrentRacerHandlingStat = 1.4f;
        }
    }
""",
    "else_var_first": """\
    var_v0 = racer->playerIndex;
    if (var_v0 != PLAYER_COMPUTER) {
    } else if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "else_const_first": """\
    var_v0 = racer->playerIndex;
    if (PLAYER_COMPUTER != var_v0) {
    } else if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "else_semicolon": """\
    var_v0 = racer->playerIndex;
    if (PLAYER_COMPUTER != var_v0) {
        ;
    } else if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "not_ne_var": """\
    var_v0 = racer->playerIndex;
    if (!(var_v0 != PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "not_ne_const": """\
    var_v0 = racer->playerIndex;
    if (!(PLAYER_COMPUTER != var_v0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "eq_false_var": """\
    var_v0 = racer->playerIndex;
    if (((var_v0 != PLAYER_COMPUTER) == FALSE) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "eq_false_const": """\
    var_v0 = racer->playerIndex;
    if (((PLAYER_COMPUTER != var_v0) == FALSE) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "direct_var_first": """\
    if ((racer->playerIndex == PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "direct_const_first": """\
    if ((PLAYER_COMPUTER == racer->playerIndex) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "two_vars_const_first": """\
    var_v0 = racer->playerIndex;
    var_v1 = PLAYER_COMPUTER;
    if ((var_v1 == var_v0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "two_vars_player_first": """\
    var_v0 = racer->playerIndex;
    var_v1 = PLAYER_COMPUTER;
    if ((var_v0 == var_v1) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "two_vars_reverse_defs": """\
    var_v1 = PLAYER_COMPUTER;
    var_v0 = racer->playerIndex;
    if ((var_v1 == var_v0) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
    "const_holder_v0": """\
    var_v1 = racer->playerIndex;
    var_v0 = PLAYER_COMPUTER;
    if ((var_v0 == var_v1) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
""",
}


def registers(assembly: str) -> list[str]:
    import re

    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def main() -> None:
    target = ORACLE["TARGET_INSNS"]
    for serial, (tag, replacement) in enumerate(FORMS.items()):
        source = BASE.replace(OLD, replacement, 1)
        path = pathlib.Path(f"/tmp/codex_computer_condition_{serial:02d}_{tag}.c")
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
            for index, (expected, actual) in enumerate(zip(target, candidate))
            if registers(expected[1]) != registers(actual[1])
        ]
        at_523 = candidate[523][1] if len(candidate) > 523 else "-"
        print(
            tag,
            "insns",
            len(candidate),
            "reg_bad",
            len(reg_bad) + abs(len(target) - len(candidate)),
            "523",
            at_523,
            "matched",
            523 not in reg_bad,
        )


if __name__ == "__main__":
    main()
