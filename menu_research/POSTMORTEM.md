# func_8008FF1C experiment record

Status: 2026-07-24, construction investigation paused at the mechanism-level
stopping point. The operational handoff is
`SESSION_HANDOFF_2026-07-24.md`; the final construction evidence is
`report_construction_endgame.md`.

> **Superseded in part, 2026-07-24 (later session).** A pass-level
> investigation reached a sharper mechanism and corrected two claims in this
> document. Read `report_as1_directive.md` first. In summary:
>
> - The residual is **one misplaced instruction**, not two registers. All 38
>   strict differences in the raw basin follow from `sw v0,0(s0)` being emitted
>   ahead of the load instead of sinking into the branch delay slot.
> - Adding a single `.noalias $17,$16` directive to ugen's assembly listing for
>   the raw-condition source yields `FULLWORD_DIFFS: 0` (verified, with a
>   byte-exact disabled control). The retail stream is reachable from this
>   source's own ucode via one directive.
> - §4.1/§5.1's `v_base` basin is provably terminal: `$10` is in ugen's
>   expression-temp FIFO, `uopt` webs are coloured from a disjoint register
>   set, so a named holder can never produce `lh t2`.
> - §9.5's "direct access costs extra address work" is an artifact, not a law.
>   In a microcase the direct-index and pointer forms are instruction-identical.
>   The cost in this function is caused specifically by the **variable loop
>   bound `startIndex`**, which denies `uopt` the inner trip count.
> - New closure: trip-count knowledge is *necessary* for a zero-cost
>   direct-index store base and *sufficient* to trigger a `trackY + 1` LICM
>   hoist that the retail function does not contain. The two requirements are
>   mutually exclusive, which closes the directive route.
>
> Additionally closed in that session, all negative:
>
> - **The `qemu-irix` differential (§10.0 of the new report).** The original
>   MIPS IRIX `uopt` and `ugen` were run under `qemu-irix` (Docker
>   `linux/amd64`) on the real translation unit. For `func_8008FF1C` the
>   emitted assembly is **line-for-line identical** to the static
>   recompilation, including the alias directives — and contains no
>   `.noalias $17,$16`. The direct-index form emits the pair under the real
>   binaries too. This closes §11.2's "untested compiler-pass binary" and the
>   "recomp is subtly wrong" hypothesis for this site.
> - **Toolchain.** Three independent static recompilations produce
>   byte-identical output for this function. Five runnable `as1` binaries
>   (including the original/freeware 5.3 and patch-260) all give 371/38 on the
>   same binasm — this settles the `as1` dimension of the four blocked
>   pass-matrix cells. Five alternate `uopt` binaries and one alternate `cfe`
>   emit no reg-reg `.noalias` and keep store-before-load.
> - **Options** (reopen-criterion 3, by binary-derived enumeration, not
>   guesses). `-Wf,`→cfe, `-Wo,`→uopt, `-Wa,`/`-Wb,`→as1, and **no driver
>   letter reaches `ugen`**. 21 uopt options, 8 as1 options and 18 cfe options
>   screened; none produces the fact. `-noPalias` and `-f77alias` are
>   byte-identical no-ops, confirming §9.11 independently.
> - **Duplicated store + code hoisting**, a route needing no alias fact at
>   all: uopt sinks rather than hoists; `-docodehoist` is worse.
> - **`volatile` on `gQMarkPtr`**: `as1` rejects the store as illegal, not as
>   less-preferred, so removing the competing delay-slot candidate cannot help.
> - **The community `possibly_better.c` scratch**: its inline store and
>   `trackY = trackCursorY + i` restructure compile byte-identically to
>   `v_construct_raw`.
>
> This is a stronger and more constructive negative result than the one below,
> but it is still a negative result. No match was found.

This document records the experiments performed on `func_8008FF1C`, the
observed outcomes, the compiler decisions isolated by those experiments, and
the remaining unknowns.

It does not identify Rare's original source or build environment. A diagnostic
compiler modification that reproduces the ROM establishes that the modified
decision is sufficient; it does not establish that Rare used that source or
that modification. A source sweep establishes only that the tested sources did
not match. Those distinctions are maintained throughout this record.

`../MENU_FINDINGS.md`, `../MENU_REATTACK.md`, and
`../CODEX_REATTACK_LOG.md` are the chronological working notes. They retain
superseded hypotheses and some claims that were later narrowed. The individual
`menu_research/report_*.md` files are the primary records for the experiments
summarized here.

## 1. Current result

The US v80 reference function contains 371 instructions. The current stock
toolchain reconstruction differs in two instruction words:

```asm
current:  lh   v1,0(s1)     ...     beq  v1,at,<else>
retail:   lh   t2,0(s1)     ...     beq  t2,at,<else>
```

