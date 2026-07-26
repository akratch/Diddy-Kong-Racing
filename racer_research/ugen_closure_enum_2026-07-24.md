# ugen.c integer temp free-list (0x10019da4) — formal append/remove/skip enumeration & closure verdict

Companion to `ugen_allocator_map_2026-07-24.md`. Target file:
`/private/tmp/ido-static-recomp/build/5.3/ugen.c` (now 139,120 lines — grew ~100 lines since the
prior map, so **all line numbers here are re-derived from the current file** and differ slightly from
the earlier map). All excerpts below are from the current file. Instrumentation lines (`codex_*`,
`fprintf`, `codex_dump_queue`, the `codex_rot`/`codex_hold`/`codex_defer` hacks at 82383-82438) are
called out and excluded from the "real code" reasoning.

## 0. The four lists (confirmed by the `a1`/`a0` literal at every call site)

| addr | list | pop primitive | append primitive |
|---|---|---|---|
| **0x10019da4** | **GP integer FREE list (the FIFO temp pool {11,12,13,14,15,24,25})** | `f_remove_head` (head/FIFO), `f_remove_from_list`/`f_remove_direg` (middle) | `f_append_to_list` |
| 0x10019da8 | GP integer IN-USE list | — | `f_append_to_list` |
| 0x10019dac | FP FREE list | — | — |
| 0x10019db0 | FP IN-USE list | — | — |

Register class = MIPS o32 caller-saved temporaries: t3=11,t4=12,t5=13,t6=**14**,t7=15,t8=24,t9=25.
The pool and its initial FIFO order come from a static table at **0x100054d4**, count at 0x10019328,
loaded once by `f_init_regs` (loop at 79403-79416, `f_add_to_free_list` per entry). This ordering is
compilation-invariant. Register **14 is even** (relevant to the pair machinery, §5).

---

## 1. Complete APPEND-to-0x10019da4 call-site table

`f_append_to_list(mem,sp,a0=reg,a1=list)` — grep gives 21 total call sites; exactly **6 target the
free list 0x10019da4**. Plus the primitive `f_add_to_free_list` (which itself appends at 84141).

| # | line | enclosing fn | reg appended | trigger (ucode/node config) | gated? |
|---|---|---|---|---|---|
| A1 | 83500 | `f_free_reg` (83322) | the freed reg | **normal free**: reg was on in-use list, moved in-use→free | **YES** — only if `MEM_U16(entry+4)==0` after `f_dec_usage` (gate at 83363-83367) |
| A2 | 83669 | `f_free_reg` | the freed reg's **partner** | primary reg usage hit 0 **and** `MEM_U8(entry+8)==6` (kind=pair-primary) → partner moved in-use→free | YES (same gate + kind==6, 83517-83519) |
| A3 | 82498 | `f_get_one_free_reg` (82357) | partner of a **spilled pair** | free list **empty** on a single-reg request, victim head is a pair (kind 6/7) → `f_spill_two_regs` evicts it, partner returned to free | conditional: FIFO empty **and** head kind∈{6,7} |
| A4 | 80451 | `f_spill` (80386) | partner (s0+9) of a **spilled pair** | spilling a reg whose `entry+8==6` — partner removed from in-use, appended to free | conditional: victim is pair-primary |
| A5 | 83956 | `f_force_free_reg` (83905) | the reg | reg was on in-use list → in-use→free | **UNGATED** (ignores usage count). Callers: `f_flt_reg` 45170, 45335 (evicting a GP scratch used by float codegen) |
| A6 | 84141 | `f_add_to_free_list` (83982) | the reg | generic "put reg in free list". Callers: `f_init_regs` 79407/79433 (startup pool fill); `f_eval` EXIT 57696 (return the mode-reserved frame reg — see §3) | UNGATED |

**Key fact:** the *only* append that returns an ordinary just-finished single-word integer temp to the
free list is **A1 (83500), and it is gated on the reg-table usage count (`entry+4`) reaching exactly
zero** (83363: `t8=MEM_U16(v1+4); if(t8!=0) goto L43eb9c` = return, no append). This gate is the sole
"defer" mechanism (see §Skip).

---

## 2. Complete REMOVE-from-0x10019da4 call-site table

