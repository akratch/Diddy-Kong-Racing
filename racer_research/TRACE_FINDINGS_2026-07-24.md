# func_80049794 allocator-trace findings — 2026-07-24 session

Continuation of `RACER_FINAL_MILE_HANDOFF.md`. This file records the first
results of the mechanism-led phase (Phases 1–2 of the handoff plan). All
claims below are measured, not inferred, unless marked as hypothesis.

## 1. Checkpoint re-verification

`racer_research/checkpoints/func_80049794_best_20.c`
(SHA-256 `28b4638b…`) was recompiled from scratch through `/tmp/isoeval.sh`:

```text
insns=2625 norm=20 sha1=ebfa69e218fc
indices=[72, 1656, 1667, 1682-1685, 1687-1691, 1701-1704, 1706-1709]
FP histogram byte-identical to target
```

Note: the instruction-word SHA1 is over the *ASCII hex concatenation* of the
instruction words (see `codex_racer_oracle.py` line 123), not raw bytes.

New shared scoring tool: `racer_research/tools/verify_candidate.py`
(takes a .c or .o; prints insns/norm/indices/FP histogram/sha1).

## 2. Trace instrumentation repaired (handoff Phase 1 — DONE)

The failed `UGEN_ROTTRACE` build is superseded. The recompiled-ugen source
`/private/tmp/ido-static-recomp/build/5.3/ugen.c` now has ALL diagnostic
output env-gated:

- `CODEX_UGEN_TRACE=1` → GET/ALLOC/FREE/EVAL/APPEND/REMOVE-HEAD events plus
  full free-queue dumps at every alloc/free/get boundary.
- `CODEX_UGEN_ROT=1` → the old one-shot line-765/766 hold/reinsert hack
  (off by default; kept for reference).

Toolchain: `/tmp/codex-ido-trace/` (stock repo toolchain + this ugen).
Driver: `/tmp/traceeval.sh in.c out.o` (same flags as isoeval).

Verification: with no env vars set, stderr is empty (0 bytes) and the
checkpoint compiles to the identical object (`sha1=ebfa69e218fc`). The
tracing therefore observes without perturbing.

Rebuild recipe:
`cd /private/tmp/ido-static-recomp && make VERSION=5.3 build/5.3/out/ugen`
then copy `build/5.3/out/ugen` over `/tmp/codex-ido-trace/ugen`.

## 3. Measured free-queue mechanism (the rotation residual, 19 diffs)

Register numbering: t3=11 t4=12 t5=13 t6=14 t7=15 t8=24 t9=25.

- The integer expression-temp free list at emulated `0x10019da4` holds
  exactly {11,12,13,14,15,24,25} in this function and behaves as a strict
  FIFO: `get_one_free_reg` removes the HEAD; when a temp's last use is
  emitted, `free_reg` APPENDs it to the TAIL.
- `f_get_one_reg` (specific-register requests) was observed requesting only
  regs 2–10 (v0/v1/a0–a3/t0–t2) across the whole function — it never
  perturbs the t3–t9 queue in the current compile.
- Queue evolution measured from source line 743 to the mismatch region
  (line 766ff): exactly 7 temp allocations occur —
  line 743: 14,12,24 (the three `||` operand tests of
  `if (!(gCurrentRacerInput & R_TRIG) || racer->groundedWheels == 0 || racer->zipperDirCorrection != 0)`),
  line 747: 25, line 751: 15,11 (the two operand loads of
  `if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->raceFinished == FALSE)`),
  line 763: 13. Each is freed immediately, so the queue performs one full
  rotation and re-enters the rotation region as
  `[14 12 24 25 15 11 13]` = `[t6 t4 t8 t9 t7 t3 t5]`.
- The target requires entry order `[12 24 25 15 14 11 13]` =
  `[t4 t8 t9 t7 t6 t3 t5]` (independently matches handoff §8.2).

**Key structural fact:** the two orders are NOT cyclic rotations of each
other. Because allocs only take the head and frees only append to the tail,
no arithmetic/statement respelling that keeps the same temp events can ever
produce the target order. The ONLY mechanisms that can are:

