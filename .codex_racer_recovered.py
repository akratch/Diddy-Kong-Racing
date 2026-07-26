#!/usr/bin/env python3
"""Search source-equivalent drag shapes on the later recovered racer source."""

from __future__ import annotations

import concurrent.futures
import itertools
import re
import runpy
import sys
from pathlib import Path


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = ORACLE["recovered"]()
TARGET_FP = {
    "f0": 131,
    "f2": 66,
    "f4": 188,
    "f6": 188,
    "f8": 187,
    "f10": 188,
    "f12": 62,
    "f14": 50,
    "f16": 8,
    "f18": 190,
    "f20": 74,
    "f21": 2,
}
POOL = (
    "spEC",
    "spE8",
    "spE4",
    "spE0",
    "spD8",
    "spD4",
    "spD0",
    "spCC",
    "racerThrottle",
    "racerBrake",
    "var_f0",
    "var_f2",
    "var_f6",
    "segmentXVelocity",
    "var_f14",
)
OLD = """\
        obj->x_velocity -= racer->ox2 * var_f20;
        obj->y_velocity -= racer->oy2 * var_f20;
        obj->z_velocity -= racer->oz2 * var_f20;

        racer->forwardVel"""
FLOAT_INITIALIZERS = """\
    spD4 = 0.01f;
    spD0 = 0.02f;
    spD8 = 0.004f;
"""


def constants_before_speed(source: str) -> str:
    assert FLOAT_INITIALIZERS in source
    source = source.replace(FLOAT_INITIALIZERS, "", 1)
    anchor = (
        "    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + "
        "(obj->z_velocity * obj->z_velocity) +\n"
    )
    assert anchor in source
    return source.replace(anchor, FLOAT_INITIALIZERS + anchor, 1)


def initialize_sp_d(source: str, name: str) -> str:
    values = {"spD8": "0.004f", "spD4": "0.01f", "spD0": "0.02f"}
    value = values[name]
    declaration = f"    f32 {name};\n"
    assignment = f"    {name} = {value};\n"
    assert declaration in source
    assert assignment in source
    return source.replace(
        declaration, f"    f32 {name} = {value};\n", 1
    ).replace(assignment, "", 1)


def reshape_sp_ec(source: str, variant: int) -> str:
    initial = "        spEC = racer->velocity * racer->velocity;\n"
    trick = (
        "            spEC = racer->velocity * "
        "0.058823529411764705 * 1.5;\n"
    )
    assert initial in source
    assert trick in source
    if variant == 1:
        source = source.replace(
            initial,
            "        spEC = (spEC = racer->velocity * racer->velocity);\n",
            1,
        ).replace(
            trick,
            "            spEC = (spEC = racer->velocity * "
            "0.058823529411764705 * 1.5);\n",
            1,
        )
    elif variant == 2:
        source = source.replace(initial, initial + "        spEC = spEC;\n", 1)
        source = source.replace(trick, trick + "            spEC = spEC;\n", 1)
    elif variant == 3:
        source = source.replace(
            "        if (spEC < 1.0f && ",
            "        if ((spEC = spEC) < 1.0f && ",
            1,
        )
    elif variant == 4:
        source = source.replace(
            "        if (spEC < 1.0f && ",
            "        if (spEC < 1.0f && spEC < 1.0f && ",
            1,
        )
    elif variant == 5:
        source = source.replace(
            "        if (spEC < 1.0f && ",
            "        if ((spEC, spEC < 1.0f) && ",
            1,
        )
    elif variant == 6:
        source = source.replace(
            "            var_f20 = spEC * spD8;\n",
            "            var_f20 = (spEC = spEC) * spD8;\n",
            1,
        )
    else:
        raise ValueError(variant)
    return source


def loop_sp_ec_region(source: str, variant: int) -> str:
    begin_marker = "        spEC = racer->velocity * racer->velocity;\n"
    end_marker = "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n"
    begin = source.index(begin_marker)
    end = source.index(end_marker, begin)
    region = source[begin:end]
    if variant == 1:
        wrapped = "        do {\n" + region + "        } while (0);\n"
    elif variant == 2:
        wrapped = (
            "        while (1) {\n"
            + region
            + "            break;\n"
            + "        }\n"
        )
    elif variant == 3:
        wrapped = (
            "        for (;;) {\n"
            + region
            + "            break;\n"
            + "        }\n"
        )
    elif variant == 4:
        wrapped = (
            "        do {\n"
            + region
            + "            break;\n"
            + "        } while (1);\n"
        )
    else:
        raise ValueError(variant)
    return source[:begin] + wrapped + source[end:]


