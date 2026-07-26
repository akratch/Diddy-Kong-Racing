#!/usr/bin/env python3
"""Move invariant final-drag axis preloads across the late plane CFG."""

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

ANCHOR_SP_EC = "        spEC = racer->velocity * racer->velocity;\n"
ANCHOR_LATERAL = (
    "    var_f20 = racer->lateral_velocity * racer->lateral_velocity * spD4;\n"
)
ANCHOR_TRICK = (
    "        obj->z_velocity -= racer->oz3 * var_f20;\n"
    "        if (racer->trickType == 1 || racer->trickType == -1) {\n"
)


def replace_once(source: str, old: str, new: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"expected one occurrence, found {count}: {old!r}")
    return source.replace(old, new, 1)


def make(
    positions: tuple[int, int, int],
    hosts: tuple[str, str, str],
    held: bool,
) -> str:
    source = BASE
    if held:
        factor = "        var_f2 = racer->unk34 * spD0;\n"
        delta = "        var_f20 += 4.0f * var_f2;\n"
    else:
        factor = "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n"
        delta = "        var_f20 += 4.0f * (racer->unk34 * spD0);\n"
    if held:
        source = replace_once(
            source,
            OLD_DELTA,
            """\
        var_f2 = racer->unk34 * spD0;
        var_f20 = racer->unk34 * var_f2;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * var_f2;
""",
        )
    x, y, z = hosts
    drag = f"""\
        obj->x_velocity -= {x} * var_f20;
        obj->y_velocity -= {y} * var_f20;
        obj->z_velocity -= {z} * var_f20;
"""
    source = replace_once(source, OLD_DRAG, drag)
    assignments = (
        f"        {x} = racer->ox2;\n",
        f"        {y} = racer->oy2;\n",
        f"        {z} = racer->oz2;\n",
    )
    insertions: dict[int, str] = {}
    for position, assignment in zip(positions, assignments):
        insertions[position] = insertions.get(position, "") + assignment
    anchors = (
        ANCHOR_SP_EC,
        ANCHOR_LATERAL,
        ANCHOR_TRICK,
        factor,
        "        if (racer->unk34 < 0.0f) {\n",
        delta,
        drag,
    )
    for position, lines in sorted(insertions.items()):
        anchor = anchors[position]
        source = replace_once(source, anchor, lines + anchor)
    return source


def evaluate(
    positions: tuple[int, int, int],
    hosts: tuple[str, str, str],
    held: bool,
) -> tuple[str, dict[str, object], str]:
    tag = (
        f"{'held' if held else 'inline'}_"
        f"{''.join(map(str, positions))}_"
        f"{'-'.join(hosts)}"
    )
    source = make(positions, hosts, held)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_axispre_{tag}.o"
    )
    return tag, result, source


def main() -> None:
    base_hosts = ("spCC", "var_f6", "segmentXVelocity")
    phase1 = [
        ((position, position, position), hosts, held)
        for position in range(7)
        for hosts in itertools.permutations(base_hosts)
        for held in (False, True)
    ]
    rows = [evaluate(*item) for item in phase1]
    print("PHASE1", len(rows))
    for tag, result, source in rows:
        if result.get("f20_insns") or result.get("f18", 0) > 100:
            print(tag, ORACLE["concise"](result), result.get("fp"))
            with open(f"/tmp/codex_axispre_{tag}.c", "w", encoding="utf-8") as output:
                output.write(source)

    phase2 = [
        (positions, base_hosts, held)
        for positions in itertools.combinations_with_replacement(
            range(7), 3
        )
        for held in (False, True)
    ]
    rows = [evaluate(*item) for item in phase2]
    promoted = [row for row in rows if row[1].get("f20_insns") == 69]
    promoted.sort(
        key=lambda row: (
            abs(int(row[1].get("f18", 0)) - 190),
            abs(int(row[1].get("insns", 9999)) - 2625),
            int(row[1].get("norm", 9999)),
        )
    )
    print("PHASE2", len(rows), "promoted", len(promoted))
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
        print("BEST", tag, ORACLE["concise"](result), result.get("fp"))
        with open(f"/tmp/codex_axispre_{tag}.c", "w", encoding="utf-8") as output:
            output.write(source)
        if len(seen) >= 50:
            break


if __name__ == "__main__":
    main()
