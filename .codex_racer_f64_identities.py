#!/usr/bin/env python3
"""Tune retained f64 web costs with optimizer-erased identity uses."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE_PATH = "/tmp/codex_f64_d0123_d0d1d2d3.c"

IDENTITIES = {
    "expr": "{v};",
    "void": "(void) {v};",
    "self": "{v} = {v};",
    "plus": "{v} = +{v};",
    "comma": "{v} = ({v}, {v});",
    "mul1": "{v} = {v} * 1.0;",
    "div1": "{v} = {v} / 1.0;",
    "negneg": "{v} = -(-{v});",
    "addzero": "{v} = {v} + 0.0;",
    "subzero": "{v} = {v} - 0.0;",
}

ANCHORS = {
    "d0": "        d0 = racer->velocity * 0.05;\n",
    "d1": "        d1 = racer->forwardVel + d0;\n",
    "d2": "        d2 = d1 * 0.125;\n",
}


def make(identity: str, variables: tuple[str, ...], count: int) -> str:
    source = open(BASE_PATH, encoding="utf-8").read()
    for variable in variables:
        anchor = ANCHORS[variable]
        lines = "".join(
            f"        {IDENTITIES[identity].format(v=variable)}\n"
            for _ in range(count)
        )
        if source.count(anchor) != 1:
            raise ValueError(f"anchor not unique: {anchor!r}")
        source = source.replace(anchor, anchor + lines, 1)
    return source


def main() -> None:
    rows = []
    for identity in IDENTITIES:
        for size in (1, 2, 3):
            for variables in itertools.combinations(("d0", "d1", "d2"), size):
                for count in (1, 2, 4, 8):
                    tag = f"{identity}_{''.join(variables)}_{count}"
                    source = make(identity, variables, count)
                    result = ORACLE["evaluate"](
                        source, keep=f"/tmp/codex_f64ident_{tag}.o"
                    )
                    rows.append((tag, result))
                    if (
                        result.get("f20_insns")
                        or result.get("f18", 0) > 100
                        or result.get("insns") != 2630
                    ):
                        with open(
                            f"/tmp/codex_f64ident_{tag}.c",
                            "w",
                            encoding="utf-8",
                        ) as output:
                            output.write(source)
                        print(tag, ORACLE["concise"](result))
    print("tested", len(rows))


if __name__ == "__main__":
    main()
