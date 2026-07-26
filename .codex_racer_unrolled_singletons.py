#!/usr/bin/env python3
"""Test fully-unrolled four-trip loops whose body executes exactly once.

The IDO uopt unroller accepts constant-trip loops with at least four iterations.
Putting an existing call behind an induction-variable equality may leave only one
copy after constant folding while still perturbing loop-frequency allocation data.
"""

from __future__ import annotations

import concurrent.futures
import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
CALLS = {
    "move": """\
        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectMoved = TRUE;
        }
""",
    "approach": """\
        racer_approach_object(obj, racer, updateRateF);
""",
    "ai": """\
            onscreen_ai_racer_physics(obj, racer, updateRate);
""",
    "physics": """\
        func_80054FD0(obj, racer, updateRate);
""",
    "sound": """\
        racer_play_sound(obj, SOUND_CRASH);
""",
}
COUNTERS = ("pad5", "pad7", "pad2", "pad4", "var_t9")
LOOPS = {
    "lt": "for ({counter} = 0; {counter} < 4; {counter}++)",
    "ne": "for ({counter} = 0; {counter} != 4; {counter}++)",
    "le": "for ({counter} = 0; {counter} <= 3; {counter}++)",
}
CONDS = {
    "eq": "{counter} == {active}",
    "ne": "{counter} != {inactive}",
    "ule": "(u32) {counter} <= {active}",
}


def indent_block(text: str, spaces: int = 4) -> str:
    prefix = " " * spaces
    return "".join(prefix + line if line.strip() else line for line in text.splitlines(True))


def wrap(source: str, call_name: str, counter: str, loop_name: str, cond_name: str, active: int) -> str:
    call = CALLS[call_name]
    count = source.count(call)
    if count != 1 and call_name != "sound":
        raise ValueError((call_name, count))
    indent = call[: len(call) - len(call.lstrip())]
    loop = LOOPS[loop_name].format(counter=counter)
    inactive = 3 if active == 0 else 0
    cond = CONDS[cond_name].format(counter=counter, active=active, inactive=inactive)
    block = (
        f"{indent}{loop} {{\n"
        f"{indent}    if ({cond}) {{\n"
        f"{indent_block(call, 8)}"
        f"{indent}    }}\n"
        f"{indent}}}\n"
    )
    if call_name == "sound":
        before, after = source.rsplit(call, 1)
        return before + block + after
    return source.replace(call, block, 1)


def evaluate(case: tuple[str, str, str, str, int]) -> tuple:
    call_name, counter, loop_name, cond_name, active = case
    tag = f"{call_name}_{counter}_{loop_name}_{cond_name}_{active}"
    source = wrap(BASE, *case)
    result = ORACLE["evaluate"](source, keep=f"/tmp/codex_unrolled_singleton_{tag}.o")
    if (
        result.get("ok")
        and result.get("insns") == 2625
        and result.get("norm", 9999) <= 900
    ):
        with open(f"/tmp/codex_unrolled_singleton_{tag}.c", "w", encoding="utf-8") as output:
            output.write(source)
    return tag, result


def main() -> None:
    cases = list(
        itertools.product(CALLS, COUNTERS, LOOPS, CONDS, (0, 3))
    )
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[1].get("insns", 9999) != 2625,
            row[1].get("f20_operands", 0) == 0,
            abs(row[1].get("f18", 0) - 190),
            row[1].get("norm", 9999),
        )
    )
    for tag, result in rows:
        print(tag, ORACLE["concise"](result), result.get("fp"))
    print(
        "tested",
        len(rows),
        "exact_count",
        sum(row[1].get("insns") == 2625 for row in rows),
        "promoted",
        sum(row[1].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