The instruction order and the other 369 words match. A separate 371-word
source construction also reaches two differences, but at a later pair of
`addu` instructions. Later conversion-chain searches found additional
two-difference constructions; none reached zero.

No stock-toolchain source tested in this campaign produced a strict full-word
match.

The skeptical construction handoff's three remaining routes were subsequently
pursued. Direct/pointer alias-state predecessors, independent live pair
activity around a 32-bit index, and non-alias producer/collapse predecessors
all remained negative. The important result is structural: target-compatible
forms normalize into a small set of compiler states whose requirements are
mutually incompatible. This is a rational stopping point, but not a universal
proof over every possible C topology.

Two controlled compiler interventions did produce the reference function:

1. In `ugen`, withholding the named variable's destination register from one
   load makes a simple named-holder source produce the reference stream.
2. In `uopt`, granting load/store disjointness at the relevant alias query
   makes a raw-condition source produce the reference stream.

The second intervention was also tested as a query-specific gate in a complete
US v80 build. That build passed the project's ROM verification and had the
retail SHA-1. The gate was derived from the target query's internal descriptor
fields and is a diagnostic construction, not evidence that the historical
compiler contained that gate.

The historical cause of the two words remains unknown.

## 2. Comparison and control standards

### 2.1 Candidate comparison

Candidates were compiled as part of the full `menu.c` translation unit.
`menu_research/tools/tryfw.py` compares all instruction words in
`func_8008FF1C`, masking relocation-controlled fields. A candidate match
requires:

1. `FULLWORD_DIFFS: 0` for all 371 instructions; and
2. a normal project build with `Verify: OK` and retail US v80 SHA-1
   `6d96743d46f8c0cd0edb0ec5600b003c89b93755`.

"Stock toolchain" in this record means the compiler-pass binaries and flags
used by the current project. It is a test configuration, not a claim that the
same physical binaries were present in Rare's build environment.

The earlier `try.py` score compares mnemonics and registers. It is useful for
sorting candidates but once missed a relocation-affected word. Legacy reports
that use `DIFFS` without saying `FULLWORD_DIFFS` should therefore be treated as
search results unless a later strict check or whole-ROM build confirmed them.

The current WIP, the community mask construction, and the later construction
sweeps were rerun with the strict comparison.

### 2.2 Instrumented compiler controls

The compiler experiments used static recompilations of the original IDO pass
binaries. Logging and behavioral changes were enabled through environment
variables. Before using an instrumented pass, the same pass was run with its
gate disabled and its output was compared with the unmodified pass.

The reports record byte-identical disabled-gate controls for:

- the `ugen` free-register trace and collapse intervention;
- the `uopt` alias trace and alias-grant intervention;
- the mask-allocation rotation/single-register interventions; and
- the heap and stack memory-poisoning hooks.

The query-specific alias intervention additionally had a whole-ROM disabled-gate
control: all C objects were rebuilt and the project still verified against the
retail image.

### 2.3 Experiment counts

The counts in the working notes are not one deduplicated total:

- the campaign log estimates roughly 600 manually constructed or generated
  source variants and about 58,000 earlier decomp-permuter iterations;
- `menu_research/variants/` contains 264 archived variants;
- `menu_research/ledger.txt` contains the earlier machine-scored subset; and
- the later `construct_*.py` scripts encode 48,671 counted, overlapping cases
  in the tables below, plus shared baselines and templates.

This record reports the count for each finite sweep where it is known. It does
not add those counts together or present them as unique source programs.

## 3. The two words in context

The relevant retail sequence is:

```asm
jal   level_world_id
jal   level_name
lh    t2,0(s1)       # signed track ID load
li    at,-1
beq   t2,at,<else>
 sw   v0,0(s0)       # cur->hubName in the delay slot
```

Three conditions must hold at once:

1. the signed halfword load must remain in expression temporary `$10` (`t2`);
2. the unrelated pointer store must be scheduled after the load and placed in
   the branch delay slot; and
3. the temporary allocation state after the branch must produce the remaining
   retail register choices.

Different source constructions satisfy different subsets of those conditions.
That is why the near matches fall into several repeatable states rather than
converging one word at a time.

## 4. Compiler behavior observed at this site

This section describes the tested IDO 5.3 binaries and the relevant paths
through them. It makes no claim about every IDO release or about the historical
DKR build machine.

### 4.1 Load into a named variable

For the fixed statement shape

```c
selectedTrack = gTrackSelectIDs[trackY][trackX];
```

`uopt` assigns `selectedTrack` a register web. In the tested `ugen`, the
`Ustr` statement handler passes that web register to its `Uilod` child as a
destination hint. The load is then emitted directly into the web register. At
this site that register is `v1`; no expression-temporary allocation occurs.