1. the t6 temp allocated at line 743 (allocator serial 229, the
   `andi t6,v0,0x10` R_TRIG mask; the mask value itself is CSE'd into a
   v0-web that dies at line 766) being FREED LATER — specifically in the
   window between the `gCurrentPlayerIndex` load (temp 15) and the
   `racer->raceFinished` load (temp 11) at line 751; or
2. a specific-register GET pulling a queue register from the middle
   (never observed for this class); or
3. different compiler point behavior in the free/dec-usage path.

Simulation of mechanism 1 reproduces the required entry order exactly:

```text
entry [14 12 24 25 15 11 13]; 14 allocated at 743 and HELD
743: 12,24 alloc+free  -> [25 15 11 13 12 24]
747: 25                -> [15 11 13 12 24 25]
751: 15                -> [11 13 12 24 25 15]
     t6 dies here      -> [11 13 12 24 25 15 14]
751: 11                -> [13 12 24 25 15 14 11]
763: 13                -> [12 24 25 15 14 11 13]  == target order
```

Combined with the handoff's forced-serial proof (§8.1: forcing serials
236–257 makes the whole region exact), delaying that ONE free event is
sufficient to clear all 19 rotation diffs.

## 4. Falsified: optimizer-erased uses cannot move ugen temp frees

Three variants inserted an erased `if (gCurrentRacerInput & R_TRIG) {}`
(a) between the two operand tests of line 751 (split into nested ifs),
(b) before the line-751 if, (c) inside its body. All three compiled
**byte-identical** to the checkpoint (`sha1=ebfa69e218fc`) and left zero
events in the ugen trace. Conclusion: empty-if probes are folded before
ugen; they can shape uopt priorities (wave loop) but can NEVER re-time
ugen's temp releases. The rotation fix requires a construct that survives
into ugen's ucode stream as a use of the mask temp while emitting nothing
(e.g. a coalesced move), or a compiler point difference (handoff Theory C).

## 5. WAVE SOLVED — norm 20 → 19 (2026-07-24, later same day)

`racer_research/checkpoints/func_80049794_best_19_wave_win.c`
(SHA-256 `970b22ed…`) verifies at insns=2625, norm=19,
sha1=`e95892dd53eb`, indices = the 19 rotation diffs only. Index 72 and the
whole wave region now match. Winning combination (all three required):

1. direct guard `var_a0 >= 0` (backedge tests the counter → `bltz a0`);
2. once-run dead double-assign `var_t9 = (var_t9 = gRacerWaveCount - 1);`
   into a dead-slot local (zero instructions; perturbs the interfering
   stack-slot/coloring order — bit 218 — decoupling the counter fix from the
   v0/v1 swap);
3. exactly 3 empty `if (gRacerWaveCount - 1) {}` body tests.

Full history in `wave_campaign_2026-07-24.md`. Measured coloring facts:
endpoint priority = 2/uses (N pinned at 2 for all zero-cost levers);
competitors sit in (0.1111, 0.1176); the coupling flips at one discrete
threshold; the double-assign moves the third interfering range instead of
the endpoint priority.

## 6. Rotation: allocator-map + falsifications + hold oracle

- ugen map (`ugen_allocator_map_2026-07-24.md`): frees are usage-count
  gated (reg-table +4, initialized from node use count +20); non-final
  consumers' free calls are silent; no-emit consumer paths exist (memoized
  node re-visits, case-97 unary fusion).
- Microcase campaign (`rotation_microcase_campaign_2026-07-24.md`):
  DECISIVE NEGATIVE at expression level — any use-count>1 value is routed
  to the GET class (v0/v1/a*/t0-t2), never to the t3-t9 FIFO queue; the
  FIFO class carries only use-count-1 scratch. 20 constructs tested: every
  one either byte-identical (folded before ugen) or emission-changing.
