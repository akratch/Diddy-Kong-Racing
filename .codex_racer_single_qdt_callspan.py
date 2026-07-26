#!/usr/bin/env python3
"""Test whether one noninterfering double web can directly prepay f20."""

from __future__ import annotations

import itertools
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
ANALYSIS = "/tmp/codex_run_analysis_natural.sh"
DECL_ANCHOR = "    Object_Boost *boostObj;\n"
STARTS = {
    "post_wave": "    D_8011D550 = 0;\n",
    "pre_handlers": "    handle_racer_items(obj, racer, updateRate);\n",
    "pre_matrix": "    mtxf_from_transform((MtxF *) &sp60, &gCurrentRacerTransform);\n",
}
ENDS = {
    "post_handlers": "    if (gCurrentRacerInput & A_BUTTON) {\n",
    "post_matrix": "    if (racer->approachTarget == NULL) {\n",
    "pre_factor": "    var_v0 = racer->playerIndex;\n",
}


def make(start: str, end: str, weighted: bool) -> str:
    source = BASE.replace(DECL_ANCHOR, DECL_ANCHOR + "    f64 prepay_q;\n", 1)
    start_anchor = STARTS[start]
    source = source.replace(
        start_anchor,
        "    prepay_q = (f64) gCurrentCourseHeight;\n" + start_anchor,
        1,
    )
    if weighted:
        loop_anchor = """\
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}
"""
        loop_body = """\
        {
            prepay_q = (f64) gRacerCurrentWave[var_a0]->waveHeight;
            var_a0 += (prepay_q > 0.0) * 0;
            if (var_a0 != 0) {
                if (gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position) {
                    var_a0 += (prepay_q > 0.0) * 0;
                } else {
                    var_a0 -= (prepay_q > 0.0) * 0;
                }
            } else {
                var_a0 += (prepay_q > 0.0) * 0;
            }
            var_a0 += (prepay_q > 0.0) * 0;
        }
"""
        source = source.replace(loop_anchor, loop_anchor[:-3] + loop_body, 1)
    end_anchor = ENDS[end]
    source = source.replace(
        end_anchor,
        "    gCurrentCarSteerVel += (prepay_q > 0.0) * 0;\n" + end_anchor,
        1,
    )
    return source


def main() -> None:
    cases = itertools.product(STARTS, ENDS, (False, True))
    for start, end, weighted in cases:
        tag = f"{start}_{end}_{'weighted' if weighted else 'plain'}"
        source = make(start, end, weighted)
        source_path = f"/tmp/codex_single_qdt_callspan_{tag}.c"
        trace_path = f"/tmp/codex_single_qdt_callspan_{tag}.trace"
        with open(source_path, "w", encoding="utf-8") as output:
            output.write(source)
        result = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_single_qdt_callspan_{tag}.o"
        )
        proc = subprocess.run(
            [
                ANALYSIS,
                source_path,
                f"/tmp/codex_single_qdt_callspan_{tag}_analysis.o",
                trace_path,
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        qdt = []
        factor = "-"
        if proc.returncode == 0:
            with open(trace_path, encoding="utf-8") as input_file:
                for line in input_file:
                    if "RACER-COLOR " in line and " size=8" in line:
                        match = re.search(
                            r"bit=(\d+).*reg=(\d+).*adjsave=([0-9.-]+)"
                            r".*uses=(\d+).*cost=([0-9.-]+).*addr=(-?\d+)",
                            line,
                        )
                        if match:
                            qdt.append("/".join(match.groups()))
                    elif "FACTOR-CHOICE" in line:
                        match = re.search(r"reg=(\d+) cost=([0-9.-]+)", line)
                        if match:
                            factor = "/".join(match.groups())
        print(
            tag,
            "rc",
            proc.returncode,
            "factor",
            factor,
            "qdt",
            ",".join(qdt) or "-",
            ORACLE["concise"](result),
        )


if __name__ == "__main__":
    main()
