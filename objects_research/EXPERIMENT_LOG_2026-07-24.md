# func_80017A18 experiment log (session 2026-07-24, later)

> Current status: the metric discussion below is historical. The exact scorer
> is now `tools/realscore.py`, the verified best is 1472 / 94.72%, and the
> authoritative resume state is in `HANDOFF_func_80017A18.md`.

## Objective function corrected

decomp.me reports asm-differ's score. Weights (tools/asm-differ/diff.py:498):
insertion/deletion = 100 each, reordering = 60, regalloc = 5 per differing
operand field, stackdiff = **abs(offset difference)** per sp-relative
instruction (NOT flat 1). max = len(target)*100 = 27900.

Replicated as `objects_research/tools/dscore.py`. It reproduces the
user's observed decomp.me numbers closely (model 92.98% vs reported
93.39% for the community scratch; 79.82% vs 81.71% for our other
lineage), so it is a valid optimisation target.

**This invalidated the previous "structural delta" objective.** Optimising
struct made the real score WORSE:

| source | struct | dscore | % |
|---|---:|---:|---:|
| community scratch (baseline) | 10 | 1958 | 92.98 |
| struct-8 (prologue permutation) | 8 | 2015 | 92.78 |
| struct-7 (agent) | 7 | 2088 | 92.52 |
| our other lineage, frame -288 | 52 | 5631 | 79.82 |

## Result: best = 1945 (93.03%)

`checkpoints/func_80017A18_dscore1945.c` — prologue order `oz rad j oy ox cnt`,
found by re-running the 720-permutation prologue sweep against dscore.
Breakdown: ins=5 del=1 reord=3 reg=105 stack=640, insns=283, frame -296.

## Where the remaining 1945 points are

- insertions/deletions/reordering: 780  (5 extra instructions, net +4)
- register allocation: 525  (105 differing operand fields)
- stack offsets: 640

## Experiments (all measured)

| experiment | result |
|---|---|
| 720 prologue orderings vs dscore | best 1945 (from 1958) |
| term permutation, both plane chains (36 combos) | ABC/ABC already optimal; all others worse (1950-2244) |
| drop one origin copy axis (5 shapes) | 2575-3090; reg explodes 106 -> ~195 |
| inline k-loop coefficient locals, all 15 subsets | **frame mechanism proven**: removing exactly 2 locals gives frame -288; but reg 105 -> 215, net worse (best 2439) |
| add 1 or 2 unused locals | frame -296 -> -304, score worse |
| inline all 4 coefficient locals | frame -280, structure destroyed (7517) |

## Key mechanism findings

1. **The frame is directly driven by declared local count**, in 8-byte
   steps: +1 or +2 locals -> -304; -2 locals -> -288; -4 locals -> -280.
2. **Fixing the frame is only worth ~56 points**, not the ~400 assumed.
   Most stack penalty comes from individual variables sitting in
   different slots, not from the frame size itself.
3. Therefore the dominant remaining costs are the 5 extra instructions
   (500) and register allocation (525), not the frame.

## Session continued — matching-focused (points are a proxy, not the goal)

### Forced allocation: INERT (unlike the racer)
Instrumented uopt (`/tmp/objforce.sh`, byte-identical when disabled, re-verified
on this lineage). 27 webs are split via the neighbour path (`colorsleft == 0`).
Forcing `needsplit=0` on each of the 27 individually: **all 27 produce a
byte-identical object**. So the extra stores are NOT an allocator artifact that
one forced decision can remove — the source shape genuinely differs. This is the
opposite of func_80049794, where forcing reproduced the target exactly.

### Declaration order: INERT (now confirmed with the correct metric)
Hill-climb, 420 single-move relocations of 36 declaration lines, scored by
dscore: zero improvement. The earlier agent's finding stands, and it is not an
artifact of their having used a structural metric.

### Homed-local census (target vs ours)
Both home exactly **7** locals (written once, read many):
  target: 156 160 164 192 216 220 228
  ours:   104 112 128 184 192 220 228
Same count, different offsets — but declaration order does not move them.

### m2c reconstruction of the target (NEW, high value)
`objects_research/m2c_target_reconstruction.c` — m2c run directly on
`asm/nonmatchings/objects/func_80017A18.s`. Its variable names encode the
target's own stack offsets, confirming the census: spA4=164, spA0=160,
sp9C=156 (origin trio), spE4=228, spDC=220, spD8=216 (A/C/D), spC0=192.

