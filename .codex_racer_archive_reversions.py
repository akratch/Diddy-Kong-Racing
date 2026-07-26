#!/usr/bin/env python3
"""Cross archived SlvtN source shapes with the strongest canonical source."""

from __future__ import annotations

import concurrent.futures
import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()


def replace_once(source: str, old: str, new: str, tag: str) -> str:
    if source.count(old) != 1:
        raise ValueError((tag, source.count(old)))
    return source.replace(old, new, 1)


def transform(source: str, name: str) -> str:
    if name == "factor_first":
        source = replace_once(source, "    f32 var_f14;\n", "    f32 __swap;\n", name)
        source = replace_once(source, "    f32 var_f20;\n", "    f32 var_f14;\n", name)
        return replace_once(source, "    f32 __swap;\n", "    f32 var_f20;\n", name)
    if name == "segment_temp":
        source = replace_once(
            source,
            "    s8 newSpinoutTimer;\n",
            "    s8 newSpinoutTimer;\n    f32 segmentZVelocity;\n",
            name,
        )
        return replace_once(
            source,
            """\
    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
""",
            """\
    segmentZVelocity = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
                       (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
    var_f14 = segmentZVelocity;
""",
            name,
        )
    if name == "top_combined":
        return replace_once(
            source,
            """\
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
""",
            """\
    var_f14 = (var_f14 * handle_racer_top_speed(obj, racer)) * 1.8;
""",
            name,
        )
    if name == "throttle_temp":
        return replace_once(
            source,
            """\
        racerThrottle = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
""",
            """\
        var_f0 = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * var_f0;
        obj->y_velocity -= racer->oy1 * var_f0;
        obj->z_velocity -= racer->oz1 * var_f0;
""",
            name,
        )
    if name == "unk34_archive":
        return replace_once(
            source,
            "        var_f20 += racer->unk34 * spD0 * 4.0f;\n",
            "        var_f20 += 4.0f * (racer->unk34 * spD0);\n",
            name,
        )
    if name == "buoyancy_archive":
        return replace_once(
            source,
            """\
    if (racer->buoyancy != 0.0) {
        var_f20 = -1.0f;
        gCurrentStickY = -60;
        var_f2 = racer->buoyancy - 20.0f;
        if (var_f2 < 0.0) {
            var_f2 = 0;
        }
        var_f20 -= var_f2 / 10;
""",
            """\
    if (racer->buoyancy != 0.0) {
        gCurrentStickY = -60;
        var_f2 = racer->buoyancy - 20.0f;
        if (var_f2 < 0.0) {
            var_f2 = 0;
        }
        var_f20 = -1 - (var_f2 / 10);
""",
            name,
        )
    if name == "stick_archive":
        return replace_once(
            source,
            "        gCurrentStickY = ((f32) gCurrentStickY) * (1.0 - var_f20);\n",
            "        gCurrentStickY = (1.0 - var_f20) * ((f32) gCurrentStickY);\n",
            name,
        )
    if name == "yvel_archive":
        return replace_once(
            source,
            "            obj->y_velocity = racer->velocity * racer->oy1;\n",
            "            obj->y_velocity = racer->oy1 * racer->velocity;\n",
            name,
        )
    if name == "literal_archive":
        source = replace_once(source, "    spD4 = 0.01f;\n", "    spD4 = 0.01;\n", name)
        source = replace_once(source, "    spD0 = 0.02f;\n", "    spD0 = 0.02;\n", name)
        source = replace_once(source, "    spD8 = 0.004f;\n", "    spD8 = 0.004;\n", name)
        return replace_once(
            source,
            "        spD4 = 0.02f;\n",
            "        spD4 = 0.02;\n",
            name,
        )
    raise ValueError(name)


def make(names: tuple[str, ...]) -> str:
    source = BASE
    for name in names:
        source = transform(source, name)
    return source


def evaluate(names: tuple[str, ...]) -> tuple:
    tag = "_".join(names) if names else "canonical"
    source = make(names)
    with open(f"/tmp/codex_archive_reversions_{tag}.c", "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_archive_reversions_{tag}.o"
    )
    return tag, names, source, result


def main() -> None:
    names = (
        "factor_first",
        "segment_temp",
        "top_combined",
        "throttle_temp",
        "unk34_archive",
        "buoyancy_archive",
        "stick_archive",
        "yvel_archive",
        "literal_archive",
    )
    cases = [()]
    for size in (1, 2, 3):
        cases.extend(itertools.combinations(names, size))
    cases.append(names)
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
    for tag, names, source, result in rows:
        print(tag, ORACLE["concise"](result), result.get("fp"))
    print(
        "tested",
        len(rows),
        "promoted",
        sum(row[3].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