The controlled `UGEN_NOCOLLAPSE` experiment replaces that hint with the
"no destination" value for the selected load. The load then obtains a
temporary from the free-register queue. This is the exact point at which the
named-holder test changes from `lh v1` to a pool-register load.

This experiment isolates a sufficient code-generation decision. It does not
show why the retail object contains `t2`, nor does it prove that the named-holder
source was original.

Primary records: `report_oracle.md`, `report_ucode_enum.md`.

### 4.2 Load and pointer-store ordering

The raw condition

```c
cur->hubName = levelName;
if (gTrackSelectIDs[trackY][trackX] != -1) {
```

already keeps the load in an expression temporary, but the stock compilation
places the pointer store before the load. Its strict score is 38.

Two direct-index loop forms caused `uopt` to retain enough symbol information
to emit a load/store disjointness directive. In those forms, the load moved
above the store and the local four-instruction window matched the retail
ordering. The whole functions did not match: the surviving index and address
work increased the function to 377 or 378 instructions and produced reported
scores of 327 and 329.

The `UGEN_ALIASGRANT` experiment held the byte-required bare-pointer loop
constant and changed only the `uopt` alias result for the relevant
global-load/pointer-store pair. With that grant, the raw-condition source
produced `FULLWORD_DIFFS: 0`.

This is a second sufficient intervention. It acts in a different compiler pass
and starts from a different source frame than the collapse intervention. The
two experiments should not be treated as evidence for one historical
mechanism.

Primary records: `report_loopmatrix.md`, `report_aliasgrant.md`,
`report_descriptor_gate.md`.

### 4.3 Expression-temporary allocation

For the observed `ugen` runs, integer expression temporaries use a FIFO queue
over registers `$8..$15`, `$24`, and `$25`. The observed initial order was:

```text
[14, 15, 24, 25, 8, 9, 10, 11, 12, 13]
```

An allocation removes the head. When a value dies, its register is appended.
The instrumented model predicted all 267 allocation events checked in the
basin-merge run.

The allocator also has a pair path for 64-bit integer values. On the path
relevant to the mask construction it selects an even-aligned pair and carries
the scalar low half in the odd member. Consequently, that 64-bit result can
occupy `$9`, `$11`, `$13`, `$15`, or `$25`, but not the retail destination
`$12`.

The downstream retail register pattern can be reproduced when the queue enters
the branch region in the required state. Several artificial source forms do
this. Reproducing an allocation state does not identify the source that
historically produced it.

Primary records: `report_basin_merge.md`, `report_stmtsplit.md`,
`traces/fltrace2_base.txt`, and `traces/fltrace2_zz1.txt`.

### 4.4 The current WIP's dead `s16` assignment

The current nonmatching C body contains:

```c
temp = (temp = gTrackSelectIDs[trackY][trackX]);
selectedTrack = gTrackSelectIDs[trackY][trackX];
```

With `temp` declared as `s16`, the first expression survives far enough to
alter `ugen`'s temporary queue. The assembler later removes its emitted copy
chain, so it changes register allocation without adding a final instruction.
That queue change makes the rest of the function match, while the live
`selectedTrack` load still collapses to `v1`. The result is the current
two-word mismatch.

Stacking one through six copies of this burner did not change the holder's
`uopt` color. Live interfering variables did change coloring, but also emitted
additional code.

This explains the observed WIP. It is not evidence that the dead assignment
appeared in the original source.

### 4.5 The 64-bit mask construction

The community construction widens the track ID through 64-bit mask operations.
The widening causes the original halfword load to use a pool temporary, and
the assembler removes the intermediate move chain so the branch also uses that
temporary. This satisfies the load and branch-register requirement.

Its later index add travels through the 64-bit pair path. The value therefore
ends in an odd register; the retail instruction uses even register `$12`.
Forcing the allocation to the single-register path can change that instruction,
but it changes the subsequent queue state and breaks the trophies block.

The rotation, delayed-free, and forced-single diagnostic hooks did not produce
a zero-difference result. They establish the pair-path parity restriction and
rule out repairing this exact 64-bit result by simple queue retiming. They do
not rule out a different source topology that uses a 32-bit add and supplies
the later queue effects another way.

Primary records: `report_basin_merge.md`, `report_stmtsplit.md`.

## 5. Source experiments

### 5.1 Earlier archived families

The following table reports outcomes, not source-space proofs.

