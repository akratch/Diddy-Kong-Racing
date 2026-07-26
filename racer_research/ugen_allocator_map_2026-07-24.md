# ugen.c integer temp-register allocator — technical map

Target: `/private/tmp/ido-static-recomp/build/5.3/ugen.c` (~139,023 lines), recompiled IDO 5.3 `ugen`
integer-expression register allocator. All line numbers below are from that file as it stood during
this investigation (it already carries prior `codex_*` instrumentation — trace prints, queue dumps,
a couple of one-shot `codex_rot`-gated register-rotation hacks around lines 82319–82341 — which is
extremely useful corroborating evidence and is cited where relevant).

## Data structures

### Register table: `0x10019830`, 12-byte entries, indexed `entry = 0x10019830 + reg*12`

Confirmed field layout (reg index runs 0..31 for GP int regs; `0x48`/72 is the universal "none/empty"
sentinel used both for "no register" in a node and for empty list head/tail):

| offset | size | field | evidence |
|---|---|---|---|
| +0 | 4B (u32) | **owner node pointer** — the ucode tree node currently bound to this register | `f_fill_reg` (79686-79715): `MEM_U32(v0+0)=a1` where `a1` is the node ptr passed through from `f_get_one_free_reg`/`f_get_free_reg`; `f_copy_reg` (79717-79773) copies this word between entries |
| +4 | 2B (u16) | **usage/reference count** | `f_dec_usage` (82937 ff.) reads/writes `MEM_U16(v1+4)`; `f_fill_reg` initializes it from `a2` |
| +6 | 1B | **`next` link byte** — singly-linked list chain (used for both the free list and the in-use list) | `codex_dump_queue` (18-29) walks it: `reg = MEM_U8(0x10019830 + reg*12 + 6)`; `f_remove_head`/`f_append_to_list`/`f_remove_from_list` (80077-80211+) all read/write offset+6 |
| +7 | 1B | **"managed/listed" flag** — nonzero iff this register participates in the free/in-use queues at all | `f_append_to_list` line 80158-80167 `abort()`s if 0; `f_free_reg` line 83272 branches around list removal/insertion when 0 (fixed/scratch regs that are never queued still get their usage count and node-ptr fields updated via `f_fill_reg`, but are not chained into the lists) |
| +8 | 1B | **kind/class byte** | `0` = plain single register; `6` = **primary half of a register pair**, `7` = **secondary/partner half** — set explicitly by `f_get_two_free_regs` (82121-82220): `a3=0x7` passed to `f_get_one_reg` for the partner reg, and callers check `MEM_U8(entry+8)==6` (dec_usage L43e688-694, free_reg L43e9ac-9e8) to decide whether to also touch the partner |
| +9 | 1B | **paired-register index** — only meaningful when kind==6/7 | `f_get_two_free_regs` line 82209: `MEM_U8(t0+9) = v1+1` (partner is the numerically adjacent register); `f_dec_usage`/`f_free_reg` read it to locate/decrement/free the partner |
| +10,+11 | — | not observed accessed anywhere in the allocator, spill, eval, or list code searched | padding/reserved, or fields used only outside the reg-alloc path (not confirmed) |

Two list *heads* (2-byte head/tail pair, byte0=head reg, byte1=tail reg, `0x48` = empty):
- `0x10019da4` — **free list**
- `0x10019da8` — **in-use list**

Both confirmed directly by `codex_dump_queue` and by every `f_append_to_list`/`f_remove_from_list`/`f_remove_head` call site (all pass one of these two addresses as `a1`).

### Ucode tree node fields (referenced throughout `f_eval` and friends)

