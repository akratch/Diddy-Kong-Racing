#!/usr/bin/env python3
"""Sweep integer temporary-web reuse immediately before plane pitch damping."""

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
HUMAN_OLD = """\
                        var_t0 *= gCurrentRacerHandlingStat;
                        var_v0 = var_t0 * updateRate;
                        racer->steerVisualRotation -= var_v0 & 0xFFFF;
"""
COMPUTER_OLD = """\
                        var_t0 = gCurrentStickX * 4;
                        var_v0 = var_t0 * updateRate;
                        racer->steerVisualRotation -= var_v0 & 0xFFFF;
"""
OFFSET_OLD = """\
                var_v0 = -(racer->x_rotation_vel & 0xFFFF);
                if (var_v0 > 0x8000) {
                    var_v0 -= 0xFFFF;
                }
                if (var_v0 < -0x8000) {
                    var_v0 += 0xFFFF;
                }
                racer->x_rotation_vel += (var_v0 * updateRate) >> 4;
"""
FINAL_STEER_OLD = """\
                racer->steerVisualRotation -= (var_t0 * updateRate) & 0xFFFF;
"""


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    if source.count(old) != 1:
        raise ValueError(f"replacement anchor occurs {source.count(old)} times")
    return source.replace(old, new, 1)


def human(host: str, form: str = "split") -> str:
    if form == "direct":
        return """\
                        var_t0 *= gCurrentRacerHandlingStat;
                        racer->steerVisualRotation -= (var_t0 * updateRate) & 0xFFFF;
"""
    if form == "assign":
        return f"""\
                        var_t0 *= gCurrentRacerHandlingStat;
                        {host} = var_t0 * updateRate;
                        racer->steerVisualRotation = racer->steerVisualRotation - ({host} & 0xFFFF);
"""
    return f"""\
                        var_t0 *= gCurrentRacerHandlingStat;
                        {host} = var_t0 * updateRate;
                        racer->steerVisualRotation -= {host} & 0xFFFF;
"""


def computer(host: str, form: str = "split") -> str:
    if form == "direct":
        return """\
                        var_t0 = gCurrentStickX * 4;
                        racer->steerVisualRotation -= (var_t0 * updateRate) & 0xFFFF;
"""
    if form == "assign":
        return f"""\
                        var_t0 = gCurrentStickX * 4;
                        {host} = var_t0 * updateRate;
                        racer->steerVisualRotation = racer->steerVisualRotation - ({host} & 0xFFFF);
"""
    return f"""\
                        var_t0 = gCurrentStickX * 4;
                        {host} = var_t0 * updateRate;
                        racer->steerVisualRotation -= {host} & 0xFFFF;
"""


def offset(host: str, final_form: str = "compound") -> str:
    final = (
        f"racer->x_rotation_vel += ({host} * updateRate) >> 4;"
        if final_form == "compound"
        else "racer->x_rotation_vel = racer->x_rotation_vel + "
        f"(({host} * updateRate) >> 4);"
    )
    return f"""\
                {host} = -(racer->x_rotation_vel & 0xFFFF);
                if ({host} > 0x8000) {{
                    {host} -= 0xFFFF;
                }}
                if ({host} < -0x8000) {{
                    {host} += 0xFFFF;
                }}
                {final}
"""


def final_steer(host: str, form: str) -> str:
    if form == "split":
        return f"""\
                {host} = var_t0 * updateRate;
                racer->steerVisualRotation -= {host} & 0xFFFF;
"""
    if form == "assign":
        return f"""\
                {host} = var_t0 * updateRate;
                racer->steerVisualRotation = racer->steerVisualRotation - ({host} & 0xFFFF);
"""
    if form == "reverse":
        return """\
                racer->steerVisualRotation -= (updateRate * var_t0) & 0xFFFF;
"""
    return FINAL_STEER_OLD


def cases() -> list[tuple[str, str]]:
    result = [("baseline", BASE)]
    for left in HOSTS:
        for right in HOSTS:
            source = replace_once(BASE, HUMAN_OLD, human(left))
            source = replace_once(source, COMPUTER_OLD, computer(right))
            result.append((f"human_{left}__computer_{right}", source))
    for host in HOSTS:
        for form in ("split", "assign", "direct"):
            source = replace_once(BASE, HUMAN_OLD, human(host, form))
            result.append((f"human_{host}_{form}", source))
            source = replace_once(BASE, COMPUTER_OLD, computer(host, form))
            result.append((f"computer_{host}_{form}", source))
        for final_form in ("compound", "assign"):
            source = replace_once(BASE, OFFSET_OLD, offset(host, final_form))
            result.append((f"offset_{host}_{final_form}", source))
        for form in ("split", "assign"):
            source = replace_once(
                BASE, FINAL_STEER_OLD, final_steer(host, form)
            )
            result.append((f"final_steer_{host}_{form}", source))
    result.append(
        (
            "final_steer_reverse",
            replace_once(
                BASE, FINAL_STEER_OLD, final_steer("var_v0", "reverse")
            ),
        )
    )
    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_prehost_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_prehost_{tag}.c").write_text(
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
