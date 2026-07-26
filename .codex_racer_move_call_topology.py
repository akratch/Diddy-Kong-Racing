#!/usr/bin/env python3
"""Search equivalent move/approach call CFGs for allocator-cost differences."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
CANONICAL_SHA = "28ae550756b5"

OLD = """\
    if (racer->approachTarget == NULL) {
        var_f20 = obj->x_velocity;
        spEC = obj->z_velocity;
        if (racer->unk1D2 != 0) {
            var_f20 += racer->unk11C * 0.5;
            spEC += racer->unk120 * 0.5;
        }
        if (gRacerInputBlocked) {
            if (var_f20 > 0.5 || var_f20 < -0.5) {
                var_f20 *= 0.65;
            } else {
                var_f20 = 0.0f;
            }
            if (spEC > 0.5 || spEC < -0.5) {
                spEC *= 0.65;
            } else {
                spEC = 0.0f;
            }
        } else {
            var_f20 += racer->unk84;
            spEC += racer->unk88;
        }
        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectMoved = TRUE;
        }
    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
"""

PREP = """\
        var_f20 = obj->x_velocity;
        spEC = obj->z_velocity;
        if (racer->unk1D2 != 0) {
            var_f20 += racer->unk11C * 0.5;
            spEC += racer->unk120 * 0.5;
        }
        if (gRacerInputBlocked) {
            if (var_f20 > 0.5 || var_f20 < -0.5) {
                var_f20 *= 0.65;
            } else {
                var_f20 = 0.0f;
            }
            if (spEC > 0.5 || spEC < -0.5) {
                spEC *= 0.65;
            } else {
                spEC = 0.0f;
            }
        } else {
            var_f20 += racer->unk84;
            spEC += racer->unk88;
        }
"""

ARGS = "obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF"

MOVES = {
    "canonical": f"""\
        if (move_object({ARGS}) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {{
            playerObjectMoved = TRUE;
        }}
""",
    "nested": f"""\
        if (move_object({ARGS})) {{
            if (gCurrentPlayerIndex != PLAYER_COMPUTER) {{
                playerObjectMoved = TRUE;
            }}
        }}
""",
    "nested_reverse_player": f"""\
        if (move_object({ARGS})) {{
            if (gCurrentPlayerIndex == PLAYER_COMPUTER) {{
            }} else {{
                playerObjectMoved = TRUE;
            }}
        }}
""",
    "temp_call_first": f"""\
        var_v0 = move_object({ARGS});
        if (var_v0 && gCurrentPlayerIndex != PLAYER_COMPUTER) {{
            playerObjectMoved = TRUE;
        }}
""",
    "temp_nested": f"""\
        var_v0 = move_object({ARGS});
        if (var_v0) {{
            if (gCurrentPlayerIndex != PLAYER_COMPUTER) {{
                playerObjectMoved = TRUE;
            }}
        }}
""",
    "temp_player_first": f"""\
        var_v0 = move_object({ARGS});
        if (gCurrentPlayerIndex != PLAYER_COMPUTER && var_v0) {{
            playerObjectMoved = TRUE;
        }}
""",
    "assign_bool": f"""\
        playerObjectMoved = move_object({ARGS}) &&
                            gCurrentPlayerIndex != PLAYER_COMPUTER;
""",
    "or_bool": f"""\
        playerObjectMoved |= move_object({ARGS}) &&
                             gCurrentPlayerIndex != PLAYER_COMPUTER;
""",
    "duplicate_ai_first": f"""\
        if (gCurrentPlayerIndex == PLAYER_COMPUTER) {{
            move_object({ARGS});
        }} else if (move_object({ARGS})) {{
            playerObjectMoved = TRUE;
        }}
""",
    "duplicate_human_first": f"""\
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {{
            if (move_object({ARGS})) {{
                playerObjectMoved = TRUE;
            }}
        }} else {{
            move_object({ARGS});
        }}
""",
    "duplicate_nested": f"""\
        if (gCurrentPlayerIndex != PLAYER_COMPUTER) {{
            if (move_object({ARGS})) {{
                playerObjectMoved = TRUE;
            }}
        }} else if (!move_object({ARGS})) {{
        }}
""",
}

OUTERS = {
    "null_first": """\
    if (racer->approachTarget == NULL) {
{prep}{move}    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
""",
    "target_first": """\
    if (racer->approachTarget != NULL) {
        racer_approach_object(obj, racer, updateRateF);
    } else {
{prep}{move}    }
""",
    "target_else_eq": """\
    if (racer->approachTarget) {
        racer_approach_object(obj, racer, updateRateF);
    } else {
{prep}{move}    }
""",
    "null_not": """\
    if (!racer->approachTarget) {
{prep}{move}    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
""",
}


def make(move_name: str, outer_name: str) -> str:
    if BASE.count(OLD) != 1:
        raise ValueError(BASE.count(OLD))
    block = (
        OUTERS[outer_name]
        .replace("{prep}", PREP)
        .replace("{move}", MOVES[move_name])
    )
    return BASE.replace(OLD, block, 1)


def read_cost(trace: str) -> tuple[float | None, str | None]:
    caller = None
    choice = None
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "FACTOR-COST reg=27 " in line:
                match = re.search(r"cost=([0-9.-]+)", line)
                if match:
                    caller = float(match.group(1))
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    choice = "/".join(match.groups())
    return caller, choice


def evaluate(case: tuple[str, str]) -> tuple:
    move_name, outer_name = case
    tag = f"{move_name}_{outer_name}"
    source = make(*case)
    path = f"/tmp/codex_move_topology_{tag}.c"
    trace = f"/tmp/codex_move_topology_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](source, keep=f"/tmp/codex_move_topology_{tag}.o")
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_move_topology_{tag}_analysis.o", trace],
        check=False,
        capture_output=True,
        text=True,
    )
    cost = read_cost(trace) if proc.returncode == 0 else (None, None)
    return tag, source, natural, cost, natural.get("sha1") == CANONICAL_SHA


def main() -> None:
    cases = [(move, outer) for move in MOVES for outer in OUTERS]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[4],
            -(row[3][0] or -1),
            row[2].get("f20_operands", 0) == 0,
            row[2].get("norm", 9999),
        )
    )
    for tag, source, natural, cost, exact in rows:
        if exact and cost[0] != 21.0:
            with open(
                f"/tmp/codex_move_topology_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "exact",
            exact,
            "cost",
            cost,
            ORACLE["concise"](natural),
            natural.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "exact",
        sum(row[4] for row in rows),
        "exact_cost_changed",
        sum(row[4] and row[3][0] != 21.0 for row in rows),
        "promoted",
        sum(row[2].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
