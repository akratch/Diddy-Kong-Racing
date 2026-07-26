#!/usr/bin/env bash
INPUT="$(realpath "$1")"
OUTPUT="$(realpath "$3")"
cd /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing
tools/ido-recomp/macos/cc -c -G 0 -non_shared -verbose -Xcpluscomm -nostdinc -Wab,-r4300_mul -D_FINALROM -DNDEBUG -DTARGET_N64 -DF3DDKR_GBI -DVERSION_us_v80 -DANTI_TAMPER=1 -DBUILD_VERSION=VERSION_G '-DBUILD_VERSION_STRING="2.0G"' -D_MIPS_SZLONG=32 -DCIC_ID=6103 -I . -I include -I include/libc -I include/PR -I include/sys -I assets -I src -I libultra -I libultra/src/gu -I libultra/src/libc -I libultra/src/io -I libultra/src/sc -I libultra/src/audio -I libultra/src/os -I src/hasm -I src/hasm/ido -fullwarn -Xfullwarn -woff 838,649,624,835,516 -O2 -mips1 "$INPUT" -o "$OUTPUT"