| Family | Tested outcome |
|:----------------------|:------------------------------------------|
| Named holder with ordinary assignments | Load went to `v1`; the simple form scored 133. |
| Raw array expression in the condition | Load and branch used `t2`; store remained before the load; strict score 38. |
| Dead `s16` assignment used as a queue burner | Current 371-word WIP; strict score 2 at the load and branch. |
| 64-bit masks and widen/narrow forms | Best 371-word construction scored 2 at the later add; other forms commonly scored 56, 119, 128, or more. |
| Same-width casts and arithmetic identities | Usually folded before `ugen` or returned to the named-holder state. |
| Surviving 64-bit conversions | Allocated register pairs and changed later queue state. |
| Integer/float conversions | Emitted real FPU conversion instructions. |
| `s16`/`u16`/`s8`/`u8` conversions | Folded into a narrower load or emitted live shift pairs; none matched. |
| Chain assignments and self-assignments | Collapsed into a named-variable web or emitted additional work; none matched. |
| Scope, lifetime, and declaration order | About 48 cases; none beat 2. Named holders continued to use `v1`. |
| CFG forms | `goto`, labels, inverted conditions, common stores, and related forms were negative. Some labels changed allocation much earlier in the function. |
| Aggregate and bitfield holders | 18 forms; exact signed-load forms still collapsed, while non-collapsing forms added stack or pointer work. |
| Loop forms | 10 forms; two obtained the local target ordering through `.noalias`, but their whole-function scores were 327 and 329. |
| Build modes and optimizer settings | Recorded `-O0`, `-O1`, `-O3`, `-Olimit`, `-mips2`, debug, and coloring-knob tests did not produce the target. |
| Earlier permuter campaign | About 58,000 iterations; no reported full match. |

The machine-readable archive is `variants/`, `ledger.txt`, and `ledger.json`.
The family reports are `report_scope_cfg.md`, `report_loopmatrix.md`,
`report_passmatrix.md`, and `report_ucode_enum.md`.

### 5.2 Fixed RHS-wrapper enumeration

`report_ucode_enum.md` inspected the 152-opcode `ugen` expression dispatch for
the fixed frame:

```c
holder = <WRAP(load)>;
cur->hubName = levelName;
if (holder != -1) {
```

Within that frame:

- a leaf load receives the holder's destination hint and collapses;
- binary, relational, floating-point, and nontrivial unary roots emit at least
  one real instruction;
- a surviving 64-bit conversion allocates a pair;
- narrowing conversions fold into the load or emit live shifts; and
- the only root that both defers the load and adds only a dissolvable move is
  an identity integer `Ucvt`.

The tested front end removes that identity conversion. The source with and
without `(s32)` produced byte-identical objects and content-identical optimizer
listings.

This eliminates zero-cost RHS wrappers for that statement frame. It does not
enumerate alternate statement topology, CFG shape, web formation, alias state,
or an assembler schedule whose producer is outside that frame.

### 5.3 Later construction sweeps

After the first post-mortem and the skeptical construction handoff, additional
strict full-word sweeps were added. They were rerun while preparing this
record. The counts overlap because many scripts include a baseline or share
templates.

| Script | Construction varied | Cases | Best strict result |
|:--------------------------------------|:---------------------------------------------|-------:|--------:|
| `construct_control_sweep.py` | Common-store and duplicated control forms | 7 | 178 |
| `construct_index_sweep.py` | Index width, lifetime, and mask count | 438 | 2 |
| `construct_condition_sweep.py` | Load wrappers, pair activity, and comparison forms | 4,752 | 35 |
| `construct_wide_sequence_sweep.py` | Zero-emission signed/unsigned 32↔64 conversion sequences | 4,452 | 2 |
| `construct_pair_orientation_sweep.py` | Copy orientation within the restored pair cycle | 672 | 2 |
| `construct_conversion_carrier_sweep.py` | Carrier variable, signedness, and sink across eight conversions | 10,240 | 2 |
| `construct_branch_lifetime_sweep.py` | Keeping the condition value live into required index work | 26 | 35 |
| `construct_condition_sink_sweep.py` | Destinations for the final narrowing/comparison value | 207 | 35 |
| `construct_retained_load_sweep.py` | Keeping the pool-loaded value live until the branch | 407 | 35 |
| `construct_fw119_index_sweep.py` | Index/address producers from the 119-difference state | 161 | 119 |
| `construct_trophy_sweep.py` | Trophy expression spellings | 630 | 56 |
| `construct_trophy_stmt_sweep.py` | Trophy statement and live-range boundaries | 47 | 56 |
| `construct_crossuse_sweep.py` | Shared index/trophy wide-value carriers | 216 | 327 |
| `construct_store_barrier_sweep.py` | Real store positions inside the live conversion cycle | 75 | 2 |
| `construct_postbranch_index_sequence_sweep.py` | Live pair activity on the real index after the branch | 3,975 | 3 |
| `construct_preconverted_index_sweep.py` | Pair activity before the real multiply | 3,180 | 35 |
| `construct_fw3_mul_sweep.py` | Multiply-by-six producer forms in the FW3 basin | 264 | 3 |
| `construct_call_split_sweep.py` | Conversion phases split across `level_name` | 3,888 | 3 |
| `construct_live_index_carrier_sweep.py` | Scalar handoffs carrying the real index | 1,044 | 3 |
| `construct_entry_pointer_sweep.py` | Entry-pointer and pointer-to-row forms | 249 | 6 |
| `construct_mul_stage_split_sweep.py` | Independent shift/subtract/shift stages | 6,480 | no match |
| `construct_mul_tail_fusion_sweep.py` | Fused subtract/shift producer trees | 1,326 | no match |
| `construct_mul_pre_post_sweep.py` | Independent conversion phases around the multiply | 1,083 | no match |
| `construct_subtract_handoff_sweep.py` | Final live-scalar handoff at the subtract boundary | 4,852 | no match |

