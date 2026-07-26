#!/usr/bin/env python3
"""Sweep assignment-value, cast, and nested-comma forms for the final tilt."""

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


def branch(amount: int, form: str, cast_load: str, cast_damp: str, cast_delta: str) -> str:
    field = "obj->trans.rotation.x_rotation"
    load_value = {
        "none": field,
        "s16": f"(s16) {field}",
        "u16s16": f"(s16) (u16) {field}",
        "s32": f"(s32) {field}",
        "volatile": f"*(volatile s16 *) &{field}",
    }[cast_load]
    host = {
        "none": "var_v1",
        "s16": "(s16) var_v1",
        "u16s16": "(s16) (u16) var_v1",
        "s32": "(s32) var_v1",
        "volatile": "var_v1",
    }[cast_load]
    damp = f"{host} - (({host} * updateRate) >> 4)"
    damp = {
        "none": damp,
        "s16": f"(s16) ({damp})",
        "u16s16": f"(s16) (u16) ({damp})",
        "s32": f"(s32) ({damp})",
    }[cast_damp]
    delta = f"((var_t0 >> 1) * {amount} * updateRate) >> 1"
    delta = {
        "none": delta,
        "s16": f"(s16) ({delta})",
        "u16s16": f"(s16) (u16) ({delta})",
        "s32": f"(s32) ({delta})",
    }[cast_delta]
    load = f"var_v1 = {load_value}"
    first = f"{field} = {damp}"
    second = f"{field} -= {delta}"
    second_plain = f"{field} = {field} - ({delta})"
    forms = {
        "baseline": f"{load};\n                {first};\n                {second};",
        "plain": f"{load};\n                {first};\n                {second_plain};",
        "nested_outer": (
            f"{load};\n"
            f"                {field} = (({first}), {field} - ({delta}));"
        ),
        "nested_outer_value": (
            f"{load};\n"
            f"                {field} = ({first}, {field}) - ({delta});"
        ),
        "nested_outer_void": (
            f"{load};\n"
            f"                {field} = ((void) ({first}), {field} - ({delta}));"
        ),
        "nested_outer_cast": (
            f"{load};\n"
            f"                {field} = (({first}), (s16) {field} - ({delta}));"
        ),
        "nested_outer_u16": (
            f"{load};\n"
            f"                {field} = (({first}), (s16) (u16) {field} - ({delta}));"
        ),
        "comma_compound": (
            f"{load};\n"
            f"                ({first}, {second});"
        ),
        "comma_plain": (
            f"{load};\n"
            f"                ({first}, {second_plain});"
        ),
        "load_nested_outer": (
            f"{field} = (({load}), ({first}), {field} - ({delta}));"
        ),
        "load_comma_compound": (
            f"({load}, {first}, {second});"
        ),
    }
    body = forms[form]
    return "".join(f"                {line}\n" if i else f"                {line}\n"
                   for i, line in enumerate(body.splitlines()))


def block(
    form19: str,
    form30: str,
    cast_load: str,
    cast_damp: str,
    cast_delta: str,
) -> str:
    return (
        "            // Note: The following if/else has messed up t registers\n"
        "            if (!(gCurrentRacerInput & R_TRIG)) {\n"
        + branch(19, form19, cast_load, cast_damp, cast_delta)
        + "            } else {\n"
        + branch(30, form30, cast_load, cast_damp, cast_delta)
        + "            }\n"
    )


def cases() -> list[tuple[str, str]]:
    forms = (
        "baseline",
        "plain",
        "nested_outer",
        "nested_outer_value",
        "nested_outer_void",
        "nested_outer_cast",
        "nested_outer_u16",
        "comma_compound",
        "comma_plain",
        "load_nested_outer",
        "load_comma_compound",
    )
    casts_load = ("none", "s16", "u16s16", "s32")
    casts_result = ("none", "s16", "u16s16", "s32")
    result: list[tuple[str, str]] = [("baseline", BASE)]
    # First test every value/cast topology symmetrically.
    for form, cast_load, cast_damp, cast_delta in itertools.product(
        forms, casts_load, casts_result, casts_result
    ):
        tag = f"{form}_{cast_load}_{cast_damp}_{cast_delta}"
        result.append(
            (
                tag,
                replace_once(
                    BASE,
                    OLD,
                    block(form, form, cast_load, cast_damp, cast_delta),
                ),
            )
        )
    # Asymmetric branch forms catch free-list changes that only need one arm.
    for form in forms[1:]:
        for side in ("19", "30"):
            form19 = form if side == "19" else "baseline"
            form30 = form if side == "30" else "baseline"
            result.append(
                (
                    f"asym_{form}_{side}",
                    replace_once(
                        BASE,
                        OLD,
                        block(form19, form30, "none", "none", "none"),
                    ),
                )
            )
    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_rotvalue_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_rotvalue_{tag}.c").write_text(
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
