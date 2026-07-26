#!/usr/bin/env python3
"""Probe wide/aggregate scalar types for a direct f20 allocation route."""

from __future__ import annotations

import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
DECL_ANCHOR = "    Object_Boost *boostObj;\n"
LOOP_ANCHOR = """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}
"""


TYPE_FORMS = {
    "f64": ("f64", "0.0"),
    "long_double": ("long double", "0.0L"),
    "complex_float": ("complex float", "0.0f"),
    "complex_double": ("complex double", "0.0"),
    "underscore_complex_float": ("_Complex float", "0.0f"),
    "underscore_complex_double": ("_Complex double", "0.0"),
    "dunder_complex_float": ("__complex__ float", "0.0f"),
    "dunder_complex_double": ("__complex__ double", "0.0"),
}


def make(tag: str) -> str:
    type_name, zero = TYPE_FORMS[tag]
    declaration = f"    {type_name} wave_q;\n"
    body = f"""\
        {{
            wave_q = ({type_name}) gRacerCurrentWave[var_a0]->waveHeight;
            var_a0 += (wave_q > {zero}) * 0;
            if (var_a0 != 0) {{
                if (gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position) {{
                    var_a0 += (wave_q > {zero}) * 0;
                }} else {{
                    var_a0 -= (wave_q > {zero}) * 0;
                }}
            }} else {{
                var_a0 += (wave_q > {zero}) * 0;
            }}
            var_a0 += (wave_q > {zero}) * 0;
        }}
"""
    source = BASE.replace(DECL_ANCHOR, DECL_ANCHOR + declaration, 1)
    return source.replace(LOOP_ANCHOR, LOOP_ANCHOR[:-3] + body, 1)


def main() -> None:
    for tag in TYPE_FORMS:
        source = make(tag)
        source_path = f"/tmp/codex_direct_f20_typeclass_{tag}.c"
        object_path = f"/tmp/codex_direct_f20_typeclass_{tag}.o"
        trace_path = f"/tmp/codex_direct_f20_typeclass_{tag}.trace"
        with open(source_path, "w", encoding="utf-8") as output:
            output.write(source)
        result = ORACLE["evaluate"](source, keep=object_path)
        proc = subprocess.run(
            [
                ANALYSIS,
                source_path,
                f"/tmp/codex_direct_f20_typeclass_{tag}_analysis.o",
                trace_path,
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        colors = []
        factor = "-"
        if proc.returncode == 0:
            with open(trace_path, encoding="utf-8") as input_file:
                for line in input_file:
                    if "RACER-COLOR " in line and " type=3 " in line:
                        match = re.search(
                            r"bit=(\d+).*reg=(\d+).*adjsave=([0-9.-]+)"
                            r".*uses=(\d+).*addr=(-?\d+).*size=(\d+)",
                            line,
                        )
                        if match:
                            colors.append("/".join(match.groups()))
                    elif "FACTOR-CHOICE" in line:
                        match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                        if match:
                            factor = "/".join(match.groups())
        print(
            tag,
            "analysis_rc",
            proc.returncode,
            "factor",
            factor,
            "colors",
            ",".join(colors) or "-",
            ORACLE["concise"](result),
            result.get("stderr", ""),
        )


if __name__ == "__main__":
    main()
