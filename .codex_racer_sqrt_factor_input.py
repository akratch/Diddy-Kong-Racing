#!/usr/bin/env python3
"""Feed sqrtf through the factor local to test call-spanning web formation."""

from __future__ import annotations

import pathlib
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = pathlib.Path("/tmp/codex_unk34_left_associative.c").read_text(
    encoding="utf-8"
)
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
OLD = """\
    var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
                    (obj->y_velocity * obj->y_velocity)) -
              2.0;
"""
SUMS = {
    "left": (
        "(obj->x_velocity * obj->x_velocity) + "
        "(obj->z_velocity * obj->z_velocity) + "
        "(obj->y_velocity * obj->y_velocity)"
    ),
    "nested_left": (
        "((obj->x_velocity * obj->x_velocity) + "
        "(obj->z_velocity * obj->z_velocity)) + "
        "(obj->y_velocity * obj->y_velocity)"
    ),
    "nested_right": (
        "(obj->x_velocity * obj->x_velocity) + "
        "((obj->z_velocity * obj->z_velocity) + "
        "(obj->y_velocity * obj->y_velocity))"
    ),
}


def forms(total: str) -> dict[str, str]:
    return {
        "factor_assign": (
            f"    var_f20 = {total};\n"
            "    var_f20 = sqrtf(var_f20) - 2.0;\n"
        ),
        "factor_compound": (
            f"    var_f20 = {total};\n"
            "    var_f20 = sqrtf(var_f20);\n"
            "    var_f20 -= 2.0;\n"
        ),
        "factor_comma": (
            f"    var_f20 = {total};\n"
            "    var_f20 = (var_f20, sqrtf(var_f20)) - 2.0;\n"
        ),
        "factor_selfarg": (
            f"    var_f20 = {total};\n"
            "    var_f20 = sqrtf(+var_f20) - 2.0;\n"
        ),
        "factor_times_one": (
            f"    var_f20 = {total};\n"
            "    var_f20 = sqrtf(var_f20 * 1.0f) - 2.0;\n"
        ),
        "factor_plus_zero": (
            f"    var_f20 = {total};\n"
            "    var_f20 = sqrtf(var_f20 + 0.0f) - 2.0;\n"
        ),
        "factor_seed_result": (
            f"    var_f20 = {total};\n"
            "    var_f2 = sqrtf(var_f20);\n"
            "    var_f20 = var_f2 - 2.0;\n"
        ),
    }


def metrics(trace: pathlib.Path) -> list[str]:
    rows: list[str] = []
    for line in trace.read_text(encoding="utf-8").splitlines():
        if "RACER-FVAR " in line and "addr=-44 " in line:
            match = re.search(
                r"bit=(\d+).*adjsave=([0-9.-]+) uses=(\d+).*"
                r"c14=([0-9.-]+) c20=([0-9.-]+)",
                line,
            )
            if match:
                rows.append("/".join(match.groups()))
        elif "FACTOR-CHOICE" in line:
            match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
            if match:
                rows.append("choice=" + "/".join(match.groups()))
    return rows


def main() -> None:
    rows = []
    serial = 0
    for sum_name, total in SUMS.items():
        for form_name, replacement in forms(total).items():
            if BASE.count(OLD) != 1:
                raise ValueError("sqrt anchor is not unique")
            source = BASE.replace(OLD, replacement, 1)
            tag = f"{serial:03d}_{sum_name}_{form_name}"
            serial += 1
            path = pathlib.Path(f"/tmp/codex_sqrt_factor_input_{tag}.c")
            obj = path.with_suffix(".o")
            trace = path.with_suffix(".trace")
            path.write_text(source, encoding="utf-8")
            result = ORACLE["evaluate"](source, keep=str(obj))
            proc = subprocess.run(
                [ANALYSIS, str(path), str(obj) + ".analysis", str(trace)],
                check=False,
                capture_output=True,
                text=True,
            )
            trace_metrics = metrics(trace) if proc.returncode == 0 else []
            rows.append((tag, result, trace_metrics, path))
    rows.sort(
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            abs(int(row[1].get("insns", 9999)) - 2625),
            int(row[1].get("norm", 9999)),
        )
    )
    for tag, result, trace_metrics, path in rows:
        print(
            tag,
            trace_metrics,
            ORACLE["concise"](result),
            result.get("fp"),
            path,
        )


if __name__ == "__main__":
    main()
