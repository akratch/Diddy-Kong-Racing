#!/usr/bin/env python3
"""Weight only individual calls crossed by the factor source web."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
CALLS = (
    """\
                sound_play_spatial(SOUND_ZIP_PAD_BOOST, obj->trans.x_position, obj->trans.y_position,
                                   obj->trans.z_position, NULL);
""",
    """\
                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, SOUND_NUMBER_OF_RACERS, 0x80 | 0x2);
""",
    """\
            racer->boostTimer = normalise_time(45);
""",
    """\
            rumble_set(racer->playerIndex, 8);
""",
    """\
            racer_play_sound(obj, SOUND_CRASH);
""",
    """\
                            racer->boostTimer = normalise_time(0xA);
""",
    """\
                            racer->boostTimer = normalise_time(10);
""",
)
ZEROS = {
    "comma": "(var_f20 > 0.0f, 0)",
    "and": "(var_f20 > 0.0f) & 0",
    "mul": "(var_f20 > 0.0f) * 0",
    "ternary": "(var_f20 > 0.0f) ? 0 : 0",
}


def zero_names(count: int, pattern: str) -> list[str]:
    if pattern in ZEROS:
        return [pattern] * count
    if pattern == "comma_last_and":
        return ["comma"] * (count - 1) + ["and"]
    if pattern == "and_last_comma":
        return ["and"] * (count - 1) + ["comma"]
    if pattern == "alternate":
        return ["comma" if index % 2 == 0 else "and" for index in range(count)]
    raise ValueError(pattern)


def counters(count: int, pattern: str) -> list[str]:
    if pattern == "same":
        return ["pad5"] * count
    if pattern == "alternate":
        return ["pad5" if index % 2 == 0 else "pad7" for index in range(count)]
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
        raise ValueError((count, call))
    indent = re.match(r"[ \t]*", call).group(0)
    if loop_form == "for":
        block = (
            f"{indent}{counter} = 0;\n"
            f"{indent}for (; {counter} < 1; {counter}++) {{\n"
            + call
            + f"{indent}    {counter} += {ZEROS[zero_name]};\n"
            + f"{indent}}}\n"
        )
    else:
        block = (
            f"{indent}{counter} = 0;\n"
            f"{indent}do {{\n"
            + call
            + f"{indent}    {counter} += {ZEROS[zero_name]};\n"
            + f"{indent}}} while (++{counter} < 1);\n"
        )
    if count == 1:
        return source.replace(call, block, 1)
    before, after = source.rsplit(call, 1)
    return before + block + after


def make(
    count: int,
    zero_pattern: str,
    counter_pattern: str,
    loop_form: str,
) -> str:
    source = BASE
    names = zero_names(count, zero_pattern)
    counter_names = counters(count, counter_pattern)
    for call, zero_name, counter in zip(
        CALLS[:count], names, counter_names
    ):
        source = wrap_call(source, call, counter, zero_name, loop_form)
    return source


def evaluate(case: tuple[int, str, str, str]) -> tuple:
    count, zero_pattern, counter_pattern, loop_form = case
    tag = f"n{count}_{zero_pattern}_{counter_pattern}_{loop_form}"
    source = make(*case)
    path = f"/tmp/codex_call_microloops_{tag}.c"
    trace = f"/tmp/codex_call_microloops_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_call_microloops_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_call_microloops_{tag}_analysis.o",
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
                if "FACTOR-COST reg=27 " in line:
                    match = re.search(r"cost=([0-9.-]+)", line)
                    if match:
                        metrics["caller"] = match.group(1)
                elif "FACTOR-COST reg=30 " in line:
                    match = re.search(
                        r"cost=([0-9.-]+).*first-used=(\\d+)", line
                    )
                    if match:
                        metrics["callee"] = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\\d+) cost=([0-9.-]+)", line)
                    if match:
                        metrics["choice"] = "/".join(match.groups())
    return tag, source, result, metrics, proc.returncode


def main() -> None:
    patterns = (
        "comma",
        "and",
        "mul",
        "ternary",
        "comma_last_and",
        "and_last_comma",
        "alternate",
    )
    cases = [
        (count, zero_pattern, counter_pattern, loop_form)
        for count in (4, 5, 6, 7)
        for zero_pattern in patterns
        for counter_pattern in ("same", "alternate", "rotate")
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
                f"/tmp/codex_call_microloops_promising_{tag}.c",
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
