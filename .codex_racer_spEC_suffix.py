#!/usr/bin/env python3
"""Split the long spEC web immediately after the decisive final drag node."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_f64_d0123_d0d1d2d3.c", encoding="utf-8").read()

MARKERS = {
    "after_forward": "        racer->forwardVel = d3;\n",
    "after_approach": """\
    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
""",
    "before_late": "    if (racer->unk1D2 != 0) {\n",
}


def make(host: str, marker_name: str, form: str) -> str:
    source = BASE.replace(
        "    Object_Boost *boostObj;\n",
        f"    Object_Boost *boostObj;\n    f32 {host};\n",
        1,
    )
    marker = MARKERS[marker_name]
    if source.count(marker) != 1:
        raise ValueError(f"marker is not unique: {marker_name}")
    before, after = source.split(marker, 1)
    after = after.replace("spEC", host)
    if form == "copy":
        bridge = f"        {host} = spEC;\n"
    elif form == "chain":
        bridge = f"        {host} = (spEC = spEC);\n"
    elif form == "reverse":
        bridge = f"        spEC = ({host} = spEC);\n"
    else:
        raise ValueError(form)
    return before + marker + bridge + after


def main() -> None:
    for host in ("spCC", "var_f6", "segmentXVelocity"):
        for marker_name in MARKERS:
            for form in ("copy", "chain", "reverse"):
                tag = f"{host}_{marker_name}_{form}"
                source = make(host, marker_name, form)
                result = ORACLE["evaluate"](
                    source, keep=f"/tmp/codex_spECsuffix_{tag}.o"
                )
                with open(f"/tmp/codex_spECsuffix_{tag}.c", "w", encoding="utf-8") as output:
                    output.write(source)
                print(tag, ORACLE["concise"](result), result.get("fp"))


if __name__ == "__main__":
    main()
