#!/usr/bin/env python3
"""Test the two remaining func_80049794 structural source hypotheses."""

from __future__ import annotations

import collections
import difflib
import hashlib
import os
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = "/tmp/codex_unused_spCC.c"
TARGET = ORACLE["TARGET_INSNS"]

OLD_BUOYANCY = """\
    if (racer->buoyancy != 0.0) {
        gCurrentStickY = -60;
        var_f2 = racer->buoyancy - 20.0f;
        if (var_f2 < 0.0) {
            var_f2 = 0;
        }
        var_f20 = -1 - (var_f2 / 10);
"""

NEW_BUOYANCY = """\
    if (racer->buoyancy != 0.0) {
        var_f20 = -1.0f;
        gCurrentStickY = -60;
        var_f2 = racer->buoyancy - 20.0f;
        if (var_f2 < 0.0) {
            var_f2 = 0;
        }
        var_f20 -= var_f2 / 10;
"""

OLD_TRICK_DECAY = """\
            var_v1 = racer->x_rotation_vel;
            racer->x_rotation_vel = var_v1 - ((var_v1 * updateRate) >> 4);
"""

NEW_TRICK_DECAY = """\
            racer->x_rotation_vel -= (racer->x_rotation_vel * updateRate) >> 4;
"""

OLD_TRICK_POSITIVE = """\
            if (racer->trickType == 2) {
                if (var_t0 > 0) {
"""

NEW_TRICK_POSITIVE = """\
            if (racer->trickType == 2) {
                if (var_v1 > 0) {
"""

OLD_TRICK_NEGATIVE = """\
            } else {
                if (var_t0 < 0) {
"""

NEW_TRICK_NEGATIVE = """\
            } else {
                if (var_v1 < 0) {
"""


def replace_once(source: str, old: str, new: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"expected one occurrence, found {count}: {old!r}")
    return source.replace(old, new, 1)


def variant(*, buoyancy: bool, trick: str | None) -> str:
    source = open(BASE_PATH, encoding="utf-8").read()
    if buoyancy:
        source = replace_once(source, OLD_BUOYANCY, NEW_BUOYANCY)
    if trick is not None:
        if trick == "direct":
            decay = NEW_TRICK_DECAY
        else:
            decay = OLD_TRICK_DECAY.replace("var_v1", trick)
        source = replace_once(source, OLD_TRICK_DECAY, decay)
        source = replace_once(source, OLD_TRICK_POSITIVE, NEW_TRICK_POSITIVE)
        source = replace_once(source, OLD_TRICK_NEGATIVE, NEW_TRICK_NEGATIVE)
    return source


def mnemonic_edits(
    instructions: list[tuple[str, str]],
) -> tuple[int, list[tuple[str, int, int, int, int]]]:
    target_ops = [assembly.split()[0] for _, assembly in TARGET]
    candidate_ops = [assembly.split()[0] for _, assembly in instructions]
    matcher = difflib.SequenceMatcher(
        a=target_ops, b=candidate_ops, autojunk=False
    )
    edits = [
        opcode
        for opcode in matcher.get_opcodes()
        if opcode[0] != "equal"
    ]
    distance = sum(
        max(i2 - i1, j2 - j1) for _, i1, i2, j1, j2 in edits
    )
    return distance, edits


def forced(source_path: str, tag: str) -> dict[str, object]:
    obj = f"/tmp/codex_struct_{tag}_forced.o"
    trace = f"/tmp/codex_struct_{tag}_forced.trace"
    result = subprocess.run(
        ["/tmp/codex_run_analysis.sh", source_path, obj, trace],
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0 or not os.path.exists(obj):
        return {
            "ok": False,
            "returncode": result.returncode,
            "stderr": result.stderr[-1000:],
        }
    text, instructions = ORACLE["dump_object"](obj)
    words = [word for word, _ in instructions]
    fp = collections.Counter(
        match
        for _, assembly in instructions
        for match in re.findall(r"\$(f\d+)\b", assembly)
    )
    frame_match = re.search(r"(?:\$)?sp,(?:\$)?sp,(-\d+)", text)
    trace_text = open(trace, encoding="utf-8", errors="replace").read()
    factor = re.search(
        r"FACTOR before-cost icbit=(\d+) lrbit=(\d+) "
        r"forb=([0-9a-f]+):([0-9a-f]+) adjsave=([0-9.]+) "
        r"numintf=(\d+) regsleft=(\d+)",
        trace_text,
    )
    distance, edits = mnemonic_edits(instructions)
    return {
        "ok": True,
        "frame": int(frame_match.group(1)) if frame_match else None,
        "insns": len(instructions),
        "f20": fp["f20"],
        "f21": fp["f21"],
        "f18": fp["f18"],
        "mnemonic_distance": distance,
        "mnemonic_edits": edits,
        "sha1": hashlib.sha1("".join(words).encode()).hexdigest()[:12],
        "factor": factor.groups() if factor else None,
    }


def main() -> None:
    for buoyancy, trick in (
        (False, None),
        (True, None),
        (True, "direct"),
        (True, "var_v0"),
        (True, "temp_t7"),
        (True, "xRotationOffset"),
        (True, "i"),
    ):
        trick_tag = trick or "none"
        tag = f"b{int(buoyancy)}_{trick_tag}"
        source = variant(buoyancy=buoyancy, trick=trick)
        source_path = f"/tmp/codex_struct_{tag}.c"
        with open(source_path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_struct_{tag}_natural.o"
        )
        forced_result = forced(source_path, tag)
        print(tag)
        print("  natural", ORACLE["concise"](natural))
        print("  forced ", forced_result)


if __name__ == "__main__":
    main()