The wide-sequence and carrier sweeps are useful negative results. Repeated
pair-allocation cycles can restore the 371-word length and much of the later
queue state, but the best cases still differ at the load and branch. Changing
the pair's copy orientation did not remove those differences.

These are large finite sweeps, not a finite enumeration of C source topology.

The late rows contain 26,416 overlapping cases in addition to the 22,255
overlapping cases in the earlier rows. The strongest new state is a 371-word
FW3 basin whose differences are fixed at indices 106, 107, and 109. Moving the
real index across the call, changing its carrier, and decomposing
`trackY * 6` into separate arithmetic stages all converge on that same
producer trace.

The first seven late rows were replayed when this document was finalized. A
redundant replay of the 6,480-case stage-split row was intentionally
interrupted at the documentation stop condition; its case count comes from the
checked-in case set and its prior negative result is the starting premise of
the checked-in downstream scripts. See `report_construction_endgame.md` for
that audit distinction.

### 5.4 Targeted structural predecessors

The final session replaced broad syntax search with one-candidate tests for
the missing compiler states.

| Variant | Question | LEN | Strict diffs |
|:--|:--|--:|--:|
| `v_construct_redundant_direct_seed.txt` | Can an outer direct address assignment be eliminated while retaining alias state? | 372 | 167 |
| `v_construct_pointer_roundtrip_seed.txt` | Can `g[cur-g]` cancel to the carried pointer? | 378 | 300 |
| `v_construct_byte_roundtrip_seed.txt` | Can a byte-pointer round trip cancel more cheaply? | 374 | 296 |
| `v_construct_coalesced_direct_seed.txt` | Can an equal direct-memory and pointer web coalesce? | 378 | 336 |
| `v_construct_const_holder.txt` | Does a truthful block `const` holder defer the load? | 371 | 133 |
| `v_construct_parameter_holder.txt` | Does reusing the parameter change holder coloring/collapse? | 371 | 133 |
| `v_construct_noalias_pragma.txt` | Does stock `cfe` support a no-alias source directive? | 371 | 38 |
| `v_construct_flat_rowsplit.txt` | Can continuous direct induction preserve the local target window? | 372 | 311 |

The flat direct loop is the useful counterexample to the old “direct always
costs +7” assertion. It reaches the local no-alias window without re-deriving
the address each element, but flattening changes the outer induction and
register-allocation graph. Restoring a source-visible row counter makes
`trackY + 1` an induction recurrence; disguising the addition prevents that
promotion only by emitting real instructions.

`#pragma noalias` and `#pragma distinct` are unsupported and leave the raw
FW38 behavior; `__restrict` is rejected. The driver's `-noaliasok` spelling is
forwarded only to `as1`, where it is ignored with no `.text` change. Making
either or both relevant globals `static` changes only relocation addends, not
the optimized instruction sequence.

## 6. Compiler and build experiments

### 6.1 `ugen` binaries

`report_hunt.md` isolated `ugen` while holding the other passes fixed.

| Candidate | Result for this function |
|:----------------------|:----------------------------------------------------------|
| IDO 5.1 | Same relevant output as the stock 5.3 test; no match. Four other currently matching `menu.c` functions changed. |
| IDO 5.2 | Same behavior group as 5.1; no match. |
| IDO 5.3, MD5 `9fcff937…` | Project baseline; no stock-source match found. |
| IDO 6.0 | Did not produce the target; changed 52 currently matching functions in the tested translation unit. |
| IDO 7.1 and 7.4.4 | Same tested behavior group as 6.0 for this translation unit; no match. |
| IDO 4.1 | Not tested because the available ECOFF binary was not runnable in the harness. |

The on-disk search found one 5.3 `ugen` hash. The later online survey obtained
an independent pressed 5.3MR CD and SGI's September 1997 freeware release.
Their compiler-pass files, including `ugen`, were byte-identical to each other;
their `ugen` matched the project baseline.

Both SGI patch-CD manifests were searched. No listed patch contained `ugen`.
This rules out the binaries and patch contents that were actually inspected.
It does not rule out an undiscovered pressing, a private build, a local patch,
or a build wrapper.