- Queue-replay analysis (this file's §3 model, formalized as a replay of
  472 pops/frees): the cyclic-order mismatch admits exactly two short
  single edits — delaying the line-738 R_TRIG mask free past the
  steerVisualRotation statement, or delaying the line-745 mask free into
  the line-753 `&&` window. Ternary/embedding respellings of the 738-743
  region either compile byte-identical (no ugen effect) or explode.
- HOLD ORACLE (env-gated in the trace ugen): CODEX_UGEN_HOLD_REG=14
  CODEX_UGEN_HOLD_NTH=34 CODEX_UGEN_HOLD_POPS=4 delays that one line-745
  release; entry queue becomes the target's [t4 t8 t9 t7 t6 t3 t5].
  Result: allocation serials 236-242 then match the target exactly, but
  the cascade diverges inside the arms (net norm=164). Conclusion: the
  doc §8.1 serial map requires BOTH the entry-queue change AND a different
  free interleaving inside the rotation arms — i.e. Rare's arm statements
  have a different tree shape than our three-statement reconstruction
  (target holds the arm-1 result temp t7 to the final sh; re-pops t6
  immediately at serial 243).

## 6b. Arm-respell closure + FIFO stream invariance (later same day)

- Arm respell campaign (`rotation_arm_respell_2026-07-24.md`): 13
  structurally distinct opcode-preserving spellings all produce the
  IDENTICAL dataflow graph → identical op-sequence (IDO normalizes comma
  operators, named temps, reordering, explicit hoists). All 5040 entry
  queue permutations are infeasible under our arm op-sequence. The target
  needs a different op-sequence: all 7 region temps long-lived, freed
  just-in-time; the two updateRate reloads live ACROSS the branch on
  t3/t4 with cross-arm consumption.
- FIFO STREAM INVARIANCE (measured): deferred-free policies (flush on
  line-change or on-empty; 420 deferral events) produce a BYTE-IDENTICAL
  object. A FIFO's outcome depends only on append ORDER, never timing —
  all "free-timing policy" compiler theories are dead. The target differs
  only in free/append ORDER, i.e. in ucode consumption structure.
- Live hypothesis: the target's cross-branch updateRate reloads are
  uopt-level WEBS (named locals assigned from updateRate), colored t3/t4
  by globalcolor, outside the FIFO entirely — leaving the FIFO to serve
  only 5 region temps. Feasibility + spelling search delegated.

## 6c. Web hypothesis dead — C-space for the rotation region is closed

Round 2 of the arm campaign (see `rotation_arm_respell_2026-07-24.md`)
tested making the two updateRate reloads named-local webs so they leave
the FIFO and color t3/t4 across the branch. Decisive negative: IDO's
value-based copy propagation folds EVERY trivial `local = updateRate`
(any local, any placement, 1 or 2 copies) before coloring — all six
spelling families compile byte-identical to base; RACER-COLOR shows no
integer web spanning the region. Non-trivial derivations that survive
propagation change opcodes.

Four independent falsification lines now close the C-reachable space for
the 19-diff region under the canonical IDO 5.3 binary:

1. expression-level lifetime constructs (use-count>1 routes to GET class);
2. arm respellings (13 families → identical dataflow graph/op-sequence);
3. all 5040 entry-queue permutations (infeasible under our op-sequence;
   hold-entry matches only the 7-alloc prefix);
4. named webs (copy-propagated away).

The target requires region free order `4,0,1,2,5,6,7…` (the `var_t0>>1`
temp freed first) where the store/reload structure forces `0,1,2,3,4…`.
Status: the residual is a fully-characterized free-ORDER anomaly,
paralleling the menu function's proven ceiling (two independent functions
whose only residue is ugen free-order behavior). Unless the silent-ucode
microcase hunt (in flight) finds a construct that emits nothing but
perturbs consumption order, norm=19 is the honest natural ceiling for
this compiler binary and the campaign moves to documentation +
upstream-of-region global-state search as a long shot.

## 6d. Compiler-variant battery (closes obtainable-compiler provenance)

The menu-campaign hunt harness (paired alternate toolchains, scratchpad
`hunt/harness/`) was run on the best-19 checkpoint through the isolated
pipeline:

