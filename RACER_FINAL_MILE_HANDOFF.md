# `func_80049794` plane-physics matching handoff

> **Addendum 2026-07-24 (later session):** the mechanism-led phase has
> started. Phase 1 (trace instrumentation) is complete and the rotation
> free-queue mechanism is now measured, including a falsification of
> erased-if probes at the ugen level. See
> `racer_research/TRACE_FINDINGS_2026-07-24.md` for current state before
> acting on §8/§12 of this document.

- Status: paused on 2026-07-24
- Repository: Diddy Kong Racing decompilation
- Branch at checkpoint: `match-trackbg-render-flashy`
- Base commit: `527889b5d10d047d69aa53bbb7142c784453f0b5`
- Tracked game source at checkpoint: unchanged

This is the authoritative summary of the latest `func_80049794` re-attack.
It consolidates the useful evidence from `RACER_REATTACK.md`,
`CODEX_REATTACK_LOG.md`, `REATTACK_HANDOFF.md`, the retained campaign
drivers, and the live `/tmp` artifacts. Earlier documents remain useful as
chronological ledgers, but their intermediate conclusions are superseded
where they conflict with this file.

The menu function `func_8008FF1C` is outside this document. Its separate
closure is recorded in `MENU_FINDINGS.md` and `MENU_REATTACK.md`.

## 1. Executive conclusion

The function is not a match and is not ready for a PR, but the remaining
problem is much smaller and better understood than at the start of the
re-attack.

The strongest stock-compiler source now reproduces:

- the target's 2,625 instructions;
- the target's 248-byte stack frame;
- the complete floating-point register histogram;
- the target's `f20/f21` save, restore, and use pattern;
- the target's complete normalized instruction structure;
- all but 20 physical-register choices.

The 20 remaining differences are confined to two source regions:

1. one wave-loop backedge register;
2. nineteen late plane-rotation temporary registers.

The residual is an integer-register allocation problem, not a remaining
floating-point, frame-size, instruction-count, or broad scheduling problem.
Custom compiler diagnostics can independently make each residual region take
the target allocation. Those builds are not solutions, but they establish
that the target register states are internally consistent with the present
instruction topology.

The work was still making real forward progress over the full attack:

```text
hundreds of differences
  -> exact target frame/instruction count
  -> exact floating-point allocation
  -> 43 GPR differences
  -> 42
  -> 28
  -> 27
  -> 26
  -> 20
```

The reason for pausing is marginal search cost. The latest broad campaigns
compiled at least 16,779 source variants. One focused wave campaign produced
the 26-to-20 improvement; the surrounding campaigns did not improve it.
Another scan examined 26,568 retained same-size objects without finding an
accidental exact late-rotation allocation. Continuing with more algebraic
variants of the same forms is unlikely to be productive.

## 2. Terms and acceptance standard

This work uses three distinct kinds of result.

### 2.1 Natural or accepted diagnostic checkpoint

A natural result is compiled with the ordinary isolated IDO toolchain,
currently through `/tmp/isoeval.sh`. No allocator source, priority, register
choice, or compiler binary is modified for the candidate. Only natural
results count as source progress.

The current 20-difference checkpoint is natural.

### 2.2 Instrumented diagnostic

An instrumented compiler reports live-range identities, priorities, costs,
forbidden masks, allocation serials, or free-register queue state while
otherwise retaining ordinary behavior. Its output explains a result but is
not itself a match.

### 2.3 Forced diagnostic

A forced diagnostic changes an allocator priority or physical-register
choice. It is an oracle used to answer questions such as:

- Is the target register assignment reachable with this instruction graph?
- Would one different allocator choice eliminate the remaining region?
- Is the source opcode topology already correct?

Forced output never counts as an accepted solution, even when its assembly
matches a target region.

The final acceptance standard remains:

1. ordinary repository compiler and flags;
2. natural source allocation;
3. exact function assembly, including physical registers;
4. successful normal repository build;
5. ROM-level validation required by the project.

## 3. Verified current checkpoint

The source and object were rechecked immediately before this document was
written. The exact source was then copied to a repo-local research checkpoint:

```text
durable source:
    racer_research/checkpoints/func_80049794_best_20.c
original temporary source:
    /tmp/codex_gpr_final_spinoffset_var_v0.c
object: /tmp/codex_gpr_final_spinoffset_var_v0.o

frame=-248
instructions=2625
f20/f21 instructions=69
f20/f21 operands=76
normalized differences=20
frequent stack offsets=[(220, 20), (248, 32)]
instruction-word SHA1 prefix=ebfa69e218fc
```

