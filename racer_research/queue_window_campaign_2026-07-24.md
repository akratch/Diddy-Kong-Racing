# func_80049794 — queue/window campaign → **FULL MATCH (diff = 0)**

Date: 2026-07-24. Base: `checkpoints/func_80049794_best_19_clean_arms.c` (19 diffs).
Result: `checkpoints/func_80049794_MATCH_diff0.c` — **norm=0, raw masked diff=0/2625,
insns=2625, frame -248, FP histogram unchanged, sha1=160331871b28**.

## The fix (2-line source change)

```c
if (!(gCurrentRacerInput & R_TRIG)) {
    var_t0 >>= 1;                                                 /* NEW: separate statement, FIRST in the arm */
    obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
    obj->trans.rotation.x_rotation -= ((var_t0 * 19) * updateRate) >> 1;   /* was (((var_t0 >> 1) * 19) * ...) */
} else {
    var_t0 >>= 1;
    obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
    obj->trans.rotation.x_rotation -= ((var_t0 * 30) * updateRate) >> 1;
}
```

`var_t0 = var_t0 >> 1;` works identically. Placement is load-bearing:
* shift **at the top of each arm** → diff 0
* shift **after** the damping statement → diff 19 (baseline)
* shift **hoisted before the if/else** → insns 2624 (emitted once, not twice)

`var_t0` is dead after the region (next write is line 918), so the mutation is safe.

## How it was found — the event-structure solver

Model (verified against a full ugen trace of the whole function; strict FIFO reproduced
every one of the 734 temp-queue operations exactly):

> With 7 temps and no queue exhaustion, the **pop sequence = Q0 ++ pushes in push order**.
> Hence the region's register sequence is fully determined by (entry queue, free order).

Region = 22 temp allocations (ugen serials 236-257), mapped from the trace:

| # | node op | construct | ours | target |
|---|---|---|---|---|
| A0 | leaf | `lw updateRate` for stmt-1 | t6 | **t4** |
| A1 | mul | `x_rotation * updateRate` | t4 | **t8** |
| A2 | shift | `>> 4` | t8 | **t9** |
| A3 | sub | `x_rotation - …` | t9 | **t7** |
| A4 | shift | **`var_t0 >> 1`** | t7 | **t6** |
| A5..A10 | | `*19`, `lw ur`, mul, `>>1`, `lh`, sub | t3 t5 t6 t4 t8 t9 | identical |
| A11..A14 | | else-arm stmt-1 | t7 t3 t5 t6 | **t3 t5 t6 t8** |
| A15 | shift | **`var_t0 >> 1`** (else arm) | t8 | **t7** |
| A16..A21 | | else-arm rest | identical | identical |

The delta is exactly: *the first five allocations of each arm are rotated left by one.*

Our event structure (from a trace, `A`=alloc, `F`=free of that alloc):

```
A0 F0 A1 F1 A2 F2 A3 F3 A4 F4 A5 A6 F5 F6 A7 F7 A8 A9 F9 F8 A10 F10
A11 F11 A12 F12 A13 F13 A14 F14 A15 F15 A16 A17 F16 F17 A18 F18 A19 A20 F20 F19 A21 F21
```

An exhaustive search over relocations of contiguous `(Ai,Fi)` pairs, keeping **our existing
entry queue `[t6 t4 t8 t9 t7 t3 t5]`**, found exactly **one** structure reproducing all 22
target registers — and it is unique:

```
A4 F4 A0 F0 A1 F1 A2 F2 A3 F3 A5 A6 F5 F6 A7 F7 A8 A9 F9 F8 A10 F10
A15 F15 A11 F11 A12 F12 A13 F13 A14 F14 A16 A17 F16 F17 A18 F18 A19 A20 F20 F19 A21 F21
```

i.e. **move the `var_t0 >> 1` temp's alloc+free ahead of the damping statement's four temps,
in both arms.** Making the shift a standalone leading statement realizes precisely that.

## Notes on the abandoned entry-queue line of attack

Corroborated by construction: the entry queue **never needed to change**. The alleged target
queue `[t4 t8 t9 t7 t6 t3 t5]` was an artifact of assuming the region's first seven allocations
pop straight off the queue; they do not, because `A4` is allocated and freed between them.

For the record, before the pivot the following were established:
* Entry queue is `[t6 t4 t8 t9 t7 t3 t5]` and equals the queue at the last-7-allocs boundary.
* Six single-free-delay sites reach `[t4 t8 t9 t7 t6 t3 t5]` (source lines 250, 432, 533, 644, 738, 745) — all now moot.
* 13 pre-region free-runs of length 2 give position transpositions; all 2^13 subsets reach
  952 distinct queues, none the (spurious) target — consistent with it being unreachable/unneeded.
* Source levers that measurably moved the queue: `712 var_t0*20*updateRate` (diff 228),
  `710 var_t0*(16*updateRate)` (insns 2626). Both cost instructions; irrelevant now.

## Tools written (scratchpad, not committed)
`extract.py` / `sched.py` (trace → abstract alloc/free schedule), `region.py` (event-structure
solver), `rcheck.py` (compile → region register sequence + diff + insns + FP histogram).
