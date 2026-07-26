# func_8008FF1C session handoff — construction endgame

Read this file first. It supersedes the action list in
`MENU_HANDOFF_FOR_CONSTRUCTION.md`.

Status: investigation intentionally paused on 2026-07-24.

## Outcome

No acceptable stock-toolchain match was found. The best honest stock result
remains 369 matching words out of 371.

This session did produce a structural win: the three open construction routes
from the skeptical handoff no longer fail for vague “we tried many spellings”
reasons. Their target-compatible predecessor classes are now tied to explicit
compiler-state contradictions:

- pointer induction preserves the target graph but cannot acquire the needed
  no-alias state;
- direct induction acquires no-alias state but changes the target graph;
- a zero-cost named-holder defer requires an identity `Ucvt` that `cfe`
  removes; and
- a value-preserving independent pair cycle cannot both leave a 32-bit result
  in even `$12` and preserve the downstream queue state.

The complete evidence from this session is in
`report_construction_endgame.md`. The cumulative cautious synthesis is
`POSTMORTEM.md`.

## Exact current minima

```text
variants/v_base.txt
  LEN 371/371
  FULLWORD_DIFFS 2
  target wants lh/beq t2; candidate uses v1

variants/v_scratch.txt
  LEN 371/371
  FULLWORD_DIFFS 2
  target wants fresh t4 in the later index adds

variants/v_construct_raw.txt
  LEN 371/371
  FULLWORD_DIFFS 38
  has t2 but emits sw before lh
```

The strict gate is:

```sh
python3 menu_research/tools/tryfw.py \
  menu_research/variants/v_base.txt \
  menu_research/tools
```

Any claimed source win must first report `FULLWORD_DIFFS: 0`, then pass the
normal US v80 whole-ROM build with `Verify: OK` and SHA-1:

```text
6d96743d46f8c0cd0edb0ec5600b003c89b93755
```

Diagnostic compiler grants do not qualify.

## What changed in this session

Added durable construction variants:

- `v_construct_raw.txt`
- `v_construct_redundant_direct_seed.txt`
- `v_construct_pointer_roundtrip_seed.txt`
- `v_construct_byte_roundtrip_seed.txt`
- `v_construct_coalesced_direct_seed.txt`
- `v_construct_const_holder.txt`
- `v_construct_parameter_holder.txt`
- `v_construct_noalias_pragma.txt`
- `v_construct_distinct.txt`
- `v_construct_restrict.txt`
- `v_construct_flat_rowsplit.txt`

The flat row-split diagnostic was restored to its best documented declaration
ordering. It currently compiles to 372 words with a 136-byte frame and 311
strict differences. It is valuable because it reaches the target local
no-alias window while demonstrating why the whole nested-loop allocation graph
cannot survive flattening.

The generated `menu_research/tools/cand_fw.c` was reset from
`v_construct_raw.txt`; it contains no `static` linkage experiment residue.

Updated documentation:

- `report_construction_endgame.md`
- `POSTMORTEM.md`
- `MENU_HANDOFF_FOR_CONSTRUCTION.md`
- `H_SOURCE_TEST_PLAN_codex.md`
- `codex_review2_transfer_verdict.md`
- relevant mechanism reports
- root chronological/synthesis notes
- the HTML/PDF research paper

No tracked game source was changed. Do not touch `src/racer.c`; it belongs to a
separate completed workstream and is already dirty in this workspace.

## Strongest new evidence

### Retained-direct predecessor

The strongest missing seed was tested: perform a real direct store through
`gTrackSelectRenderDetails[k]`, then assign an equal
`cur = &gTrackSelectRenderDetails[k]` and use `cur`. IDO does not coalesce the
direct/pointer bases or transfer retained no-alias state. It emits the direct
address work and scores 336.

Address-only redundant seeds, pointer-difference round trips, and byte-pointer
round trips also fail with visible address machinery.

### Flat direct loop

A continuously incremented direct induction disproves “direct always costs
+7.” It can reach the exact local condition window. The cost reappears as a
different outer induction/register graph:

- ordinary `trackY + 1` is strength-reduced into an `s8` recurrence;
- disguising it as `-~trackY` blocks that recurrence but emits two real
  instructions; and
- restoring true nested scope reintroduces direct-address initialization.

This is the core structural dichotomy.

### 32-bit index plus live pair activity

Late construction scripts encode 26,416 overlapping cases in addition to the
22,255 cases already listed in the postmortem. The best new honest basin is
371 words and three differences at `(106,107,109)`. Post-call, cross-call,
live-carrier, and multiply-producer forms all converge on that same trace.
Stage splitting and handoff families do not eliminate it.

### Producer/collapse

`const`, block scope, and reusing the function parameter as the condition
holder all remain the ordinary FW133 collapse. The only zero-real-instruction
defer arm remains the C-unreachable identity `Ucvt` from
`report_ucode_enum.md`.

### Hidden context

`#pragma noalias`, `#pragma distinct`, `__restrict`, `-noaliasok`,
`-noPalias`, and all `static` linkage permutations were checked. None changes
the optimizer decision. The `static` cases change relocation addends only.

## Do not repeat

Do not restart:

- mask-count or signed/unsigned 64-bit conversion sweeps;
- dead register burners;
- declaration-order, scope, `const`, or parameter-holder variants;
- direct-index versus pointer spelling sweeps;
- `restrict`, alias pragma, or hidden-driver-flag guesses;
- pair free-queue rotation/delay experiments; or
- broad loop/CFG permutations without a predicted new compiler state.

These are represented in the reports and construction scripts.

## Honest standing

There is no universal proof over all C source. The remaining logical
possibility is an unconceived topology outside the enumerated normalized
predecessors.

There is also no evidence that the diagnostic query fingerprint or no-collapse
gate existed historically. They are oracles demonstrating sufficiency.

The best-supported historical explanation is a persistent DKR-specific
build-environment/compiler difference that was stable across the five retail
revisions. This remains an inference, not a solution accepted by the
stock-toolchain gate.

## Reopen only on new information

A future session should begin only if it has one of:

1. new Rare/Nintendo source, objects, build scripts, or compiler binaries;
2. a runnable previously blocked compiler/pass combination;
3. a driver option proved to reach `uopt` or `ugen`;
4. a normalized producer arm missing from the current opcode/predecessor
   enumeration; or
5. a source construction with a written prediction for the new compiler state
   and a reason it preserves all 371 target words.

Otherwise, the correct action is to leave the committed DIFFS-2 nonmatch and
this dossier intact.
