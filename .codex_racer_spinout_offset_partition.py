#!/usr/bin/env python3
"""Split the spinout offset web at correction branches and invite coalescing."""

from __future__ import annotations

import itertools
import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path(
    "/tmp/codex_gpr_combined_001_spin_offset_var_v1.c"
).read_text(encoding="utf-8")
TARGET = ORACLE["TARGET_INSNS"]
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"
DECL = "    s32 xRotationOffset;\n"
OLD = """\
        var_v1 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v1 > 0x8000) {
            var_v1 -= 0xFFFF;
        }
        if (var_v1 < -0x8000) {
            var_v1 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v1 * updateRate) >> 4;
"""


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def straight(first: str, second: str, third: str, copy_form: str) -> str:
    def copy(dst: str, src: str) -> str:
        if copy_form == "assign":
            return f"        {dst} = {src};\n"
        if copy_form == "plus_zero":
            return f"        {dst} = {src} + 0;\n"
        if copy_form == "or_zero":
            return f"        {dst} = {src} | 0;\n"
        if copy_form == "comma":
            return f"        {dst} = ({src}, {src});\n"
        raise ValueError(copy_form)

    return f"""\
        {first} = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if ({first} > 0x8000) {{
            {first} -= 0xFFFF;
        }}
""" + copy(second, first) + f"""\
        if ({second} < -0x8000) {{
            {second} += 0xFFFF;
        }}
""" + copy(third, second) + f"""\
        obj->trans.rotation.x_rotation += ({third} * updateRate) >> 4;
"""


def phi(first: str, second: str, third: str) -> str:
    return f"""\
        {first} = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if ({first} > 0x8000) {{
            {second} = {first} - 0xFFFF;
        }} else {{
            {second} = {first};
        }}
        if ({second} < -0x8000) {{
            {third} = {second} + 0xFFFF;
        }} else {{
            {third} = {second};
        }}
        obj->trans.rotation.x_rotation += ({third} * updateRate) >> 4;
"""


def main() -> None:
    rows: list[tuple[str, str]] = []
    existing = (
        "var_v0",
        "var_v1",
        "var_a0",
        "var_t0",
        "temp_t7",
        "pad2",
        "var_t9",
        "racerTrickType",
        "xRotationOffset",
        "zRotationOffset",
    )
    for first, second in itertools.permutations(existing, 2):
        for copy_form in ("assign", "plus_zero", "or_zero", "comma"):
            rows.append(
                (
                    f"two_{first}_{second}_{copy_form}",
                    BASE.replace(
                        OLD, straight(first, second, second, copy_form), 1
                    ),
                )
            )
    # Three-stage samples centered on the low-risk v/a temporaries.
    for first, second, third in itertools.permutations(
        ("var_v0", "var_v1", "var_a0", "temp_t7"), 3
    ):
        rows.append(
            (
                f"three_{first}_{second}_{third}",
                BASE.replace(
                    OLD, straight(first, second, third, "assign"), 1
                ),
            )
        )
        rows.append(
            (
                f"phi_{first}_{second}_{third}",
                BASE.replace(OLD, phi(first, second, third), 1),
            )
        )

    for count in (2, 3):
        names = tuple(f"spinPart{i}" for i in range(count))
        function = BASE.replace(
            DECL,
            DECL + "".join(f"    s32 {name};\n" for name in names),
            1,
        )
        third = names[-1]
        rows.append(
            (
                f"fresh_function_{count}",
                function.replace(
                    OLD,
                    straight(names[0], names[1], third, "assign"),
                    1,
                ),
            )
        )

    results = []
    for serial, (tag, source) in enumerate(rows):
        path = pathlib.Path(f"/tmp/codex_spin_partition_{serial:03d}_{tag}.c")
        obj = path.with_suffix(".o")
        trace = path.with_suffix(".trace")
        path.write_text(source, encoding="utf-8")
        proc = subprocess.run(
            [FORCED_RUNNER, str(path), str(obj), str(trace)],
            check=False,
            capture_output=True,
            text=True,
        )
        if proc.returncode != 0:
            results.append((9999, 9999, tag, "compile", path))
            continue
        _, candidate = ORACLE["dump_object"](str(obj))
        reg_bad = [
            index
            for index, (expected, actual) in enumerate(zip(TARGET, candidate))
            if registers(expected[1]) != registers(actual[1])
        ]
        spin_bad = [index for index in reg_bad if 1160 <= index <= 1210]
        total = len(reg_bad) + abs(len(TARGET) - len(candidate))
        results.append(
            (
                total,
                len(spin_bad),
                tag,
                f"insns={len(candidate)} spin={spin_bad}",
                path,
            )
        )
    for total, spin_count, tag, detail, path in sorted(results):
        print(tag, "reg_bad", total, "spin_bad", spin_count, detail, path)


if __name__ == "__main__":
    main()
