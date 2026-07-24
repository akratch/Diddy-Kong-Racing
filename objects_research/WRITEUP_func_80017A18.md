# `func_80017A18` — reconstruction write-up (2026-07-24)

Object-collision resolution routine, `src/objects.c`. Target: 279 instructions,
stack frame `-0x120`. **MATCHED — score 0 / 100.00%**, compiled from ordinary C
with no fakematch or UB scaffolding. `GLOBAL_ASM` removed; the full ROM builds
and verifies OK, taking Adventure One to 99.48%.

---

## 1. What the function does

Recovered entirely from `asm/nonmatchings/objects/func_80017A18.s`.

```c
s32 func_80017A18(ObjectModel *arg0,   // collision model
                  s32   arg1,          // point count
                  s32  *arg2,          // out: collision counter
                  f32  *arg3,          // origin X   (read-only)
                  f32  *arg4,          // origin Y
                  f32  *arg5,          // origin Z
                  f32  *arg6,          // current X  (read/write)
                  f32  *arg7,          // current Y
                  f32  *arg8,          // current Z
                  f32  *arg9,          // radius
                  s8   *argA,          // out: surface flags
                  f32   argB);         // radius scale
```

For each of `arg1` points it resolves the segment origin→current against the
model's collision facets:

- `radius = arg9[i] * argB`.
- For each facet: fetch the base plane `(A,B,C,D)` and form the signed plane
  distances of the origin and current points, each biased by `radius`.
- If the origin is outside (`>= -0.1`) and the current point is inside
  (`< -0.1`), interpolate the crossing point, then test it against the facet's
  three edge-bisector planes (early-out on the first `> 4.0f`).
- On a real hit: if the plane is near-horizontal (`B > 0.707`) solve for Y on
  the plane, otherwise push the point out along the normal. Write the point
  back, clear the surface byte, and restart the facet scan.
- The restart loop is capped at 10 iterations; on overflow the point is reset
  to the origin.
- Returns a bitmask of which points collided, one bit per point.

## 2. How the source shape was pinned down

Every structural decision below is backed by a specific instruction in the
target, not by taste.

### 2.1 The 33 locals and their order are fully determined

IDO lays locals out at descending addresses. Assuming a start of `0x11c` and
the declaration list in `src/objects.c`, every stack home the target actually
references falls out:

```text
0x11c planes    0x118 i        0x114 j          0x110 k       0x10c sum1
0x108 sum2      0x104 t        0x100 var_a2     0xfc  counter 0xf8  spF8   *
0xf4  var_s6    0xf0  node     0xec  pad        0xe8  closestTri
0xe4  A      *  0xe0  B        0xdc  C       *  0xd8  D     *
0xd4  A1        0xd0  B1       0xcc  C1         0xc8  D1     0xc4  redoLoop
0xc0  spC0   *  0xbc  x1     *  0xb8  y1         0xb4  z1    *
0xb0  x3        0xac  y3       0xa8  z3
0xa4  x2     *  0xa0  y2     *  0x9c  z2      *
```

`*` = confirmed by an instruction. Ten of ten land correctly, so the list is
right in both content and order. Below `0x9c` sit the compiler's own temp
slots — the target uses `0x60/0x64/0x68/0x70/0x74` for FP spills and `0x80`
for the `arg9` induction pointer; we match all six.

Follow-up measurement: declaration order is **inert** for register allocation
in this function. 330 relocations and swaps among the unreferenced slots all
compile byte-identically.

### 2.2 The guarded facet loop

The target stores the three origin values *after* the facet-count branch:

```text
00f0  blez  t3, .Lskip
00f4   move t2, zero          # j = 0 in the delay slot
00f8  swc1  f18, 0xa4(sp)
00fc  swc1  f20, 0xa0(sp)
0100  swc1  f22, 0x9c(sp)
```

That is an explicit `if (count > 0) { … }` around a `do/while`, not a `for` —
a `for` puts the spills before the branch:

```c
j = 0;
if (arg0->collisionFacetCount > 0) {
    do { … j++; } while (j < arg0->collisionFacetCount);
}
```

### 2.3 Those stores are spills, not copies

This is the point that took longest to see, and it is written up in §5. The
`swc1`/`lwc1` pair around the facet loop is the compiler saving and restoring
the origin values, because `f18`/`f20`/`f22` are needed inside the loop —
`f18` becomes the scaled radius at `0x0120`. There is no second set of origin
variables and no save/restore block in the source; the origins are read once
per outer iteration into `x2/y2/z2`.

### 2.4 `var_a2` must be `u32`, and assigned after the `t` branch

The target emits `li a2,1` for `var_a2 = TRUE`, and separately hoists a `1`
into `a3` for the k-loop test `beq a2,a3`. If the assignment is written before
the interpolation-factor branch, IDO CSEs the two constants and emits
`move a2,a3` instead. Declaring `var_a2` as `s32` also breaks it (≈180 points).

### 2.5 IDO emits `add.s`/`mul.s` operands in source order

Verified directly, not assumed: compiling `sum1 = B*y2 + A*x2 + …` emits
`add.s dst, (B*y2), (A*x2)`, i.e. left operand first. So the target's

```text
0134  mul.s f14, f26, f6    # B*y2   (scheduled first)
0144  mul.s f4,  f16, f28   # A*x2
0158  add.s f4,  f4,  f14   # A*x2 + B*y2
```

really does mean `A*x2` is written first in the source; the earlier `B*y2`
multiply is the scheduler filling the load-use slot of A's load at `0130`.

## 3. Measurement