Primary records: `report_hunt.md`, `report_online_survey.md`.

### 6.2 Pass combinations

The runnable Cartesian pass matrix covered eight combinations of the available
`cfe`, `uopt`, and `as1` variants. Four additional `as1` cells could not be run
because the available artifact was not an IRIX binary usable by the harness.
Across the eight runnable cells, the four principal source states remained:

```text
simple named holder: 133
current WIP:            2
community mask:         2
raw condition:         38
```

The original pressed/freeware `as1` changed three already matching functions.
The 816,064-byte community-circulated `as1` is the build used by the project to
reproduce those functions. This identifies the tested pass combination that
matches the current project; it does not by itself prove which physical
binary Rare ran.

Primary record: `report_passmatrix.md`.

### 6.3 Memory-state tests

The recompiled `uopt` and `ugen` were run with 13 patterns over the guest heap
and the full 1 MB guest stack gap: zero, `FF`, `AA`, `55`, `01`, and eight
seeded random patterns. Heap-only, stack-only, and combined runs produced
byte-identical `menu.c` text, and the site remained in the named-holder state.

A non-conservative recompilation mode also produced identical `menu.c` text.
The test did not poison the initial static values used to model callee-saved
host registers. That untested state is retained as an open, low-level
environment question.

Primary record: `report_mempoison.md`.

## 7. ROM and sister-project observations

These observations constrain explanations but do not identify a cause.

### 7.1 Retail revisions

All five supplied retail ROMs contain the same register/opcode structure for
this function. After masking link-address differences, no hard instruction
differences were found:

| ROM | Site form | Hard differences from US Rev 1 |
|:----------------------|:--------------------------------|------------------------------:|
| USA v1.0 | `lh t2` / `beq t2` | 0 |
| USA Rev 1 | `lh t2` / `beq t2` | reference |
| Europe v1.0 | `lh t2` / `beq t2` | 0 |
| Europe Rev 1 | `lh t2` / `beq t2` | 0 |
| Japan | `lh t2` / `beq t2` | 0 |

This eliminates the hypothesis that the instruction form exists only in the
US Rev 1 ROM. Nearby structural differences in the Japanese ROM are consistent
with recompilation in the same translation-unit area, but they do not prove
that this function was independently recompiled from source.

Primary record: `../MENU_FINDINGS.md` §12.

### 7.2 Other compiled code

The corpus searches reported:

- one exact anomaly-shaped site in the scanned DKR code region: this function;
- no compare-feeding signed-halfword pool temporary in 345 GoldenEye code
  objects, plus a matched GoldenEye function with the corresponding named-local
  pattern compiled into a web register;
- no relevant analog among 124 audited Banjo-Kazooie `-1` comparisons; and
- no full conjunction of the measured features in the scanned Jet Force
  Gemini and Mickey's Speedway USA code regions.

The sister-ROM report notes a residual possibility of unexamined compressed
code or incorrectly classified data. More importantly, absence in another
corpus is statistical evidence, not a proof about this function's source or
compiler.

Primary records: `report_rare_mining.md`, `report_sistergames.md`,
`report_sister_deep.md`.

## 8. Diagnostic exact-match experiments

### 8.1 Withholding the `ugen` destination hint

Input source:

```c
selectedTrack = gTrackSelectIDs[trackY][trackX];
cur->hubName = levelName;
if (selectedTrack != -1) {
```

Controlled change: for the selected signed halfword load stored into the
`v1`-colored web, pass no destination hint to the load evaluator.

Observed outcome: the load used the pool, the pre-assembly listing contained
the predicted load/copy sequence, the assembler removed the copy, and the
function matched the 371-word reference in the oracle run. With the gate
disabled, the same source returned to its stock score.

Established: this intervention is sufficient for this source.

Not established: that this was the original source, that the historical
compiler withheld the hint, or that a general no-collapse rule can reproduce
the shipped translation unit.

Primary record: `report_oracle.md`.

### 8.2 Granting `uopt` load/store disjointness

Input source:

```c
cur->hubName = levelName;
if (gTrackSelectIDs[trackY][trackX] != -1) {
```

Controlled change: grant disjointness for the selected
global-load/pointer-store alias query.

Observed outcome: the load moved above the store, remained in `t2`, and the
function reached strict `FULLWORD_DIFFS: 0`.

A later gate selected only the query whose two internal descriptor words were
`w13 == 0x00040020` and `w15 == 0x00000043`. With that gate and the raw source,
the complete US v80 ROM rebuilt to the retail SHA-1 and passed verification.
With the gate disabled, the patched pass reproduced the stock whole-ROM build.

Established: the alias result is another sufficient control point, and the
constructed single-query intervention can be isolated without changing the
rest of that rebuilt ROM.

