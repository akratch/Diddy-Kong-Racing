#!/usr/bin/env python3
"""Tune each arithmetic stage of trackY*6 independently.

The retail as1 expansion is:
    t3 = trackY << 2
    t3 = t3 - trackY
    t3 = t3 << 1

The FW3 basin performs the first two stages in t2 and only the final stage in
t3.  Insert value-preserving live conversion events between those exact
arithmetic stages, rather than after a completed multiply, so each in-place
destination and the downstream allocator state can be selected separately.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_postbranch_index_sequence_sweep as post


MASKS = {
    "S": "new_var = new_var & 0xFFFFFFFFFFFFFFFFLL;",
    "U": "new_var = new_var & 0xFFFFFFFFFFFFFFFFULL;",
}

STAGES = {
    "assign": (
        "new_var = trackY << 2;",
        "new_var = new_var - trackY;",
        "new_var = new_var << 1;",
    ),
    "compound": (
        "new_var = trackY << 2;",
        "new_var -= trackY;",
        "new_var <<= 1;",
    ),
    "mul4-compound": (
        "new_var = trackY * 4;",
        "new_var -= trackY;",
        "new_var *= 2;",
    ),
    "seed-shift-compound": (
        "new_var = trackY;",
        "new_var <<= 2;",
        "new_var -= trackY;",
        "new_var <<= 1;",
    ),
    "double-then-triple": (
        "new_var = trackY + trackY;",
        "new_var *= 3;",
        "",
    ),
}


def render(
    stages: tuple[str, ...],
    counts: tuple[int, ...],
    kind: str,
) -> str:
    lines: list[str] = []
    for stage, count in zip(stages, counts):
        if stage:
            lines.append(stage)
        lines.extend(MASKS[kind] for _ in range(count))
    lines.append(
        "cur->trackName = level_name("
        "trackMenuIds[new_var + trackX]);"
    )
    return "\n".join(f"                    {line}" for line in lines)


CASES: list[tuple[str, tuple[int, ...], str, str]] = []
for label, stages in STAGES.items():
    # One conversion count follows each stage.  For four-stage forms, keep the
    # first seed/shift adjacent and distribute events over the last three
    # meaningful boundaries to avoid a needless fourth-dimensional sweep.
    if len(stages) == 4:
        effective_stages = (
            stages[0],
            stages[1] + "\n                    " + stages[2],
            stages[3],
        )
    else:
        effective_stages = stages
    for first in range(0, 15):
        for second in range(0, 15):
            for third in range(0, 15):
                total = first + second + third
                if total < 9 or total > 15:
                    continue
                counts = (first, second, third)
                for kind in MASKS:
                    CASES.append(
                        (
                            label,
                            counts,
                            kind,
                            render(effective_stages, counts, kind),
                        )
                    )


def evaluate(
    case: tuple[str, tuple[int, ...], str, str]
) -> tuple[
    int, int, int, str, tuple[int, ...], str, str, tuple[int, ...]
]:
    label, counts, kind, replacement = case
    source = post.SOURCE.replace(post.OLD_CALL, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-mul-stages-") as tmp:
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
                counts,
                kind,
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
        counts,
        kind,
        replacement,
        diffs,
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(
        key=lambda row: (row[0], -row[1], row[3], row[4], row[5])
    )
    print(f"cases={len(results)}")
    for (
        full,
        first,
        length,
        label,
        counts,
        kind,
        replacement,
        diffs,
    ) in results[:300]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{label} counts={counts} kind={kind} diffs={diffs}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
