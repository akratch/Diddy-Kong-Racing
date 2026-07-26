#!/usr/bin/env python3
"""Scan retained isolated racer objects for exact target instruction regions."""

from __future__ import annotations

import pathlib
import re
import struct
import subprocess
import sys


TARGET = pathlib.Path(
    "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
    "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/work-racer/"
    "nonmatchings/func_80049794/target.o"
)
OBJDUMP = (
    "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
    "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/work-racer/"
    "tools/binutils/mips64-elf-objdump"
)
REGIONS = {
    "wave": (54, 55, 56, 59, 71, 72, 83, 85),
    "equality": (523,),
    "spin": (1182, 1184, 1185, 1187, 1191, 1192, 1195, 1196, 1199),
    "steer": (1417, 1419, 1422, 1428, 1431),
    "rotation": (
        1656,
        1667,
        1682,
        1683,
        1684,
        1685,
        1687,
        1688,
        1689,
        1690,
        1691,
        1701,
        1702,
        1703,
        1704,
        1706,
        1707,
        1708,
        1709,
    ),
}


def text_words(path: pathlib.Path) -> tuple[int, ...] | None:
    try:
        with path.open("rb") as source:
            header = source.read(52)
            if len(header) != 52 or header[:6] != b"\x7fELF\x01\x02":
                return None
            section_offset = struct.unpack_from(">I", header, 32)[0]
            section_size = struct.unpack_from(">H", header, 46)[0]
            section_count = struct.unpack_from(">H", header, 48)[0]
            string_index = struct.unpack_from(">H", header, 50)[0]
            source.seek(section_offset + string_index * section_size)
            string_header = source.read(section_size)
            string_offset, string_size = struct.unpack_from(
                ">II", string_header, 16
            )
            source.seek(string_offset)
            names = source.read(string_size)
            for index in range(section_count):
                source.seek(section_offset + index * section_size)
                section = source.read(section_size)
                name_offset = struct.unpack_from(">I", section, 0)[0]
                end = names.find(b"\0", name_offset)
                if names[name_offset:end] != b".text":
                    continue
                text_offset, text_size = struct.unpack_from(">II", section, 16)
                source.seek(text_offset)
                data = source.read(text_size)
                return struct.unpack(f">{len(data) // 4}I", data)
    except (OSError, struct.error):
        return None
    return None


def main() -> None:
    region_name = sys.argv[1] if len(sys.argv) > 1 else "rotation"
    limit = int(sys.argv[2]) if len(sys.argv) > 2 else 100
    region = REGIONS[region_name]
    target = text_words(TARGET)
    if target is None:
        raise SystemExit("could not read target text")
    disassembly = subprocess.run(
        [OBJDUMP, "-d", str(TARGET), "--disassemble=func_80049794"],
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    instruction_offsets = [
        int(address, 16) // 4
        for address in re.findall(
            r"^\s+([0-9a-f]+):\s+[0-9a-f]{8}\s+.+$",
            disassembly,
            re.MULTILINE,
        )
    ]
    region_offsets = tuple(instruction_offsets[index] for index in region)
    rows = []
    for path in pathlib.Path("/private/tmp").glob("codex*.o"):
        words = text_words(path)
        if words is None or len(words) < len(target):
            continue
        words = words[: len(target)]
        region_bad = sum(
            words[index] != target[index] for index in region_offsets
        )
        total_bad = sum(left != right for left, right in zip(words, target))
        source_exists = path.with_suffix(".c").exists()
        rows.append((region_bad, total_bad, not source_exists, path))
    rows.sort()
    for region_bad, total_bad, missing_source, path in rows[:limit]:
        print(
            f"region={region_bad:2d} total={total_bad:4d} "
            f"source={'no' if missing_source else 'yes'} {path}"
        )
    print(f"scanned={len(rows)} region={region_name}")


if __name__ == "__main__":
    main()
