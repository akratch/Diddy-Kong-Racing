#!/usr/bin/env python3
"""Search entry-pointer and pointer-to-row topologies in the FW35 basin.

The retail code preserves the selected `trackMenuIds` entry address in s1 and
dereferences it on both sides of a call.  Model that value directly instead
of asking CSE to recover it from a saved integer index.  Pointer-to-array
forms are especially useful: the compiler, rather than source arithmetic,
creates the multiply-by-six after any live row-index conversions.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_postbranch_index_sequence_sweep as post


OLD_DECL = "    s32 new_var;"
SECOND_USE = "trackMenuIds[new_var + trackX]"
for needle in (OLD_DECL, SECOND_USE):
    if post.SOURCE.count(needle) != 1:
        raise RuntimeError(f"expected one occurrence of {needle!r}")

DECLS = """\
    s32 new_var;
    s8 *entry;
    s8 *row;
    s8 (*rows)[6];"""

MASK = "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL;"


def indent(lines: list[str]) -> str:
    return "\n".join(f"                    {line}" for line in lines)


def make_source(lines: list[str], second: str) -> tuple[str, str]:
    replacement = indent(lines)
    source = post.SOURCE.replace(OLD_DECL, DECLS, 1)
    source = source.replace(post.OLD_CALL, replacement, 1)
    source = source.replace(SECOND_USE, second, 1)
    return replacement, source


CASES: list[tuple[str, int, str, str]] = []

# First compute byte offset trackY*6, then retain the actual entry pointer.
for count in range(0, 17):
    prefix = ["new_var = trackY * 6;", *([MASK] * count)]
    topologies = {
        "entry-index": [
            *prefix,
            "entry = &trackMenuIds[new_var + trackX];",
            "cur->trackName = level_name(*entry);",
        ],
        "entry-pointer-add": [
            *prefix,
            "entry = trackMenuIds + new_var + trackX;",
            "cur->trackName = level_name(*entry);",
        ],
        "entry-pointer-reverse": [
            *prefix,
            "entry = trackMenuIds + trackX + new_var;",
            "cur->trackName = level_name(*entry);",
        ],
        "row-then-entry": [
            *prefix,
            "row = trackMenuIds + new_var;",
            "entry = row + trackX;",
            "cur->trackName = level_name(*entry);",
        ],
        "entry-then-add": [
            *prefix,
            "entry = trackMenuIds + trackX;",
            "entry += new_var;",
            "cur->trackName = level_name(*entry);",
        ],
        "entry-base-then-add": [
            *prefix,
            "entry = trackMenuIds;",
            "entry += new_var + trackX;",
            "cur->trackName = level_name(*entry);",
        ],
    }
    for label, lines in topologies.items():
        replacement, source = make_source(lines, "*entry")
        CASES.append((f"offset-{label}", count, replacement, source))

# Preserve a row number; let pointer-to-array lowering introduce scale 6.
for count in range(0, 18):
    initial_forms = {
        "plain": "new_var = trackY;",
        "wide": (
            "new_var = trackY & 0xFFFFFFFFFFFFFFFFLL;"
        ),
    }
    for initial_label, initial in initial_forms.items():
        prefix = [
            "rows = (s8 (*)[6])trackMenuIds;",
            initial,
            *([MASK] * count),
        ]
        topologies = {
            "entry": [
                *prefix,
                "entry = &rows[new_var][trackX];",
                "cur->trackName = level_name(*entry);",
            ],
            "row-entry": [
                *prefix,
                "row = rows[new_var];",
                "entry = &row[trackX];",
                "cur->trackName = level_name(*entry);",
            ],
            "direct": [
                *prefix,
                "cur->trackName = level_name(rows[new_var][trackX]);",
            ],
            "nested-entry": [
                *prefix,
                "cur->trackName = level_name("
                "*(entry = &rows[new_var][trackX]));",
            ],
        }
        for label, lines in topologies.items():
            second = (
                "*entry"
                if label in {"entry", "row-entry", "nested-entry"}
                else "rows[new_var][trackX]"
            )
            replacement, source = make_source(lines, second)
            CASES.append(
                (
                    f"rows-{initial_label}-{label}",
                    count,
                    replacement,
                    source,
                )
            )

# No scalar carrier at all: repeated pointer-to-row expressions or a retained
# entry pointer.  These are plausible original-source shapes on their own.
direct_forms = {
    "rows-direct": [
        "rows = (s8 (*)[6])trackMenuIds;",
        "cur->trackName = level_name(rows[trackY][trackX]);",
    ],
    "rows-entry": [
        "rows = (s8 (*)[6])trackMenuIds;",
        "entry = &rows[trackY][trackX];",
        "cur->trackName = level_name(*entry);",
    ],
    "raw-entry": [
        "entry = &trackMenuIds[trackY * 6 + trackX];",
        "cur->trackName = level_name(*entry);",
    ],
}
for label, lines in direct_forms.items():
    second = (
        "rows[trackY][trackX]"
        if label == "rows-direct"
        else "*entry"
    )
    replacement, source = make_source(lines, second)
    CASES.append((label, 0, replacement, source))


def evaluate(
    case: tuple[str, int, str, str]
) -> tuple[int, int, int, str, int, str, tuple[int, ...]]:
    label, count, replacement, source = case
    with tempfile.TemporaryDirectory(prefix="menu-entry-pointer-") as tmp:
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
            return (
                9999,
                -1,
                -1,
                label,
                count,
                proc.stderr[-800:],
                (),
            )
        got = core.words(obj)
    diffs = tuple(
        i
        for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    )
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (
        full,
        first,
        len(got),
        label,
        count,
        replacement,
        diffs,
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(
        key=lambda row: (row[0], -row[1], row[3], row[4])
    )
    print(f"cases={len(results)}")
    for full, first, length, label, count, replacement, diffs in results[:200]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{label} count={count} diffs={diffs}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
