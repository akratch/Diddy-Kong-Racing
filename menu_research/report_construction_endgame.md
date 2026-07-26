# func_8008FF1C construction endgame

Status: paused at a safe stopping point, 2026-07-24.

This report records the construction session started from
`MENU_HANDOFF_FOR_CONSTRUCTION.md`. It is the primary record for work performed
after that handoff. The short operational handoff is
`SESSION_HANDOFF_2026-07-24.md`; the long synthesis is `POSTMORTEM.md`.

## 1. Result

No acceptable stock-toolchain source match was found.

The two established 371-word minima remain:

| Basin | Strict result | Residual |
|:--|--:|:--|
| `variants/v_base.txt` | 2 | `lh/beq v1` instead of `t2` |
| `variants/v_scratch.txt` | 2 | two later `addu` register fields |

The raw condition remains 371 words but scores 38 because the pointer store is
emitted before the load:

```c
cur->hubName = levelName;
if (gTrackSelectIDs[trackY][trackX] != -1) {
```

Both diagnostic compiler controls still establish sufficiency, not an
acceptable solution:

- granting the one load/store no-alias relation makes the raw condition match
  all 371 words; and
- suppressing the one `ugen` destination collapse makes the named-holder form
  match all 371 words.

No compiler, tracked source, or project build file was changed in this
construction session. In particular, `src/menu.c` and `src/racer.c` were not
touched.

## 2. Critical reassessment

The search has stopped producing new compiler states. New source spellings now
normalize into one of four already characterized states:

1. pointer induction: correct 371-word shape, but conservative alias ordering;
2. direct indexing: desired no-alias ordering, but additional address
   computation or a different loop/allocator graph;
3. named holder: correct global shape, but the load collapses into the colored
   web; or
4. widened/pair value: the load is deferred, but pair allocation fixes the
   later scalar home to odd-register states and perturbs trophies allocation.

This is the safe stopping point. Further unprincipled expression, declaration,
or mask sweeps would exercise the same normalized states and constitute
wheel-spinning.

The result is strong mechanism-level closure, not a theorem over every possible
C program. Reopening the source search is justified only by a topology that can
name the new optimizer/ugen state it expects to enter.

## 3. SOFT-B: retained/direct alias state

### 3.1 What the trace proves

The raw pointer loop carries `cur` as a pointer-class (`P`) base. Its first
memory access records that class, and a `P/P` query pre-locks the relevant
`unaltab` entry to may-alias before `gTrackSelectIDs` is resident. The state is
irreversible at this site; the later direct-global load cannot re-query it.

An address assignment such as:

```c
cur = gTrackSelectRenderDetails;
```

does not seed alias state. `f_base_in_reg` is driven by memory accesses, not by
the `la` that constructs the address.

A direct global-array memory access does seed the desired `D/D` no-alias
relation. In a true nested loop it also re-derives the element address, which
adds the observed shift/subtract/shift/add sequence.

### 3.2 Static-predecessor constructions tested

The skeptical handoff correctly identified a hole in the earlier universal
claim: a direct seed might conceivably reuse an instruction already required
by the target. Four targeted constructions tested that hole.

| Variant | Mechanism tested | LEN | Strict diffs |
|:--|:--|--:|--:|
| `v_construct_redundant_direct_seed.txt` | redundant outer direct address plus continuous `cur` | 372 | 167 |
| `v_construct_pointer_roundtrip_seed.txt` | direct store through `g[cur-g]` | 378 | 300 |
| `v_construct_byte_roundtrip_seed.txt` | byte-pointer direct round trip | 374 | 296 |
| `v_construct_coalesced_direct_seed.txt` | direct visible store followed by an equal `cur=&g[k]` | 378 | 336 |

The coalesced form was the strongest missing predecessor: it supplied a real
direct memory event and made the pointer hold the same value, without keeping
two semantically different addresses live. IDO did not transfer or coalesce
the direct base state. It preserved the address machinery.

These results close the identified zero-instruction seed candidates:

- address-only seeds do not enter the alias state machine;
- direct memory seeds retain direct address computation;
- pointer-difference round trips are not algebraically cancelled; and
- an equal direct-index/pointer pair is not coalesced into the target pointer
  induction.

