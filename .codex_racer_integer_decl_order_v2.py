#!/usr/bin/env python3
"""Natural integer-declaration-order sweep from the 28-word racer checkpoint."""

from __future__ import annotations

import concurrent.futures
import itertools
import pathlib
import random
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

FUNCTION = BASE.index("void func_80049794")
BODY = BASE.index("\n\n    if (func_8000E138())", FUNCTION)
PREFIX = BASE[:FUNCTION]
DECL_REGION = BASE[FUNCTION:BODY]
SUFFIX = BASE[BODY:]
DECL_PATTERN = re.compile(r"^    s32 ([A-Za-z_][A-Za-z0-9_]*);$", re.MULTILINE)
NAMES = tuple(DECL_PATTERN.findall(DECL_REGION))


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def source_for(order: tuple[str, ...]) -> str:
    iterator = iter(order)
    declarations = DECL_PATTERN.sub(
        lambda _: f"    s32 {next(iterator)};", DECL_REGION
    )
    return PREFIX + declarations + SUFFIX


def cases() -> list[tuple[str, tuple[str, ...]]]:
    result = [("baseline", NAMES)]
    for left, right in itertools.combinations(range(len(NAMES)), 2):
        order = list(NAMES)
        order[left], order[right] = order[right], order[left]
        result.append((f"swap_{NAMES[left]}_{NAMES[right]}", tuple(order)))

    rng = random.Random(0x80049794)
    for index in range(200):
        order = list(NAMES)
        rng.shuffle(order)
        result.append((f"random_{index:03d}", tuple(order)))
    return result


def worker(case: tuple[str, tuple[str, ...]]) -> tuple:
    tag, order = case
    source = source_for(order)
    obj = pathlib.Path(f"/tmp/codex_idecl_v2_{tag}.o")
    result = ORACLE["evaluate"](source, keep=str(obj))
    if not result.get("ok") or result.get("insns") != len(TARGET):
        obj.unlink(missing_ok=True)
        return tag, order, result, []
    _, candidate = ORACLE["dump_object"](str(obj))
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    if len(reg_bad) < 28 and result.get("fp") == EXPECTED_FP:
        pathlib.Path(f"/tmp/codex_idecl_v2_{tag}.c").write_text(
            source, encoding="utf-8"
        )
    else:
        obj.unlink(missing_ok=True)
    return tag, order, result, reg_bad


def main() -> None:
    all_cases = cases()
    print(f"base={BASE_PATH} integer_declarations={len(NAMES)} cases={len(all_cases)}")
    print(NAMES)
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(worker, all_cases))
    rows.sort(
        key=lambda row: (
            len(row[3]) if row[3] else 10000,
            row[2].get("norm", 10000),
            row[0],
        )
    )
    seen: set[tuple] = set()
    for tag, order, result, reg_bad in rows:
        fingerprint = (result.get("sha1"), tuple(reg_bad))
        if fingerprint in seen:
            continue
        seen.add(fingerprint)
        print(
            tag,
            ORACLE["concise"](result),
            f"fp_exact={result.get('fp') == EXPECTED_FP}",
            f"reg={len(reg_bad)}",
            reg_bad,
            order,
        )
        if len(seen) >= 30:
            break
    print(f"tested={len(rows)} unique={len(seen)}")


if __name__ == "__main__":
    main()
