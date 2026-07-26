#!/usr/bin/env python3
"""Evaluate an already-compiled racer object against the target oracle."""

from __future__ import annotations

import collections
import difflib
import hashlib
import re
import runpy
import sys


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")


def evaluate_object(path: str) -> dict[str, object]:
    text, instructions = ORACLE["dump_object"](path)
    words = [word for word, _ in instructions]
    assembly = [asm for _, asm in instructions]
    fp_counts = collections.Counter(
        match
        for line in assembly
        for match in re.findall(r"\$(f(?:[02468]|1[02468]|2[01]))\b", line)
    )
    normalized = [ORACLE["normalized_instruction"](line) for line in assembly]
    matcher = difflib.SequenceMatcher(
        a=normalized, b=ORACLE["TARGET_NORMALIZED"], autojunk=False
    )
    normalized_diff = sum(
        max(i2 - i1, j2 - j1)
        for tag, i1, i2, j1, j2 in matcher.get_opcodes()
        if tag != "equal"
    )
    frame = re.search(r"(?:\\$)?sp,(?:\\$)?sp,(-\d+)", text)
    offsets = collections.Counter(
        int(value)
        for value in re.findall(r"(-?\d+)\((?:\$)?sp\)", text)
    )
    return {
        "ok": True,
        "frame": int(frame.group(1)) if frame else None,
        "insns": len(instructions),
        "f20_insns": sum(
            1 for line in assembly if re.search(r"\$f2[01]\b", line)
        ),
        "f20_operands": fp_counts["f20"] + fp_counts["f21"],
        "f18": fp_counts["f18"],
        "fp": dict(sorted(fp_counts.items())),
        "spill20": sorted(
            (offset, count) for offset, count in offsets.items() if count >= 18
        ),
        "norm": normalized_diff,
        "sha1": hashlib.sha1("".join(words).encode()).hexdigest()[:12],
    }


def main() -> None:
    for path in sys.argv[1:]:
        result = evaluate_object(path)
        print(path, ORACLE["concise"](result), result["fp"])


if __name__ == "__main__":
    main()
