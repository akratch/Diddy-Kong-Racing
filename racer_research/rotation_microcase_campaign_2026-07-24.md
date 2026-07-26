# Rotation microcase campaign — 2026-07-24

Goal: find a C source construct that DELAYS an integer expression-temp's release
back to ugen's FIFO free queue (i.e. moves its `free_reg`/APPEND event later)
WITHOUT changing the emitted instruction stream. Applying such a construct to
func_80049794 line 743 must push the reg-14 (t6, R_TRIG-mask) free into the
window between the two operand allocs of line 751, converting queue entry order
`[14 12 24 25 15 11 13]` → target `[12 24 25 15 14 11 13]` and clearing the 19
rotation diffs (indices 1656,1667,1682-1691,1701-1709).

Tools: `CODEX_UGEN_TRACE=1 /tmp/traceeval.sh in.c out.o 2>trace.log`
Score: compile via /tmp/isoeval.sh to .o, then verify_candidate.py on the .o.

Baseline checkpoint: insns=2625 norm=20 sha1=ebfa69e218fc
indices=[72, 1656,1667,1682-1685,1687-1691,1701-1704,1706-1709]
Target = clear all but [72].

Register numbering: t3=11 t4=12 t5=13 t6=14 t7=15 t8=24 t9=25.

---

## Log

### Setup / baseline (measured)
- verify_candidate.py fails on `.c` paths (its internal isoeval invocation returns
  "COMPILE FAILED" spuriously); WORKAROUND: compile with /tmp/isoeval.sh to a .o
  then run verify on the .o. Confirmed baseline: insns=2625 norm=20 sha1=ebfa69e218fc.
- Region-entry queue @ line 767 GET-ENTRY = `[14 12 24 25 15 11 13]` (matches findings).
- Mask node = `101a2f48` op=4 (AND), serial 229, allocated reg 14 at line 743 and
  freed/appended at line 743 (immediate). Its value is GET into v0 (reg 2) for the
  cross-statement CSE web tested at line 766 via `bnez v0`.

### Construct catalog (real function, gated by sha1 = code-identical, score = win)
| # | construct (where) | emitted code | effect on queue/score |
|---|---|---|---|
| v1 | extract mask to `s32 rmask; if(!rmask...)` | CHANGED (norm 29) | worse; extraction not code-neutral |
| A | `(void)(gCurrentRacerInput & R_TRIG);` before 751 | identical (sha1 same) | DEAD → folds, zero effect |
| C_or0 | `stickY | ((mask) & 0)` | identical | DEAD → folds |
| D_comma | `((mask), gCurrentStickY)` | identical | DEAD → folds (mask discarded) |
| B_ternary | `(mask) ? stickY : stickY` | CHANGED (norm 1431) | emits branch; wrecks |
| E_storeD560 | `D_8011D560 = mask;` before 751 | CHANGED (norm 1102) | emits store |
| F_condmask | `&& ((mask)|1)` in 751 cond | CHANGED (norm 1110) | emits |
| G_selfassign | `if(mask){var_t0=var_t0;}` | CHANGED (norm 1121) | emits |
| H_split751 | split `&&` into nested ifs | identical | transparent; queue UNCHANGED |
| I_swap766 | swap if/else arms + negate | CHANGED (norm 31) | changes fall-through |
| J_hoistshift | hoist `(var_t0>>1)` to local | identical | canonicalizes; no change |
| K_mulreorder | `*19*updateRate`→`*updateRate*19` | CHANGED (norm 906) | changes mul order |
| L_explicitmul | `*=`→`= x *` | identical | no change |
| M_urcopy | `var_t9 = updateRate;` (dead) | identical | folds |
| N_mask_eq0 | `!(m)`→`(m)==0` | identical | canonicalizes |
| O_mask_swap | `(input&R_TRIG)`→`(R_TRIG&input)` | identical | canonicalizes |
| P_743_reorder | reorder the 3 `||` clauses | CHANGED (norm 341) | changes short-circuit order |
| Q_751_swap | swap the 2 `&&` operands | CHANGED (norm 1132) | changes load order |
| R_751_eq | `==FALSE`→`!raceFinished` | identical | canonicalizes |
| S_region_paren | reassociate region multiply | identical | canonicalizes |

