#!/usr/bin/env python3
"""Fast variant tester for func_8008FF1C.
Usage: try.py <variant_file>
variant_file contains the replacement text for the block between
'levelName = level_name(...);' and 'cur->trackName = level_name' lines.
Compares mnemonic+registers (immediates ignored) against target.o.
"""
import re, subprocess, sys, os

D = os.path.dirname(os.path.abspath(__file__))
REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
OBJDUMP = REPO + "/tools/binutils/mips64-elf-objdump"

base = open(D + "/base.c").read()
variant = open(sys.argv[1]).read().rstrip("\n")

# optional declaration-block override: variant file may start with
# ===DECLS=== ... ===CODE=== sections
if variant.startswith("===DECLS==="):
    decls, variant = variant.split("===CODE===\n", 1)
    decls = decls[len("===DECLS===\n"):]
    variant = variant.rstrip("\n")
    dpat = re.compile(r"(void func_8008FF1C\( s32 updateRate\) \{\n).*?(\n    settings = get_settings\(\);)", re.S)
    dm = dpat.search(base)
    assert dm, "decl anchor not found"
    base = base[:dm.start()] + dm.group(1) + decls.rstrip("\n") + dm.group(2) + base[dm.end():]

if variant.startswith("===FROM==="):
    _, rest = variant.split("===FROM===\n", 1)
    fr, rest = rest.split("\n===TO===\n", 1)
    to, code = rest.split("\n===CODE===\n", 1)
    i1 = base.index(fr)
    i2 = base.index(to, i1) + len(to)
    src = base[:i1] + code + base[i2:]
else:
    pat = re.compile(
        r"(levelName = level_name\(level_world_id\(trackY \+ 1\)\);\n).*?(\n\s*cur->trackName = level_name)",
        re.S)
    m = pat.search(base)
    assert m, "anchor not found"
    src = base[:m.start(1)] + m.group(1) + variant + m.group(2) + base[m.end(2):]
cand = D + "/cand.c"
open(cand, "w").write(src)

open(D + "/cand.o", "a").close()
r = subprocess.run(["bash", D + "/compile.sh", cand, "-o", D + "/cand.o"],
                   capture_output=True, text=True)
if not os.path.exists(D + "/cand.o") or r.returncode != 0:
    print("COMPILE FAIL"); print(r.stderr[-1500:]); sys.exit(1)

def dump(obj):
    out = subprocess.run([OBJDUMP, "-d", obj], capture_output=True, text=True).stdout
    lines = out.splitlines()
    res, active = [], False
    for l in lines:
        if "<func_8008FF1C>:" in l:
            active = True; continue
        if active:
            mm = re.match(r"\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)\s*(.*)", l)
            if not mm:
                if l.strip() == "": break
                continue
            mnem, ops = mm.group(1), mm.group(2)
            # strip immediates & branch targets: keep registers only
            regs = re.findall(r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b|c1_fcsr)", ops)
            res.append(mnem + " " + ",".join(regs))
    return res

got = dump(D + "/cand.o")
want = dump(D + "/target.o")
os.remove(D + "/cand.o")
n = 0
if len(got) != len(want):
    print(f"LENGTH {len(got)} vs {len(want)}")
for i, (g, w) in enumerate(zip(got, want)):
    if g != w:
        n += 1
        if n <= 12:
            print(f"{i:4d}: got [{g}]  want [{w}]")
print("DIFFS:", n + abs(len(got) - len(want)))
