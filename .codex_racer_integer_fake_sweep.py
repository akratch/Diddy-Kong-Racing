#!/usr/bin/env python3
"""Sweep the optimizer-erased integer use already present in the wave block."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
FORCED = "/tmp/codex_run_analysis.sh"
OLD = "            if ((!racerSteerAngle)) {}\n"
NAMES = (
    "pad5",
    "pad7",
    "racerMiscAssetIdx",
    "racerSteerAngle",
    "var_t0",
    "var_v0",
    "var_v1",
    "var_a0",
    "temp_t7",
    "pad2",
    "xRotationOffset",
    "zRotationOffset",
    "i",
    "var_t9",
    "racerTrickType",
    "playerObjectMoved",
    "steerVisualRotationOffset",
    "pad4",
    "newSpinoutTimer",
    "spA3",
    "spA2",
    "spA1",
)
FORMS = {
    "not": "            if ((!{name})) {{}}\n",
    "value": "            if ({name}) {{}}\n",
    "comma0": "            if (({name}, 0)) {{}}\n",
    "self": "            {name} = {name};\n",
    "zero": "            {name} = 0;\n",
}


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def ranges(indices: list[int]) -> list[tuple[int, int]]:
    if not indices:
        return []
    result = []
    first = previous = indices[0]
    for index in indices[1:]:
        if index != previous + 1:
            result.append((first, previous))
            first = index
        previous = index
    result.append((first, previous))
    return result


def compare(obj: str) -> dict[str, object]:
    _, candidate = ORACLE["dump_object"](obj)
    if len(candidate) != len(TARGET):
        return {
            "insns": len(candidate),
            "regs": 10000 + abs(len(candidate) - len(TARGET)),
            "fp": 10000 + abs(len(candidate) - len(TARGET)),
            "ranges": [],
        }
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    fp_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if re.findall(r"\$f\d+", expected[1])
        != re.findall(r"\$f\d+", actual[1])
    ]
    return {
        "insns": len(candidate),
        "regs": len(reg_bad),
        "fp": len(fp_bad),
        "ranges": ranges(reg_bad),
    }


def evaluate(case: tuple[str, str]) -> tuple:
    name, form = case
    if name == "baseline":
        tag = "baseline"
        source = BASE
    elif name == "remove":
        tag = "remove"
        source = BASE.replace(OLD, "", 1)
    else:
        tag = f"{form}_{name}"
        source = BASE.replace(OLD, FORMS[form].format(name=name), 1)
    path = f"/tmp/codex_integer_fake_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    natural = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_integer_fake_{tag}_natural.o",
    )
    forced_obj = f"/tmp/codex_integer_fake_{tag}_forced.o"
    proc = subprocess.run(
        [FORCED, path, forced_obj, forced_obj + ".trace"],
        check=False,
        capture_output=True,
        text=True,
    )
    forced = (
        compare(forced_obj)
        if proc.returncode == 0
        else {"error": proc.stderr[-1000:], "regs": 20000, "fp": 20000}
    )
    return tag, natural, forced


def main() -> None:
    cases = [("baseline", ""), ("remove", "")]
    cases.extend((name, form) for form in FORMS for name in NAMES)
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[2].get("fp", 20000),
            row[2].get("regs", 20000),
            row[1].get("norm", 9999),
        )
    )
    for tag, natural, forced in rows:
        print(
            tag,
            "forced",
            forced,
            "natural",
            ORACLE["concise"](natural),
            natural.get("fp"),
        )


if __name__ == "__main__":
    main()
