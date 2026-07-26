#!/usr/bin/env python3
"""Search source topologies that keep the branch value live into the index.

The best known construction has the right instruction topology and every
downstream allocation is correct modulo a persistent t2/t3 swap.  These cases
move an already-required index assignment (or the complete track-name store)
into the true side of the condition expression.  If Ugen retains the branch
value while constructing that side, the multiply takes t3 and the comparison
value returns to the FIFO afterward, which is the target queue order.
"""

from __future__ import annotations

import concurrent.futures
import os
import subprocess
import tempfile
from pathlib import Path

import construct_condition_sweep as conditions
import construct_index_sweep as core


CONDITION = "(s32)(s64)pad != -1"
COND35_REPLACEMENT = """\
                pad = (gTrackSelectIDs[pad][trackX]) & 0xFFFFFFFFFFFFFFFFLL;
                pad = pad & 0xFFFFFFFFFFFFFFFFULL;
                pad = pad & 0xFFFFFFFFFFFFFFFFULL;
                cur->hubName = trackName;
                if (((s32)(s64)pad != -1)) {"""
SOURCE = conditions.SOURCE.replace(
    conditions.OLD_COND, COND35_REPLACEMENT, 1
)

OLD_HEAD = """\
                if (((s32)(s64)pad != -1)) {
                    cur->trackName = level_name(trackMenuIds[(new_var = trackY * 6) + trackX]);"""
if SOURCE.count(OLD_HEAD) != 1:
    raise RuntimeError("expected one branch/call head")

ASSIGN = "(new_var = trackY * 6)"
INDEX = "new_var + trackX"
CALL = f"level_name(trackMenuIds[{ASSIGN} + trackX])"
CALL_INDEXED = f"level_name(trackMenuIds[{INDEX}])"
STORE = f"(cur->trackName = {CALL})"
STORE_INDEXED = f"(cur->trackName = {CALL_INDEXED})"


def head(condition: str, statement: str = "") -> str:
    result = f"                if (({condition})) {{"
    if statement:
        result += f"\n                    {statement}"
    return result


CASES: list[tuple[str, str]] = [
    (
        "baseline",
        head(CONDITION, f"cur->trackName = {CALL};"),
    ),
]

# Move only the required multiply assignment into the true arm.  The following
# expression is intentionally constant, so it should add no target operation.
assignment_conditions = {
    "and-comma-one": f"({CONDITION}) && ({ASSIGN}, 1)",
    "and-comma-notzero": f"({CONDITION}) && ({ASSIGN}, !0)",
    "and-comma-uone": f"({CONDITION}) && ({ASSIGN}, 1U)",
    "and-comma-llone": f"({CONDITION}) && ({ASSIGN}, 1LL)",
    "and-or-one": f"({CONDITION}) && ({ASSIGN} || 1)",
    "and-not-and-zero": f"({CONDITION}) && !({ASSIGN} && 0)",
    "and-eq-self": f"({CONDITION}) && ({ASSIGN} == {ASSIGN})",
    "and-ternary-one": f"({CONDITION}) && ({ASSIGN} ? 1 : 1)",
    "ternary-comma": f"({CONDITION}) ? ({ASSIGN}, 1) : 0",
    "ternary-notzero": f"({CONDITION}) ? ({ASSIGN}, !0) : 0",
    "ternary-nested": f"({CONDITION}) ? ({ASSIGN} ? 1 : 1) : 0",
    "bitand-comma": f"({CONDITION}) & ({ASSIGN}, 1)",
    "multiply-comma": f"({CONDITION}) * ({ASSIGN}, 1)",
    "comma-after-cond": f"(({CONDITION}) ? ({ASSIGN}, 1) : 0) != 0",
}
for label, condition in assignment_conditions.items():
    CASES.append(
        (label, head(condition, f"cur->trackName = {CALL_INDEXED};"))
    )

# Put the entire already-required call/store into the true side.  This joins
# the branch and index DAGs more strongly than moving just the multiply.
store_conditions = {
    "and-store-comma": f"({CONDITION}) && ({STORE}, 1)",
    "and-store-notzero": f"({CONDITION}) && ({STORE}, !0)",
    "and-store-uone": f"({CONDITION}) && ({STORE}, 1U)",
    "and-store-or-one": f"({CONDITION}) && ({STORE} || 1)",
    "and-store-ternary": f"({CONDITION}) && ({STORE} ? 1 : 1)",
    "ternary-store-comma": f"({CONDITION}) ? ({STORE}, 1) : 0",
    "ternary-store-notzero": f"({CONDITION}) ? ({STORE}, !0) : 0",
    "ternary-store-nested": f"({CONDITION}) ? ({STORE} ? 1 : 1) : 0",
}
for label, condition in store_conditions.items():
    CASES.append((label, head(condition)))

# Split assignment and call across successive short-circuit operands.
split_conditions = {
    "and-assign-and-store": (
        f"({CONDITION}) && ({ASSIGN}, 1) && ({STORE_INDEXED}, 1)"
    ),
    "and-assign-ternary-store": (
        f"({CONDITION}) && (({ASSIGN}, 1) ? ({STORE_INDEXED}, 1) : 0)"
    ),
    "ternary-assign-store": (
        f"({CONDITION}) ? ({ASSIGN}, {STORE_INDEXED}, 1) : 0"
    ),
}
for label, condition in split_conditions.items():
    CASES.append((label, head(condition)))


def evaluate(case: tuple[str, str]) -> tuple[int, int, int, str, str]:
    label, replacement = case
    source = SOURCE.replace(OLD_HEAD, replacement, 1)
    with tempfile.TemporaryDirectory(prefix="menu-branch-life-") as tmp:
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
            return (9999, -1, -1, label, proc.stderr[-800:])
        got = core.words(obj)
    diffs = [
        i for i, (left, right) in enumerate(zip(got, core.WANT))
        if left != right
    ]
    full = len(diffs) + abs(len(got) - len(core.WANT))
    first = diffs[0] if diffs else min(len(got), len(core.WANT))
    return (full, first, len(got), label, replacement)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES))
    results.sort(key=lambda row: (row[0], -row[1], row[3]))
    print(f"cases={len(results)}")
    for full, first, length, label, replacement in results:
        print(f"FW={full:4d} FIRST={first:3d} LEN={length:3d} {label}")
        if full == 0:
            print(replacement)


if __name__ == "__main__":
    main()
