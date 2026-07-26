#!/usr/bin/env python3
"""Sweep instruction-neutral trees immediately before the final rotation branch."""

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
            var_f2 = -racer->velocity;
            if (var_f2 < 4.0) {
                var_f2 = 4.0f;
            }
            if (var_f2 > 14.0) {
                var_f2 = 14.0f;
            }
            var_f2 /= 7.0;
            var_t0 *= var_f2;
"""


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def replace_once(source: str, old: str, new: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"replacement anchor occurs {count} times")
    return source.replace(old, new, 1)


def render(parts: dict[str, str]) -> str:
    return (
        parts["velocity"]
        + parts["low"]
        + parts["high"]
        + parts["divide"]
        + parts["convert"]
    )


def cases() -> list[tuple[str, str]]:
    base = {
        "velocity": "            var_f2 = -racer->velocity;\n",
        "low": (
            "            if (var_f2 < 4.0) {\n"
            "                var_f2 = 4.0f;\n"
            "            }\n"
        ),
        "high": (
            "            if (var_f2 > 14.0) {\n"
            "                var_f2 = 14.0f;\n"
            "            }\n"
        ),
        "divide": "            var_f2 /= 7.0;\n",
        "convert": "            var_t0 *= var_f2;\n",
    }
    variants: dict[str, dict[str, str]] = {
        "velocity": {
            "base": base["velocity"],
            "paren": "            var_f2 = -(racer->velocity);\n",
            "neg_mul_left": "            var_f2 = -1.0 * racer->velocity;\n",
            "neg_mul_right": "            var_f2 = racer->velocity * -1.0;\n",
            "zero_sub": "            var_f2 = 0.0 - racer->velocity;\n",
            "neg_float": "            var_f2 = -1.0f * racer->velocity;\n",
        },
        "low": {
            "base": base["low"],
            "reverse": (
                "            if (4.0 > var_f2) {\n"
                "                var_f2 = 4.0f;\n"
                "            }\n"
            ),
            "not_ge": (
                "            if (!(var_f2 >= 4.0)) {\n"
                "                var_f2 = 4.0f;\n"
                "            }\n"
            ),
            "double_f": (
                "            if (var_f2 < 4.0f) {\n"
                "                var_f2 = 4.0f;\n"
                "            }\n"
            ),
            "assign_double": (
                "            if (var_f2 < 4.0) {\n"
                "                var_f2 = 4.0;\n"
                "            }\n"
            ),
            "assign_cast": (
                "            if (var_f2 < 4.0) {\n"
                "                var_f2 = (f32) 4.0;\n"
                "            }\n"
            ),
        },
        "high": {
            "base": base["high"],
            "reverse": (
                "            if (14.0 < var_f2) {\n"
                "                var_f2 = 14.0f;\n"
                "            }\n"
            ),
            "not_le": (
                "            if (!(var_f2 <= 14.0)) {\n"
                "                var_f2 = 14.0f;\n"
                "            }\n"
            ),
            "double_f": (
                "            if (var_f2 > 14.0f) {\n"
                "                var_f2 = 14.0f;\n"
                "            }\n"
            ),
            "assign_double": (
                "            if (var_f2 > 14.0) {\n"
                "                var_f2 = 14.0;\n"
                "            }\n"
            ),
            "assign_cast": (
                "            if (var_f2 > 14.0) {\n"
                "                var_f2 = (f32) 14.0;\n"
                "            }\n"
            ),
        },
        "divide": {
            "base": base["divide"],
            "assign": "            var_f2 = var_f2 / 7.0;\n",
            "int": "            var_f2 /= 7;\n",
            "float": "            var_f2 /= 7.0f;\n",
            "cast": "            var_f2 = var_f2 / (f32) 7.0;\n",
            "reciprocal_left": "            var_f2 = (1.0 / 7.0) * var_f2;\n",
            "reciprocal_right": "            var_f2 = var_f2 * (1.0 / 7.0);\n",
        },
        "convert": {
            "base": base["convert"],
            "assign": "            var_t0 = var_t0 * var_f2;\n",
            "cast_left": "            var_t0 = (f32) var_t0 * var_f2;\n",
            "cast_result": "            var_t0 = (s32) ((f32) var_t0 * var_f2);\n",
            "reverse": "            var_t0 = var_f2 * var_t0;\n",
            "reverse_cast": "            var_t0 = var_f2 * (f32) var_t0;\n",
            "reverse_result": "            var_t0 = (s32) (var_f2 * (f32) var_t0);\n",
            "self_add_zero": "            var_t0 = (var_t0 * var_f2) + 0;\n",
        },
    }

    result: list[tuple[str, str]] = [("baseline", BASE)]
    for part, choices in variants.items():
        for tag, value in choices.items():
            if tag == "base":
                continue
            modified = dict(base)
            modified[part] = value
            result.append(
                (
                    f"{part}_{tag}",
                    replace_once(BASE, OLD, render(modified)),
                )
            )

    nonbase = {
        part: [(tag, value) for tag, value in choices.items() if tag != "base"]
        for part, choices in variants.items()
    }
    for left, right in itertools.combinations(variants, 2):
        for (left_tag, left_value), (right_tag, right_value) in itertools.product(
            nonbase[left], nonbase[right]
        ):
            modified = dict(base)
            modified[left] = left_value
            modified[right] = right_value
            result.append(
                (
                    f"{left}_{left_tag}__{right}_{right_tag}",
                    replace_once(BASE, OLD, render(modified)),
                )
            )

    float_hosts = (
        "var_f2",
        "var_f0",
        "var_f6",
        "var_f14",
        "var_f20",
        "spCC",
        "spD0",
        "spD4",
        "spD8",
        "spE0",
        "spE4",
        "spE8",
        "spEC",
        "racerVelocity",
        "segmentXVelocity",
    )
    for host in float_hosts:
        if host == "var_f2":
            continue
        body = OLD.replace("var_f2", host)
        result.append((f"host_{host}", replace_once(BASE, OLD, body)))

    extra_bodies = {
        "low_high_nested_else": (
            "            var_f2 = -racer->velocity;\n"
            "            if (var_f2 < 4.0) {\n"
            "                var_f2 = 4.0f;\n"
            "            } else if (var_f2 > 14.0) {\n"
            "                var_f2 = 14.0f;\n"
            "            }\n"
            "            var_f2 /= 7.0;\n"
            "            var_t0 *= var_f2;\n"
        ),
        "high_first": (
            "            var_f2 = -racer->velocity;\n"
            "            if (var_f2 > 14.0) {\n"
            "                var_f2 = 14.0f;\n"
            "            }\n"
            "            if (var_f2 < 4.0) {\n"
            "                var_f2 = 4.0f;\n"
            "            }\n"
            "            var_f2 /= 7.0;\n"
            "            var_t0 *= var_f2;\n"
        ),
        "convert_temp_v0": (
            "            var_f2 = -racer->velocity;\n"
            "            if (var_f2 < 4.0) {\n"
            "                var_f2 = 4.0f;\n"
            "            }\n"
            "            if (var_f2 > 14.0) {\n"
            "                var_f2 = 14.0f;\n"
            "            }\n"
            "            var_f2 /= 7.0;\n"
            "            var_v0 = var_t0;\n"
            "            var_t0 = var_v0 * var_f2;\n"
        ),
        "convert_temp_v1": (
            "            var_f2 = -racer->velocity;\n"
            "            if (var_f2 < 4.0) {\n"
            "                var_f2 = 4.0f;\n"
            "            }\n"
            "            if (var_f2 > 14.0) {\n"
            "                var_f2 = 14.0f;\n"
            "            }\n"
            "            var_f2 /= 7.0;\n"
            "            var_v1 = var_t0;\n"
            "            var_t0 = var_v1 * var_f2;\n"
        ),
    }
    for tag, body in extra_bodies.items():
        result.append((tag, replace_once(BASE, OLD, body)))

    unique: dict[str, tuple[str, str]] = {}
    for tag, source in result:
        unique.setdefault(source, (tag, source))
    return list(unique.values())


def worker(case: tuple[str, str]) -> tuple:
    tag, source = case
    obj = pathlib.Path(f"/tmp/codex_prerotation_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_prerotation_{tag}.c").write_text(
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
