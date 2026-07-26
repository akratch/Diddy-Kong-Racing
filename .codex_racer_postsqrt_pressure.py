#!/usr/bin/env python3
"""Try short-lived FP pressure after sqrtf, avoiding live-across-call spills."""

from __future__ import annotations

import itertools
import pathlib
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
OLD = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
    if (racer->vehicleID >= VEHICLE_BOSSES) {
"""
SQRT = """\
        pressResult = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                            (obj->y_velocity * obj->y_velocity)) -
                      2.0;
"""
FIELDS = (
    "obj->x_velocity",
    "obj->z_velocity",
    "obj->y_velocity",
    "obj->trans.x_position",
    "obj->trans.y_position",
    "obj->trans.z_position",
    "racer->velocity",
    "racer->ox1",
)


def assignments(topology: str, count: int) -> str:
    lines: list[str] = []
    if topology == "fields":
        lines = [f"        press{i} = {FIELDS[i]};\n" for i in range(count)]
    elif topology == "result_star":
        lines = [f"        press{i} = pressResult;\n" for i in range(count)]
    elif topology == "result_chain":
        for i in range(count):
            source = "pressResult" if i == 0 else f"press{i - 1}"
            lines.append(f"        press{i} = {source};\n")
    elif topology == "field_chain":
        lines.append(f"        press0 = {FIELDS[0]};\n")
        for i in range(1, count):
            lines.append(f"        press{i} = press{i - 1};\n")
    else:
        raise ValueError(topology)
    return "".join(lines)


def fake(count: int, form: str) -> str:
    values = [f"press{i}" for i in range(count)]
    comparisons = [f"({value} > 0.0f)" for value in values]
    if form == "factor_zero":
        return f"        var_f20 += (f32) (({' + '.join(comparisons)}) * 0);\n"
    if form == "empty":
        return "".join(f"        if ({comparison}) {{}}\n" for comparison in comparisons)
    if form == "store_zero":
        return f"        spA3 = ({' + '.join(comparisons)}) * 0;\n"
    if form == "comma":
        return f"        spA3 = ({', '.join(comparisons)}, 0);\n"
    raise ValueError(form)


def make(topology: str, count: int, placement: str, form: str) -> str:
    decls = "        f32 pressResult;\n" + "".join(
        f"        f32 press{i};\n" for i in range(count)
    )
    loads = assignments(topology, count)
    use = fake(count, form)
    if placement == "before_factor":
        body = SQRT + loads + "        var_f20 = pressResult;\n" + use
    elif placement == "after_factor":
        body = SQRT + "        var_f20 = pressResult;\n" + loads + use
    elif placement == "split_factor":
        # Assign before and after the blockers to encourage a split/merge web.
        body = (
            SQRT
            + "        var_f20 = pressResult;\n"
            + loads
            + "        var_f20 = pressResult;\n"
            + use
        )
    else:
        raise ValueError(placement)
    replacement = (
        "    {\n"
        + decls
        + body
        + "    }\n"
        + "    if (racer->vehicleID >= VEHICLE_BOSSES) {\n"
    )
    if BASE.count(OLD) != 1:
        raise ValueError("sqrt block not unique")
    return BASE.replace(OLD, replacement, 1)


def main() -> None:
    cases = itertools.product(
        ("fields", "result_star", "result_chain", "field_chain"),
        range(1, 9),
        ("before_factor", "after_factor", "split_factor"),
        ("factor_zero", "empty", "store_zero", "comma"),
    )
    promoted: list[tuple[int, str, dict[str, object], pathlib.Path]] = []
    for serial, (topology, count, placement, form) in enumerate(cases):
        tag = f"{serial:03d}_{topology}_{count}_{placement}_{form}"
        source = make(topology, count, placement, form)
        path = pathlib.Path(f"/tmp/codex_postsqrt_{tag}.c")
        path.write_text(source, encoding="utf-8")
        result = ORACLE["evaluate"](source, keep=str(path.with_suffix(".o")))
        if result.get("f20_operands", 0):
            promoted.append((int(result["norm"]), tag, result, path))
            print(tag, ORACLE["concise"](result), result.get("fp"), path)
    print("PROMOTED", len(promoted))
    for _, tag, result, path in sorted(promoted)[:30]:
        print("BEST", tag, ORACLE["concise"](result), result.get("fp"), path)


if __name__ == "__main__":
    main()
