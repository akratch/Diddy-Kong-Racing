# func_8008FF1C — construction handoff (skeptical edition)

> **Status update, 2026-07-24:** This was the incoming brief for the completed
> construction session. Its three open targets were pursued and no stock
> source match was found. Do not restart from the action list below. Read
> `SESSION_HANDOFF_2026-07-24.md` first, then
> `report_construction_endgame.md` for the evidence. This file is retained as
> the pre-session statement of what was genuinely open.

Purpose: hand a fresh solver (Codex, via construction) the exact state of the
menu match attempt, with the bold claims flagged by how much weight they
actually bear. The goal of this document is NOT to convince you the function
is closed. It is to point you at the two places the closures are soft, keep
you off the ~600 dead variants, and hold any candidate to a real gate.

Read this as adversarial: where a claim is a proof, it says PROVEN; where it is
an inference or an unenumerated assertion, it says so. Attack the SOFT ones.

---

## 1. The goal and the acceptance standard

Match `func_8008FF1C` (menu.c, track-selection render/update) to the retail
US v80 ROM under the STOCK canonical toolchain. A submittable win is:

1. relocation-masked full-word equality for all 371 instructions
   (`menu_research/tools/tryfw.py`, FULLWORD_DIFFS 0), THEN
2. the project's real whole-ROM build with the GLOBAL_ASM stub removed:
   `PATH="/opt/homebrew/opt/make/libexec/gnubin:$PATH"`, `REGION=us
   VERSION=v80`, require `Verify: OK` and retail sha1
   `6d96743d46f8c0cd0edb0ec5600b003c89b93755`.

No compiler patch, no env gate, no descriptor fingerprint. Those exist in this
archive as diagnostics only (§6) and are NOT submittable — decomp.me runs the
stock compiler. The loose mnemonic metric (`try.py`) is search guidance only;
it once under-counted by one relocation word.

Anti-hack line (a candidate that reaches FULLWORD 0 is still rejected if):
dead temp burners whose only purpose is allocation rotation, redundant 64-bit
masks/casts used solely to shape registers, false `const`/`restrict`/`volatile`,
UB, or any construct with no coherent source-level purpose. An unusual but
semantically honest loop/assignment topology is acceptable. (Caveat: the
committed WIP itself uses a dead `temp = (temp = ...)` burner and the community
idiom uses a 64-bit mask — the bar for "honest" here is contested; if you reach
0 with a burner, flag it and let the project decide.)

---

## 2. Current state — two DIFFS-2 basins

The reconstruction is 369/371 in two different ways (this predates all of our
work; the community decomp.me scratch L6qKV is at 99.69% in the second basin):

- **WIP basin** (`menu_research/variants/v_base.txt`, committed): downstream
  allocation exact; the load/branch use `v1` where the ROM uses `t2`
  (a ugen pool temp). first_diff 102.
- **Mask basin** (`menu_research/variants/v_scratch.txt`, community idiom):
  `lh t2` exact; two `addu` operands wrong at idx 110/111 (ours `$11`/t3
  in-place, ROM `$12`/t4 fresh). first_diff 110.

The target simultaneously needs: (F1) the load as a pool temp `t2`, not
collapsed into the holder's colored web; (F2) the `cur->hubName` store in the
branch delay slot; (F3) no perturbation of the following index/trophies code.

---

## 3. Confidence ledger — attack the SOFT rows

### PROVEN (do not expect to overturn; verify if you must, don't sink time)
- **Mask-basin parity** (`report_stmtsplit`, oracle-tested). The 64-bit
  low-add datatype hits the pair mask `0x05010000` → `f_get_two_free_regs` →
  even-aligned base, home = base+1 = ALWAYS ODD {9,11,13,15,25}. `$12` (even)
  is unreachable by any 64-bit pair-add. Oracle (rotate/delay/force-single)
  cannot reach FULLWORD 0. SKEPTICISM: this proves you cannot get `$12` at the
  low-add head *by free-queue retiming while keeping the 64-bit index*. It does
  NOT prove the trophies block genuinely REQUIRES the 64-bit pair — that half
  rests on the specific mask-idiom structure (see SOFT row A). If trophies can
  be satisfied with a 32-bit index by some other structure, the parity lock is
  bypassed, not beaten. Probe that, not the retiming.
