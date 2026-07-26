#!/usr/bin/env python3
"""Reuse existing scratch homes for short post-sqrt register pressure."""

from __future__ import annotations

import itertools
import pathlib
import random
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
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
POOL = (
    "spEC",
    "spE8",
    "spE4",
    "spE0",
    "var_f14",
    "spD8",
    "spD4",
    "spD0",
    "var_f0",
    "var_f2",
    "spCC",
    "var_f6",
    "segmentXVelocity",
    "racerVelocity",
)
FIELDS = (
    "obj->x_velocity",
    "obj->z_velocity",
    "obj->y_velocity",
    "obj->trans.x_position",
    "obj->trans.y_position",
)


def make(hosts: tuple[str, ...], form: str, rotate: int) -> str:
    fields = FIELDS[rotate:] + FIELDS[:rotate]
    assignments = "".join(
        f"    {host} = {fields[i]};\n" for i, host in enumerate(hosts)
    )
    comparisons = [f"({host} > 0.0f)" for host in hosts]
    if form == "factor_zero":
        fake = f"    var_f20 += (f32) (({' + '.join(comparisons)}) * 0);\n"
    elif form == "empty":
        fake = "".join(f"    if ({comparison}) {{}}\n" for comparison in comparisons)
    elif form == "store_zero":
        fake = f"    spA3 = ({' + '.join(comparisons)}) * 0;\n"
    else:
        raise ValueError(form)
    replacement = SQRT + assignments + fake + "    if (racer->vehicleID >= VEHICLE_BOSSES) {\n"
    if BASE.count(OLD) != 1:
        raise ValueError("sqrt block not unique")
    return BASE.replace(OLD, replacement, 1)


def main() -> None:
    random.seed(49794)
    cases: list[tuple[tuple[str, ...], str, int]] = []
    for count in (3, 4, 5):
        combos = list(itertools.combinations(POOL, count))
        if count != 4:
            random.shuffle(combos)
            combos = combos[:20]
        else:
            # Cover every declaration address as well as likely unused scratch sets.
            random.shuffle(combos)
            combos = combos[:60]
        for hosts in combos:
            for form in ("factor_zero", "empty", "store_zero"):
                cases.append((hosts, form, 0))
    # Also test source-field order on a few likely scratch-only host sets.
    special = (
        ("spEC", "spE8", "spE4", "spE0"),
        ("spD8", "spD4", "spD0", "spCC"),
        ("spCC", "var_f6", "segmentXVelocity", "racerVelocity"),
        ("var_f14", "var_f0", "var_f2", "spCC"),
    )
    cases.extend(
        (hosts, "factor_zero", rotate)
        for hosts in special
        for rotate in range(1, len(FIELDS))
    )

    promoted: list[tuple[int, int, str, dict[str, object], pathlib.Path]] = []
    for serial, (hosts, form, rotate) in enumerate(cases):
        tag = f"{serial:04d}_{len(hosts)}_{'_'.join(hosts)}_{form}_r{rotate}"
        source = make(hosts, form, rotate)
        path = pathlib.Path(f"/tmp/codex_postsqrt_existing_{tag}.c")
        path.write_text(source, encoding="utf-8")
        result = ORACLE["evaluate"](source, keep=str(path.with_suffix(".o")))
        if result.get("f20_operands", 0):
            promoted.append(
                (int(result["norm"]), int(result["insns"]), tag, result, path)
            )
            print(tag, ORACLE["concise"](result), result.get("fp"), path)
    print("PROMOTED", len(promoted), "OF", len(cases))
    for _, _, tag, result, path in sorted(promoted)[:50]:
        print("BEST", tag, ORACLE["concise"](result), result.get("fp"), path)


if __name__ == "__main__":
    main()