def duplicate_final_delta(source: str) -> str:
    old = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    new = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
            var_f20 += 4.0f * (racer->unk34 * spD0);
        } else {
            var_f20 += 4.0f * (racer->unk34 * spD0);
        }
"""
    assert old in source
    return source.replace(old, new, 1)


def reshape_final_sign(source: str, variant: int) -> str:
    old = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    if variant == 1:
        new = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        var_f20 = racer->unk34 < 0.0f ? -var_f20 : var_f20;
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    elif variant == 2:
        new = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        var_f20 = (racer->unk34 < 0.0f ? -var_f20 : var_f20) +
                  (4.0f * (racer->unk34 * spD0));
"""
    elif variant == 3:
        new = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        } else {
            var_f20 = var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    elif variant == 4:
        new = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (!(racer->unk34 >= 0.0f)) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    elif variant == 5:
        new = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 >= 0.0f) {
        } else {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    else:
        raise ValueError(variant)
    assert old in source
    return source.replace(old, new, 1)


def merge_preceding_into_sp_ec(source: str, holder: str) -> str:
    function_start = source.index("void func_80049794")
    code_start = source.index("\n\n    if (func_8000E138())", function_start)
    sp_ec_start = source.index(
        "        spEC = racer->velocity * racer->velocity;\n", code_start
    )
    before = source[code_start:sp_ec_start]
    assert re.search(rf"\b{re.escape(holder)}\b", before)
    before = re.sub(rf"\b{re.escape(holder)}\b", "spEC", before)
    return source[:code_start] + before + source[sp_ec_start:]


def merge_var_f2_ranges_into_sp_ec(source: str, count: int) -> str:
    ranges = (
        (
            "            var_f2 = -racer->velocity;\n",
            "            var_t0 *= var_f2;\n",
        ),
        (
            "        var_f2 = racer->buoyancy - 20.0f;\n",
            "        var_f20 = -1 - (var_f2 / 10);\n",
        ),
        (
            "    var_f2 = (gCurrentCourseHeight - 50.0) - "
            "obj->trans.y_position;\n",
            "        spA3 = TRUE;\n",
        ),
        (
            "        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;\n",
            "        racer->unk1BA = 0;\n",
        ),
    )
    for start_marker, end_marker in ranges[:count]:
        start = source.index(start_marker)
        end = source.index(end_marker, start) + len(end_marker)
        region = source[start:end]
        assert "var_f2" in region
        region = re.sub(r"\bvar_f2\b", "spEC", region)
        source = source[:start] + region + source[end:]
    return source


def hold_final_delta(source: str, holder: str) -> str:
    old = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
    new = f"""\
        {holder} = racer->unk34 * spD0;
        var_f20 = racer->unk34 * {holder};
        if (racer->unk34 < 0.0f) {{
            var_f20 = -var_f20;
        }}
        var_f20 += 4.0f * {holder};
"""
    assert old in source
    return source.replace(old, new, 1)


def replace_drag(source: str, shape: str, hosts: tuple[str, str, str]) -> str:
    for count in range(1, 5):
        suffix = f"-mergef2r{count}"
        if shape.endswith(suffix):
            source = merge_var_f2_ranges_into_sp_ec(source, count)
            shape = shape.removesuffix(suffix)
            break
    for holder, suffix in (
        ("var_f2", "-deltaf2"),
        ("racerBrake", "-deltabrake"),
        ("racerThrottle", "-deltathrottle"),
        ("segmentXVelocity", "-deltasegment"),
    ):
        if shape.endswith(suffix):
            source = hold_final_delta(source, holder)
            shape = shape.removesuffix(suffix)
            break
    for holder, suffix in (
        ("racerBrake", "-mergebrake"),
        ("racerThrottle", "-mergethrottle"),
        ("var_f2", "-mergef2"),
        ("var_f14", "-mergef14"),
    ):
        if shape.endswith(suffix):
            source = merge_preceding_into_sp_ec(source, holder)
            shape = shape.removesuffix(suffix)
            break
    for name, suffix in (
        ("spD8", "-initd8"),
        ("spD4", "-initd4"),
        ("spD0", "-initd0"),
    ):
        if shape.endswith(suffix):
            source = initialize_sp_d(source, name)
            shape = shape.removesuffix(suffix)
            break
    sign_variant = None
    for variant in range(1, 6):
        suffix = f"-sign{variant}"
        if shape.endswith(suffix):
            sign_variant = variant
            shape = shape.removesuffix(suffix)
            break
    if sign_variant is not None:
        source = reshape_final_sign(source, sign_variant)
    if shape.endswith("-dupdelta"):
        source = duplicate_final_delta(source)
        shape = shape.removesuffix("-dupdelta")
    loop_variant = None
    for variant in range(1, 5):
        suffix = f"-specloop{variant}"
        if shape.endswith(suffix):
            loop_variant = variant
            shape = shape.removesuffix(suffix)
            break
    if loop_variant is not None:
        source = loop_sp_ec_region(source, loop_variant)
    match = None
    for variant in range(1, 7):
        suffix = f"-speccse{variant}"
        if shape.endswith(suffix):
            match = variant
            shape = shape.removesuffix(suffix)
            break
    if match is not None:
        source = reshape_sp_ec(source, match)
    if shape.endswith("-const-early"):
        source = constants_before_speed(source)
        shape = shape.removesuffix("-const-early")
    x, y, z = hosts
    if shape in (
        "axis-early-duplicate-delta",
        "velocity-early-duplicate-delta",
    ):
        sign_and_delta = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += 4.0f * (racer->unk34 * spD0);
"""
        assert sign_and_delta in source
        if shape.startswith("axis-"):
            definitions = (
                f"        {x} = racer->ox2;\n"
                f"        {y} = racer->oy2;\n"
                f"        {z} = racer->oz2;\n"
            )
            updates = (
                f"        obj->x_velocity -= {x} * var_f20;\n"
                f"        obj->y_velocity -= {y} * var_f20;\n"
                f"        obj->z_velocity -= {z} * var_f20;\n"
            )
        else:
            definitions = (
                f"        {x} = obj->x_velocity;\n"
                f"        {y} = obj->y_velocity;\n"
                f"        {z} = obj->z_velocity;\n"
            )
            updates = (
                f"        obj->x_velocity = {x} - (racer->ox2 * var_f20);\n"
                f"        obj->y_velocity = {y} - (racer->oy2 * var_f20);\n"
                f"        obj->z_velocity = {z} - (racer->oz2 * var_f20);\n"
            )
        delta = "4.0f * (racer->unk34 * spD0)"
        replacement = (
            definitions
            + "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n"
            + "        if (racer->unk34 < 0.0f) {\n"
            + "            var_f20 = -var_f20;\n"
            + f"            var_f20 += {delta};\n"
            + "        } else {\n"
            + f"            var_f20 += {delta};\n"
            + "        }\n"
        )
        source = source.replace(sign_and_delta, replacement, 1)
        body = updates + "\n        racer->forwardVel"
        assert OLD in source
        return source.replace(OLD, body, 1)
    if shape in ("axis-inputs-branch-phi", "velocity-inputs-branch-phi"):
        sign_block = """\
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
"""
        assert sign_block in source
        if shape == "axis-inputs-branch-phi":
            assignments = (
                f"            {x} = racer->ox2;\n"
                f"            {y} = racer->oy2;\n"
                f"            {z} = racer->oz2;\n"
            )
            updates = (
                f"        obj->x_velocity -= {x} * var_f20;\n"
                f"        obj->y_velocity -= {y} * var_f20;\n"
                f"        obj->z_velocity -= {z} * var_f20;\n"
            )
        else:
            assignments = (
                f"            {x} = obj->x_velocity;\n"
                f"            {y} = obj->y_velocity;\n"
                f"            {z} = obj->z_velocity;\n"
            )
            updates = (
                f"        obj->x_velocity = {x} - (racer->ox2 * var_f20);\n"
                f"        obj->y_velocity = {y} - (racer->oy2 * var_f20);\n"
                f"        obj->z_velocity = {z} - (racer->oz2 * var_f20);\n"
            )
        replacement = (
            "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n"
            "        if (racer->unk34 < 0.0f) {\n"
            "            var_f20 = -var_f20;\n"
            + assignments
            + "        } else {\n"
            + assignments
            + "        }\n"
        )
        source = source.replace(sign_block, replacement, 1)
        body = updates + "\n        racer->forwardVel"
        assert OLD in source
        return source.replace(OLD, body, 1)
    if shape in (
        "axis-inputs-early",
        "axis-early-label",
        "axis-early-goto",
        "axis-early-self",
        "axis-early-void",
        "velocity-inputs-early",
    ):
        anchor = "        var_f20 = racer->unk34 * racer->unk34 * spD0;\n"
        assert anchor in source
        if shape.startswith("axis-"):
            definitions = (
                f"        {x} = racer->ox2;\n"
                f"        {y} = racer->oy2;\n"
                f"        {z} = racer->oz2;\n"
            )
            updates = (
                f"        obj->x_velocity -= {x} * var_f20;\n"
                f"        obj->y_velocity -= {y} * var_f20;\n"
                f"        obj->z_velocity -= {z} * var_f20;\n"
            )
        else:
            definitions = (
                f"        {x} = obj->x_velocity;\n"
                f"        {y} = obj->y_velocity;\n"
                f"        {z} = obj->z_velocity;\n"
            )
            updates = (
                f"        obj->x_velocity = {x} - (racer->ox2 * var_f20);\n"
                f"        obj->y_velocity = {y} - (racer->oy2 * var_f20);\n"
                f"        obj->z_velocity = {z} - (racer->oz2 * var_f20);\n"
            )
        if shape == "axis-early-label":
            definitions += "codex_drag_inputs_ready:\n"
        elif shape == "axis-early-goto":
            definitions += (
                "        goto codex_drag_inputs_ready;\n"
                "codex_drag_inputs_ready:\n"
            )
        elif shape == "axis-early-self":
            definitions += (
                f"        {x} = {x};\n"
                f"        {y} = {y};\n"
                f"        {z} = {z};\n"
            )
        elif shape == "axis-early-void":
            definitions += (
                f"        (void) {x};\n"
                f"        (void) {y};\n"
                f"        (void) {z};\n"
            )
        source = source.replace(anchor, definitions + anchor, 1)
        body = updates + "\n        racer->forwardVel"
        assert OLD in source
        return source.replace(OLD, body, 1)
    if shape == "products":
        body = f"""\
        {x} = racer->ox2 * var_f20;
        {y} = racer->oy2 * var_f20;
        {z} = racer->oz2 * var_f20;
        obj->x_velocity -= {x};
        obj->y_velocity -= {y};
        obj->z_velocity -= {z};

        racer->forwardVel"""
    elif shape == "partial-products-xy":
        body = f"""\
        {x} = racer->ox2 * var_f20;
        {y} = racer->oy2 * var_f20;
        obj->x_velocity -= {x};
        obj->y_velocity -= {y};
        obj->z_velocity -= racer->oz2 * var_f20;

        racer->forwardVel"""
    elif shape == "partial-products-xz":
        body = f"""\
        {x} = racer->ox2 * var_f20;
        {y} = racer->oz2 * var_f20;
        obj->x_velocity -= {x};
        obj->y_velocity -= racer->oy2 * var_f20;
        obj->z_velocity -= {y};

        racer->forwardVel"""
    elif shape == "partial-products-yz":
        body = f"""\
        {x} = racer->oy2 * var_f20;
        {y} = racer->oz2 * var_f20;
        obj->x_velocity -= racer->ox2 * var_f20;
        obj->y_velocity -= {x};
        obj->z_velocity -= {y};

        racer->forwardVel"""
    elif shape == "results":
        body = f"""\
        {x} = obj->x_velocity - (racer->ox2 * var_f20);
        {y} = obj->y_velocity - (racer->oy2 * var_f20);
        {z} = obj->z_velocity - (racer->oz2 * var_f20);
        obj->x_velocity = {x};
        obj->y_velocity = {y};
        obj->z_velocity = {z};

        racer->forwardVel"""
    elif shape == "axis-inputs":
        body = f"""\
        {x} = racer->ox2;
        {y} = racer->oy2;
        {z} = racer->oz2;
        obj->x_velocity -= {x} * var_f20;
        obj->y_velocity -= {y} * var_f20;
        obj->z_velocity -= {z} * var_f20;

        racer->forwardVel"""
    elif shape == "velocity-inputs":
        body = f"""\
        {x} = obj->x_velocity;
        {y} = obj->y_velocity;
        {z} = obj->z_velocity;
        obj->x_velocity = {x} - (racer->ox2 * var_f20);
        obj->y_velocity = {y} - (racer->oy2 * var_f20);
        obj->z_velocity = {z} - (racer->oz2 * var_f20);

        racer->forwardVel"""
    elif shape == "mixed-axis-product":
        body = f"""\
        {x} = racer->ox2;
        {y} = racer->oy2 * var_f20;
        {z} = racer->oz2 * var_f20;
        obj->x_velocity -= {x} * var_f20;
        obj->y_velocity -= {y};
        obj->z_velocity -= {z};

        racer->forwardVel"""
    else:
        raise ValueError(shape)
    assert OLD in source
    return source.replace(OLD, body, 1)


def fp_distance(fp: dict[str, int]) -> int:
    return sum(abs(fp.get(reg, 0) - count) for reg, count in TARGET_FP.items())


def evaluate(item: tuple[str, tuple[str, str, str]]) -> tuple[object, ...]:
    shape, hosts = item
    source = replace_drag(BASE, shape, hosts)
    result = ORACLE["evaluate"](source)
    fp = result.get("fp", {})
    return (
        result.get("frame"),
        result.get("f20_insns"),
        fp_distance(fp),
        result.get("norm", 99999),
        abs(result.get("insns", 0) - 2625),
        shape,
        hosts,
        result,
        source,
    )


def sweep(shapes: tuple[str, ...]) -> None:
    items = [
        (shape, hosts)
        for shape in shapes
        for hosts in itertools.combinations(POOL, 3)
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        results = list(executor.map(evaluate, items))
    promoted = [
        row for row in results if row[0] == -248 and row[1] == 69
    ]
    promoted.sort(key=lambda row: row[2:5])
    print(
        f"total={len(results)} target-frame-promoted={len(promoted)}",
        flush=True,
    )
    for rank, row in enumerate(promoted[:50], 1):
        print(
            f"BEST {rank} distance={row[2]} norm={row[3]} "
            f"insn_delta={row[4]} shape={row[5]} hosts={row[6]} "
            f"{ORACLE['concise'](row[7])} fp={row[7].get('fp')}",
            flush=True,
        )
    if promoted:
        Path("/tmp/codex_drag_shape_best.c").write_text(promoted[0][8])


def main() -> None:
    if len(sys.argv) == 6 and sys.argv[1] == "one":
        shape = sys.argv[2]
        hosts = (sys.argv[3], sys.argv[4], sys.argv[5])
        source = replace_drag(BASE, shape, hosts)
        result = ORACLE["evaluate"](source)
        Path("/tmp/codex_drag_one.c").write_text(source)
        print(shape, hosts, ORACLE["concise"](result), result.get("fp"))
        return
    if len(sys.argv) >= 2 and sys.argv[1] == "pairs":
        shapes = tuple(sys.argv[2:]) or (
            "partial-products-xy-const-early",
            "partial-products-xz-const-early",
            "partial-products-yz-const-early",
        )
        items = [
            (shape, (hosts[0], hosts[1], hosts[0]))
            for shape in shapes
            for hosts in itertools.combinations(POOL, 2)
        ]
        with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
            results = list(executor.map(evaluate, items))
        promoted = [row for row in results if row[1] == 69]
        promoted.sort(key=lambda row: (row[0] != -248, row[2:5]))
        print(f"total={len(results)} promoted={len(promoted)}")
        for row in promoted[:60]:
            print(
                f"PAIR frame={row[0]} distance={row[2]} norm={row[3]} "
                f"insn_delta={row[4]} shape={row[5]} hosts={row[6][:2]} "
                f"{ORACLE['concise'](row[7])} fp={row[7].get('fp')}"
            )
        return
    shapes = tuple(sys.argv[1:]) or (
        "axis-inputs",
        "velocity-inputs",
        "results",
        "mixed-axis-product",
    )
    sweep(shapes)


if __name__ == "__main__":
    main()
