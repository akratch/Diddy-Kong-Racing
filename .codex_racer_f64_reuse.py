#!/usr/bin/env python3
"""Reuse final f64 temporaries for earlier existing double expressions."""

from __future__ import annotations

import itertools
import os
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()

SITES = {
    "rate": (
        "        updateRateF *= 1.09;\n",
        "        {d} = updateRateF * 1.09;\n"
        "        updateRateF = {d};\n",
    ),
    "throttle_add": (
        "        racer->throttle += updateRateF * 0.01;\n",
        "        {d} = racer->throttle + (updateRateF * 0.01);\n"
        "        racer->throttle = {d};\n",
    ),
    "throttle_sub": (
        "        racer->throttle -= updateRateF * 0.01;\n",
        "        {d} = racer->throttle - (updateRateF * 0.01);\n"
        "        racer->throttle = {d};\n",
    ),
    "brake_add": (
        "        racer->brake += updateRateF * 0.016;\n",
        "        {d} = racer->brake + (updateRateF * 0.016);\n"
        "        racer->brake = {d};\n",
    ),
    "brake_sub": (
        "        racer->brake -= updateRateF * 0.016;\n",
        "        {d} = racer->brake - (updateRateF * 0.016);\n"
        "        racer->brake = {d};\n",
    ),
    "topspeed": (
        "    var_f14 = (var_f14 * handle_racer_top_speed(obj, racer)) * 1.8;\n",
        "    {d} = (var_f14 * handle_racer_top_speed(obj, racer)) * 1.8;\n"
        "    var_f14 = {d};\n",
    ),
    "trick_scale": (
        "            spEC = racer->velocity * 0.058823529411764705 * 1.5;\n",
        "            {d} = racer->velocity * 0.058823529411764705 * 1.5;\n"
        "            spEC = {d};\n",
    ),
    "approach_x": (
        "            var_f20 += racer->unk11C * 0.5;\n",
        "            {d} = var_f20 + (racer->unk11C * 0.5);\n"
        "            var_f20 = {d};\n",
    ),
    "approach_z": (
        "            spEC += racer->unk120 * 0.5;\n",
        "            {d} = spEC + (racer->unk120 * 0.5);\n"
        "            spEC = {d};\n",
    ),
    "wheel0": (
        "                temp_v0_obj->trans.y_position = temp_v0_obj->trans.y_position - 2.0;\n",
        "                {d} = temp_v0_obj->trans.y_position - 2.0;\n"
        "                temp_v0_obj->trans.y_position = {d};\n",
    ),
}


def make(assignments: tuple[tuple[str, str], ...]) -> str:
    source = BASE
    for site, variable in assignments:
        old, template = SITES[site]
        if source.count(old) < 1:
            raise ValueError(f"site missing: {site}")
        source = source.replace(old, template.format(d=variable), 1)
    return source


def evaluate(tag: str, source: str) -> dict[str, object]:
    result = ORACLE["evaluate"](source, keep=f"/tmp/codex_f64reuse_{tag}.o")
    with open(f"/tmp/codex_f64reuse_{tag}.c", "w", encoding="utf-8") as output:
        output.write(source)
    print(tag, ORACLE["concise"](result), result.get("fp"))
    return result


def main() -> None:
    for site in SITES:
        for variable in ("d0", "d1", "d2"):
            evaluate(f"single_{site}_{variable}", make(((site, variable),)))

    if os.environ.get("CODEX_SINGLES_ONLY"):
        return

    promising = ("rate", "throttle_add", "throttle_sub", "brake_add",
                 "brake_sub", "topspeed", "trick_scale", "approach_x",
                 "approach_z")
    for sites in itertools.permutations(promising, 3):
        tag = "triple_" + "_".join(sites)
        result = evaluate(
            tag,
            make(tuple(zip(sites, ("d0", "d1", "d2")))),
        )
        if result.get("f20_insns") == 69 and result.get("f18", 0) > 100:
            print("HIT", tag)
            break


if __name__ == "__main__":
    main()
