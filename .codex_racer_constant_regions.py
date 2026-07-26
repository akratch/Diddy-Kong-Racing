#!/usr/bin/env python3
"""Test control regions that may disappear while retaining allocator metadata."""

from __future__ import annotations

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
FORMS = {
    "do0": "do {{\n{body}{indent}}} while (0);\n",
    "do_and0": (
        "do {{\n{body}{indent}}} while ((var_f20 > 0.0f) & 0);\n"
    ),
    "do_land0": (
        "do {{\n{body}{indent}}} while ((var_f20 > 0.0f) && 0);\n"
    ),
    "do_ternary0": (
        "do {{\n{body}{indent}}} while ((var_f20 > 0.0f) ? 0 : 0);\n"
    ),
    "if1": "if (1) {{\n{body}{indent}}}\n",
    "if_or1": (
        "if ((var_f20 > 0.0f) || 1) {{\n{body}{indent}}}\n"
    ),
    "if_ternary1": (
        "if ((var_f20 > 0.0f) ? 1 : 1) {{\n{body}{indent}}}\n"
    ),
}


def indent_body(text: str, amount: str) -> str:
    return "".join(amount + line if line.strip() else line for line in text.splitlines(True))


def wrap(source: str, call: str, form: str) -> str:
    if source.count(call) == 0:
        raise ValueError(call)
    indent = re.match(r"[ \t]*", call).group(0)
    body = indent_body(call, "    ")
    replacement = indent + FORMS[form].format(
        body=body[len(indent):],
        indent=indent,
    )
    if source.count(call) == 1:
        return source.replace(call, replacement, 1)
    before, after = source.rsplit(call, 1)
    return before + replacement + after


def make(selected: tuple[int, ...], form: str) -> str:
    source = BASE
    for index in selected:
        source = wrap(source, CALLS[index], form)
    return source


def trace_metrics(trace: str) -> dict[str, str]:
    result: dict[str, str] = {}
    with open(trace, encoding="utf-8") as input_file:
        for line in input_file:
            if "FVAR " in line and "addr=-44 " in line:
                match = re.search(
                    r"adjsave=([0-9.-]+) uses=(\d+).*c14=([0-9.-]+)",
                    line,
                )
                if match:
                    result["factor"] = "/".join(match.groups())
            elif "FACTOR-CHOICE" in line:
                match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                if match:
                    result["choice"] = "/".join(match.groups())
    return result


def main() -> None:
    selections = [
        selected
        for count in range(1, len(CALLS) + 1)
        for selected in itertools.combinations(range(len(CALLS)), count)
    ]
    rows = []
    for form in FORMS:
        for selected in selections:
            tag = f"{form}_c{''.join(map(str, selected))}"
            source = make(selected, form)
            obj = f"/tmp/codex_constant_regions_{tag}.o"
            result = ORACLE["evaluate"](source, keep=obj)
            metrics: dict[str, str] = {}
            if result.get("ok") and (
                result.get("sha1") == "28ae550756b5"
                or result.get("f20_operands", 0) > 0
            ):
                path = f"/tmp/codex_constant_regions_{tag}.c"
                trace = f"/tmp/codex_constant_regions_{tag}.trace"
                with open(path, "w", encoding="utf-8") as output:
                    output.write(source)
                proc = subprocess.run(
                    [ANALYSIS, path, obj + ".analysis", trace],
                    check=False,
                    capture_output=True,
                    text=True,
                )
                if proc.returncode == 0:
                    metrics = trace_metrics(trace)
            rows.append((tag, result, metrics))
    rows.sort(
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            row[1].get("norm", 9999),
            abs(row[1].get("insns", 9999) - 2625),
        )
    )
    for tag, result, metrics in rows:
        print(tag, metrics, ORACLE["concise"](result), result.get("fp"))
    print(
        "tested",
        len(rows),
        "exact-natural",
        sum(row[1].get("sha1") == "28ae550756b5" for row in rows),
        "promoted",
        sum(row[1].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