**Dichotomy, no exceptions:** every construct is EITHER byte-identical (dead uses
fold before ugen — reproduces the prior erased-if finding for void-cast/`&0`/comma;
transparent respellings canonicalize to the same ucode tree) OR it changes emitted
instructions (any live use emits, any short-circuit/operand reorder changes
branch/load order). No construct moved a queue-temp free while keeping code identical.

### DECISIVE mechanism measurement (FREE-vs-APPEND per register, whole function)
Signature: a queue reg with use-count>1 shows FREE-without-following-APPEND (deferred).
Measured on baseline trace:
- QUEUE class t3-t9 (11,12,13,14,15,24,25): FREEs = APPENDs for every reg (diff -1 =
  initial free-list seed). **Every free is matched by exactly one append → use-count
  is ALWAYS EXACTLY 1. Zero deferred frees anywhere in the function.**
- GET class v0/v1/a0-a3/t0-t2 (2-10): v0=166 frees / 0 queue-appends, v1=87/0, etc.
  These absorb ALL multi-use / CSE'd values and never enter the FIFO free queue.
- Positive controls (pc.c `(a+b)` used twice; pc2.c `a&0x10` reused 3x): the shared
  subexpression is allocated to **t0 (reg 8, GET class)**, NOT a queue reg — 0 deferred
  queue frees. Confirms: ugen routes use-count>1 values to GET class by policy.

### CONCLUSION — falsification
The only ugen mechanism that can delay reg14's free-list append into the line-751
window is the usage-count deferral (node+20 >= 2, per ugen_allocator_map Q1/Q3).
But ugen's allocation policy assigns any value with use-count > 1 to the GET-class
registers (v0/v1/a0-a3/t0-t2), reserving the FIFO queue class (t3-t9) exclusively for
use-count-1 scratch. Therefore the two requirements — (i) the mask temp stays a queue
register (t6), and (ii) it has use-count >= 2 so its append defers — are MUTUALLY
EXCLUSIVE under ugen. The moment a C construct gives the mask a genuine second consumer,
ugen relocates it out of the queue class (changing t6→v0/t0 and the whole permutation)
AND emits code; a construct that does NOT give it a real second consumer folds before
ugen and leaves the queue untouched. There is no reachable middle.

Corollary: target order `[12 24 25 15 14 11 13]` is NOT a cyclic rotation of the
current `[14 12 24 25 15 11 13]` (reg14 jumps head→position-4). With strict-FIFO,
use-count-1 queue temps, a non-rotation can only arise from a different alloc/free
NESTING (expression-tree shape) upstream. Every tree-shape change I found that would
alter the interleaving also alters emitted branch/load order (P, Q, K, I). Every
code-neutral respelling canonicalizes to the identical ucode tree (N,O,R,S,H,J,L,M).

Best remaining hypothesis: the target's queue order reflects a ugen internal state
unreachable from expression-level C respelling of this window — i.e. it depends either
on a different upstream statement STRUCTURE (changing the alloc/free nesting while
somehow preserving emitted code — not found in this window) or is a genuine
compiler-point artifact (Theory C). The forced-serial "proof" that delaying reg14
reproduces the target was done by HACKING ugen serials, which is exactly what C source
cannot induce given the class-based allocation policy proven above.

Note: the `CODEX_UGEN_ROT=1` forced hack currently in the trace toolchain is INERT
(superseded per TRACE_FINDINGS §2) — running it left norm=20 and the queue unchanged,
so an independent end-to-end forced-order proof was not reproducible this session.
</content>
