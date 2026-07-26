#!/usr/bin/env python3
"""Test block-local scope for the long-lived var_f14 coefficient."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
BASE = open(
    "/tmp/codex_unk34_left_associative.c", encoding="utf-8"
).read()
TARGET = ORACLE["TARGET_INSNS"]
START = "    var_f14 = racer->velocity;\n"
END = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
    }
"""
DIRECT = """\
    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
"""
TWO_LINE = """\
    spCC = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
           (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
    var_f14 = spCC;
"""


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(
            r"\$f\d+\b", actual
        ):
            return index
    return min(len(TARGET), len(candidate))


def make(name: str, keep_function_decl: bool, two_line: bool, end_at_function: bool) -> str:
    source = BASE
    if not keep_function_decl:
        if source.count("    f32 var_f14;\n") != 1:
            raise ValueError("function declaration missing")
        source = source.replace("    f32 var_f14;\n", "", 1)

    start = source.index(START)
    if end_at_function:
        end = source.rindex("\n}") + 1
    else:
        end = source.index(END, start) + len(END)
    region = source[start:end]
    if name != "var_f14":
        region = re.sub(r"\bvar_f14\b", name, region)
    if two_line:
        direct = DIRECT if name == "var_f14" else re.sub(r"\bvar_f14\b", name, DIRECT)
        replacement = (
            TWO_LINE
            if name == "var_f14"
            else re.sub(r"\bvar_f14\b", name, TWO_LINE)
        )
        if region.count(direct) != 1:
            raise ValueError("scoped interpolation missing")
        region = region.replace(direct, replacement, 1)
    scoped = "    {\n        f32 " + name + ";\n" + region + "    }\n"
    return source[:start] + scoped + source[end:]


def main() -> None:
    rows = []
    for name in ("var_f14", "coefficient"):
        for keep in (False, True):
            if name == "var_f14" and keep:
                continue
            for two_line in (False, True):
                for end_at_function in (False, True):
                    tag = (
                        f"{name}_{'keep' if keep else 'remove'}_"
                        f"{'two' if two_line else 'direct'}_"
                        f"{'function' if end_at_function else 'physics'}"
                    )
                    source = make(name, keep, two_line, end_at_function)
                    path = f"/tmp/codex_varf14_scope_{tag}.c"
                    with open(path, "w", encoding="utf-8") as output:
                        output.write(source)
                    natural = ORACLE["evaluate"](
                        source, keep=f"/tmp/codex_varf14_scope_{tag}_natural.o"
                    )
                    forced = STICK["forced"](path, f"varf14_scope_{tag}")
                    obj = f"/tmp/codex_stickform_varf14_scope_{tag}_forced.o"
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
