#!/usr/bin/env python3
"""Hoist real later FP definitions across the factor's early control flow."""

from __future__ import annotations

import itertools
import pathlib
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
ANCHOR = """\
    if (racer->vehicleID >= VEHICLE_BOSSES) {
"""
DEFINITIONS = (
    ("v2", "    var_f2 = (gCurrentCourseHeight - 50.0) - obj->trans.y_position;\n"),
    ("v14", "    var_f14 = racer->velocity;\n"),
    ("v0", "    var_f0 = racer->velocity;\n"),
    ("d4", "    spD4 = 0.01f;\n"),
    ("d0", "    spD0 = 0.02f;\n"),
    ("d8", "    spD8 = 0.004f;\n"),
)


def make(indices: tuple[int, ...], reverse: bool) -> str:
    source = BASE
    ordered = tuple(reversed(indices)) if reverse else indices
    hoisted = "".join(DEFINITIONS[i][1] for i in ordered)
    for i in indices:
        definition = DEFINITIONS[i][1]
        if source.count(definition) != 1:
            raise ValueError((DEFINITIONS[i][0], source.count(definition)))
        source = source.replace(definition, "", 1)
    if source.count(ANCHOR) < 1:
        raise ValueError("anchor missing")
    return source.replace(ANCHOR, hoisted + ANCHOR, 1)


def main() -> None:
    rows = []
    serial = 0
    for count in range(1, len(DEFINITIONS) + 1):
        for indices in itertools.combinations(range(len(DEFINITIONS)), count):
            for reverse in (False, True):
                names = "_".join(DEFINITIONS[i][0] for i in indices)
                tag = f"{serial:03d}_{names}_{'rev' if reverse else 'fwd'}"
                serial += 1
                source = make(indices, reverse)
                path = pathlib.Path(f"/tmp/codex_real_hoist_{tag}.c")
                path.write_text(source, encoding="utf-8")
                result = ORACLE["evaluate"](source, keep=str(path.with_suffix(".o")))
                rows.append(
                    (
                        not bool(result.get("f20_operands", 0)),
                        int(result.get("norm", 9999)),
                        abs(int(result.get("insns", 9999)) - 2625),
                        tag,
                        result,
                        path,
                    )
                )
    for _, _, _, tag, result, path in sorted(rows):
        print(tag, ORACLE["concise"](result), result.get("fp"), path)


if __name__ == "__main__":
    main()
