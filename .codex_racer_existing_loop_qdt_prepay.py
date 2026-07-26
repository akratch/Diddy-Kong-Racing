#!/usr/bin/env python3
"""Try to prepay f20 with short Qdt webs in an existing pre-factor loop."""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
ANCHOR = """\
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
        }
"""
VALUES = (
    "obj->x_velocity",
    "obj->y_velocity",
    "obj->z_velocity",
    "racer->velocity",
    "racer->lateral_velocity",
    "racer->forwardVel",
    "racer->ox1",
    "racer->oy1",
)


def zero_expression(names: list[str], form: str) -> str:
    if form == "compare":
        return "(" + " + ".join(f"({name} > 0.0)" for name in names) + ") * 0"
    if form == "sum_compare":
        return "((" + " + ".join(names) + ") > 0.0) * 0"
    if form == "self_sub":
        body = " + ".join(names)
        return f"(s32) (({body}) - ({body}))"
    if form == "product_zero":
        body = " + ".join(names)
        return f"(s32) (({body}) * 0.0)"
    raise ValueError(form)


def make(
    count: int,
    value_form: str,
    zero_form: str,
    scope: str,
    use_shape: str,
) -> str:
    names = [f"loop_q{index}" for index in range(count)]
    declarations = "".join(f"            f64 {name};\n" for name in names)
    definitions = []
    for index, name in enumerate(names):
        value = VALUES[index]
        if value_form == "raw":
            rhs = f"(f64) {value}"
        elif value_form == "square":
            rhs = f"(f64) ({value} * {value})"
        elif value_form == "int":
            rhs = "(f64) racer->wheel_surfaces[var_t0]"
        else:
            raise ValueError(value_form)
        definitions.append(f"            {name} = {rhs};\n")
    zero = zero_expression(names, zero_form)
    old_body = """\
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
"""
    if use_shape == "single":
        use_body = old_body + f"            i += {zero};\n"
    elif use_shape == "both_sides":
        use_body = (
            f"            i += {zero};\n"
            + old_body
            + f"            i += {zero};\n"
        )
    elif use_shape == "branch":
        use_body = (
            f"            i += {zero};\n"
            "            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && "
            "i < racer->wheel_surfaces[var_t0]) {\n"
            f"                i = racer->wheel_surfaces[var_t0] + {zero};\n"
            "            } else {\n"
            f"                i += {zero};\n"
            "            }\n"
            f"            i += {zero};\n"
        )
    elif use_shape == "branch_twice":
        use_body = (
            f"            i += {zero};\n"
            "            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && "
            "i < racer->wheel_surfaces[var_t0]) {\n"
            f"                i = racer->wheel_surfaces[var_t0] + {zero};\n"
            "            } else {\n"
            f"                i += {zero};\n"
            "            }\n"
            "            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE) {\n"
            f"                i += {zero};\n"
            "            } else {\n"
            f"                i -= {zero};\n"
            "            }\n"
            f"            i += {zero};\n"
        )
    elif use_shape == "nested":
        use_body = (
            f"            i += {zero};\n"
            "            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE) {\n"
            "                if (i < racer->wheel_surfaces[var_t0]) {\n"
            f"                    i = racer->wheel_surfaces[var_t0] + {zero};\n"
            "                } else {\n"
            f"                    i += {zero};\n"
            "                }\n"
            "            } else {\n"
            f"                i -= {zero};\n"
            "            }\n"
            f"            i += {zero};\n"
        )
    elif use_shape == "loop_control":
        use_body = (
            old_body
            + f"            i += {zero};\n"
            + f"            var_t0 += {zero};\n"
        )
    else:
        raise ValueError(use_shape)
    new_body = (
        ("        {\n" + declarations if scope == "loop_block" else "")
        + "".join(definitions)
        + use_body
        + ("        }\n" if scope == "loop_block" else "")
    )
    replacement = ANCHOR.replace(old_body, new_body)
    source = BASE
    if scope == "function":
        function_declarations = "".join(
            f"    f64 {name};\n" for name in names
        )
        source = source.replace(
            "    Object_Boost *boostObj;\n",
            "    Object_Boost *boostObj;\n" + function_declarations,
            1,
        )
    if source.count(ANCHOR) != 1:
        raise ValueError(source.count(ANCHOR))
    return source.replace(ANCHOR, replacement, 1)


def evaluate(case: tuple[int, str, str, str, str]) -> tuple:
    count, value_form, zero_form, scope, use_shape = case
    tag = f"n{count}_{value_form}_{zero_form}_{scope}_{use_shape}"
    source = make(*case)
    path = f"/tmp/codex_existing_loop_qdt_prepay_{tag}.c"
    trace = f"/tmp/codex_existing_loop_qdt_prepay_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source,
        keep=f"/tmp/codex_existing_loop_qdt_prepay_{tag}.o",
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_existing_loop_qdt_prepay_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    qdt_colors: list[tuple[int, int, float, int]] = []
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
                elif "RACER-COLOR " in line and " size=8" in line:
                    match = re.search(
                        r"bit=(\d+).*reg=(\d+).*adjsave=([0-9.-]+).*uses=(\d+)",
                        line,
                    )
                    if match:
                        qdt_colors.append(
                            (
                                int(match.group(1)),
                                int(match.group(2)),
                                float(match.group(3)),
                                int(match.group(4)),
                            )
                        )
    return tag, source, result, factor, qdt_colors, proc.returncode


def main() -> None:
    cases = [
        (count, value_form, zero_form, scope, use_shape)
        for count in range(5, 9)
        for value_form in ("int",)
        for zero_form in ("compare", "sum_compare")
        for scope in ("function", "loop_block")
        for use_shape in ("branch_twice", "nested")
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not any(reg == 30 for _, reg, _, _ in row[4]),
            not row[3].startswith("30/"),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
        )
    )
    for tag, source, result, factor, colors, returncode in rows:
        if factor.startswith("30/") or any(reg == 30 for _, reg, _, _ in colors):
            with open(
                f"/tmp/codex_existing_loop_qdt_prepay_promising_{tag}.c",
                "w",
                encoding="utf-8",
            ) as output:
                output.write(source)
        print(
            tag,
            "rc",
            returncode,
            "factor",
            factor,
            "qdt",
            ",".join(
                f"{bit}/{reg}/{save:g}/{uses}"
                for bit, reg, save, uses in colors
            )
            or "-",
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].startswith("30/") for row in rows),
        "qdt_f20",
        sum(any(reg == 30 for _, reg, _, _ in row[4]) for row in rows),
    )


if __name__ == "__main__":
    main()
