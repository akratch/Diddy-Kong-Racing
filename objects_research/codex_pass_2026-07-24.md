# func_80017A18 Codex pass — 2026-07-24

> Historical campaign record. Its `dscore.py` values should not rank current
> candidates. The exact asm-differ best is now 1472 / 94.72%; see
> `HANDOFF_func_80017A18.md` and `EXPERIMENT_LOG_2026-07-24.md`.

All scores use `objects_research/tools/dscore.py`. Only the candidate function
body is changed.

| # | Candidate / one change | Score | Insns | Frame | Breakdown |
|---:|---|---:|---:|---:|---|
| 0 | Supplied baseline `checkpoints/func_80017A18_dscore1945.c` | 1945 | 283 | -296 | ins=5 del=1 reord=3 reg=105 stack=640 |
| 1 | Clean m2c-shaped rewrite using named locals and pointer iteration | 13952 | 283 | -312 | ins=46 del=42 reord=2 reg=236 stack=3852 |
| 2 | Near-literal m2c variable/control-flow rewrite | 12700 | 268 | -328 | ins=34 del=45 reord=5 reg=264 stack=3180 |
| 3 | Baseline rewritten coherently with origin copies inside the facet guard and all plane/intersection/restore reads using them | 8839 | 285 | -288 | ins=37 del=31 reord=7 reg=199 stack=624 |
| 4 | Baseline outer loop converted wholesale to explicit pointer iteration, preserving inner array re-reads | 4672 | 286 | -272 | ins=13 del=6 reord=2 reg=132 stack=1992 |
| 5 | Only `originPointsX` converted to early pointer advance and `[-1]` re-reads | 1977 | 283 | -296 | ins=5 del=1 reord=4 reg=105 stack=612 |
| 6 | Move origin-copy creation/restoration inside separate facet-count guards, leaving the `for` loop intact | 9807 | 305 | -304 | ins=50 del=24 reord=5 reg=219 stack=1012 |
| 7 | Single facet-count guard around copy creation, facet `do` loop, and restore; inner array reads unchanged | 3313 | 290 | -296 | ins=13 del=2 reord=2 reg=209 stack=648 |
| 8 | Current upstream `NON_EQUIVALENT` body adapted verbatim to the host signature | 5951 | 280 | -288 | ins=26 del=25 reord=3 reg=67 stack=336 |
| 9 | Upstream body with both plane distances rewritten as direct ABCD-minus-radius chains | 7608 | 288 | -288 | ins=34 del=25 reord=5 reg=180 stack=508 |
| 10 | Upstream body with origin copies moved into a single facet-count guard | 5596 | 281 | -288 | ins=25 del=23 reord=2 reg=68 stack=336 |
| 11 | Guarded-upstream body with baseline `curPlanes`/`new_var3` plane-chain topology | 6693 | 282 | -296 | ins=27 del=24 reord=2 reg=157 stack=688 |
| 12 | Guarded-upstream body with three dedicated per-facet intersection-copy locals | 8652 | 286 | -304 | ins=36 del=29 reord=5 reg=152 stack=1092 |
| 13 | Reuse edge-plane coefficient locals as the three intersection copies | 7978 | 286 | -288 | ins=36 del=29 reord=5 reg=150 stack=428 |
| 14 | Guarded-upstream body with target-distance chain interleaved between the two halves of the origin-distance chain | 5731 | 281 | -288 | ins=25 del=23 reord=2 reg=151 stack=56 |
| 15 | Guarded-upstream body with explicit m2c-style cached `A*x1` and `C*z1` locals | 8136 | 286 | -296 | ins=35 del=28 reord=3 reg=180 stack=756 |
| 16 | Remove the trailing empty `if (!var_f22)` fakematch from the 1945 baseline | 2023 | 282 | -296 | ins=5 del=2 reord=2 reg=111 stack=648 |
| 17 | Remove only the inner empty `if (sum2)` fakematch from the 1945 baseline | 1953 | 283 | -296 | ins=5 del=1 reord=3 reg=105 stack=648 |
| 18 | Change only `redoLoop` from `u32` to `s32` in the 1945 baseline | 2145 | 283 | -296 | ins=6 del=2 reord=3 reg=105 stack=640 |
| 19 | Change only `var_s6` from `s32` to `u32` in the 1945 baseline | 1945 | 283 | -296 | ins=5 del=1 reord=3 reg=105 stack=640 |
| 20 | Change only edge-test `ret` from `s32` to `u32` in the 1945 baseline | 1945 | 283 | -296 | ins=5 del=1 reord=3 reg=105 stack=640 |
| 21 | Reuse dead `sum1`/`t` for edge coefficients A/B, removing two locals | 1954 | 283 | -288 | ins=5 del=1 reord=3 reg=118 stack=584 |
| 22 | Reuse dead `sum1`/`t` for edge coefficients A/C, removing two locals | **1944** | 283 | -288 | ins=5 del=1 reord=3 reg=116 stack=584 |
| 23 | Reuse dead `sum1`/`t` for edge coefficients A/D, removing two locals | **1924** | 283 | -288 | ins=5 del=1 reord=3 reg=112 stack=584 |
| 24 | Reuse dead `sum1`/`t` for edge coefficients B/C, removing two locals | 1964 | 283 | -288 | ins=5 del=1 reord=3 reg=120 stack=584 |
| 25 | Reuse dead `sum1`/`t` for edge coefficients B/D, removing two locals | **1944** | 283 | -288 | ins=5 del=1 reord=3 reg=116 stack=584 |
| 26 | Reuse dead `sum1`/`t` for edge coefficients C/D, removing two locals | 1954 | 283 | -288 | ins=5 del=1 reord=3 reg=118 stack=584 |
| 27 | Swap the A/D reuse mapping so `t` carries A and `sum1` carries D | **1944** | 283 | -288 | ins=5 del=1 reord=3 reg=116 stack=584 |
| 28 | Reuse dead `t`/`new_var3` for edge coefficients A/D | **1944** | 283 | -288 | ins=5 del=1 reord=3 reg=116 stack=584 |
| 29 | Reuse dead `sum1`/`new_var3` for edge coefficients A/D | **1879** | 283 | -288 | ins=5 del=1 reord=3 reg=103 stack=584 |
| 30 | On the 1879 candidate, explicitly pointer-iterate both origin Y/Z arrays | 2616 | 285 | -280 | ins=8 del=2 reord=2 reg=108 stack=956 |
| 31 | On the 1879 candidate, explicitly pointer-iterate only origin Z | 2138 | 284 | -288 | ins=7 del=2 reord=2 reg=106 stack=588 |
| 32 | Add a surface-pointer alias while reusing `t` for edge coefficient B | 2195 | 283 | -288 | ins=6 del=2 reord=2 reg=135 stack=600 |
| 33 | On the 1879 candidate, also reuse `t` for edge coefficient B (three locals removed total) | 1994 | 283 | -288 | ins=5 del=1 reord=3 reg=114 stack=644 |
| 34 | On the 1879 candidate, instead also reuse `t` for edge coefficient C | 1974 | 283 | -288 | ins=5 del=1 reord=3 reg=110 stack=644 |
| 35 | Remove the self-assignment of `new_var3` from the 1879 candidate | **1879** | 283 | -288 | ins=5 del=1 reord=3 reg=103 stack=584 |
| 36 | Simplify `((0, originPointsY))[i]` to `originPointsY[i]` on the 1879 candidate | **1879** | 283 | -288 | ins=5 del=1 reord=3 reg=103 stack=584 |

## Best result

`checkpoints/func_80017A18_dscore1879_reuse_sum1_newvar3.c`

```text
score=1879  93.27%  [ins=5 del=1 reord=3 reg=103 stack=584]  insns=283
frame=-288
```

Relative to the supplied 1945 baseline, reusing the dead `sum1` and
`new_var3` webs for edge-plane coefficients A and D removed two declared
locals. This reached the target frame, reduced stack penalty by 56, and also
reduced register penalty by two operand fields (10 points), for a total
improvement of 66.

The coherent m2c/upstream-shaped lineages reached the correct frame and, in
one case, low register/stack penalties, but their main-plane opcode schedules
were too different to compete. Moving the origin copies inside the guard,
pointer-iterating origins, removing load-bearing fakes, and reusing a third
edge coefficient all scored worse.

The most promising next step is to retain the 1879 source's exact opcode
alignment and A/D web reuse, then target the remaining opcode deltas
individually: the origin-master prologue/late `s7` increment, the one extra
main-plane reload versus the target's D reload, the missing post-facet `nop`,
and the final redundant origin store. Coherent rewrites of those regions
should be avoided unless they preserve the surrounding instruction schedule.
