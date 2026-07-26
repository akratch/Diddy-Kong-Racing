#!/usr/bin/env python3
"""Probe coalesced spEC round trips on the natural f64 promotion mechanism."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()

ANCHORS = (
    "        spEC = racer->velocity * racer->velocity;\n",
    "            spEC = racer->velocity * 0.058823529411764705 * 1.5;\n",
    "        spEC = obj->z_velocity;\n",
    "        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&\n",
    "        spEC = (obj->trans.z_position - spE0 - D_8011D54C) * var_f0;\n",
    "    obj->z_velocity = spEC;\n",
)

FORMS = {
    "round": "{h} = spEC;\n{i}spEC = {h};",
    "chain": "spEC = {h} = spEC;",
    "comma": "spEC = ({h} = spEC, {h});",
    "selfchain": "{h} = ({h} = spEC);",
}


def make(host: str, form: str, indices: tuple[int, ...]) -> str:
    source = BASE
    source = source.replace(
        "    Object_Boost *boostObj;\n",
        f"    Object_Boost *boostObj;\n    f32 {host};\n",
        1,
    )
    for index in indices:
        anchor = ANCHORS[index]
        indent = anchor[: len(anchor) - len(anchor.lstrip())]
        statement = FORMS[form].format(h=host, i=indent)
        if index in (3, 5):
            addition = indent + statement + "\n"
            source = source.replace(anchor, addition + anchor, 1)
        else:
            addition = indent + statement + "\n"
            source = source.replace(anchor, anchor + addition, 1)
    return source


def main() -> None:
    groups = [(index,) for index in range(len(ANCHORS))]
    groups += [tuple(range(3)), tuple(range(3, 6)), tuple(range(6)), (0, 1, 4)]
    for host in ("spCC", "var_f6", "segmentXVelocity"):
        for form in FORMS:
            for indices in groups:
                tag = f"{host}_{form}_{''.join(map(str, indices))}"
                source = make(host, form, indices)
                result = ORACLE["evaluate"](
                    source, keep=f"/tmp/codex_spECcopy_{tag}.o"
                )
                if (
                    result.get("f20_insns") != 69
                    or result.get("f18") != 35
                    or result.get("insns") != 2630
                    or result.get("sha1") != "dfb7847254a6"
                ):
                    with open(f"/tmp/codex_spECcopy_{tag}.c", "w", encoding="utf-8") as output:
                        output.write(source)
                    print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