- **Fresh alias query** (`report_provenance_hunt`, truth table validated
  7.1==5.3). In C, a Direct-global load vs a pointer store is a compile-time
  CONSTANT may-alias (`aliaswithptr` returns true unconditionally). So F2
  cannot come from a fresh `f_base_noalias` query. Solid.
- **ucode RHS-wrapper frame** (`report_ucode_enum`). Inside the fixed frame
  `holder = <WRAP>; store; if (holder != -1)`, the only zero-cost collapse-
  defer shape is an identity int cvt, which cfe deletes. Enumeration complete
  FOR THAT FRAME ONLY (see SOFT row C).

### STRONGLY EVIDENCED BUT ASSERTED — the real construction targets
- **SOFT-B: retained-direct-base universal theorem** (`report_retained_base`).
  The RAW bare-pointer path is genuinely closed (unaltab pre-locked to 1 by an
  early P/P query before the load is resident; `!=1` guard blocks re-query).
  BUT the UNIVERSAL claim — "every Direct-seed of a retained no-alias
  necessarily adds the +7-instruction direct-index shape" — is ASSERTED, not
  enumerated. Codex review flagged this. NOT tested: a live direct seed that
  REUSES an operation already present in the 371-word target; same-register
  reuse establishing unaltab==2 that survives to the branch; a retained-state
  predecessor other than the direct-index loop. THIS IS A CONSTRUCTION TARGET:
  enumerate the static predecessors of a retained no-alias per
  `H_SOURCE_TEST_PLAN_codex.md` Steps 6-7 and find one whose seeding access is
  already an instruction the target emits. If F2 can be gotten this way with
  zero added instructions, the raw source (which already gives F1=t2) matches.
- **SOFT-A: the trophies-needs-64-bit half of the parity theorem.** The mask
  basin's `$11`-vs-`$12` is parity-locked ONLY because the index is 64-bit AND
  trophies depends on the 64-bit pair consumption advancing the queue. Nobody
  constructively tried to satisfy trophies with a 32-bit index (which frees the
  even register) via a different trophies/index source structure. CONSTRUCTION
  TARGET: can the index be 32-bit (even dest reachable) while the trophies
  block reaches its target registers by an independent route? If yes, the mask
  basin closes at 0.

### SWEPT, NOT CLOSED (low value — do not re-run without a NEW mechanism)
- ~600 source variants + ~58k permuter iterations; scope/lifetime/decl-order
  (~48 cells); CFG topologies (switch, goto diamonds, store commoning,
  inversions); signatures/prototypes; aggregates/bitfields (18); the 10-form
  loop-induction matrix; cast/chain-assign/comma families. All negative.
  Ledger: `menu_research/ledger.txt` (nothing scores 3-37; two DIFFS-2 basins).

### OPEN — genuinely un-enumerated (Codex ranked priority 1)
- **Step 8: non-alias producer / collapse-deferral topology predecessors.**
  The WIP basin's F1 (get `t2` instead of collapsing to `v1`) is a ugen
  ilod→web COLLAPSE / uopt COLORING decision, not a free-queue event. The
  racer statement-split technique is STRUCTURALLY INAPPLICABLE here (proven for
  the mask basin, and coloring ≠ event-ordering). What is NOT enumerated: the
  complete set of ugen/as1/uopt normalized producer traces that emit the exact
  4-word target window, and which are C-reachable. This is the largest open
  surface. SKEPTICISM: the coloring analysis (`report_basin_merge` Direction B)
  showed forcing the holder to `t2` needs 7 zero-code interfering webs which
  don't exist — but that argued at the web level, not a full producer
  enumeration. A topology that changes WHAT uopt colors (not just adds dead
  webs) was not exhausted.