| offset | field | evidence |
|---|---|---|
| +0 | left-child pointer | `f_eval` debug print line 56059-56061: `MEM_U32(a0+0)` labeled `left=`; also `f_get_one_reg` debug print reads `a1+0..3` as first word of node |
| +4 | right-child pointer | same debug print, `right=` |
| +20 | 2B **use count** — number of times this node's value will be consumed | see Q3 below; read at ~15+ sites inside `f_eval` (56141, 60040/87/101/113, 60846, 61065/78, 61310/334, 62080/107/131, 62841, 63646/55/88) |
| +24 | 1B **temp/spilled flag** | `f_eval` 56089-56104: if nonzero, calls `f_restore_from_temp(mem,sp,a0)` before using the node's value |
| +25 | 1B **raw register byte** — register index encoded in the high 7 bits (`(byte<<24)>>25`), sentinel `0x48` = "no register assigned yet" | `f_eval` top-of-function debug print and dispatch logic (56082-56087) |
| +32 | 1B **op byte** — selects the ~152-way `switch (jtbl_index)` dispatch (cases 0..0x97) | `f_eval` 56177-56186: `a0 = MEM_U8(s6+32); jtbl_index=a0; switch(jtbl_index){ case 0: goto L43270c; ... }` |
| +33 | 1B bitmask consulted for "does this op need a register **pair**" | `f_get_free_reg` 82544-82553 and `f_get_two_free_regs` 82160-82168: `t7=MEM_U8(a0+33); ...& 0x5010000` bit test decides `f_get_two_free_regs` vs `f_get_one_free_reg` |
| +34 | 2B flags, bit `0x2` checked at eval exit (67141-67150) | minor, not central to this task |

---

## Q1 — `f_dec_usage`: what it decrements, when `free_reg` actually appends, register-table fields 0-11

**`f_dec_usage(mem, sp, a0)`** — line **82937**, label `L43e534` (`//dec_usage:`).

- `a0` is a register index. Entry = `0x10019830 + a0*12`.
- `v0 = MEM_U16(entry+4)` — the **usage-count** field.
  - If `v0 == 0`: this is an assertion failure (decrementing an already-zero usage count). It builds an
    error string and calls `f_report_error(...)` (lines 82969-83070, then again a second, near-identical
    block at 83107-83208 for the *paired*-register case), but **does not abort()** — it just reports and
    falls through to `L43e688`/`L43e7ec` without actually decrementing anything further.
  - If `v0 != 0` (label `L43e680`, line 83078): `MEM_U16(entry+4) = v0 - 1`. This is the real decrement.
- After decrementing (or reporting), it checks a debug/spill-mode flag byte at `0x10018ecc`
  (line 83082-83088); if that byte is 0 it additionally checks `MEM_U8(entry+8) == 6` (line 83090-83094):
  if the register is the **primary half of a pair**, it looks up the **partner** at `MEM_U8(entry+9)` and
  recursively applies the exact same decrement-or-report logic to the partner's usage count
  (lines 83096-83217). So decrementing a paired register's usage also decrements its partner's usage
  in the same call.
