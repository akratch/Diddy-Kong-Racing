# H-SOURCE TEST PLAN

## 0. Required conclusion standard

H-SOURCE is true only if a semantically legitimate C reconstruction, compiled by the unmodified canonical toolchain, produces:

1. relocation-masked full-word equality for all 371 instructions;
2. the exact `[lh t2][li][beq t2][sw delay-slot]` sequence;
3. a normal whole-ROM build;
4. `Verify OK` and retail SHA-1.

Instrumentation and forced decisions are diagnostic only. A compiler patch, including the zero-collateral descriptor gate, cannot establish H-SOURCE.

H-SOURCE is false only after every normalized compiler decision trace capable of producing the target has been shown C-unreachable or incompatible with another target word. Source-family exhaustion is insufficient.

---

## 1. Audit of prior closure claims

### 1.1 Genuinely closed

| Claim | Status | Exact scope |
|---|---|---|
| The retail/local difference is two register fields | Closed | Full-word comparison, not the loose mnemonic metric. |
| Granting the target load/store disjointness is sufficient | Closed | The raw source plus the target `f_base_noalias` grant gives 371/371 words. Sufficiency does not prove uniqueness. |
| The relevant grant originates in `uopt` | Closed | `f_base_in_reg -> f_base_noalias -> Uunal`; `ugen` translates the directive. |
| Stock C behavior for the observed query is may-alias | Closed | The pair is direct global `islda` versus pointer-variable `isvar`; `aliaswithptr` returns true for non-`Rmt` objects in C. |
| The fixed holder frame has no zero-cost RHS wrapper | Closed lemma | `holder = <WRAP>; store; if (holder)` only. The 152-opcode dispatch enumeration is valid inside this frame. |
| Individual WIP and mask basins have the stated queue/color contradictions | Closed locally | Applies to those normalized ucode/emission basins, not every possible topology. |
| The tested ten loop forms have the reported behavior | Closed observations | Two retain direct-symbol provenance and gain `.noalias`; eight do not. |
| The canonical installed pass combination is pinned | Closed for tested binaries | Does not constrain source topology. |
| Uniform `k31`/collapse rules damage matched code | Closed for those predicates | Counts byte effects of those exact gates. |
| Descriptor pair `w13+w15` is ROM-unique | Closed observation | It establishes a unique raw fingerprint, not a unique semantic category. |
| `gTrackSelectIDs` is writable | Closed | `const` is not a legitimate source lever. |

### 1.2 Swept, not closed

These are negative searches:

- 500+ source variants and the permuter campaigns;
- the ~48 scope/CFG/signature cells;
- the 18 declaration/aggregate cells;
- the ten loop spellings;
- direct-index, pointer-copy, cast, comma, branch duplication, and holder families;
- compiler optimization-level and pass-binary matrices;
- Rare-game and revision singleton surveys.

They are useful posterior evidence, not universal source-space proofs.

### 1.3 Specific overclaims

1. **Dispatch lemma promoted to theorem.**  
   `report_ucode_enum` enumerates expression roots in one statement frame. It does not cover:

   - raw conditions;
   - statement reordering;
   - earlier alias-state seeding;
   - alternate CFGs;
   - store commoning;
   - different web identities;
   - different induction representations;
   - compensating allocator state elsewhere.

2. **“Strength reduction destroys provenance” is under-instrumented.**  
   The loop matrix observed before/after outcomes but did not record:

   - the exact expression/ichain carrying the global root;
   - the transformation that replaced it;
   - every write to `stat->u.store.baseaddr` and load `unk34`;
   - the history of `baseregbase[reg]`;
   - `unaltab` transitions;
   - whether an earlier direct base could survive a later non-direct access.

3. **Memory tags and base descriptors were conflated.**  
   `f_base_noalias` does not consult the `mtagno` assigned by `assign_mtag`. It examines `Expression` base classes and `VariableLocation`. `Umtag`, `f_set_mtag`, `f_get_mtag`, and `f_find_vreg_mtag` are separate machinery and possible alternate alias producers.

