#!/usr/bin/env python3
"""Sweep scoped/type-qualified endpoint locals for the opening wave loop."""

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
OLD_OUTER = """\
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->vehicleIDPrev != VEHICLE_WIZPIG && gRacerWaveCount != 0) {
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""
TAIL = """\

        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;
"""


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


def opening(
    dtype: str,
    qualifier: str,
    declaration: str,
    loop_form: str,
    compare_form: str,
) -> str:
    declaration_text = f"{qualifier}{dtype} waveEnd"
    if declaration == "initialized":
        first = f"        {declaration_text} = gRacerWaveCount - 1;\n"
    else:
        first = (
            f"        {declaration_text};\n"
            "        waveEnd = gRacerWaveCount - 1;\n"
        )
    loops = {
        "for": (
            "        for (var_a0 = waveEnd;\n"
            "             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5; var_a0--) {}\n"
        ),
        "split_for": (
            "        var_a0 = waveEnd;\n"
            "        for (;\n"
            "             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5; var_a0--) {}\n"
        ),
        "while": (
            "        var_a0 = waveEnd;\n"
            "        while (var_a0 >= 0 && "
            "gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5) {\n"
            "            var_a0--;\n"
            "        }\n"
        ),
        "chain_left": (
            "        waveEnd = var_a0 = gRacerWaveCount - 1;\n"
            "        for (;\n"
            "             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5; var_a0--) {}\n"
        ),
        "chain_right": (
            "        var_a0 = waveEnd = gRacerWaveCount - 1;\n"
            "        for (;\n"
            "             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < "
            "obj->trans.y_position + 5; var_a0--) {}\n"
        ),
    }
    if loop_form.startswith("chain_"):
        first = f"        {declaration_text};\n"
    comparisons = {
        "cached": "var_a0 == waveEnd",
        "cached_cast": f"var_a0 == ({dtype}) waveEnd",
        "cached_s32": "var_a0 == (s32) waveEnd",
        "sub_zero": "(var_a0 - waveEnd) == 0",
        "zero_sub": "(waveEnd - var_a0) == 0",
        "xor_zero": "(var_a0 ^ waveEnd) == 0",
    }
    return (
        "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && "
        "racer->vehicleIDPrev != VEHICLE_WIZPIG && gRacerWaveCount != 0) {\n"
        + first
        + loops[loop_form]
        + f"\n        if ({comparisons[compare_form]}) {{\n"
        "            var_a0--;\n"
        "        }\n"
    )


def cases() -> list[tuple[str, str]]:
    dtypes = ("s32", "u32", "s16", "u16", "s8", "u8")
    qualifiers = ("", "register ", "const ")
    declarations = ("split", "initialized")
    loop_forms = ("for", "split_for", "while", "chain_left", "chain_right")
    compare_forms = (
        "cached",
        "cached_cast",
        "cached_s32",
        "sub_zero",
        "zero_sub",
        "xor_zero",
    )
    result: list[tuple[str, str]] = [("baseline", BASE)]
    for dtype, qualifier, declaration, loop_form, compare_form in itertools.product(
        dtypes, qualifiers, declarations, loop_forms, compare_forms
    ):
        if qualifier == "const " and declaration == "split":
            continue
        body = opening(
            dtype,
            qualifier,
            declaration,
            loop_form,
            compare_form,
        )
        tag = "_".join(
            (
                dtype,
                qualifier.strip() or "plain",
                declaration,
                loop_form,
                compare_form,
            )
        )
        result.append((tag, replace_once(BASE, OLD_OUTER, body)))

    # Reuse each dormant declaration but alter its type. This preserves the
    # declaration count and often the frame while changing Uopt's web class.
    dormant = ("pad5", "pad7", "newSpinoutTimer", "pad2", "var_t9", "pad4")
    for host, dtype, loop_form in itertools.product(
        dormant, dtypes, ("for", "split_for", "while")
    ):
        declaration_re = re.compile(
            rf"^    (?:s32|s8) {re.escape(host)};$", re.MULTILINE
        )
        source, count = declaration_re.subn(f"    {dtype} {host};", BASE, count=1)
        if count != 1:
            continue
        body = opening(dtype, "", "split", loop_form, "cached").replace(
            f"{dtype} waveEnd;\n        waveEnd", f"/* reuse {host} */\n        {host}",
            1,
        ).replace("waveEnd", host)
        result.append(
            (
                f"reuse_{host}_{dtype}_{loop_form}",
                replace_once(source, OLD_OUTER, body),
            )
        )

    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_wavescope_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_wavescope_{tag}.c").write_text(
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
