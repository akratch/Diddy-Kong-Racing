#!/usr/bin/env python3
"""Probe optimizer-erased spEC uses as a global-color priority lever."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()

ANCHORS = (
    "        spEC = racer->velocity * racer->velocity;\n",
    "            spEC = -spEC;\n",
    "            spEC = racer->velocity * 0.058823529411764705 * 1.5;\n",
    "        spEC = obj->z_velocity;\n",
    "            spEC += racer->unk120 * 0.5;\n",
    "                spEC *= 0.65;\n",
    "                spEC = 0.0f;\n",
    "            spEC += racer->unk88;\n",
    "        spEC = (obj->trans.z_position - spE0 - D_8011D54C) * var_f0;\n",
)

IDENTITIES = {
    "self": "spEC = spEC;",
    "expr": "spEC;",
    "void": "(void) spEC;",
    "plus": "spEC = +spEC;",
    "comma": "spEC = (spEC, spEC);",
    "addzero": "spEC = spEC + 0.0f;",
    "negneg": "spEC = -(-spEC);",
}


def make(identity: str, indices: tuple[int, ...], count: int) -> str:
    source = BASE
    for index in indices:
        anchor = ANCHORS[index]
        indent = anchor[: len(anchor) - len(anchor.lstrip())]
        addition = "".join(
            indent + IDENTITIES[identity] + "\n" for _ in range(count)
        )
        if source.count(anchor) != 1:
            raise ValueError(f"anchor is not unique: {anchor!r}")
        source = source.replace(anchor, anchor + addition, 1)
    return source


def main() -> None:
    groups = [(index,) for index in range(len(ANCHORS))]
    groups += [
        tuple(range(3)),
        tuple(range(3, 9)),
        tuple(range(9)),
        (0, 2, 3, 8),
        (3, 4, 5, 6, 7, 8),
    ]
    for identity in IDENTITIES:
        for indices in groups:
            for count in (1, 2, 4):
                tag = f"{identity}_{''.join(map(str, indices))}_{count}"
                source = make(identity, indices, count)
                result = ORACLE["evaluate"](
                    source, keep=f"/tmp/codex_spECcost_{tag}.o"
                )
                if (
                    result.get("f20_insns") != 69
                    or result.get("f18") != 35
                    or result.get("insns") != 2630
                ):
                    with open(f"/tmp/codex_spECcost_{tag}.c", "w", encoding="utf-8") as output:
                        output.write(source)
                    print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