4. **The descriptor singleton does not close principled predicates.**  
   `w13` and `w15` are raw internal fields, partly containing compiler pointers/IDs. Sweeping raw fields cannot disprove a rule based on semantic origin such as “affine induction derived solely from distinct global object B.”

5. **Collateral was counted at the wrong abstraction.**  
   “16 collateral functions” is not necessarily 16 semantic query sites. No reported experiment maps each changed function to singleton query flips and classifies each pointer origin.

### 1.4 Required experiments not previously reported

- Log every `f_base_noalias` call, including existing no-alias returns, with a reason code.
- Log the complete `f_base_in_reg` state before and after each call.
- Trace provenance through `findbaseaddr`, copy propagation, induction discovery, strength reduction, loop transforms, and emission.
- Compare the provenance timeline for bare-pointer control versus winning direct-index and linear-index loops.
- Test state-history opportunities: earlier direct-base seeding, retained `baseregbase`, union widening, and Uunal revocation.
- Perform singleton replay for every candidate alias query and map it to final changed words.
- Classify every causal collateral store pointer by semantic origin.
- Enumerate every producer of an alias relation consumed by `as1`, including ugen’s independent mtag scan.
- Instrument `as1` to identify exactly why the store becomes or cannot become the delay-slot instruction.
- Extend backward dispatch enumeration from RHS roots to complete local statement/CFG traces.
- Prove whole-function, not merely four-word, incompatibility for every surviving trace.

---

## 2. Exact alias decision model

Let:

- `D` = `islda` or `isilda`, carrying `VariableLocation` and size;
- `P` = any non-direct base relevant in C: `isvar`, `isop`, `issvar`, or `dumped`.

For stock C, after validating the readable 7.1 logic against 5.3:

| Base 1 | Base 2 | Stock no-alias result |
|---|---|---|
| `D` | `D` | True iff their `(memtype, blockno, addr, size)` regions do not overlap |
| `D` | `P` | True only if the direct location is `Rmt`; an `Smt` global is may-alias |
| `P` | `D` | Symmetric |
| `P` | `P` | Always may-alias |

The target is `D(Smt:gTrackSelectIDs)` versus `P(isvar:cur)`, hence may-alias.

The complete decision input is larger than the two descriptors:

- both expression classes;
- direct-location `memtype`, `blockno`, address and size;
- `lang`, `nopalias`, `nof77alias`, `use_c_semantics`;
- `pointtoheap` and `aliaswithptr` results;
- base-register colors and encounter order;
- `baseregexpr[]` and `baseregbase[]`;
- `unaltab[][]`, including prior `0`, no-alias `2`, or irreversible may-alias `1`;
- range union when a register receives multiple direct bases;
- the early return when a register already has a base and the incoming base is non-direct;
- GP/SP alias tables;
- whether the pair is ever simultaneously visible to `f_base_in_reg`.

Legitimate source-level flip opportunities are therefore limited to:

1. make both bases stock-visible `D` objects with non-overlapping locations;
2. establish a valid no-alias relation earlier while both bases are direct and retain it;
3. cause a previously direct `baseregbase` to survive a later non-direct access;
4. reach an independent ugen/as1 alias mechanism;
5. avoid the alias route and reach the final sequence through another normalized emission trace.

Qualifiers, casts, raw descriptor values, and shadow provenance alone cannot change the stock verdict.

---

## 3. Ordered protocol

### Step 1 — Qualify the instrumentation

**Instrumentation**

Add env-gated observation only to the statically recompiled 5.3 passes. No observer may change emulated memory layout, allocation order, branch decisions, or output.

**Measure**

- Pristine canonical pass hashes.
- Instrumented, env-unset build of all 196 C objects.
- Env-enabled logging build of the same sources.
- Per-function full-word hashes for all matched functions.
- Whole-ROM SHA-1 and verifier result.

**Decision rule**

Both env-unset and logging-only output must equal the pristine output byte-for-byte.

**Kill criterion**

Any difference invalidates all traces. Fix the observer before continuing.

---

### Step 2 — Establish stable event identities

