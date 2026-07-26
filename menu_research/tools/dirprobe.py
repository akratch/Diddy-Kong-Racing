#!/usr/bin/env python3
"""Directive probe for func_8008FF1C candidates.

Compiles a variant with -K, then reports:
  1. the alias directives ugen emitted in the load/store window,
  2. whether the store base register appears in a .noalias with the load base,
  3. the strict FULLWORD_DIFFS from as1's object.

Usage: dirprobe.py <variant_file> [--keep]
"""
import os
import re
import shutil
import subprocess
import sys
import tempfile

REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
IDO = REPO + "/tools/ido-recomp/macos"
D = REPO + "/menu_research/tools"

FLAGS = ["-G", "0", "-non_shared", "-Xcpluscomm", "-nostdinc", "-Wab,-r4300_mul",
         "-D_FINALROM", "-DNDEBUG", "-DTARGET_N64", "-DF3DDKR_GBI",
         "-DVERSION_us_v80", "-DANTI_TAMPER=1", "-DBUILD_VERSION=VERSION_G",
         '-DBUILD_VERSION_STRING="2.0G"', "-D_MIPS_SZLONG=32", "-DCIC_ID=6103"]
for inc in ["", "include", "include/libc", "include/PR", "include/sys", "assets",
            "src", "libultra", "libultra/src/gu", "libultra/src/libc",
            "libultra/src/io", "libultra/src/sc", "libultra/src/audio",
            "libultra/src/os", "src/hasm", "src/hasm/ido"]:
    FLAGS += ["-I", os.path.join(REPO, inc) if inc else REPO]
FLAGS += ["-fullwarn", "-Xfullwarn", "-woff", "838,649,624,835,516", "-O2", "-mips1"]


def build_src(variant_path):
    base = open(D + "/base.c").read()
    variant = open(variant_path).read().rstrip("\n")
    if variant.startswith("===DECLS==="):
        decls, variant = variant.split("===CODE===\n", 1)
        decls = decls[len("===DECLS===\n"):]
        variant = variant.rstrip("\n")
        dpat = re.compile(r"(void func_8008FF1C\( s32 updateRate\) \{\n).*?"
                          r"(\n    settings = get_settings\(\);)", re.S)
        dm = dpat.search(base)
        base = base[:dm.start()] + dm.group(1) + decls.rstrip("\n") + dm.group(2) + base[dm.end():]
    if variant.startswith("===FROM==="):
        _, rest = variant.split("===FROM===\n", 1)
        fr, rest = rest.split("\n===TO===\n", 1)
        to, code = rest.split("\n===CODE===\n", 1)
        i1 = base.index(fr)
        i2 = base.index(to, i1) + len(to)
        return base[:i1] + code + base[i2:]
    pat = re.compile(r"(levelName = level_name\(level_world_id\(trackY \+ 1\)\);\n).*?"
                     r"(\n\s*cur->trackName = level_name)", re.S)
    m = pat.search(base)
    return base[:m.start(1)] + m.group(1) + variant + m.group(2) + base[m.end(2):]


def run(variant_path, keep=False):
    W = tempfile.mkdtemp(prefix="dirprobe_")
    open(os.path.join(W, "unit.c"), "w").write(build_src(variant_path))
    extra = [a for a in sys.argv[2:] if a != "--keep"]
    r = subprocess.run([IDO + "/cc", "-K", "-c"] + FLAGS + extra + ["unit.c", "-o", "unit.o"],
                       cwd=W, capture_output=True, text=True)
    if r.stdout.strip() or r.stderr.strip():
        msg = (r.stdout + r.stderr)
        for ln in msg.splitlines():
            if "limit" in ln.lower() or "optimiz" in ln.lower():
                print("CC:", ln)
    sp = os.path.join(W, "unit.s")
    if not os.path.exists(sp):
        print("COMPILE FAIL")
        print((r.stdout + r.stderr)[-1500:])
        return
    # extract the target function from the listing
    lines = open(sp).read().split("\n")
    lo = hi = None
    for i, l in enumerate(lines):
        if re.match(r"\s*\.ent\s+func_8008FF1C\b", l):
            lo = i
        if lo is not None and re.match(r"\s*\.end\s+func_8008FF1C\b", l):
            hi = i
            break
    fn = lines[lo:hi] if lo is not None else []
    # find the condition load site
    site = None
    for i, l in enumerate(fn):
        if re.search(r"\bl[hbw]u?\s+\$\d+,\s*0\(\$(\d+)\)", l) and \
           "gTrackSelectIDs" in "\n".join(fn[max(0, i - 14):i]):
            site = i
    print("--- window ---")
    if site is not None:
        for l in fn[max(0, site - 8):site + 6]:
            if l.strip():
                print("   " + l)
    else:
        print("   (condition-load site not located)")
    dirs = [l.strip() for l in fn if ".noalias" in l or (".alias" in l and ".noalias" not in l)]
    print("--- all alias directives in function: %d ---" % len(dirs))
    for l in sorted(set(dirs)):
        print("   " + l)
    # assemble and score
    g = os.path.join(W, "unit.G")
    if os.path.exists(g):
        subprocess.run([IDO + "/as1", "-elf", "-G", "0", "-p0", "-EB", "-g0", "-O2",
                        "unit.G", "-o", "probe.o", "-t", "unit.T"],
                       cwd=W, capture_output=True, text=True)
        po = os.path.join(W, "probe.o")
        if os.path.exists(po):
            print("--- score ---")
            subprocess.run([sys.executable, D + "/tryfw_obj.py", po])
    if keep:
        print("workdir:", W)
    else:
        shutil.rmtree(W)


if __name__ == "__main__":
    run(sys.argv[1], "--keep" in sys.argv)
