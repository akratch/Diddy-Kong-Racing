#!/usr/bin/env python3
"""Recover the grounded-wheel stick expression's allocator-visible spelling."""

from __future__ import annotations

import collections
import hashlib
import os
import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_layout_exact.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
OLD = "        gCurrentStickY = (1.0 - var_f20) * ((f32) gCurrentStickY);\n"
FAKE_BLOCK = """\
#ifdef FAKEMATCH
    // fake match for $f registers
    gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;
#else
    gCurrentCarSteerVel = 0;
#endif
"""
FAKE = "    gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;\n"

FORMS = {
    "original": OLD,
    "reverse": "        gCurrentStickY = ((f32) gCurrentStickY) * (1.0 - var_f20);\n",
    "reverse_cast": "        gCurrentStickY = (f32) gCurrentStickY * (1.0 - var_f20);\n",
    "compound": "        gCurrentStickY *= 1.0 - var_f20;\n",
    "cast_result": "        gCurrentStickY = (s32) ((1.0 - var_f20) * ((f32) gCurrentStickY));\n",
    "cast_product_f32": "        gCurrentStickY = (f32) ((1.0 - var_f20) * ((f32) gCurrentStickY));\n",
    "double_stick": "        gCurrentStickY = (1.0 - var_f20) * ((f64) gCurrentStickY);\n",
    "double_cast_stick": "        gCurrentStickY = (1.0 - var_f20) * ((f64) ((f32) gCurrentStickY));\n",
    "one_long": "        gCurrentStickY = (1.0L - var_f20) * ((f32) gCurrentStickY);\n",
    "one_cast": "        gCurrentStickY = ((f64) 1 - var_f20) * ((f32) gCurrentStickY);\n",
    "one_float": "        gCurrentStickY = (1.0f - var_f20) * ((f32) gCurrentStickY);\n",
    "one_int": "        gCurrentStickY = (1 - var_f20) * ((f32) gCurrentStickY);\n",
    "paren_left": "        gCurrentStickY = ((1.0 - var_f20) * (f32) gCurrentStickY);\n",
    "paren_right": "        gCurrentStickY = ((f32) gCurrentStickY * (1.0 - var_f20));\n",
    "assign_vf2_value": """\
        var_f2 = (f32) gCurrentStickY;
        gCurrentStickY = (1.0 - var_f20) * var_f2;
""",
    "assign_spcc_value": """\
        spCC = (f32) gCurrentStickY;
        gCurrentStickY = (1.0 - var_f20) * spCC;
""",
    "comma_vf2_value": """\
        gCurrentStickY =
            (var_f2 = (f32) gCurrentStickY,
             (1.0 - var_f20) * var_f2);
""",
    "comma_spcc_value": """\
        gCurrentStickY =
            (spCC = (f32) gCurrentStickY,
             (1.0 - var_f20) * spCC);
""",
    "assign_vf2_factor": """\
        var_f2 = 1.0 - var_f20;
        gCurrentStickY = var_f2 * ((f32) gCurrentStickY);
""",
    "assign_spcc_factor": """\
        spCC = 1.0 - var_f20;
        gCurrentStickY = spCC * ((f32) gCurrentStickY);
""",
    "comma_vf2_factor": """\
        gCurrentStickY =
            (var_f2 = 1.0 - var_f20,
             var_f2 * ((f32) gCurrentStickY));
""",
    "comma_spcc_factor": """\
        gCurrentStickY =
            (spCC = 1.0 - var_f20,
             spCC * ((f32) gCurrentStickY));
""",
}

F64_FORMS = {
    "f64_value": """\
        d0 = (f32) gCurrentStickY;
        gCurrentStickY = (1.0 - var_f20) * d0;
""",
    "f64_factor": """\
        d0 = 1.0 - var_f20;
        gCurrentStickY = d0 * ((f32) gCurrentStickY);
""",
    "f64_comma_value": """\
        gCurrentStickY =
            (d0 = (f32) gCurrentStickY,
             (1.0 - var_f20) * d0);
""",
    "f64_comma_factor": """\
        gCurrentStickY =
            (d0 = 1.0 - var_f20,
             d0 * ((f32) gCurrentStickY));
""",
}


def source_for(tag: str, block: str, add_f64: bool = False) -> str:
    source = BASE.replace(FAKE_BLOCK, FAKE, 1)
    if add_f64:
        source = source.replace(
            "    Object_Boost *boostObj;\n",
            "    Object_Boost *boostObj;\n    f64 d0;\n",
            1,
        )
    if source.count(OLD) != 1:
        raise ValueError(f"stick expression missing for {tag}")
    return source.replace(OLD, block, 1)


def forced(source_path: str, tag: str) -> dict[str, object]:
    obj = f"/tmp/codex_stickform_{tag}_forced.o"
    trace = f"/tmp/codex_stickform_{tag}_forced.trace"
    process = subprocess.run(
        ["/tmp/codex_run_analysis.sh", source_path, obj, trace],
        capture_output=True,
        text=True,
    )
    if process.returncode != 0 or not os.path.exists(obj):
        return {"ok": False, "stderr": process.stderr[-1000:]}
    _, instructions = ORACLE["dump_object"](obj)
    if len(instructions) != len(TARGET):
        mismatch = max(len(instructions), len(TARGET))
    else:
        mismatch = 0
        for (_, target), (_, candidate) in zip(TARGET, instructions):
            target = re.sub(r"\b[0-9a-f]+\s+<[^>]+>", "ADDR", target)
            candidate = re.sub(r"\b[0-9a-f]+\s+<[^>]+>", "ADDR", candidate)
            target = re.sub(r"-?\d+\((?:\$)?at\)", "OFF(at)", target)
            candidate = re.sub(r"-?\d+\((?:\$)?at\)", "OFF(at)", candidate)
            mismatch += target != candidate
    fp = collections.Counter(
        reg
        for _, assembly in instructions
        for reg in re.findall(r"\$(f\d+)\b", assembly)
    )
    words = [word for word, _ in instructions]
    return {
        "ok": True,
        "insns": len(instructions),
        "mismatch": mismatch,
        "fp": dict(sorted(fp.items(), key=lambda item: int(item[0][1:]))),
        "sha1": hashlib.sha1("".join(words).encode()).hexdigest()[:12],
    }


def main() -> None:
    entries = [(tag, block, False) for tag, block in FORMS.items()]
    entries += [(tag, block, True) for tag, block in F64_FORMS.items()]
    rows = []
    for tag, block, add_f64 in entries:
        source = source_for(tag, block, add_f64)
        path = f"/tmp/codex_stickform_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_stickform_{tag}_natural.o"
        )
        forced_result = forced(path, tag)
        rows.append((forced_result.get("mismatch", 9999), tag, natural, forced_result))
    for _, tag, natural, forced_result in sorted(rows):
        print(
            tag,
            "natural",
            ORACLE["concise"](natural),
            "forced",
            forced_result,
        )


if __name__ == "__main__":
    main()
