#!/usr/bin/env python3
"""Sweep explicit pointer-induction source forms for the opening wave loop."""

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
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


def body(
    declaration: str,
    endpoint: str,
    pointer_init: str,
    condition: str,
    update: str,
    loop_kind: str,
) -> str:
    decls = {
        "inner": "        WaterProperties **wavePtr;\n",
        "inner_register": "        register WaterProperties **wavePtr;\n",
        "inner_volatile": "        WaterProperties **volatile wavePtr;\n",
    }
    endpoint_setup = {
        "direct": "",
        "var_v1": "        var_v1 = gRacerWaveCount - 1;\n",
        "var_v0": "        var_v0 = gRacerWaveCount - 1;\n",
        "i": "        i = gRacerWaveCount - 1;\n",
    }
    end = {
        "direct": "gRacerWaveCount - 1",
        "var_v1": "var_v1",
        "var_v0": "var_v0",
        "i": "i",
    }[endpoint]
    ptr = {
        "from_counter": "&gRacerCurrentWave[var_a0]",
        "from_end": f"&gRacerCurrentWave[{end}]",
        "base_plus_counter": "gRacerCurrentWave + var_a0",
        "base_plus_end": f"gRacerCurrentWave + {end}",
    }[pointer_init]
    cond_wave = {
        "deref": "(*wavePtr)->waveHeight",
        "index0": "wavePtr[0]->waveHeight",
        "field": "wavePtr[0][0].waveHeight",
        "normal": "gRacerCurrentWave[var_a0]->waveHeight",
    }[condition]
    update_expr = {
        "both_comma": "var_a0--, wavePtr--",
        "ptr_first": "wavePtr--, var_a0--",
        "counter_only": "var_a0--",
        "body_both": "",
    }[update]
    init = {
        "counter_then_ptr": f"var_a0 = {end}, wavePtr = {ptr}",
        "ptr_then_counter": f"wavePtr = {ptr}, var_a0 = {end}",
        "split": "",
    }[loop_kind]
    prefix = decls[declaration] + endpoint_setup[endpoint]
    if loop_kind == "split":
        prefix += f"        var_a0 = {end};\n        wavePtr = {ptr};\n"
    if update == "body_both":
        loop = (
            f"        for ({init};\n"
            f"             var_a0 >= 0 && {cond_wave} < obj->trans.y_position + 5;) {{\n"
            "            var_a0--;\n"
            "            wavePtr--;\n"
            "        }\n"
        )
    else:
        loop = (
            f"        for ({init};\n"
            f"             var_a0 >= 0 && {cond_wave} < obj->trans.y_position + 5; "
            f"{update_expr}) {{}}\n"
        )
    return (
        prefix
        + loop
        + f"\n        if (var_a0 == {end}) {{\n"
        "            var_a0--;\n"
        "        }\n"
    )


def cases() -> list[tuple[str, str]]:
    result: list[tuple[str, str]] = [("baseline", BASE)]
    for args in itertools.product(
        ("inner", "inner_register"),
        ("direct", "var_v1", "var_v0", "i"),
        ("from_counter", "from_end", "base_plus_counter", "base_plus_end"),
        ("deref", "index0", "field", "normal"),
        ("both_comma", "ptr_first", "counter_only", "body_both"),
        ("counter_then_ptr", "ptr_then_counter", "split"),
    ):
        declaration, endpoint, pointer_init, condition, update, loop_kind = args
        # A pointer unused by either the condition or update optimizes away and
        # duplicates the baseline; retain only one representative.
        if condition == "normal" and update == "counter_only":
            continue
        tag = "_".join(args)
        result.append((tag, replace_once(BASE, OLD, body(*args))))
    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_waveptr_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_waveptr_{tag}.c").write_text(
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
