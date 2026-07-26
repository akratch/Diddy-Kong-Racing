#!/usr/bin/env python3
"""Localize target/forced-object register divergences by instruction range."""

from __future__ import annotations

import re
import runpy
import sys


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
TARGET = ORACLE["TARGET_INSNS"]


def registers(assembly: str) -> list[str]:
    return re.findall(r"\$(?:f\d+|[a-z][a-z0-9]*)\b", assembly)


def ranges(indices: list[int]) -> list[tuple[int, int]]:
    if not indices:
        return []
    result: list[tuple[int, int]] = []
    start = previous = indices[0]
    for index in indices[1:]:
        if index != previous + 1:
            result.append((start, previous))
            start = index
        previous = index
    result.append((start, previous))
    return result


def main() -> None:
    obj = sys.argv[1]
    _, candidate = ORACLE["dump_object"](obj)
    if len(candidate) != len(TARGET):
        raise SystemExit(f"instruction count differs: {len(candidate)} vs {len(TARGET)}")

    fp_bad = []
    all_register_bad = []
    exact_bad = []
    for index, ((_, expected), (_, actual)) in enumerate(zip(TARGET, candidate)):
        expected_fp = re.findall(r"\$f\d+\b", expected)
        actual_fp = re.findall(r"\$f\d+\b", actual)
        if expected_fp != actual_fp:
            fp_bad.append(index)
        if registers(expected) != registers(actual):
            all_register_bad.append(index)
        if expected != actual:
            exact_bad.append(index)

    print("FP ranges:", ranges(fp_bad))
    print("all-register ranges:", ranges(all_register_bad))
    print("exact ranges:", ranges(exact_bad))
    print("FP mismatch count:", len(fp_bad))

    for start, end in ranges(fp_bad):
        print(f"\nFP range {start}..{end}")
        for index in range(max(0, start - 2), min(len(TARGET), end + 3)):
            marker = "!" if index in fp_bad else " "
            print(f"{marker} {index:4d} T {TARGET[index][1]}")
            print(f"{marker}      C {candidate[index][1]}")

    if len(sys.argv) > 2 and sys.argv[2] == "--exact":
        for start, end in ranges(exact_bad):
            print(f"\nExact range {start}..{end}")
            for index in range(start, end + 1):
                print(f"! {index:4d} T {TARGET[index][1]}")
                print(f"!      C {candidate[index][1]}")


if __name__ == "__main__":
    main()
