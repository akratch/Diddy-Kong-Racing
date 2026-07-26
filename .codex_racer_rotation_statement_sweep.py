#!/usr/bin/env python3
"""Sweep statement boundaries around the final plane rotation updates."""

from __future__ import annotations

import concurrent.futures
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
ROTATION_INDICES = {
    1656,
    1667,
    1682,
    1683,
    1684,
    1685,
    1687,
    1688,
    1689,
    1690,
    1691,
    1701,
    1702,
    1703,
    1704,
    1706,
    1707,
    1708,
    1709,
}
OLD = """\
            // Note: The following if/else has messed up t registers
            if (!(gCurrentRacerInput & R_TRIG)) {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }
"""


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


def expressions(amount: int) -> tuple[str, str, str, str]:
    load = "var_v1 = obj->trans.rotation.x_rotation"
    damp = (
        "obj->trans.rotation.x_rotation = "
        "var_v1 - ((var_v1 * updateRate) >> 4)"
    )
    compound = (
        "obj->trans.rotation.x_rotation -= "
        f"((var_t0 >> 1) * {amount} * updateRate) >> 1"
    )
    plain = (
        "obj->trans.rotation.x_rotation = "
        "obj->trans.rotation.x_rotation - "
        f"(((var_t0 >> 1) * {amount} * updateRate) >> 1)"
    )
    return load, damp, compound, plain


def branch(amount: int, form: str) -> str:
    load, damp, compound, plain = expressions(amount)
    indent = "                "
    forms = {
        "baseline": f"{indent}{load};\n{indent}{damp};\n{indent}{compound};\n",
        "load_damp_comma": (
            f"{indent}{load},\n"
            f"{indent}    {damp};\n"
            f"{indent}{compound};\n"
        ),
        "damp_steer_comma": (
            f"{indent}{load};\n"
            f"{indent}{damp},\n"
            f"{indent}    {compound};\n"
        ),
        "all_comma": (
            f"{indent}{load},\n"
            f"{indent}    {damp},\n"
            f"{indent}    {compound};\n"
        ),
        "all_comma_parens": (
            f"{indent}({load},\n"
            f"{indent} {damp},\n"
            f"{indent} {compound});\n"
        ),
        "all_comma_void": (
            f"{indent}(void) ({load},\n"
            f"{indent}        {damp},\n"
            f"{indent}        {compound});\n"
        ),
        "damp_steer_parens": (
            f"{indent}{load};\n"
            f"{indent}({damp}, {compound});\n"
        ),
        "load_damp_parens": (
            f"{indent}({load}, {damp});\n"
            f"{indent}{compound};\n"
        ),
        "plain_baseline": (
            f"{indent}{load};\n{indent}{damp};\n{indent}{plain};\n"
        ),
        "plain_damp_steer_comma": (
            f"{indent}{load};\n"
            f"{indent}{damp},\n"
            f"{indent}    {plain};\n"
        ),
        "plain_all_comma": (
            f"{indent}{load},\n"
            f"{indent}    {damp},\n"
            f"{indent}    {plain};\n"
        ),
        "direct_compounds_separate": (
            f"{indent}obj->trans.rotation.x_rotation -= "
            "(obj->trans.rotation.x_rotation * updateRate) >> 4;\n"
            f"{indent}{compound};\n"
        ),
        "direct_compounds_comma": (
            f"{indent}obj->trans.rotation.x_rotation -= "
            "(obj->trans.rotation.x_rotation * updateRate) >> 4,\n"
            f"{indent}    {compound};\n"
        ),
        "if_comma_true": (
            f"{indent}if (({load}, TRUE)) {{\n"
            f"{indent}    {damp};\n"
            f"{indent}    {compound};\n"
            f"{indent}}}\n"
        ),
        "do_once": (
            f"{indent}do {{\n"
            f"{indent}    {load};\n"
            f"{indent}    {damp};\n"
            f"{indent}    {compound};\n"
            f"{indent}}} while (FALSE);\n"
        ),
        "nested_scope": (
            f"{indent}{{\n"
            f"{indent}    {load};\n"
            f"{indent}    {damp};\n"
            f"{indent}    {compound};\n"
            f"{indent}}}\n"
        ),
    }
    return forms[form]


def block(form19: str, form30: str) -> str:
    return (
        "            // Note: The following if/else has messed up t registers\n"
        "            if (!(gCurrentRacerInput & R_TRIG)) {\n"
        + branch(19, form19)
        + "            } else {\n"
        + branch(30, form30)
        + "            }\n"
    )


def cases() -> list[tuple[str, str]]:
    forms = (
        "baseline",
        "load_damp_comma",
        "damp_steer_comma",
        "all_comma",
        "all_comma_parens",
        "all_comma_void",
        "damp_steer_parens",
        "load_damp_parens",
        "plain_baseline",
        "plain_damp_steer_comma",
        "plain_all_comma",
        "direct_compounds_separate",
        "direct_compounds_comma",
        "if_comma_true",
        "do_once",
        "nested_scope",
    )
    result = []
    for form19 in forms:
        for form30 in forms:
            result.append(
                (
                    f"{form19}__{form30}",
                    replace_once(BASE, OLD, block(form19, form30)),
                )
            )
    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_rotstmt_{tag}.o")
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
    rotation_bad = len(ROTATION_INDICES.intersection(reg_bad))
    outside_bad = len(reg_bad) - rotation_bad
    if (
        result.get("fp") == EXPECTED_FP
        and (len(reg_bad) < 28 or rotation_bad < 19)
    ):
        pathlib.Path(f"/tmp/codex_rotstmt_{tag}.c").write_text(
            source, encoding="utf-8"
        )
    else:
        obj.unlink(missing_ok=True)
    return tag, source, result, reg_bad, rotation_bad, outside_bad


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
    for tag, _source, result, reg_bad, rotation_bad, outside_bad in rows:
        fingerprint = (result.get("sha1"), tuple(reg_bad))
        if fingerprint in seen:
            continue
        seen.add(fingerprint)
        print(
            tag,
            ORACLE["concise"](result),
            f"fp_exact={result.get('fp') == EXPECTED_FP}",
            f"reg={len(reg_bad)} rot={rotation_bad} outside={outside_bad}",
            reg_bad[:100],
        )
        if len(seen) >= 100:
            break
    print(f"tested={len(rows)} unique={len(seen)}")


if __name__ == "__main__":
    main()
