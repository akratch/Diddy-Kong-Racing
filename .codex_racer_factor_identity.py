#!/usr/bin/env python3
"""Move the initial factor web among existing local identities."""

from __future__ import annotations

import pathlib
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
INITIAL = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
"""
LATER = "                var_f20 = racer->velocity * var_t0 * 0.00015;\n"
HOSTS = ("spCC", "var_f6", "segmentXVelocity")


def swap_identity(host: str) -> str:
    source = BASE.replace("var_f20", "__CODEX_FACTOR_SWAP__")
    source = source.replace(host, "var_f20")
    return source.replace("__CODEX_FACTOR_SWAP__", host)


def initial_only(host: str) -> str:
    start = BASE.index(INITIAL)
    end = BASE.index(LATER, start)
    region = BASE[start:end].replace("var_f20", host)
    return BASE[:start] + region + BASE[end:]


def initial_and_late(host: str, keep_regions: int) -> str:
    source = initial_only(host)
    markers = [
        LATER,
        "            var_f20 = racer->velocity * spD8 * 8.0f;\n",
        "        var_f20 = obj->x_velocity;\n",
    ]
    for marker in markers[:keep_regions]:
        start = source.index(marker)
        # Rename from this marker to the next assignment of a different
        # region, or to the function end for the final one.
        next_starts = [
            source.find(next_marker, start + 1)
            for next_marker in markers
            if source.find(next_marker, start + 1) >= 0
        ]
        end = min(next_starts) if next_starts else source.index("\n}\n", start)
        region = source[start:end].replace("var_f20", host)
        source = source[:start] + region + source[end:]
    return source


def main() -> None:
    cases: dict[str, str] = {}
    for host in HOSTS:
        cases[f"swap_{host}"] = swap_identity(host)
        cases[f"initial_{host}"] = initial_only(host)
        for regions in range(1, 4):
            cases[f"initial_{host}_late{regions}"] = initial_and_late(
                host, regions
            )
    rows = []
    for serial, (name, source) in enumerate(cases.items()):
        path = pathlib.Path(f"/tmp/codex_factor_identity_{serial:03d}_{name}.c")
        path.write_text(source, encoding="utf-8")
        result = ORACLE["evaluate"](source, keep=str(path.with_suffix(".o")))
        rows.append(
            (
                not bool(result.get("f20_operands", 0)),
                int(result.get("norm", 9999)),
                name,
                result,
                path,
            )
        )
    for _, _, name, result, path in sorted(rows):
        print(name, ORACLE["concise"](result), result.get("fp"), path)


if __name__ == "__main__":
    main()
