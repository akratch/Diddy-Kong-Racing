#!/usr/bin/env python3
"""Make the FW3 index conversion web end at its multiply producer.

The FW3 basin has a pre-as1 `mul t2,s3,6; move t3,t2`; as1 folds the move
into only the final shift.  This sweep changes the value graph, not the
arithmetic: it alternates a live index through real scalar carriers and also
tests nested conversion trees.  The final carrier feeds both table lookups,
so no assignment is dead.
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

MASKS = {
    "S": "0xFFFFFFFFFFFFFFFFLL",
    "U": "0xFFFFFFFFFFFFFFFFULL",
}
CARRIERS = ("new_var", "pad2")


def block(lines: list[str], final: str) -> str:
    result = list(lines)
    result.append(
        "cur->trackName = level_name("
        f"trackMenuIds[{final} + trackX]);"
    )
    return "\n".join(f"                    {line}" for line in result)


def source_for(replacement: str, final: str) -> str:
    source = post.SOURCE.replace(post.OLD_CALL, replacement, 1)
    return source.replace(
        SECOND_USE, f"trackMenuIds[{final} + trackX]", 1
    )


CASES: list[tuple[str, int, str, str, str]] = []

# Cross-statement carrier paths.  Each starts with a real multiply and each
# conversion assigns the only value used by both later lookups.
for initial in CARRIERS:
    other = CARRIERS[initial == "new_var"]
    initial_forms = {
        "plain": [f"{initial} = trackY * 6;"],
        "wide-s": [
            f"{initial} = (trackY * 6) & {MASKS['S']};"
        ],
        "wide-u": [
            f"{initial} = (trackY * 6) & {MASKS['U']};"
        ],
        "chain-inner": [
            f"{other} = {initial} = trackY * 6;"
        ],
        "chain-outer": [
            f"{initial} = {other} = trackY * 6;"
        ],
        "nested-wide-s": [
            f"{other} = ({initial} = trackY * 6) & {MASKS['S']};"
        ],
        "nested-wide-u": [
            f"{other} = ({initial} = trackY * 6) & {MASKS['U']};"
        ],
    }
    for init_label, initial_lines in initial_forms.items():
        init_final = (
            other if init_label.startswith(("chain", "nested")) else initial
        )
        for count in range(7, 17):
            for kind in MASKS:
                paths: dict[str, list[str]] = {}

                current = init_final
                lines: list[str] = []
                for _ in range(count):
                    lines.append(
                        f"{current} = {current} & {MASKS[kind]};"
                    )
                paths["self"] = lines

                current = init_final
                lines = []
                for _ in range(count):
                    dest = other if current == initial else initial
                    lines.append(
                        f"{dest} = {current} & {MASKS[kind]};"
                    )
                    current = dest
                paths["alternate"] = lines

                current = init_final
                lines = []
                dest = other if current == initial else initial
                for _ in range(count):
                    lines.append(
                        f"{dest} = {current} & {MASKS[kind]};"
                    )
                    current = dest
                paths["one-handoff"] = lines

                for path_label, path_lines in paths.items():
                    final = current if path_label == "one-handoff" else (
                        init_final
                        if path_label == "self"
                        else (
                            init_final if count % 2 == 0 else (
                                other if init_final == initial else initial
                            )
                        )
                    )
                    replacement = block(
                        [*initial_lines, *path_lines], final
                    )
                    CASES.append(
                        (
                            f"{initial}-{init_label}-{path_label}-{kind}",
                            count,
                            final,
                            replacement,
                            source_for(replacement, final),
                        )
                    )

# Entire conversion trees nested around the multiply.  These can propagate an
# outer destination hint directly into Umpy instead of creating a trailing
# copy.  Parentheses are explicit to preserve the intended tree.
for final in CARRIERS:
    for count in range(1, 18):
        for kind, mask in MASKS.items():
            expression = "trackY * 6"
            for _ in range(count):
                expression = f"({expression}) & {mask}"
            forms = {
                "nested-mask": f"{final} = {expression};",
                "nested-cast": (
                    f"{final} = (s32)(s64)({expression});"
                ),
                "nested-chain": (
                    f"{final} = "
                    f"({CARRIERS[final == 'new_var']} = {expression});"
                ),
            }
            for label, statement in forms.items():
                replacement = block([statement], final)
                CASES.append(
                    (
                        f"{final}-{label}-{kind}",
                        count,
                        final,
                        replacement,
                        source_for(replacement, final),
                    )
                )


def evaluate(
    case: tuple[str, int, str, str, str]
) -> tuple[int, int, int, str, int, str, str, tuple[int, ...]]:
    label, count, final, replacement, source = case
    with tempfile.TemporaryDirectory(prefix="menu-live-carrier-") as tmp:
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
                final,
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
        final,
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
    for full, first, length, label, count, final, replacement, diffs in results[:200]:
        print(
            f"FW={full:4d} FIRST={first:3d} LEN={length:3d} "
            f"{label} count={count} final={final} diffs={diffs}"
        )
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
