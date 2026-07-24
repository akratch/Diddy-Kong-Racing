# func_80017A18 instruction-count campaign (2026-07-24)

> Historical campaign record. Instruction count and normalized alignment were
> useful diagnostics, but current candidates must be ranked with
> `tools/realscore.py`. The verified best is 1472 / 94.72%; see
> `HANDOFF_func_80017A18.md`.

Target = 279 insns. Baseline candidate = 280 (+1), aligned-identical 224/279, edit distance 91.
Scoring: `objects_research/tools/obj_score.py`. Region under test = the plane-coefficient
loads + the sum1/sum2 accumulation inside the j-loop.

## Region semantics (verified from target disassembly)
- 188(sp)=x1, f30=y1(callee-saved), 180(sp)=z1, spC0=192(sp)
- x2/y2/z2 spilled at 164/160/156(sp) at top of do-loop, reloaded per j-iteration
- TARGET computes sum1 (x2 chain) FIRST, sum2 (x1 chain) second
- TARGET keeps B in callee-saved f26; homes A->228(sp), C->220(sp), D->216(sp), each
  store immediately followed by reload (live-range split)
- TARGET also CSEs A*x1 ->116(sp) and C*z1 ->112(sp) for the later `y1 = (spC0-(A*x1+C*z1+D))/B`
- CANDIDATE emits the same 3 coefficient homes, PLUS an extra spill/reload pair of the
  C*z2 partial at 108(sp) (insn 96 `swc1 f4,108(sp)` / insn 103 `lwc1 f4,108(sp)`).
  It also evaluates the x1 chain first (inverted vs target).

## Batch 1 - association / statement-splitting / load order
| construct | insns | delta | aligned-identical | edit dist | verdict |
|---|---|---|---|---|---|
| v00_base (`s2=Ax2+By2; s1=s2+Cz2+D-c; s2=Ax1+By1+Cz1; s2+=D; s2-=c;`) | 280 | +1 | 224 | 91 | baseline |
| v01_full_both (one expr each, sum1 first) | 288 | +9 | 167 | 172 | worse |
| v02_full_swapped (one expr each, sum2 first) | 288 | +9 | 167 | 172 | worse |
| v03_mirror (both chains split as `X=Ax+By; X=X+Cz+D-c`) | 281 | +2 | 184 | 144 | worse |
| v04_mirror_swapped | 286 | +7 | 163 | 158 | worse |
| v05_temp_t (shared temp `t` for both partials) | 281 | +2 | 170 | 161 | worse |
| v06_temp_t_swapped | 289 | +10 | 162 | 165 | worse |
| **v07_pluseq (every product its own `+=` stmt, sum1 first)** | **279** | **0** | 164 | 171 | **COUNT HIT** |
| v08_pluseq_swapped (sum2 chain first) | 286 | +7 | 160 | 192 | worse |
| v09_paren (explicit full parenthesisation) | 288 | +9 | 167 | 172 | worse |
| v10_base_sum1temp (base, `sum1` as the partial temp) | 280 | +1 | 224 | 91 | identical to base |
| v11_base_x1_first | 286 | +7 | 163 | 157 | worse |
| v12_loadBACD (load order B,A,C,D) | 280 | +1 | 224 | 91 | no effect |
| v13_loadDCBA | 281 | +2 | 224 | 90 | edit -1, count +1 |
| v14_loadBCDA | 281 | +2 | 225 | 87 | **edit -4**, count +1 |
| v15_loadACDB | 280 | +1 | 224 | 91 | no effect |
| v16_ptr (`pl=&planes[4*tri]; A=pl[0]...`) | 281 | +2 | 183 | 145 | worse |
| v18_full_both_noB (B*y first in each expr) | 288 | +9 | 173 | 154 | worse |
| v19_sum2_partial_shared (`X=Ax+By+Cz; X=X+D-c`) | 281 | +2 | 164 | 172 | worse |

Finding: statement granularity of the accumulation is the lever that moves the count.
Load order of A/B/C/D moves edit distance but not favourably on count.

## Batch 2 - 7x7 "split level" cross product (chain1 = sum1/x2 first, chain2 = sum2/x1)
Levels: L0 one expr; L1 `X=Ax+By; X=X+Cz+D-c`; L2 `X=Ax+By+Cz; X+=D; X-=c`;
L3 all-`+=`; L4 `X=Ax+By; X+=Cz; X+=D; X-=c`; L5 `X=Ax+By+Cz+D; X-=c`; L6 `X=Ax+By+Cz; X=X+D-c`.

| chain1 \ chain2 | L0 | L1 | L2 | L3 | L4 | L5 | L6 |
|---|---|---|---|---|---|---|---|
| L0/L2/L3/L4/L5/L6 (all identical) | 288 | 281 | **279** e107 | **279** e171 | 278 | 281 | 281 |
| **L1** | 286 | 281 | 280 e91 (base) | **279** e141 | **278** e85 | 281 | 281 |

Finding: chain1 level is inert except for L1 (the base form), which is the only one preserving
the 224-identical alignment. chain2 level is the count dial: L2->280, L3->279, L4->278.
So the count moves in 1-instruction steps with the statement granularity of the SECOND chain.

