# `func_80017A18` authoritative handoff — 2026-07-24 (evening)

Collision routine at `src/objects.c:5403`. This supersedes every earlier
version of this file; the numbers in the older campaign documents were
produced before the exact scorer existed and should be read as history only.

## Current state

**355 / 98.73%**, integrated into `src/objects.c` behind
`#ifdef NON_EQUIVALENT` (so the ROM build still uses `GLOBAL_ASM` and
verifies OK).

```text
score=355  98.73%  max=27900
stack=40  reg=255  reorder=60  insert=0  delete=0
target_insns=279  candidate_insns=279
```

Previous best was 1472 / 94.72% (`objects_research/func_80017A18_codex_work.c`,
a fakematch/UB-laden source). The current source is ordinary C: no fakematch,
no UB, no dead stores, no `register`/`volatile`.

Also mirrored to the standalone WIP repo (function alone + full TU + notes):
`https://github.com/akratch/dkr-func80017A18-wip`.

## What matches exactly

- 279 instructions and stack frame `-0x120`;
- **every opcode count** (instruction mix is identical);
- **instruction order**: `insert=0`, `delete=0`, a single reordering left
  (`sll t9,t2,0x3` sits one slot early);
- all 33 declared locals land on the target's stack homes;
- the long-lived GPR map and the compiler temp slots
  `0x60/0x64/0x68/0x70/0x74/0x80`;
- the whole tail of the function from `0x01c0` onward except register names.

## The four levers that took 1472 → 400

1. **Guarded facet loop** — `if (arg0->collisionFacetCount > 0) { saves; do
   {...} while (...); restores; }`. Puts the three origin `swc1`s after the
   `blez`, matching the target's control topology. (This was the previous
   session's 1790 branch; it is the right skeleton.)
2. **`sum1 = (A * x2 + D) + (B * y2 + C * z2);`** — the single change that
   drove `insert`/`delete` to zero. Found by exhaustively scoring all 24 term
   orders × 5 parse trees for both sums (14,400 combinations). 400 is the
   unique minimum of that space.
3. **`var_a2 = TRUE` after the interpolation-factor branch.** Before it, IDO
   CSEs the constant with the `1` it hoists into `a3` for the k-loop test and
   emits `move a2,a3`; after it, we get the target's `li a2,1`. `var_a2` must
   stay `u32` (`s32` costs ~180).
4. **Hit point computed z, y, x.** Worth 342 on its own. The target computes
   x, y, z — this reversal is compensating for the FP rotation below and is the
   one element of the source that is probably not original.

## Declaration order is solved

The 33 locals reproduce every observed stack home. IDO assigns them descending
from `0x11c`; the ten slots the target actually references (`spF8` 0xf8,
`A` 0xe4, `C` 0xdc, `D` 0xd8, `spC0` 0xc0, `x1` 0xbc, `z1` 0xb4, `x2` 0xa4,
`y2` 0xa0, `z2` 0x9c) all land correctly.

Declaration order is **inert** for register allocation here: 330 relocations
and swaps among the unreferenced slots all score exactly 400. Do not spend
time on declaration shuffling again.

## What is left, and why

One extra live FP value in the facet-loop head. The target's origin sum is a
flat accumulator chain, so the `B*y2` partial dies at the first add and `f14`
is free for `B*y1`:

```text
target                          this source
mul.s f14, f26, f6   B*y2       mul.s f6,  f26, f28
mul.s f4,  f16, f28  A*x2       mul.s f16, f16, f20
add.s f4,  f4,  f14             add.s f16, f16, f12   (A*x2 + D)
...                             ...
mul.s f14, f26, f30  B*y1       mul.s f2,  f26, f30   <-- f2, not f14
```

`(A*x2 + D) + (B*y2 + C*z2)` keeps two partials alive across the final add, so
IDO reaches into `f2` and the whole low-temp pool (`f4/f6/f10/f12/f14/f16`)
rotates by one. That rotation accounts for essentially all 51 mismatched
register fields, the four stack-offset diffs, and the single reordering.

**The remaining problem, stated precisely:** find a source shape that produces
the *flat* accumulator chain `((A*x2 + B*y2) + C*z2) + D` **and** keeps the
three origin loads (`0xa4/0xa0/0x9c`) hoisted above the facet-index
computation, the way the target does at `0x0108`–`0x0110`.

Every flat variant tried so far interleaves those loads with the plane loads,
gains a `nop` (280 instructions), and scores ~3700. The operand-order rule was
verified directly: IDO emits `add.s`/`mul.s` operands in source order, so the
target's `add.s f4,f4,f14` really does mean `A*x2 + B*y2` with `A*x2` written
first, and the earlier `mul.s f14,f26,f6` is the scheduler filling a load-use
slot — not evidence of a different source order.

## Searched and exhausted (exact scorer throughout)

- 14,400 term-order × parse-tree combinations for both dot products;
- 5,040 prolog statement orders; 7,200 prolog staging/order/mul-order combos;
- all hit-point orders × forms × `var_a2` positions;
- plane and edge-plane load orders, edge-sum trees, comparison spellings;
- 600 statement-split / compound-assignment accumulation forms;
- 309 alternate-accumulator forms (every one adds instructions);
- 330 declaration relocations and swaps;
- control-flow spellings: outer loop form, guard form, `counter` form, `j`
  update, store order, save/restore/reset orders, `arg2[0]++` spellings;
- coordinate descent over 30 axes — converged, and re-converged after each
  axis was added;
- randomised 1–4 axis annealing over the same space;
- decomp-permuter with the exact scorer, ~100k iterations across three bases.

## Tooling

Score and diff (these drive the repo's own asm-differ and reproduce
decomp.me exactly):

```sh
.venv/bin/python3 objects_research/tools/realscore.py <candidate.c>
.venv/bin/python3 objects_research/tools/realdiff.py  <candidate.c>
```

The search harness built this session lives in the session scratchpad under
`h/`: `tmpl2.py` (slotted source template), `descend2.py` (config-space
renderer + coordinate descent), `joint.py` (multi-axis sweeps), `anneal.py`
(randomised search), `sweep.py`/`probe.py` (ad-hoc generators), `fd.sh`
(full-context diff). A single compile+score is ~0.2 s, so ~25–50 candidates/s
across the box.

Both scorers depend on the preserved toolchain under
`/private/tmp/claude-501/.../17d442b1-.../scratchpad`. If that tree
disappears, recreate the isolated object harness and update the `SP`
constants in `realscore.py` and `realdiff.py`.

## Do not repeat

- declaration-order shuffling (measured inert);
- alternate accumulator variables for the dot products (all add instructions);
- wholesale m2c rewrites; pointer-iterating the origin arrays;
- `register`/`volatile` qualifiers, forced allocator decisions;
- the fakematch/self-assignment scaffolding from the old 1472 lineage — the
  current clean source is 1072 points ahead of it.