Floating-point operand histogram:

```text
f0=131   f2=66    f4=188   f6=188
f8=187   f10=188  f12=62   f14=50
f16=8    f18=190  f20=74   f21=2
```

This histogram is byte-for-byte the target histogram. The source was
recompiled during the checkpoint review and reproduced the same metrics and
instruction-word hash.

Both source copies have:

```text
SHA-256:
28b4638b682dd92df8167aff4a672a0ad92e5802b9e88c4459954e1d3cb4cde4
```

The full ELF object's filesystem hash is not a stable identity because the
isolated compiler's temporary input name affects non-instruction metadata.
Use the disassembled instruction-word hash and the metrics above.

### 3.1 Oracle details

The primary oracle is `/tmp/codex_racer_oracle.py`. Its target is:

```text
/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/
17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/
work-racer/nonmatchings/func_80049794/target.o
```

The normalized score strips branch destinations, immediates, stack offsets,
and `$` punctuation. It preserves opcodes and register names. At the current
checkpoint, `norm=20` therefore corresponds exactly to the 20 remaining
physical-register differences.

When counting FP registers, require a literal `$` before the name. A search
for bare `f18`, for example, can count hexadecimal branch destinations.
Several early notes used the unsafe form; the corrected counts in this
document and `RACER_REATTACK.md` are authoritative.

## 4. What changed during the re-attack

### 4.1 Starting state

The strongest early natural/diagnostic sources were around:

```text
frame=-240
instructions=2653 to 2657
f20 operands=0
```

One early handoff representative was 2,655 instructions. The precise count
changed as correct source tokens and source lifetimes were recovered, but the
central failure was stable: the long normalization/drag factor lived in
caller-saved `f14`, was spilled around calls, and never reached target `f20`.

The broad raw-word mismatch was mostly downstream fallout from that one
allocation decision.

### 4.2 Correct source facts recovered before natural `f20`

The following changes were established as target-shaped:

- interpolate directly into `var_f14` rather than through a separate
  `segmentZVelocity` source variable;
- declare `var_f14` immediately after `spE0` and `var_f20` immediately after
  `spD0`;
- use the float-token spellings `0.01f`, `0.02f`, and `0.004f`, including the
  conditional `spD4 = 0.02f`;
- preserve the split buoyancy seed and update:

  ```c
  var_f20 = -1.0f;
  ...
  var_f20 -= var_f2 / 10;
  ```

- preserve source-order and expression-shape corrections around stick input,
  velocity components, top-speed multiplication, throttle reuse, and the
  final `unk34` drag;
- reuse or remove genuinely obsolete declarations so saving `f20/f21` crosses
  the correct stack-alignment boundary and yields a 248-byte frame.

IDO's literal-pool behavior depends on source tokens, so the `f` suffixes are
not merely cosmetic.

### 4.3 Allocator model for the former `f20` blocker

The long factor was identified as allocator bit/live range 279:

```text
uses/unk1C=81
natural forbidden mask=0xe0
natural physical choice=f14
natural caller-save cost approximately 21
fresh first callee-save cost approximately 60
```

Early pressure experiments proved that filling the remaining caller-saved FP
colors makes the factor choose `f20`, but those source forms polluted target
`f18` scratch behavior or added code and stack homes. They were mechanism
proofs, not plausible source.

Other campaigns proved that prepaying a callee-saved register, changing loop
frequency, and creating `Qdt` or `f64` ranges can also reach `f20`, but again
with non-target code or allocation. This ruled out simplistic claims that the
target allocator state was impossible while also showing that source-neutral
pressure was the wrong path.

### 4.4 Natural `f20` breakthrough

The decisive source topology was to assign the squared magnitude to the same
local that receives the `sqrtf` result:

```c
var_f20 = (obj->x_velocity * obj->x_velocity) +
          (obj->z_velocity * obj->z_velocity) +
          (obj->y_velocity * obj->y_velocity);
var_f20 = sqrtf(var_f20) - 2.0;
```

The older one-statement form was:

```c
var_f20 = sqrtf((obj->x_velocity * obj->x_velocity) +
                (obj->z_velocity * obj->z_velocity) +
                (obj->y_velocity * obj->y_velocity)) - 2.0;
```

The two-statement form emits no extra instructions. It merges the pre-call
square-sum input and the post-call factor into one long source web. That
changes the allocator's global ordering/cost cascade and naturally selects
`f20` with the stock compiler.

This single discovery simultaneously recovered:

- the 248-byte target frame;
- all `f20/f21` save and restore instructions;
- all 69 instructions that touch `f20/f21`;
- all 76 `f20/f21` operands;
- the target's local-scratch use of `f18`;
- the complete target FP histogram;
- the exact 2,625-instruction count.

