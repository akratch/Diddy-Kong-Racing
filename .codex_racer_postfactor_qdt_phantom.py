#!/usr/bin/env python3
"""Probe invisible post-factor Qdt ranges as an f20 first-use prepayment."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

DECL_ANCHOR = "    Object_Boost *boostObj;\n"
DEF_ANCHOR = "    obj->z_velocity = spEC;\n"
VALUES = (
    "obj->x_velocity",
    "obj->y_velocity",
    "obj->z_velocity",
    "racer->velocity",
    "racer->lateral_velocity",
    "racer->forwardVel",
    "racer->ox1",
    "racer->oy1",
)
ANCHORS = {
    "rotation": (
        "    gCurrentRacerTransform.rotation.y_rotation = -obj->trans.rotation.y_rotation;\n",
        "    gCurrentRacerTransform.rotation.y_rotation = "
        "-obj->trans.rotation.y_rotation + {zero};\n",
    ),
    "attach1": (
        "    if (obj->attachPoints != NULL && obj->attachPoints->count >= 3) {\n",
        "    if (obj->attachPoints != NULL + {zero} && obj->attachPoints->count >= 3) {\n",
    ),
    "boost": (
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {\n",
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && "
        "racer->boostTimer == {zero} && gNumViewports < 2) {\n",
    ),
    "vehicle": (
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES) {\n",
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES + {zero}) {\n",
    ),
    "camera": (
        "    second_racer_camera_update(obj, racer, 1, updateRateF);\n",
        "    second_racer_camera_update(obj, racer, 1 + {zero}, updateRateF);\n",
    ),
    "moved": (
        "    if (playerObjectMoved != FALSE) {\n",
        "    if (playerObjectMoved != FALSE + {zero}) {\n",
    ),
}


def replace_last(source: str, old: str, new: str) -> str:
    if old not in source:
        raise ValueError(old)
    before, after = source.rsplit(old, 1)
    return before + new + after


def zero_expression(count: int, form: str) -> str:
    names = [f"post_q{index}" for index in range(count)]
    if form == "compare":
        body = " + ".join(f"({name} > 0.0)" for name in names)
        return f"(({body}) * 0)"
    if form == "sum_compare":
        body = " + ".join(names)
        return f"((({body}) > 0.0) * 0)"
    if form == "self_sub":
        body = " + ".join(names)
        return f"((s32) (({body}) - ({body})))"
    if form == "comma":
        body = ", ".join(f"({name} > 0.0)" for name in names)
        return f"(({body}), 0)"
    if form == "ternary":
        body = " + ".join(names)
        return f"((({body}) > 0.0) ? 0 : 0)"
    raise ValueError(form)


def make(
    count: int,
    form: str,
    start: str,
    end: str,
    init_mode: str,
) -> str:
    source = BASE
    declarations = "".join(f"    f64 post_q{index};\n" for index in range(count))
    if source.count(DECL_ANCHOR) != 1:
        raise ValueError("declaration anchor")
    source = source.replace(DECL_ANCHOR, DECL_ANCHOR + declarations, 1)
    if init_mode != "uninit":
        definitions = []
        for index in range(count):
            value = VALUES[index]
            if init_mode == "raw":
                rhs = f"(f64) {value}"
            elif init_mode == "square":
                rhs = f"(f64) ({value} * {value})"
            else:
                raise ValueError(init_mode)
            definitions.append(f"    post_q{index} = {rhs};\n")
        source = replace_last(
            source,
            DEF_ANCHOR,
            DEF_ANCHOR + "".join(definitions),
        )
    zero = zero_expression(count, form)
    for anchor_name in dict.fromkeys((start, end)):
        old, new = ANCHORS[anchor_name]
        source = replace_last(source, old, new.replace("{zero}", zero))
    return source


def evaluate(case: tuple[int, str, str, str, str]) -> tuple:
    count, form, start, end, init_mode = case
    tag = f"n{count}_{init_mode}_{form}_{start}_{end}"
    source = make(*case)
    path = f"/tmp/codex_postfactor_qdt_phantom_{tag}.c"
    trace = f"/tmp/codex_postfactor_qdt_phantom_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_postfactor_qdt_phantom_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_postfactor_qdt_phantom_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    qdt_colors: list[tuple[int, int, float]] = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
                elif "RACER-COLOR " in line and " size=8" in line:
                    match = re.search(
                        r"bit=(\d+).*reg=(\d+).*adjsave=([0-9.-]+)", line
                    )
                    if match:
                        qdt_colors.append(
                            (
                                int(match.group(1)),
                                int(match.group(2)),
                                float(match.group(3)),
                            )
                        )
    return tag, source, result, factor, qdt_colors, proc.returncode


def main() -> None:
    spans = (
        ("rotation", "moved"),
        ("rotation", "camera"),
        ("attach1", "moved"),
        ("boost", "moved"),
        ("vehicle", "moved"),
    )
    cases = [
        (count, form, start, end, init_mode)
        for count in range(1, 9)
        for form in ("compare", "sum_compare", "self_sub", "comma", "ternary")
        for start, end in spans
        for init_mode in ("uninit", "raw", "square")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[3].startswith("30/"),
            not any(reg == 30 for _, reg, _ in row[4]),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, factor, colors, returncode in rows:
        if factor.startswith("30/") or any(reg == 30 for _, reg, _ in colors):
            with open(
                f"/tmp/codex_postfactor_qdt_phantom_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
            "factor",
            factor,
            "qdt",
            ",".join(f"{bit}/{reg}/{save:g}" for bit, reg, save in colors)
            or "-",
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].startswith("30/") for row in rows),
        "qdt_f20",
        sum(any(reg == 30 for _, reg, _ in row[4]) for row in rows),
    )


if __name__ == "__main__":
    main()