**The target's structure, as reconstructed:**
```c
if (facetCount > 0) {
    spA4 = var_f18; spA0 = var_f20; sp9C = var_f22;   // copies INSIDE the guard
    do { ...
        temp_f0 = ((A*spA4) + (B*spA0) + (C*sp9C) + D) - spC0;   // chain reads the COPIES
    } while (...);
}
```
So: masters in registers, working copies homed and made *inside* the facet-count
guard, and the plane chain reads the copies (never the arrays).

Crude hand-transplants of this shape into the scratch lineage scored far worse
(67.95%, 59.69%) — the structure has to be built as a coherent whole, not
grafted piecemeal. That is the next line of work.

## Post-codex session: 1879 -> 1843 (93.39%)

Codex's pass (37 experiments) found the key lever and reached 1879 with the
frame corrected to -288: **reuse locals that are already dead** (`sum1`,
`new_var3`) to carry two edge-plane coefficients. That removes two declarations
-- correcting the frame -- without the register-allocation cost of deleting
them (reg 103 vs 105 baseline; my own deletion attempt cost 215).

This also corrects an earlier wrong conclusion of mine: "fixing the frame costs
more than it saves" was true only of the method I tried.

Then, on the corrected-frame base:

| step | score | stack | reg |
|---|---:|---:|---:|
| codex best | 1879 | 584 | 103 |
| + declaration relocation (`spF8`, then `curOriginY`) | **1843** | 548 | 103 |
| + declaration swap neighbourhood | converged, no gain | | |
| + re-sweep of all 88 dead-local carrier assignments | converged, no gain | | |

**Declaration order matters only once the frame is correct.** It was measurably
inert on the -296 base (420 relocations, zero gain) and productive on the -288
base. Any future search must fix the frame first.

Re-confirmed on the new base: substituting locals for the inner-loop
`originPoints*[i]` array re-reads remains catastrophic (73-78%), so the array
re-reads are a hard invariant of this source family, on both lineages.

### Session total for func_80017A18
community scratch 1958 (92.98%) -> **1843 (93.39%)**, frame -296 -> **-288**.
Remaining: 283 instructions vs 279; ins=5 del=1 reord=3 reg=103 stack=548.

## Exact asm-differ correction and final investigation

The prior `dscore.py` replica did not use the same object-dump input as
asm-differ. In particular, section selection and relocation rendering changed
the instruction stream being scored.

New tools:

```text
tools/realscore.py  - imports tools/asm-differ/diff.py and reports exact score
tools/realdiff.py   - same pipeline plus component and aligned-pair diagnostics
```

Both use asm-differ's actual object-dump flags:

```text
-d -rz -j .text
```

Calibration:

| Source | Exact local | decomp.me |
|---|---:|---:|
| adapted `better_scratch.c` snippet | 1843 / 93.39% | 93.39% |
| repository source before final self assignments | 1752 / 93.72% | 93.72% |

The root `better_scratch.c` is a standalone function snippet; calibration used
its adapted full objects translation unit, not the snippet as a direct compiler
input.

This establishes that the repository source was already ahead of the public
scratch. The earlier contrary conclusion came from comparing values produced
by different/broken pipelines.

### Final incumbent: 1472 / 94.72%

Adding these load-bearing self assignments to the corrected-frame,
declaration-ordered scratch lineage:

```c
var_f18 = var_f18;
var_f20 = var_f20;
var_f22 = var_f22;
```

produced:

```text
source=func_80017A18_codex_work.c
score=1472  94.72%
stack=512  reg=420  reorder=240  insert=200  delete=100
target=279 instructions  candidate=280 instructions
```

### Natural-lineage bridge

The natural source has the target's frame and long-lived GPR topology. The
final session searched its arithmetic and reconstructed its facet guard:

| Candidate | Exact score | Breakdown |
|---|---:|---|
| best partition/interleave | 2335 | stack 140, reg 395, reorder 300, insert 700, delete 800 |
| + surface store first | 2270 | stack 140, reg 390, reorder 240, insert 700, delete 800 |
| + save/restore placement | 2140 | stack 140, reg 400, reorder 300, insert 600, delete 700 |
| + explicit guarded `do/while` | **1790** | stack 140, reg 390, reorder 60, insert 600, delete 600 |

The guarded source is
`func_80017A18_natural_guarded_1790.c`. It expresses the target's
facet-count test before the three origin saves, then uses an inner
`do/while`. That change alone was worth 350 points on the combined source.

### Exact-scored sweeps completed

- Natural top partition/term orders: 9072; best 2335.
- Guarded ABC/ABC partition/interleave: 6802; best remained 1790.
- Guarded per-point load order: 5040; baseline won.
- Guarded control/save/restore forms: 216; best 1790.
- Natural declaration relocations: 601; no gain.
- Natural alternate dead accumulators: 900; no gain.
- Natural lifetime/self probes: 811; no gain.
- Natural scratch-style carrier chains: 576; best 4567.
- Current-source pointer subsets, arrays, copy layouts, qualifiers, register
  hints, edge forms, and origin placement families: no gain.