| # | line | enclosing fn | kind | trigger |
|---|---|---|---|---|
| R1 | 82568 | `f_get_one_free_reg` | **HEAD pop (FIFO)** | normal allocation, free list non-empty (`f_list_is_empty`→0 at 82439/82444). **This is THE FIFO pop.** |
| R2 | 80503 | `f_spill` | HEAD pop | spill picks victim from the *list passed as a2* (not necessarily da4); part of spill machinery |
| R3 | 81017 | `f_get_one_reg` (80953) | **MIDDLE** (`f_remove_from_list(reg,0x10019da4)`) | a GET of a **specific** reg that is currently sitting in the free list (entry+7 managed, L43d210) → pluck it out, move to in-use |
| R4 | 81360 | `f_get_reg1` (81323) | MIDDLE | GET specific reg (primary) currently in free list |
| R5 | 81490 | `f_get_reg1` | MIDDLE | GET specific reg (partner, v0=a0+1) currently in free list |
| R6 | 84358 | `f_remove_from_free_list` (84322) | MIDDLE | dedicated "definitely remove this reg from free list". Callers: `f_save_vreg` 53868/53908 (param-reg save), `f_gen_regs` 54399 (param-reg codegen), `f_eval` **entry** 56708 (mode-reserved frame reg, §3) |
| R7 | 80015-80090 | `f_remove_direg` (79996), called from `f_get_two_free_regs` 82262 | **MIDDLE, even-aligned** | **pair allocation**: walk free-list chain skipping ODD regs (80023-80043 `t6=v0&1; if odd follow next-link`) to the first EVEN reg, splice it out. §5. |

`f_remove_head` (80123) always pops the head and rewrites the head/tail bytes; `f_remove_from_list`
(80276) unlinks an arbitrary reg by walking the `next` chain (offset+6).

---

## 3. FIFO-vs-GET routing proof (hunt item 1)

**The result-register allocation class is chosen per-eval-case, NOT by the result node's own use-count.**
Representative binary-op case (both children materialized), lines 60056-60162:

```
60056  if (fp != 0x48) goto L42fff4;              // parent forced a target reg (a1 hint to f_eval)
       // -- fp == 0x48: try to REUSE a dying operand's register (in-place, GET class) --
60062  a0=s3(right-operand reg); v0=f_usage_count(a0);   // 85173: reads MEM_U16(entry+4)
60069  if (v0 != 0) goto L42ff5c;                  // operand still has consumers -> can't reuse
60076  v0=f_is_available(s3);                      // 84859: reads MEM_U8(entry+7) managed flag
60081  if (v0 == 0) goto L42ff5c;                  // not managed -> can't reuse
60086  a2=MEM_U16(s6+20); a1=s6; f_get_reg(a0=s3,...)   // REUSE right-operand reg  [GET]
       ...  L42ff5c: same test on LEFT-operand reg (sp+318) -> f_get_reg(a0=left) [GET] (60137)
60145  L42ffd8: a1=MEM_U16(s6+20); a0=s6;
60149  v0 = f_get_free_reg(mem,sp,a0,a1);          // FIFO pop  [FIFO class]
60157  L42fff4: a2=MEM_U16(s6+20); a0=fp; a1=s6;
60162  f_get_reg(a0=fp,...)                        // parent-demanded specific reg [GET]
```

So the driver of FIFO vs GET for the RESULT is:
1. **parent forced-target hint** `fp` (the `a1` argument to `f_eval`) ≠ 0x48 → GET(fp); else
2. **operand-register reuse**: an operand reg whose `usage_count==0` (dead here) AND `is_available!=0`
   → GET(that operand reg), in-place, no new alloc, no move; else
3. → **FIFO** `f_get_free_reg`.

`f_get_free_reg` (82608) then picks single vs **pair** only on `MEM_U8(node+33) & 0x5010000`
(82641-82655) — the type/pair bitmask — again **not** use-count. The result node's own use-count
`MEM_U16(node+20)` is read only as the `a2` **seed** passed into `f_fill_reg` → written to `entry+4`;
it never selects the allocation class.

The one place use-count gates behavior is the **memoization re-visit** path at the top of `f_eval`
(56185-56197): for an *already-materialized* node, `t5=MEM_U16(node+20); if (t5 < 2) keep hint else
fp=0x48` — i.e. a shared node (use-count≥2) being re-touched clears the forced-target hint so it stays
in its existing register. This is a re-visit with **no emit** and no dispatch (returns via L434ee8).

