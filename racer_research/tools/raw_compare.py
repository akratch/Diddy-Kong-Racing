#!/usr/bin/env python3
"""Raw instruction-word comparison against the target (true match metric).

Unlike verify_candidate.py's normalized score (which strips immediates,
stack offsets and branch targets), this counts instruction WORDS that
differ exactly. Relocated operands (lui/addiu/lw against unresolved
symbols) are masked, since those resolve at link time.
"""
import re, subprocess, sys, runpy, os, tempfile

SP = ("/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
      "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad")
TARGET = f"{SP}/work-racer/nonmatchings/func_80049794/target.o"
OBJD = runpy.run_path(f"{SP}/iso_sweep.py")["OBJD"]


def dump(obj):
    t = subprocess.run([OBJD, "-d", obj, "--disassemble=func_80049794"],
                       capture_output=True, text=True).stdout
    return re.findall(r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.+)$", t, re.MULTILINE)


def mask(word, asm):
    w = int(word, 16)
    op = w >> 26
    # mask 16-bit immediate for reloc-prone ops (lui/addiu/lw/sw against symbols)
    if op in (0x0F, 0x09, 0x23, 0x2B, 0x25, 0x21, 0x29, 0x28, 0x31, 0x39, 0x35, 0x3D):
        return w & 0xFFFF0000
    if op in (0x02, 0x03):           # j / jal
        return w & 0xFC000000
    if op in (0x04, 0x05, 0x06, 0x07, 0x01):  # branches
        return w & 0xFFFF0000
    return w


def main():
    path = sys.argv[1]
    obj, tmp = path, None
    if path.endswith(".c"):
        fd, tmp = tempfile.mkstemp(suffix=".o", dir="/tmp"); os.close(fd)
        subprocess.run(["/tmp/isoeval.sh", path, tmp], capture_output=True)
        obj = tmp
    tgt, cand = dump(TARGET), dump(obj)
    n = min(len(tgt), len(cand))
    exact = sum(1 for i in range(n) if tgt[i][0] == cand[i][0])
    masked = sum(1 for i in range(n) if mask(*tgt[i]) == mask(*cand[i]))
    diffs = [i for i in range(n) if mask(*tgt[i]) != mask(*cand[i])]
    print(f"insns: target={len(tgt)} cand={len(cand)}")
    print(f"raw-exact words:   {exact}/{len(tgt)}")
    print(f"reloc-masked match: {masked}/{len(tgt)}  (diff={len(diffs)})")
    print(f"masked diff indices: {diffs[:40]}{' ...' if len(diffs) > 40 else ''}")
    if tmp: os.unlink(tmp)


if __name__ == "__main__":
    main()
