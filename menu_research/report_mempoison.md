# Memory-poisoning sweep (H1c: environment-dependent codegen) — 2026-07-24

VERDICT: INSENSITIVE (ugen AND uopt). 13 poison patterns (0x00 control,
0xFF, 0xAA, 0x55, 0x01, rand:1..8) over every byte of freshly-allocated
guest heap AND the full 1MB guest stack gap (BSS kept zero per IRIX
semantics) produce WHOLE-OBJECT BYTE-IDENTICAL menu TU output in every
case. The site never flips (stays lh v1); DIFFS pinned at 133.
Poison verified to actually fire: ~2.13MB filled per ugen run (1MB
stack + 4 heap fills). Channel attribution (heap-only / stack-only /
both): all identical.

THE MAKEFILE SMOKING GUN RESOLVED: the recomp's "5.3 ugen relies on UB
stack reads / --conservative" comment refers to REGISTER-LIVENESS UB,
not guest-memory reads: --conservative (a) keeps 11,442 register
statements a strict liveness pass would elide (3417 fdead + 8025 bdead
in the non-conservative build), (b) makes callee-saved s0-s7/fp
file-scope statics persisting across calls, (c) seeds gp/ra=0x10000.
Decisive control: a NON-conservative ugen build produces byte-identical
.text for all 226 menu functions — the UB channel is empirically inert
for this TU and cannot reach the collapse decision.

Methodology note: an early apparent 29.7KB sensitivity was a .mdebug
source-path artifact (FDR embeds the path), value-independent;
path-matched reruns show 0-byte diffs. Fidelity verified env-unset
(cmp-clean vs stock; deterministic double-build).

HONEST RESIDUAL: the initial values of the static s0-s7/fp registers
(program-entry garbage on real IRIX) were not poisoned (requires
editing the generated ugen.c). The non-conservative experiment
(re-zeroing per function) is a strong negative proxy. A follow-up
could seed that one line from the env.

Meaning for the endgame: the anomaly is NOT a memory-state phenomenon
reproducible through the recomp; consistent with §12 (bit-stable across
five retail builds). H1's surviving form remains a genuinely different
binary/pass on the DKR build machine, or the <1-2% unconceived source
construct. Artifacts: ido-recomp-pub/libc_impl.c poison subsystem
(env-gated UGEN_MEMPOISON, fidelity-preserving), sweep harness at
session-84e018d6 scratchpad menu/mp/. Repo toolchain restored pristine.