Not established: that those descriptor words have a source-level meaning, that
the gate represents a general optimization rule, or that any historical
compiler used it. The gate was selected after inspecting the target and should
be treated as an oracle.

Primary records: `report_aliasgrant.md`, `report_descriptor_gate.md`.

## 9. What is definitively eliminated

Here, "eliminated" is deliberately scoped. It means that the stated mechanism
cannot produce the target under the stated conditions, or that a finite tested
set contains no match.

1. The archived candidates and the later generated cases do not contain a
   stock-toolchain full-word match. This statement applies to those exact
   candidates only.

2. In the fixed
   `holder = <WRAP(load)>; store; if (holder != -1)` frame, no C-reachable
   expression root in the inspected 152-opcode dispatch both defers the load
   and adds no final cost. The sole move-only deferring root is an identity
   integer conversion removed by the tested front end. `const`, block scope,
   and parameter reuse do not change that collapse. This does not close every
   imaginable statement or control-flow frame.

3. A value produced by the relevant 64-bit pair-add path cannot have `$12` as
   its scalar home: the pair base is even and the scalar home is odd. Rotating
   or delaying the tested pair allocation cannot change that parity. The later
   construction campaign separated a real 32-bit index from semantically live
   pair activity across producer, call, carrier, entry-pointer, and arithmetic-
   stage families; none matched. This eliminates those predecessor classes,
   not every theoretical 32-bit construction.

4. A fresh stock `f_base_noalias` query between the direct global object and a
   pointer-class store base cannot grant disjointness in the tested C path;
   `aliaswithptr` returns may-alias. The raw bare-pointer source therefore
   cannot obtain the retail ordering from a fresh query.

5. In the traced raw bare-pointer loop, retained alias state does not supply a
   grant. The relevant table entry is set to may-alias before the later load
   becomes resident, and the guard prevents a new query. The tested direct
   index seeds do establish disjointness but alter the target graph. Address-
   only seeds, direct/pointer round trips, and an equal direct-store/pointer
   coalescing opportunity were tested and did not transfer state at zero cost.
   A flat direct induction can avoid per-element address recomputation only by
   changing the target nested-loop induction graph. This closes the named
   predecessor classes, not every possible object topology.

6. The tested uniform collapse and alias predicates cannot reproduce the
   shipped `menu.c` object. The narrow tested collapse predicate changed 11
   other matching functions; the tested pointer/global alias predicate changed
   16. This eliminates those predicates, not every possible context-dependent
   compiler rule.

7. None of the runnable `ugen` binaries, pass combinations, build modes, or
   optimizer settings listed in the reports produced the target. IDO 4.1 and
   the four blocked `as1` matrix cells were not tested.

8. The obtained pressed 5.3MR distribution, SGI freeware distribution, and
   listed community sources do not contain a distinct 5.3 `ugen`; their
   inspected binary is byte-identical. This does not cover private or
   undiscovered binaries.

9. Changing the tested guest heap and stack contents does not control the
   decision in the recompiled passes. Initial modeled callee-saved register
   state was not directly poisoned.

10. The `t2` form is not unique to one supplied retail revision. It occurs in
    all five tested ROMs.

11. The stock front end exposes no usable `noalias`, `distinct`, or `restrict`
    source route in this language mode; the apparent driver alias flag does not
    reach `uopt` or `ugen`; and external versus `static` linkage does not alter
    the deciding optimized sequence.

No broader source-space or historical-toolchain elimination is supported by
the current record.

## 10. Negative evidence that is not a proof

The following results affect which experiments are worth repeating, but they
do not eliminate a source or build explanation:

- the lack of a matching candidate after large source sweeps;
- the gap between the best near matches and most other source families;
- the absence of the same measured pattern in the scanned sister projects;
- the presence of ordinary named-variable collapse in matched sister code;
- the fact that every publicly obtained 5.3 `ugen` had the same hash;
- the persistence of the retail instruction form across five ROMs; and
- the ability to rebuild the ROM with a target-derived single-query gate.

In particular, none of these observations proves that the original source was
the simple named-holder form, the raw-condition form, or any other tested form.
They also do not prove that Rare used a modified compiler.

## 11. What remains open

### 11.1 Stock-source construction

No finite enumeration of all C-reachable statement and control-flow topologies
has been completed. However, the four concrete questions previously listed
here have now been attacked at their target-compatible predecessor classes:

- the fixed named-holder producer dispatch is empty except for a front-end-
  deleted identity conversion;
- address-only, round-trip, and coalesced direct/pointer alias seeds do not
  create a zero-cost retained grant;
- direct continuous induction reaches the local window only by changing the
  target outer induction/allocation graph; and
- independent, semantically live pair activity around a real 32-bit index
  converges on the FW3 producer basin rather than the target.