The problem then became a localized GPR-only endgame.

### 4.5 GPR reduction after natural `f20`

The first natural exact-FP checkpoint had 43 GPR differences.

Directly reloading `obj->trans.rotation.x_rotation` in the steering clamp,
instead of preserving an unnecessary `var_v1` web, recovered target
scheduling and reduced the residual to 42.

Using `var_v0` for the spinout offset:

```c
var_v0 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
if (var_v0 > 0x8000) {
    var_v0 -= 0xFFFF;
}
if (var_v0 < -0x8000) {
    var_v0 += 0xFFFF;
}
obj->trans.rotation.x_rotation += (var_v0 * updateRate) >> 4;
```

placed the offset in target `v0` and left the shared rotation-field web in
target `v1`. That removed all nine spinout differences and all five linked
steering-clamp differences, reaching 28.

An equality spelling using an optimizer-neutral XOR:

```c
if (((var_v0 ^ 0) == PLAYER_COMPUTER) &&
    (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
```

recovered the target branch operand and removed one difference.

Focused wave-loop lifetime shaping then moved the natural sequence through
27 and 26 to the current 20.

## 5. Current source reconstruction

The exact isolated source is preserved at
`racer_research/checkpoints/func_80049794_best_20.c`; its SHA-256 is recorded
in section 3. The changes below are the recovery recipe relative to the
current tracked WIP in `src/racer.c`. They are also enough to distinguish the
current 20-difference source from the older 28-difference source.

Do not apply these changes directly to tracked source as a claimed match. The
wave-loop empty conditions are allocator probes and the function remains
nonmatching.

### 5.1 Declaration and stack-shape changes

In the function's float declarations:

```diff
-    f32 var_f20;
+    f32 var_f14;
     f32 spD8;
     f32 spD4;
     f32 spD0;
-    f32 spCC;
+    f32 var_f20;
...
-    f32 segmentZVelocity;
+    f32 spCC;
...
-    f32 var_f14;
...
-    s32 pad3;
```

The resulting declaration order is visible at the top of
`/tmp/codex_gpr_final_spinoffset_var_v0.c`.

### 5.2 Current wave-loop form

```c
for (var_a0 = gRacerWaveCount - 1;
     (gRacerWaveCount - 1) >= 0 &&
         gRacerCurrentWave[var_a0]->waveHeight <
             obj->trans.y_position + 5;
     var_a0--) {
    if (gRacerWaveCount - 1) {}
    if (gRacerWaveCount - 1) {}
}

if (var_a0 == gRacerWaveCount - 1) {
    var_a0--;
}
```

The two empty body conditions survive long enough in IDO's intermediate
representation to change priorities and coloring, but they emit no target
instructions. This form is responsible for the natural 26-to-20 reduction.

### 5.3 Other essential current-source forms

```c
gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;
```

```c
if (((var_v0 ^ 0) == PLAYER_COMPUTER) &&
    (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
    gCurrentRacerHandlingStat = 1.4f;
}
```

```c
var_f20 = (obj->x_velocity * obj->x_velocity) +
          (obj->z_velocity * obj->z_velocity) +
          (obj->y_velocity * obj->y_velocity);
var_f20 = sqrtf(var_f20) - 2.0;
```

```c
var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
          (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] *
           (1.0 - var_f0));
spD4 = 0.01f;
spD0 = 0.02f;
spD8 = 0.004f;
...
spD4 = 0.02f;
spD0 = 0.01f;
```

```c
gCurrentStickY = ((f32) gCurrentStickY) * (1.0 - var_f20);
```

```c
var_f20 = -1.0f;
...
var_f20 -= var_f2 / 10;
```

```c
var_t0 = racer->x_rotation_vel;
racer->x_rotation_vel +=
    ((racer->trickType * 0x600) * updateRate);
```

```c
obj->y_velocity = racer->velocity * racer->oy1;
```

```c
var_f0 = handle_racer_top_speed(obj, racer);
var_f14 = var_f14 * var_f0;
var_f14 *= 1.8;
```

```c
racerThrottle = racerThrottle * var_f14;
obj->x_velocity -= racer->ox1 * racerThrottle;
obj->y_velocity -= racer->oy1 * racerThrottle;
obj->z_velocity -= racer->oz1 * racerThrottle;
```

```c
var_f20 += racer->unk34 * spD0 * 4.0f;
```

The steering/spinout and later rotation bodies should be taken from the
repo-local checkpoint. The important GPR-shaping forms are:

