#!/usr/bin/env python3
"""Tune a real pseudo-multiply with independent pre/post conversion phases.

Pre-converted-index work rotated the queue before `* 6`, while post-converted
work repaired the downstream queue, but the two controls were previously
tested separately.  Combining them can allocate the Umpy result directly in
t3 and then restore the exact later state without a trailing copy being
folded into only the last as1 expansion instruction.
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
INITIALS = {
    "plain": "new_var = trackY;",
    "wide-s": "new_var = trackY & 0xFFFFFFFFFFFFFFFFLL;",
    "wide-u": "new_var = trackY & 0xFFFFFFFFFFFFFFFFULL;",
}
MULTIPLIES = {
    "assign": "new_var = new_var * 6;",
    "reverse": "new_var = 6 * new_var;",
    "compound": "new_var *= 6;",
}


def render(
    initial: str,
    pre_count: int,
    multiply: str,
    post_count: int,
    pre_kind: str,
    post_kind: str,
) -> str:
    lines = [
        initial,
        *([MASKS[pre_kind]] * pre_count),
        multiply,
        *([MASKS[post_kind]] * post_count),
        "cur->trackName = level_name("
        "trackMenuIds[new_var + trackX]);",
    ]
    return "\n".join(f"                    {line}" for line in lines)


CASES: list[tuple[str, int, str, int, str, str, str]] = []
# Start with the canonical signed path.  Every preceding construction sweep
# found S/U pairs register-identical; the additional forms remain above for a
# focused expansion if this grid exposes a useful boundary.
for initial_label, initial in {"plain": INITIALS["plain"]}.items():
    for pre_count in range(0, 19):
        for multiply_label, multiply in MULTIPLIES.items():
            for post_count in range(0, 19):
                # Homogeneous phases expose the queue period.  Cross-kind
                # endpoints are retained because signedness can alter Ucvt
                # normalization even when the emitted value is identical.
                for pre_kind, post_kind in (("S", "S"),):
                    CASES.append(
                        (
                            initial_label,
                            pre_count,
                            multiply_label,
                            post_count,
                            pre_kind,
                            post_kind,
                            render(
                                initial,
                                pre_count,
                                multiply,
                                post_count,
                                pre_kind,
                                post_kind,
                            ),
                        )
                    )


def evaluate(
    case: tuple[str, int, str, int, str, str, str]
) -> tuple[
    int, int, int, str, int, str, int, str, str, str, tuple[int, ...]
]:
    (
        initial,
        pre_count,
        multiply,
        post_count,
        pre_kind,
        post_kind,
        replacement,
    ) = case
    source = post.SOURCE.replace(post.OLD_CALL, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-mul-pre-post-") as tmp:
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
                initial,
                pre_count,
                multiply,
                post_count,
                pre_kind,
                post_kind,
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
        initial,
        pre_count,
        multiply,
        post_count,
        pre_kind,
        post_kind,
        replacement,
        diffs,
    )


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(
        key=lambda row: (
            row[0],
            -row[1],
            row[3],
            row[4],
            row[5],
            row[6],
            row[7],
            row[8],
        )
    )
    print(f"cases={len(results)}")
    for (
        full,
        first,
        length,
        initial,
        pre_count,
        multiply,
        post_count,
        pre_kind,
        post_kind,
        replacement,
        diffs,
    ) in results[:300]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{initial} pre={pre_kind}{pre_count} {multiply} "
            f"post={post_kind}{post_count} diffs={diffs}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
