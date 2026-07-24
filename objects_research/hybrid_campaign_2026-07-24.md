# func_80017A18 hybrid campaign — 2026-07-24

> Historical structural campaign. The lineage discoveries remain useful, but
> `struct`, aligned-word, and positional-word values must not rank current
> candidates. The exact-scored best is 1472 / 94.72%, and the strongest
> natural bridge is 1790; see `HANDOFF_func_80017A18.md`.

Goal: build a hybrid source combining the two lineages (ours = `func_80017A18_frame288_r0t0.c`,
scratch = decomp.me xNAlf adapted TU) and drive it toward an exact match.

Tooling built (all under `<S8>/hyb/`, `<S8>` =
`/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/8a754f4c-0ca5-493b-8e37-fce59c7d7a3a/scratchpad`):

| file | purpose |
|---|---|
| `h.py` | compile + disassemble + positional metrics + FP/GP histograms |
| `m2.py` | **mnemonic-alignment** metrics: `struct` (mnemonic edit distance), `same_mn`, `aligned_ident` |
| `al.py` | aligned side-by-side target/candidate dump |
| `sbs.py` | positional side-by-side dump |
| `forms.py` / `forms2.py` | enumerate statement-partition × term-permutation forms of a 5-term chain |
| `gen3.py` | OUR-lineage parameterized generator (19 knobs) |
| `gen4.py` / `gen5.py` | SCRATCH-lineage parameterized generator (16 knobs) |
| `par.py` / `par5.py` | 10-way parallel compile+score (~60 candidates/sec) |
| `cd.py`, `d1..d7.py` | sweep / coordinate-descent drivers |

Throughput: ~60 full-TU compiles + scores per second. ~45 000 candidates evaluated.

---

## 0. Baselines (fixed scorer, mnemonic metrics)

| source | insns | frame | struct | aligned-ident | pos-exact |
|---|---|---|---|---|---|
| `func_80017A18_frame288_r0t0.c` (ours) | 279 | **-288** | 62 | 206 | 105 |
| `func_80017A18_count279_edit81_M01_10.c` (old ours) | 279 | -296 | – | – | 85 |
| `dm_objects_scratch.c` (scratch) | 283 | -296 | **10** | 184 | 34 |

---

## 1. OUR lineage — result: 105 → **118** pos-exact at 279 insns / frame -288

Best config (`<S8>/hyb/best118_fn.c`, TU `<S8>/hyb/best118_tu.c`):

```c
A = planes[4 * triIndex + 0];
B = planes[4 * triIndex + 1];
C = planes[4 * triIndex + 2];
D = planes[4 * triIndex + 3];

sum1 = B * y2;
sum1 = sum1 - spC0 + C * z2 + D + A * x2;
sum2 = A * x1;
sum2 = sum2 + B * y1;
sum2 = sum2 + C * z1;
sum2 = sum2 + D;
sum2 = sum2 - spC0;
```
plus `DO_TOP` reversed (`z2 = sum2; y2 = z3; x2 = y3;`),
`KCHAIN` split as `t = A1 * x3; t = t + B1*y3 + C1*z3 + D1;`,
and `STORE` with `argA[i] = 0;` moved after the three `argN[i] =` stores.

Metrics: `insns=279  frame=-288  pos-exact=118/279  aligned-ident=205  struct=52`.

### Feature → effect map (our lineage)