- spinout offset in `var_v0`;
- direct `obj->trans.rotation.x_rotation` comparisons in the steering clamp;
- explicit `var_v1` load/update in each final `R_TRIG` rotation arm.

## 6. Exact residual map

The remaining differing instruction indices are:

```text
72,
1656, 1667,
1682, 1683, 1684, 1685, 1687, 1688, 1689, 1690, 1691,
1701, 1702, 1703, 1704, 1706, 1707, 1708, 1709
```

### 6.1 Wave backedge

```asm
index 72
target:    bltz  a0, 148 <func_80049794+0x148>
candidate: bltz  v1, 148 <func_80049794+0x148>
```

This is the only remaining difference in the entire wave region.

### 6.2 Late rotation block

```asm
index 1656
target:    lw    t3,248(sp)
candidate: lw    t7,248(sp)

index 1667
target:    lw    t4,248(sp)
candidate: lw    t6,248(sp)

index 1682
target:    sra   t6,t0,0x1
candidate: sra   t7,t0,0x1

index 1683
target:    multu v1,t4
candidate: multu v1,t6

index 1684
target:    sll   t3,t6,0x2
candidate: sll   t3,t7,0x2

index 1685
target:    addu  t3,t3,t6
candidate: addu  t3,t3,t7

index 1687
target:    subu  t3,t3,t6
candidate: subu  t3,t3,t7

index 1688
target:    mflo  t8
candidate: mflo  t4

index 1689
target:    sra   t9,t8,0x4
candidate: sra   t8,t4,0x4

index 1690
target:    subu  t7,v1,t9
candidate: subu  t9,v1,t8

index 1691
target:    sh    t7,2(s1)
candidate: sh    t9,2(s1)

index 1701
target:    sra   t7,t0,0x1
candidate: sra   t8,t0,0x1

index 1702
target:    multu v1,t3
candidate: multu v1,t7

index 1703
target:    sll   t4,t7,0x4
candidate: sll   t4,t8,0x4

index 1704
target:    subu  t4,t4,t7
candidate: subu  t4,t4,t8

index 1706
target:    mflo  t5
candidate: mflo  t3

index 1707
target:    sra   t6,t5,0x4
candidate: sra   t5,t3,0x4

index 1708
target:    subu  t8,v1,t6
candidate: subu  t6,v1,t5

index 1709
target:    sh    t8,2(s1)
candidate: sh    t6,2(s1)
```

There are no opcode, immediate, branch-target, or instruction-count
differences in this block. It is a pure temporary-register permutation.

## 7. Wave-loop analysis

### 7.1 Original eight-difference mechanism

At the 28-difference checkpoint, the wave loop had three competing integer
live ranges:

- the loop/address role;
- the decrementing counter;
- a retained `gRacerWaveCount - 1` endpoint value.

The target requires the retained endpoint to be colored between the other two
ranges. In the original natural source, its priority was too low. A
diagnostic-only priority addition of about 10.67 moved it into the required
ordering and removed all eight wave differences.

This proved that the target wave allocation is reachable without changing the
instruction graph. It did not identify a valid source spelling.

### 7.2 Natural source progression

The useful progression was:

1. Starting 28-difference form: eight wave differences.
2. Use `(var_a0 + 0) >= 0` for the guard and an identity-shaped endpoint
   comparison: 26 total differences.
3. Use the retained endpoint expression directly as the loop invariant:
   25 total differences.
4. Keep the invariant and add two optimizer-erased endpoint tests inside the
   body: 20 total differences.

The current form gives the desired primary register allocation throughout
the loop, but the backedge tests the endpoint-colored register `v1` rather
than counter register `a0`. Hence only index 72 remains.

### 7.3 Priority measurements near the discontinuity

Allocator traces around the current family showed the following discrete
states. The labels `ixa`, `counter`, and `endpoint` are the labels used in the
campaign notes for the three competing live ranges:

```text
invariant baseline:
    ixa=12, counter=8, endpoint=4.667

invariant + two erased body tests:
    ixa=9, endpoint=8.5, counter=6
    primary coloring correct; backedge uses endpoint

direct counter guard + three erased endpoint tests:
    ixa=9, counter=8.75, endpoint=8.25
    endpoint just misses the required order

direct counter guard + four erased endpoint tests:
    endpoint=8.6, ixa=7.2, counter=7
    endpoint overshoots and colors first
```

A forced addition of about 3.1 to the endpoint priority in the direct-guard,
two-body-test family makes the complete wave region exact.

The source problem is therefore a narrow, discontinuous ordering problem.
Adding one more syntactic use changes block frequency and priority by too
much; adding none changes it by too little.