- `f_dec_usage` itself **never touches the free/in-use lists** — it is purely a counter operation on
  register-table field `+4` (and optionally the partner's `+4`).

**`f_free_reg(mem, sp, a0)`** — line **83225**, label `L43e7f8` (`//free_reg:`). This is the function containing the label the prompt named. It already has `codex_trace()`/`codex_dump_queue` instrumentation at its entry (lines 83241-83245).

Logic:
1. Calls `f_dec_usage(mem, sp, a0)` (line 83255).
2. Re-reads `entry+4` (`t8`) **after** the decrement (line 83266). **This is the condition that gates the append**: `if (t8 != 0) goto L43eb9c` (return immediately — line 83268-83270). **Only when the post-decrement usage count is exactly 0** does the function proceed to actually free the register.
3. If usage hit 0: checks `entry+7` (the "managed/listed" flag). If 0, skips list manipulation entirely (register was never in the queues — e.g. a fixed scratch register used bypassing the pool) and jumps to `L43e9ac`.
4. If `entry+7 != 0`: removes the register from the **in-use list** (`0x10019da8`) via `f_remove_from_list` (line 83281); if that removal unexpectedly fails (`v0==0`) it's an assertion/error-report path (lines 83291-83397); on success it **appends the register to the free list `0x10019da4`** via `f_append_to_list` (line 83403, label `L43e988`) — this is the actual free-list-append site.
5. Then (label `L43e9ac`, line 83411) it repeats essentially the same paired-register handling as `f_dec_usage`: if `entry+8==6`, calls `f_fill_reg` (a debug/poison refill, `a3=1`) on the register, then does the identical remove-from-in-use / append-to-free dance for the **partner** register at `entry+9` (lines 83420-83592), and finally calls `f_fill_reg` again unconditionally before returning.

**Answer to "under what condition does free_reg actually append": only when the register-table usage count (`entry+4`) reaches exactly zero after the decrement.** Any register whose usage count was initialized >1 (see Q3) survives one or more `free_reg` calls with no list effect at all — it stays in the in-use list, still "live," until enough `free_reg` calls have drained the counter to 0.

---

## Q2 — All call sites of `free_reg`, classified

`f_free_reg` (the function at line 83225 containing label `L43e7f8`) has **50 call sites**, all of the
literal form `f_free_reg(mem, sp, a0);`. Grep: `grep -n "f_free_reg(mem" ugen.c`. Mapped to enclosing
function by nearest preceding `static ... f_xxx(` declaration:

| caller function | call-site lines | count |
|---|---|---|
| `f_emit_branch_rill` | 29952 | 1 |
| `f_emit_trap_ri` | 31566, 31584, 31602, 31955, 31973, 31991 | 6 |
| `f_dw_emit_rri` | 36345 | 1 |
| `f_gen_entry_exit` | 37241, 37676, 37685 | 3 |
| `f_gen_entry` | 38201, 38210 | 2 |
| `f_reg` | 44627 | 1 |
| `f_binary_regs` | 44963, 45001 | 2 |
| `f_loadstore` | 47148, 47279, 47554, 47800 | 4 |
| `f_unaligned_loadstore_for_fp_word` | 49190 | 1 |
| `f_unaligned_loadstore_for_two_fp_w[ords]` | 49355 | 1 |
| `f_eval_mov` | 51171, 51846, 51889, 51898, 51928, 52016, 52025, 52057, 52146, 52155 | 10 |
| `f_eval_irel` | 53615, 53624, 53633 | 3 |
| `f_eval` | 58547, 61522, 62245, 62408, 62436, 62605, 62938, 64252, 64508, 65464, 66016, 67158 | 12 |
| `f_eval_flt_int_cvt` | 68811, 69028, 69074 | 3 |

Reading the ~15-line window around every site (dumped to a scratch file and inspected in full),
three recurring shapes emerge:

**(A) "expression temp finished right after this instruction" — by far the dominant pattern.**
`v0 = f_get_free_reg(...)` (or `f_get_reg`) immediately followed, after exactly one `f_emit_*`/`f_demit_*`
call that consumes the fresh register as a scratch/immediate-materialization register, by
`a0 = v0 & 0xff; f_free_reg(mem, sp, a0);`. Examples: 31566, 36345, 58547, 61522, 62245/408/436/605/938,
64508, 65464. This is register-allocator scratch usage for building constants that don't fit an
immediate field (lui/ori-style sequences) — get a temp, use it in one emitted instruction, free it
immediately. Also present with **no intervening emit at all** (29952, 51846, 51889, 51928, 52016,
52057) — `f_get_free_reg` then immediate `f_free_reg` with nothing else in between; this looks like a
"probe the allocator / force a possible spill eviction, but don't actually keep the register" idiom
(seen heavily inside `f_eval_mov`, the coalesced-move handler).

**(B) Freeing a node's/child's *own* register after its value has been consumed by the parent op.**
Distinguishable by the freed register coming from a node field rather than a fresh `f_get_free_reg`
call: e.g. `f_reg`/`f_binary_regs` at 44627/44963/45001 free `a0 = MEM_U8(s0+25)` / `MEM_U8(s1+25)`
— the **node+25 raw-register byte** of a child node, right after its value has been folded into the
current instruction. `f_loadstore` (47554, 47800) and the unaligned-loadstore functions (49190, 49355)
free the register that was used to hold a loaded/stored value immediately after `f_move_to_dest` has
copied it to its final destination — i.e. "the source temp is dead, the value has been relocated."
`f_eval_flt_int_cvt` (68811, 69028, 69074) frees the int-side scratch register(s) of an fp↔int
conversion right after the converting instruction (and after a companion `f_free_fp_reg` for the fp
half at 69019) — a paired-value teardown, structurally identical to (B) but for float/int cross-class
conversions.

**(C) Fixed/reserved scratch register released after a code-generation sequence (function
prologue/epilogue), not tied to any expression node at all.** `f_gen_entry_exit` (37241, 37676, 37685)
and `f_gen_entry` (38201, 38210) free hard-coded register numbers (`a0 = 0x18`, i.e. register 24,
etc.) right after `f_demit_rrr`/`f_emit_rrll` calls that build the stack-frame prologue/epilogue code.
`f_eval` line 66016 does the same (`a0 = 0x18`) after `f_emit_ri_`. These are the closest thing to
**"block-boundary" frees** in the call-site set — they release a scratch register that was borrowed
for one specific code-generation burst (function entry/exit emission), not for an expression-tree
node — but they're still immediate (no queued/deferred flush).

**One conditional-coalescing-adjacent site:** `f_eval` line 67158 (inside the relational/branch-eval
tail, around label `L434b4c`): `if (s2 != t1) { f_free_reg(a0=s2); }` — i.e. the destination register
picked for the compare result is only freed if it differs from the register the caller actually wanted
(`t1`, loaded from `MEM_U8(sp+318)`); if they're the same the register is kept (it's being handed to
the caller as the live comparison-result register). This is the "free the loser of a reg==reg check"
idiom, structurally close to Q4's coalescing question but here it's disposing an *extra* register
picked during instruction selection, not eliding an instruction.

