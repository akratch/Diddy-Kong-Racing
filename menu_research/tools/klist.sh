#!/usr/bin/env bash
# usage: klist.sh <variant.txt> <outname> — build cand.c via try.py logic, compile with -K, save full .s
set -e
MW=/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/menuwork
NEW=/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/84e018d6-3923-40cd-a174-5850defac48f/scratchpad/menu
W=$NEW/kwork_$2
mkdir -p $W
cd $MW
python3 - "$1" "$W/kcand.c" <<'PYEOF'
import re, sys, os
D = "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/menuwork"
base = open(D + "/base.c").read()
variant = open(sys.argv[1]).read().rstrip("\n")
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
open(sys.argv[2], "w").write(src)
PYEOF
cd $W
rm -f kcand.s kcand.o
REPO=/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing
$REPO/tools/ido-recomp/macos/cc -c -G 0 -non_shared -Xcpluscomm -nostdinc -Wab,-r4300_mul -D_FINALROM -DNDEBUG -DTARGET_N64 -DF3DDKR_GBI -DVERSION_us_v80 -DANTI_TAMPER=1 -DBUILD_VERSION=VERSION_G '-DBUILD_VERSION_STRING="2.0G"' -D_MIPS_SZLONG=32 -DCIC_ID=6103 -I $REPO -I $REPO/include -I $REPO/include/libc -I $REPO/include/PR -I $REPO/include/sys -I $REPO/assets -I $REPO/src -I $REPO/libultra -fullwarn -Xfullwarn -woff 838,649,624,835,516 -O2 -mips1 -K kcand.c -o kcand.o >/dev/null 2>&1 || true
cp kcand.s $NEW/klist_$2.s 2>/dev/null || echo "NO .s for $2"
