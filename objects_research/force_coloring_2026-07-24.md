# func_80017A18 — forced-coloring experiment (uopt globalcolor), 2026-07-24

> Historical compiler experiment. The negative forced-coloring conclusion
> remains valid, but its word-agreement metrics are not the current ranking
> metric. See `HANDOFF_func_80017A18.md` for the exact-scored 1472 / 94.72%
> checkpoint.

## Tooling built (all in /tmp, no repo compiler touched)

- `/private/tmp/ido-static-recomp/build/5.3/uopt.c` regenerated from `ido/5.3/usr/lib/uopt`
  and instrumented with three `getenv`-gated hooks (patch scripts kept in the session
  scratchpad: `patch_uopt.py`, `patch2_uopt.py`, plus an inline patch3).
- Instrumented `uopt` installed at `/tmp/codex-uopt-force/uopt`; driver `/tmp/objforce.sh`
  (same flags as `/tmp/objeval.sh`, only `uopt` swapped).
- **Byte-identity verified** with all instrumentation disabled, on both the v13 candidate
  and the new `count279_edit81_M01_10` checkpoint: `cmp` clean against the stock-pipeline
  object, before and after each of the three patches.

### Env levers
| var | meaning |
|---|---|
| `CDX_LOG=1`, `CDX_OUT=<file>` | dump every coloring decision |
| `CDX_PROC=108` | restrict to func_80017A18 (globalcolor invocation #108 of 221 in objects.c) |
| `CDX_FORCE="w<N>=c<C>"` / `"w<N>=s"` | force web N to color C / force it to be split |
| `CDX_NS="w<N>=0|1"` | force `needsplit()` result for web N (neighbour-spill path) |
| `CDX_SAVE="w<N>=<float>"` | override web N's `save` cost input (drives selection order) |

Proc #108 identified by differential logging: inserting one extra FP statement into
func_80017A18 changed exactly one globalcolor block (#108).

## Instrumented decision points inside `f_globalcolor`

Recompiled-source line refs are relative to `f_globalcolor` (abs = 157379 + rel, before patching):

| rel | label | what it decides |
|---|---|---|
| 645 | `L471758` | selection loop: pick the uncolored web with max `save` (`web+48`, float) |
| 1006 | `L471b74` | `totalsave = save * numocs (web+28)`; `if (totalsave <= bestcolorcost) -> f_split()` else colour |
| 1180 | `L471d6c` | store chosen colour into `web+32` |
| 1487/1502 | `L472104`/`L472110` | after colouring a web, every *neighbour* gets the colour added to its forbidden mask and `colorsleft (web+33)` decremented; if `needsplit()` (i.e. `colorsleft == 0`) the neighbour is **split/homed** |
| 1962 | `L472628` | phase-2 pass, same shape (`if (bestcost < totalsave) colour`) |

`save` comes from `f_compute_save` = (sum of per-occurrence weighted costs) / (numocs + bvectcard),
doubled when the symbol's type byte (`sym+1`) == 0xC (double).

## MEASURED per-web decision table for func_80017A18 (proc 108)

Identical on **both** the v13 candidate (280 insns) and the new 279-insn checkpoint —
19 splits, 48 colourings, same webs, same colours, same costs in both.

### Phase-1 split/colour decisions — **every single one was COLOR; `f_split` was never
reached from the `totalsave <= bestcost` test.**

FP class (`class=2`) webs, in selection order:

| web | save | nocs | totalsave | bestcost | colour | result |
|---|---|---|---|---|---|---|
| 187,194,198,202 | 20000 | 1 | 20000 | 0.0 | 24,25,26,27 | COLOR |
| 161 | 3666.667 | 3 | 11000 | 0.0 | 28 | COLOR |
| 41 | 2802.5 | 4 | 11210 | 0.0 | 29 | COLOR |
| 48 | 2802.5 | 4 | 11210 | **8.5** | 30 | COLOR |
| 131,155 | 2500 | 2 | 5000 | 0.0 | 24,25 | COLOR |
| 55 | 1701.667 | 6 | 10210 | **8.5** | 31 | COLOR |
| 135 | 1500 | 2 | 3000 | 0.0 | 25 | COLOR |
| 297 | 1111.111 | 9 | 10000 | **8.5** | 32 | COLOR |
| 111 | **1000** | 6 | 6000 | **8.5** | 33 | COLOR |
| 163 | **1000** | 2 | 2000 | 0.0 | 26 | COLOR |
| 167 | **1000** | 2 | 2000 | 0.0 | 27 | COLOR |
| 171 | **1000** | 2 | 2000 | **8.5** | 34 | COLOR |
| 27 | 876.25 | 8 | 7010 | **8.5** | 35 | COLOR |
| 104,133,137 | **1000** | 1 | 1000 | 0.0 | 24,26,26 | COLOR |
| 318 (sym 119) | **1000** | 1 | 1000 | 0.0 | 27 | COLOR |
| 321 (sym 115) | **1000** | 1 | 1000 | 0.0 | 28 | COLOR |
| 343 (sym 62) | **1000** | 1 | 1000 | 0.0 | 29 | COLOR |

`bestcost = 0.0` means a colour already live in the frame was reusable;
`bestcost = 8.5` is the callee-saved first-use toll for a *fresh* register.
The `adjsave = 1000` tie in the earlier verdict is real and visible: webs
104/133/137/163/167/171/318/321/343 all sit at exactly `save = 1000.0`, and the
tie is broken purely by **web-array index order**, not by any cost.

### Where the homing actually comes from — 19 splits, all via `needsplit()`

`needsplit()` returns true iff the web has `colorsleft == 0`. All 19 splits in this
function came from that neighbour path, none from the `totalsave <= bestcost` test:

| web | save | livran | colorsleft |
|---|---|---|---|
| 104, 115, 119 | 800.0 | 35, 33, 34 | 0 |
| 34, 19 | 751.25 | 54, 58 | 0 |
| 133, 137 | 600.0 | 33, 32 | 0 |
| 84, 81, 78 | 525.0 | 40, 44, 48 | 0 |
| 296 | 444.444 | 31 | 0 |
| 62 | 376.25 | 52 | 0 |
| 299 | 222.222 | 31 | 0 |
| 300 | 111.111 | 31 | 0 |
| 66 | 3.444 | 36 | 0 |
| 267 | 2.222 | 36 | 0 |
| 0 | 2.200 | 40 | 0 |
| 15 | 1.222 | 39 | 0 |
| 68 | 1.111 | 52 | 0 |

Webs 104/115/119/133/137 (save 600-800) are the `A`, `C`, `D` plane coefficients —
these are the `swc1 $fX,0xE4/0xDC/0xD8(sp)` + immediate `lwc1` pairs.
`B` survives in `f26` because it is never a neighbour of a web that exhausts its colours.

## FORCED-BUILD VERDICT

### 1. Forcing a colour (`CDX_FORCE=w<N>=c<C>`)
276 trials (23 FP webs x 12 colours) on the 279-insn checkpoint.
**Every non-identity colour force produced no object at all** — forcing a colour that is
in a web's forbidden mask makes downstream passes (`updatelivran`/`ujoin`) fail.
Only identity forces (the colour globalcolor already chose) reproduce the baseline.
Colour forcing is therefore not a usable lever here; there is no legal alternative
colour for any of these webs given the interference graph produced by this source.

### 2. Forcing splits (`CDX_FORCE=w<N>=s`) — 23 trials
No configuration reached the target. Best single split: web 137 (`ed 80` vs base `81`).
All others made it worse (up to `+10` instructions).

### 3. Forcing `needsplit` off (`CDX_NS=w<N>=0`) — 19 trials
**Crucially: the stack-slot map is bit-identical in all 19 runs.** Suppressing any split
does not remove a home slot from the frame. The frame layout for this function is not
decided by globalcolor.

### 4. The v13 (280-insn) candidate already had the target frame
`addiu sp,sp,-288` and slot map
`0x60:2 0x64:2 0x68:2 0x6C:2 0x70:2 0x74:2 0x9C:5 0xA0:5 0xA4:5 0xB4:6 0xBC:6 0xC0:3 0xD8:3 0xDC:3 0xE4:3`
vs target
`0x60:2 0x64:2 0x68:2      0x70:2 0x74:2 0x9C:5 0xA0:5 0xA4:5 0xB4:6 0xBC:6 0xC0:3 0xD8:3 0xDC:3 0xE4:3`
— one extra *referenced* slot (0x6C), not extra frame. globalcolor's decisions on v13 and
on the new checkpoint are **identical** (same 19 splits, same 48 colours, same costs),
yet v13 is `-288` and the new checkpoint is `-296`. **The 8-byte frame growth is therefore
100% a front-end/ugen consequence of the source shape, not a uopt colouring decision.**

## ANSWER TO "is the C structurally correct?" — NO, not the way `func_80049794` was

The racer playbook worked because the target's allocation was *reachable* by the allocator
and only mis-chosen. Here it is not even reachable: no legal alternative colour exists for
any FP web, and the split set is fully determined by `colorsleft == 0`, which is determined
by the interference graph, which is determined by the source. There is no allocator knob
whose flip produces the target.

**But the "compiler-variant-blocked" framing is also wrong** — the difference is not a
compiler variant, it is a source shape, and it is reachable. See below.

## THE ACTUAL LEVER: the x1-group statement shape controls the frame

Measured 7 x 8 grid over the two plane-dot-product statement groups (stock pipeline only).
Metric note: the repo's `obj_score.py` normalizes `N(sp)` to `OFF(sp)`, so a whole-frame
+8 shift is **invisible** to it. Scoring by *aligned exact 32-bit words* instead:

| variant | x2 group | x1 group | insns | frame | slot map | aligned exact words |
|---|---|---|---|---|---|---|
| current checkpoint | `sum1 = A*x2;` / `sum1 = sum1 + B*y2 + C*z2 + D - spC0;` | `sum2 = A*x1 + B*y1;` / `sum2 = sum2 + C*z1 + D;` / `sum2 -= spC0;` | 279 | **-296** | +8 shifted | 168/279 |
| **p3_q1** | `sum1 = A*x2 + B*y2 + C*z2 + D - spC0;` | `sum2 = A*x1 + B*y1 + C*z1;` / `sum2 += D;` / `sum2 -= spC0;` | 279 | **-288** | **exact match** | **212/279** |

`p3_q1` reproduces the target's stack frame and its complete slot map
(0x60,0x64,0x68,0x70,0x74,0x9C,0xA0,0xA4,0xB4,0xBC,0xC0,0xD8,0xDC,0xE4 with identical
reference counts) at the correct 279 instructions.

Rule extracted from the grid: **frame = -296 iff the x1 group is written as
`sum2 = A*x1 + B*y1;` followed by `sum2 = sum2 + C*z1 + D;`.** Every other x1 shape
(q1 `A*x1+B*y1+C*z1` then `+= D`, q2, q4, q5, q7) yields -288. The x2 group has no
effect on the frame.

## Remaining gap after p3_q1 (all scheduling, not allocation)

- Target emits `blez t3,...` / `move t2,zero` **before** the three `swc1 $f18/$f20/$f22`
  at 164/160/156(sp); candidate emits them after (a 3-instruction rotation at 60-64).
- Target reloads x2/y2/z2 into `f28/f6/f20` once at the j-loop head (insns 66-68);
  candidate reloads lazily per use.
- Candidate has an unfilled `bc1f` delay slot (`nop`) where the target schedules
  `swc1 $f8,112(sp)`.
- Callee-saved profile still differs: target `f20:10 f22:12 f24:4 f26:8 f28:7 f30:10`,
  candidate `f20:7 f22:14 f24:4 f26:8 f28:4 f30:10` (target uses 4 more callee-saved
  operands). This is the residual allocation delta and it is **not** reachable by
  forcing — see verdict above.

## Final sweep numbers (added after the save-cost lever was built)

`CDX_SAVE` overrides the `save` cost input a web carries into the selection loop — the
one input the earlier "impossible" verdict was built on. 336 trials per base
(48 webs x {0.0, 0.5, 900, 1001, 1500, 3000, 100000}), scored by aligned exact 32-bit words:

| base | baseline aligned | best forced | winning override |
|---|---|---|---|
| `count279_edit81_M01_10` (frame -296) | 168/279 | **168/279** | none improved |
| `r0_t0` (frame -288) | 212/279 | **213/279** | `w133=0.5` (+1 word) |

Combined with the 276 colour-force trials (all illegal) and the 19+23 split-force trials
(all neutral or worse), **every knob in `globalcolor` has now been exercised and none of
them moves this function toward the target.** That is the opposite of the
`func_80049794` result, where a single forced decision produced a byte-perfect match.

## Deliverable

`objects_research/func_80017A18_frame288_r0t0.c` — stock-pipeline verified:

```
insns: target=279 cand=279  (delta +0)
frame: -288                     (target -288; previous checkpoint -288 vs -296 MISMATCH)
slot map: EXACT match to target
aligned exact 32-bit words: 212/279   (previous checkpoint: 168/279)
positional exact words: 105/279       (previous checkpoint: 85/279)
obj_score normalized: aligned-identical 214/279, edit distance 107, 25 blocks
```

Note the `obj_score` normalized edit distance *rises* (81 -> 107) while the true
word agreement *rises* too (168 -> 212). `obj_score.py` rewrites every `N(sp)` to
`OFF(sp)`, so it cannot see a whole-frame +8 shift and it scored the -296 variant as if
its 48 stack references were correct. **Recommend adding a frame-size / raw-offset check
to `obj_score.py` before any further search on this function.**