**None of the 50 sites free registers from a distinct "death list" or defer to a block/statement
boundary via a queued set of pending frees.** Every call is either (A) immediate scratch teardown,
(B) immediate post-consumption operand teardown, or (C) immediate teardown of a hardcoded
prologue/epilogue scratch register. All 50 are synchronous, single-register, called at the exact
point of code generation. The one genuine source of **temporal deferral** in this allocator is not a
second call site or a queue — it's the **usage-count mechanism** described in Q3: `free_reg` is called
just as eagerly at every one of these 50 sites, but for a register whose usage count was initialized
above 1, most of those calls are no-ops (per Q1's gating condition) until the count is drained to zero
by a later, textually-distant call.

---

## Q3 — How `eval` releases operand registers; the >1 usage-count / later-free mechanism

`f_eval` (line 56043, label `L42d47c`) starts with **memoization**, not evaluation:

```
56082  s0 = MEM_U8(a0+25) -> decoded reg  (0x48 sentinel = "no register yet")
56086  if reg == 0x48: goto L42d55c            // never evaluated: fall into first-time-eval path (see below)
56089  if node+24 (temp flag) != 0:
56096      f_restore_from_temp(mem, sp, a0)     // value was spilled; reload it
           ...
       goto L42d55c
```
`L42d55c` (56141): `t5 = MEM_U16(s6+20)` — **reads the node's use-count field** — and if `t5 >= 2`
forces `fp = 0x48` (a "don't force a specific target register" signal used later as the `a1` hint to
`f_get_reg`/`f_get_free_reg`). It then calls `f_move_to_end_gp_list`/`f_move_to_end_fp_list` (an
LRU-touch, "this register is still live/recently used, don't spill it first") and **returns without
touching the dispatch switch at all** whenever the node already has a register (`reg != 0x48`). In
other words: **if a node has already been evaluated once, subsequent `f_eval()` calls on the same
node pointer are cheap re-touches of an already-live register, not re-evaluation.**

The dispatch switch (`case 0..0x97`, 56177+) only runs on the **first** `eval()` of a node (reg was
`0x48`). When a case allocates a fresh result register, it does so via `f_get_free_reg` /
`f_get_reg`(`mem,sp,a0=node_or_targetreg,a1=node,a2=usageCount`), where **the usage-count argument is
read directly from `MEM_U16(node+20)`** — confirmed at e.g. lines 60040-60043 (`a2 =
MEM_U16(s6+20); ...; f_get_reg(mem,sp,a0,a1=s6,a2)`), 60087, 60101-60103, 60113-60116, 60846, 61065,
61078, 62080, 62107, 62131, 62841. That value flows into `f_get_one_free_reg` (82292) →
`f_fill_reg(a0=reg, a1=node, a2=usageCount, a3=kind)` (82486-82491/82419-Fig above) which writes
`usageCount` straight into register-table field `entry+4`.

**So yes — a node's result register usage count is routinely initialized to a value >1.** `node+20`
is written from the tree-building/optimizer passes (writes observed at lines 63657/63697/63699 inside
`f_eval` itself — a coalescing case copies one node's use-count onto another's — and at 101254/101256,
106522, 107180/107182, 107567 outside `f_eval`, presumably during tree construction/CSE where a node
gains an extra parent reference). It represents **how many future consumers will read this node's
value** — i.e. it's a reference count for a shared subexpression / DAG node with multiple parents.

**This is the mechanism that makes a temp's free-list append happen *later* than its last emitted
use in the textual/temporal sense of "first use":** `free_reg` gets called once per consumption (per
the Q2 call sites), decrementing `entry+4` each time, but the register is only unlinked from the
in-use list and pushed onto the free list on the call where the counter hits zero — i.e. after the
**last** of the `node+20` consumers has run, which for a shared node can be a `free_reg` call many
eval() calls (and possibly whole statements) after the node's *first* consumption. Operand register
release in `eval` is therefore **not** a direct always-frees `free_reg` call and **not** an
independent decrement-to-zero at a different site — it is a single `free_reg` call per consumption
site whose real-world effect (does it hit the free list or not) is entirely governed by how many total
consumers `node+20` recorded at allocation time.

---

## Q4 — Ops in `eval`'s dispatch that consume an operand register but emit no instruction

The clearest, concretely-identified example is **case 97** (`case 97: goto L43259c;`, dispatch table
entry at line 56269), body at lines 63622-63719. This handles a unary-op-to-single-instruction fusion:

- `v0 = f_uop_to_asm(mem, sp, a0=s6)` — asks whether this unary node's opcode can be folded directly
  into the *addressing/op-code* of the instruction that will load its child, rather than emitted as a
  separate unary instruction.
- If the child (`a2 = MEM_U32(s6+0)`) is itself a suitable node (`MEM_U8(a2+32)==0x3c`) **and** a global
  mode flag at `0x10019350` equals `2` **and** the child's use-count `MEM_U16(a2+20) == 1` (i.e. the
  child is used **only** by this unary node, so it's safe to fuse):
  - `MEM_U16(a2+20) = MEM_U16(s6+20)` (line 63657) — the child **inherits the parent's use-count**.
  - `f_eval(mem, sp, a0=MEM_U32(s6+0), a1=fp)` (line 63660) — evaluates the **grandchild**, skipping
    the child entirely.
  - `f_fill_reg(a0=<decoded reg>, a1=s6, a2=MEM_U16(s6+20), a3=<kind from reg table>)` (line 63690) —
    **rebinds the already-allocated register directly to the parent node `s6`**, i.e. the register is
    renamed from "belongs to child" to "belongs to parent" in the register table, with **no move
    instruction emitted and no `f_free_reg`/`f_get_free_reg` call at all** for this rebinding.
  - `MEM_U16(t7+20) = 1` where `t7 = MEM_U32(s6+0)` (the child) — resets the child's own use-count to 1
    (bookkeeping so a stray future `eval()` of the now-elided child doesn't misbehave).
  - Falls through to `L4326b8`/`f_reg(...)` and continues — **no `f_emit_*`/`f_demit_*` call happens
    on this path** for the unary operator itself; the only instruction emitted is whatever the
    grandchild's own eval produces (with its opcode/addressing possibly modified by `f_uop_to_asm`'s
    result, `s5`). This is exactly the "coalesced move: result reg == operand reg, no instruction"
    pattern the task asked about — it consumes the child node's registration but literally re-labels
    the same physical register rather than freeing+reallocating or emitting a copy.

A second, weaker example is the early-return path at the very top of `f_eval` itself (`L42d55c`,
line 56141, discussed in Q3): when a node has already been evaluated (`reg != 0x48`), every
subsequent `eval()` call on it "consumes" the operand (moves it to the end of the GP/FP LRU list,
touches it) but returns via `goto L434eec`/`L434ee8` **without going anywhere near the op dispatch
switch, so nothing is ever emitted for that call.** This applies to *every* opcode when its node is
being re-visited (any DAG node with >1 parent) — i.e. it's a general "already-materialized" no-emit
path rather than a specific numbered case, and it's the direct operational counterpart of the
`node+20` usage-count mechanism from Q3.

Given the size of the 152-case switch (`case 0`..`case 0x97`, spanning ~11,000 lines,
lines 56043-67505), a full opcode-by-opcode audit for *every* no-emit branch was out of scope for
this pass; case 97 (`L43259c`) and the top-of-function memoization path (`L42d55c`) are the two
confirmed, evidenced instances of "consumes an operand register, emits nothing."

---

## Q5 — The `line` global at `0x10018e00`

Confirmed as a plain "current source/ucode line" tracker used purely for diagnostics
(`f_report_error`, all the `codex_trace()` prints reference `MEM_U32(0x10018e00)` as `line=%u`).

It is written in exactly one place: **`f_build_tree`** (line 11136), the ucode-token-stream parser
that constructs the expression-tree nodes consumed by `f_eval`. Inside its big token-`switch`
(dispatching on `MEM_U8(sp+456)`), **case `0x51` (81)** (lines 11685-11694):

```
t9 = MEM_U32(sp + 460);      // token's argument word (the line number operand)
at = 0x10018e00;
MEM_U32(at + 0) = t9;        // line = <token argument>
goto L40f4e4;                // back to the token dispatch loop
```

This is a `.line`-style pseudo-op in the incoming ucode token stream: whenever the parser encounters
token `0x51`, it stores that token's operand word into the global at `0x10018e00` and continues
parsing. No other assignment to `0x10018e00` exists anywhere in the file. This confirms the prompt's
assumption exactly: `line` tracks "current source line" and is set once per `.line` directive
encountered while building the ucode tree, well before `f_eval` ever runs against that tree.

---

## Q6 — Deferred/delayed free mechanisms

**No separate "list of registers to free at end of statement/block" data structure exists** anywhere
that touches `0x10019da4`/`0x10019da8` or the register table. All 50 `free_reg` call sites are
synchronous (Q2), and `f_remove_head`/`f_append_to_list`/`f_remove_from_list` are the only
list-mutating primitives found; there is no third queue, no "pending kill" bitmap, and no
end-of-block flush routine that walks node trees freeing registers in bulk.

There *is* a structurally similar but functionally distinct deferred mechanism used for a different
purpose: **`f_clear_pmov_regs` / `f_save_pmov_reg` / `f_load_pmov_regs`** (lines 55468-55633),
operating on a 96-bit bitmap at `0x10019d30..0x10019d38`. `f_save_pmov_reg(reg)` sets a bit for a
register that has a **pending parallel move** (used when setting up call arguments, where several
register-to-register moves must be sequenced/serialized to avoid clobbering — a classic "parallel
copy" problem). `f_load_pmov_regs` later walks the bitmap and emits the actual `f_emit_rob` move
instructions for every set bit, then the bitmap is presumably cleared. **This defers instruction
*emission* (register-to-register copies), not register *freeing*** — it's unrelated to the
free-list/in-use-list mechanism and does not interact with `entry+4` usage counts or `free_reg`/
`dec_usage` at all.

**The actual mechanism that defers a temp's free-list append past its last emitted use is the
usage-count field itself (Q1/Q3 combined), not a queue:**
- Every `free_reg` call decrements `entry+4` unconditionally (via `f_dec_usage`) and only performs the
  list append when that decrement lands on zero.
- A node's result register can be initialized with `entry+4 = MEM_U16(node+20)`, i.e. a count equal to
  the number of times that node's value will be consumed by later parts of the expression tree/DAG.
- For a node with `node+20 > 1` (a shared subexpression, e.g. a common-subexpression-eliminated value
  referenced by multiple parent nodes), the *first* `free_reg` call against its register — issued right
  after its first consumer emits its instruction — is a pure no-op on the free list: the register stays
  bound and in the in-use list. Only the call tied to the **last** of the `node+20` recorded consumers
  actually appends it to the free list at `0x10019da4`.
- Because each consumer is evaluated (and its `free_reg` issued) as a separate, temporally-later
  `f_eval()` invocation — potentially in a different statement or even a different basic block of the
  ucode tree being walked — **this is precisely a mechanism by which a register's free-list return is
  delayed well past the point where it was last "used" in the sense of its first/only textually-visible
  emission**, without any explicit queue: the delay is encoded entirely in a per-register saturating
  counter seeded from a per-node static reference count computed ahead of time by the tree builder /
  optimizer (writers of `node+20` at lines 63657/63697/63699, 101254/101256, 106522, 107180/107182,
  107567).

## Summary — call graph

```
f_build_tree (11136)                    parses ucode tokens -> tree nodes; sets `line` (0x10018e00)
                                         at token 0x51 (11685-11694)

f_eval (56043, L42d47c)                 top: memoize / re-touch already-live node (L42d55c, 56141) — NO EMIT
  |  reads node+20 (use count), node+24 (temp flag), node+25 (reg byte), node+32 (op switch)
  |  dispatch switch case 0..0x97 (56186+)
  |    case 97 (L43259c, 63622)         unary-op fusion: rebinds child's reg to parent via f_fill_reg,
  |                                     recurses into grandchild — NO EMIT for this node
  |  ... (150 other cases, mostly emit + f_get_free_reg/f_get_reg + f_free_reg)
  |  f_get_free_reg(node, a1=MEM_U16(node+20))  (82511)
  |     -> f_get_one_free_reg (82292) / f_get_two_free_regs (82121, kind=6/7 pairs)
  |          -> f_fill_reg (79686): entry+0=node, entry+4=usageCount, entry+8=kind
  |  f_free_reg (83225, L43e7f8)  [12 call sites inside f_eval alone; 50 total across the file]
  |     -> f_dec_usage (82937, L43e534): entry+4 -=1 (or report-error if already 0); also
  |          cascades to partner reg if entry+8==6
  |     -> if entry+4 == 0 (post-decrement): f_remove_from_list(0x10019da8) + f_append_to_list(0x10019da4)
  |          (+ mirrors onto partner reg if entry+8==6)
  |     -> else: return, no list effect  <-- THE deferral point

f_eval_mov / f_eval_irel / f_eval_flt_int_cvt / f_loadstore / f_binary_regs / f_reg /
f_gen_entry / f_gen_entry_exit / f_emit_trap_ri / f_dw_emit_rri / f_emit_branch_rill
  -> all call f_free_reg directly for scratch/operand/prologue-epilogue register teardown
     (Q2 categories A/B/C), all synchronous, none queued.

f_clear_pmov_regs / f_save_pmov_reg / f_load_pmov_regs (55468-55633)
  -> unrelated deferred mechanism: batches pending register-to-register MOVE emission
     (parallel-copy sequencing for call-arg setup) via a 96-bit bitmap at 0x10019d30;
     does not touch entry+4 usage counts or the free/in-use lists.
```
