#!/usr/bin/env python3
"""Strict full-word verifier that takes a prebuilt .o instead of a variant.
Usage: tryfw_obj.py <candidate.o> [menuwork_dir]"""
import re, subprocess, sys, os
D = sys.argv[2] if len(sys.argv) > 2 else "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/menu_research/tools"
REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
OBJDUMP = REPO + "/tools/binutils/mips64-elf-objdump"
obj = sys.argv[1]


def relocmask(o):
    out = subprocess.run([OBJDUMP, "-r", o], capture_output=True, text=True).stdout
    masks = {}
    for l in out.splitlines():
        mm = re.match(r"([0-9a-f]+)\s+(R_MIPS_\S+)", l)
        if not mm:
            continue
        off = int(mm.group(1), 16)
        t = mm.group(2)
        if t in ("R_MIPS_LO16", "R_MIPS_HI16", "R_MIPS_GOT16", "R_MIPS_CALL16"):
            masks[off] = 0xFFFF0000
        elif t == "R_MIPS_26":
            masks[off] = 0xFC000000
    return masks


def dump(o):
    out = subprocess.run([OBJDUMP, "-d", o], capture_output=True, text=True).stdout
    masks = relocmask(o)
    words, meta, active = [], [], False
    for l in out.splitlines():
        if "<func_8008FF1C>:" in l:
            active = True
            continue
        if active:
            mm = re.match(r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)", l)
            if not mm:
                if l.strip() == "":
                    break
                continue
            off = int(mm.group(1), 16)
            w = int(mm.group(2), 16) & masks.get(off, 0xFFFFFFFF)
            words.append(f"{w:08x}")
            meta.append(mm.group(3) + " " + mm.group(4))
    return words, meta


gw, gm = dump(obj)
tw, tm = dump(D + "/target.o")
fw = sum(1 for a, b in zip(gw, tw) if a != b) + abs(len(gw) - len(tw))
n = 0
for i, (a, b) in enumerate(zip(gw, tw)):
    if a != b:
        n += 1
        if n <= 12:
            print(f"{i:4d}: got {a} [{gm[i]}]  want {b} [{tm[i]}]")
print(f"LEN {len(gw)}/{len(tw)}  FULLWORD_DIFFS: {fw}")
print("MATCH" if fw == 0 and len(gw) == len(tw) else "no match")