They do not prove that no more exotic C topology exists. They do establish
that the previously named predecessor classes cannot produce the target
prefix at zero cost.

## 4. Direct flat-loop construction: useful falsification

A flat, direct-index loop disproved the overbroad empirical statement that
direct access must always add seven instructions. With one continuously
incremented direct induction, IDO can emit the desired local sequence:

```asm
lh    t2,0(s1)
li    at,-1
beq   t2,at,...
 sw   v0,0(s0)
```

and the target inner pointer latch. The important distinction is structural:
flattening the nested loop changes the outer induction and register-allocation
graph.

The durable representative is
`variants/v_construct_flat_rowsplit.txt`. Its top-scope one-element `row`
object forces a real outer counter and currently verifies as:

```text
LEN 372/371
FULLWORD_DIFFS 311
frame 136 instead of 128
```

The array itself is diagnostic, not a proposed decompilation.

The exact producer conflict was then traced in optimizer IR:

- `trackY + 1` enters as `Uadd(trackY, 1)` and induction elimination promotes
  it into an `s8` recurrence, changing the target allocation/latch graph;
- `-~trackY` avoids that strength reduction but necessarily emits `nor` and
  `negu`, yielding a shorter but instruction-incompatible function; and
- other representation-preserving spellings normalize back to `Uadd` or add
  real operations.

Thus direct access has a zero-extra-address construction only when the source
abandons the target's nested-loop induction graph. Restoring that graph
restores either the direct reinitialization cost or the promoted `trackY+1`
recurrence.

This is the strongest structural result of the session: the conflict is
between two optimizer graphs, not between two C spellings.

## 5. SOFT-A: 32-bit index plus independent pair activity

The mask basin requires a 32-bit scalar result to reach even register `$12`,
while the downstream trophies block requires the queue effects created by the
64-bit pair path. The construction session separated those jobs and carried
real values through every conversion; dead pair burners were excluded.

The earlier postmortem table records 22,255 overlapping cases. The later
arithmetic/topology scripts encode another 26,416 overlapping cases:

| Script | Cases | Best/result |
|:--|--:|:--|
| `construct_store_barrier_sweep.py` | 75 | FW 2, first 102 |
| `construct_postbranch_index_sequence_sweep.py` | 3,975 | FW 3, first 106, LEN 371 |
| `construct_preconverted_index_sweep.py` | 3,180 | FW 35, first 106, LEN 371 |
| `construct_fw3_mul_sweep.py` | 264 | FW 3, first 106, LEN 371 |
| `construct_call_split_sweep.py` | 3,888 | FW 3 at `(106,107,109)`, LEN 371 |
| `construct_live_index_carrier_sweep.py` | 1,044 | FW 3 at `(106,107,109)`, LEN 371 |
| `construct_entry_pointer_sweep.py` | 249 | FW 6 at `(106..111)`, LEN 371 |
| `construct_mul_stage_split_sweep.py` | 6,480 | archived stage-split family; no match |
| `construct_mul_tail_fusion_sweep.py` | 1,326 | archived fused-tail family; no match |
| `construct_mul_pre_post_sweep.py` | 1,083 | archived pre/post phase family; no match |
| `construct_subtract_handoff_sweep.py` | 4,852 | archived final handoff family; no match |

The first seven rows were replayed while preparing this report. The redundant
replay of `construct_mul_stage_split_sweep.py` was deliberately interrupted
after the documentation stop condition; its case count is derived from the
checked-in case set, and the prior negative result is encoded by the downstream
scripts' starting states. This distinction is preserved for auditability.

The most informative new basin is FW 3. It has the exact four-word
load/store/branch window and exact length, but the real `trackY*6` producer
differs at indices 106, 107, and 109. Splitting the value across the call,
changing the live carrier, pre-rotating the queue, and independently composing
the shift/subtract/shift stages all converge on that same producer trace.

The later fused-tail work can move the remaining difference boundary but does
not create the required same-register handoff. At the critical point, either:

- the value remains live in `t3`, preventing `t3` from being freshly selected;
- the value is copied to another scalar, and the copy changes a real target
  word; or
- a 64-bit conversion supplies the queue event, reintroducing pair parity.

