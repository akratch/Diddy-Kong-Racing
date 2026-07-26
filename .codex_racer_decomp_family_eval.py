#!/usr/bin/env python3
"""Compile fetched decomp.me family functions in the isolated racer context."""

from __future__ import annotations

import glob
import os
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
CONTEXT = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()
PREFIX = CONTEXT[: CONTEXT.index("void func_80049794")]


def main() -> None:
    for path in sorted(glob.glob("/tmp/codex_decomp_*.c")):
        tag = os.path.basename(path).removeprefix("codex_decomp_").removesuffix(".c")
        function = open(path, encoding="utf-8").read()
        source = PREFIX + function
        result = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_decomp_family_{tag}.o"
        )
        print(tag, ORACLE["concise"](result) if result.get("ok") else result)


if __name__ == "__main__":
    main()
