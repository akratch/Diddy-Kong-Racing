#!/usr/bin/env python3
"""Focused integer lifetime/topology sweeps that preserve the target opcode stream."""

from __future__ import annotations

import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(encoding="utf-8")
TARGET = ORACLE["TARGET_INSNS"]
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"

WAVE_OLD = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""

WAVE_LOOP = """\
        for ({init};
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{}}

        if (var_a0 == gRacerWaveCount - 1) {{
            var_a0--;
        }}
"""

WAVE_FORMS = {"baseline": WAVE_OLD}
for name in ("var_v1", "var_v0", "temp_t7", "i", "var_t9", "pad5", "pad7", "pad2", "pad4"):
    WAVE_FORMS[f"nested_{name}"] = WAVE_LOOP.format(
        init=f"var_a0 = ({name} = gRacerWaveCount - 1)"
    )
    WAVE_FORMS[f"comma_{name}"] = WAVE_LOOP.format(
        init=f"{name} = gRacerWaveCount - 1, var_a0 = {name}"
    )
    WAVE_FORMS[f"split_{name}"] = (
        f"        {name} = gRacerWaveCount - 1;\n"
        + WAVE_LOOP.format(init=f"var_a0 = {name}")
    )
    WAVE_FORMS[f"cached_{name}"] = (
        f"        {name} = gRacerWaveCount - 1;\n"
        + WAVE_LOOP.format(init=f"var_a0 = {name}").replace(
            "if (var_a0 == gRacerWaveCount - 1)",
            f"if (var_a0 == {name})",
        )
    )

SPINOUT_OLD = """\
        xRotationOffset = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (xRotationOffset > 0x8000) {
            xRotationOffset -= 0xFFFF;
        }
        if (xRotationOffset < -0x8000) {
            xRotationOffset += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (xRotationOffset * updateRate) >> 4;
"""

SPINOUT_FORMS = {"baseline": SPINOUT_OLD}
for original in ("var_v1", "var_v0", "var_t0", "var_a0"):
    for final in ("assign", "compound"):
        statement = (
            f"obj->trans.rotation.x_rotation = {original} + "
            "((xRotationOffset * updateRate) >> 4);"
            if final == "assign"
            else "obj->trans.rotation.x_rotation += (xRotationOffset * updateRate) >> 4;"
        )
        SPINOUT_FORMS[f"{original}_{final}"] = f"""\
        {original} = obj->trans.rotation.x_rotation;
        xRotationOffset = 0xD800 - ({original} & 0xFFFF);
        if (xRotationOffset > 0x8000) {{
            xRotationOffset -= 0xFFFF;
        }}
        if (xRotationOffset < -0x8000) {{
            xRotationOffset += 0xFFFF;
        }}
        {statement}
"""

STEER_HEAD_OLD = """\
            racerSteerAngle = racer->steerAngle;
            spA1 = FALSE;
"""

STEER_AIR_OLD = """\
                var_v1 = obj->trans.rotation.x_rotation;
                xRotationOffset = 0;
                var_t0 = racerSteerAngle;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    xRotationOffset = var_v1 - 0x3000;
                    if (xRotationOffset > 0x1000) {
                        xRotationOffset = 0x1000;
                    }
                } else if (var_v1 < -0x3000) {
                    xRotationOffset = var_v1 + 0x3000;
                    if (xRotationOffset < -0x1000) {
                        xRotationOffset = -0x1000;
                    }
                    xRotationOffset = -xRotationOffset;
                }
                var_t0 *= (f32) (1.0 - ((f32) xRotationOffset / 4096));
"""

STEER_FORMS = {"baseline": (STEER_HEAD_OLD, STEER_AIR_OLD)}
for source_name in ("racerSteerAngle", "var_a0", "var_v0"):
    head = (
        STEER_HEAD_OLD
        if source_name == "racerSteerAngle"
        else f"            {source_name} = racer->steerAngle;\n            spA1 = FALSE;\n"
    )
    air = f"""\
                var_v1 = obj->trans.rotation.x_rotation;
                var_t0 = {source_name};
                {source_name} = 0;
                if (obj->trans.rotation.x_rotation > 0x3000) {{
                    {source_name} = var_v1 - 0x3000;
                    if ({source_name} > 0x1000) {{
                        {source_name} = 0x1000;
                    }}
                }} else if (var_v1 < -0x3000) {{
                    {source_name} = var_v1 + 0x3000;
                    if ({source_name} < -0x1000) {{
                        {source_name} = -0x1000;
                    }}
                    {source_name} = -{source_name};
                }}
                var_t0 *= (f32) (1.0 - ((f32) {source_name} / 4096));
"""
    STEER_FORMS[f"reuse_{source_name}"] = (head, air)

ROTATION_OLD = """\
            if (!(gCurrentRacerInput & R_TRIG)) {
                obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }
"""

