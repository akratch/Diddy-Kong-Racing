# func_80049794 rotation-arm respell — lab notebook (2026-07-24)

Baseline: `checkpoints/func_80049794_best_19_wave_win.c` — stock insns=2625, norm=19,
sha1=e95892dd53eb. Diff indices: 1656,1667,1682-1685,1687-1691,1701-1704,1706-1709
(all register-only, two arms of the R_TRIG if/else at source lines 767-776).

Target gradient (hold ON, region alloc serials 236-257), regs:
`[12,24,25,15,14,11,13, 14,12,24,25,11,13,14, 24,15,12,25,15,11,13,14]`
Natural entry queue `[14 12 24 25 15 11 13]`, hold entry `[12 24 25 15 14 11 13]`.

## Tooling built (scratchpad/rot)
- `eval.sh <abs.c>` — stock+hold compile/trace/verify, prints region alloc seq + gradient match.
- `lib.py` — extracts the abstract A/F op-sequence from a trace; `replay(opseq, entry)`
  and `entries_for_target(opseq)` (searches all 7! entry perms).
- `solve_ops.py` — given entry+target output, reconstructs the required free schedule.

## Key measured facts
- Region free-queue is self-contained over the 7 temps {11,12,13,14,15,24,25};
  external frees (regs 3,8,17 = v1 etc.) are not in the tracked list, don't perturb it.
- Base op-sequence (entry-independent — identical from stock and hold traces):
  `A0 F0 A1 F1 A2 F2 A3 F3 A4 F4 A5 A6 F5 F6 A7 F7 A8 A9 F9 F8 A10 F10 A11 F11 ...`
  i.e. **stmt2's temps are freed IMMEDIATELY** (F right after each A), because the
  memory store that ends stmt2 consumes them.
- `replay(base_opseq, hold)` = `[12,24,25,15,14,11,13, 12,24,25,15,14,11,13, 12,25,24,15,14,11,13,12]`
  matches target only for serials 236-242 (prefix 7). Diverges at serial 243
  (base gives 12, target needs 14).
- **INVERSION RESULT: no entry-queue permutation (all 5040 tried) reproduces the
  target under the base op-sequence.** So the target requires a *different arm
  op-sequence*, not just a different entry queue.
- Required target free-schedule (solve_ops, under HOLD entry — NATURAL is infeasible
  at alloc 0): allocs 0-6 held live with NO frees, then freed just-in-time before
  reuse: before A7 free A4; before A8 free A0; A9→free A1; A10→A2; A11→A5; A12→A6; ...
  This is the exact OPPOSITE of our arm's "free stmt2 temps immediately" schedule.
  It corresponds to all 7 temps being simultaneously long-lived — i.e. the two
  updateRate reloads hoisted above the branch and **held live across it** (target
  regs 11,12), with cross-arm register reuse (arm1 reuses t3 as the *19 accumulator).

## Experiments (stock_norm / opseq_changed / reachable?)
| spelling | stock_norm | opseq changed | target reachable |
|---|---|---|---|
| base (identity) | 19 | — | no (any entry) |
| comma `x -= (x=A, B)` | 19 | no | no |
| factor-first comma `x = (t=(t0>>1)*19, A); x -= (t*ur)>>1` | 19 | no | no |
| assoc_L `(((t0>>1)*19)*ur)>>1` | 19 | no | no |
| assoc_19first `(19*(t0>>1)*ur)>>1` | 19 | no | no |
| assoc_URfirst `(ur*(t0>>1)*19)>>1` | 905 | yes (opcodes broke) | no |
| assoc_URmid `((t0>>1)*ur*19)>>1` | 905 | yes (opcodes broke) | no |
| assoc_group_UR19 `((t0>>1)*(19*ur))>>1` | 905 | yes (opcodes broke) | no |
| s2_swap `(ur*v1)>>4` | 19 | no | no |
| s2_temp `temp_t7=(v1*ur)>>4; x=v1-temp_t7` | 19 | no | no |
| factor_pre `xRot=(t0>>1)*19` before stmt2 | 19 | no | no |
| shift_temp `zRot=t0>>1` in stmt3 | 19 | no | no |
| ur_two_local `s32 urA=updateRate; urB=...` per-arm | 19 | no | no |

## Conclusion (decisive)
Every source rewrite that PRESERVES the exact opcodes (stock_norm stays 19, same
indices) produces the IDENTICAL dataflow graph, hence identical op-sequence, hence
identical register allocation for a given entry queue — IDO normalizes comma
operators, named temps, textual reordering, and explicit updateRate hoisting all to
the same ucode. Every rewrite that DID change the op-sequence also changed the
opcodes (norm 905). 

