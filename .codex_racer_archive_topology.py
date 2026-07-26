#!/usr/bin/env python3
"""Recover useful source-only topology from the archived SlvtN scratch."""

from __future__ import annotations

import concurrent.futures
import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()

INTERP = """\
    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
"""
INTERP_TEMP = """\
    segmentZVelocity = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
                       (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
    var_f14 = segmentZVelocity;
"""


def factor_first(source: str) -> str:
    source = source.replace("    f32 var_f14;\n", "    f32 var_f20;\n", 1)
    source = source.replace("    f32 var_f20;\n", "    f32 var_f14;\n", 1)
    # The sequential replacement above changes the first replacement again.
    # Restore with a sentinel-based exact rewrite.
    if source == BASE:
        raise AssertionError("factor declaration swap did not change source")
    return source


def make(flags: tuple[str, ...]) -> str:
    source = BASE
    if "factor_first" in flags:
        if source.count("    f32 var_f14;\n") != 1 or source.count("    f32 var_f20;\n") != 1:
            raise ValueError("factor declarations not unique")
        source = source.replace("    f32 var_f14;\n", "    f32 __codex_swap;\n", 1)
        source = source.replace("    f32 var_f20;\n", "    f32 var_f14;\n", 1)
        source = source.replace("    f32 __codex_swap;\n", "    f32 var_f20;\n", 1)
    if "spcc_early" in flags:
        source = source.replace("    f32 spCC;\n", "", 1)
        source = source.replace("    f32 spD0;\n", "    f32 spD0;\n    f32 spCC;\n", 1)
    if "segment_temp" in flags:
        anchor = "    s8 newSpinoutTimer;\n"
        source = source.replace(anchor, anchor + "    f32 segmentZVelocity;\n", 1)
        source = source.replace(INTERP, INTERP_TEMP, 1)
    if "pad3" in flags:
        source = source.replace(
            "    Object_Boost *boostObj;\n",
            "    Object_Boost *boostObj;\n    s32 pad3;\n",
            1,
        )
    return source


def evaluate(flags: tuple[str, ...]) -> tuple:
    tag = "_".join(flags) if flags else "canonical"
    source = make(flags)
    result = ORACLE["evaluate"](source, keep=f"/tmp/codex_archive_topology_{tag}.o")
    return tag, flags, source, result


def main() -> None:
    names = ("factor_first", "spcc_early", "segment_temp", "pad3")
    cases = [
        tuple(name for name, enabled in zip(names, bits) if enabled)
        for bits in itertools.product((False, True), repeat=len(names))
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            row[3].get("f20_operands", 0) == 0,
            abs(row[3].get("f18", 0) - 190),
            abs(row[3].get("insns", 9999) - 2625),
            row[3].get("norm", 9999),
        )
    )
    for tag, flags, source, result in rows:
        print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
