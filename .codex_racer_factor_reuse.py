#!/usr/bin/env python3
"""Merge disjoint float-temporary ranges into the long var_f20 web."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()


def rename_between(
    source: str,
    start_marker: str,
    end_marker: str,
    old: str,
    new: str = "var_f20",
) -> str:
    start = source.index(start_marker)
    end = source.index(end_marker, start)
    region = source[start:end]
    if old not in region:
        raise ValueError(f"{old} absent from selected region")
    return source[:start] + region.replace(old, new) + source[end:]


def wave_f2(source: str) -> str:
    return rename_between(
        source,
        "        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;\n",
        "    D_8011D550 = 0;\n",
        "var_f2",
    )


def wave_velocity(source: str) -> str:
    return rename_between(
        source,
        "        // previously var_f0\n",
        "    D_8011D550 = 0;\n",
        "racerVelocity",
    )


def steer_divisor(source: str) -> str:
    return rename_between(
        source,
        "    if (racer->trickType != 0) {\n",
        "    racer->steerAngle += var_v1;\n",
        "var_f2",
    )


def trick_speed(source: str) -> str:
    return rename_between(
        source,
        "            var_f2 = -racer->velocity;\n",
        "            var_t0 *= var_f2;\n",
        "var_f2",
    )


def propulsion(source: str) -> str:
    return rename_between(
        source,
        "        var_f0 = racerThrottle * var_f14;\n",
        "        if (racer->groundedWheels >= 3",
        "var_f0",
    )


TRANSFORMS = {
    "steer": steer_divisor,
    "trick": trick_speed,
    "propulsion": propulsion,
}


def make(wave: str, selected: tuple[str, ...]) -> str:
    source = BASE
    if wave == "height":
        source = wave_f2(source)
    elif wave == "velocity":
        source = wave_velocity(source)
    for name in selected:
        source = TRANSFORMS[name](source)
    return source


def main() -> None:
    rows = []
    names = tuple(TRANSFORMS)
    for wave in ("none", "height", "velocity"):
        for count in range(len(names) + 1):
            for selected in itertools.combinations(names, count):
                tag = "_".join((wave,) + selected)
                source = make(wave, selected)
                result = ORACLE["evaluate"](
                    source, keep=f"/tmp/codex_factorreuse_{tag}.o"
                )
                rows.append((tag, result, source))
                print(tag, ORACLE["concise"](result), result.get("fp"))
                if result.get("f20_insns"):
                    with open(
                        f"/tmp/codex_factorreuse_{tag}.c", "w", encoding="utf-8"
                    ) as output:
                        output.write(source)
    print("promoted", sum(row[1].get("f20_insns") == 69 for row in rows))


if __name__ == "__main__":
    main()