An unconceived CFG or object topology remains logically possible. It is no
longer a high-value search prompt by itself. A future source proposal should
name the new normalized optimizer/code-generator state it expects to enter
before compilation. Broad spelling sweeps are exhausted.

### 11.2 Compiler and build history

The following remain distinguishable only with new evidence:

- an untested compiler-pass binary or private/local modification;
- a build wrapper or option not reproduced by the current harness;
- a context-dependent but non-site-specific optimizer rule narrower than the
  tested uniform predicates;
- object reuse, manual assembly, or object-level intervention; and
- a source topology not yet represented in the tests.

These are possibilities, not ranked conclusions. Rare or Nintendo source,
objects, build scripts, or compiler binaries would provide evidence that the
current archive cannot.

### 11.3 Remaining low-level control

The initial static values used by the recompiled pass for modeled callee-saved
registers were not directly poisoned. This is a bounded unperformed
environment test. Nothing in the current heap/stack results predicts that it
will change the site, but it has not been executed.

## 12. Reproduction map

Core candidate tools:

- `tools/tryfw.py`: strict function comparison;
- `tools/try.py`: legacy search score;
- `tools/compile.sh`: stock full-translation-unit compile;
- `tools/base.c`: translation-unit basis;
- `tools/target.o`: reference object;
- `variants/`, `ledger.txt`, and `ledger.json`: archived source candidates and
  earlier scores.

Mechanism reports:

- `report_oracle.md`: `ugen` destination-hint intervention;
- `report_ucode_enum.md`: fixed RHS-wrapper dispatch enumeration;
- `report_basin_merge.md` and `report_stmtsplit.md`: queue and pair-path
  behavior;
- `report_loopmatrix.md`, `report_aliasgrant.md`,
  `report_provenance_hunt.md`, and `report_retained_base.md`: alias and loop
  provenance experiments;
- `report_descriptor_gate.md`: query-specific whole-ROM diagnostic;
- `report_scope_cfg.md`: scope, CFG, and declaration sweep;
- `report_passmatrix.md`: compiler-pass combinations and aggregate holders;
- `report_hunt.md` and `report_online_survey.md`: binary and media searches;
- `report_mempoison.md`: environment-memory tests; and
- `report_rare_mining.md`, `report_sistergames.md`, and
  `report_sister_deep.md`: ROM and sister-project searches; and
- `report_construction_endgame.md`: final structural construction session.

Late construction tools:

- `tools/construct_control_sweep.py`;
- `tools/construct_index_sweep.py`;
- `tools/construct_condition_sweep.py`;
- `tools/construct_wide_sequence_sweep.py`;
- `tools/construct_pair_orientation_sweep.py`;
- `tools/construct_conversion_carrier_sweep.py`;
- `tools/construct_branch_lifetime_sweep.py`;
- `tools/construct_condition_sink_sweep.py`;
- `tools/construct_retained_load_sweep.py`;
- `tools/construct_fw119_index_sweep.py`;
- `tools/construct_trophy_sweep.py`;
- `tools/construct_trophy_stmt_sweep.py`;
- `tools/construct_crossuse_sweep.py`;
- `tools/construct_store_barrier_sweep.py`;
- `tools/construct_postbranch_index_sequence_sweep.py`;
- `tools/construct_preconverted_index_sweep.py`;
- `tools/construct_fw3_mul_sweep.py`;
- `tools/construct_call_split_sweep.py`;
- `tools/construct_live_index_carrier_sweep.py`;
- `tools/construct_entry_pointer_sweep.py`;
- `tools/construct_mul_stage_split_sweep.py`;
- `tools/construct_mul_tail_fusion_sweep.py`;
- `tools/construct_mul_pre_post_sweep.py`; and
- `tools/construct_subtract_handoff_sweep.py`.

## 13. Stopping point

The current stock-toolchain result is 369 matching instruction words out of
371. No clean stock-source match has been found. The current evidence does not
prove that two differences are a universal source-space ceiling, but every
high-value mechanism named in the skeptical construction handoff now has a
decision-level negative result for its target-compatible predecessor classes.

The controlled compiler experiments identify two places where changing one
decision is sufficient to reproduce the function. They explain how the tested
near matches arise and which local mechanisms cannot repair them. They do not
identify what happened in the historical build.

This is the safe stopping point: additional expression, mask, scope, or loop
spelling sweeps are expected to revisit characterized compiler states rather
than make progress.

The function should remain nonmatching unless a candidate reaches strict
`FULLWORD_DIFFS: 0` and passes the normal whole-ROM verification. Reopen the
investigation only when there is either:

- a source construction with a concrete prediction for a previously untested
  normalized compiler state and why it preserves all 371 target words; or
- new external source, object, build, or toolchain evidence.
