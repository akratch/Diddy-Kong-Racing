#!/usr/bin/env python3
"""Report the ugen temp free-queue state entering the rotation region.

Baseline: [t6 t4 t8 t9 t7 t3 t5]   Target: [t4 t8 t9 t7 t6 t3 t5]
Also prints raw-word diff count vs target.
"""
import re, subprocess, sys, os, tempfile, runpy
SP = ("/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
      "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad")
NAME = {11:'t3',12:'t4',13:'t5',14:'t6',15:'t7',24:'t8',25:'t9'}
TARGET_Q = ['t4','t8','t9','t7','t6','t3','t5']

def probe(csrc):
    fd, obj = tempfile.mkstemp(suffix=".o", dir="/tmp"); os.close(fd)
    fd2, log = tempfile.mkstemp(suffix=".log", dir="/tmp"); os.close(fd2)
    env = dict(os.environ, CODEX_UGEN_TRACE="1")
    with open(log, "w") as lf:
        subprocess.run(["/tmp/traceeval.sh", csrc, obj], stderr=lf, env=env)
    # region = first alloc at a source line whose text is the R_TRIG arm block
    txt = open(log, errors="ignore").read().splitlines()
    src = open(csrc).read().splitlines()
    region_line = None
    for i, l in enumerate(src):
        if "messed up t registers" in l:
            region_line = i + 2   # the if() right after the comment
            break
    if region_line is None:
        for i, l in enumerate(src):
            if "* 19) * updateRate" in l or "* 19 * updateRate" in l:
                region_line = i - 1; break
    q = None
    for ln in txt:
        m = re.search(r"CODEX-QUEUE \S+ line=(\d+) q:((?: \d+)*) end", ln)
        if m:
            if int(m.group(1)) >= region_line:
                q = [NAME.get(int(x), str(x)) for x in m.group(2).split()]
                break
    os.unlink(log)
    return q, obj

def raw_diff(obj):
    O = runpy.run_path(f"{SP}/iso_sweep.py")["OBJD"]
    def dump(o):
        t = subprocess.run([O,"-d",o,"--disassemble=func_80049794"],
                           capture_output=True,text=True).stdout
        return re.findall(r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s+(.+)$",t,re.MULTILINE)
    tgt = dump(f"{SP}/work-racer/nonmatchings/func_80049794/target.o"); c = dump(obj)
    if len(c) != len(tgt): return f"INSNS {len(c)}"
    def mask(w, asm):
        v = int(w,16); op = v>>26
        if op in (0x0F,0x09,0x23,0x2B,0x25,0x21,0x29,0x28,0x31,0x39,0x35,0x3D): return v & 0xFFFF0000
        if op in (0x02,0x03): return v & 0xFC000000
        if op in (0x04,0x05,0x06,0x07,0x01): return v & 0xFFFF0000
        return v
    return sum(1 for i in range(len(tgt)) if mask(*tgt[i]) != mask(*c[i]))

if __name__ == "__main__":
    for f in sys.argv[1:]:
        q, obj = probe(f)
        d = raw_diff(obj) if os.path.getsize(obj) else "FAIL"
        hit = "  <== TARGET QUEUE" if q == TARGET_Q else ""
        print(f"{os.path.basename(f):28} diff={str(d):>6}  q={q}{hit}")
        os.unlink(obj)
