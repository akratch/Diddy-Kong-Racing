#!/usr/bin/env python3
"""Lower f64 web priority with zero-opcode basic-block separators."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()
ANCHORS = {
    "d0": "        d0 = racer->velocity * 0.05;\n",
    "d1": "        d1 = racer->forwardVel + d0;\n",
    "d2": "        d2 = d1 * 0.125;\n",
}


def make(kind: str, variables: tuple[str, ...], count: int) -> str:
    source = BASE
    serial = 0
    for variable in variables:
        anchor = ANCHORS[variable]
        lines = ""
        for _ in range(count):
            serial += 1
            label = f"codex_f64_label_{serial}"
            if kind == "plain":
                lines += f"        {label}:\n"
            elif kind == "goto":
                lines += f"        goto {label};\n        {label}:\n"
            elif kind == "ifzero":
                lines += f"        if (0) goto {label};\n        {label}:\n"
            else:
                raise ValueError(kind)
        source = source.replace(anchor, anchor + lines, 1)
    return source


def main() -> None:
    groups = (("d0",), ("d1",), ("d2",), ("d0", "d1"),
              ("d0", "d2"), ("d1", "d2"), ("d0", "d1", "d2"))
    for kind in ("plain", "goto", "ifzero"):
        for variables in groups:
            for count in (1, 2, 4, 8, 16):
                tag = f"{kind}_{''.join(variables)}_{count}"
                source = make(kind, variables, count)
                result = ORACLE["evaluate"](
                    source, keep=f"/tmp/codex_f64label_{tag}.o"
                )
                if (
                    result.get("f20_insns") != 69
                    or result.get("f18") != 35
                    or result.get("insns") != 2630
                    or result.get("sha1") != "dfb7847254a6"
                ):
                    with open(f"/tmp/codex_f64label_{tag}.c", "w", encoding="utf-8") as output:
                        output.write(source)
                    print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
