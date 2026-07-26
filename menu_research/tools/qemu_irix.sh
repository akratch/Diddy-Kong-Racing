#!/usr/bin/env bash
# Run the ORIGINAL IRIX uopt/ugen (not the static recompilation) under
# qemu-irix, and emit the pre-as1 assembly listing.
#
#   qemu_irix.sh <work-dir-with-unit.B-and-unit.T> [tag]
#
# The work dir must contain `unit.B` (cfe output) and `unit.T` (symbol table),
# both produced by `cc -K -c ...` with the project flags. The listing is
# written to <tag>.s in the same directory (default tag: irix).
#
# Requires: Docker running; the qemu-irix Debian package extracted; the
# original IRIX 5.3 tree (usr/lib/{uopt,ugen} plus lib/).
#
# Established result (2026-07-24): for func_8008FF1C the real IRIX output is
# line-for-line identical to the static recompilation, including the alias
# directives. See report_as1_directive.md §10.0.
set -e
W="$(cd "$1" && pwd)"
TAG="${2:-irix}"
QEMU="${QEMU_IRIX_DIR:-/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/f0723ef5-e988-4f13-9d5e-b1e03c34cfee/scratchpad/qemu}"
IRIX="${IRIX_ROOT:-/private/tmp/ido-static-recomp/ido/5.3}"

[ -x "$QEMU/usr/bin/qemu-irix" ] || {
  echo "qemu-irix not found at $QEMU/usr/bin/qemu-irix"
  echo "extract it with: mkdir -p <dir> && cd <dir> && tar xf /private/tmp/qemu-irix-deb/data.tar.xz"
  exit 1; }
[ -f "$IRIX/usr/lib/uopt" ] || { echo "IRIX tree not found at $IRIX"; exit 1; }
[ -f "$W/unit.B" ] && [ -f "$W/unit.T" ] || { echo "$W needs unit.B and unit.T"; exit 1; }

docker run --rm --platform linux/amd64 \
  -v "$QEMU":/q -v "$IRIX":/irix -v "$W":/w -w /w \
  debian:bookworm-slim sh -c "
    apt-get update -qq >/dev/null 2>&1
    apt-get install -y -qq libglib2.0-0 >/dev/null 2>&1
    /q/usr/bin/qemu-irix -L /irix /irix/usr/lib/uopt -G 0 -EB -g0 -O2 \
        unit.B $TAG.O -t unit.T $TAG.os
    /q/usr/bin/qemu-irix -L /irix /irix/usr/lib/ugen -G 0 -EB -g0 -O2 \
        $TAG.O -o $TAG.G -l $TAG.s -t unit.T -temp ${TAG}tmp
  "
echo "wrote $W/$TAG.s"
echo "--- alias directives in func_8008FF1C ---"
awk '/\.ent[ \t]+func_8008FF1C/,/\.end[ \t]+func_8008FF1C/' "$W/$TAG.s" \
  | grep -E '\.noalias' | sort | uniq -c || true
