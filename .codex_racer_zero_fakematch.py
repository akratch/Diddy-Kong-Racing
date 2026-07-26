#!/usr/bin/env python3
"""Probe optimizer-erased float comparisons on existing integer zero stores."""

from __future__ import annotations

import re
import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
STICK = runpy.run_path(".codex_racer_stick_forms.py")
TARGET = ORACLE["TARGET_INSNS"]
BASES = {
    "direct": open(
        "/tmp/codex_unk34_left_associative.c", encoding="utf-8"
    ).read(),
    "copy": open("/tmp/codex_segment_z_spcc.c", encoding="utf-8").read(),
}
FLOATS = (
    "spD0",
    "spD4",
    "spD8",
    "var_f14",
    "var_f20",
    "racerThrottle",
    "racerBrake",
)


def zero_lines(source: str) -> list[int]:
    lines = source.splitlines(keepends=True)
    start = next(i for i, line in enumerate(lines) if "spD4 = 0.01f;" in line)
    end = next(
        i
        for i, line in enumerate(lines[start:], start)
        if "racerBrake *= var_f14 / 2;" in line
    )
    return [
        i
        for i in range(start, end)
        if re.search(r"=\s*(?:0|FALSE);\s*$", lines[i])
    ]


def replace_zero(source: str, line_index: int, value: str) -> str:
    lines = source.splitlines(keepends=True)
    line = lines[line_index]
    if not re.search(r"=\s*(?:0|FALSE);[ \t]*\n?$", line):
        raise ValueError(f"not an integer zero store: {line!r}")
    lines[line_index] = re.sub(
        r"=\s*(?:0|FALSE);[ \t]*\n?$",
        f"= ({value} > 0.0f) * 0;\n",
        line,
    )
    return "".join(lines)


def fp_prefix(obj: str) -> int:
    _, candidate = ORACLE["dump_object"](obj)
    for index, ((_, target), (_, actual)) in enumerate(zip(TARGET, candidate)):
        if re.findall(r"\$f\d+\b", target) != re.findall(r"\$f\d+\b", actual):
            return index
    return min(len(TARGET), len(candidate))


def main() -> None:
    rows = []
    for base_name, base in BASES.items():
        for line_index in zero_lines(base):
            lhs = base.splitlines()[line_index].split("=", 1)[0].strip()
            lhs_tag = re.sub(r"\W+", "-", lhs).strip("-")
            for value in FLOATS:
                tag = f"{base_name}_l{line_index + 1}_{lhs_tag}_{value}"
                source = replace_zero(base, line_index, value)
                path = f"/tmp/codex_zero_fakematch_{tag}.c"
                with open(path, "w", encoding="utf-8") as output:
                    output.write(source)
                natural = ORACLE["evaluate"](
                    source, keep=f"/tmp/codex_zero_fakematch_{tag}_natural.o"
                )
                forced = STICK["forced"](path, f"zero_fakematch_{tag}")
                obj = f"/tmp/codex_stickform_zero_fakematch_{tag}_forced.o"
                prefix = fp_prefix(obj) if forced.get("ok") else -1
                rows.append((tag, natural, forced, prefix))
    for tag, natural, forced, prefix in sorted(
        rows,
        key=lambda row: (
            row[1].get("f20_operands", 0) == 0,
            -row[3],
            row[2].get("mismatch", 9999),
            row[0],
        ),
    ):
        if (
            natural.get("f20_operands", 0) > 0
            or prefix == len(TARGET)
            or natural.get("sha1")
            not in ("28ae550756b5", "30bfe1f7e10e")
        ):
            print(
                tag,
                "prefix",
                prefix,
                "natural",
                ORACLE["concise"](natural),
                "forced",
                forced,
            )
    print("tested", len(rows))


if __name__ == "__main__":
    main()
