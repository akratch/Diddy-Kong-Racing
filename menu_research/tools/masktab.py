#!/usr/bin/env python3
"""For each mask count 1-6 (cast index form), compile -K and print the allocation table."""
import subprocess, sys, os, re
SP = "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad"
MW = SP + "/menuwork"
NEW = os.path.dirname(os.path.abspath(__file__))
zz1 = open(MW + "/v_zz1.txt").read()
mask = "                pad = pad & 0xFFFFFFFFFFFFFFFF;\n"
anchor = mask + mask

def variant(n):  # n = total masks
    if n == 1: return zz1.replace(anchor, "", 1)
    return zz1.replace(anchor, mask * (n - 1), 1)

def window(sfile):
    txt = open(sfile).read().splitlines()
    start = None
    for i, l in enumerate(txt):
        if "pad = (gTrackSelectIDs[pad][trackX])" in l: start = i - 2; break
    if start is None: return ["NO WINDOW"]
    out = []
    for l in txt[start:start + 90]:
        if re.match(r"\s*\.(loc|livereg|set)", l): continue
        out.append(l)
        if "courseFlagsPtr" in l: break
    return out

for n in range(1, 7):
    vf = NEW + f"/tmp_mask{n}.txt"
    open(vf, "w").write(variant(n))
    subprocess.run(["bash", NEW + "/klist.sh", vf, f"mask{n}"], capture_output=True)
    print(f"#################### {n} masks")
    print("\n".join(window(NEW + f"/klist_mask{n}.s")))