This does not enumerate all C. It closes the handoff's proposed
"32-bit index plus independent, semantically live pair activity" mechanism
across the explicit producer, call-boundary, carrier, entry-pointer, and
arithmetic-stage predecessor classes.

## 6. Step 8: non-alias load producer

`report_ucode_enum.md` remains the finite opcode-level result for the fixed
named-holder frame. Of 152 `ugen` expression opcodes, the sole root that can
defer the load while adding no real instruction and no pair is an identity
integer `Ucvt`; `cfe` removes it before `ugen`.

This session tested two claimed outer-frame escape routes:

| Variant | Result |
|:--|:--|
| `v_construct_const_holder.txt` | LEN 371, FW 133 |
| `v_construct_parameter_holder.txt` | LEN 371, FW 133 |

Block scope, `const`, and reusing the parameter as the holder do not alter the
collapse. The load still enters the holder's colored web.

The direct flat-loop experiment reaches the target local window through the
alias route, not through a fourth non-alias producer. Its whole-function
failure is described in section 4.

No zero-cost, C-reachable producer outside the enumerated `Ucvt` arm was found.
Alternate arbitrary CFGs are not finitely enumerated, so the precise claim is:
the target-compatible named-holder producer frame is closed, and every
mechanistically distinct outer topology tested either remains in that frame or
changes target-visible CFG/induction code.

## 7. Directives, flags, and declaration context

These were low-cost boundary checks, not proposed source solutions.

| Test | Outcome |
|:--|:--|
| `#pragma noalias(cur, gTrackSelectIDs)` | unsupported pragma; raw FW 38 |
| `#pragma distinct(...)` | unsupported by stock `cfe`; raw FW 38 |
| `__restrict` | rejected by the stock front end |
| driver `-noaliasok` | forwarded only to `as1`; warning/ignored; `.text` unchanged |
| `-noPalias` | Pascal-specific internal option; no C route |
| `gTrackSelectIDs` made `static` | optimized instruction sequence unchanged |
| render array made `static` | optimized instruction sequence unchanged |
| both globals made `static` | optimized instruction sequence unchanged |

The `static` permutations changed only relocation addends caused by local
section offsets. They did not affect alias class, instruction selection,
ordering, or register allocation.

The stock assembler contains a real `.noalias` directive because it consumes
optimizer output. Inline assembly that injects such a directive changes
allocation/length and is neither an exact match nor coherent source.

## 8. What is closed, and what is not

Closed at the deciding mechanism for target-compatible constructions:

1. fresh pointer/global no-alias queries;
2. retained direct state from address-only, direct round-trip, and coalesced
   direct/pointer predecessors;
3. zero-cost RHS producer roots in the named-holder frame;
4. the 64-bit pair-add's ability to produce even `$12`;
5. independent live pair activity around the real 32-bit index across the
   enumerated producer and handoff classes;
6. supported stock alias directives/qualifiers; and
7. global linkage as a hidden optimizer input.

Not proved:

- a theorem over every C-reachable CFG or object model;
- the exact historical source;
- the exact historical compiler/build cause;
- every unpublished compiler binary or private wrapper; or
- whether manual/object-level intervention occurred.

The evidence now favors a persistent, undistributed DKR build-environment
difference over a recoverable stock-source spelling. That is an inference from
the mechanism closures and cross-revision/corpus evidence, not a match claim.

## 9. Reopen criteria

Do not resume broad syntax, mask, declaration-order, or loop-form sweeps.
Reopen construction only if a proposal answers all three questions before it
is compiled:

1. Which new `uopt`/`ugen` state or producer arm does it enter?
2. Why does it preserve the target's 371-word nested-loop and allocation graph?
3. Why is its enabling operation already represented by a required retail
   instruction?

High-value external reopen triggers are:

- Rare/Nintendo source, object, build-script, or compiler-pass evidence;
- a new, independently hashed IDO pass binary or runnable blocked pass-matrix
  cell;
- evidence of a previously unknown driver option reaching `uopt` or `ugen`;
  or
- a newly identified normalized producer arm, not a new spelling of an
  enumerated arm.

Until then, the honest stock-toolchain endpoint remains 369/371.
