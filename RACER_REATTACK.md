# func_80049794 (plane physics) re-attack plan
(untracked working notes, not for any PR)

> **Current handoff:** This file is a chronological allocator and campaign
> ledger. `RACER_FINAL_MILE_HANDOFF.md` supersedes its status conclusions with
> the verified 2026-07-24 natural checkpoint: exact frame, instruction count,
> and FP histogram with 20 localized GPR differences remaining.

## 0. STATUS UPDATE (2026-07-23 O5) — §3 premise CORRECTED; route closed negative
The "updateRateF@220(sp)→f14 is the missing interference; our shape leaves f14 free"
hypothesis in §3/§4 is FALSE and is retired. Verified from the disasm + the
instrumented ASSIGN-C forbidden-mask dump:
 - 220(sp) is NOT updateRateF. Target: 220(sp)=var_f14 (=segmentZVelocity). WIP:
   220(sp)=var_f20's OWN spill home (var_f20 lives in caller-saved f14 and spills
   around every call). The "f14 reloads near every call" are var_f20's non-promotion
   SYMPTOM, not missing pressure. The WIP does not leave f14 free — var_f20 is in f14.
 - The real gate (verified, now CONSTRAINTS L13): var_f20's web (icbit 279) colors
   reg27=f14 with forb=0x000000e0 (f0,f2,f12 already forbidden; f2 IS already
   forbidden — the "f2+f14 free" reading came from anz.py's CUP set, which is NOT the
   final coloring). To reach $f20 it needs forb=0xfc — THREE more caller regs
   (f14,f16,f18) forbidden co-live. adjsave (0.876543) is byte-identical baseline vs
   every promoted variant ⇒ priority/tie-break is provably NOT a lever.
 - What promotes: co-live drag-product triples (`t0=oxN*v;t1=oyN*v;t2=ozN*v; vel-=t0;
   vel-=t1; vel-=t2`) drive forb→0xfc, promote var_f20 to $f20 (69 uses, exact), and
   emit inline mul-sub-store structurally identical to the target's drag. But they
   land in a DIFFERENT equilibrium (frame 256 vs 248; −18 insns; probe_eval ~1025 vs
   baseline 471; normalized structural diff 435 vs baseline 233 = WORSE). Frame +8 is
   intrinsic (one temp spills) and not reclaimable by pad removal.
 - What does NOT promote (all zero-emission or plan-route): float-suffix, spD reorder,
   spD-early, dead-def CSE (L3), decl reorder, move_object arg co-live, updateRateF
   kept live in drag.
 - VERDICT: the target's promoted equilibrium (var_f20→f20, inline drag, frame 248,
   only register-renumber vs WIP) is a marginal global-allocation fixed-point the
   canonical no-feedback allocator does not select from the structurally-correct
   source; every source-forced promotion reaches a different, worse-matching
   fixed-point. Same signature as menu/objects. Best byte-state stays baseline 471.
   Full detail: scratchpad/TRIED.md (O5 session), CONSTRAINTS.md (L13, RACER, O5).
   Artifacts: scratchpad/hf_colive_PROMOTES.c, batch.py, reuse.py.
 - Everything below this line is the PRE-O5 plan; §3/§4 premise is superseded above.

---


## 1. The problem, reduced to its final form

