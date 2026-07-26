#!/usr/bin/env python3
"""Full-word verifier for func_8008FF1C candidates.
Usage: tryfw.py <variant_file> [menuwork_dir]
Reports BOTH metrics: the legacy mnemonic+register DIFFS (search guidance)
and the strict full-instruction-word DIFFS (required 0 for any match claim).
Both cand.o and target.o are unlinked same-TU objects, so raw words compare
validly (relocation fields are unresolved identically in both)."""
import re, subprocess, sys, os
D = sys.argv[2] if len(sys.argv) > 2 else os.path.dirname(os.path.abspath(sys.argv[1]))
REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
OBJDUMP = REPO + "/tools/binutils/mips64-elf-objdump"
sys.path.insert(0, REPO + "/menu_research/tools")
base = open(D + "/base.c").read()
variant = open(sys.argv[1]).read().rstrip("\n")
# same build_src logic as try.py/score_all.py
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
    src = base[:i1] + code + base[i2:]
else:
    pat = re.compile(r"(levelName = level_name\(level_world_id\(trackY \+ 1\)\);\n).*?(\n\s*cur->trackName = level_name)", re.S)
    m = pat.search(base)
    src = base[:m.start(1)] + m.group(1) + variant + m.group(2) + base[m.end(2):]
cand = D + "/cand_fw.c"; obj = D + "/cand_fw.o"
open(cand, "w").write(src); open(obj, "a").close()
r = subprocess.run(["bash", D + "/compile.sh", cand, "-o", obj], capture_output=True, text=True)
if r.returncode != 0:
    print("COMPILE FAIL"); print(r.stderr[-1200:]); sys.exit(1)
def relocmask(o):
    out = subprocess.run([OBJDUMP, "-r", o], capture_output=True, text=True).stdout
    masks = {}
    for l in out.splitlines():
        mm = re.match(r"([0-9a-f]+)\s+(R_MIPS_\S+)", l)
        if not mm: continue
        off = int(mm.group(1), 16); t = mm.group(2)
        if t in ("R_MIPS_LO16", "R_MIPS_HI16", "R_MIPS_GOT16", "R_MIPS_CALL16"):
            masks[off] = 0xFFFF0000
        elif t == "R_MIPS_26":
            masks[off] = 0xFC000000
    return masks
def dump(o):
    out = subprocess.run([OBJDUMP, "-d", o], capture_output=True, text=True).stdout
    masks = relocmask(o)
    words, meta, active, base_off = [], [], False, None
    for l in out.splitlines():
        if "<func_8008FF1C>:" in l:
            active = True
            hm = re.match(r"([0-9a-f]+) <", l)
            base_off = int(hm.group(1), 16) if hm else 0
            continue
        if active:
            mm = re.match(r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)", l)
            if not mm:
                if l.strip() == "": break
                continue
            off = int(mm.group(1), 16)
            w = int(mm.group(2), 16) & masks.get(off, 0xFFFFFFFF)
            words.append(f"{w:08x}"); meta.append(mm.group(3) + " " + mm.group(4))
    return words, meta
gw, gm = dump(obj); tw, tm = dump(D + "/target.o")
os.remove(obj)
fw = sum(1 for a, b in zip(gw, tw) if a != b) + abs(len(gw) - len(tw))
regre = re.compile(r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b|c1_fcsr)")
def sig(m): 
    mn, _, ops = m.partition(" ")
    return mn + " " + ",".join(regre.findall(ops))
lg = sum(1 for a, b in zip(gm, tm) if sig(a) != sig(b)) + abs(len(gm) - len(tm))
n = 0
for i, (a, b) in enumerate(zip(gw, tw)):
    if a != b:
        n += 1
        if n <= 12: print(f"{i:4d}: got {a} [{gm[i]}]  want {b} [{tm[i]}]")
print(f"LEN {len(gw)}/{len(tw)}  LEGACY_DIFFS: {lg}  FULLWORD_DIFFS: {fw}")
print("MATCH" if fw == 0 and len(gw) == len(tw) else "no match")