**VERDICT on "use-count>1 ⇒ GET class":** REFUTED as a hard law. Case 60145-60149 proves a result
with any use-count lands in the **FIFO pool** whenever (a) the parent passes no forced target and
(b) neither operand register is a dead-reusable reg. A FIFO-class temp's `entry+4` is routinely seeded
>1. What the main session measured (bumping use-count → reg moved to a GET/specific reg) is a
**cascade effect, not a direct routing rule**: raising the mask node's use-count keeps its register
live across a neighboring op, so that neighbor's operand-reuse test (`f_usage_count==0`, 60069) now
fails where it previously succeeded, rerouting the *neighbor* and shifting registers. The routing law
itself does not key on the result's use-count.

---

## 4. Skip / defer analysis (the deferral mechanism)

- **`f_dec_usage` (83034)** never touches any list — pure counter op on `entry+4` (+ partner's if
  kind==6). Confirmed.
- **`f_free_reg` gate (83363-83367)** is the *entire* deferral mechanism:
  ```
  f_dec_usage(reg);                        // entry+4 -= 1
  t8 = MEM_U16(entry+4);
  if (t8 != 0) return;                      // <-- SKIP the append; reg stays in-use list
  // else: remove from in-use (83378), append to free (83500)
  ```
  A reg whose `entry+4` was seeded to N survives N−1 `f_free_reg` calls as no-ops; the append fires on
  the Nth call — i.e. after the **last** of the node's `node+20` consumers runs. Because each consumer
  is a temporally-later `f_eval`, the append can land many pops later than the first use. **This, and
  only this, moves a single-word integer temp's free-list return later without emitting any
  instruction.**
- No secondary queue, kill-bitmap, or end-of-block flush touches da4 (confirmed in prior map §6; the
  pmov bitmap at 0x10019d30 defers *move emission*, not frees).

---

## Per-hunt-item verdicts

### Item 1 — eval cases that free_reg a reg whose usage was seeded >1, still FIFO-class
**Routing refuted (§3): a FIFO temp CAN legally carry use-count>1.** The deferral lever exists and is
zero-emit **iff** the extra consumer is a **CSE re-visit** (a shared DAG node evaluated once, its
second+ parents taking the memoized no-emit path 56185-56197, each still issuing a `free_reg` that
drains `entry+4`). That is the exact machinery that makes the append land later.
**C-reachable contained perturbation: PLAUSIBLE-YES, with the construct in the final section.** Risk:
cascade rerouting of neighbor ops (the measured "moves to GET" effect).

### Item 2 — appends of a reg that is NOT the just-popped temp
Enumerated: A2/A3/A4 (pair partner via kind 6/7), A5 (`f_force_free_reg`, float-scratch eviction),
A6 (`f_add_to_free_list`: init + mode-reserved frame reg). Every one of these requires either a
**paired (s64/f64/ll/dw) value** — which emits different instructions (ld/sd/two-word ops) — or
**float codegen** (A5) — or is **init / global-mode-gated and constant** (A6). None can insert an
ordinary single-word int temp into the middle of the relative order while emitting zero extra
instructions. **VERDICT: NO** (no zero-emit contained path via these).

### Item 3 — middle-removals (GET of a reg currently in the FIFO list)
R3 (`f_get_one_reg` 81017), R4/R5 (`f_get_reg1`), R6 (`f_remove_from_free_list`), R7 (`f_remove_direg`
pair). These **remove**, they do not **defer an append** — so they cannot by themselves delay reg 14's
return. A specific-register GET of a t3–t9 reg is triggered only when the ucode/ABI demands that exact
register (function-result/arg regs, div/mult HI/LO landing regs, the mode-reserved frame reg). The one
hardcoded temp demand, `a0=0xd` (reg 13) at **56708**, is at `f_eval` **entry**, gated by the global
mode flag **0x10019390** (reserves reg 13 as frame/global reg, returned at exit via 57696) — constant
across the whole compilation, not a per-expression lever. **VERDICT: NO** for delaying reg 14's append;
(these are removals; demanding reg 14 specifically would also change the emitted register).

