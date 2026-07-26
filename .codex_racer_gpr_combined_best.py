#!/usr/bin/env python3
"""Combine independently useful exact-length integer topology changes."""

from __future__ import annotations

import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_gpr_topology_048.c").read_text(encoding="utf-8")
TARGET = ORACLE["TARGET_INSNS"]
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"
OLD = """\
        xRotationOffset = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (xRotationOffset > 0x8000) {
            xRotationOffset -= 0xFFFF;
        }
        if (xRotationOffset < -0x8000) {
            xRotationOffset += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (xRotationOffset * updateRate) >> 4;
"""


def offset_form(name: str) -> str:
    return f"""\
        {name} = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if ({name} > 0x8000) {{
            {name} -= 0xFFFF;
        }}
        if ({name} < -0x8000) {{
            {name} += 0xFFFF;
        }}
        obj->trans.rotation.x_rotation += ({name} * updateRate) >> 4;
"""


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def main() -> None:
    cases = [("baseline_best", BASE)]
    for name in ("var_v1", "var_a0", "temp_t7", "var_t9"):
        cases.append((f"spin_offset_{name}", BASE.replace(OLD, offset_form(name), 1)))

    for serial, (tag, source) in enumerate(cases):
        path = pathlib.Path(f"/tmp/codex_gpr_combined_{serial:03d}_{tag}.c")
        obj = path.with_suffix(".o")
        trace = path.with_suffix(".trace")
        path.write_text(source, encoding="utf-8")
        natural = ORACLE["evaluate"](source)
        proc = subprocess.run(
            [FORCED_RUNNER, str(path), str(obj), str(trace)],
            check=False,
            capture_output=True,
            text=True,
        )
        if proc.returncode != 0:
            print(tag, "compile", proc.returncode, proc.stderr[-500:])
            continue
        _, candidate = ORACLE["dump_object"](str(obj))
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
        print(
            tag,
            ORACLE["concise"](natural),
            "forced_insns",
            len(candidate),
            "reg_bad",
            len(reg_bad) + abs(len(TARGET) - len(candidate)),
            "fp_bad",
            len(fp_bad),
            "indices",
            ",".join(map(str, reg_bad)),
            path,
        )


if __name__ == "__main__":
    main()
