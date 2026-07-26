#!/usr/bin/env python3
"""Search statement/lifetime forms for the trophy test in v_zz1.

Expression-only variants value-number to the same ucode.  This sweep instead
introduces explicit, live statement boundaries using existing dead-at-this-
point locals, which changes whether the shift/mask is a pool expression or a
colored web.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core


VARIANT = (
    core.ROOT / "menu_research" / "variants" / "v_zz1.txt"
).read_text().rstrip()
SOURCE = core.build_variant(core.BASE, VARIANT)
OLD = """\
                    if (trackX == 4) {
                        if (((settings->trophies >> (trackY * 2)) & 3) == 3) {
                            cur->visible = 2;
                        }
                    }"""
if SOURCE.count(OLD) != 1:
    raise RuntimeError("expected one baseline trophy block")

SHIFT = "(settings->trophies >> (trackY * 2))"
LOW = f"({SHIFT} & 3)"

CASES: list[tuple[str, str, str]] = []

for var in ("temp", "pad2"):
    CASES.extend(
        [
            (
                f"{var}-low-before",
                "",
                f"""\
                    if (trackX == 4) {{
                        {var} = {LOW};
                        if ({var} == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"{var}-shift-before",
                "",
                f"""\
                    if (trackX == 4) {{
                        {var} = {SHIFT};
                        if (({var} & 3) == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"{var}-count-before",
                "",
                f"""\
                    if (trackX == 4) {{
                        {var} = trackY * 2;
                        if (((settings->trophies >> {var}) & 3) == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"{var}-low-assign-cond",
                "",
                f"""\
                    if (trackX == 4) {{
                        if (({var} = {LOW}) == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"{var}-shift-assign-cond",
                "",
                f"""\
                    if (trackX == 4) {{
                        if ((({var} = {SHIFT}) & 3) == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"{var}-visible-value",
                "",
                f"""\
                    if (trackX == 4) {{
                        {var} = 2;
                        if ({LOW} == 3) {{
                            cur->visible = {var};
                        }}
                    }}""",
            ),
            (
                f"{var}-bool",
                "",
                f"""\
                    if (trackX == 4) {{
                        {var} = ({LOW} == 3);
                        if ({var}) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
        ]
    )

for typename in ("s32", "u32", "s16", "u16", "s8", "u8"):
    var = "trophyTemp"
    declaration = f"\n    {typename} {var};"
    CASES.extend(
        [
            (
                f"new-{typename}-low-before",
                declaration,
                f"""\
                    if (trackX == 4) {{
                        {var} = {LOW};
                        if ({var} == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"new-{typename}-shift-before",
                declaration,
                f"""\
                    if (trackX == 4) {{
                        {var} = {SHIFT};
                        if (({var} & 3) == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"new-{typename}-count-before",
                declaration,
                f"""\
                    if (trackX == 4) {{
                        {var} = trackY * 2;
                        if (((settings->trophies >> {var}) & 3) == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"new-{typename}-assign-cond",
                declaration,
                f"""\
                    if (trackX == 4) {{
                        if (({var} = {LOW}) == 3) {{
                            cur->visible = 2;
                        }}
                    }}""",
            ),
            (
                f"new-{typename}-visible-value",
                declaration,
                f"""\
                    if (trackX == 4) {{
                        {var} = 2;
                        if ({LOW} == 3) {{
                            cur->visible = {var};
                        }}
                    }}""",
            ),
        ]
    )

CASES.extend(
    [
        (
            "inverted-continue",
            "",
            f"""\
                    if (trackX == 4) {{
                        if ({LOW} != 3) {{
                        }} else {{
                            cur->visible = 2;
                        }}
                    }}""",
        ),
        (
            "bit-test-pair",
            "",
            f"""\
                    if (trackX == 4) {{
                        if (({SHIFT} & 1) && ({SHIFT} & 2)) {{
                            cur->visible = 2;
                        }}
                    }}""",
        ),
        (
            "switch-low",
            "",
            f"""\
                    if (trackX == 4) {{
                        switch ({LOW}) {{
                        case 3:
                            cur->visible = 2;
                            break;
                        }}
                    }}""",
        ),
    ]
)


def evaluate(
    case: tuple[str, str, str]
) -> tuple[int, int, int, str, str, str]:
    label, declaration, block = case
    source = SOURCE.replace("    long long new_var;", f"    long long new_var;{declaration}", 1)
    source = source.replace(OLD, block, 1)
    with tempfile.TemporaryDirectory(prefix="menu-trophy-stmt-") as tmp:
        directory = Path(tmp)
        src = directory / "candidate.c"
        obj = directory / "candidate.o"
        src.write_text(source)
        obj.touch()
        proc = subprocess.run(
            ["bash", core.COMPILE, src, "-o", obj],
            cwd=core.ROOT,
            capture_output=True,
            text=True,
        )
        if proc.returncode:
            return (9999, -1, -1, label, declaration, proc.stderr[-500:])
        got = core.words(obj)
    diffs = [i for i, (left, right) in enumerate(zip(got, core.WANT)) if left != right]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), label, declaration, block)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3]))
    print(f"cases={len(results)}")
    for full, first, length, label, declaration, block in results:
        print(f"FW={full:4d} FIRST={first:3d} LEN={length:3d} {label}")
        if full == 0:
            print(declaration)
            print(block)


if __name__ == "__main__":
    main()
