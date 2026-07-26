#!/usr/bin/env bash
# Emit the pre-as1 assembly (ugen output) for a generated candidate .c
# using the exact project flags. This is the text as1 consumes.
#   passrun.sh <input.c> <output.s> [extra cc flags...]
set -e
INPUT="$(realpath "$1")"
OUTPUT="$2"; case "$OUTPUT" in /*) ;; *) OUTPUT="$PWD/$OUTPUT";; esac
shift 2
CC=/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/tools/ido-recomp/macos/cc
WORK="$(mktemp -d)"
cd /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing
cp "$INPUT" "$WORK/unit.c"
# -S stops after ugen; the .s lands next to the input basename in cwd
( cd "$WORK" && "$CC" -S -G 0 -non_shared -Xcpluscomm -nostdinc \
  -Wab,-r4300_mul -D_FINALROM -DNDEBUG -DTARGET_N64 -DF3DDKR_GBI \
  -DVERSION_us_v80 -DANTI_TAMPER=1 -DBUILD_VERSION=VERSION_G \
  '-DBUILD_VERSION_STRING="2.0G"' -D_MIPS_SZLONG=32 -DCIC_ID=6103 \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/include \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/include/libc \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/include/PR \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/include/sys \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/assets \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/src \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/libultra \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/libultra/src/gu \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/libultra/src/libc \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/libultra/src/io \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/libultra/src/sc \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/libultra/src/audio \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/libultra/src/os \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/src/hasm \
  -I /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing/src/hasm/ido \
  -fullwarn -Xfullwarn -woff 838,649,624,835,516 -O2 -mips1 "$@" unit.c )
cp "$WORK/unit.s" "$OUTPUT"
rm -rf "$WORK"
echo "wrote $OUTPUT"