### 7.4 Wave campaigns completed

The latest wave-specific work includes:

| Campaign | Variants | Outcome |
|---|---:|---|
| Mixed repeated/fake endpoint forms | 1,947 | No result below the then-best 26 |
| Algebraic initializer/guard/index/update forms | 3,240 | No further improvement |
| Retained endpoint-use placements | 216 | Found the current 20-difference form |
| Backedge/guard retopology | 2,269 | No exact wave |
| Cold-block tuning | 420 | No improvement |
| Existing-block tuning | 1,753 | No improvement |
| Multiset/`ixa` priority tuning | 5,436 | No exact ordering |

Earlier relevant closures include:

- 144 existing-local wave hosts;
- loop syntax and predecrement variants;
- explicit endpoint caching, which either produced 2,624 instructions or
  rotated allocation globally;
- erased expressions and external empty conditions;
- 1,015 empty-fake placements;
- 103 integer identity forms.

### 7.5 Best remaining wave theory

The next useful search should alter control-flow topology, not arithmetic
spelling. The desired source must:

1. keep the backedge condition directly tied to `var_a0`;
2. keep the retained endpoint live through enough hot blocks to raise its
   priority slightly;
3. avoid making the endpoint the backedge-tested value;
4. emit no extra instructions;
5. preserve the exact global FP and GPR allocation outside the wave region.

Promising classes are optimizer-erased uses in a different existing basic
block, a short-circuit shape that survives frequency accounting but folds
before ugen, or a source-level lifetime split whose second segment merges back
into the retained endpoint ichain.

More commutative identities, repeated `(endpoint - endpoint)` arithmetic, and
simple empty `if` count sweeps have already sampled the relevant states and
should not be repeated without a new compiler mechanism.

## 8. Late-rotation analysis

### 8.1 Register-allocation serial proof

The desired physical-register sequence for allocator serials 236 through 257
is:

```text
236 t4   237 t8   238 t9   239 t7   240 t6
241 t3   242 t5   243 t6   244 t4   245 t8
246 t9   247 t3   248 t5   249 t6   250 t8
251 t7   252 t4   253 t9   254 t7   255 t3
256 t5   257 t6
```

A diagnostic `UGEN_FORCE` build that forces exactly this sequence makes the
entire late-rotation block register-exact. The only remaining function
difference in that build is wave index 72.

This is strong evidence that:

- the current rotation statements produce the correct operations;
- instruction scheduling and serial topology are correct;
- the mismatch is caused by the free-register queue entering the region in
  the wrong order.

### 8.2 Queue state and first suspected divergence

Immediately before allocation serial 236, the observed natural free queue is:

```text
[t6, t4, t8, t9, t7, t3, t5]
```

The target allocation requires the equivalent order:

```text
[t4, t8, t9, t7, t6, t3, t5]
```

Thus `t6` needs to be released after `t4`, `t8`, `t9`, and `t7`, not before
them.

The earliest identified source of this ordering is the first `R_TRIG` mask.
Allocator serial 229 naturally receives `t6` and emits:

```asm
andi  t6,v0,0x10
beqz  t6,...
move  v0,t6
```

The emitted target and candidate instructions at that point are already
identical. The difference is when the temporary is returned to ugen's free
queue. That hidden release timing affects the later serials without leaving
an earlier assembly difference.

### 8.3 Experiments completed

The following rotation-oriented routes were tested:

- statement-order permutations;
- alternative damping and update spellings;
- multiply/shift association changes;
- direct versus cached `R_TRIG` values;
- trigger refreshes across nearby blocks;
- assignment-expression and comma-expression forms;
- nested conditions;
- direct field reloads;
- old/original-style steering, spinout, and damping combinations;
- existing local hosts and declaration orders;
- single and paired `register s32` declarations;
- drag/trigger condition AST spellings;
- broad retained-object scans.

Recent focused counts:

| Campaign | Variants | Outcome |
|---|---:|---|
| Trigger refresh placements | 601 | No clean rotation improvement |
| Trigger assignment expressions | 897 | Best local rotation residual 17, but hundreds of global differences |
| Drag-condition AST forms | about 32 | Canonicalized or did not improve |
| Retained same-size object scan | 26,568 objects | No accidental exact rotation region |

The best historical local rotation score was 16, but those candidates had
hundreds of differences elsewhere and are not useful bases.

A custom `UGEN_ROTQUEUE` attempt to hold and restore `t6` was too coarse. It
created 165 later mismatches. The forced per-serial sequence is the reliable
mechanism proof; the hold/restore experiment is not.

