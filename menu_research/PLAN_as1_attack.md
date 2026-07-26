# func_8008FF1C — as1/scheduling attack plan

Status: opened 2026-07-24. **Executed through Phase 3; results in
`report_as1_directive.md`.** Phases 0–3 are complete and produced a sharper
mechanism and a new closure argument, but no match. Phases 4–6 were not
started. Read `report_as1_directive.md` before acting on anything below.

Outcome summary:

- Phase 1 verdict was outcome (a): the ordering is decided downstream of
  `ugen`, and `as1` is fed an alias directive. `ugen` emits `sw` before `lh`,
  so `uopt` never reordered.
- The deciding artifact is a single `.noalias $17,$16`. Injecting it yields
  `FULLWORD_DIFFS: 0`.
- Phase 2 (building `as1`/`cfe`) turned out not to be on the critical path:
  `as1` has no alias option, and the directive is produced by `ugen` from
  `uopt`'s alias result. Phase 3 became the main effort.
- Phase 3 found the real cost driver (`startIndex` denying the inner trip
  count) and then a hard conflict between trip-count knowledge and the
  retail function's un-hoisted `trackY + 1`.

This plan is an untracked research document, consistent with the rest of
`menu_research/`. It is not part of any PR.

## 0. Why this reopens

`SESSION_HANDOFF_2026-07-24.md` permits reopening on, among others:

> 2. a runnable previously blocked compiler/pass combination;
> 3. a driver option proved to reach `uopt` or `ugen`;
> 5. a source construction with a written prediction for the new compiler
>    state and a reason it preserves all 371 target words.

Two new observations justify reopening under criteria 2 and 3.

### 0.1 The residual is one misplaced instruction, not two registers

Re-running the strict gate on `variants/v_construct_raw.txt`:

```text
     candidate                     target
102: sw   v0,0(s0)                 lh   t2,0(s1)
103: lh   t2,0(s1)                 li   at,-1
104: li   at,-1                    beq  t2,at,+0x22c
105: beq  t2,at,+0x230              sw  v0,0(s0)      <- delay slot
106: lui  t0,%hi(gQMarkPtr)        sll  t3,s3,0x2
107: sll  t3,s3,0x2                subu t3,t3,s3
...  (pure one-slot shift; the streams re-sync before the end)
LEN 371/371   FULLWORD_DIFFS: 38
```

All 38 strict differences are the consequence of a single instruction being
in the wrong slot. The four-instruction window contains the same four
instructions in both streams, with the same registers — `t2` is already
correct in the raw form. The target sinks `sw v0,0(s0)` into the branch
delay slot; the candidate emits it ahead of the load and then fills the
delay slot with a `lui` hoisted from the else-block.

`report_aliasgrant.md` independently confirms that this same source reaches
`FULLWORD_DIFFS: 0` when the one load/store alias relation is granted.

### 0.2 The `v_base` basin is provably a dead end

`variants/v_base.txt` differs in two words, `lh v1` / `beq v1` where the
target has `t2`. `$10` is a member of `ugen`'s integer expression-temporary
FIFO (`$8..$15,$24,$25`); `uopt` webs at this site are colored from the
disjoint set `$2,$3,$4..$7,$16..$23,$30`. A named holder's web therefore
cannot be colored `$10`, so no amount of coloring pressure on the
named-holder form can produce `lh t2`. `POSTMORTEM.md` §4.1 and §5.2 reach
the same conclusion by a different route.

Consequence: effort should be spent entirely on the raw-condition basin.
The "two register flip" framing is misleading; the real target is one
scheduling decision.

### 0.3 The pass that performs that decision was never examined

Sinking a store past a load and filling a branch delay slot are `as1`'s
responsibilities. The campaign built and instrumented `uopt` and `ugen`
(`/private/tmp/ido-static-recomp/build/5.3/{uopt,ugen}.c`, 4.2 MB and
2.8 MB of readable recompiled C). It never built `as1` or `cfe`.

Two of the campaign's own results point at `as1`:

- `report_loopmatrix.md` records that two direct-index loop forms caused
  `uopt` to "emit a load/store disjointness **directive**", after which the
  load moved above the store. A directive is emitted into assembly text and
  consumed by `as1`.
- `report_passmatrix.md` records four `as1` matrix cells as never runnable,
  and notes that the project ships a community-circulated `as1` that differs
  in behaviour from the pressed/freeware one.

`ido-static-recomp`'s Makefile lists `as1` and `cfe` as buildable targets
for both 5.3 and 7.1. The blocked cells are blocked only by tooling that
already exists in this workspace.

## 1. Goal and acceptance gate

Unchanged from the postmortem. A candidate is a solution only if:

1. `python3 menu_research/tools/tryfw.py <variant> menu_research/tools`
   reports `FULLWORD_DIFFS: 0`; and
2. `make VERSION=v80` reports `Verify: OK` with SHA-1
   `6d96743d46f8c0cd0edb0ec5600b003c89b93755`.