The only metric used is the repository's own asm-differ, driven through
`objdump -d -rz -j .text`:

```sh
.venv/bin/python3 objects_research/tools/realscore.py <candidate.c>
.venv/bin/python3 objects_research/tools/realdiff.py  <candidate.c>
```

This reproduces decomp.me exactly on two calibration sources. A normalizing
metric (one that rewrites `N(sp)` to a placeholder) misranks candidates here
because it hides whole-frame shifts — that mistake cost a previous session most
of its time.

A search harness was built on top: a slotted source template, a config-space
renderer with coordinate descent, multi-axis joint sweeps, a randomised
annealer, and a full-context diff. One compile-and-score round trip is ~0.2 s,
giving 25–50 candidates/second across the machine.

## 4. The path to the match

The starting point was a 1472 / 94.72% source built from fakematch and UB
constructs (`var_f18 = var_f18;`, `if (sum2) {}`, `& 0xFFFFFFFFFFFFFFFF`,
comma-operator probes). It was abandoned: a structurally cleaner 1790 branch
had exact frame, stack homes and long-lived GPRs with the mismatch confined to
one basic block.

| # | change | score |
|---|---|---:|
| — | guarded natural branch (inherited) | 1790 |
| 1 | `sum1 = (A*x2 + B*y2) + (C*z2 + D)` | 1752 |
| 2 | edge-plane sum as one flat expression | 1712 |
| 3 | radius staged through a dead local | 1377 |
| 4 | `var_a2 = TRUE` moved after the `t` branch | 1177 |
| 5 | hit point computed y, x, z | 1088 |
| 6 | `sum1 = (A*x2 + D) + (B*y2 + C*z2)` | 742 |
| 7 | hit point computed z, y, x | 400 |
| 8 | edge index staged through the dead `triIndex` | 355 |
| 9 | community: flat sum + deltas split out + `y3 = x2` in-loop | 296 |
| 10 | **origins read straight into `x2/y2/z2`; save/restore deleted** | 441 |
| 11 | **interpolation deltas computed x, y, z** | **0** |

Step 10 *raises* the score and is still the decisive move — see below.

## 5. The insight that finished it

Every attempt through step 9 modelled this pair

```text
00f8  swc1  f18, 0xa4(sp)      ...      0380  lwc1  f22, 0x9c(sp)
00fc  swc1  f20, 0xa0(sp)               0384  lwc1  f20, 0xa0(sp)
0100  swc1  f22, 0x9c(sp)               0388  lwc1  f18, 0xa4(sp)
```

as *source-level copies*: a second set of origin variables saved at the head of
the facet-count guard and restored at its tail. That reading forced a whole
scaffolding of double-duty variables (`y3`/`z3`/`sum2` holding origins and also
serving as the hit point), and it is what kept the flat accumulator chain — the
form the target obviously computes — out of reach.

They are not copies. They are the **compiler spilling and restoring** the origin
values around the facet loop, because those registers are needed inside it:
`f18` becomes the scaled radius at `0x0120`. Under that reading the source is
far simpler — the origins are read directly into `x2/y2/z2` in the outer loop
and the save/restore block does not exist at all:

```c
x1 = arg6[i];
y1 = arg7[i];
z1 = arg8[i];
x2 = arg3[i];
y2 = arg4[i];
z2 = arg5[i];
spC0 = arg9[i] * argB;
```

That change *raises* the exact score from 296 to 441 — but it makes the
instruction **order** exact: `insert=0, delete=0, reorder=0` at 279
instructions, with the entire remaining penalty a rotation of the low FP temp
pool `{f4, f6, f8}`. Computing the interpolation deltas in `x, y, z` order
rather than `z, y, x` resolves the rotation, and the function matches.

The methodological point: **score is not distance.** The move that finished the
function looked like a 147-point regression. Structural penalties
(`insert`/`delete`/`reorder`) are the signal worth steering by; register
penalties are a phase problem that resolves once the structure is right.

## 6. Two reusable techniques

**A store/reload pair around a loop is not necessarily a source-level copy.**
Check whether the register is reused inside the loop before modelling it as a
variable. That single misreading cost the bulk of this campaign.

**A redundant assignment through an already-dead local shifts the allocator
phase for free.**

```c
triIndex = node->edgeBisectorPlane[k];   /* triIndex is dead here */
closestTri = triIndex;
```

IDO coalesces it — no instruction is emitted — but the order in which the
allocator's free list is touched changes, rotating the whole register
assignment by one slot. This was worth roughly 300 points twice on the way
here, once on the FP side and once on the GPR side. Reach for it whenever a
diff reads as "correct instructions, rotated registers". The final source no
longer needs it.

## 7. Search effort

Roughly 30,000 exact-scored candidates across: all 24 term orders x 5 parse
trees for both dot products (14,400 combinations); 5,040 prolog statement
orders; every hit-point order and form; plane and edge-plane load orders;
statement-split, compound-assignment and alternate-accumulator forms; 330
declaration relocations and swaps (declaration order is inert for register
allocation here); 181 staging-variable insertions; multiplication operand
orientation; `register` storage class on every local and parameter (inert);
explicit `f64` comparison webs; control-flow spellings; coordinate descent over
30+ axes; randomised multi-axis annealing; and roughly 120,000 decomp-permuter
iterations, which found step 8.

## 8. Where the source lives

- `src/objects.c` — compiled from C, `GLOBAL_ASM` removed, ROM verifies OK.
- `objects_research/func_80017A18_best.c` — the function alone.
- `https://github.com/akratch/dkr-func80017A18-wip` — function, full
  translation unit, and notes, for decomp.me.