**Instrumentation**

Assign deterministic IDs from:

`function / basic block / statement ordinal / ucode ordinal / static callsite / node-generation ordinal`.

Do not use host or emulated pointer values as identities.

**Measure**

Stable IDs for:

- target load, store, branch and their base definitions;
- every `f_base_in_reg` call;
- every `f_base_noalias` call;
- every emitted/revoked Uunal;
- every mtag/Ualia event;
- every final instruction and its ugen/as1 origin.

**Decision rule**

The same normalized source compiled twice must produce identical event streams modulo timing.

**Kill criterion**

If IDs drift under identical input, query-index experiments and descriptor comparisons are untrustworthy.

---

### Step 3 — Re-establish causality query by query

**Instrumentation**

At `f_base_noalias`, support diagnostic replay of one stable query result without changing other decisions.

**Measure**

For stock raw source:

- singleton force-noalias for every may-alias query;
- singleton force-may-alias for every stock no-alias query relevant to the target slice;
- emitted Uunal sequence;
- target full-word result;
- all changed functions and words.

**Decision rule**

Identify the minimal causal set \(Q^*\). Expected result: one query is sufficient for 371/371 equality.

**Kill criterion**

If multiple queries are required, or another singleton query reaches the target, the one-query model is false. Expand the backward slice; do not reject H-SOURCE.

---

### Step 4 — Instrument the complete `f_base_in_reg` state machine

**Instrumentation**

At entry, early return, range union, pair iteration, Uunal emission and revocation, log:

- register and ichain ID;
- incoming and retained base IDs;
- semantic base class;
- direct location and size;
- `baseregexpr`, `baseregbase`;
- old/new `unaltab` state;
- reason for skipping or querying;
- `f_base_noalias` return path.

**Measure**

The full state history leading to \(Q^*\) in:

- bare-pointer control;
- raw source;
- winning direct-index loop;
- winning linear-index loop;
- WIP holder;
- mask near-match.

**Decision rule**

Reduce all differences to explicit state transitions, not source spellings.

**Kill criterion**

A purportedly complete model is invalid if an alias relation appears without a logged producer, disappears without revocation, or depends on an unlogged state field.

---

### Step 5 — Build non-invasive semantic provenance

**Instrumentation**

Maintain an external shadow DAG for every address expression and ichain.

Roots:

- `GLOBAL(symbol, offset, extent)`;
- `PARAM(n)`;
- `CALL_RETURN(callee)`;
- `POINTER_LOAD(base, offset)`;
- `STACK`;
- `UNKNOWN`.

Edges:

- copy/CSE;
- affine add/subtract;
- `Uixa`, `Uinc`, `Udec`;
- conversion/type wrapper;
- phi/loop recurrence;
- induction replacement;
- dump/fix;
- strength-reduction replacement.

Instrument every writer of:

- load `unk34`/secondary base;
- `stat->u.store.baseaddr`;
- ichain base fields;
- `baseregbase`;
- mtag fields.

**Measure**

For each relevant pass boundary:

- shadow root set;
- actual stock-visible expression class;
- direct location, if present;
- the exact transformation where the actual class changes;
- whether the origin remains single-symbol affine, becomes call-derived, or becomes unknown.

**Decision rule**

Distinguish:

- semantic provenance retained only in the shadow DAG;
- provenance actually visible to stock `f_base_noalias`;
- alias state retained from an earlier visible base.

**Kill criterion**

The fixed-loop provenance claim is killed if the root is lost somewhere other than the reported strength-reduction transform, or if it remains stock-visible through a history path not previously tested.

---

### Step 6 — Enumerate stock-visible alias preimages

This is decision enumeration, not a loop-family sweep.

**Method**

Statically enumerate every predecessor transition capable of placing \(Q^*\) in a no-alias state:

1. fresh `D/D` query;
2. retained direct base followed by a non-direct early return;
3. prior Uunal that remains active;
4. direct-base range union;
5. register reuse that changes encounter order;
6. GP/SP relation;
7. ugen-generated alias relation;
8. Uunal revocation followed by replacement.