### INFERENCE, NOT PROOF (context — don't let it discourage construction)
- **Singleton / build-environment provenance** (`report_sister_deep`,
  `report_provenance_hunt` §15). The anomaly is absent from and the normal
  collapse present in JFG (→a2), Mickey (→a3), GoldenEye (→s0), Perfect Dark;
  the ROM is bit-stable across 5 retail revisions. This is the strongest
  EXPLANATION but it is a negative inference. A stock-source match remains
  logically possible (~3-5%) and would beat this inference. Do not treat "it's
  a compiler thing" as a reason not to try SOFT-A / SOFT-B / Step 8.
- **"No principled toolchain rule is zero-collateral"** — OVERSTATED (Codex
  corrected it). The coarse single/distinct-global-origin rule breaks ≥3
  matched functions, but a REFINED rule ("loop-carried induction over one fixed
  global, proven disjoint from another") might be zero-collateral. NOTE: this
  is a TOOLCHAIN rule, not a source fix — it does not yield a decomp.me match.
  Relevant only to the provenance story, not to the win condition.

---

## 4. The construction plan (ordered by expected value)

1. **SOFT-B (retained no-alias via an existing operation).** Highest value:
   the raw source already gives F1=t2; you only need F2 (store in slot) via a
   retained disjointness whose seed is already an emitted instruction. Trace
   `f_base_in_reg`/`unaltab` on the raw source (instrumentation exists, §6);
   enumerate what would establish unaltab[cur-reg][load-reg]==2 before the P/P
   lock, using operations the target already contains. Kill criterion: prove
   (by static predecessor enumeration, not spelling sweep) that every seed
   either adds an instruction or is pre-empted by the P/P lock.
2. **SOFT-A (32-bit index + independent trophies).** The mask basin is 2 words
   from done. Try to reach the trophies target registers with a 32-bit index
   (even dest reachable). Kill criterion: prove trophies' target queue state is
   only reachable via the 64-bit pair consumption.
3. **Step 8 (WIP-basin producer enumeration).** Largest and least likely.
   Backward-enumerate normalized producers of the 4-word target window through
   as1/ugen/uopt; classify C-reachability. Likely returns a closure, not a
   match. Do this last, or only if 1-2 dead-end and you want formal closure.

For 1 and 2, the discipline that has actually worked here: read the deciding
compiler code and TRACE the events FIRST; predict the register from the model
BEFORE compiling; only then write source. Blind permutation is exhausted.

---

## 5. Reproduction and tooling (durable in menu_research/)

- Harness: `tools/try.py` (guidance), `tools/tryfw.py <variant> <dir>`
  (FULLWORD, reloc-masked, the pre-filter). `tools/base.c` (TU basis),
  `tools/target.o` (reference), `tools/compile.sh` (stock repo toolchain
  invocation). `tools/score_all.py` (parallel ledger). `tools/klist.sh` (pre-as1
  `-K` listing), `tools/utrace.sh` (ucode listing). NOTE: klist/utrace embed
  session-scratch paths — re-root them before use.
- Variants: `menu_research/variants/` (264 files at final handoff, incl. v_base, v_scratch,
  v_natural, v_zz1). Scores in `ledger.txt`.
- Instrumented compilers (VOLATILE, in /private/tmp scratchpads; regenerate
  from the recomp source per each report's recipe): the ugen free-queue tracer
  (`UGEN_FLTRACE`, and racer's richer `CODEX_UGEN_TRACE`), the uopt alias
  tracer (`BIR_TRACE`) + the descriptor gate (`UGEN_ALIASGRANT`), the
  no-collapse oracle (`UGEN_NOCOLLAPSE`), the mask-basin oracle
  (`CODEX_MENU_ROTK`/`CODEX_MENU_SINGLE`). ALL env-gated, ALL fidelity-verified
  byte-identical when unset. The recomp uopt/ugen sources with 542 named
  functions are the readable oracle; validate any 7.1-decompilation claim
  against the 5.3 recomp.
- Whole-ROM verify: build a fresh `git worktree` (never modify the main tree);
  swap in a stock toolchain copy; the target function's GLOBAL_ASM stub is at
  `asm/nonmatchings/menu/func_8008FF1C.s`; the C body site is `src/menu.c`
  around the `cur` loop.
- DO NOT touch `src/racer.c` (parallel workstream, now matched).

---

## 6. Full report index (menu_research/)

report_oracle, report_hunt, report_online_survey, report_ucode_enum,
report_basin_merge, report_scope_cfg, report_loopmatrix, report_rare_mining,
report_passmatrix, report_sistergames, report_sister_deep, report_mempoison,
report_aliasgrant, report_descriptor_gate, report_provenance_hunt,
report_retained_base, report_stmtsplit; the plan `H_SOURCE_TEST_PLAN_codex.md`;
the review `codex_review2_transfer_verdict.md`; synthesis `MENU_FINDINGS.md`
(§1-15); narrative history `../MENU_REATTACK.md`, `../CODEX_REATTACK_LOG.md`.

---

## 7. Honest probability and stop condition

A stock-toolchain submittable match: ~3-5% and falling. The three known routes
to the `t2` load are closed (raw+disjointness, holder-coloring, mask-parity);
a win needs a fourth route, living in SOFT-B, SOFT-A, or Step 8. Most likely
outcome of pursuing them is a definitive closure, not a match.

Stop condition: if SOFT-B yields no zero-instruction seed under static
predecessor enumeration, SOFT-A proves trophies needs the 64-bit pair, and
Step 8's producer enumeration is complete with no C-reachable target trace,
then the stock-source match is closed at the decision level and the honest
terminal state is the committed 369/371 WIP plus this dossier. Until all three
are enumerated (not swept), the correct verdict is OPEN, not closed.

Do not claim a match without whole-ROM `Verify OK` + retail sha1. Do not claim
closure without static enumeration (spelling sweeps are not proofs — this
project has had four "closed" claims corrected by later work: all-of-C, the
fixed-loop provenance, the li/beq adjacency law, and the mask-basin static read
that the oracle overturned).

---

## 8. Construction-session resolution (added after execution)

The incoming priorities produced the following results:

1. **SOFT-B:** address-only direct seeds never enter the alias state machine;
   real direct-memory seeds retain their address computation; direct/pointer
   round trips do not cancel; and the strongest coalescing predecessor
   (direct store followed by an equal `cur=&g[k]`) retains both address webs.
   A flat direct induction can remove the +7 address cost, correcting the
   earlier universal theorem, but only by changing the target's nested-loop
   induction/allocation graph.
2. **SOFT-A:** the real 32-bit index was separated from semantically live pair
   activity across producer, call-boundary, carrier, entry-pointer, and
   shift/subtract/shift-stage families. The strongest new basin is 371 words
   and three differences at indices 106, 107, and 109. No independent live
   pair construction preserves both the even `$12` result and the trophies
   queue state.
3. **Step 8:** the finite `ugen` root enumeration still has one zero-cost
   defer arm—identity integer `Ucvt`—and it remains unreachable because `cfe`
   removes it. `const`, block scope, and parameter reuse do not alter the
   holder collapse. Outer direct-loop topology reaches the local window only
   through the alias route and fails the whole target graph.

Boundary checks also eliminated supported alias pragmas/qualifiers, hidden
driver flags, and global `static` linkage as missing inputs.

This is a rational stopping point, not an all-C theorem. The specific open
mechanisms named in this handoff are exhausted to their target-compatible
predecessor classes; the residual logical possibility is an unmodeled topology
or new historical build evidence. Full results and exact scores:
`report_construction_endgame.md`.
