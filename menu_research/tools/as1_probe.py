#!/usr/bin/env python3
"""as1-level oracle harness for func_8008FF1C.

Takes the kept ugen listing (unit.s), applies a named edit to the
noalias/load/store window, re-runs as0+as1, and reports the strict score.

Usage: as1_probe.py <workdir> <edit-name>
"""
import os
import re
import shutil
import subprocess
import sys

REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
IDO = REPO + "/tools/ido-recomp/macos"
TOOLS = REPO + "/menu_research/tools"

W = sys.argv[1]
EDIT = sys.argv[2]

src = open(os.path.join(W, "unit.s")).read()
lines = src.split("\n")

# locate the window inside func_8008FF1C: the .noalias before lh $10,0($17)
li = None
for i, l in enumerate(lines):
    if l.strip() == "lh\t$10, 0($17)" and lines[i - 1].strip().startswith(".noalias"):
        li = i
        break
if li is None:
    print("site not found")
    sys.exit(1)

na = li - 1                      # .noalias $17,$sp
beq = li + 1                     # beq $10, -1, $1128
# find the matching .alias line after the branch
al = None
for i in range(beq, beq + 6):
    if lines[i].strip().startswith(".alias"):
        al = i
        break

# the store is the last `sw $2, 0($16)` before the .noalias
st = None
for i in range(na - 1, na - 12, -1):
    if lines[i].strip() == "sw\t$2, 0($16)":
        st = i
        break


def apply(name):
    out = list(lines)
    if name == "control":
        pass
    elif name == "noalias_17_16":
        out[na] = "\t.noalias\t$17,$sp\n\t.noalias\t$17,$16"
        out[al] = "\t.alias\t$17,$16\n" + out[al]
    elif name == "noalias_16_17":
        out[na] = "\t.noalias\t$17,$sp\n\t.noalias\t$16,$17"
        out[al] = "\t.alias\t$16,$17\n" + out[al]
    elif name == "noalias_only_16":
        out[na] = "\t.noalias\t$17,$16"
        out[al] = "\t.alias\t$17,$16"
    elif name == "store_after_manual":
        # hand-sink the store below the load: proves the target stream is
        # reachable from this ucode if as1 were willing to move it
        s = out[st]
        del out[st]
        out.insert(li, s)  # indices shifted by -1 after delete -> lands after lh
    elif name == "noalias_before_store":
        out[st] = "\t.noalias\t$17,$16\n" + out[st]
        out[al] = "\t.alias\t$17,$16\n" + out[al]
    else:
        print("unknown edit", name)
        sys.exit(1)
    return "\n".join(out)


tag = EDIT
p = os.path.join(W, tag + ".s")
open(p, "w").write(apply(EDIT))
for f in (tag + ".G", tag + ".T", tag + ".o"):
    fp = os.path.join(W, f)
    if os.path.exists(fp):
        os.remove(fp)
r = subprocess.run([IDO + "/as0", "-G", "0", "-EB", "-g0", "-O2", tag + ".s",
                    "-o", tag + ".G", "-t", tag + ".T"],
                   cwd=W, capture_output=True, text=True)
if r.returncode != 0 or not os.path.exists(os.path.join(W, tag + ".G")):
    print("as0 FAIL:", r.stdout[-600:], r.stderr[-600:])
    sys.exit(1)
r = subprocess.run([IDO + "/as1", "-elf", "-G", "0", "-p0", "-EB", "-g0", "-O2",
                    tag + ".G", "-o", tag + ".o", "-t", tag + ".T"],
                   cwd=W, capture_output=True, text=True)
if r.returncode != 0 or not os.path.exists(os.path.join(W, tag + ".o")):
    print("as1 FAIL:", r.stdout[-600:], r.stderr[-600:])
    sys.exit(1)
print("=== " + EDIT + " ===")
subprocess.run([sys.executable, TOOLS + "/tryfw_obj.py", os.path.join(W, tag + ".o")])