ROTATION_NEW = """\
            if (!(gCurrentRacerInput & R_TRIG)) {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 19 * updateRate) >> 1;
            } else {
                var_v1 = obj->trans.rotation.x_rotation;
                obj->trans.rotation.x_rotation = var_v1 - ((var_v1 * updateRate) >> 4);
                obj->trans.rotation.x_rotation -= ((var_t0 >> 1) * 30 * updateRate) >> 1;
            }
"""


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def metrics(obj: pathlib.Path) -> dict[str, object]:
    _, candidate = ORACLE["dump_object"](str(obj))
    if len(candidate) != len(TARGET):
        return {
            "insns": len(candidate),
            "regs": None,
            "fp": None,
        }
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    fp_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if re.findall(r"\$f\d+", expected[1])
        != re.findall(r"\$f\d+", actual[1])
    ]
    return {
        "insns": len(candidate),
        "regs": len(reg_bad),
        "fp": len(fp_bad),
        "reg_bad": reg_bad,
    }


def compile_case(tag: str, source: str, serial: int) -> tuple[dict[str, object], dict[str, object], pathlib.Path]:
    source_path = pathlib.Path(f"/tmp/codex_gpr_topology_{serial:03d}.c")
    obj_path = pathlib.Path(f"/tmp/codex_gpr_topology_{serial:03d}.o")
    source_path.write_text(source, encoding="utf-8")
    natural = ORACLE["evaluate"](source)
    proc = subprocess.run(
        [FORCED_RUNNER, str(source_path), str(obj_path), str(obj_path) + ".trace"],
        check=False,
        capture_output=True,
        text=True,
    )
    forced = metrics(obj_path) if proc.returncode == 0 else {"error": proc.stderr[-800:]}
    print(tag, ORACLE["concise"](natural), {k: v for k, v in forced.items() if k != "reg_bad"})
    return natural, forced, source_path


def main() -> None:
    cases: list[tuple[str, str]] = []
    for tag, replacement in WAVE_FORMS.items():
        if tag != "baseline":
            cases.append((f"wave:{tag}", BASE.replace(WAVE_OLD, replacement, 1)))
    for tag, replacement in SPINOUT_FORMS.items():
        if tag != "baseline":
            cases.append((f"spinout:{tag}", BASE.replace(SPINOUT_OLD, replacement, 1)))
    for tag, (head, air) in STEER_FORMS.items():
        if tag != "baseline":
            cases.append((
                f"steer:{tag}",
                BASE.replace(STEER_HEAD_OLD, head, 1).replace(STEER_AIR_OLD, air, 1),
            ))
    cases.append(("rotation:explicit", BASE.replace(ROTATION_OLD, ROTATION_NEW, 1)))

    reuse_head, reuse_air = STEER_FORMS["reuse_racerSteerAngle"]
    reuse_source = BASE.replace(STEER_HEAD_OLD, reuse_head, 1).replace(STEER_AIR_OLD, reuse_air, 1)
    cases.append((
        "steer:reuse+rotation",
        reuse_source.replace(ROTATION_OLD, ROTATION_NEW, 1),
    ))
    for tag, expression in {
        "positive": "+racerSteerAngle",
        "add_zero": "racerSteerAngle + 0",
        "zero_add": "0 + racerSteerAngle",
        "sub_zero": "racerSteerAngle - 0",
        "or_zero": "racerSteerAngle | 0",
        "xor_zero": "racerSteerAngle ^ 0",
        "comma": "(var_v1, racerSteerAngle)",
        "self_assign": "(racerSteerAngle = racerSteerAngle)",
        "compound_add": "(racerSteerAngle += 0)",
        "compound_or": "(racerSteerAngle |= 0)",
    }.items():
        cases.append((
            f"steer:reuse_{tag}",
            reuse_source.replace(
                "                var_t0 = racerSteerAngle;\n",
                f"                var_t0 = {expression};\n",
                1,
            ),
        ))

    duplicate_air = reuse_air.replace(
        "                var_t0 = racerSteerAngle;\n"
        "                racerSteerAngle = 0;\n"
        "                if (obj->trans.rotation.x_rotation > 0x3000) {\n",
        "                if (var_v1 > 0x3000) {\n"
        "                    var_t0 = racerSteerAngle;\n",
        1,
    ).replace(
        "                } else if (var_v1 < -0x3000) {\n",
        "                } else if (var_v1 < -0x3000) {\n"
        "                    var_t0 = racerSteerAngle;\n",
        1,
    ).replace(
        "                    racerSteerAngle = -racerSteerAngle;\n"
        "                }\n"
        "                var_t0 *= (f32)",
        "                    racerSteerAngle = -racerSteerAngle;\n"
        "                } else {\n"
        "                    var_t0 = racerSteerAngle;\n"
        "                    racerSteerAngle = 0;\n"
        "                }\n"
        "                var_t0 *= (f32)",
        1,
    )
    cases.append((
        "steer:reuse_duplicate_branches",
        BASE.replace(STEER_HEAD_OLD, reuse_head, 1).replace(STEER_AIR_OLD, duplicate_air, 1),
    ))

    results = []
    for serial, (tag, source) in enumerate(cases):
        natural, forced, source_path = compile_case(tag, source, serial)
        results.append((forced.get("regs") if forced.get("regs") is not None else 100000, tag, natural, forced, source_path))
    print("\nBEST EXACT-LENGTH CASES")
    for _, tag, natural, forced, source_path in sorted(results)[:20]:
        print(tag, ORACLE["concise"](natural), forced, source_path)


if __name__ == "__main__":
    main()
