#!/usr/bin/env python3
"""Sweep algebraically neutral endpoint uses inside the hot wave loop."""

from __future__ import annotations

import concurrent.futures
import itertools
import pathlib
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
TARGET = ORACLE["TARGET_INSNS"]
BASE_PATH = pathlib.Path("/tmp/codex_gpr_final_spinoffset_var_v0.c")
BASE = BASE_PATH.read_text(encoding="utf-8")
EXPECTED_FP = {
    "f0": 131,
    "f2": 66,
    "f4": 188,
    "f6": 188,
    "f8": 187,
    "f10": 188,
    "f12": 62,
    "f14": 50,
    "f16": 8,
    "f18": 190,
    "f20": 74,
    "f21": 2,
}
REGISTER_RE = re.compile(
    r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)"
)
WAVE_INDICES = {54, 55, 56, 59, 71, 72, 83, 85}
OLD = """\
        for (var_a0 = gRacerWaveCount - 1;
             (var_a0 + 0) >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}
"""
END = "(gRacerWaveCount - 1)"


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


def cases() -> list[tuple[str, str]]:
    indices = {
        "base": "var_a0",
        "add_delta": f"var_a0 + ({END} - {END})",
        "add_then_sub": f"(var_a0 + {END}) - {END}",
        "sub_then_add": f"(var_a0 - {END}) + {END}",
        "xor_pair": f"var_a0 ^ ({END} ^ {END})",
        "or_zero": f"var_a0 | ({END} & 0)",
        "and_ones": f"var_a0 & ~({END} & 0)",
        "mul_zero": f"var_a0 + ({END} * 0)",
        "eq_minus_one": f"var_a0 + (({END} == {END}) - 1)",
        "ne_sub": f"var_a0 - ({END} != {END})",
    }
    guards = {
        "base": "(var_a0 + 0) >= 0",
        "add_delta": f"(var_a0 + ({END} - {END})) >= 0",
        "add_then_sub": f"((var_a0 + {END}) - {END}) >= 0",
        "sub_then_add": f"((var_a0 - {END}) + {END}) >= 0",
        "eq_and": f"({END} == {END}) && var_a0 >= 0",
        "ne_not_and": f"!({END} != {END}) && var_a0 >= 0",
        "eq_or": f"({END} != {END}) || var_a0 >= 0",
        "xor_pair": f"(var_a0 ^ ({END} ^ {END})) >= 0",
        "mul_zero": f"(var_a0 + ({END} * 0)) >= 0",
    }
    updates = {
        "postdec": "var_a0--",
        "predec": "--var_a0",
        "sub_eq": f"var_a0 -= ({END} == {END})",
        "assign_sub_eq": f"var_a0 = var_a0 - ({END} == {END})",
        "add_ne_minus_one": f"var_a0 += ({END} != {END}) - 1",
        "assign_add_ne": f"var_a0 = var_a0 + ({END} != {END}) - 1",
        "delta_then_dec": f"var_a0 = var_a0 + ({END} - {END}) - 1",
        "add_sub_then_dec": f"var_a0 = (var_a0 + {END}) - {END} - 1",
        "sub_add_then_dec": f"var_a0 = (var_a0 - {END}) + {END} - 1",
    }
    initializers = {
        "base": f"var_a0 = {END}",
        "comma_dup": f"var_a0 = ({END}, {END})",
        "add_zero": f"var_a0 = {END} + ({END} - {END})",
        "eq_zero": f"var_a0 = {END} + (({END} == {END}) - 1)",
    }

    result: list[tuple[str, str]] = [("baseline", BASE)]
    for (init_tag, initializer), (guard_tag, guard), (
        index_tag,
        index,
    ), (update_tag, update) in itertools.product(
        initializers.items(), guards.items(), indices.items(), updates.items()
    ):
        if (
            init_tag == "base"
            and guard_tag == "base"
            and index_tag == "base"
            and update_tag == "postdec"
        ):
            continue
        body = (
            f"        for ({initializer};\n"
            f"             {guard} && gRacerCurrentWave[{index}]->waveHeight < "
            f"obj->trans.y_position + 5; {update}) {{}}\n"
        )
        tag = "_".join((init_tag, guard_tag, index_tag, update_tag))
        result.append((tag, replace_once(BASE, OLD, body)))

    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_wavealgebra_{tag}.o")
    result = ORACLE["evaluate"](source, keep=str(obj))
    if not result.get("ok") or result.get("insns") != len(TARGET):
        obj.unlink(missing_ok=True)
        return tag, source, result, [], 10000, 10000
    _, candidate = ORACLE["dump_object"](str(obj))
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    wave_bad = len(WAVE_INDICES.intersection(reg_bad))
    outside_bad = len(reg_bad) - wave_bad
    if result.get("fp") == EXPECTED_FP and (
        len(reg_bad) < 26 or wave_bad < 7
    ):
        pathlib.Path(f"/tmp/codex_wavealgebra_{tag}.c").write_text(
            source, encoding="utf-8"
        )
    else:
        obj.unlink(missing_ok=True)
    return tag, source, result, reg_bad, wave_bad, outside_bad


def main() -> None:
    all_cases = cases()
    print(f"base={BASE_PATH} cases={len(all_cases)}")
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(worker, all_cases))
    rows.sort(
        key=lambda row: (
            len(row[3]) if row[3] else 10000,
            row[4],
            row[5],
            row[2].get("norm", 10000),
            row[0],
        )
    )
    seen: set[tuple] = set()
    for tag, _source, result, reg_bad, wave_bad, outside_bad in rows:
        fingerprint = (result.get("sha1"), tuple(reg_bad))
        if fingerprint in seen:
            continue
        seen.add(fingerprint)
        print(
            tag,
            ORACLE["concise"](result),
            f"fp_exact={result.get('fp') == EXPECTED_FP}",
            f"reg={len(reg_bad)} wave={wave_bad} outside={outside_bad}",
            reg_bad[:100],
        )
        if len(seen) >= 120:
            break
    print(f"tested={len(rows)} unique={len(seen)}")


if __name__ == "__main__":
    main()
