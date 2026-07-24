#!/usr/bin/env python3
"""decomp.me-equivalent scorer for func_80017A18 candidates.

Replicates tools/asm-differ/diff.py's scoring model, which is what
decomp.me reports:

    insertion   = 100 per instruction
    deletion    = 100 per instruction
    reordering  =  60 (an insert+delete pair with an identical scorable line)
    regalloc    =   5 per differing operand field on a same-mnemonic pair
    stackdiff   =   1 * abs(sp-offset difference)   <-- NOT flat!

max_score = len(target) * 100, and percent = 100 * (1 - score/max_score).

The stack rule matters a lot here: a frame 8 bytes wrong costs 8 penalty
on EVERY sp-relative instruction, which is why frame size dominates.

Usage: dscore.py <file.c|file.o> [...]
"""
import difflib, os, re, runpy, subprocess, sys, tempfile
from collections import Counter

SP = ("/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
      "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad")
TARGET = f"{SP}/work-objects/nonmatchings/func_80017A18/target.o"
OBJD = runpy.run_path(f"{SP}/iso_sweep.py")["OBJD"]
RE_SPREL = re.compile(r"(-?[0-9]+|0x[0-9a-f]+)\(sp\)")


def dump(obj):
    t = subprocess.run([OBJD, "-d", obj, "--disassemble=func_80017A18"],
                       capture_output=True, text=True).stdout
    out = []
    for _, a in re.findall(r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.+)$", t, re.MULTILINE):
        a = re.sub(r"\s+", " ", a).strip()
        a = re.sub(r"\b[0-9a-f]{4,}\s+<[^>]+>", "TGT", a)   # branch/call targets
        out.append(a)
    return out


def mnemonic(l):
    return l.split()[0]


def sameline_penalty(old, new):
    """Returns (stack_penalty, regalloc_penalty)."""
    if old == new:
        return 0, 0
    sp_pen = 0
    ignore_last = False
    o_sp, n_sp = RE_SPREL.search(old), RE_SPREL.search(new)
    if o_sp and n_sp:
        sp_pen += abs(int(o_sp.group(1), 0) - int(n_sp.group(1), 0))
        ignore_last = True
    op = old.split(None, 1)
    np_ = new.split(None, 1)
    of = op[1].split(",") if len(op) > 1 else []
    nf = np_[1].split(",") if len(np_) > 1 else []
    if ignore_last:
        of, nf = of[:-1], nf[:-1]
    reg_pen = sum(1 for a, b in zip(of, nf) if a != b) + abs(len(of) - len(nf))
    return sp_pen, reg_pen


def score(path):
    obj, tmp = path, None
    if path.endswith(".c"):
        fd, tmp = tempfile.mkstemp(suffix=".o", dir="/tmp"); os.close(fd)
        subprocess.run(["/tmp/objeval.sh", path, tmp], capture_output=True)
        if not os.path.exists(tmp) or os.path.getsize(tmp) == 0:
            print(f"{os.path.basename(path):46} COMPILE FAILED"); return None
        obj = tmp
    tgt, cand = dump(TARGET), dump(obj)
    sm = difflib.SequenceMatcher(a=[mnemonic(x) for x in tgt],
                                 b=[mnemonic(x) for x in cand], autojunk=False)
    stack = reg = 0
    ins, dele = [], []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            for k in range(i2 - i1):
                s, r = sameline_penalty(tgt[i1 + k], cand[j1 + k])
                stack += s; reg += r
        else:
            dele.extend(tgt[i1:i2])
            ins.extend(cand[j1:j2])
    ic, dc = Counter(ins), Counter(dele)
    n_ins = n_del = n_reo = 0
    for item in set(ic) | set(dc):
        a, b = ic[item], dc[item]
        common = min(a, b)
        n_ins += a - common
        n_del += b - common
        n_reo += common
    total = stack * 1 + reg * 5 + n_reo * 60 + n_ins * 100 + n_del * 100
    maxs = len(tgt) * 100
    pct = 100.0 * (1 - total / maxs)
    print(f"{os.path.basename(path):46} score={total:>6}  {pct:6.2f}%   "
          f"[ins={n_ins} del={n_del} reord={n_reo} reg={reg} stack={stack}]  insns={len(cand)}")
    if tmp: os.unlink(tmp)
    return total


if __name__ == "__main__":
    for p in sys.argv[1:]:
        score(p)
