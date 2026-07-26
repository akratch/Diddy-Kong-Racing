#!/usr/bin/env python3
"""Place the erased racerSteerAngle use at every legal early statement boundary."""

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
FAKE = "if ((!racerSteerAngle)) {}"


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
        delta = abs(len(candidate) - len(TARGET))
        return {"insns": len(candidate), "regs": 10000 + delta, "fp": 10000 + delta}
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


def placement_sources() -> list[tuple[str, str, str]]:
    source = BASE.replace(OLD, "", 1)
    lines = source.splitlines(True)
    function_start = next(
        index for index, line in enumerate(lines)
        if line.startswith("void func_80049794")
    )
    first_statement = next(
        index for index in range(function_start, len(lines))
        if "if (func_8000E138())" in lines[index]
    )
    final_statement = next(
        index for index in range(first_statement, len(lines))
        if "racerSteerAngle = racer->steerAngle;" in lines[index]
    )
    balance = 0
    candidates = [("remove", source, "removed")]
    for index in range(function_start, final_statement):
        line = lines[index]
        clean = re.sub(r"//.*", "", line)
        balance += clean.count("(") - clean.count(")")
        stripped = clean.strip()
        if index < first_statement or balance != 0:
            continue
        if not (
            stripped.endswith(";")
            or stripped.endswith("{}")
            or stripped == "}"
        ):
            continue
        indent = re.match(r"[ \t]*", line).group(0)
        inserted = lines[: index + 1] + [indent + FAKE + "\n"] + lines[index + 1 :]
        tag = f"p{index + 1:04d}"
        context = stripped[-80:]
        candidates.append((tag, "".join(inserted), context))
    return candidates


def forced_evaluate(case: tuple[str, str, str]) -> tuple:
    tag, source, context = case
    path = f"/tmp/codex_integer_fake_placement_{tag}.c"
    obj = f"/tmp/codex_integer_fake_placement_{tag}_forced.o"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    proc = subprocess.run(
        [FORCED, path, obj, obj + ".trace"],
        check=False,
        capture_output=True,
        text=True,
    )
    metrics = (
        compare(obj)
        if proc.returncode == 0
        else {"regs": 20000, "fp": 20000, "error": proc.stderr[-500:]}
    )
    return tag, source, context, metrics


def main() -> None:
    cases = placement_sources()
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(forced_evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[3].get("fp", 20000),
            row[3].get("regs", 20000),
        )
    )
    for rank, (tag, source, context, forced) in enumerate(rows):
        natural = {}
        if rank < 24 or forced.get("regs", 20000) <= 51:
            natural = ORACLE["evaluate"](
                source,
                keep=f"/tmp/codex_integer_fake_placement_{tag}_natural.o",
            )
        print(
            tag,
            repr(context),
            "forced",
            forced,
            "natural",
            ORACLE["concise"](natural) if natural else "-",
            natural.get("fp"),
        )
    print("tested", len(rows))


if __name__ == "__main__":
    main()
