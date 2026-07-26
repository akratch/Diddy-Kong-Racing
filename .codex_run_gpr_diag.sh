#!/bin/sh
set -eu

if [ "$#" -ne 3 ]; then
    echo "usage: $0 source.c output.o trace.log" >&2
    exit 2
fi

source_file=$1
output_file=$2
trace_file=$3
analysis_cc=/tmp/codex-ido-analysis/cc
work_racer=/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/work-racer

cd "$work_racer"
"$analysis_cc" -c -G 0 -non_shared -Xcpluscomm -nostdinc \
    -Wab,-r4300_mul \
    -D_FINALROM -DNDEBUG -DTARGET_N64 -DF3DDKR_GBI \
    -DVERSION_us_v80 -DANTI_TAMPER=1 \
    -DBUILD_VERSION=VERSION_G '-DBUILD_VERSION_STRING="2.0G"' \
    -D_MIPS_SZLONG=32 -DCIC_ID=6103 \
    -I . -I include -I include/libc -I include/PR -I include/sys \
    -I assets -I src -I libultra -I libultra/src/gu \
    -I libultra/src/libc -I libultra/src/io -I libultra/src/sc \
    -I libultra/src/audio -I libultra/src/os -I src/hasm \
    -I src/hasm/ido \
    -woff 838,649,624,835,516,550 -O2 -mips1 \
    -o "$output_file" "$source_file" 2>"$trace_file"
