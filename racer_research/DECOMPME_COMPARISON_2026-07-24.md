# Head-to-head: our source vs. the decomp.me community best

The community's best public scratch for `func_80049794`
(https://decomp.me/scratch/SlvtN, reported **score 4837 / 98.16%**) was
compiled in our isolated harness against the real target object, with its
function body spliced onto our translation-unit preamble so the only
variable is the function source itself.

## Result

| metric | decomp.me best | **ours (`best_19`)** | target |
|---|---|---|---|
| instructions | 2622 | **2625** | 2625 |
| stack frame | -248 | **-248** | -248 |
| reloc-masked matching words | **551 / 2625 (21.0%)** | **2606 / 2625 (99.28%)** | 2625 |
| normalized diffs | 2074 | **19** | 0 |
| `f20` operands | **0 (absent)** | **74** | 74 |
| `f21` operands | 0 | 2 | 2 |
| `f14` operands | 112 (spill scratch) | 50 | 50 |

Ours matches **2,606** instruction words; the community best matches
**551**. The decomp.me percentage is that site's own weighted score
(it credits matching opcodes and structure); by actual instruction-word
identity the public scratch is at ~21%.

The reason is visible in one line. The scratch still uses the
single-statement form

```c
var_f20 = sqrtf((x*x) + (z*z) + (y*y)) - 2.0;
```

which never triggers the callee-saved promotion: its build contains **no
`f20`/`f21` at all**, and the long normalization factor spills through
`f14` (112 operands vs. the target's 50). Our two-statement form

```c
var_f20 = (x*x) + (z*z) + (y*y);
var_f20 = sqrtf(var_f20) - 2.0;
```

merges the pre-call input and post-call factor into one web and
reproduces the target's entire FP allocation. That single discovery is
the difference between 551 and 2,606 matching words.

The public scratch also still carries the invariant wave guard
(`(gRacerWaveCount - 1) >= 0`), i.e. the `bltz v1` backedge bug we
eliminated this session.

## What we adopted from it

Its rotation arms drop the `var_v1` cache and write the field directly:

```c
obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
obj->trans.rotation.x_rotation -= (((var_t0 >> 1) * 19) * updateRate) >> 1;
```

Compiled into our source this is **byte-identical** (sha1 `e95892dd53eb`,
2606/2625, same 19 indices) but is more natural C. Adopted into
`checkpoints/func_80049794_best_19_clean_arms.c` and `src/racer.c`.
This also independently confirms the arm-respell equivalence class
measured earlier: the two spellings share one dataflow graph.

## What we rejected from it

- **Its declaration order**: transplanted onto our body it costs 6 extra
  diffs (2600/2625; new stack-offset-driven differences at 857, 859,
  2419, 2596, 2599, 2612). Our tuned order is load-bearing.
- **`obj->y_velocity = racer->oy1 * racer->velocity;`** (operand order):
  adds 2 diffs at 1298-1299.
- **Its steering-clamp shape** (cached `var_v1` + separate
  `xRotationOffset`): costs 33 extra diffs (norm 52).

Notably, none of these upstream perturbations moved the 19 rotation
diffs at all — independent corroboration that the residual is invariant
under source-level change (see `TRACE_FINDINGS_2026-07-24.md` §6c-6f).

## Convergent evidence

The scratch independently contains the same `(var_v0 ^ 0) ==
PLAYER_COMPUTER` idiom and the same `((0x180 & 0xFFFFFFFF) ...)` mask
chain as our lineage, confirming those two fakematch-flavored spellings
are genuinely load-bearing for this compiler and not artifacts of our
search.

## Tooling note

Raw-word comparison (the true match metric, immune to the normalized
score's stripping of immediates and stack offsets) is now
`tools/raw_compare.py`. Prefer it over `verify_candidate.py` when
comparing sources whose stack layouts may differ.