```text
CANON / CANON-check          norm=19  (control)
IDO61-uopt / IDO71-uopt /
IDO744-uopt / P1260-uopt /
P1078-cfe / P1260-P1078 / WRAP  norm=19  — residual INVARIANT
IDO52-full / IDO52-uopt      norm≈2456-2462 (2610-2619 insns)
IDO53-origAs1 / P260-as1     norm≈2365 (2615 insns)
IDO61-full                   norm≈2364
IDO51 / IDO71-full / IDO744-full  crash (era-incompatible)
```

No obtainable compiler variant touches the 19-diff region without
destroying the rest of the function. Combined with the menu campaign's
proof that all public 5.3 ugen binaries are byte-identical (incl. the
pressed retail CD), the obtainable-compiler branch is CLOSED. Remaining
theory space: (a) silent-ucode source construct (microcase hunt in
flight), (b) unobtainable Rare-internal toolchain difference, (c) an
unconceived source construct altering the region op-sequence with
identical opcodes.

## 6e. Type/idiom genre closed (~30 variants)

`type_idiom_campaign_2026-07-24.md`: every semantically-neutral cast/mask
respell is byte-identical inert (the byte-identical ⟹ queue-invariant
axiom held throughout); every queue-moving construct is an upstream
mask-node reshape that reflows the whole downstream uncontained
(norm 220-1045). Closest signal: `(s16)(var_t0*updateRate)` at line 743
reaches entry-queue front-3 `[12 24 25 …]` at norm 220. Structural gap:
the target's entry-queue difference is ABSORBED (only 19 regs differ,
downstream reconverges), but no source-expressible perturbation is
contained — movers reflow, non-movers don't reach the queue.

## 6f. Formal closure enumeration + final positive control

`ugen_closure_enum_2026-07-24.md`: complete enumeration of every
append/remove/defer path on the 0x10019da4 list (6 append sites, 7
remove sites). The only deferral mechanism is the usage-count gate in
f_free_reg. Notably it REFUTES the earlier "use-count>1 ⇒ GET class"
routing law (ugen's class choice keys on parent hints and dead-operand
reuse, not the node's own use count) and leaves exactly one surviving
theoretical path: a FIFO-allocated node with use count 2 whose second
consumer takes the no-emit memoization path.

Final positive control (mc_cse.c microcase, traced): uopt materializes
EVERY shared subexpression — (a+b)² , (a^b) used twice, an andi mask
used twice — into its own specific uregs (a0/a1/a2, GET class) with
visible usage draining. cfe emits linear trees with no sharing. Therefore
ugen never receives a FIFO-class node with use count > 1 from this
front end: the surviving path is UNREACHABLE from C through the
canonical cfe/uopt. Self-cancelling shared forms (x−x, x^x at the
line-745 condition) fold before ucode (byte-identical inert; tested).

With this, the C-reachable space for a contained free-order perturbation
is closed at the same standard of rigor as the menu campaign's ucode
enumeration, subject only to the still-running silent-ucode microcase
sweep confirming no exotic residue.

## 6g. BREAKTHROUGH — the C source is proven structurally correct

Two decisive measurements (2026-07-24, late):

**(a) Forced register choices ⇒ a complete match.** ugen was patched with
a forced choice map for the region's 22 allocations (serials 236-257 =
t4,t8,t9,t7,t6,t3,t5,t6,t4,t8,t9,t3,t5,t6,t8,t7,t4,t9,t7,t3,t5,t6;
env `CODEX_UGEN_FORCE=<N>` forces the first N). Compiling the CURRENT
checkpoint with it yields **diff=0 — the whole function byte-identical
to the ROM.** Therefore the ucode, tree shape, instruction selection,
scheduling, frame and FP allocation produced by our C are all already
correct; only ugen's physical-register choices differ.

Prefix sweep: N=1→89, 2→117, 3→141, 4-7→164, **N=8→9** (residual
1656,1701-1709), N=22→0. The region splits into two independent blocks.

