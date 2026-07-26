#!/usr/bin/env python3
"""Parallel scorer: score every v_*.txt in menuwork against target.o, write ledger."""
import re, subprocess, sys, os, tempfile, concurrent.futures, json

D = "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/menuwork"
REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
OBJDUMP = REPO + "/tools/binutils/mips64-elf-objdump"
BASE = open(D + "/base.c").read()

def build_src(variant, base=BASE):
    if variant.startswith("===DECLS==="):
        decls, variant = variant.split("===CODE===\n", 1)
        decls = decls[len("===DECLS===\n"):]
        variant = variant.rstrip("\n")
        dpat = re.compile(r"(void func_8008FF1C\( s32 updateRate\) \{\n).*?(\n    settings = get_settings\(\);)", re.S)
        dm = dpat.search(base)
        base = base[:dm.start()] + dm.group(1) + decls.rstrip("\n") + dm.group(2) + base[dm.end():]
    if variant.startswith("===FROM==="):
        _, rest = variant.split("===FROM===\n", 1)
        fr, rest = rest.split("\n===TO===\n", 1)
        to, code = rest.split("\n===CODE===\n", 1)
        i1 = base.index(fr); i2 = base.index(to, i1) + len(to)
        return base[:i1] + code + base[i2:]
    pat = re.compile(r"(levelName = level_name\(level_world_id\(trackY \+ 1\)\);\n).*?(\n\s*cur->trackName = level_name)", re.S)
    m = pat.search(base)
    return base[:m.start(1)] + m.group(1) + variant.rstrip("\n") + m.group(2) + base[m.end(2):]

def dump(obj):
    out = subprocess.run([OBJDUMP, "-d", obj], capture_output=True, text=True).stdout
    res, active = [], False
    for l in out.splitlines():
        if "<func_8008FF1C>:" in l: active = True; continue
        if active:
            mm = re.match(r"\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)\s*(.*)", l)
            if not mm:
                if l.strip() == "": break
                continue
            regs = re.findall(r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b|c1_fcsr)", mm.group(2))
            res.append(mm.group(1) + " " + ",".join(regs))
    return res

WANT = dump(D + "/target.o")

def score(path):
    name = os.path.basename(path)
    try:
        src = build_src(open(path).read().rstrip("\n"))
    except Exception as e:
        return (name, None, f"BUILD_SRC_FAIL {e}")
    with tempfile.TemporaryDirectory() as td:
        c = td + "/cand.c"; o = td + "/cand.o"
        open(c, "w").write(src)
        open(o, "a").close()
        r = subprocess.run(["bash", D + "/compile.sh", c, "-o", o], capture_output=True, text=True)
        if r.returncode != 0 or not os.path.exists(o):
            return (name, None, "COMPILE_FAIL")
        got = dump(o)
    n = sum(1 for g, w in zip(got, WANT) if g != w) + abs(len(got) - len(WANT))
    first = next((i for i, (g, w) in enumerate(zip(got, WANT)) if g != w), -1)
    return (name, n, f"first_diff={first} len={len(got)}/{len(WANT)}")

if __name__ == "__main__":
    import glob
    files = sorted(glob.glob(D + "/v_*.txt"))
    out = {}
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as ex:
        for name, n, info in ex.map(score, files):
            out[name] = (n, info)
            print(f"{name:24s} {n if n is not None else 'FAIL':>5} {info}", flush=True)
    json.dump(out, open(os.path.dirname(os.path.abspath(__file__)) + "/ledger.json", "w"), indent=1)