### 8.4 Best remaining rotation theory

The likely missing source feature delays the lifetime end of the first
`R_TRIG` mask temporary without changing its emitted instructions. This could
be:

- a source expression that makes the same value appear in a later ucode
  relationship that is folded or coalesced before emission;
- a different short-circuit/assignment AST that gives the mask a later
  last-use point;
- a subtle reuse relationship between the mask and one of the later
  rotation temporaries;
- a compiler point/version difference in `f_free_reg` ordering or ucode
  lifetime accounting.

The next step is not another broad source sweep. It is to instrument the exact
allocation and free events for serial 229 and the affected register, then map
that event back through ucode and ichains to a specific source AST property.

Only after the release event is understood should new source variants be
generated.

## 9. Equality branch: solved

The former standalone equality mismatch is no longer present. Equivalent
plain comparison and subtraction spellings either canonicalized to the wrong
operand ordering or disturbed later allocation. The neutral XOR spelling:

```c
((var_v0 ^ 0) == PLAYER_COMPUTER)
```

retains the required source web long enough to recover the target operand and
then optimizes without an extra instruction.

This is a legitimate natural source result, although the spelling is likely a
fakematch rather than the original Rare source.

## 10. Major closed routes and what they taught us

This section condenses the larger graveyard. Detailed chronological output
remains in `RACER_REATTACK.md` and `CODEX_REATTACK_LOG.md`.

### 10.1 FP pressure and promotion routes

- 1,365 existing-local product triples found source-reachable promotion, but
  most installed the wrong long-lived `f18` occupant.
- 2,730 ordered host permutations reproduced the same wrong equilibrium.
- 2,240 split-spelling/two-result combinations did not preserve target
  scratch allocation.
- 697 float declaration placements, yielding 523 distinct object hashes,
  produced no direct natural solution.
- 1,638 one-pass loop topologies proved loop-frequency and callee-save
  mechanisms but retained non-target loop/frame effects.
- Tail-zero pressure, tail-call uses, partitioned factor webs, `Qdt`
  prepayment, `f64`, `long double`, pragma/register, and post-`sqrtf`
  saturation campaigns all reached useful allocator states but not target
  source shape.

These routes are superseded by the two-statement `var_f20`/`sqrtf`
breakthrough. Do not return to artificial FP pressure unless the natural
checkpoint is somehow invalidated.

### 10.2 Source-layout and type routes

The following did not independently solve the problem:

- declaration reordering beyond the recovered layout;
- arrays, structs, unions, volatile, and `register`;
- fresh block/function locals;
- `f32`, `f64`, and `long double` topology substitutions;
- labels/gotos, one-iteration loops, and branch-phi definitions;
- all 18 associations/permutations of the velocity-square magnitude;
- broad reuse/merge partitions among wave, steering, brake, throttle,
  interpolation, `spEC`, and factor ranges.

### 10.3 GPR source routes

- 544 explicit spinout host pairs;
- 122 nested spinout assignments;
- steering statement-order permutations;
- all single/paired `register s32` declarations;
- 60 original-style topology combinations;
- 1,015 empty-fake placements;
- 103 integer identities;
- wave caches, loop syntax, and predecrement variants;
- rotation expression and trigger cache/refresh campaigns.

The useful exceptions were the `var_v0` spinout offset, direct rotation-field
steering form, XOR equality, and the current two erased wave-body tests.

### 10.4 External source and compiler checks

- Current upstream and 43 discoverable GitHub forks contained no newer
  matching `func_80049794`.
- The linked decomp.me scratch was inaccessible from the environment during
  the check.
- Historical compiler/version investigations did not reveal an obvious
  alternate toolchain that fixes this site without disturbing matched code.

Compiler provenance remains a fallback theory because a tiny point behavior
could affect free-queue ordering, not because there is current positive
evidence for a different compiler.

## 11. Ranked remaining theories

### Theory A: recoverable source-level allocator shaping

Confidence: highest.

The wave and rotation forced diagnostics both show target states reachable
from the current topology. Earlier apparent walls in this function were
broken by small, original-looking source lifetime changes. The two-statement
`sqrtf` input and `var_v0` spinout reuse are strong precedents.

For the wave loop, the missing feature is probably a CFG/lifetime detail that
moves endpoint priority through a narrow ordering window.

For rotation, the missing feature is probably an AST/reuse relationship that
delays the first `R_TRIG` mask's free event.

### Theory B: original source contains optimizer-visible dead structure

Confidence: moderate.

