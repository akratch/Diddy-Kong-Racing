#!/usr/bin/env python3
"""Sweep allocator-sensitive source trees for the final plane rotation block."""

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
HOSTS = (
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
    "steerVisualRotationOffset",
    "pad4",
)

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
    count = source.count(old)
    if count != 1:
        raise ValueError(f"replacement anchor occurs {count} times")
    return source.replace(old, new, 1)


def steer(amount: int, form: str = "base") -> str:
    expressions = {
        "base": f"((var_t0 >> 1) * {amount} * updateRate) >> 1",
        "group_left": f"(((var_t0 >> 1) * {amount}) * updateRate) >> 1",
        "constant_left": f"({amount} * (var_t0 >> 1) * updateRate) >> 1",
        "update_left": f"(updateRate * ((var_t0 >> 1) * {amount})) >> 1",
        "update_middle": f"((var_t0 >> 1) * updateRate * {amount}) >> 1",
        "constant_group": f"((var_t0 >> 1) * ({amount} * updateRate)) >> 1",
    }
    return (
        "                obj->trans.rotation.x_rotation -= "
        f"{expressions[form]};\n"
    )


def damp_simple(host: str, form: str) -> str:
    assign = f"                {host} = obj->trans.rotation.x_rotation;\n"
    forms = {
        "base": (
            "                obj->trans.rotation.x_rotation = "
            f"{host} - (({host} * updateRate) >> 4);\n"
        ),
        "unwrapped": (
            "                obj->trans.rotation.x_rotation = "
            f"{host} - ({host} * updateRate >> 4);\n"
        ),
        "mul_reverse": (
            "                obj->trans.rotation.x_rotation = "
            f"{host} - ((updateRate * {host}) >> 4);\n"
        ),
        "negative_right": (
            "                obj->trans.rotation.x_rotation = "
            f"{host} + -(({host} * updateRate) >> 4);\n"
        ),
        "negative_left": (
            "                obj->trans.rotation.x_rotation = "
            f"-(({host} * updateRate) >> 4) + {host};\n"
        ),
        "compound": (
            "                obj->trans.rotation.x_rotation -= "
            f"({host} * updateRate) >> 4;\n"
        ),
        "comma": (
            "                obj->trans.rotation.x_rotation = "
            f"({host} = obj->trans.rotation.x_rotation, "
            f"{host} - (({host} * updateRate) >> 4));\n"
        ),
        "nested": (
            "                obj->trans.rotation.x_rotation = "
            f"({host} = obj->trans.rotation.x_rotation) - "
            f"(({host} * updateRate) >> 4);\n"
        ),
    }
    if form in {"comma", "nested"}:
        return forms[form]
    return assign + forms[form]


def damp_temp(host: str, temp: str, form: str) -> str:
    first = f"                {host} = obj->trans.rotation.x_rotation;\n"
    forms = {
        "product": (
            f"                {temp} = {host} * updateRate;\n"
            "                obj->trans.rotation.x_rotation = "
            f"{host} - ({temp} >> 4);\n"
        ),
        "shifted": (
            f"                {temp} = ({host} * updateRate) >> 4;\n"
            "                obj->trans.rotation.x_rotation = "
            f"{host} - {temp};\n"
        ),
        "mutate": (
            f"                {temp} = {host};\n"
            f"                {temp} *= updateRate;\n"
            "                obj->trans.rotation.x_rotation = "
            f"{host} - ({temp} >> 4);\n"
        ),
        "result": (
            f"                {temp} = {host} - (({host} * updateRate) >> 4);\n"
            f"                obj->trans.rotation.x_rotation = {temp};\n"
        ),
    }
    return first + forms[form]


def block(
    damp19: str,
    damp30: str,
    *,
    steer19: str | None = None,
    steer30: str | None = None,
    condition: str = "!(gCurrentRacerInput & R_TRIG)",
    reverse: bool = False,
) -> str:
    first = damp19 + (steer19 or steer(19))
    second = damp30 + (steer30 or steer(30))
    if reverse:
        first, second = second, first
    return (
        "            // Note: The following if/else has messed up t registers\n"
        f"            if ({condition}) {{\n"
        + first
        + "            } else {\n"
        + second
        + "            }\n"
    )


def cases() -> list[tuple[str, str]]:
    base_damp = damp_simple("var_v1", "base")
    result: list[tuple[str, str]] = [("baseline", BASE)]

    conditions = {
        "not_mask": "!(gCurrentRacerInput & R_TRIG)",
        "mask_eq_zero": "(gCurrentRacerInput & R_TRIG) == 0",
        "zero_eq_mask": "0 == (gCurrentRacerInput & R_TRIG)",
        "mask_ne_zero_false": "!((gCurrentRacerInput & R_TRIG) != 0)",
        "mask_eq_false": "(gCurrentRacerInput & R_TRIG) == FALSE",
        "notnot_false": "!!(gCurrentRacerInput & R_TRIG) == FALSE",
    }
    for tag, condition in conditions.items():
        body = block(base_damp, base_damp, condition=condition)
        result.append((f"condition_{tag}", replace_once(BASE, OLD, body)))

    reverse_conditions = {
        "mask": "gCurrentRacerInput & R_TRIG",
        "mask_ne_zero": "(gCurrentRacerInput & R_TRIG) != 0",
        "zero_ne_mask": "0 != (gCurrentRacerInput & R_TRIG)",
        "notnot": "!!(gCurrentRacerInput & R_TRIG)",
    }
    for tag, condition in reverse_conditions.items():
        body = block(base_damp, base_damp, condition=condition, reverse=True)
        result.append((f"reverse_{tag}", replace_once(BASE, OLD, body)))

    for host in HOSTS:
        for form in (
            "base",
            "unwrapped",
            "mul_reverse",
            "negative_right",
            "negative_left",
            "compound",
            "comma",
            "nested",
        ):
            damping = damp_simple(host, form)
            for scope, damp19, damp30 in (
                ("both", damping, damping),
                ("19", damping, base_damp),
                ("30", base_damp, damping),
            ):
                body = block(damp19, damp30)
                result.append(
                    (
                        f"simple_{host}_{form}_{scope}",
                        replace_once(BASE, OLD, body),
                    )
                )

    for temp in HOSTS:
        if temp == "var_v1":
            continue
        for form in ("product", "shifted", "mutate", "result"):
            damping = damp_temp("var_v1", temp, form)
            for scope, damp19, damp30 in (
                ("both", damping, damping),
                ("19", damping, base_damp),
                ("30", base_damp, damping),
            ):
                body = block(damp19, damp30)
                result.append(
                    (
                        f"temp_{temp}_{form}_{scope}",
                        replace_once(BASE, OLD, body),
                    )
                )

    for form in (
        "base",
        "group_left",
        "constant_left",
        "update_left",
        "update_middle",
        "constant_group",
    ):
        for scope, steer19, steer30 in (
            ("both", steer(19, form), steer(30, form)),
            ("19", steer(19, form), steer(30)),
            ("30", steer(19), steer(30, form)),
        ):
            body = block(
                base_damp,
                base_damp,
                steer19=steer19,
                steer30=steer30,
            )
            result.append(
                (
                    f"steer_{form}_{scope}",
                    replace_once(BASE, OLD, body),
                )
            )

    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_rotation_tree_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_rotation_tree_{tag}.c").write_text(
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
