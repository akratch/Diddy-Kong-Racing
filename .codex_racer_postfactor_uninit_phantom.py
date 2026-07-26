#!/usr/bin/env python3
"""Seed f20 after var_f20 dies using an optimizer-erased undefined local."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
STARTS = {
    "after_x": "    obj->x_velocity = var_f20;\n",
    "after_z": "    obj->z_velocity = spEC;\n",
    "before_inverse": (
        "    mtxf_from_inverse_transform((MtxF *) &sp60, "
        "&gCurrentRacerTransform);\n"
    ),
}
FIRSTS = {
    "rotation_y": (
        "    gCurrentRacerTransform.rotation.y_rotation = "
        "-obj->trans.rotation.y_rotation;\n",
        "    gCurrentRacerTransform.rotation.y_rotation = "
        "-obj->trans.rotation.y_rotation + {zero};\n",
    ),
    "rotation_x": (
        "    gCurrentRacerTransform.rotation.x_rotation = "
        "-obj->trans.rotation.x_rotation;\n",
        "    gCurrentRacerTransform.rotation.x_rotation = "
        "-obj->trans.rotation.x_rotation + {zero};\n",
    ),
}
SINKS = {
    "moved": (
        "    if (playerObjectMoved != FALSE) {\n",
        "    if (playerObjectMoved != FALSE + {zero}) {\n",
    ),
    "camera": (
        "    second_racer_camera_update(obj, racer, 1, updateRateF);\n",
        "    second_racer_camera_update(obj, racer, 1 + {zero}, updateRateF);\n",
    ),
    "vehicle": (
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES) {\n",
        "    if (racer->vehicleIDPrev < VEHICLE_BOSSES + {zero}) {\n",
    ),
    "unk201": (
        "    if (racer->unk201 == 0) {\n",
        "    if (racer->unk201 == {zero}) {\n",
    ),
}
ZEROS = {
    "gt_mul": "(postFactorSeed > 0.0f) * 0",
    "lt_mul": "(postFactorSeed < 0.0f) * 0",
    "eq_mul": "(postFactorSeed == 0.0f) * 0",
    "ne_mul": "(postFactorSeed != 0.0f) * 0",
    "gt_and": "(postFactorSeed > 0.0f) & 0",
    "comma": "(postFactorSeed > 0.0f, 0)",
    "ternary": "(postFactorSeed > 0.0f) ? 0 : 0",
}


def make(
    start_name: str,
    first_name: str,
    sink_name: str,
    zero_name: str,
) -> str:
    source = BASE
    start = STARTS[start_name]
    old_first, new_first = FIRSTS[first_name]
    old_sink, new_sink = SINKS[sink_name]
    if (
        source.count(start) != 1
        or source.count(old_first) != 1
        or source.count(old_sink) != 1
    ):
        raise ValueError(
            (
                start_name,
                source.count(start),
                first_name,
                source.count(old_first),
                sink_name,
                source.count(old_sink),
            )
        )
    source = source.replace(
        start,
        start + "    {\n        f32 postFactorSeed;\n",
        1,
    )
    source = source.replace(
        old_first,
        new_first.replace("{zero}", ZEROS[zero_name]),
        1,
    )
    source = source.replace(
        old_sink,
        new_sink.replace("{zero}", ZEROS[zero_name]),
        1,
    )
    end = source.rfind("\n}")
    if end < 0:
        raise ValueError("function close not found")
    return source[:end] + "    }\n" + source[end:]


def evaluate(case: tuple[str, str, str, str]) -> tuple:
    start_name, first_name, sink_name, zero_name = case
    tag = f"{start_name}_{first_name}_{sink_name}_{zero_name}"
    source = make(*case)
    path = f"/tmp/codex_postfactor_uninit_{tag}.c"
    trace = f"/tmp/codex_postfactor_uninit_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_postfactor_uninit_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_postfactor_uninit_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    f20_rows = []
    seed_rows = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
                elif "RACER-COLOR bit" in line and "reg=30 " in line:
                    f20_rows.append(line.strip())
                elif "RACER-FVAR" in line and "addr=-172 " in line:
                    seed_rows.append(line.strip())
    return tag, source, result, factor, f20_rows, seed_rows, proc.returncode


def main() -> None:
    cases = [
        (start_name, first_name, sink_name, zero_name)
        for start_name in STARTS
        for first_name in FIRSTS
        for sink_name in SINKS
        for zero_name in ZEROS
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[2].get("mismatch", 999999),
            not row[3].startswith("30/"),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, factor, f20_rows, seed_rows, returncode in rows:
        if result.get("mismatch") == 0:
            with open(
                f"/tmp/codex_postfactor_uninit_exact_{tag}.c",
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
            "f20colors",
            len(f20_rows),
            "seedrows",
            len(seed_rows),
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].startswith("30/") for row in rows),
        "exact",
        sum(row[2].get("mismatch") == 0 for row in rows),
    )


if __name__ == "__main__":
    main()