The function is ~2630 instructions. Measured honestly (raw instruction words,
one WIP enabled, -DNON_EQUIVALENT, symtab-sliced .text), the committed WIP is
471 words from the target: ~106 of those are measurement artifacts of the
direct-cc harness (literal-table offsets baked into lwc1 immediates vs the
expected object's named-symbol relocs) and ~365 are real. Every real diff is
the downstream ripple of one decision: the target keeps a float variable
(var_f20) in callee-saved $f20/$f21 for the whole function; our compile keeps
it in caller-saved f2 with spills. Frame, CFG, all 82 sibling functions,
and (after the fix below) the rodata literal table are fully accounted for.

## 2. What is proven dead (do not revisit)

- Compiler variants: IDO 5.1/5.2/6.1/7.1/MIPSpro 7.4.4 and the complete IRIX
  5.3 compiler patch stream (SG260/SG1078/SG1260). Behaviorally identical at
  this site or they break matched code. The community 5.3 as1 is itself
  patchSG0001118; that combination is required and already in use.
- Profile feedback (-Wo,-f): uopt's feedback path uses a different global
  cost model; no profile reproduces a no-feedback-style object. The target is
  a no-feedback-style build. Also -O3, -g/-g3/-O1/mips2 ladders, -Olimit,
  -loopunroll: no promotion anywhere.
- Per-file flags: impossible. Same-TU is PROVEN by rodata interleaving (the
  shipped racer.c.o's per-function literal tables abut with zero gap across
  function boundaries in text order; separate linker inputs cannot interleave).
- Hand-tuning: refuted. The target's f20/f21 save order, pairing, prologue
  sequencing and frame slots are byte-identical to IDO convention (matches
  racer_ai_eggs, func_8005698C, func_80045C48).
- The er-cost lever: category error, closed. Neither the target nor the WIP
  has any call inside a loop; er-cost is hard-capped ~41 < 60 for every web.
  Raising the "benefit" was never the game.
- The rodata lever for promotion: orthogonal, closed. But it PROVED a piece
  of the true source: Rare wrote float-suffixed constants
  (spD4 = 0.01f; spD0 = 0.02f; spD8 = 0.004f). With those tokens our literal
  table is byte-identical to shipped (23 literals, 168 B). The committed
  WIP's double tokens (0.01) are wrong-shape; they only luck into a lower
  no-promotion score. Apply the float-suffix shape whenever promotion works.

## 3. The live mechanism (this is the path)

Read from globalcolor in uoptreg2.c and verified with the instrumented 5.3
binary: a callee-saved register is chosen iff totalsave > cost of the BEST
NON-FORBIDDEN register. Caller-saved registers cost only their call-crossing
spills; callee-saved cost includes the first-use toll (60 here). var_f20's
totalsave is 71 > 60 ALREADY. It colors f2 only because f2 and f14 are free:
f0/f12/f16/f18 are already forbidden by four interfering FP webs. The gate is
INTERFERENCE, not value.

Empirical proof: injecting 4 co-live FP values across var_f20's span promotes
it to $f20/$f21 with exactly 69 uses — the target's precise count — and the
op pattern aligns (mov.s $f20,$f2 / c.lt.s $f20,$f12 / mtc1 $zero,$f20 ...).
N=2 and N=3 do not promote; N=4 does. PoC: /tmp/hf_press2.c (session scratch).

The target shows how Rare's source supplied the pressure naturally: it
reloads a pervasive stack local at 220(sp) — almost certainly updateRateF —
into $f14 near nearly every call in var_f20's span, and something else
occupies f2. Our shape parks updateRateF in memory and leaves f14 free.

Important alignment: the interference we need to add corresponds to
instructions the TARGET stream actually has (those f14 reloads) and ours
lacks. Adding the pressure moves our stream toward the target. The two
objectives converge.

## 4. The plan

Step 1. Characterize the occupants precisely from the shipped disasm
   (exp_racer_dr.txt + the extracted .s): which value lives in f14 across
   which call ranges, and what occupies f2. Map def-use: parameter, local,
   or temp; where reloaded; where stored.
Step 2. Reproduce in C: reshape how updateRateF (and the f2 occupant) are
   used so their webs span the calls and color f14/f2. Candidate levers:
   avoid the early spill-to-home; add uses that keep the web live across the
   span; check the documented target-correct expression shapes (TRIED.md)
   for ones that naturally reference updateRateF late. Oracle each attempt
   with anz.py (promotion + forbidden set + totalsave; seconds per eval),
   not full diffs.
Step 3. Once promoted with the right occupants: apply the float-suffix
   rodata shape + the banked target-correct expression shapes together;
   measure raw words (probe_eval.py). Expect collapse toward the ~106
   artifact floor.
Step 4. Near the floor: real verification. Enable the body in the clone,
   full gmake REGION=us VERSION=v80, asm-differ, ROM byte-compare.

Kill criteria: if reproducing the f14/f2 occupancy in C provably requires
emission the target lacks (i.e., the pressure cannot be expressed with the
target's own instruction stream), document the exact contradiction. That
would be a genuine wall. Nothing found so far suggests it.

## 5. Tooling map (for whoever picks this up)

- scratchpad/work-racer/: repo clone, src/racer.c WIP (guard NON_EQUIVALENT),
  .BASE snapshot, rodsig.py (literal-table classifier), exp_racer_dr.txt.
- scratchpad/probe_eval.py: raw-word oracle (~1s). scratchpad/anz.py:
  promotion/forbidden-set oracle. scratchpad/tracehf.sh: traced compile.
- scratchpad/ido-traced/: instrumented 5.3 toolchain (env-gated dumps:
  UOPT_TRACE etc.), byte-identical when disabled.
- CONSTRAINTS.md (laws L1-L12) and TRIED.md (full attempt log) in scratchpad.
  Read both before doing anything.

## 6. POST-O5 PIVOT (2026-07-23, coordinator) — fight inside the promoted basin

O5's closure logic has one gap: it compared scores ACROSS allocation basins.
Baseline 471 lives in the unpromoted basin, which cannot contain the target
by definition (it lacks f20 entirely; ~365 words are unfixable there). The
promoting variant (hf_colive_PROMOTES.c, drag-product triples) ENTERS the
basin the target actually lives in: f20/f21 promoted, 69 uses exact, inline
drag emission structurally identical. Its 1025 raw / 435 normalized diff is
not "worse than 471" — it is the first measurement ever taken from inside
the right basin, and unlike 471 it is reducible in principle to 0.

Every shape campaign in this project's history operated in the wrong basin.
The remaining work is ordinary matching, executed entirely within the
promoted basin: fix frame 256→248 (one intrinsic temp spill — find the
triple formulation or shape that avoids it), fix the instruction-count gap,
apply the banked target-correct shapes and float-suffix rodata THERE, and
grind the register renumbering with the usual oracles. Cross-basin score
comparisons are meaningless and must not be used to abandon the basin.

## 7. FINAL VERDICT (2026-07-23, promoted-basin campaign) — wall proven with mechanism

The §6 campaign ran to completion. Result: THREE basins, all characterized.
 A: unpromoted (baseline raw 471; cannot reach 0 — lacks f20 entirely).
 B: source-forced promotion via co-live product triples (floor raw 996 with
    float-suffix applied; 36 of 2040 formulations promote, EVERY one at
    frame 256; the 3rd co-live web both causes promotion and costs the slot).
 C: the target (frame 248): promotion via a constant-residency fixed-point in
    which the allocator promotes AND reclaims var_f20's old spill home slot
    (net frame 0). No source formulation reaches C: constant-residency routes
    never promote from source; triple routes never reclaim the slot.
Controlled experiment sealing it: the SAME host triple placed on drag block
ox1 gives frame 248 without promotion; on ox2 gives promotion at frame 256.
Second-sourced on two oracles per protocol.

Also confirmed: shapes are basin-relative (float-suffix is score-positive in
B, score-negative in A) — apply banked shapes only within the basin being
worked.

STATUS: racer is closed under the canonical toolchain, now with the exact
mechanism of unreachability. Remaining explanations are outside
source-reachable space (unreproduced compiler build/behavior). The complete
evidence chain: compiler-variant hunt (exhaustive negative), FDO (falsified),
flags/suboptions (negative), hand-tuning (refuted), same-TU (proven),
rodata (recovered true source tokens), er-cost (category error, corrected),
interference (mechanism found, basin B reached), frame reclamation (the
final, unreachable delta). Tooling: dash.py (5-number dashboard),
build_promote.py, iso_sweep.py, best_promoted_996.c in scratchpad.

## 8. CODEX REATTACK (2026-07-23) — §7 closure disproved; frame-248 promotion is source-reachable

### 8.1 Measurement protocol and corrected oracle

All observations below were reproduced with the canonical US v1.0 IDO 5.3
toolchain through `scratchpad/iso_sweep.py` and `/tmp/isoeval.sh`. Allocation
decisions were independently checked with the instrumented
`scratchpad/tracehf.sh`. The main repo source was not changed.

Important oracle correction: FP-register histograms must require the `$`
prefix. Searching for bare `f18` also counts branch destinations such as
`6f18 <func+...>`. Correct target facts are:

```
frame=-248, insns=2625, f20/f21 instructions=69
FP operands:
f0=131 f2=66 f4=188 f6=188 f8=187 f10=188
f12=62 f14=50 f16=8 f18=190 f20=74 f21=2
```

The old `dash.py` "norm" score has a related defect: its register regex
requires `$`, while this objdump prints GPR names without `$`. It remains
useful only as a campaign-relative number, not as a structural proof.

### 8.2 Recovered source facts

Four source corrections expose a previously untested frame:

1. Remove `segmentZVelocity` and assign the interpolation directly to
   `var_f14`. The target carries this value continuously in `$f14`; the
   committed WIP creates a second source variable and copies it.
2. Declare `var_f14` immediately after `spD8`. This reproduces the target's
   exact 20-reference stack home at `220(sp)` once promoted.
3. Use the recovered Rare literals `0.01f`, `0.02f`, and `0.004f`.
4. `racerVelocity` is dead before the later `var_f0` ranges. Reuse `var_f0`
   for that early wave calculation and remove the separate local.

The resulting no-pressure source is:

```
frame=-240 insns=2653 f20=0 f18=3
word SHA1 prefix=500ef2fd6a02
```

The frame is 240 because the obsolete `racerVelocity` home is gone. Saving
the `$f20/$f21` pair therefore lands at the target frame 248, not 256.

### 8.3 Direct contradiction of §7

On the recovered source, a three-result `ox2` drag form using already-declared
locals:

```c
t0 = racer->ox2 * var_f20;
t1 = racer->oy2 * var_f20;
t2 = racer->oz2 * var_f20;
obj->x_velocity -= t0;
obj->y_velocity -= t1;
obj->z_velocity -= t2;
```

produces, under the canonical compiler:

```
frame=-248 insns=2628 f20/f21 instructions=69
f20 operands=74 f21 operands=2
word SHA1 prefix=51673220a309
```

Ten host triples reproduce frame 248 + promotion; all are on `ox2`. Examples:
`(spCC,var_f0,var_f6)`, `(spCC,var_f0,segmentXVelocity)`, and
`(var_f0,var_f6,segmentXVelocity)`. A complete sweep covered 1,365
block/host combinations (three drag sites × C(15,3)); ten hit. Thus §7's
"every source promotion is frame 256" and "basin C is source-unreachable"
claims are false. The missing frame reclamation is ordinary source-local
reuse, not an inaccessible compiler fixed point.

A result-temp version of the same drag:

```c
t0 = obj->x_velocity - racer->ox2 * var_f20;
t1 = obj->y_velocity - racer->oy2 * var_f20;
t2 = obj->z_velocity - racer->oz2 * var_f20;
obj->x_velocity = t0;
obj->y_velocity = t1;
obj->z_velocity = t2;
```

keeps frame 248 and all 69 `$f20/$f21` instructions while reaching 2,627
instructions (target +2; SHA1 prefix `b85ffd898e23` for one host order).

A negated-factor form reaches the exact target instruction count:

```c
n = -var_f20;
t0 = racer->ox2 * n;
t1 = racer->oy2 * n;
t2 = racer->oz2 * n;
obj->x_velocity += t0;
obj->y_velocity += t1;
obj->z_velocity += t2;
```

It emits `frame=-248, insns=2625`, but only 67 `$f20/$f21` instructions
(`f20=72, f21=2`) because the final uses move to the negated web. One object
has SHA1 prefix `c6e119672eb3`; another host order gives target-exact
`f14=50` with prefix `fd596bc12e21`. This is not a solution, but it proves
instruction count and promotion/frame are separately controllable from C.

### 8.4 Exact remaining allocation mechanism

Allocator trace identities on the recovered no-pressure source:

```
bit 279: normalized/drag factor, uses=81, saving=71, reg27=f14, forb=0xe0
bit 334: long interpolation value, uses=66, saving=16, reg28=f16
bit 945: spEC-shaped long web, uses=18, saving=17, reg26=f12
```

With the three-result `ox2` pressure:

```
bit 279 -> reg30=f20, forb=0xfc       (correct)
bit 334 -> reg27=f14                 (correct)
bit 945 -> reg29=f18                 (wrong)
two new 1-use webs -> f14/f16
```

This explains the residual register cascade. The target topology is
`bit945/spEC -> f12`, long interpolation -> f14, short webs -> f16/f18`,
which forces bit279 to f20 while leaving f18 reusable as scratch. The forcing
triple instead parks the 18-use `spEC` web in f18. Corrected histograms:

```
target:   f12=62 f14=50 f16=8  f18=190
triple:   f12=49 f14=45 f16=12 f18=35
```

The remaining task is therefore not "find promotion" or "reclaim eight
bytes." It is specifically: retain bit945 in f12 while bit279 is forbidden
from f14/f16/f18.

### 8.5 Correction: the target scratch equilibrium is not yet source-reachable

An immediate strict recount on 2026-07-23 falsified the first version of this
subsection. The earlier experimental driver accepted both `$f18` register
operands and bare `f18` text. Bare text includes branch destinations such as
`6f18 <func+...>`, so the reported `f18=190/188` results were not register
histograms.

The kept objects were re-counted directly with the corrected `$`-required
regex:

```
constants moved before interpolation:
  frame=-240 insns=2654 f18=3
  f0=117 f2=59 f4=243 f6=232 f8=238 f10=234
  f12=79 f14=110 f16=47 f18=3

promoted declaration-initializer candidate:
  frame=-248 insns=2630 f18=35
  f0=118 f2=59 f4=236 f6=236 f8=236 f10=239
  f12=46 f14=45 f16=9 f18=35 f20=74 f21=2
```

The frame-248 promotion result in §§8.2–8.4 remains valid because it was
rechecked with both disassembly and the allocator trace. What is *not*
established is independent source reachability of the target's `$f18=190`
scratch regime. The exact remaining problem remains the register topology in
§8.4, and confidence estimates must not use the old scratch-regime claim.

### 8.6 Sweeps completed after reopening

- 1,365 existing-local triples over `ox1`, `ox3`, and `ox2`: ten
  frame-248 promotions, all `ox2`, all with the same `spEC -> f18` issue.
- All 105 two-temp `ox2` host pairs, both plain and with an `spD8`
  declaration initializer: no promotion.
- 630 combinations of six explicit interpolation shapes × all two-temp
  `ox2` host pairs: no promotion.
- Direct/const/block `f32` and `f64` interpolation legs, load temps, inverse
  weights, product temps, and 1.0 literal types: no correct promotion.
- Every declaration position for `spEC`: allocation histogram unchanged
  (stack homes move as expected).
- `register` on `spEC`, `var_f20`, `var_f14`, and `spD*`: byte-identical.
- Explicit velocity components before `sqrtf`: optimized away; no promotion.
- Explicit three-value inputs to the final `mtxf_transform_point`: improves
  an unpromoted structural score and makes f2/f12 counts target-like, but does
  not promote, alone or with two drag temps.
- Splitting the late `spEC` ranges, early constant carriers, and distributed
  pressure across interpolation/drag: no correct promotion.
- All 2,730 ordered permutations of the three-host `ox2` pressure form:
  60 frame-248 promotions, collapsing to 12 object hashes/signatures; every
  promoted case still has `spEC -> f18` and `f18=35`. Host order does not
  expose the target allocation.

Reproducible campaign scripts created during this session:
`/tmp/codex_racer_oracle.py`, `/tmp/codex_racer_trace_compare.py`,
`/tmp/codex_racer_host_sweep.py`, `/tmp/codex_racer_shape_sweep.py`, and
`/tmp/codex_racer_decl_sweep.py`. Key kept objects:
`/tmp/codex_rec_notriple.o`, `/tmp/codex_rvmerge_3.o`,
`/tmp/codex_bestinit.o`, and `/tmp/codex_constants_before_interp.o`.

### 8.7 Explicit `spEC` split and two-result pressure campaigns

The target's decompilation appears to split the velocity-square/trick-result
value before merging it into `spEC`; the WIP expresses the whole range with
one `spEC` source variable. This was tested directly rather than inferred.

The first campaign compiled 144 combinations of explicit split/merge
spellings, declaration hosts, and the known three-result `ox2` pressure
forms. None produced the target topology. One useful discriminator was:

```
explicit direct-value split + three-result pressure:
  frame=-248 insns=2628 f20/f21 instructions=69
  f12=63 f18=2
  SHA1 prefix=da00302bed1d
```

Here the split web remains in `$f12`, but the third new one-use result web
is globally colored `$f18`. This establishes that merely preserving the
long `$f12` web is insufficient: a pressure web must not occupy `$f18`
globally, because the target uses `$f18` as a member of its local scratch
pool.

A second campaign exhaustively tested every split spelling with every pair
of two-result hosts: 2,240 canonical compiles, 90 frame-248 promotions, and
zero cases with `f18 > 100`. The best promoted family still globally colored
something in `$f18`.

The most informative unpromoted two-result object is:

```
explicit direct-value split + two-result pressure:
  frame=-240 insns=2654 f20/f21 instructions=0
  f12=63 f18=102
  SHA1 prefix=81e09838fbf3
```

Its allocator trace assigns the normalized/drag factor itself to `$f18`:

```
bit279: uses=81, reg29=f18, forbidden=0xf8
bit66:  uses=16, reg26=f12
bit334:               reg27=f14
CUP bit279 reg25: callee-saved=1 cost=21
CUP bit279 reg30: callee-saved=0 cost=0
```

This is the sharpest remaining boundary. Two result webs correctly block
`$f14/$f16`; the factor then chooses `$f18`. The target must make `$f18`
unavailable or more expensive to that global web without assigning another
long-lived global web there. If that single choice flips to `$f20`, `$f18`
returns to the local scratch pool and the entire downstream register
distribution can change at once.

Campaign scripts and logs:
`/tmp/codex_racer_spEC_split.py`, `/tmp/codex_racer_split_p2.py`,
`/tmp/codex_spEC_split.log`, `/tmp/codex_split_p2.log`,
`/tmp/codex_split_f12_trace.log`, and
`/tmp/codex_split_p2_f12_trace.log`.

### 8.8 Target `$f18` classification and negative micro-experiments

Instruction-alignment analysis proves that target `$f18` is local scratch,
not one resident value. Its 190 uses span the whole function and map in a
promoted candidate primarily to candidate `$f4`, `$f6`, `$f8`, and `$f10`
(48, 40, 41, and 45 aligned instructions respectively). The totals balance:
the target has five nearly even scratch registers
`f4/f6/f8/f10/f18 ~= 188` uses each; candidates with a global `$f18` web
compress the same work into four scratch registers with roughly 230–241
uses each.

This rules out treating the target's `$f18` count as another source variable
to recover. The objective is to keep `$f18` out of global coloring.

Two focused source-shape hypotheses were also killed:

- The target's first FP block stores the `updateRateF * 8.0` conversion
  through `$f18`, whereas candidates use `$f4`. Assignment, compound
  assignment, reversed multiplication, explicit casts, signed zero, and
  division spellings did not change the allocation; the divide form only
  changed instruction count.
- Keeping two axis products live while computing the third axis inline was
  tested across assignment/update permutations on the explicit `$f12`
  split. Every form stayed unpromoted at frame 240 with the factor in
  `$f18`. Ordinary C evaluation-order pressure is therefore not enough to
  pre-forbid `$f18`.

The allocator implementation (`uoptreg1.c`/`uoptreg2.c`) shows the remaining
source-visible levers precisely: per-block `regsused` contributes to a
global web's forbidden mask, while `cupcosts` and the callee-save first-use
cost select among allowed colors. The next campaign should target a real
live-through-call/caller-save cost or a homologous source topology, not add
more arbitrary arithmetic temporaries.

## 9. Final combined handoff checkpoint (2026-07-23)

`REATTACK_HANDOFF.md` is now the entry point for the next agent. This section
records the final racer delta so the older analysis above remains auditable.

### 9.1 Force-color isolation closes the `f18` uncertainty

An isolated instrumented uopt build changed only the final color selected for
bit 279 from reg27/`f14` to reg30/`f20`. No source or repository compiler was
changed.

On the strongest original-style source, kept as
`/tmp/codex_unused_spCC.c`:

```text
natural:
  frame=-240 insns=2655
  f20=0 f18=3
  sha1=c73ca5497d68

same source, bit 279 forced to f20:
  frame=-248 insns=2625
  f20=74 f21=2 f18=186
  sha1=14d77d835190

target:
  frame=-248 insns=2625
  f20=74 f21=2 f18=190
```

The forced object is `/tmp/codex_unused_forced_spCC.o`; its allocator trace is
`/tmp/codex_unused_forced_spCC.trace`. It matches 2,619 of the target's 2,625
mnemonics in order. This supersedes the first canonical forced experiment,
which had 2,623 instructions and 2,614 matching mnemonics but independently
proved the same allocator causality.

The forced result establishes that a long-lived global web does not need to be
invented for target `f18`. Once bit 279 leaves the caller-saved pool, the
compiler naturally returns `f18` to scratch and almost exactly reproduces the
target histogram.

### 9.2 Remaining visible source regions

All six mnemonic differences in the best diagnostic cluster in two places:

1. **Buoyancy.** Target seeds `-1.0f` before the stick/value/clamp work and
   subtracts the `/ 10` result later. The WIP computes
   `-1 - (var_f2 / 10)` as one expression. A 108-case sweep of seed literal,
   divisor literal, seed placement, and subtraction spelling changed local
   schedules but produced zero natural promotions. This clue should be used to
   recover opcode order after the allocator trigger, not cited as a trigger.
2. **Trick rotation.** Target preserves the pre-update halfword in `t0`
   (`move t0,v1` at target instruction index 1215) and uses `t0` for subsequent
   sign tests. The diagnostic copy-propagates that relationship away and uses
   `v1`. The relevant source is the `trickType == 2 || trickType == -2`
   branch around the `var_t0`/`var_v1` setup.

The exact instruction count plus these two clusters make a focused final-mile
attack credible. They do not prove that correcting the clusters will
naturally move bit 279; allocator behavior remains discontinuous.

### 9.3 Final allocator localization

Source-line instrumentation maps bit 279 across 43 basic blocks. The maximum
natural local FP mask is node 389 (`0xe0`), in the final `unk34` drag and
`forwardVel` block. Natural coloring chooses `f14` at cost 21; the first
callee-saved choice costs 60, while total saving is about 71.

The authentic source must add the equivalent of `f14/f16/f18` unavailability
without leaving a resident web in `f18`. Explicit three-product temporaries
create the mask but visibly change the source topology and land in the wrong
global equilibrium, so they remain a proof tool only.

### 9.4 Additional negatives and issues

- One reusable and two alternating late drag temporaries: 240 variants, zero
  natural promotions.
- Split buoyancy formulations: 108 variants, zero natural promotions.
- Latest upstream and 43 discoverable forks: no newer matching source.
- decomp.me scratch `SlvtN`: HTTP 403 from this environment.
- A reporting harness used zsh's read-only `$status` parameter once. The
  compiler had already produced the object and trace; both were independently
  verified. Later harnesses use task-specific names.
- The attempted full-TU force-color wrapper in
  `/tmp/codex_racer_full_forced.py` failed all cases and is not an oracle.
  Use the isolated source/oracle path instead.

The canonical next steps, exact artifact map, stock-validation requirement,
and PR cleanup checklist are in `REATTACK_HANDOFF.md`.

## 10. Codex structural and allocator breakthrough (2026-07-23)

The §9 diagnostic is now structurally complete. Both remaining mnemonic
clusters were recovered as authentic C:

```c
if (racer->buoyancy != 0.0) {
    var_f20 = -1.0f;
    gCurrentStickY = -60;
    var_f2 = racer->buoyancy - 20.0f;
    if (var_f2 < 0.0) {
        var_f2 = 0;
    }
    var_f20 -= var_f2 / 10;
    ...
}
```

and, in the `trickType == 1 || trickType == -1` rotation branch:

```c
var_t0 = racer->x_rotation_vel;
racer->x_rotation_vel += (racer->trickType * 0x600) * updateRate;
/* every subsequent sign test uses var_t0 */
```

The target's `move t0,v1` at instruction 1215 belongs to this `1/-1` branch,
not the later `2/-2` branch. With those forms and bit 279 forced only for
diagnosis, all 2,625 target mnemonics occur in exactly the same order.

The declaration layout is also fully recovered. On the current source family:

- `var_f14` must be declared immediately after `spE0`;
- `var_f20` must be declared immediately after `spD0`;
- the otherwise-unused `spCC` float is retained late in the declaration list;
- the otherwise-unused `pad3` declaration is absent.

`/tmp/codex_layout_exact.c` is the canonical source checkpoint. Its forced
object `/tmp/codex_struct_layout_exact_forced.o` has:

```text
frame=-248 insns=2625
f20=74 f21=2 f18=188
mnemonic distance=0
paired target/candidate stack-offset mismatches=0
sha1=a362e29e7365
```

Natural stock allocation is still:

```text
frame=-240 insns=2655 f20=0 f18=3
sha1=74981a591512
```

The instrumented allocator now dumps every live range at the decisive final
drag/`forwardVel` node. On the exact-layout source, the factor remains bit 279
with `forbidden=0xe0`, `adjsave=0.901235`, 44 interferences, and nine registers
left. The three existing blockers are the long `spEC`-shaped source web in
`f12`, an `ilod` web in `f2`, and a conversion web in `f0`.

### 10.1 New source-reachable `0xfc` mechanism

The final expression can be written through double-precision intermediates
without changing its arithmetic opcode multiset:

```c
d0 = racer->velocity * 0.05;
d1 = racer->forwardVel + d0;
d2 = d1 * 0.125;
d3 = racer->forwardVel - d2;
racer->forwardVel = d3;
```

With four `f64` locals, stock IDO naturally gives bit 279
`forbidden=0xfc` and selects `f20`. The result has 2,630 instructions, and
its opcode multiset differs from the target by exactly five additional
`nop`s—there are no missing or additional non-`nop` opcodes. This is the
first source-local mechanism to reproduce the exact target forbidden mask
while preserving the original double-precision arithmetic.

It is not yet the target source. The retained `f64` webs have adjusted
savings 4, 4, and 2, so they color before the `spEC` web
(`adjsave=0.944444`). `spEC` is consequently pushed from target-like `f12`
to `f18`, producing the familiar compressed four-register scratch pool:

```text
frame=-264 insns=2630
f20 instructions=69, f20/f21 operands=74/2
f18=35, normalized distance=900
sha1=dfb7847254a6
```

The required topology is now precise: preserve these three additional
interferences (or homologous ones), but make `spEC` color first into `f12`;
the short webs must then occupy `f14/f16/f18`. Experiments closed so far:

- 2,730 ordered `f32` final-expression chains: 80 promotions; best results
  were 2,630 instructions and `f18=37`, with precision conversions.
- One-, two-, and three-stage `f64` chains do not reach `f20`. The
  four-stage form does because naming the final subtraction prevents the
  preceding product web from being copy-propagated away.
- All 24 declaration permutations are byte-identical.
- `register` is ignored; `volatile` and fixed arrays emit extra memory
  traffic and lose promotion. Block scope, declaration initializers, nested
  scopes, and struct fields reproduce the same wrong coloring.
- 280 optimizer-erased/identity-use variants produced no case with both
  natural `f20` and scratch-like `f18`; 88 stayed in the `f18=35` promoted
  basin and four arithmetic identities created a worse `f18=5` basin.
- Moving or duplicating the double definitions across the existing `unk34`
  sign branch changes web costs/schedules but has not preserved promotion
  with `spEC` in `f12`.
- Combining all explicit `spEC` split shapes with the four-stage chain also
  failed to restore scratch `f18`.

Reproducers are `.codex_racer_structural.py`,
`.codex_racer_f64_sweep.py`, `.codex_racer_f64_layout.py`,
`.codex_racer_f64_identities.py`, `.codex_racer_f64_cfg.py`,
`.codex_racer_f64_scope.py`, and `.codex_racer_split_f64.py`.

## 11. Canonical exact-FP checkpoint and prepayment campaign (2026-07-24)

`/tmp/codex_unk34_left_associative.c` supersedes the earlier layout checkpoint.
With only the factor web assigned to internal register 30 by the isolated
diagnostic compiler, this source reproduces all target floating-point
instruction sequences and register counts and has 2,625 instructions. The
remaining 90 raw word differences are 39 constant-pool relocation addends and
51 GPR differences. The forced SHA1 prefix is `0f5cd81b7383`.

Stock allocation remains:

```text
frame=-240 insns=2657 f20=0 f18=3 norm=875
sha1=28ae550756b5
```

The allocation problem is not merely “create four more interferences.” The
factor naturally has caller-saved cost 21 and chooses `f14`; choosing unused
callee-saved `f20` costs 60. The target also requires `f18` to remain available
for local scratch:

```text
target:  factor=f20  var_f14=f14  expression=f16  f18=local scratch
natural: factor=f14  var_f14=f16  expression=f18
```

This distinction explains why many apparently strong promotions are false
positives. Tail-zero pressure and fake uses around late calls can yield the
exact 2,625 instruction count and correct `f20=74`, but do so by installing
long-lived global webs in `f14/f16/f18`; the target uses no global `f18` web.

The following routes are now closed:

- erased uses inside the existing wave/wheel loops (91 cases): no factor-cost
  increase and no promotion;
- tail zero-pressure trees (504 cases): 56 promotions, all with wrong
  `f14/f16/f18` blockers;
- tail-call factor uses (441 cases): 42 promotions; best exact-count cases
  were `frame=-248`, `f18=3`, `norm=898`;
- all 15 partitions of the factor's disjoint source regions: no promotion;
- every distinct historical body in local git history and current upstream:
  no missing solution;
- all-range allocator inspection: no dormant `0xfc` web exists before
  coloring; the mask is produced dynamically;
- 1,638 one-pass loop topologies around a late call: explicit mechanics can
  obtain `f20` and scratch-like `f18` but remain in the object, while loop
  wrappers that optimize away also lose their frequency weighting and revert
  to the canonical unpromoted bytes.

The best control-flow demonstration is
`/tmp/codex_landing_loop_topology_call_for_down_i_pad2.c`:

```text
frame=-256 insns=2625 f20=74 f18=192 norm=1007
sha1=e1b4b699d2c7
```

It is diagnostic, not a source candidate. Current evidence leaves hidden
callee-save prepayment by a noninterfering ABI-shaped range, or an unmodeled
source/compiler provenance detail, as the remaining mechanism class.

## 12. Prepayment proof, direct-route closure, and exact residual map (2026-07-24)

The callee-save prepayment theory is now demonstrated end to end in
source-reachable allocator states. Six noninterfering `Qdt` ranges placed
before the factor can prepay internal register 30. Raising the factor's
priority with an optimizer-retained, arithmetic-neutral double conversion or
double negation inside the existing wheel loop then makes the factor claim
that prepaid register at zero cost. Forty variants selected `f20` naturally.
The best representative, `mut_double_r1_before`, has:

```text
factor reg=30 cost=0
frame=-248 insns=2645 f20 operands=78 f18=0 norm=1595
```

This proves the allocator path but not the target source. The six artificial
prepayment ranges occupy the caller-saved FP pool globally, eliminating the
target's local `f18` scratch behavior. Related campaigns showed:

- initialized post-factor `Qdt` ranges can promote through blockers but choose
  the wrong `f18` topology;
- an existing-loop `Qdt` with priority 40 and total caller cost 80 can itself
  reach internal register 30, but overlaps the factor, which is displaced to
  `f24`;
- noninterfering pre-factor `Qdt` ranges can prepay `f20`, but higher-priority
  conversion and `spEC` ranges consume the prepaid colors before the factor
  unless the factor's priority is raised;
- one `Qdt` range spanning every available pre-factor call costs only 11–12,
  far below the fresh callee-save cost of 60.

The remaining direct language routes were also checked. Plain `register`
declarations are byte-identical to the baseline; GCC fixed-register syntax is
rejected; `#pragma register` and `#pragma reg` are ignored; the IDO 5.3 SGI
pragma set has no fixed-register facility. `long double` is byte-identical to
`f64` in this ABI/compiler, while all tested `complex`, `_Complex`, and
`__complex__` spellings are rejected. There is therefore no source-level
wide/aligned scalar class that skips the caller-saved FP registers and lands
directly in `f20`.

An expanded, environment-gated trace of every initial FP live range gives a
stronger prepayment closure. The two most expensive non-factor ranges are
`updateRateF` (bit 4) and the shared real zero constant (bit 1267), each with
caller cost 41 versus fresh `f20` cost 60. Both interfere with the factor.
Every other initial range with nonzero caller cost also interferes with the
factor; every noninterfering range has caller cost zero. No existing
noninterfering range can therefore prepay `f20` without first changing the
source lifetime/control-flow topology. The trace is
`/tmp/codex_all_costs_v2.trace`; the diagnostic build remains byte-identical
when tracing is disabled.

The exact-FP forced object's 51 non-relocation GPR mismatches are localized,
not diffuse:

```text
wave-loop index/cache roles       8
one reversed branch operand       1
spinout rotation topology        11
steering/tilt topology           31
```

Focused source-topology variants preserve all 2,625 instructions and the exact
FP sequence while reducing the GPR residual from 51 to 43. The best combined
source is `/tmp/codex_gpr_combined_001_spin_offset_var_v1.c`: it combines
`steer:reuse+rotation` with reuse of `var_v1` for the spinout offset. Its stock
build still has no `f20`. The 43 residuals are wave-loop roles (8), one
reversed branch operand, a remaining `v0`/`v1` spinout swap (9), and
steering/tilt roles (25). Explicitly caching `gRacerWaveCount - 1` did not
recover the target wave-loop register roles: the clean variants optimize to
2,624 instructions, while variants that retain a third value rotate registers
throughout the function. These integer findings narrow the eventual source
cleanup but do not solve the pre-factor allocation state.

Primary reproducers and logs added in this phase:

- `.codex_racer_postfactor_qdt_phantom.py`
- `.codex_racer_existing_loop_qdt_prepay.py`
- `.codex_racer_wave_loop_qdt_prepay.py`
- `.codex_racer_qdt_prepay_factor_priority.py`
- `.codex_racer_direct_f20_typeclass.py`
- `.codex_racer_single_qdt_callspan.py`
- `.codex_racer_register_binding.py`
- `.codex_racer_diff_localize.py`
- `.codex_racer_gpr_recovery.py`
- `.codex_racer_gpr_topologies.py`

No tracked game source or repository compiler was modified.

## 13. Spinout reduction and exact post-`sqrtf` pressure mechanism (2026-07-24)

Combining the previously best steering topology with a `var_v1` spinout
offset local reduces the exact-FP forced GPR residual from 45 to 43:

```text
source=/tmp/codex_gpr_combined_001_spin_offset_var_v1.c
forced: frame=-240 insns=2625 FP mismatch=0 GPR mismatch=43
stock:  frame=-240 insns=2657 f20=0 norm=867
sha1=54139a6a5dbf
```

The remaining nine spinout words are one exact `v0`/`v1` role swap: target
uses original rotation in `v1` and offset in `v0`; the candidate uses original
rotation in `v0` and offset in `v1`. The allocator trace explains the choice.
The offset local is colored first into internal GPR 2 because that already-used
caller-save wins the tie; the original halfword load is colored later into
internal GPR 1. Comparison reversals, inclusive/negated tests, update
spellings, multiply orders, explicit final values, erased/self uses, direct
rotation reloads, and every safe existing `s32` host preserve the swap or
worsen global allocation. Reproducers are
`.codex_racer_gpr_combined_best.py` and
`.codex_racer_spinout_topology.py`; logs are
`/tmp/codex_racer_gpr_combined_best.log` and
`/tmp/codex_racer_spinout_topology_v3.log`.

The FP allocator mechanism around the initial magnitude calculation is now
more precise. A five-value source bridge across `sqrtf` naturally selects the
factor in `f20`:

```c
spCC = obj->x_velocity;
var_f6 = obj->z_velocity;
segmentXVelocity = obj->y_velocity;
var_f0 = (spCC * spCC) + (var_f6 * var_f6);
var_f2 = var_f0 + (segmentXVelocity * segmentXVelocity);
var_f20 = sqrtf(var_f2) - 2.0;
var_f20 += (f32) (((spCC > 0.0f) + (var_f6 > 0.0f) +
                   (segmentXVelocity > 0.0f) + (var_f0 > 0.0f) +
                   (var_f2 > 0.0f)) * 0);
```

The best representative is
`/tmp/codex_sqrt_bridge_024_h0_inputs_sums_factor_zero_existing.c`:

```text
frame=-248 insns=2641 f20 instructions=69
f20/f21 operands=74/2 f18=3 norm=860
factor reg=30 cost=60
```

Fresh function or block locals reproduce the same allocation but expand the
frame to 272 bytes. Moving the pressure after `sqrtf` avoids call spills and
needs four independent `f32` values. The smallest fresh-local representative
has 2,636 instructions, a 272-byte frame, and the exact 69 factor
instructions/74 `f20` operands. Reusing existing declarations produced 14
promotions in 316 samples, but every promotion activated at least one dormant
stack home and therefore retained a 248-byte frame.

The all-range trace identifies the exact coloring transition:

```text
baseline factor forbidden mask 0xe0 -> f14 chosen at cost 21
four new ranges color internal 25,26,27,28
another interfering range shifts to internal 29
promoted factor forbidden mask 0xfc -> f20 chosen at cost 60
```

Thus the bridge does not merge or raise the factor web's own cost; it fills
all three remaining caller-save choices (`f14`, `f16`, `f18`). This also
explains why it cannot preserve the target's `f18` scratch regime.

Newly closed routes:

- 1,590 direct field-pressure combinations immediately after the first
  factor definition: no promotion;
- 384 post-`sqrtf` alias/field topologies: aliases optimize away; real fields
  promote only with four independent values and extra stack homes/code;
- 46 explicit/mixed `f64` topologies: one `f64` range consumes one allocator
  color, so doubles do not compress the four-range requirement;
- 35 split assignment and intermediate-local spellings around `sqrtf`:
  ordinary forms canonicalize byte-for-byte to the unpromoted baseline;
- 126 hoists of real downstream definitions: the frame remains 240 and some
  variants raise `f18` use to 107, but none promotes the factor;
- full/local identity swaps among `var_f20`, `spCC`, `var_f6`, and
  `segmentXVelocity`: full swaps are byte-identical and all partitions remain
  unpromoted.

Primary new reproducers are
`.codex_racer_postdef_field_pressure.py`,
`.codex_racer_sqrt_bridge_pressure.py`,
`.codex_racer_postsqrt_pressure.py`,
`.codex_racer_postsqrt_existing_pressure.py`,
`.codex_racer_sqrt_assignment_topology.py`,
`.codex_racer_real_hoist_pressure.py`,
`.codex_racer_sqrt_f64_topology.py`, and
`.codex_racer_factor_identity.py`. No tracked game source or repository
compiler was modified.

## 14. Natural `f20` recovery and localized GPR endgame (2026-07-24)

The factor allocation no longer requires a forced compiler. The source-level
trigger is to assign the squared magnitude to `var_f20` before passing that
same local to `sqrtf`:

```c
var_f20 = (obj->x_velocity * obj->x_velocity) +
          (obj->z_velocity * obj->z_velocity) +
          (obj->y_velocity * obj->y_velocity);
var_f20 = sqrtf(var_f20) - 2.0;
```

This form is instruction-neutral. It turns the square-sum input and
normalization result into one factor web spanning the call. The allocator
trace changes the factor's adjusted saving to `0.925926`; its 81 uses plus
call span make caller-save `f14` cost 23.1 and callee-save `f20` cost 60.1.
The surrounding interference/cost cascade selects internal color 30 (`f20`)
naturally. The resulting FP allocation is exactly the target's:

```text
frame=-248 insns=2625
f0=131 f2=66 f4=188 f6=188 f8=187 f10=188
f12=62 f14=50 f16=8 f18=190 f20=74 f21=2
```

The natural combined checkpoint is
`/tmp/codex_gpr_natural_combined.c`:

```text
norm=45 sha1=29b6e852e795
43 GPR-register mismatches
```

There are also 39 raw relocation-addend words for constant-pool addresses.
Those are linkage artifacts and not emitted instruction differences.

The former 42-word source was
`/tmp/codex_gpr_final_steer_direct_mz.c`. Directly reloading
`obj->trans.rotation.x_rotation` in the steering clamp removed the saved
`var_v1` web and recovered target scheduling.

The current strongest natural source is
`/tmp/codex_gpr_final_spinoffset_var_v0.c`. Reusing `var_v0` for the spinout
offset, rather than `var_v1`, changes the shared direct-field web to the
target's `v1` and places the offset in the target's `v0`. This removes all
nine spinout and all five steering-clamp mismatches:

```text
frame=-248 insns=2625 norm=28 sha1=8ea0281b4084
exact FP register counts; 28 GPR-register mismatches
```

The residual is now completely localized:

```text
wave loop                 8
computer equality         1
late rotation block      19
```

The wave-loop allocator mechanism is now experimentally exact. The endpoint
range has priority 12, the counter range 11.6667, and the retained
`gRacerWaveCount - 1` range 1. A diagnostic-only priority addition of 10.67
puts that retained range between the other two and removes all eight wave
differences. The source task is therefore to reproduce that narrow ordering
window without changing code. The diagnostic compiler is not an accepted
solution.

Focused campaigns have closed equality spelling, 144 existing-local wave
hosts, loop syntax/predecrement forms, 544 explicit spinout host pairs, 122
nested spinout assignments, steering statement-order permutations,
damping/update spellings, all single/paired `register s32` declarations, 60
original-style topology combinations, 1,015 empty-fake placements, and 103
integer identity forms. A scan of 26,568 retained same-size objects found no
accidental exact late-rotation allocation. The comprehensive driver is
`.codex_racer_gpr_final_campaign.py`; its `/tmp/codex_gpr_final_*.log`
outputs are the current experiment ledger.

All candidate measurements above use the stock isolated compiler. The
instrumented `/tmp/codex-ido-analysis` compiler is diagnostic only, and
the repository compiler and tracked game source remain untouched.
