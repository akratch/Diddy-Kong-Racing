#!/usr/bin/env python3
"""Sweep explicit source webs for the R-trigger value live into final tilt."""

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
DRAG_OLD = """\
            if (!(gCurrentRacerInput & R_TRIG) || racer->groundedWheels == 0 || racer->zipperDirCorrection != 0) {
                var_f20 = racer->velocity * var_t0 * 0.00015;
                obj->x_velocity -= racer->ox3 * var_f20;
                obj->y_velocity -= racer->oy3 * var_f20;
                obj->z_velocity -= racer->oz3 * var_f20;
            }
"""
ROTATION_OLD = """\
            // Note: The following if/else has messed up t registers
            if (!(gCurrentRacerInput & R_TRIG)) {
"""
HOSTS = (
    "pad5",
    "pad7",
    "racerMiscAssetIdx",
    "racerSteerAngle",
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
    "steerVisualRotationOffset",
    "pad4",
)


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


def drag(host: str, web_type: str, first_form: str, refresh_form: str) -> str:
    mask = "gCurrentRacerInput & R_TRIG"
    if web_type == "mask":
        value = mask
        false_test = f"!{host}"
    elif web_type == "boolean":
        value = f"!({mask})"
        false_test = host
    else:
        value = "gCurrentRacerInput"
        false_test = f"!({host} & R_TRIG)"
    prefix = ""
    conditions = {
        "split": false_test,
        "assign_eq": f"({host} = {value}) == 0" if web_type != "boolean" else f"({host} = {value}) != 0",
        "assign_not": f"!({host} = {value})" if web_type != "boolean" else f"!!({host} = {value})",
        "comma": f"({host} = {value}, {false_test})",
    }
    if first_form == "split":
        prefix = f"            {host} = {value};\n"
    refresh = {
        "split": f"                {host} = {value};\n",
        "self_assign": f"                {host} = ({host} = {value});\n",
        "comma": f"                ({host} = {value}, (void) 0);\n",
        "none": "",
    }[refresh_form]
    condition = conditions[first_form]
    return (
        prefix
        + f"            if ({condition} || racer->groundedWheels == 0 || "
        "racer->zipperDirCorrection != 0) {\n"
        "                var_f20 = racer->velocity * var_t0 * 0.00015;\n"
        "                obj->x_velocity -= racer->ox3 * var_f20;\n"
        "                obj->y_velocity -= racer->oy3 * var_f20;\n"
        "                obj->z_velocity -= racer->oz3 * var_f20;\n"
        + refresh
        + "            }\n"
    )


def final_condition(host: str, web_type: str, form: str) -> str:
    tests = {
        "mask": {
            "not": f"!{host}",
            "eq_zero": f"{host} == 0",
            "zero_eq": f"0 == {host}",
            "false_eq": f"{host} == FALSE",
        },
        "boolean": {
            "not": host,
            "eq_zero": f"{host} != 0",
            "zero_eq": f"0 != {host}",
            "false_eq": f"{host} != FALSE",
        },
        "raw": {
            "not": f"!({host} & R_TRIG)",
            "eq_zero": f"({host} & R_TRIG) == 0",
            "zero_eq": f"0 == ({host} & R_TRIG)",
            "false_eq": f"({host} & R_TRIG) == FALSE",
        },
    }
    return (
        "            // Note: The following if/else has messed up t registers\n"
        f"            if ({tests[web_type][form]}) {{\n"
    )


def cases() -> list[tuple[str, str]]:
    result: list[tuple[str, str]] = [("baseline", BASE)]
    for host, web_type, first_form, refresh_form, final_form in itertools.product(
        HOSTS,
        ("mask", "boolean", "raw"),
        ("split", "assign_eq", "assign_not", "comma"),
        ("split", "self_assign", "comma", "none"),
        ("not", "eq_zero", "zero_eq", "false_eq"),
    ):
        # Without a refresh, the explicit source differs whenever the drag
        # branch executes; still keep one spelling to test optimizer CSE.
        if refresh_form == "none" and final_form != "not":
            continue
        source = replace_once(
            BASE,
            DRAG_OLD,
            drag(host, web_type, first_form, refresh_form),
        )
        source = replace_once(
            source,
            ROTATION_OLD,
            final_condition(host, web_type, final_form),
        )
        tag = "_".join(
            (host, web_type, first_form, refresh_form, final_form)
        )
        result.append((tag, source))
    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_inputweb_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_inputweb_{tag}.c").write_text(
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
