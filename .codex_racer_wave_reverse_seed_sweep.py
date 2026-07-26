#!/usr/bin/env python3
"""Sweep counter-first/retained-endpoint seeds in the outer wave condition."""

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
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->vehicleIDPrev != VEHICLE_WIZPIG && gRacerWaveCount != 0) {
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""
HOSTS = (
    "pad5",
    "pad7",
    "racerMiscAssetIdx",
    "racerSteerAngle",
    "var_t0",
    "var_v0",
    "var_v1",
    "temp_t7",
    "pad2",
    "xRotationOffset",
    "zRotationOffset",
    "i",
    "var_t9",
    "racerTrickType",
    "steerVisualRotationOffset",
    "pad4",
)


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


def opening(host: str, form: str, loop_form: str, compare_form: str) -> str:
    conditions = {
        "counter_only": (
            "(var_a0 = gRacerWaveCount - 1, gRacerWaveCount != 0)"
        ),
        "counter_copy": (
            "(var_a0 = gRacerWaveCount - 1, "
            f"{host} = var_a0, gRacerWaveCount != 0)"
        ),
        "copy_counter": (
            f"({host} = var_a0 = gRacerWaveCount - 1, "
            "gRacerWaveCount != 0)"
        ),
        "counter_host": (
            f"(var_a0 = {host} = gRacerWaveCount - 1, "
            "gRacerWaveCount != 0)"
        ),
        "count_first_counter": (
            "gRacerWaveCount != 0 && "
            "(var_a0 = gRacerWaveCount - 1, TRUE)"
        ),
        "count_first_copy": (
            "gRacerWaveCount != 0 && "
            f"(var_a0 = gRacerWaveCount - 1, {host} = var_a0, TRUE)"
        ),
    }
    prefixes = {
        "counter_only": f"        {host} = var_a0;\n",
        "counter_copy": "",
        "copy_counter": "",
        "counter_host": "",
        "count_first_counter": f"        {host} = var_a0;\n",
        "count_first_copy": "",
    }
    loops = {
        "for_empty_init": (
            "        for (;\n"
            "             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5; var_a0--) {}\n"
        ),
        "while": (
            "        while (var_a0 >= 0 && "
            "gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5) {\n"
            "            var_a0--;\n"
            "        }\n"
        ),
        "do_guard": (
            "        if (var_a0 >= 0 && "
            "gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5) {\n"
            "            do {\n"
            "                var_a0--;\n"
            "            } while (var_a0 >= 0 && "
            "gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5);\n"
            "        }\n"
        ),
    }
    comparisons = {
        "host": f"var_a0 == {host}",
        "host_reverse": f"{host} == var_a0",
        "global": "var_a0 == gRacerWaveCount - 1",
    }
    return (
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && "
        "racer->vehicleIDPrev != VEHICLE_WIZPIG && "
        f"{conditions[form]}) {{\n"
        "        // UNMATCHED\n"
        + prefixes[form]
        + loops[loop_form]
        + f"\n        if ({comparisons[compare_form]}) {{\n"
        "            var_a0--;\n"
        "        }\n"
    )


def cases() -> list[tuple[str, str]]:
    result: list[tuple[str, str]] = [("baseline", BASE)]
    for host, form, loop_form, compare_form in itertools.product(
        HOSTS,
        (
            "counter_only",
            "counter_copy",
            "copy_counter",
            "counter_host",
            "count_first_counter",
            "count_first_copy",
        ),
        ("for_empty_init", "while", "do_guard"),
        ("host", "host_reverse", "global"),
    ):
        tag = "_".join((host, form, loop_form, compare_form))
        result.append(
            (tag, replace_once(BASE, OLD, opening(host, form, loop_form, compare_form)))
        )
    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_wavereverse_{tag}.o")
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
    if (
        result.get("fp") == EXPECTED_FP
        and (len(reg_bad) < 28 or wave_bad < 8)
    ):
        pathlib.Path(f"/tmp/codex_wavereverse_{tag}.c").write_text(
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
        if len(seen) >= 100:
            break
    print(f"tested={len(rows)} unique={len(seen)}")


if __name__ == "__main__":
    main()