For each transition, use a diagnostic state injection to establish whether it can yield the exact whole-function target. Then derive the C/ucode preconditions from the 5.3 constructors and callsites.

**Measure**

A table:

`transition -> forced result -> target words -> required IR -> C-reachable? -> semantic?`

Collapse source variants that produce identical cfe ucode and identical decision traces.

**Decision rule**

Only transitions whose forced form produces the exact target remain source-search obligations.

**Kill criterion**

The alias route is dead only if every target-producing transition is proved either:

- unreachable from C;
- semantically illegitimate;
- necessarily accompanied by a hard target-word mismatch.

Ten negative loop spellings do not satisfy this criterion.

---

### Step 7 — Prove or refute the bare-induction invariant

**Required theorem**

For every stock trace producing the target’s exact bare-induction address/update instructions, either:

- the store base at `f_base_in_reg` is necessarily `P`, with no retained direct alias state; or
- there exists a stock-visible `D`/retained-state path.

**Method**

Backward-execute:

`target address instructions -> ugen handler -> emitted ucode -> uopt ichain -> findbaseaddr -> induction/strength-reduction constructors`.

Enumerate every static writer and dispatcher capable of constructing the relevant ichain. Quotient copy chains and erased operations rather than enumerating their lengths.

**Decision rule**

- If a `D` or retained-direct path exists, derive canonical natural C topologies from its preconditions.
- If only `P` paths exist, document the code-level invariant and the first unavoidable mismatching word for every `D` alternative.

**Kill criterion**

The stock alias route is closed only by the latter proof. “All tried pointer loops became `P`” is not sufficient.

---

### Step 8 — Enumerate all non-alias routes to the final sequence

Instrument instruction origins through ugen and as1, then backward-enumerate every normalized producer of the four target words.

| Route | Existing coverage | Remaining proof |
|---|---|---|
| Raw load plus alias-authorized store scheduling | Causally demonstrated | Steps 4–7 |
| Holder load plus collapse deferral | RHS wrapper lemma only | Enumerate topology/web/context predecessors |
| Pool load plus copy dissolution | Mask basin examples | Enumerate normalized copy graphs, pairs and allocator states |
| Uopt statement motion/commoning | Several CFG forms swept | Enumerate relevant statement-transform dispatch |
| Branch-head duplication/delay-slot formation | Partially tested | Instrument exact as1 origin and enumerate scheduler arms |
| Ugen mtag/scan-generated noalias | Claimed impossible for `$17` | Enumerate all producer dispatches and register-class preconditions |

**Decision rule**

Every final instruction must have a logged origin. Every origin-producing switch arm must appear in the backward grammar.

**Kill criterion**

H-SOURCE cannot be rejected while any producer arm or normalized predecessor class remains unclassified.

---

### Step 9 — Test only decision-distinct source candidates

For each surviving predecessor class, synthesize one canonical source topology per distinct compiler decision vector. Likely vectors include:

- symbol re-derived yet strength-reduced to identical machine addressing;
- affine global-origin phi or loop recurrence;
- preheader/direct-base seeding retained across the loop;
- same-register reuse preserving direct alias state;
- pointer-to-array or subobject topology whose `findbaseaddr` remains direct;
- statement/CFG topology selecting a non-alias producer route.

**Measure**

- cfe ucode hash;
- provenance trace;
- decision-vector hash;
- full-word function result.

**Decision rule**

Different syntax with the same normalized trace is one test, not a new family.

**Kill criterion**

A decision vector is killed by a C-unreachability proof or unavoidable hard-word contradiction, not by several negative spellings.

---

### Step 10 — Acceptance gate

For any full-word-zero candidate:

1. review legitimacy under §6;
2. rebuild from a clean tree using the stock canonical passes;
3. compare all 226 matched `menu.c` functions;
4. compare every currently matched ROM function;
5. run the project’s normal whole-ROM build;
6. require `Verify OK` and exact retail SHA-1.

A loose mnemonic score is never an acceptance result.

---

## 4. Provenance-opportunity measurement for collateral sites