| feature | effect |
|---|---|
| **Chain order swap** (target-point chain textually first) | **strictly bad**: 283–288 insns, exact ≤ 55. And with sum2 first, the sum2 statement-partition has *zero* effect (compiler re-associates). REFUTED. |
| **Direct `arg3[i]` re-reads instead of cached x2/y2/z2** | strictly bad: exact 63 → 40s, several variants move the frame off -288 (-280/-296/-304/-312). |
| **`curPlanes` pointer form for plane loads** | strictly bad *in our lineage*: 279→281 insns and frame -296 immediately. `PLANES2` (k-loop) pointer form alone: 279 insns but frame -296. |
| **Dropping the y3/z3/sum2 ↔ x2/y2/z2 save/restore dance** (`hoist1..4`) | 270–278 insns, exact 40–77. The dance is load-bearing: it is what produces target insns 62-64 (3 × `swc1`) and 224-226 (3 × `lwc1`). |
| **Statement partition of the origin (sum1) chain** | `1stmt`/`2stmt`/`3stmt` all compile *identically* — only partitions that break the multiply chain matter. |
| **Statement partition of the target (sum2) chain** | very sensitive. `A*x1+B*y1+C*z1` / `+= D` / `-= spC0` (3-1-1) → 279 @ -288. `A*x1+B*y1` / `+C*z1+D` / `-=spC0` (2-2-1) → **frame -296** (confirms the coordinator's rule). Fully split 1-1-1-1-1 → best. |
| **Term permutation inside a chain** (new lever) | worth +3 exact. Starting the origin chain with `B * y2` (not `A * x2`) matches the target's schedule, where `mul.s $f14,$f26,$f6` (B·y2) is the first FP multiply of the loop body. |
| `DO_TOP` order reversed | +1 exact |
| k-loop chain split `t = A1*x3; t = t + …` | +1 exact |
| `argA[i] = 0` moved after the coordinate stores | +3 exact |
| everything else (COND forms, TRUEV, KCOND, TCALC, BGT, YEQ, ELSE, HEAD orders, `PLANES` order) | no effect at 279 |

### FP-histogram hypothesis — REFUTED as a search objective
The complementary-histogram framing did not predict anything useful. Moving from
exact 105 → 118 the FP histogram got *worse* on several registers
(`f8 -3 → +11`, `f22 +2 → +6`, `f14 -4 → -7`) while positional exactness improved.
Coloring is global; operand counts are not a usable objective.

---

## 2. Frame result (major)

Two independent frame mechanisms found, in the two lineages:

* **Our lineage** (already known): frame is -296 **iff** the target-point chain is written
  `sum2 = A*x1 + B*y1;` / `sum2 = sum2 + C*z1 + D;`. Reconfirmed across the full
  256-combination partition sweep. Also newly found: **`curPlanes` pointer addressing for
  either plane-load site forces -296** in this lineage, and dropping the origin
  save/restore can push the frame to -272/-280/-304/-312.

* **Scratch lineage** (new): the frame is decided by **where the j-loop reads the origin
  from**. Reading `originPointsX[i]` / `originPointsY[i]` / `originPointsZ[i]` directly
  inside the loop ⇒ **-296**. Reading cached locals (`var_f18/20/22`) ⇒ **-288**.
  This holds across every other knob setting (`scratch_v`, `ours`, `ours_rev`, `plain`
  origin modes all give -288; `scratch` and its array-reading variants all give -296).
  So the scratch's extra 8 bytes come from the direct array re-reads, *not* from the
  chain shape — a different cause from our lineage's rule, as the coordinator suspected.

---

## 3. SCRATCH lineage — struct 10 → **7**

Reproduced the scratch exactly in `gen5.py` (283 / -296 / struct 10 / aligned 184).

Improvements found:

| change | struct | insns |
|---|---|---|
| scratch as-is | 10 | 283 |
| drop the stray `j = arg0->collisionFacetCount;` from the per-i prologue **and** move `radius = collisionRadii[i] * scale;` to last (`HEAD=tgt_org_rad`) | **8** | 282 |
| … plus drop the trailing `if (!var_f22) { }` probe (`PROBE_F22=off`) | **7** | 281 |

Remaining structural defects at struct 7 / 281:

```
[replace] tgt[55:56] cand[55:58]   tgt: addiu s7,s7,4
                                   cnd: swc1 f0,168(sp) / swc1 f4,192(sp) / swc1 f2,172(sp)
[insert]  tgt[91:91]  cand[93:94]  cnd extra: lwc1 f4,188(sp)
[delete]  tgt[92:93]  cand[95:95]  tgt has:   lwc1 f12,216(sp)
[delete]  tgt[227:228]cand[229:229] tgt has:  nop
[insert]  tgt[252:252]cand[253:254] cnd extra: addiu s7,s7,4
[insert]  tgt[254:254]cand[256:257] cnd extra: swc1 f12,156(sp)
```

Probe verdicts — each removed individually from the unmodified scratch and measured
(baseline: n=283 frame=-296 struct=10 aligned=184):

| probe | result when REMOVED | verdict |
|---|---|---|
| `((0, originPointsY))[i]` | 283 / struct 10 / aligned 184 | **inert** |
| `curPlanes[2 & 0xFFFFu]` | 283 / struct 10 / aligned 184 | **inert** |
| `if (sum2) { }` | 283 / struct 10 / aligned 184 | **inert** |
| `* 1.0f` on z3 | 283 / struct 10 / aligned 184 | **inert** |
| `new_var3 = new_var3;` | 283 / struct 10 / aligned 184 | **inert** |
| `&arg0->collisionFacets[0, j]` | 283 / struct 10 / aligned **183** | mildly load-bearing — keep |
| `& 0xFFFFFFFFFFFFFFFF` on `edgeBisectorPlane[k]` | 283 / struct 10 / aligned **182** | load-bearing — keep |
| double `& 0xFFFFFFFFFFFFFFFF` on the k-loop index | 283 / struct 10 / aligned **181** | load-bearing — keep |
| `sum1++; sum1--;` | 283 / struct **15** / aligned 183 | **strongly load-bearing — keep** |
| `if (!var_f22) { }` | **282** / struct **9** / aligned 181 | net win on struct, loses 3 aligned |
| stray `j = arg0->collisionFacetCount;` in the prologue | 283 / struct 10 / aligned **182** | neutral alone; **wins only in combination with moving `radius = …` last** (→ struct 8 / 282) |

## 4. The frame rule in the scratch lineage — clean and general

12 origin-handling shapes × 240 other-knob settings each (2 880 candidates). Frame outcome
depends on exactly one thing: **what the j-loop body reads the origin from.**

| origin mode | what the j-loop reads | frames observed |
|---|---|---|
| `cur_readcur` | `curOriginX/Y/Z` (locals) | **-288** ×240 |
| `ours`, `ours_rev` | working-copy locals | **-288** ×240 |
| `plain` | `var_f18/20/22` (locals) | **-288** ×240 |
| `scratch_v` | `var_f18/20/22` (locals) | **-288** ×240 |
| `scratch_mix` (loop reads locals, `counter>10` restore re-reads arrays) | locals | **-288** ×240 |
| `scratch` (unmodified) | `originPointsX[i]` … | -296 ×120, -304 ×60, -312 ×60 |
| `cur_rev`, `restore_top`, `save_in_do` | arrays | -296 / -304 / -312 |
| `cur_from_arr` | arrays | -296 / -312 |
| `scratch_mix2` (loop reads arrays, restore reads locals) | arrays | **-320** ×240 |

So: **loop reads locals ⇒ -288 unconditionally; loop reads arrays ⇒ never -288.** Neither the
save/restore shape, the declaration order, the chain shape, nor any probe changes this.
(Contrast our lineage, where the frame is set by the *statement partition* of the
target-point chain — genuinely two different mechanisms, as suspected.)

## 5. The hard tension (main negative result)

Exhaustive search of the frame-(-288) half of the scratch lineage — 25 920 candidates over
6 origin modes × 5 declaration orders × 6 prologue orders × 4 chain shapes × 3 intersect
forms × 3 plane-load forms × 2 probes × 2 probes — gives:

```
best at frame -288 in the scratch lineage:  struct 55, insns 276, aligned 135, exact 49
```

i.e. **every scratch variant that reaches frame -288 is structurally worse than our own
lineage** (struct 52 at 279 insns, aligned 196, exact 118). The scratch's struct-7 structure
and the -288 frame are mutually exclusive under every source transformation tried:
the direct array re-reads are simultaneously the cause of its good structure and of its bad
frame.

Other scratch-base failures:
* Replacing `curOrigin*` save/restore with our top-of-do-loop shape: struct 55-56, 273-276 insns.
* All `plain` (no save/restore) modes: struct ≥ 70.
* `cur_from_arr` (copies sourced from the arrays instead of the registers): frame -312.
* `restore_top` (restore at the do-loop top instead of the bottom): no struct gain, worse frames.
* Declaration-order permutations of `curOrigin*` / `var_f18/20/22`: never change struct,
  change `aligned` by ≤ 3. The two home sets do not coalesce by reordering.

## 6. Checkpoints written

| file | struct | insns | frame | aligned | exact |
|---|---|---|---|---|---|
| `checkpoints/func_80017A18_ours_n279_frame288_exact118.c` | 52 | 279 | -288 | 196 | **118** |
| `checkpoints/func_80017A18_scratch_struct7_n281.c` | **7** | 281 | -296 | 168 | n/a |
| (prior best) `func_80017A18_frame288_r0t0.c` | 62 | 279 | -288 | 199 | 105 |
| (prior best) `dm_objects_scratch.c` | 10 | 283 | -296 | 168 | n/a |
