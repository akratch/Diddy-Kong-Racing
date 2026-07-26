#!/usr/bin/env python3
"""Fast allocation oracle for isolated func_80049794 source experiments."""

from __future__ import annotations

import collections
import difflib
import hashlib
import os
import re
import runpy
import subprocess
import tempfile


CAMPAIGN = (
    "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
    "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad"
)
ISO = runpy.run_path(f"{CAMPAIGN}/iso_sweep.py")
DECL = runpy.run_path("/tmp/codex_racer_decl_sweep.py")
OBJDUMP = ISO["OBJD"]
TARGET = f"{CAMPAIGN}/work-racer/nonmatchings/func_80049794/target.o"


def recovered(*, merge_racer_velocity: bool = True) -> str:
    source = DECL["recovered_without_decl"]()
    source = source.replace("    f32 spD8;\n", "    f32 spD8;\n    f32 var_f14;\n", 1)
    if merge_racer_velocity:
        source = source.replace("    f32 racerVelocity;\n", "", 1)
        function_start = source.index("void func_80049794")
        function_end = source.index("\n}\n", function_start)
        function = source[function_start:function_end]
        function = re.sub(r"\bracerVelocity\b", "var_f0", function)
        source = source[:function_start] + function + source[function_end:]
    return source


def dump_object(obj: str) -> tuple[str, list[tuple[str, str]]]:
    text = subprocess.run(
        [OBJDUMP, "-d", obj, "--disassemble=func_80049794"],
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    instructions = re.findall(
        r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.+)$", text, re.MULTILINE
    )
    return text, instructions


TARGET_TEXT, TARGET_INSNS = dump_object(TARGET)


def normalized_instruction(assembly: str) -> str:
    assembly = re.sub(r"\b[0-9a-f]+\s+<[^>]+>", "ADDR", assembly)
    assembly = re.sub(r"-?\d+\((sp|\$sp)\)", "OFF(sp)", assembly)
    assembly = re.sub(r"\b-?(?:0x[0-9a-f]+|\d+)\b", "IMM", assembly)
    return assembly.replace("$", "")


TARGET_NORMALIZED = [normalized_instruction(asm) for _, asm in TARGET_INSNS]


def evaluate(source: str, *, keep: str | None = None) -> dict[str, object]:
    with tempfile.NamedTemporaryFile("w", suffix=".c", dir="/tmp") as c_file:
        c_file.write(source)
        c_file.flush()
        fd, obj = tempfile.mkstemp(suffix=".o", dir="/tmp")
        os.close(fd)
        os.unlink(obj)
        compile_result = subprocess.run(
            ["/tmp/isoeval.sh", c_file.name, obj],
            check=False,
            capture_output=True,
            text=True,
        )
    if not os.path.exists(obj):
        return {
            "ok": False,
            "stderr": compile_result.stderr[-2000:],
            "stdout": compile_result.stdout[-2000:],
        }
    text, instructions = dump_object(obj)
    if keep:
        subprocess.run(["cp", obj, keep], check=True)
    os.unlink(obj)
    words = [word for word, _ in instructions]
    assembly = [asm for _, asm in instructions]
    fp_counts = collections.Counter(
        match
        for line in assembly
        for match in re.findall(r"\$(f(?:[02468]|1[02468]|2[01]))\b", line)
    )
    normalized = [normalized_instruction(line) for line in assembly]
    matcher = difflib.SequenceMatcher(
        a=normalized, b=TARGET_NORMALIZED, autojunk=False
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


def concise(result: dict[str, object]) -> str:
    if not result.get("ok"):
        return f"compile failed: {result}"
    return (
        f"frame={result['frame']} insns={result['insns']} "
        f"f20i={result['f20_insns']} f20o={result['f20_operands']} "
        f"f18={result['f18']} norm={result['norm']} "
        f"spill20={result['spill20']} sha1={result['sha1']}"
    )


if __name__ == "__main__":
    target_counts = collections.Counter(
        match
        for _, line in TARGET_INSNS
        for match in re.findall(r"\$(f(?:[02468]|1[02468]|2[01]))\b", line)
    )
    print("target", len(TARGET_INSNS), dict(sorted(target_counts.items())))
    print("recovered", concise(evaluate(recovered(merge_racer_velocity=True))))
