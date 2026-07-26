#!/usr/bin/env python3
"""Free and recover t3 at the remaining FW2 subtract boundary.

The fused-tail basin emits:
    sll  t3,s3,2
    subu v0,t3,s3
    sll  t3,v0,1

Hand the live first-stage value to a second scalar through a conversion web
before evaluating the fused tail.  If t3 becomes free for the subtract, as1
can collapse the handoff copy and leave the exact destructive-looking
`subu t3,t3,s3` followed by `sll t3,t3,1`.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_index_sweep as core
import construct_postbranch_index_sequence_sweep as post


SECOND_USE = "trackMenuIds[new_var + trackX]"
if post.SOURCE.count(SECOND_USE) != 1:
    raise RuntimeError("expected one second index use")

MASK = "{var} = {var} & 0xFFFFFFFFFFFFFFFFLL;"

HANDOFFS: dict[str, tuple[list[str], str, int]] = {
    "none": ([], "new_var", 0),
    "copy": (["pad2 = new_var;"], "pad2", 0),
    "mask": (
        ["pad2 = new_var & 0xFFFFFFFFFFFFFFFFLL;"],
        "pad2",
        1,
    ),
    "mask-twice": (
        [
            "pad2 = new_var & 0xFFFFFFFFFFFFFFFFLL;",
            "pad2 = pad2 & 0xFFFFFFFFFFFFFFFFLL;",
        ],
        "pad2",
        2,
    ),
    "roundtrip": (["pad2 = (s32)(s64)new_var;"], "pad2", 0),
    "nested-copy": (["pad2 = (new_var = new_var);"], "pad2", 0),
    "chain-mask": (
        ["pad2 = (new_var = new_var & 0xFFFFFFFFFFFFFFFFLL);"],
        "pad2",
        1,
    ),
    "mask-copy-back": (
        [
            "pad2 = new_var & 0xFFFFFFFFFFFFFFFFLL;",
            "new_var = pad2;",
        ],
        "new_var",
        1,
    ),
    "mask-roundtrip-back": (
        [
            "pad2 = new_var & 0xFFFFFFFFFFFFFFFFLL;",
            "new_var = (s32)(s64)pad2;",
        ],
        "new_var",
        1,
    ),
}

TAIL_TEMPLATES = {
    "to-new": ("new_var = ({source} - trackY) << 1;", "new_var"),
    "to-pad2": ("pad2 = ({source} - trackY) << 1;", "pad2"),
    "nested-to-new": (
        "new_var = (pad2 = {source} - trackY) << 1;",
        "new_var",
    ),
    "nested-to-pad2": (
        "pad2 = (new_var = {source} - trackY) << 1;",
        "pad2",
    ),
}


def render(
    pre_count: int,
    handoff: list[str],
    source: str,
    tail_template: str,
    final: str,
    post_count: int,
) -> str:
    lines = [
        "new_var = trackY << 2;",
        *([MASK.format(var="new_var")] * pre_count),
        *handoff,
        tail_template.format(source=source),
        *([MASK.format(var=final)] * post_count),
        "cur->trackName = level_name("
        f"trackMenuIds[{final} + trackX]);",
    ]
    return "\n".join(f"                    {line}" for line in lines)


CASES: list[tuple[str, int, str, str, int, str, str]] = []
for pre_count in range(0, 16):
    for handoff_label, (handoff, source, handoff_events) in HANDOFFS.items():
        for tail_label, (tail_template, final) in TAIL_TEMPLATES.items():
            # Avoid the undefined nested self-assignment spellings.
            if tail_label == "nested-to-new" and source == "pad2":
                pass
            for post_count in range(0, 16):
                total = pre_count + handoff_events + post_count
                if total < 11 or total > 20:
                    continue
                replacement = render(
                    pre_count,
                    handoff,
                    source,
                    tail_template,
                    final,
                    post_count,
                )
                source_text = post.SOURCE.replace(
                    post.OLD_CALL, replacement, 1
                ).replace(
                    SECOND_USE,
                    f"trackMenuIds[{final} + trackX]",
                    1,
                )
                CASES.append(
                    (
                        handoff_label,
                        pre_count,
                        tail_label,
                        final,
                        post_count,
                        replacement,
                        source_text,
                    )
                )


def evaluate(
    case: tuple[str, int, str, str, int, str, str]
) -> tuple[
    int, int, int, str, int, str, str, int, str, tuple[int, ...]
]:
    (
        handoff,
        pre_count,
        tail,
        final,
        post_count,
        replacement,
        source,
    ) = case
    with tempfile.TemporaryDirectory(prefix="menu-sub-handoff-") as tmp:
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
                handoff,
                pre_count,
                tail,
                final,
                post_count,
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
        handoff,
        pre_count,
        tail,
        final,
        post_count,
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
            row[7],
        )
    )
    print(f"cases={len(results)}")
    for (
        full,
        first,
        length,
        handoff,
        pre_count,
        tail,
        final,
        post_count,
        replacement,
        diffs,
    ) in results[:300]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{handoff} pre={pre_count} {tail} final={final} "
            f"post={post_count} diffs={diffs}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
