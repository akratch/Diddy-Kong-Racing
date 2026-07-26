#!/usr/bin/env python3
"""Embed the canonical function in the full racer.c translation unit."""

from __future__ import annotations

import pathlib
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
ROOT = pathlib.Path("/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing")
CANONICAL = pathlib.Path("/tmp/codex_unk34_left_associative.c")
OUTPUT_SOURCE = pathlib.Path("/tmp/codex_full_tu_canonical.c")
OUTPUT_OBJECT = pathlib.Path("/tmp/codex_full_tu_canonical.o")


def function_span(source: str) -> tuple[int, int]:
    start = source.index("void func_80049794(")
    brace = source.index("{", start)
    depth = 0
    for index in range(brace, len(source)):
        if source[index] == "{":
            depth += 1
        elif source[index] == "}":
            depth -= 1
            if depth == 0:
                return start, index + 1
    raise ValueError("unterminated func_80049794")


def main() -> None:
    full = (ROOT / "src/racer.c").read_text(encoding="utf-8")
    canonical = CANONICAL.read_text(encoding="utf-8")
    full_start, full_end = function_span(full)
    canonical_start, canonical_end = function_span(canonical)
    merged = (
        full[:full_start]
        + canonical[canonical_start:canonical_end]
        + full[full_end:]
    )
    guard = "// https://decomp.me/scratch/SlvtN\n#ifdef NON_EQUIVALENT\n"
    if merged.count(guard) != 1:
        raise ValueError("func_80049794 guard not found")
    merged = merged.replace(
        guard,
        "// https://decomp.me/scratch/SlvtN\n#if 1\n",
        1,
    )
    OUTPUT_SOURCE.write_text(merged, encoding="utf-8")
    proc = subprocess.run(
        ["/tmp/isoeval.sh", str(OUTPUT_SOURCE), str(OUTPUT_OBJECT)],
        check=False,
        capture_output=True,
        text=True,
    )
    print("compile", proc.returncode)
    if proc.stdout:
        print("stdout", proc.stdout[-2000:])
    if proc.stderr:
        print("stderr", proc.stderr[-2000:])
    if OUTPUT_OBJECT.exists():
        _, instructions = ORACLE["dump_object"](str(OUTPUT_OBJECT))
        print("function instructions", len(instructions))
        print(
            "canonical isolated",
            ORACLE["concise"](
                ORACLE["evaluate"](
                    canonical,
                    keep="/tmp/codex_full_tu_isolated_control.o",
                )
            ),
        )


if __name__ == "__main__":
    main()
