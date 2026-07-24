#!/usr/bin/env python3
"""Correct scorer for func_80017A18 candidates.

Ranking metrics, in priority order:
  1. structural delta  - mnemonic-level edit distance (wrong/misordered OPCODES).
                         This is what decomp.me's score mostly reflects and it is
                         the expensive residual. Must reach 0 first.
  2. insns             - must be 279
  3. frame             - must be -288
  4. aligned-identical - full instruction text agreement after alignment
  5. exact-words       - positional raw words (ONLY meaningful at 279 insns)

Two earlier mistakes this tool exists to prevent:
  * normalizing N(sp) hides whole-frame shifts (48 wrong stack refs scored as correct)
  * positional comparison is invalid when instruction counts differ, and will
    rank a structurally superior source as worse.

Usage: score.py <file.c|file.o> [file2 ...] [--blocks]
"""
import difflib, os, re, runpy, subprocess, sys, tempfile

SP = ("/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
      "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad")
TARGET = f"{SP}/work-objects/nonmatchings/func_80017A18/target.o"
OBJD = runpy.run_path(f"{SP}/iso_sweep.py")["OBJD"]


def dump(obj):
    t = subprocess.run([OBJD, "-d", obj, "--disassemble=func_80017A18"],
                       capture_output=True, text=True).stdout
    ins = [(w, re.sub(r"\s+", " ", a).strip())
           for w, a in re.findall(r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.+)$", t, re.MULTILINE)]
    m = re.search(r"addiu\s+sp,sp,(-\d+)", t)
    return ins, (m.group(1) if m else "?")


def mnem(a):
    return a.split()[0]


def score(path, show_blocks=False):
    obj, tmp = path, None
    if path.endswith(".c"):
        fd, tmp = tempfile.mkstemp(suffix=".o", dir="/tmp"); os.close(fd)
        subprocess.run(["/tmp/objeval.sh", path, tmp], capture_output=True)
        if not os.path.exists(tmp) or os.path.getsize(tmp) == 0:
            print(f"{os.path.basename(path):40} COMPILE FAILED")
            return
        obj = tmp
    tgt, _ = dump(TARGET)
    cand, frame = dump(obj)

    sm_m = difflib.SequenceMatcher(a=[mnem(a) for _, a in tgt],
                                   b=[mnem(a) for _, a in cand], autojunk=False)
    struct = sum(max(i2 - i1, j2 - j1)
                 for tag, i1, i2, j1, j2 in sm_m.get_opcodes() if tag != "equal")
    sm_f = difflib.SequenceMatcher(a=[a for _, a in tgt],
                                   b=[a for _, a in cand], autojunk=False)
    aligned = sum(i2 - i1 for tag, i1, i2, _, _ in sm_f.get_opcodes() if tag == "equal")
    exact = "n/a"
    if len(cand) == len(tgt):
        exact = f"{sum(1 for i in range(len(tgt)) if tgt[i][0] == cand[i][0])}/{len(tgt)}"

    fflag = "" if frame == "-288" else "!"
    iflag = "" if len(cand) == len(tgt) else "!"
    print(f"{os.path.basename(path):40} struct={struct:>3}  insns={len(cand)}{iflag:1} "
          f"frame={frame}{fflag:1}  aligned={aligned}/{len(tgt)}  exact={exact}")

    if show_blocks:
        for tag, i1, i2, j1, j2 in sm_m.get_opcodes():
            if tag == "equal":
                continue
            print(f"   [{tag}] tgt[{i1}:{i2}] cand[{j1}:{j2}]")
            for k in range(i1, min(i2, i1 + 6)):
                print(f"       tgt {k}: {tgt[k][1]}")
            for k in range(j1, min(j2, j1 + 6)):
                print(f"       cnd {k}: {cand[k][1]}")
    if tmp:
        os.unlink(tmp)


if __name__ == "__main__":
    blocks = "--blocks" in sys.argv
    for p in [a for a in sys.argv[1:] if not a.startswith("--")]:
        score(p, blocks)
