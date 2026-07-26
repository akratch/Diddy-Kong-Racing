#!/usr/bin/env python3
"""Find instruction-neutral one-pass CFG wrappers around factor-crossed calls.

The allocator charges a call in a frequency-10 block ten times.  A construct
which is simplified to the canonical machine code after loop-frequency
analysis could therefore make the factor prefer f20 without changing output.
"""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
CANONICAL_SHA = "28ae550756b5"

CALLS = {
    "apply": """\
    apply_vehicle_rotation_offset(racer, updateRate, 0, var_t0, 0);
""",
    "zip_norm": """\
            racer->boostTimer = normalise_time(45);
""",
    "spin_crash": """\
            racer_play_sound(obj, SOUND_CRASH);
""",
    "trick_norm_a": """\
                            racer->boostTimer = normalise_time(0xA);
""",
    "trick_norm_b": """\
                            racer->boostTimer = normalise_time(10);
""",
    "top_speed": """\
    var_f0 = handle_racer_top_speed(obj, racer);
""",
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
    "landing_crash": """\
        racer_play_sound(obj, SOUND_CRASH);
""",
}

FORMS = {
    "block": """\
{indent}{{
{body}{indent}}}
""",
    "do_zero": """\
{indent}do {{
{body}{indent}}} while (0);
""",
    "do_false": """\
{indent}do {{
{body}{indent}}} while (FALSE);
""",
    "do_zero_and": """\
{indent}do {{
{body}{indent}}} while (0 && var_f20 > 0.0f);
""",
    "while_break": """\
{indent}while (TRUE) {{
{body}{indent}    break;
{indent}}}
""",
    "for_break": """\
{indent}for (;;) {{
{body}{indent}    break;
{indent}}}
""",
    "for_one": """\
{indent}pad5 = 0;
{indent}for (; pad5 < 1; pad5++) {{
{body}{indent}}}
""",
    "for_one_nested": """\
{indent}pad5 = 0;
{indent}for (; pad5 < 1; pad5++) {{
{indent}    pad7 = 0;
{indent}    for (; pad7 < 1; pad7++) {{
{body}{indent}    }}
{indent}}}
""",
    "for_one_nested_unroll": """\
{indent}pad5 = 0;
{indent}#pragma unroll
{indent}for (; pad5 < 1; pad5++) {{
{indent}    pad7 = 0;
{indent}    #pragma unroll
{indent}    for (; pad7 < 1; pad7++) {{
{body}{indent}    }}
{indent}}}
""",
    "for_one_nested_unroll1": """\
{indent}pad5 = 0;
{indent}#pragma unroll 1
{indent}for (; pad5 < 1; pad5++) {{
{indent}    pad7 = 0;
{indent}    #pragma unroll 1
{indent}    for (; pad7 < 1; pad7++) {{
{body}{indent}    }}
{indent}}}
""",
    "for_one_nested_unroll4": """\
{indent}pad5 = 0;
{indent}#pragma unroll 4
{indent}for (; pad5 < 1; pad5++) {{
{indent}    pad7 = 0;
{indent}    #pragma unroll 4
{indent}    for (; pad7 < 1; pad7++) {{
{body}{indent}    }}
{indent}}}
""",
    "if_one": """\
{indent}if (1) {{
{body}{indent}}}
""",
    "if_else": """\
{indent}if (0) {{
{indent}}} else {{
{body}{indent}}}
""",
    "switch_default": """\
{indent}switch (0) {{
{indent}default:
{body}{indent}}}
""",
    "goto_label": """\
{indent}goto {label};
{indent}{label}:
{body}""",
}


def add_indent(text: str, spaces: int) -> str:
    prefix = " " * spaces
    return "".join(prefix + line if line.strip() else line for line in text.splitlines(True))


def selected_call(source: str, name: str) -> str:
    call = CALLS[name]
    if name == "zip_norm":
        # Select the second normalise_time(45), inside zipper correction.
        matches = list(re.finditer(re.escape(call), source))
        if len(matches) != 2:
            raise ValueError((name, len(matches)))
        start = matches[1].start()
        return source[:start] + "\x00" + source[start + len(call) :]
    if name == "spin_crash":
        matches = list(re.finditer(re.escape(call), source))
        if len(matches) != 1:
            raise ValueError((name, len(matches)))
        start = matches[0].start()
        return source[:start] + "\x00" + source[start + len(call) :]
    if name == "landing_crash":
        matches = list(re.finditer(re.escape(call), source))
        if len(matches) != 2:
            raise ValueError((name, len(matches)))
        start = matches[1].start()
        return source[:start] + "\x00" + source[start + len(call) :]
    if source.count(call) != 1:
        raise ValueError((name, source.count(call)))
    return source.replace(call, "\x00", 1)


def wrap(source: str, name: str, form: str) -> str:
    call = CALLS[name]
    marked = selected_call(source, name)
    indent = call[: len(call) - len(call.lstrip())]
    body = add_indent(call, 4)
    label = f"codex_singleton_{name}_{form}"
    replacement = FORMS[form].format(indent=indent, body=body, label=label)
    return marked.replace("\x00", replacement, 1)


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
    name, form = case
    tag = f"{name}_{form}"
    source = wrap(BASE, name, form)
    path = f"/tmp/codex_constant_singleton_{tag}.c"
    trace = f"/tmp/codex_constant_singleton_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_constant_singleton_{tag}.o"
    )
    proc = subprocess.run(
        [ANALYSIS, path, f"/tmp/codex_constant_singleton_{tag}_analysis.o", trace],
        check=False,
        capture_output=True,
        text=True,
    )
    cost = read_cost(trace) if proc.returncode == 0 else (None, None)
    exact = natural.get("sha1") == CANONICAL_SHA
    return tag, source, natural, cost, exact, proc.returncode


def main() -> None:
    cases = [(name, form) for name in CALLS for form in FORMS]
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
    for tag, source, natural, cost, exact, returncode in rows:
        if exact and cost[0] != 21.0:
            with open(
                f"/tmp/codex_constant_singleton_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
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