- Exact-scored decomp-permuter from 1472: roughly 20 minutes, no gain.
- Deterministic current-source multi-declaration shuffle: stopped at
  11,250/12,000 on user request, with no improvement.

### Prepared but not run

`source_sweep.py` now has `natural-expression-trees`, an exact-scored
parenthesized expression-tree search for the 1790 guarded source. It was added
immediately before the pause request and has not been executed.

### Final stop state

- Search intentionally paused.
- Best remains `func_80017A18_codex_work.c`, score 1472 / 94.72%.
- `src/objects.c` was not changed.
- `src/racer.c` was not touched.
- Full resume instructions are in `HANDOFF_func_80017A18.md`.

---

## Evening session — 1472 → 400 (94.72% → 98.57%)

Baseline re-verified first: `codex_work.c` 1472, `natural_guarded_1790.c` 1790,
`natural_combined_2140.c` 2140. The scorer and the preserved toolchain were
intact.

Work continued on the **natural (guarded) branch**, not the 1472 fakematch
lineage, because its remaining diff was localised to one basic block while its
frame, stack homes and long-lived GPRs were already exact.

Harness built this session (session scratchpad, `h/`): a slotted source
template (`tmpl2.py`), a config-space renderer plus coordinate descent
(`descend2.py`), multi-axis joint sweeps (`joint.py`), a randomised annealer
(`anneal.py`), ad-hoc generators (`sweep.py`, `probe.py`), and a
full-context diff (`fd.sh`). One compile+score is ~0.2 s; ~25–50 candidates/s
across the box.

| step | change | score |
|---|---|---:|
| baseline | `natural_guarded_1790.c` | 1790 |
| 1 | `sum1 = (A*x2 + B*y2) + (C*z2 + D)` (from 648-variant sweep) | 1752 |
| 2 | edge sum as one flat expression | 1712 |
| 3 | `t = arg9[i]; spC0 = t * argB;` (fixed the FP allocator phase) | 1377 |
| 4 | `var_a2 = TRUE` moved after the `t` branch | 1177 |
| 5 | hit point y, x, z | 1088 |
| 6 | `sum1 = (A*x2 + D) + (B*y2 + C*z2)` | 742 |
| 7 | hit point z, y, x (staging temp no longer needed) | **400** |

Steps 3 and 5 were later subsumed: with the step-6 association the staging
temp is unnecessary and the hit order moved again, so the final source has
neither artefact.

Key diagnostics that drove this:

- **The declaration list was proved correct.** Assigning the 33 locals
  descending from `0x11c` reproduces all ten stack homes the target actually
  references. 330 subsequent relocations/swaps among the unreferenced slots
  all score exactly 400 — declaration order is inert for register allocation
  in this function.
- **The register mismatch was a systematic allocator phase shift**, not noise.
  Mapping target→candidate register fields across all aligned instructions
  showed a clean rotation of the low FP temp pool. That is what identified the
  staging-temp fix at step 3 and, later, the extra live value that remains.
- **IDO emits `add.s`/`mul.s` operands in source order** (verified by
  compiling `B*y2 + A*x2 + ...` and reading the emitted operands). The
  target's `mul.s f14,f26,f6` preceding `mul.s f4,f16,f28` is the scheduler
  filling a load-use slot, not evidence of a different source order.

Negative results worth not repeating: flat accumulator chains in every
spelling (~3700, and 280 instructions — one extra `nop`); named or alternate
accumulator variables (all add instructions); interleaved chains; carrier
variables; declaration shuffling; the whole 14,400-combination expression
space (400 is its unique minimum); ~100k permuter iterations from three
different bases.

Integrated into `src/objects.c` behind `#ifdef NON_EQUIVALENT`; the ROM build
was run and verifies OK. Pushed to `fork/match-trackbg-render-flashy` and to
`https://github.com/akratch/dkr-func80017A18-wip`.

### Step 8 — 400 → 355 (98.73%)

Found by decomp-permuter from the 400 base: stage the edge-plane index
through `triIndex`, which is dead at that point.

```c
triIndex = node->edgeBisectorPlane[k];
closestTri = triIndex;
```

Same mechanism as the earlier `t = arg9[i]` fix — an extra assignment that
costs no instruction but shifts the allocator's phase. `reg` 300 → 255.

A systematic sweep of the same trick across all 24 other assignments in the
function (181 variants, every plausible staging variable) found no further
gain, and coordinate descent re-converged at 355.
