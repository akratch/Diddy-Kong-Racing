#!/usr/bin/env python3
"""Put erased var_f20 reads into the two real loops in plane physics.

The allocator assigns loop bodies a frequency of ten.  These cases test
whether an instruction-neutral fake read can therefore make the long-lived
factor's caller-save cost exceed the one-time f20 save/restore cost.
"""

from __future__ import annotations

import concurrent.futures
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"

WHEEL_LOOP = """\
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
        }
"""

WAVE_LOOP = """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}
"""

ZEROS = {
    "gt_mul": "((var_f20 > 0.0f) * 0)",
    "lt_mul": "((var_f20 < 0.0f) * 0)",
    "eq_mul": "((var_f20 == 0.0f) * 0)",
    "ne_mul": "((var_f20 != 0.0f) * 0)",
    "gt_and": "((var_f20 > 0.0f) & 0)",
    "gt_ternary": "((var_f20 > 0.0f) ? 0 : 0)",
    "gt_comma": "((var_f20 > 0.0f), 0)",
}


def wheel(form: str, zero: str) -> str:
    if form == "init":
        return WHEEL_LOOP.replace("var_t0 = 0", f"var_t0 = {zero}")
    if form == "condition":
        return WHEEL_LOOP.replace("var_t0 < 4", f"var_t0 < 4 + {zero}")
    if form == "increment":
        return WHEEL_LOOP.replace("var_t0++", f"var_t0 += 1 + {zero}")
    if form == "surface_none":
        return WHEEL_LOOP.replace(
            "racer->wheel_surfaces[var_t0] != SURFACE_NONE",
            f"racer->wheel_surfaces[var_t0] != SURFACE_NONE + {zero}",
        )
    if form == "surface_compare":
        return WHEEL_LOOP.replace(
            "i < racer->wheel_surfaces[var_t0]",
            f"i < racer->wheel_surfaces[var_t0] + {zero}",
        )
    if form == "assignment":
        return WHEEL_LOOP.replace(
            "i = racer->wheel_surfaces[var_t0];",
            f"i = racer->wheel_surfaces[var_t0] + {zero};",
        )
    if form == "body_pre":
        return WHEEL_LOOP.replace(
            "            if (",
            f"            i += {zero};\n            if (",
        )
    if form == "body_post":
        return WHEEL_LOOP.replace(
            "            }\n        }",
            f"            }}\n            i += {zero};\n        }}",
        )
    raise ValueError(form)


def wave(form: str, zero: str) -> str:
    if form == "init":
        return WAVE_LOOP.replace(
            "gRacerWaveCount - 1", f"gRacerWaveCount - 1 + {zero}"
        )
    if form == "condition_a":
        return WAVE_LOOP.replace("var_a0 >= 0", f"var_a0 >= {zero}")
    if form == "condition_b":
        return WAVE_LOOP.replace(
            "obj->trans.y_position + 5",
            f"obj->trans.y_position + 5 + {zero}",
        )
    if form == "increment":
        return WAVE_LOOP.replace("var_a0--", f"var_a0 -= 1 + {zero}")
    if form == "body":
        return WAVE_LOOP.replace(
            "var_a0--) {}", f"var_a0--) {{ var_a0 += {zero}; }}"
        )
    raise ValueError(form)


def make(loop: str, form: str, zero_name: str) -> str:
    zero = ZEROS[zero_name]
    if loop == "wheel":
        old = WHEEL_LOOP
        new = wheel(form, zero)
    else:
        old = WAVE_LOOP
        new = wave(form, zero)
    if BASE.count(old) != 1:
        raise ValueError((loop, BASE.count(old)))
    return BASE.replace(old, new, 1)


def evaluate(case: tuple[str, str, str]) -> tuple:
    loop, form, zero_name = case
    tag = f"{loop}_{form}_{zero_name}"
    source = make(*case)
    path = f"/tmp/codex_existing_loop_factor_fake_{tag}.c"
    trace = f"/tmp/codex_existing_loop_factor_fake_{tag}.trace"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_existing_loop_factor_fake_{tag}.o"
    )
    proc = subprocess.run(
        [
            ANALYSIS,
            path,
            f"/tmp/codex_existing_loop_factor_fake_{tag}_analysis.o",
            trace,
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    factor = "-"
    factor_row = "-"
    if proc.returncode == 0:
        with open(trace, encoding="utf-8") as input_file:
            for line in input_file:
                if "RACER-FVAR" in line and "addr=-44 " in line:
                    match = re.search(
                        r"adjsave=([0-9.-]+) uses=(\d+).*"
                        r"c14=([0-9.-]+)",
                        line,
                    )
                    if match:
                        factor_row = "/".join(match.groups())
                elif "FACTOR-CHOICE" in line:
                    match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                    if match:
                        factor = "/".join(match.groups())
    return tag, source, result, factor, factor_row, proc.returncode


def main() -> None:
    wheel_forms = (
        "init",
        "condition",
        "increment",
        "surface_none",
        "surface_compare",
        "assignment",
        "body_pre",
        "body_post",
    )
    wave_forms = ("init", "condition_a", "condition_b", "increment", "body")
    cases = [
        ("wheel", form, zero)
        for form in wheel_forms
        for zero in ZEROS
    ] + [
        ("wave", form, zero)
        for form in wave_forms
        for zero in ZEROS
    ]
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[3].startswith("30/"),
            row[2].get("mismatch", 999999),
            abs(row[2].get("insns", 9999) - 2625),
            row[2].get("norm", 9999),
            row[0],
        )
    )
    for tag, source, result, factor, factor_row, returncode in rows:
        if result.get("mismatch") == 0:
            with open(
                f"/tmp/codex_existing_loop_factor_fake_exact_{tag}.c",
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
            "row",
            factor_row,
            ORACLE["concise"](result),
            result.get("fp"),
        )
    print(
        "tested",
        len(rows),
        "factor_promoted",
        sum(row[3].startswith("30/") for row in rows),
        "exact",
        sum(row[2].get("mismatch") == 0 for row in rows),
    )


if __name__ == "__main__":
    main()
