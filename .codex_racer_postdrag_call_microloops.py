#!/usr/bin/env python3
"""Weight calls after drag locals die but before var_f20's final use."""

from __future__ import annotations

import concurrent.futures
import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
CALLS = (
    """\
        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectMoved = TRUE;
        }
""",
    """\
        racer_approach_object(obj, racer, updateRateF);
""",
    """\
            onscreen_ai_racer_physics(obj, racer, updateRate);
""",
    """\
        func_80054FD0(obj, racer, updateRate);
""",
    """\
        racer_play_sound(obj, SOUND_CRASH);
""",
)
ZEROS = {
    "comma": "(var_f20 > 0.0f, 0)",
    "and": "(var_f20 > 0.0f) & 0",
    "mul": "(var_f20 > 0.0f) * 0",
    "ternary": "(var_f20 > 0.0f) ? 0 : 0",
}


def zero_names(pattern: str, count: int) -> list[str]:
    if pattern in ZEROS:
        return [pattern] * count
    if pattern == "comma_last_and":
        return ["comma"] * (count - 1) + ["and"]
    if pattern == "and_last_comma":
        return ["and"] * (count - 1) + ["comma"]
    if pattern == "alternate":
        return [
            "comma" if index % 2 == 0 else "and"
            for index in range(count)
        ]
    raise ValueError(pattern)


def counters(pattern: str, count: int) -> list[str]:
    if pattern == "same":
        return ["pad5"] * count
    if pattern == "alternate":
        return [
            "pad5" if index % 2 == 0 else "pad7"
            for index in range(count)
        ]
    if pattern == "rotate":
        values = ("pad5", "pad7", "pad2", "pad4")
        return [values[index % len(values)] for index in range(count)]
    raise ValueError(pattern)


def wrap_call(
    source: str,
    call: str,
    counter: str,
    zero_name: str,
    loop_form: str,
) -> str:
    count = source.count(call)
    if count == 0:
        raise ValueError(call)
    indent = re.match(r"[ \t]*", call).group(0)
    statement = call
    if loop_form == "for":
        block = (
            f"{indent}{counter} = 0;\n"
            f"{indent}for (; {counter} < 1; {counter}++) {{\n"
            + statement
            + f"{indent}    {counter} += {ZEROS[zero_name]};\n"
            + f"{indent}}}\n"
        )
    else:
        block = (
            f"{indent}{counter} = 0;\n"
            f"{indent}do {{\n"
            + statement
            + f"{indent}    {counter} += {ZEROS[zero_name]};\n"
            + f"{indent}}} while (++{counter} < 1);\n"
        )
    if count == 1:
        return source.replace(call, block, 1)
    before, after = source.rsplit(call, 1)
    return before + block + after


def make(
    selected: tuple[int, ...],
    zero_pattern: str,
    counter_pattern: str,
    loop_form: str,
) -> str:
    source = BASE
    for index, zero_name, counter in zip(
        selected,
        zero_names(zero_pattern, len(selected)),
        counters(counter_pattern, len(selected)),
    ):
        source = wrap_call(
            source,
            CALLS[index],
            counter,
            zero_name,
            loop_form,
        )
    return source


def evaluate(case: tuple[tuple[int, ...], str, str, str]) -> tuple:
    selected, zero_pattern, counter_pattern, loop_form = case
    call_tag = "".join(str(index) for index in selected)
    tag = f"c{call_tag}_{zero_pattern}_{counter_pattern}_{loop_form}"
    source = make(*case)
    path = f"/tmp/codex_postdrag_call_microloops_{tag}.c"
    trace = f"/tmp/codex_postdrag_call_microloops_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_postdrag_call_microloops_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_postdrag_call_microloops_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    metrics: dict[str, str] = {}
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FVAR " in line and "addr=-44 " in line:
                    match = re.search(
                        r"adjsave=([0-9.-]+) uses=(\\d+).*c14=([0-9.-]+)",
                        line,
                    )
                    if match:
                        metrics["factor"] = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\\d+) cost=([0-9.-]+)", line)
                    if match:
                        metrics["choice"] = "/".join(match.groups())
    return tag, source, result, metrics, proc.returncode


def main() -> None:
    selections = [
        selected
        for count in range(1, len(CALLS) + 1)
        for selected in itertools.combinations(range(len(CALLS)), count)
    ]
    cases = [
        (selected, zero_pattern, "same", loop_form)
        for selected in selections
        for zero_pattern in ("and", "comma", "ternary")
        for loop_form in ("for", "do")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[2].get("f20_operands", 0) == 0,
            abs(row[2].get("f18", 0) - 190),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, metrics, returncode in rows:
        if result.get("f20_operands", 0) > 0:
            with open(
                f"/tmp/codex_postdrag_call_microloops_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
            "metrics",
            metrics,
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[2].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
