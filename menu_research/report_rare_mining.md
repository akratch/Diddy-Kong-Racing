# Rare corpus mining for the pool-temp idiom (Codex family #4) — 2026-07-24

VERDICT: no matched Rare function demonstrates the pool-temp idiom, and
the exact DKR topology is shown — in a SECOND game, under the
byte-identical stock 5.3 ugen — to collapse into a web register.

Decisive corpus: GoldenEye 007 (local checkout, complete IDO 5.3 Rare
game; vendors the ORIGINAL IRIX ugen at tools/irix/root/usr/lib/ugen —
md5 9fcff937... IDENTICAL to the DKR reference). Across its 345
disassembled code objects: 0 pool-temp idioms (Class A and B), 26
web-collapse loads (Class C). Of 186 temp registers feeding a -1
compare anywhere in the game, ZERO are produced by a signed lh — the
compiler never leaves a compare-feeding signed halfword load in a pool
temp, corpus-wide.

THE COLLAPSED TWIN: GE's matched setupRoomTransformationMatrix
(src/game/unk_0BC530.c) has the exact DKR topology — s16 struct field
into a local, intervening stores, compare with -1 — and ships as
`lh s0,54(s0); li v0,-1; sw ra,28(sp); beq s0,v0; sw a0,112(sp)`:
the identical idiom SHAPE, collapsed into web s0. Same generator
binary, same topology, collapse — a second-game, source-anchored
confirmation of the collapse thesis. Its topology adapted into the DKR
frame scores 133 (the collapse basin), as predicted.

Other corpora: Banjo-Kazooie (100% matched source, IDO 5.3 recomp,
patchSG0001118 as1): 124 "-1" compares audited, none with the
signed-lh-across-store structure. JFG: no matched analog (menu still
GLOBAL_ASM). Perfect Dark: GCC lineage, out of scope. Blast Corps /
Mickey's Speedway: no public decomp repos found. No Rare project
vendors a ugen differing from 9fcff937 (third on-disk confirmation).

INTERPRETIVE WEIGHT: the DKR site is, on current evidence, a SINGLETON
across all measurable Rare shipped output — one pool-temp occurrence of
an idiom the same compiler binary demonstrably collapses everywhere
else, including in Rare's own matched code. This shifts posterior mass
toward site-specific anomaly (build-state oddity, nonstandard object)
and away from any systematic toolchain difference at Rare.

Artifacts: detectors + hits.json in session-84e018d6 scratchpad rare/;
GE-topology adaptation vM_ge_room.txt in menuwork.
