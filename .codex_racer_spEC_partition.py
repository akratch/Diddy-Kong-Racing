#!/usr/bin/env python3
"""Partition spEC's disjoint value ranges so one can reserve f12 first."""

from __future__ import annotations

import itertools
import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_segment_z_spcc.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
ANALYSIS = "/tmp/codex_run_analysis.sh"


def rename_region(
    source: str,
    start_marker: str,
    end_marker: str,
    name: str,
) -> str:
    start = source.index(start_marker)
    end = source.index(end_marker, start)
    region = source[start:end]
    if "spEC" not in region:
        raise ValueError("spEC absent from selected region")
    return source[:start] + re.sub(r"\bspEC\b", name, region) + source[end:]


def drag(source: str, name: str) -> str:
    return rename_region(
        source,
        "        spEC = racer->velocity * racer->velocity;\n",
        "    var_f20 = racer->lateral_velocity * racer->lateral_velocity * spD4;\n",
        name,
    )


def trick(source: str, name: str) -> str:
    return rename_region(
        source,
        "            spEC = racer->velocity * 0.058823529411764705 * 1.5;\n",
        "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n",
        name,
    )


def motion(source: str, name: str) -> str:
    return rename_region(
        source,
        "        spEC = obj->z_velocity;\n",
        "    gCurrentRacerTransform.rotation.y_rotation =",
        name,
    )


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    hosts = ("spEC", "var_f6", "segmentXVelocity", "racerVelocity")
    rows = []
    for drag_name, trick_name, motion_name in itertools.product(hosts, repeat=3):
        if (drag_name, trick_name, motion_name) == ("spEC",) * 3:
            continue
        source = BASE
        if drag_name != "spEC":
            source = drag(source, drag_name)
        if trick_name != "spEC":
            source = trick(source, trick_name)
        if motion_name != "spEC":
            source = motion(source, motion_name)
        tag = f"d-{drag_name}_t-{trick_name}_m-{motion_name}"
        path = f"/tmp/codex_spEC_partition_{tag}.c"
        obj = f"/tmp/codex_spEC_partition_{tag}_forced.o"
        trace = f"/tmp/codex_spEC_partition_{tag}.trace"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_spEC_partition_{tag}_natural.o"
        )
        result = ORACLE["subprocess"].run(
            [ANALYSIS, path, obj, trace],
            capture_output=True,
            text=True,
        )
        if result.returncode == 0:
            _, candidate = ORACLE["dump_object"](obj)
            forced = {
                "insns": len(candidate),
                "mismatch": sum(
                    target != actual
                    for target, actual in itertools.zip_longest(TARGET, candidate)
                ),
            }
            prefix = fp_prefix(obj)
        else:
            forced = {"error": result.stderr[-1000:]}
            prefix = -1
        rows.append((tag, natural, forced, prefix, trace))

    for tag, natural, forced, prefix, trace in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[3],
            row[2].get("mismatch", 9999),
            row[0],
        ),
    ):
        print(
            tag,
            "prefix",
            prefix,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced,
        )
        if natural.get("f20_operands", 0) > 0 or prefix == len(TARGET):
            with open(trace, encoding="utf-8") as input_file:
                colors = [
                    line.rstrip()
                    for line in input_file
                    if "RACER-COLOR" in line or "FACTOR before" in line
                ]
            for line in colors[:12]:
                print(" ", line)


if __name__ == "__main__":
    main()
