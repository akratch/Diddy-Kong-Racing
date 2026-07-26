#!/usr/bin/env python3
"""Build and evaluate archived decomp.me racer source snapshots locally."""

from __future__ import annotations

import json
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
PREAMBLE = BASE[: BASE.index("void func_80049794")]


def main() -> None:
    for slug in ("SlvtN", "Pfb7d", "ZIUaE"):
        with open(f"/tmp/codex_decomp_{slug}.json", encoding="utf-8") as input_file:
            scratch = json.load(input_file)
        source = PREAMBLE + scratch["source_code"] + "\n"
        path = f"/tmp/codex_archive_{slug}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_archive_{slug}_natural.o"
        )
        print(slug, "natural", ORACLE["concise"](natural), natural.get("fp"))
        if not natural.get("ok"):
            continue
        for runner, label in (
            ("/tmp/codex_run_analysis_natural.sh", "analysis"),
            ("/tmp/codex_run_analysis.sh", "forced"),
        ):
            trace = f"/tmp/codex_archive_{slug}_{label}.trace"
            proc = subprocess.run(
                [
                    runner,
                    path,
                    f"/tmp/codex_archive_{slug}_{label}.o",
                    trace,
                ],
                check=False,
                capture_output=True,
                text=True,
            )
            print(slug, label, "rc", proc.returncode, "trace", trace)


if __name__ == "__main__":
    main()
