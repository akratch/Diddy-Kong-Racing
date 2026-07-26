#!/usr/bin/env python3
"""Split the live index conversion cycle across the level_name call.

The known post-branch FW3 construction has the right allocator state after
the multiply, but as1 folds its final copy into only the last instruction of
the multiply-by-six expansion.  A call is a real copy-propagation barrier.
Keep the index live for the later course-flags lookup, put part of the
32<->64 conversion cycle before the call, and finish the cycle afterward so
the multiply and the trophy block can be tuned independently.
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
    "plain": "new_var = trackY * 6;",
    "wide-s": "new_var = (trackY * 6) & 0xFFFFFFFFFFFFFFFFLL;",
    "wide-u": "new_var = (trackY * 6) & 0xFFFFFFFFFFFFFFFFULL;",
}


def render(
    initial: str,
    pre_count: int,
    post_count: int,
    pre_kind: str,
    post_kind: str,
) -> str:
    lines = [initial]
    lines.extend(MASKS[pre_kind] for _ in range(pre_count))
    lines.append(
        "cur->trackName = level_name("
        "trackMenuIds[new_var + trackX]);"
    )
    lines.extend(MASKS[post_kind] for _ in range(post_count))
    return "\n".join(f"                    {line}" for line in lines)


# Include more than one full observed 5/12-step allocator period on each side
# of the call.  Homogeneous signed/unsigned runs expose the period; mixed
# endpoints test whether the conversion opcode itself affects the handoff.
CASES: list[tuple[str, int, int, str, str, str]] = []
for initial_label, initial in INITIALS.items():
    for pre_count in range(0, 18):
        for post_count in range(0, 18):
            for pre_kind, post_kind in (
                ("S", "S"),
                ("S", "U"),
                ("U", "S"),
                ("U", "U"),
            ):
                CASES.append(
                    (
                        initial_label,
                        pre_count,
                        post_count,
                        pre_kind,
                        post_kind,
                        render(
                            initial,
                            pre_count,
                            post_count,
                            pre_kind,
                            post_kind,
                        ),
                    )
                )


def evaluate(
    case: tuple[str, int, int, str, str, str]
) -> tuple[int, int, int, str, int, int, str, str, str, tuple[int, ...]]:
    (
        initial,
        pre_count,
        post_count,
        pre_kind,
        post_kind,
        replacement,
    ) = case
    source = post.SOURCE.replace(post.OLD_CALL, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-call-split-") as tmp:
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
        )
    )
    print(f"cases={len(results)}")
    for (
        full,
        first,
        length,
        initial,
        pre_count,
        post_count,
        pre_kind,
        post_kind,
        replacement,
        diffs,
    ) in results[:300]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{initial} pre={pre_kind}{pre_count} "
            f"post={post_kind}{post_count} diffs={diffs}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