Diagnostic compiler grants, gates, and instrumented passes are oracles. They
never qualify. Any candidate *pass binary* must additionally rebuild the
entire ROM, not merely this function — the tested uniform predicates already
failed that bar (`POSTMORTEM.md` §9.6).

## 2. Phases

### Phase 0 — Pass-pipeline harness

Capture the exact pass invocations that `tools/ido-recomp/macos/cc -verbose`
performs for the `menu.c` translation unit, and build a replay harness that
retains every intermediate so `cfe`, `uopt`, `ugen`, and `as1` can each be
run individually and substituted.

Deliverable: `menu_research/tools/passrun.sh` plus a retained intermediate
set for `v_construct_raw.txt`.

Nothing in the current archive can look between passes. This is the enabler
for every phase below.

### Phase 1 — Determine the deciding pass

Dump `ugen`'s assembly output for:

- (a) `v_construct_raw.txt`;
- (b) the same source under the `UGEN_ALIASGRANT` uopt oracle;
- (c) the two direct-index loop forms from `report_loopmatrix.md` that did
  obtain the target's local ordering.

Three mutually exclusive outcomes, each with a defined next action:

| Observation | Conclusion | Next |
|:--|:--|:--|
| (a) has `sw` before `lh`; (c) has `lh` first and carries an alias directive | `as1` is directive-driven | the directive text becomes the target artifact; go to Phase 2 |
| (b) differs from (a) at ugen output | `uopt` decides; `as1` never had the opportunity | as1 line collapses; go to Phases 4–5 |
| ugen output identical across (a)/(b) but objects differ | `as1` decides alone | go to Phase 2 |

This is the decisive experiment and is cheap. Run it first.

### Phase 2 — Build and instrument `as1` (and `cfe`)

1. `make VERSION=5.3 build/5.3/out/as1` in `/private/tmp/ido-static-recomp`.
2. Control, matching the discipline used for the `ugen`/`uopt` work: the
   recompiled `as1` with no instrumentation must reproduce the project's
   current objects byte-identically, and the whole ROM must still verify.
3. Instrument the delay-slot filler and the memory-disambiguation path.
   Required log content: every instruction considered as a fill candidate
   for the `beq` at this site, and the specific reason `sw v0,0(s0)` is
   rejected.
4. Instrument the directive parser: which alias/scheduling directives `as1`
   accepts, and what internal state each sets.

Deliverable: a written predicate — the exact condition that must hold for
`as1` to sink the store.

### Phase 3 — Natural-trigger hunt

Search source space to satisfy the Phase 2 predicate. This is predicate-led,
not a spelling sweep; the postmortem's do-not-repeat list stands.

One cheap untested construction is included regardless of the predicate:
direct-index *only* the single aliasing statement,

```c
gTrackSelectRenderDetails[n].hubName = levelName;
```

with `n` an explicit inner-loop counter, leaving every other access on
`cur->`. Prediction: `uopt` seeds a `D/D` no-alias relation for this store,
and strength reduction CSEs the address against the existing `cur`
induction, so no address machinery survives. This is distinct from
`v_construct_coalesced_direct_seed.txt`, which kept two semantically
different values live and scored 336.

### Phase 4 — Complete the pass-binary matrix

Build `as1` and `cfe` for 5.3 and 7.1, settle the four cells recorded as
never runnable in `report_passmatrix.md`, and run the raw source through
every combination. Guard: whole-ROM rebuild to retail SHA-1.

### Phase 5 — Binary-derived option enumeration

`uopt.c` and `ugen.c` are readable recompiled C; their option-parser tables
can be read directly rather than guessed. For `as1` and `cfe`, recover the
tables from the recompiled sources once Phase 2/4 build them. Add argv
logging to each pass to prove which `cc` / `-Wo,` / `-Wa,` / `-Xo` spellings
actually arrive. Test every option that provably reaches a pass.

This closes reopen criterion 3 with a binary-derived enumeration rather than
the flag guesses the postmortem already rejected.

### Phase 6 — External evidence

Other IDO-based N64 decompilations that hit "a store will not sink past a
global load", DKR decomp repository issues and pull requests, and the
`decomp.me` scratch `bQDRA` history.

### Phase 7 — Landing

On `FULLWORD_DIFFS: 0`: strict gate, then whole-ROM verify, then replace the
`#pragma GLOBAL_ASM` in `src/menu.c` with the C body and remove the
`NON_MATCHING` ifdef, commit, open the PR. Update `POSTMORTEM.md` and
`SESSION_HANDOFF_2026-07-24.md` to record the supersession.

## 3. Falsification

If Phase 1 shows that `uopt` performs the reordering and `as1` was never in
a position to help, the `as1` line collapses to Phases 4–5 and this plan
pivots to option mining plus alias-state work. That outcome is to be
reported, not worked around.

## 4. Scope

`src/menu.c` only. `src/racer.c` and `src/objects.c` are out of scope;
`func_80017A18` is owned by a separate workstream.