## Batch 3 - full 16x16 statement-partition sweep (256 runs)
Partition mask = which of the 4 gaps in `A*x | B*y | C*z | D | -spC0` are statement breaks.
Every combination compiled; results clustered tightly. Key rows:

| construct | insns | aligned-identical | edit | verdict |
|---|---|---|---|---|
| **M01_10 / M05_10 / M09_10 / M13_10** | **279** | **224** | **81** | **WINNER** |
| M00_10, M04_10, M06..M08_10, M12_10, M14_10, M15_10 | 279 | 220 | 88 | count ok, worse |
| M0x_12 family | 279 | 214 | 107 | count ok, worse |
| M02_10, M03_10, M10_10, M11_10 | 279 | 177 | 141 | count ok, much worse |
| M01_06 | 280 | 224 | 81 | +1 |
| M02_14 / M03_14 / M10_14 / M11_14 | 278 | 220 | 85 | -1 |
| M01_14 | 278 | 181 | 129 | -1 |

Winning source (mask a=1 for chain1: split `A*x2` into its own statement;
mask c=10 for chain2: `A*x1+B*y1` / `+C*z1+D` / `-spC0`):
```c
sum1 = A * x2;
sum1 = sum1 + B * y2 + C * z2 + D - spC0;
sum2 = A * x1 + B * y1;
sum2 = sum2 + C * z1 + D;
sum2 -= spC0;
```
FP association is bit-identical to the original in both chains (verified term by term).

## Batch 4 - chain2 emitted before chain1 in source (256 runs)
Zero 279 hits; best edit = 148 (S05_xx, 286 insns). Source order sum1-then-sum2 is mandatory.

## Batch 5 - A/B/C/D load-order permutations x (`+=` vs `X = X + t`) on the winner (48 runs)
`+=` vs `X = X + t` makes NO difference anywhere (every pair scored identically).
| load order | insns | same | edit |
|---|---|---|---|
| ABCD (winner) | 279 | 224 | 81 |
| BACD | 279 | 224 | 81 |
| ACBD | 279 | 224 | 82 |
| ABDC / BADC | 279 | 221 | 87 |
| ADBC | 279 | 221 | 90 |
| DBCA | 281 | 223 | 78 (count broken) |
| BCAD | 280 | 224 | 79 (count broken) |
| CABD / CBAD | 280 | 224 | 80 (count broken) |
Nothing beats ABCD while holding 279.

## Batch 6 - non-accumulation levers on the winner (16 runs)
| construct | insns | same | edit |
|---|---|---|---|
| winner (control) | 279 | 224 | 81 |
| `var_a2` as s32 / int | 279 | 223 | 82 |
| `var_a2` as u16 / u8 | 279 | 222 | 82 |
| `var_a2` as s16 | 281 | 197 | 123 |
| `var_a2 = 1` instead of TRUE | 279 | 224 | 81 (no change) |
| k-loop cond `var_a2` / `var_a2 != 0` | 272 | 161 | 170 |
| k-loop cond order `var_a2 && k<3` | 283 | 167 | 161 |
| k-loop as `while` | 279 | 224 | 81 (no change) |
| CSE temps `ax1=A*x1; cz1=C*z1` (+ reuse in the `B>0.707` arm) | 284 | 176 | 142 |
| local copies of x2/y2/z2 at j-loop top | 279 | 224 | 81 (no change) |
| pre-scaled `triIndex *= 4` | 279 | 224 | 81 (no change) |
u32 for `var_a2` is confirmed optimal. The remaining `move a2,a3` vs target `li a2,1`
is register allocation, not source shape.

## Batch 7 - statement ordering around the do-loop (29 runs)
All 24 permutations of `redoLoop=FALSE; x2=y3; y2=z3; z2=sum2;` and all 6 permutations of
the `sum2=z2; z3=y2; y3=x2;` epilogue. Every one holds 279 insns; best is the original
order at edit 81, everything else 82-85. No gain.

## RESULT
- **279 instructions reached** (was 280). Edit distance improved 91 -> 81, aligned-identical
  held at 224/279. Checkpoint:
  `objects_research/checkpoints/func_80017A18_count279_edit81_M01_10.c`
- Lever family that moves the count: **statement granularity of the sum1/sum2 accumulation**
  (how many `f32` statements the 5-term dot-product-plus-offset is broken into, and where the
  breaks fall). Chain2 (the x1/y1/z1 chain) is the fine dial: 3 statements -> 280,
  4 statements -> 279 or 278 depending on where the break is, 5 statements -> 279.
  Nothing else tried (load order, temp variables, pointer forms, `+=` vs `=`, loop-statement
  ordering, integer types) changes the count while preserving alignment.
- Remaining 55 differing positions after the fix are dominated by:
  (a) target loads x2/y2/z2 into f28/f6/f20 once at the j-loop head (tgt 66-68); candidate
      loads them lazily per use;
  (b) target homes A->228, C->220, D->216 with store-immediately-followed-by-reload; candidate
      homes C->228, D->224, A->236 and burns one extra 8-byte stack slot (296 vs 288 frame);
  (c) an unfilled `bc1f` delay slot (candidate insn 113 `nop`) where the target schedules
      `swc1 f8,112(sp)`;
  (d) ~9 pure register-name replaces (v1/a0/a1 in the k-loop, `li a2,1` vs `move a2,a3`).
  These are allocation/scheduling, i.e. the other agent's lane.