### 4.1 Resolve the unit first

The reported 12/16 values are changed-function counts under `gsym0`/`k31`, not proven semantic-site counts.

For every granted query:

1. replay it alone;
2. determine whether it changes final bytes;
3. group repeated executions of the same semantic load/store pair;
4. record the exact affected function and words.

Let \(N\) be the number of distinct causal query sites.

### 4.2 Classification

For the store side of each site, classify the shadow DAG as:

- **G — single-symbol affine induction:** exactly one `GLOBAL` root; only copies, affine arithmetic, phi and induction recurrence; no parameter, call, pointer load or unknown root.
- **C — call-derived:** `CALL_RETURN`, or a pointer field loaded from a call-derived object, such as `get_settings()->courseFlagsPtr`.
- **P — parameter-derived.**
- **M — mixed:** multiple incompatible roots.
- **U — unknown/instrumentation gap.**

For G sites also record:

- root symbol;
- subobject extent;
- load root symbol;
- whether the two declared objects are genuinely disjoint;
- actual stock-visible base class at the query;
- whether singleton grant changes output.

Manual source inspection must validate every automatic classification.

### 4.3 Interpretation

| Count/result | Implication |
|---|---|
| Target is the only G site; all collateral is C/P/M | A principled global-origin rule could isolate the target without descriptor fingerprinting. The simple collateral theorem does not kill a hidden toolchain rule. H-SOURCE also remains live if stock can be made to retain that origin visibly. |
| Several G sites, but only target is output-sensitive | A principled rule may still be zero-collateral in emitted bytes. Evaluate the rule over all opportunities, not only changed functions. |
| Several G sites are output-sensitive and retail-matched elsewhere | A uniform “single-symbol origin” toolchain rule is falsified. Any refinement must use a pre-registered semantic property, not raw descriptor fields. |
| All or nearly all sites are G with equivalent disjoint roots | Provenance does not explain target uniqueness. A simple principled toolchain rule dies; source-specific topology or a site-specific compiler behavior remains. |
| Target is not G | The assumed `gTrackSelectRenderDetails` provenance story is wrong or the shadow tracker is incomplete. Stop and repair the model. |
| Any U sites remain | No closure claim is allowed. |

The decisive comparison is not merely G versus C. It is:

`semantic opportunity × stock-visible descriptor × output sensitivity`.

---

## 5. Closure argument

No finite set of dynamic source experiments can prove H-SOURCE false. The required proof is a finite compiler-preimage argument.

Define:

\[
C \xrightarrow{\mathrm{cfe}} N
\xrightarrow{\mathrm{uopt}} O
\xrightarrow{\mathrm{ugen}} G
\xrightarrow{\mathrm{as1}} T
\]

where \(T\) is the exact 371-word target.

Arbitrary dead syntax, identity expressions and copy-chain length are quotiented by the normalized cfe/uopt state \(N/O\). The proof obligations are:

1. **Complete final-producer enumeration.**  
   Enumerate every ugen/as1 dispatch trace capable of producing the exact target function, not only the four-word window.

2. **Complete alias-state model.**  
   Enumerate the truth table and state transitions of `f_base_in_reg`, `f_base_noalias`, Uunal, mtag-derived aliases and as1 consumption.

3. **Complete provenance-writer inventory.**  
   Account for every static constructor and mutation of the relevant base expressions and alias state.

4. **C-reachability classification.**  
   For every normalized target-producing trace, prove one of:

   - unreachable from cfe-generated C ucode;
   - semantically illegitimate;
   - necessarily emits a non-target hard word elsewhere.

5. **No uncovered producer.**  
   Instruction-origin traces and static dispatch review must agree. Dynamic coverage validates the model but cannot substitute for static enumeration.

Then:

\[
H\text{-SOURCE is false}
\iff
\mathrm{ReachableLegitimateC}(N) \cap
\mathrm{Preimage}_{uopt,ugen,as1}(T)
= \varnothing
\]

