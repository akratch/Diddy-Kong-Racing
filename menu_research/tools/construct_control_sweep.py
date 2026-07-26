#!/usr/bin/env python3
"""Search control-flow forms that keep the track-ID load temporary.

The target evaluates the global s16 load before the hub-name store, yet the
store executes on both successors and lands in the branch delay slot.  These
forms make that "common successor store" explicit without assigning the load
to a scalar holder (the construction that ugen collapses into v1).
"""

from __future__ import annotations

import concurrent.futures
import os
import re
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "menu_research" / "tools"
BASE = (TOOLS / "base.c").read_text()
TARGET = TOOLS / "target.o"
OBJDUMP = ROOT / "tools" / "binutils" / "mips64-elf-objdump"
COMPILE = TOOLS / "compile.sh"

OLD = """\
                cur->hubName = levelName;
                if (selectedTrack != -1) {
                    cur->trackName = level_name(trackMenuIds[((trackY * 6) + trackX)]);
                    if (trackX == 4) {
                        if ((((settings->trophies) >> (trackY * 2)) & 3) == 3) {
                            cur->visible = 2;
                        }
                    } else if ((settings->courseFlagsPtr[trackMenuIds[((trackY * 6) + trackX)]] & 2)) {
                        cur->visible = 2;
                    }
                } else {
                    cur->trackName = gQMarkPtr;
                }"""

BODY = """\
                    cur->trackName = level_name(trackMenuIds[((trackY * 6) + trackX)]);
                    if (trackX == 4) {
                        if ((((settings->trophies) >> (trackY * 2)) & 3) == 3) {
                            cur->visible = 2;
                        }
                    } else if ((settings->courseFlagsPtr[trackMenuIds[((trackY * 6) + trackX)]] & 2)) {
                        cur->visible = 2;
                    }"""

LOAD = "gTrackSelectIDs[trackY][trackX]"
STORE = "cur->hubName = levelName;"
ELSE = "cur->trackName = gQMarkPtr;"

CASES = {
    "dup-if": f"""\
                if ({LOAD} != -1) {{
                    {STORE}
{BODY}
                }} else {{
                    {STORE}
                    {ELSE}
                }}""",
    "dup-if-inverted": f"""\
                if ({LOAD} == -1) {{
                    {STORE}
                    {ELSE}
                }} else {{
                    {STORE}
{BODY}
                }}""",
    "dup-comma": f"""\
                if ({LOAD} != -1) {{
                    (void) ({STORE[:-1]}, 0);
{BODY}
                }} else {{
                    (void) ({STORE[:-1]}, 0);
                    {ELSE}
                }}""",
    "goto-locked": f"""\
                if ({LOAD} == -1) {{
                    goto locked_track;
                }}
                {STORE}
{BODY}
                goto track_done;
locked_track:
                {STORE}
                {ELSE}
track_done:""",
    "goto-body": f"""\
                if ({LOAD} != -1) {{
                    goto unlocked_track;
                }}
                {STORE}
                {ELSE}
                goto track_done;
unlocked_track:
                {STORE}
{BODY}
track_done:""",
    "switch": f"""\
                switch ({LOAD}) {{
                case -1:
                    {STORE}
                    {ELSE}
                    break;
                default:
                    {STORE}
{BODY}
                    break;
                }}""",
    "ternary-void": f"""\
                ({LOAD} == -1)
                    ? (void) ({STORE[:-1]}, {ELSE[:-1]})
                    : (void) ({STORE[:-1]}, (void) 0);
                if ({LOAD} != -1) {{
{BODY}
                }}""",
}

if BASE.count(OLD) != 1:
    raise RuntimeError(f"expected one source block, got {BASE.count(OLD)}")


def reloc_masks(path: Path) -> dict[int, int]:
    output = subprocess.run(
        [OBJDUMP, "-r", path], check=True, capture_output=True, text=True
    ).stdout
    masks: dict[int, int] = {}
    for line in output.splitlines():
        match = re.match(r"([0-9a-f]+)\s+(R_MIPS_\S+)", line)
        if not match:
            continue
        offset = int(match.group(1), 16)
        kind = match.group(2)
        if kind in {"R_MIPS_LO16", "R_MIPS_HI16", "R_MIPS_GOT16", "R_MIPS_CALL16"}:
            masks[offset] = 0xFFFF0000
        elif kind == "R_MIPS_26":
            masks[offset] = 0xFC000000
    return masks


def words(path: Path) -> list[int]:
    output = subprocess.run(
        [OBJDUMP, "-d", path], check=True, capture_output=True, text=True
    ).stdout
    masks = reloc_masks(path)
    active = False
    result: list[int] = []
    for line in output.splitlines():
        if "<func_8008FF1C>:" in line:
            active = True
            continue
        if not active:
            continue
        match = re.match(r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+", line)
        if match:
            offset = int(match.group(1), 16)
            result.append(int(match.group(2), 16) & masks.get(offset, 0xFFFFFFFF))
        elif not line.strip():
            break
    return result


WANT = words(TARGET)


def evaluate(case: tuple[str, str]) -> tuple[int, int, int, str, str]:
    label, block = case
    source = BASE.replace(OLD, block, 1)
    # Remove the WIP's two holder-producing statements.  The load remains only
    # in the control form under test.
    source = source.replace(
        """\
                temp = (temp = gTrackSelectIDs[trackY][trackX]);
                selectedTrack = gTrackSelectIDs[trackY][trackX];
""",
        "",
        1,
    )
    with tempfile.TemporaryDirectory(prefix="menu-control-") as tmp:
        directory = Path(tmp)
        src = directory / "candidate.c"
        obj = directory / "candidate.o"
        src.write_text(source)
        obj.touch()
        proc = subprocess.run(
            ["bash", COMPILE, src, "-o", obj],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if proc.returncode:
            return (9999, -1, -1, label, proc.stderr[-1000:])
        got = words(obj)
    diffs = [i for i, (left, right) in enumerate(zip(got, WANT)) if left != right]
    full = len(diffs) + abs(len(got) - len(WANT))
    first = diffs[0] if diffs else min(len(got), len(WANT))
    return (full, first, len(got), label, block)


def main() -> None:
    workers = min(4, os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as executor:
        results = list(executor.map(evaluate, CASES.items()))
    results.sort(key=lambda row: (row[0], -row[1], row[3]))
    for full, first, length, label, detail in results:
        print(f"FW={full:4d} FIRST={first:3d} LEN={length:3d} {label}")
        if full == 0:
            print(detail)


if __name__ == "__main__":
    main()
