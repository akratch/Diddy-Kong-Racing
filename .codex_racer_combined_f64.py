#!/usr/bin/env python3
"""Cross earlier stick-scaling and final forwardVel retained-f64 webs."""

from __future__ import annotations

import itertools
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()

OLD_STICK = "        gCurrentStickY = (1.0 - var_f20) * ((f32) gCurrentStickY);\n"
OLD_FORWARD = """\
        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
"""

STICK_FORMS = {
    "s0": """\
        s0 = (f32) gCurrentStickY;
        gCurrentStickY = (1.0 - var_f20) * s0;
""",
    "s01a": """\
        s0 = (f32) gCurrentStickY;
        s1 = 1.0 - var_f20;
        gCurrentStickY = s1 * s0;
""",
    "s01b": """\
        s0 = 1.0 - var_f20;
        s1 = (f32) gCurrentStickY;
        gCurrentStickY = s0 * s1;
""",
    "s012a": """\
        s0 = (f32) gCurrentStickY;
        s1 = 1.0 - var_f20;
        s2 = s1 * s0;
        gCurrentStickY = s2;
""",
    "s012b": """\
        s0 = 1.0 - var_f20;
        s1 = (f32) gCurrentStickY;
        s2 = s0 * s1;
        gCurrentStickY = s2;
""",
    "s0123a": """\
        s0 = (f32) gCurrentStickY;
        s1 = 1.0 - var_f20;
        s2 = s1 * s0;
        s3 = s2;
        gCurrentStickY = s3;
""",
    "s0123b": """\
        s0 = 1.0 - var_f20;
        s1 = (f32) gCurrentStickY;
        s2 = s0 * s1;
        s3 = s2;
        gCurrentStickY = s3;
""",
}

FORWARD_FORMS = {
    "none": OLD_FORWARD,
    "d0": """\
        d0 = racer->velocity * 0.05;
        racer->forwardVel -= (racer->forwardVel + d0) * 0.125;
""",
    "d01": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        racer->forwardVel -= d1 * 0.125;
""",
    "d012": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        racer->forwardVel -= d2;
""",
    "d012a": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        racer->forwardVel = racer->forwardVel - d2;
""",
    "d0123": """\
        d0 = racer->velocity * 0.05;
        d1 = racer->forwardVel + d0;
        d2 = d1 * 0.125;
        d3 = racer->forwardVel - d2;
        racer->forwardVel = d3;
""",
}


def replace_once(source: str, old: str, new: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"expected one occurrence, found {count}: {old!r}")
    return source.replace(old, new, 1)


def variables(form: str, prefix: str) -> tuple[str, ...]:
    return tuple(f"{prefix}{index}" for index in range(4) if f"{prefix}{index}" in form)


def make(stick: str, forward: str, declaration_mode: str) -> str:
    source = BASE
    snames = variables(STICK_FORMS[stick], "s")
    dnames = variables(FORWARD_FORMS[forward], "d")
    if declaration_mode == "stick_first":
        names = snames + dnames
    elif declaration_mode == "forward_first":
        names = dnames + snames
    else:
        names = tuple(
            item
            for pair in itertools.zip_longest(snames, dnames)
            for item in pair
            if item is not None
        )
    declarations = "".join(f"    f64 {name};\n" for name in names)
    source = replace_once(
        source,
        "    Object_Boost *boostObj;\n",
        "    Object_Boost *boostObj;\n" + declarations,
    )
    source = replace_once(source, OLD_STICK, STICK_FORMS[stick])
    source = replace_once(source, OLD_FORWARD, FORWARD_FORMS[forward])
    return source


def main() -> None:
    hits: list[tuple[int, int, str, str]] = []
    seen: set[str] = set()
    for stick in STICK_FORMS:
        for forward in FORWARD_FORMS:
            for mode in ("stick_first", "forward_first", "interleave"):
                tag = f"{stick}_{forward}_{mode}"
                source = make(stick, forward, mode)
                result = ORACLE["evaluate"](source, keep=f"/tmp/codex_combined_{tag}.o")
                signature = str(
                    (
                        result.get("sha1"),
                        result.get("frame"),
                        result.get("insns"),
                        result.get("f20_operands"),
                        result.get("f18"),
                    )
                )
                if signature not in seen:
                    seen.add(signature)
                    print(tag, ORACLE["concise"](result), result.get("fp"))
                if result.get("f20_insns"):
                    with open(
                        f"/tmp/codex_combined_{tag}.c", "w", encoding="utf-8"
                    ) as output:
                        output.write(source)
                    hits.append(
                        (
                            int(result["norm"]),
                            abs(int(result["insns"]) - 2625),
                            tag,
                            ORACLE["concise"](result),
                        )
                    )
    print("HITS", len(hits))
    for hit in sorted(hits)[:40]:
        print("HIT", *hit)


if __name__ == "__main__":
    main()