### Item 4 — dispatch cases that consume operands and emit nothing
Two confirmed (prior map §4, re-verified): **case 97** unary-fusion (63622: rebinds child's reg to
parent via `f_fill_reg`, no emit, no free/get) and the **memoization re-visit** (56185, any DAG node
with ≥2 parents). The re-visit path is precisely the enabler for Item 1: the *second* parent of a
CSE'd node emits nothing yet runs a `free_reg` whose position in the pop sequence determines where the
deferred append lands. Its ordering (when that second parent is evaluated) is what shifts reg 14 past
subsequent pops. **VERDICT: this is the zero-emit machinery Item 1 depends on — reachable iff cfe/uopt
produces the shared node.**

### Item 5 — the pair mechanism (kind 6/7, offset+9)
`f_get_two_free_regs` (82186) → `f_can_get_two_regs` (81882) / `f_remove_direg` (79996) **do** operate
on **this** list (0x10019da4), unlike the menu campaign's separate FP list. The align-skip is real:
`f_remove_direg` walks the free chain skipping **odd** regs (80023-80043) to the first **even** base,
then splices that even reg out of the middle (80058-80068 relink predecessor). **Register 14 is even**,
so a pair grab whose search reaches 14 would pull 14 out of the middle, reordering {11,13,15,24,25}
around it. Pair release (A2 83669, A4 80451) re-appends the partner. **BUT** every pair transaction
requires a kind 6/7 register = an s64/f64/ll/dw-typed source, whose ops **emit different
instructions** than a single-word integer AND-mask. You cannot make the R_TRIG mask temp transit as a
pair without changing emitted bytes. **VERDICT: NO for a zero-emit contained perturbation.** Secondary
note: if the 19-diff region already contains an *adjacent* 64-bit-typed value, its existing pair grab
is a genuine reorder lever on {11..25} — worth checking whether one sits near reg 14's live range, but
that is an observation about existing code, not a new C construct.

---

## Overall verdict

The free-list order is a pure function of the **sequence of appends into 0x10019da4**, and for an
ordinary single-word integer temp the append fires **exactly when `f_free_reg` drains `entry+4` to 0**
(gate 83363-83367). To make reg 14's append land **4 pops later** with **zero added instructions**,
reg 14 must remain in the in-use list across those 4 pops — i.e. its `entry+4` must be seeded **>1**,
and the extra decrement(s) must come from a consumer that **emits nothing**. The only such consumer is
a **CSE re-visit** (memoized no-emit path, §4/Item 4). Every other path either changes emitted bytes
(pairs A2–A4/R7, float-scratch A5) or is constant/mode-gated (A6, R6@56708) or merely removes rather
than defers (R3–R7).

**The space is NOT closed empty. There is exactly one candidate zero-emit contained construct.**

### The exact C construct to try (then STOP — main session tests it)

Make the R_TRIG mask value (the `andi` result currently bound to reg 14, use-count 1, whose
`andi`/`beqz`/`move` consumers all sit in the one `||` statement) into a **common subexpression that
cfe/uopt shares with a second, later reference which folds to a no-emit re-visit** — so the ucode
tree-builder seeds `node+20 = 2` and the second parent takes the memoization path (56185-56197),
issuing the deferred `free_reg` that appends reg 14 four pops later. Concretely, in the C source for
`func_80049794`, arrange the same masked sub-expression (the exact `(x & MASK)` / relational whose
result feeds the `||`) to also feed a **second use that dies after the next 4 temp allocations** and
that the optimizer will CSE onto the *same* tree node rather than recompute — e.g. reuse the identical
sub-expression in the immediately-following relational/branch of the same boolean web (the "v0-web that
dies later" the prompt already identified), written so cfe emits it once. Success condition: `node+20`
becomes 2, the mask stays reg 14 (FIFO — §3 permits it), no new instruction is emitted, and reg 14's
append moves past the 4 pops.

**Predicted failure mode / what to watch:** if cfe instead recomputes the second use (separate node,
emitted instruction) the byte count changes; if the extended live range of reg 14 flips a *neighbor*
op's operand-reuse test (`f_usage_count==0` at 60069) the neighbor reroutes to a different register
(the previously-measured "goes to GET class" cascade). The construct is only valid if the second
reference is a **pure CSE onto the same node with no emitted use** and reg 14's extended lifetime does
not overlap a neighbor's reuse decision. That is the single hypothesis left standing; all other
append/remove/skip paths are closed to a zero-emit contained perturbation.