**(b) The entry-queue theory is FALSIFIED.** Forcing the entry queue to
the apparent target [t4 t8 t9 t7 t6 t3 t5] gives diff=164, worse than
our 19. Extracting the exact alloc/free event structure from the
byte-perfect forced run and brute-forcing all 5040 initial queues under
pure FIFO gives **zero** solutions. Allocations and frees interleave, so
the target's first seven registers are not its entry queue — the earlier
"[t6 moved to position 4]" framing (§3, §6b-6f) was an artifact of that
error, and every campaign built on it was searching an unreachable goal.

Event structure (A=alloc index, F=its free), tree-determined:
```
A0 F0 A1 F1 A2 F2 A3 F3 A4 F4 A5 A6 F5 F6 A7 F7 A8 A9 F9 F8 A10 F10
A11 F11 A12 F12 A13 F13 A14 F14 A15 F15 A16 A17 F16 F17 A18 F18
A19 A20 F20 F19 A21 F21
```
(note the inverted frees at A8/A9, A16/A17, A19/A20 — real tree-shape
artifacts, so evaluation order here IS source-controllable).

All 22 of our region allocations are plain FIFO pops (each has a
matching REMOVE-HEAD).

**Correction (verified afterwards):** my inference that the original must
have used a hint or dead-operand-reuse path was WRONG. The region's
allocations all come from one site, `f_get_dest` (ugen.c:45582, function
at 45545), which has exactly two paths: `hint != 0x48` → `f_get_reg`,
else FIFO via `f_get_one_free_reg`/`f_remove_head` with no availability
check and no reuse path. Instrumentation of all four `f_usage_count`/
`f_is_available` sites confirmed they are never reached for this region;
every one of the 22 allocations had `hint = 0x48` (FIFO). The only
non-null hints were `hint=3` (v1) for two `op=54` lvalue loads, which do
not touch the temp queue.

The real variable was therefore neither the queue nor the choice rule but
**which ucode uop is allocated when** — i.e. the event structure. That is
what the statement split changes.

## 6h. SOLVED — the two-line fix

Both remaining agents converged independently on the same change:

```c
if (!(gCurrentRacerInput & R_TRIG)) {
    var_t0 >>= 1;                    /* must be FIRST in the arm */
    obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
    obj->trans.rotation.x_rotation -= ((var_t0 * 19) * updateRate) >> 1;
} else { /* identical, * 30 */ }
```

Mechanism: `var_t0` is dead after the region, so uopt keeps the `>>= 1`
as its own temp-producing uop at the top of each arm instead of folding
it into the second statement's tree. The shift's temp is thus allocated
AND released before the damping statement's temps. Replaying plain FIFO
from our UNCHANGED entry queue `[t6 t4 t8 t9 t7 t3 t5]` with only that
pair moved reproduces the target register sequence exactly; the only
consistent placements are (pop 0, push 0 or 1) per arm. No extra
instruction is emitted.

Minimal deviation set (via `CODEX_UGEN_FORCEMASK`): allocations
{0,1,2,3,7, 11,12,13,14,18} — a symmetric pattern in which t6 sits at the
queue head and is passed over by allocs #0-#3, taken by #4 and retaken at
#7 (arm 1), with arm 2 doing the same for t7 at #11-#14/#15/#18.

**Verified:** norm=0, 2625/2625 raw words, stock pipeline and the
independent CANON toolchain; full repository build with the GLOBAL_ASM
stub removed produces a ROM byte-identical to the original
(sha1 6d96743d46f8c0cd0edb0ec5600b003c89b93755).

## 7. Status (2026-07-24)

The silent-ucode sweep concurred with the closure (zero FIFO deferred
releases anywhere in the function; the retracted "use-count routing law"
replaced by the cascade explanation). All threads resolved. Final state:

- norm=19, `func_80049794_best_19_wave_win.c`, ported into `src/racer.c`
  under `#ifdef NON_EQUIVALENT`; full build verifies ROM byte-exact.
- The 19-diff residual is proven C-unreachable with all obtainable
  toolchains; see `RACER_FINDINGS_DRAFT.md` for the community write-up.
