#!/usr/bin/env python3
"""Probe optimizer-erased control wrappers around var_f14 live units."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_unk34_left_associative.c", encoding="utf-8"
).read()
TARGET = ORACLE["TARGET_INSNS"]

INTERPOLATION = """\
    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
"""
INITIAL_START = "    var_f14 = racer->velocity;\n"
TOP_START = "    var_f0 = handle_racer_top_speed(obj, racer);\n"
TOP_END = "    var_f14 *= 1.8;\n"
PHYSICS_END = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
    }
"""

WRAPPERS = {
    "ifone": ("    if (1) {\n", "    }\n"),
    "dowhile": ("    do {\n", "    } while (0);\n"),
    "whilebreak": ("    while (1) {\n", "        break;\n    }\n"),
    "forbreak": ("    for (;;) {\n", "        break;\n    }\n"),
}


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(
            r"\$f\d+\b", actual
        ):
            return index
    return min(len(TARGET), len(candidate))


def region(kind: str) -> tuple[int, int]:
    if kind == "interpolation":
        start = BASE.index(INTERPOLATION)
        return start, start + len(INTERPOLATION)
    if kind == "initial":
        start = BASE.index(INITIAL_START)
        end = BASE.index(INTERPOLATION, start) + len(INTERPOLATION)
        return start, end
    if kind == "top":
        start = BASE.index(TOP_START)
        end = BASE.index(TOP_END, start) + len(TOP_END)
        return start, end
    if kind == "physics":
        start = BASE.index(INITIAL_START)
        end = BASE.index(PHYSICS_END, start) + len(PHYSICS_END)
        return start, end
    raise ValueError(kind)


def main() -> None:
    rows = []
    for region_tag in ("interpolation", "initial", "top", "physics"):
        start, end = region(region_tag)
        body = BASE[start:end]
        for wrapper_tag, (opening, closing) in WRAPPERS.items():
            tag = f"{region_tag}_{wrapper_tag}"
            source = BASE[:start] + opening + body + closing + BASE[end:]
            path = f"/tmp/codex_varf14_wrapper_{tag}.c"
            with open(path, "w", encoding="utf-8") as output:
                output.write(source)
            natural = ORACLE["evaluate"](
                source, keep=f"/tmp/codex_varf14_wrapper_{tag}_natural.o"
            )
            forced = STICK["forced"](path, f"varf14_wrapper_{tag}")
            obj = f"/tmp/codex_stickform_varf14_wrapper_{tag}_forced.o"
            prefix = fp_prefix(obj) if forced.get("ok") else -1
            rows.append(
                (
                    natural.get("f20_operands", 0) == 0,
                    abs(natural.get("insns", 9999) - 2625),
                    -prefix,
                    forced.get("mismatch", 9999),
                    tag,
                    natural,
                    forced,
                )
            )
    for _, _, neg_prefix, _, tag, natural, forced in sorted(rows):
        print(
            tag,
            "prefix",
            -neg_prefix,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced,
        )


if __name__ == "__main__":
    main()
