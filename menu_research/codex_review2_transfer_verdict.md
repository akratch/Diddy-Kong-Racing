# REVIEW 2 + TRANSFER VERDICT

> **Execution status, 2026-07-24:** The corrective construction plan in this
> review was carried out. The unenumerated retained-direct predecessors,
> independent 32-bit/pair constructions, and final producer routes were tested
> without a stock match. The earlier static transfer verdict immediately below
> is superseded by the trace/oracle result in `report_stmtsplit.md`: the
> datatype hits the pair path and is parity-locked. See
> `report_construction_endgame.md` and `SESSION_HANDOFF_2026-07-24.md`; do not
> treat this document's action list as pending work.

## 1. Racer → menu transfer: VALID — outcome (a)

Menu’s low-add destination is a plain, event-controllable FIFO head-pop from the same allocator mechanism as racer.

### Exact menu path

| Stage | Source |
|---|---|
| Binary dispatch | menu `ugen.c`, `L432890`, lines 63885–63940 → `f_eval2` |
| Operands released before destination selection | `f_binary_regs`, lines 44927–45012 |
| Destination request | `f_eval2`, `L429f10`, lines 50747–50762 |
| `hint == 0x48` | `f_get_dest`, `L42698c`, lines 45453–45472 → `f_get_free_reg` |
| One-register branch | `f_get_free_reg`, `L43e124`, lines 82497–82524 |
| FIFO allocation | `f_get_one_free_reg`, `L43df40`, lines 82421–82435 → `f_remove_head(0x10019da4)` |
| Literal head removal | `f_remove_head`, `L43c9ec`, lines 80091–80120 |

`f_get_free_reg` is pair-aware in general, but not for this event. Its two-register test uses datatype mask `0x05010000` at lines 82497–82511. The low-add datatypes `{5,7,15}` reported in `report_basin_merge.md:9–12` miss that mask, so execution falls through to `f_get_one_free_reg` at lines 82519–82524.

`f_dw_emit_rrr` does not select or reuse a destination: `f_eval2` passes the already-selected `v0` as `a1` at lines 50756–50762; `f_dw_emit_rrr` merely records `s0=a1`, `s1=a2`, `s2=a3` at lines 33365–33367.

### Racer equivalence

Racer uses the same labels, list and rule:

- `f_get_dest`: racer `ugen.c:45592–45612`.
- `f_get_free_reg` one-register fall-through: `82848–82874`.
- `f_get_one_free_reg` removes `0x10019da4` head: `82766–82780`.
- `f_remove_head`: `80328–80357`.

This agrees with `TRACE_FINDINGS_2026-07-24.md:303–322`: all relevant racer allocations were `hint=0x48` FIFO pops, with event ordering—not selection policy—being source-controllable.

### Required event slack

Immediately before the menu low-add, the current effective queue is:

```text
[ $11, $12, ... ]
```

To obtain `$12`, a split must create exactly one position of slack between operand release and `f_get_dest`:

1. Delay `FREE($11)` until after the low-add destination pop; or
2. Move one zero-emission `ALLOC($11) → FREE($11)` cycle into that interval, rotating the queue to `[$12, ..., $11]`; holding `$11` through the pop also works.

A split entirely before `$11` is released or after `f_get_dest` is inert. The retimed uop must survive uopt while adding no final instruction.

Therefore `report_basin_merge.md:19–23` did not prove joint unsatisfiability: it fixed the pair/copy facts but did not enumerate event-order predecessors. Its closure has the same gap racer exposed.

## 2. H-SOURCE closure review

### 2.1 Provenance opportunity count: narrow result sound; broad closure refuted

The alias truth table is sound:

- D/D overlap test: `uoptemit.c:250–252`.
- D/P calls `aliaswithptr`: `uoptemit.c:253–262`.
- P/P is may-alias in C: `uoptemit.c:273–287`.
- `aliaswithptr` returns true for C: `uoptkill.c:116–128`.

Thus a fresh gTrackSelectIDs-D versus cur-P query cannot grant no-alias.

The opportunity-count conclusion is overbroad:

- `report_provenance_hunt.md:40–49` gives changed-function counts and approximate categories, not the required per-query replay/site table from `H_SOURCE_TEST_PLAN_codex.md:461–491`.
- Its stated `load_menu_text` justification is suspect under its own G definition. `gMenuText` is a global pointer (`src/menu.c:550`); its value is loaded and dereferenced at lines 1971, 1982 and 1986. That is a `POINTER_LOAD` root, explicitly excluded from G by `H_SOURCE_TEST_PLAN_codex.md:474–480`, unless an unidentified different query is causal.
- Even accepting `func_80083098`, a semantic refinement can distinguish it: `introCharData` is a bounded, single indexed address (`src/menu.c:3231–3235`), while the target is a loop-carried affine induction over `gTrackSelectRenderDetails` (`src/menu.c:8851–8864`). “Loop-carried induction over one fixed global array, proven disjoint from another fixed global” is principled and not a raw descriptor fingerprint.

Verdict: the count falsifies the coarse uniform “single/distinct-global-origin” rule. It does not falsify every principled alias rule or “better general analysis” story.

### 2.2 Retained-direct-base proof: raw path closed; universal theorem incomplete

Confirmed:

- A retained direct base survives later P accesses through the early return at `uoptemit.c:352–354`.
- `unaltab==1` prevents re-query at lines 372–375 and is written on may-alias at lines 382–390.
- `cur = gTrackSelectRenderDetails` is address formation, not itself a memory-access seed.
- The tested direct-index forms do establish D/D no-alias but add instructions: `report_retained_base.md:30–39`.

Not confirmed:

- “P/P before gTrackSelectIDs residency” is not a source-topology invariant. Evaluation topology can make the D base resident first.
- That reordering does not help: D/P is also constant may-alias, so either order drives the pair to `1`.
- The theorem jump at `report_retained_base.md:41–50`—every possible D seed necessarily requires the tested direct-index shape and `LEN>=377`—does not supply the static predecessor enumeration required by `H_SOURCE_TEST_PLAN_codex.md:363–387`. A live direct seed reusing existing target operations, same-register reuse, or another retained-state predecessor is asserted away rather than enumerated.

Verdict: fresh-query and raw bare-pointer routes are closed. The report is strong evidence against retained seeding, but it is not a complete all-topology proof as written.

## 3. Ranked next steps

### If the statement split works

1. Run relocation-masked full-word comparison, then a clean whole-ROM build. Require `Verify OK` and retail SHA-1 `6d96743d46f8c0cd0edb0ec5600b003c89b93755`.
2. Diff uopt ucode and FIFO events against `v_scratch`; document the single crossed allocation/free interval and minimize the source form.
3. Stop Step 8. A verified stock-source match supersedes closure work.

### If the statement split fails

1. Run a diagnostic event oracle: delay `FREE($11)` past `L429f10`, or rotate `$11` once between its release and `f_get_dest`. Check whether this alone produces full-word zero. This is an oracle, not an acceptable match.
2. If the oracle wins, enumerate statement boundaries/topologies by normalized uopt trace, looking specifically for an existing zero-emission uop whose allocation/free crosses that interval.
3. If the oracle loses, record all secondary changed events; mask-basin repair by single-position retiming is then mechanically dead.

### Step 8 value

A targeted Step-8 pass is now priority 1, not low-value: racer proves statement topology can retime this exact allocator class without added instructions.

A full exhaustive Step-8 closure is conditional:

- Oracle reaches full-word zero but tested splits fail: high-value and warranted.
- Oracle cannot reach zero: low expected match value, though still required before claiming formal H-SOURCE falsity.
- A verified split matches: no closure pass needed.