The target's register pattern comes from a structurally different allocation: the
two updateRate reloads hoisted above the branch and held live across it on regs
11,12 (ours land on 15,14), which requires all 7 region temps to be simultaneously
long-lived and freed just-before-reuse. Our arm — forced by the mandatory
store+reload between the two x_rotation updates — frees stmt2's temps immediately,
the opposite schedule. This cannot be changed by any opcode-preserving arm rewrite.

**Best stock norm: 19 (unchanged). Best hold-on norm: 164 (unchanged; hold matches
only the 7-prefix then diverges structurally).** No improvement found. The remaining
19 diffs are not reachable via arm respelling under any reachable entry queue; they
require changing GLOBAL allocation state before the region so the hoisted updateRate
loads land on regs 11,12 and stay live across the branch — the "C-unreachable entry
queue / delayed release" class, and moreover a change to the arm's live-range
structure that the mandatory memory round-trip forbids locally.

## Round 2 — WEB hypothesis (coordinator update: FIFO-stream-invariance theorem)

Theorem accepted: FIFO pop outcomes depend only on APPEND ORDER, not timing.
Confirmed independently here: all opcode-preserving rewrites give an identical
op-sequence (identical append/free order), so timing-policy theories are irrelevant.
The target differs only in free ORDER.

Hypothesis tested: the two hoisted `lw ...,248(sp)` loads (@1656 -> t3=11 web A,
consumed arm2 `multu v1,t3`; @1667 -> t4=12 web B, consumed arm1 `multu v1,t4`)
are named-variable WEBS living outside the FIFO. If so, removing them from the
FIFO stream changes the residual free order and could make target reachable.

### Feasibility (model)
- Under the web assumption the residual is NOT a clean 5-temp FIFO: the target's
  non-web temps REUSE the dead web colors 11/12 inside the opposite arm (gradient
  idx5=11, idx8=12, idx16=12, idx19=11). Reachability therefore depends on uopt
  offering a dead web's color to expression temps per-arm — only a real compile
  settles it.
- Required target free order (solve_ops, HOLD entry; NATURAL infeasible at alloc 0):
  append order 4,0,1,2,5,6,7,... i.e. the `var_t0>>1` temp (A4) is freed FIRST.
  Our forced order is 0,1,2,3,4,... (updateRate load freed first, dictated by the
  stmt2 store). So the two orders genuinely differ — reachability hinges entirely
  on the two loads leaving the FIFO.

### Empirical (decisive) — every web spelling is BYTE-IDENTICAL to base
Compiled with named-local copies `xLocal = updateRate;` before/inside the arms,
referencing the locals in the damping and/or factor multiplies. sha1 vs base
(e95892dd53eb):

| spelling | region ALLOCs | stock_norm | sha1 | verdict |
|---|---|---|---|---|
| web1 (2 webs before if, damping uses them) | 15 | 19 | e95892dd53eb | INERT (=base) |
| web2 (swap arm/local) | 15 | 19 | e95892dd53eb | INERT |
| web_all (webs for both mults per arm) | 15 | 19 | e95892dd53eb | INERT |
| web_single (one web arm1) | 22 | 19 | e95892dd53eb | INERT |
| top (web at top of each arm) | — | 19 | e95892dd53eb | INERT |
| loc2 (racerMiscAssetIdx/racerSteerAngle) | — | 19 | e95892dd53eb | INERT |

RACER-COLOR analysis (/tmp/codex-ido-analysis, RACER_COLOR=1): NO integer web LU
spans the region lines for any candidate. The `local = updateRate` copy is folded
by IDO value-based copy propagation before coloring — no web ever forms, the two
loads stay FIFO expression temps colored t7/t6 (15/14). The region-ALLOC drop to 15
is internal bookkeeping only; final object is byte-for-byte base.

### Verdict: WEB HYPOTHESIS DEAD (as a source-reachable lever)
Precise failing constraint: **web formation is impossible at source level** —
copy propagation folds every trivial `local = updateRate`, and any non-trivial
derivation that would survive changes the opcodes (breaking the byte match). Since
the loads cannot leave the FIFO, the residual-free-order route is unreachable, and
(Round 1) no entry-queue permutation maps the full 22-alloc FIFO op-sequence to the
target. Both entry queues fail: NATURAL is infeasible at alloc 0 (needs 12, head is
14); HOLD matches the 7-prefix then diverges at serial 243 because the append order
is forced to 0,1,2,3,4,5,6 rather than the target's 4,0,1,2,5,6.

**Honest ceiling: stock norm = 19 (sha1 e95892dd53eb). Best hold-on norm = 164.**
The remaining 19 register-only diffs are not reachable by any opcode-preserving
change local to the arm region; they require the two updateRate reloads to be
colored t3/t4 and live across the branch, which needs either a surviving named web
(defeated by copy propagation) or a different global coloring/entry-queue state
established upstream of the region (out of scope; "C-unreachable" per project memory).
