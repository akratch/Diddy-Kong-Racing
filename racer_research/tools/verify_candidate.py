#!/usr/bin/env python3
"""Verify a func_80049794 candidate object (or source) against the target.

Usage:
  verify_candidate.py candidate.o
  verify_candidate.py candidate.c        (compiles via /tmp/isoeval.sh first)

Prints instruction count, normalized diff count, diff indices, FP histogram,
and the oracle-style instruction-word sha1 (ASCII hex concatenation).

Reference values for the 20-diff checkpoint
(racer_research/checkpoints/func_80049794_best_20.c):
  insns=2625  norm=20  sha1=ebfa69e218fc
  indices=[72, 1656, 1667, 1682..1685, 1687..1691, 1701..1704, 1706..1709]
Target FP histogram:
  f0=131 f2=66 f4=188 f6=188 f8=187 f10=188 f12=62 f14=50
  f16=8 f18=190 f20=74 f21=2
"""
import collections
import hashlib
import re
import subprocess
import sys
import tempfile
import os

SP = ("/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
      "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad")
OBJD = f"{SP}/work-racer/tools/ido-recomp/macos/../../../tools/objdump"
TARGET = f"{SP}/work-racer/nonmatchings/func_80049794/target.o"


def find_objdump():
    import runpy
    iso = runpy.run_path(f"{SP}/iso_sweep.py")
    return iso["OBJD"]


def dump(objd, obj):
    text = subprocess.run(
        [objd, "-d", obj, "--disassemble=func_80049794"],
        check=True, capture_output=True, text=True,
    ).stdout
    return re.findall(r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.+)$", text, re.MULTILINE)


def norm(asm):
    asm = re.sub(r"\b[0-9a-f]+\s+<[^>]+>", "ADDR", asm)
    asm = re.sub(r"-?\d+\((sp|\$sp)\)", "OFF(sp)", asm)
    asm = re.sub(r"\b-?(?:0x[0-9a-f]+|\d+)\b", "IMM", asm)
    return asm.replace("$", "")


def main():
    path = sys.argv[1]
    obj = path
    tmp = None
    if path.endswith(".c"):
        fd, tmp = tempfile.mkstemp(suffix=".o", dir="/tmp")
        os.close(fd)
        r = subprocess.run(["/tmp/isoeval.sh", path, tmp],
                           capture_output=True, text=True)
        if not os.path.exists(tmp) or os.path.getsize(tmp) == 0:
            print("COMPILE FAILED")
            print(r.stderr[-2000:])
            sys.exit(1)
        obj = tmp
    objd = find_objdump()
    tgt = dump(objd, TARGET)
    cand = dump(objd, obj)
    diffs = [i for i, (t, c) in enumerate(zip(tgt, cand))
             if norm(t[1]) != norm(c[1])]
    fp = collections.Counter(
        m for _, asm in cand
        for m in re.findall(r"\$(f(?:[02468]|1[02468]|2[01]))\b", asm))
    sha = hashlib.sha1("".join(w for w, _ in cand).encode()).hexdigest()[:12]
    print(f"insns={len(cand)} (target {len(tgt)})")
    print(f"norm={len(diffs) + abs(len(tgt) - len(cand))}")
    print(f"indices={diffs}")
    print(f"fp={dict(sorted(fp.items()))}")
    print(f"sha1={sha}")
    for i in diffs[:40]:
        print(f"  [{i}] target: {tgt[i][1]}")
        print(f"  [{i}] cand:   {cand[i][1]}")
    if tmp:
        os.unlink(tmp)


if __name__ == "__main__":
    main()
