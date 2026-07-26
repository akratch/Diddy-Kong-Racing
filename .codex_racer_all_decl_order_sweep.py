#!/usr/bin/env python3
"""Sweep all local-declaration orderings from the natural 28-word checkpoint."""

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
HEADER, DECL_TEXT = DECL_REGION.split("\n", 1)
DECL_LINES = tuple(DECL_TEXT.splitlines())


def registers(assembly: str) -> list[str]:
    return REGISTER_RE.findall(assembly)


def source_for(order: tuple[int, ...]) -> str:
    declarations = "\n".join(DECL_LINES[index] for index in order)
    return PREFIX + HEADER + "\n" + declarations + SUFFIX


def cases() -> list[tuple[str, tuple[int, ...]]]:
    base = tuple(range(len(DECL_LINES)))
    result = [("baseline", base)]
    for left, right in itertools.combinations(range(len(base)), 2):
        order = list(base)
        order[left], order[right] = order[right], order[left]
        result.append((f"swap_{left:02d}_{right:02d}", tuple(order)))

    # Rotate short contiguous blocks; this covers reorderings not expressible
    # by one transposition while retaining most of the original stack layout.
    for length in (3, 4, 5, 6):
        for start in range(len(base) - length + 1):
            block = list(base[start : start + length])
            for amount in range(1, length):
                order = list(base)
                order[start : start + length] = block[amount:] + block[:amount]
                result.append(
                    (f"rotate_{start:02d}_{length}_{amount}", tuple(order))
                )

    rng = random.Random(0x49794A11)
    for index in range(300):
        order = list(base)
        rng.shuffle(order)
        result.append((f"random_{index:03d}", tuple(order)))

    unique: dict[tuple[int, ...], tuple[str, tuple[int, ...]]] = {}
    for tag, order in result:
        unique.setdefault(order, (tag, order))
    return list(unique.values())


def worker(case: tuple[str, tuple[int, ...]]) -> tuple:
    tag, order = case
    source = source_for(order)
    obj = pathlib.Path(f"/tmp/codex_alldecl_{tag}.o")
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
        pathlib.Path(f"/tmp/codex_alldecl_{tag}.c").write_text(
            source, encoding="utf-8"
        )
    else:
        obj.unlink(missing_ok=True)
    return tag, order, result, reg_bad


def main() -> None:
    all_cases = cases()
    print(f"base={BASE_PATH} declarations={len(DECL_LINES)} cases={len(all_cases)}")
    for index, line in enumerate(DECL_LINES):
        print(index, line)
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(worker, all_cases))
    rows.sort(
        key=lambda row: (
            len(row[3]) if row[3] else 10000,
            row[2].get("fp") != EXPECTED_FP,
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
            reg_bad[:100],
            order,
        )
        if len(seen) >= 60:
            break
    print(f"tested={len(rows)} unique={len(seen)}")


if __name__ == "__main__":
    main()
