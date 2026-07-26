
---

# Session: allocator-decision-path investigation → **func_80049794 MATCHES (diff 0)**

Agent: allocator-mechanism track. Base: `checkpoints/func_80049794_best_19_clean_arms.c` (19 diffs).
Result: `checkpoints/func_80049794_MATCH_diff0.c` — **insns=2625, norm=0, raw reloc-masked 2625/2625,
frame -248, FP histogram identical, sha1=160331871b28** (stock pipeline, `/tmp/isoeval.sh`).

## The winning source change (only change vs the 19-diff checkpoint)

```c
if (!(gCurrentRacerInput & R_TRIG)) {
    var_t0 >>= 1;                                        // NEW
    obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
    obj->trans.rotation.x_rotation -= ((var_t0 * 19) * updateRate) >> 1;   // was ((var_t0 >> 1) * 19)
} else {
    var_t0 >>= 1;                                        // NEW
    obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
    obj->trans.rotation.x_rotation -= ((var_t0 * 30) * updateRate) >> 1;   // was ((var_t0 >> 1) * 30)
}
```
(The `// Note: The following if/else has messed up t registers` comment was dropped — no longer true.)
`var_t0` is dead after the region, so uopt keeps the `>>= 1` as a temp-producing uop at the TOP of each
arm instead of folding it into the second statement's tree. No extra instruction is emitted.

## How it was found (mechanism, with line-level evidence)

1. **The region's allocator site is `f_get_dest`, not the `f_usage_count`/`f_is_available` sites.**
   All 22 region allocations (serials 236-257) come from ONE call site: `f_get_dest` @ ugen.c L45582
   (`f_get_dest` starts L45545, called from `f_eval`/`f_eval2` at tagged sites 61363/50883/64216/61780).
   `f_get_dest(node a0, hint a1)` has only TWO paths:
     - `a1 != 0x48` → `f_get_reg`/`f_get_fp_reg` (parent target-register hint)
     - `a1 == 0x48` → `f_get_free_reg` → `f_get_one_free_reg` → plain `f_remove_head` of 0x10019da4.
   **There is no dead-operand-reuse path here.** (The `f_usage_count`/`f_is_available` reuse logic at
   L60097/60142 and L65857/65869 is a different `f_eval` sub-path; instrumentation showed it is never
   reached for the region.) Verified: in `f_get_one_free_reg`, when the free list is non-empty the head
   is popped unconditionally — no availability/skip check.
2. **Per-allocation decision inputs, serials 236-257:** every one had `hint = 72 (0x48)` and took FIFO.
   The only non-null hints anywhere in the region were `hint=3` (v1) for the two `op=54` lvalue loads
   (nodes 101a0710 @L769, 1019fe58 @L772) — those don't touch the temp queue.
3. **Independently confirmed the entry-queue dead end:** replaying the region's 44 queue events over all
   5040 entry permutations reproduces the target register sequence 0 times. Also 0 solutions when
   allowing one held-register release, or 1-2 "hint" (remove-from-middle) allocations.
4. **Minimal deviation set (new `CODEX_UGEN_FORCEMASK` env flag added to ugen):** forcing only
   `{0,1,2,3,7,11,12,13,14,18}` reproduces diff=0. Simulating shows the deviations are perfectly
   symmetric between the two arms:
     - arm1: t6 sits at the queue head and is *passed over* by allocs #0-#3, taken by #4, re-taken at #7.
     - arm2: t7 sits at the head, passed over by #11-#14, taken by #15, re-taken at #18.
5. **Unique event-structure explanation.** Moving the alloc+free event pair of allocation **#4**
   (node 101a0248, op=116 = `var_t0 >> 1` of line 770) to the very TOP of arm 1, and of **#15**
   (node 1019f990, op=116 = `var_t0 >> 1` of line 773) to the top of arm 2, and then running plain FIFO
   from our unchanged entry queue `[t6 t4 t8 t9 t7 t3 t5]`, reproduces the target register sequence
   **exactly**. The consistent placements are only (popPos 0, pushPos 0 or 1) in each arm — an extremely
   tight fit. That is precisely what `var_t0 >>= 1;` at the top of each arm produces.

## Experiments log (all stock pipeline; base = 2625 insns / raw 19)

| construct | insns | raw diff | note |
|---|---|---|---|
| baseline checkpoint | 2625 | 19 | q=[t6 t4 t8 t9 t7 t3 t5] |
| L745 guard: `(x & R_TRIG) == 0 \|\| ...` | 2625 | 19 | queue unchanged |
| L745 guard: De Morgan `!(a && b && c)` | 2625 | 19 | queue unchanged |
| L745 guard: `((a && b && c) == 0)` | 2629 | — | |
| L745 extra parens / `!(x)` forms | 2625 | 19 | queue unchanged |
| move `var_t0 = gCurrentStickY;` above L745 | 2624 | — | loses an instruction |
| ternary for L752-755 | 2626 | — | |
| comma-fused float body | 2625 | 19 | raw 25 (immediates), norm 19 |
| region: swap `updateRate * x_rotation` | 2625 | 19 | |
| region: `updateRate * ((var_t0>>1)*k)` | 2623 | — | |
| region: `(var_t0>>1) * k * updateRate` (no parens) | 2625 | 19 | |
| region: `(k * (var_t0>>1)) * updateRate` | 2625 | 19 | |
| region: swap the two statements | 2626 | — | |
| region: arms swapped / condition inverted | 2625 | 31 | new diffs 1679,1692-1700,1705 |
| region: `/ 2` instead of `>> 1` | 2631 | — | |
| region: explicit `x = x - (...)` | 2625 | 19 | |
| hoist `var_t0>>1` into a declared local (xRotationOffset, temp_t7, steerVisualRotationOffset, zRotationOffset, var_v0, var_v1, racerSteerAngle, racerMiscAssetIdx) | 2625 | 19 | uopt folds it straight back |
| hoist `(var_t0>>1)*k` into a local | 2625 | 19 | folded back |
| `(s32)` cast on the shift | 2625 | 19 | |
| hand-expanded `*19` shift chain | 2626 | — | |
| `x += -(...)` | 2625 | 19 | |
| `(var_t0>>1) * (k * updateRate)` | 2623 | — | |
| **`var_t0 >>= 1;` at top of each arm** | **2625** | **0** | **MATCH** |

**No construct moved the entry queue** — it stayed `[t6 t4 t8 t9 t7 t3 t5]` in every variant that kept
2625 instructions. That was the right conclusion: the queue was never the problem.

## ugen.c instrumentation added (all env-gated; verified byte-identical with env unset)

- `CODEX_UGEN_DEC=1` → `CODEX-DEC` (decision path + operand usage counts/availability at the reuse sites),
  `CODEX-GETDEST` (caller line, node, op, hint, FIFO serial) and `CODEX-HINT` (non-null `fp` hints into
  `f_eval`). All `f_get_free_reg`/`f_get_dest` call sites are tagged with their ugen.c line number.
- `CODEX_UGEN_FORCEMASK=<bitmask>` → with `CODEX_UGEN_FORCE=22`, forces only the selected subset of the
  22 region allocations from the target map. Used to find the minimal deviation set.
- Verified: `traceeval.sh` with no env set produces a byte-identical object to `isoeval.sh`.