The current best wave result itself depends on empty conditions that emit
nothing but affect allocator priority. The XOR equality is similar. Rare's
original source may have had a real source relationship, macro expansion, or
dead-looking assignment that left the same optimizer fingerprint.

This does not imply arbitrary fakematch searching is useful. The fingerprint
must be targeted to the measured priority or free-event mechanism.

### Theory C: correct source topology, different compiler point behavior

Confidence: low to moderate.

The rotation target and candidate emit identical instructions before their
free-queue states diverge. A subtle difference in ugen lifetime accounting or
free-list insertion could explain that. Similar compiler-sensitive behavior
was investigated for the menu function.

Against this theory:

- the stock compiler naturally reproduces almost the entire 2,625-instruction
  function;
- source changes have repeatedly recovered target allocations;
- no known tested compiler variant has supplied the missing behavior cleanly.

Compiler provenance should be revisited only after correct free-event
instrumentation shows that no C-reachable AST can alter the relevant event
without emission.

### Theory D: current target/object extraction or oracle is wrong

Confidence: very low.

The target count, frame, FP histogram, mismatch indices, and repeated natural
recompiles are internally consistent. The remaining differences are visible
directly in disassembly. The known relocation and bare-`f18` measurement
pitfalls have been corrected.

## 12. Recommended follow-on work

### Phase 0: durable checkpoint

Before resuming experimentation:

1. Confirm the repo-local source checkpoint still has the SHA-256 recorded in
   section 3.
2. Preserve `/tmp/codex_racer_oracle.py`, `/tmp/isoeval.sh`, the target object,
   and the currently working diagnostic compiler binaries or build recipes.
3. Re-run the stock compile and record the instruction hash.
4. Do not replace `src/racer.c` with the 20-difference source until the
   remaining regions match and project policy permits the change.

### Phase 1: repair rotation tracing

The last attempted `UGEN_ROTTRACE` source patch placed a reference to
`codex_rotqueue_serial` in `f_free_reg`, but that variable was block-static
inside `f_get_free_reg`. The scratch compiler build therefore failed.

Repair the diagnostic by:

1. moving the trace serial/state to file scope under the environment guard;
2. keeping tracing disabled by default;
3. proving the rebuilt compiler is byte-identical to the working compiler
   when the trace flag is absent;
4. logging allocation and free events for the first `R_TRIG` mask and
   registers `t4`, `t6`, `t7`, `t8`, and `t9`;
5. recording ucode opcode, ichain/live-range identity, source line, and queue
   before/after each event.

The failed build did not overwrite the existing
`/tmp/codex-ido-rotqueue/ugen` binary. That binary remains the prior working
diagnostic build.

### Phase 2: mechanism-led rotation source search

Once the exact early release is mapped:

1. design a minimal C microcase that reproduces the release-order choice;
2. identify which AST feature delays `t6` without emitting code;
3. transplant only that feature into the real `R_TRIG` condition;
4. reject any candidate that changes instruction count, FP histogram, or
   registers outside the rotation region;
5. use the exact 19-index residual, not a broad raw score, as the first
   oracle.

Stop broad trigger-expression sweeps until this instrumentation exists.

### Phase 3: narrow wave CFG search

Start from the natural 20-difference source and retain the direct `var_a0`
backedge. Search only source forms predicted to move endpoint priority by
roughly 0.5 to 0.75 or reduce the competing counter slightly.

Potential mechanisms:

- an erased use in a differently weighted existing basic block;
- a short-circuit node with the right execution frequency;
- a source lifetime split/merge across the endpoint equality block;
- reuse of an existing expression already present in the wave body.

For every result, record:

```text
instruction count
FP histogram
global register mismatch indices
three wave live-range priorities
physical colors
backedge register
```

Kill a family as soon as its reachable priority states jump from “below” to
“above” the required ordering without producing an intermediate state.

### Phase 4: compiler provenance only if source routes close

If the repaired trace proves the required queue order cannot be produced by
any C-reachable lifetime change:

1. compare the relevant ugen functions across verified IDO 5.3 binaries and
   patch levels;
2. focus on free-register insertion/order and last-use handling, not the
   entire compiler;
3. compile already-matched neighboring functions as controls;
4. reject any compiler whose improvement here breaks established matches.

### Phase 5: integration and final validation

When a natural zero-difference isolated candidate is found:

1. transplant only the recovered function/source changes into `src/racer.c`;
2. build with the normal project configuration;
3. compare `func_80049794` through the repository's ordinary asm-diff path;
4. verify sibling functions and rodata did not move unexpectedly;
5. perform the required ROM byte comparison;
6. remove diagnostic-only empty statements if and only if an exact
   original-looking source form replaces them;
