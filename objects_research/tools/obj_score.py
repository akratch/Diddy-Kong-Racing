#!/usr/bin/env python3
"""Scorer for func_80017A18 candidates.

IMPORTANT (fixed 2026-07-24): an earlier version of this tool normalized
`N(sp)` -> `OFF(sp)`, which made it BLIND to whole-frame shifts. It scored
a -296 frame (48 wrong stack references) as if the offsets were correct,
and therefore ranked a genuinely better candidate as worse. Raw metrics
are now primary; the normalized edit distance is kept only as secondary
search guidance.

PRIMARY metrics (what actually counts):
  frame          must be -288
  exact-words    positional identical instruction words
  identical-asm  positional identical disassembly text

Usage: obj_score.py <file.c|file.o> [--blocks]
"""
import difflib, os, re, runpy, subprocess, sys, tempfile

SP = ("/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
      "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad")
TARGET = f"{SP}/work-objects/nonmatchings/func_80017A18/target.o"
OBJD = runpy.run_path(f"{SP}/iso_sweep.py")["OBJD"]
TARGET_FRAME = "-288"


def dump(obj):
    t = subprocess.run([OBJD, "-d", obj, "--disassemble=func_80017A18"],
                       capture_output=True, text=True).stdout
    ins = re.findall(r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.+)$", t, re.MULTILINE)
    m = re.search(r"addiu\s+sp,sp,(-\d+)", t)
    return ins, (m.group(1) if m else "?")


def norm(asm):
    """Secondary guidance only. Deliberately does NOT mask sp offsets."""
    asm = re.sub(r"\s+", " ", asm).strip()
    asm = re.sub(r"\b[0-9a-f]+\s+<[^>]+>", "ADDR", asm)
    return asm.replace("$", "")


def main():
    path = sys.argv[1]
    show_blocks = "--blocks" in sys.argv
    obj, tmp = path, None
    if path.endswith(".c"):
        fd, tmp = tempfile.mkstemp(suffix=".o", dir="/tmp"); os.close(fd)
        subprocess.run(["/tmp/objeval.sh", path, tmp], capture_output=True)
        if not os.path.exists(tmp) or os.path.getsize(tmp) == 0:
            print("COMPILE FAILED"); sys.exit(1)
        obj = tmp
    (tgt, _), (cand, frame) = dump(TARGET), dump(obj)
    n = min(len(tgt), len(cand))
    exact = sum(1 for i in range(n) if tgt[i][0] == cand[i][0])
    same_asm = sum(1 for i in range(n)
                   if re.sub(r"\s+", " ", tgt[i][1]) == re.sub(r"\s+", " ", cand[i][1]))
    flag = "" if frame == TARGET_FRAME else f"   <-- WRONG (target {TARGET_FRAME})"
    print(f"insns: target={len(tgt)} cand={len(cand)}  (delta {len(cand)-len(tgt):+d})")
    print(f"frame: {frame}{flag}")
    print(f"exact-words:   {exact}/{len(tgt)}")
    print(f"identical-asm: {same_asm}/{len(tgt)}")
    sm = difflib.SequenceMatcher(a=[norm(a) for _, a in tgt],
                                 b=[norm(a) for _, a in cand], autojunk=False)
    edit = sum(max(i2 - i1, j2 - j1)
               for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != "equal")
    print(f"(secondary) normalized edit distance: {edit}")
    if show_blocks:
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == "equal":
                continue
            print(f"\n  [{tag}] target[{i1}:{i2}] vs cand[{j1}:{j2}]")
            for k in range(i1, min(i2, i1 + 6)):
                print(f"      tgt {k}: {re.sub(chr(9),' ',tgt[k][1])}")
            for k in range(j1, min(j2, j1 + 6)):
                print(f"      cnd {k}: {re.sub(chr(9),' ',cand[k][1])}")
    if tmp:
        os.unlink(tmp)


if __name__ == "__main__":
    main()
