#!/usr/bin/env bash
# utrace.sh <kwork_name> <out.lst> — compile the kcand.c in kwork_<name> with ucode listing
SP=/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad
NEW=/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/84e018d6-3923-40cd-a174-5850defac48f/scratchpad/menu
REPO=/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing
W=$NEW/kwork_$1
cd $W
rm -f trace_u.lst
$SP/ido-traced-menu/cc -c -G 0 -non_shared -Xcpluscomm -nostdinc -Wab,-r4300_mul \
 -D_FINALROM -DNDEBUG -DTARGET_N64 -DF3DDKR_GBI -DVERSION_us_v80 -DANTI_TAMPER=1 \
 -DBUILD_VERSION=VERSION_G '-DBUILD_VERSION_STRING="2.0G"' -D_MIPS_SZLONG=32 -DCIC_ID=6103 \
 -I $REPO -I $REPO/include -I $REPO/include/libc -I $REPO/include/PR -I $REPO/include/sys \
 -I $REPO/assets -I $REPO/src -I $REPO/libultra \
 -woff 838,649,624,835,516,550 -O2 -mips1 -Wo,-l,$W/trace_u.lst -Wo,-zdbug:5 -o $W/tcand.o kcand.c 2>$W/trace_err.txt
echo "exit=$? lst=$(stat -f%z $W/trace_u.lst 2>/dev/null) obj=$(stat -f%z $W/tcand.o 2>/dev/null)"
cp $W/trace_u.lst $NEW/$2 2>/dev/null