This is immune to the racer failure because an untried topology matters only if it induces a previously unenumerated normalized decision trace. If the decision-trace preimage is complete, syntax-family omissions are irrelevant.

If any producer, state transition, provenance writer, or C-reachability case remains unresolved, the correct verdict is **open**, not false.

---

## Execution addendum — 2026-07-24 construction session

This plan has now been executed through its highest-value source-construction
predecessors. Read `SESSION_HANDOFF_2026-07-24.md` and
`report_construction_endgame.md` before scheduling more work.

### Steps 6–7: retained-direct predecessors

The review's missing predecessor classes were tested:

- redundant direct address assignment plus continuous pointer induction;
- direct memory access through `g[cur-g]`;
- equivalent byte-pointer round trip;
- direct store plus an equal pointer assignment, providing an explicit
  coalescing opportunity; and
- flat continuous direct induction with a source-visible outer row counter.

Address construction alone creates no `f_base_in_reg` event. Real direct
memory events retain target-visible address work. Round trips do not cancel,
and the equal direct/pointer webs do not coalesce or transfer retained alias
state. Flat direct induction can reach the exact local no-alias window, which
corrects the earlier overbroad “direct always +7” claim, but it necessarily
changes the target's nested-loop induction and register-allocation graph.

Verdict for the listed static predecessors: empty. This is not a proof over
every possible object topology.

### SOFT-A: independent 32-bit/pair construction

The real 32-bit index and semantically live pair activity were separated
across call-boundary, carrier, entry-pointer, pre/post-conversion, and
shift/subtract/shift-stage families. The strongest new normalized state is a
371-word FW3 basin at indices `(106,107,109)`. Multiple source families
converge on that trace; the remaining live-scalar handoff cannot free and
recover `t3` without a target-visible copy or renewed pair parity.

Verdict for the enumerated producer/handoff predecessor classes: empty.

### Step 8: final producer

The 152-opcode fixed-frame dispatch enumeration remains decisive. The sole
zero-real-instruction defer root is an identity integer `Ucvt` removed by
`cfe`. Truthful `const`, block scope, and parameter reuse do not change
collapse. The flat-loop local success is produced by alias ordering, not by a
new non-alias producer.

Verdict for the target-compatible named-holder frame: empty. Arbitrary CFG
topology is not finitely enumerated, so H-SOURCE remains logically open rather
than proved false.

### Boundary inputs

Supported pragmas/qualifiers, hidden driver alias flags, and global linkage
were checked. Stock `cfe` rejects or ignores the source directives, the driver
flag reaches only `as1`, and `static` linkage changes relocation addends only.

### Stop decision

The plan's intended purpose—replace spelling sweeps with state/predecessor
analysis—has been achieved. Further broad source search is not recommended.
Reopen only for a proposal that identifies a new normalized producer/state and
explains why its enabling operation is already present in the 371-word target,
or for new historical build evidence.

---

## 6. Legitimate match versus hack

A candidate is legitimate only if all conditions hold:

- uses the unmodified canonical cfe/uopt/ugen/as1 binaries;
- uses accurate declarations, storage classes and mutability;
- preserves calls, writes, reads and observable ordering for all reachable game states;
- introduces no undefined behavior, false `restrict`, false `const`, invalid aliasing, out-of-bounds pointer construction, or unsequenced side effects;
- its topology expresses an algorithmic operation or ordinary loop structure;
- it contains no operation whose only purpose is compiler-state manipulation;
- it passes the whole-ROM gate.

Automatic hack classifications:

- descriptor-, query-index-, function- or address-keyed compiler behavior;
- any forced alias/collapse decision;
- dead temp burners;
- redundant 64-bit masks, conversion chains or identities used solely to rotate allocation;
- `volatile`, pragmas or qualifiers unsupported by real semantics;
- modifying unrelated matched functions to compensate for target differences;
- inline assembly or emitted-data tricks;
- reliance on undefined or implementation-accidental behavior without source evidence.

Compiler sensitivity alone is not a hack. An unusual loop or assignment topology is acceptable when it has a coherent source-level purpose, correct semantics, and reaches the target through stock decisions.