7. clean temporary drivers only after their evidence has been archived.

## 13. Kill criteria and pause rationale

Pause or change strategy again if:

- repaired tracing does not identify a concrete free event;
- a mechanism-led rotation search samples every C-reachable AST class for
  that event without changing queue order;
- wave CFG variants demonstrate a discrete priority gap with no reachable
  intermediate state;
- more than a few thousand additional variants repeat existing object hashes
  or mismatch signatures;
- a proposed improvement damages the exact FP histogram or spreads GPR
  differences outside the two residual regions.

The present pause is not a conclusion that the function is impossible. It is
a conclusion that the current broad enumeration strategy has reached
diminishing returns. Resumption should begin with better instrumentation and
a narrower causal hypothesis.

## 14. Artifact map

### 14.1 Primary current artifacts

```text
racer_research/checkpoints/func_80049794_best_20.c
/tmp/codex_gpr_final_spinoffset_var_v0.c
/tmp/codex_gpr_final_spinoffset_var_v0.o
/tmp/codex_gpr_final_spinoffset_var_v0_recheck.o
/tmp/codex_racer_oracle.py
/tmp/isoeval.sh
```

### 14.2 Important repo-local drivers

Natural FP and GPR recovery:

```text
.codex_racer_sqrt_factor_input.py
.codex_racer_gpr_natural_combined.py
.codex_racer_gpr_final_campaign.py
.codex_racer_gpr_combined_best.py
.codex_racer_spinout_topology.py
.codex_racer_diff_localize.py
.codex_evaluate_object.py
.codex_scan_object_regions.py
.codex_run_gpr_diag.sh
```

Latest wave work:

```text
.codex_racer_wave_algebra_sweep.py
.codex_racer_integer_wave_forms.py
.codex_racer_wave_pointer_sweep.py
.codex_racer_wave_reverse_seed_sweep.py
.codex_racer_wave_scope_type_sweep.py
```

Rotation/trigger work:

```text
.codex_racer_rotation_statement_sweep.py
.codex_racer_rotation_tree_sweep.py
.codex_racer_rotation_value_sweep.py
.codex_racer_drag_literal_suffixes.py
.codex_racer_prerotation_sweep.py
.codex_racer_prerotation_host_sweep.py
```

Older FP allocator mechanism work is represented by the many
`.codex_racer_f64_*`, `.codex_racer_factor_*`,
`.codex_racer_postsqrt_*`, `.codex_racer_qdt_*`, and
`.codex_racer_pressure_*` drivers. Their conclusions are summarized in
section 10 and in the older ledgers.

### 14.3 Documents

Read in this order:

1. `RACER_FINAL_MILE_HANDOFF.md` — authoritative current state.
2. `RACER_REATTACK.md` — detailed allocator history and earlier campaigns.
3. `CODEX_REATTACK_LOG.md` — chronological experiment log.
4. `REATTACK_HANDOFF.md` — older combined menu/racer executive handoff.

### 14.4 Diagnostic compiler artifacts

Important historical paths include:

```text
/tmp/codex-ido-analysis
/tmp/codex-ido-rotqueue/ugen
/tmp/codex-uopt-analysis.*
/private/tmp/.../ido-recomp-pub/build/5.3/ugen.c
```

These are external scratch builds. Never replace the repository compiler with
them. Rebuilds must be validated in disabled-instrumentation mode before any
trace is trusted.

## 15. Workspace state at pause

Before this write-up, `git diff -- src/racer.c` and the tracked repository
diff were empty. The repository contained many untracked research drivers,
documents, ROM archives, logs, and scratch files. They may include work from
multiple sessions and must not be bulk-deleted without review.

This document is itself a research artifact. It does not assert that the
current source is matching, and it should not be included in a gameplay-source
PR unless the project explicitly wants the research history.

## 16. Final assessment

The high-risk parts of the function are solved:

- target stack frame;
- target instruction count;
- target FP allocator fixed point;
- `f20/f21` promotion and saves;
- `f18` scratch equilibrium;
- spinout and steering GPR topology;
- standalone equality operand.

The remaining work is narrow but compiler-sensitive:

```text
wave:     one backedge register
rotation: nineteen temporary-register choices
```

The current source is structurally much closer to the target than the raw
history suggests. The final mile is no longer a decompilation-wide search; it
is a pair of measured allocator-lifetime problems. That is good evidence for
eventual solvability, but not good evidence that more unguided variants will
solve it.

The correct restart posture is:

```text
preserve -> instrument -> explain one release/priority event
         -> make one source change -> verify globally
```

Do not restart with another broad algebraic sweep.
