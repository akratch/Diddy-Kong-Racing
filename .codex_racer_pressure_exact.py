#!/usr/bin/env python3
"""Probe final-drag pressure shapes on the structurally exact plane source."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()

OLD_DELTA = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
OLD_DRAG = """\
        obj->x_velocity -= racer->ox2 * var_f20;
        obj->y_velocity -= racer->oy2 * var_f20;
        obj->z_velocity -= racer->oz2 * var_f20;
"""

HOST_SETS = (
    ("spCC", "var_f6", "segmentXVelocity"),
    ("spCC", "var_f0", "var_f6"),
    ("var_f0", "var_f6", "segmentXVelocity"),
    ("spCC", "racerThrottle", "racerBrake"),
)


def replace_once(source: str, old: str, new: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"expected one occurrence, found {count}: {old!r}")
    return source.replace(old, new, 1)


def shape(source: str, kind: str, hosts: tuple[str, str, str]) -> str:
    x, y, z = hosts
    if kind == "products":
        block = f"""\
        {x} = racer->ox2 * var_f20;
        {y} = racer->oy2 * var_f20;
        {z} = racer->oz2 * var_f20;
        obj->x_velocity -= {x};
        obj->y_velocity -= {y};
        obj->z_velocity -= {z};
"""
    elif kind == "results":
        block = f"""\
        {x} = obj->x_velocity - (racer->ox2 * var_f20);
        {y} = obj->y_velocity - (racer->oy2 * var_f20);
        {z} = obj->z_velocity - (racer->oz2 * var_f20);
        obj->x_velocity = {x};
        obj->y_velocity = {y};
        obj->z_velocity = {z};
"""
    elif kind == "axes":
        block = f"""\
        {x} = racer->ox2;
        {y} = racer->oy2;
        {z} = racer->oz2;
        obj->x_velocity -= {x} * var_f20;
        obj->y_velocity -= {y} * var_f20;
        obj->z_velocity -= {z} * var_f20;
"""
    elif kind == "velocities":
        block = f"""\
        {x} = obj->x_velocity;
        {y} = obj->y_velocity;
        {z} = obj->z_velocity;
        obj->x_velocity = {x} - (racer->ox2 * var_f20);
        obj->y_velocity = {y} - (racer->oy2 * var_f20);
        obj->z_velocity = {z} - (racer->oz2 * var_f20);
"""
    else:
        raise ValueError(kind)
    return replace_once(source, OLD_DRAG, block)


def held_delta(source: str, host: str) -> str:
    block = f"""\
        {host} = racer->unk34 * spD0;
        var_f20 = racer->unk34 * {host};
        if (racer->unk34 < 0.0f) {{
            var_f20 = -var_f20;
        }}
        var_f20 += 4.0f * {host};
"""
    return replace_once(source, OLD_DELTA, block)


def main() -> None:
    rows = []
    for held in (None, "var_f2", "racerBrake", "racerThrottle"):
        base = held_delta(BASE, held) if held else BASE
        for kind in ("products", "results", "axes", "velocities"):
            for hosts in HOST_SETS:
                for ordered in itertools.permutations(hosts):
                    tag = "_".join(
                        (
                            held or "inline",
                            kind,
                            "-".join(ordered),
                        )
                    )
                    source = shape(base, kind, ordered)
                    result = ORACLE["evaluate"](
                        source, keep=f"/tmp/codex_pressure_exact_{tag}.o"
                    )
                    rows.append((tag, result, source))
    promoted = [row for row in rows if row[1].get("f20_insns") == 69]
    promoted.sort(
        key=lambda row: (
            abs(int(row[1].get("f18", 0)) - 190),
            abs(int(row[1].get("insns", 9999)) - 2625),
            int(row[1].get("norm", 9999)),
        )
    )
    print("tested", len(rows), "promoted", len(promoted))
    seen: set[str] = set()
    for tag, result, source in promoted:
        signature = str(
            (
                result.get("sha1"),
                result.get("frame"),
                result.get("insns"),
                result.get("f18"),
            )
        )
        if signature in seen:
            continue
        seen.add(signature)
        path = f"/tmp/codex_pressure_exact_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        print(tag, ORACLE["concise"](result), result.get("fp"), path)
        if len(seen) >= 40:
            break


if __name__ == "__main__":
    main()
