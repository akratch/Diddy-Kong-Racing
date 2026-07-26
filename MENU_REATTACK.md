# func_8008FF1C re-attack plan
(untracked working notes, not for any PR)

## 1. The problem, reduced to its final form

The committed WIP compiles byte-identical to the target except two instructions:

```
ours:    lh v1,0(s1)   ...   beq v1,at,<else>
target:  lh t2,0(s1)   ...   beq t2,at,<else>
```

Around the divergence, the target's instruction stream is:

```
jal level_world_id
jal level_name          # result in v0
lh  t2, 0(s1)           # load gTrackSelectIDs[trackY][trackX]
li  at, -1
beq t2, at, <else>
 sw v0, 0(s0)           # DELAY SLOT: cur->hubName = levelName
```

Two facts about this sequence, each independently fatal to every shape we tried:

F1. The compared value sits in t2, a ugen pool temp. Named C variables at this
    site always color to v1 (er-scan v0,v1,a0..; only v0 is forbidden). Proven:
    a named holder can never produce t2 (law L6). So the target's condition
    consumes the raw expression, not a variable.

F2. The load is emitted ABOVE the hubName store, inside the span of the
    statement that produced v0. Raw-expression consumption in our compiles
    always emits the load lazily at the branch statement, i.e. AFTER the store
    (store statement precedes the if in source). For the store to land in the
    delay slot, the pre-as1 order must be [lh][li][sw][beq].

Everything else in the function is solved. The whole question is: what makes
the compiler order the load above the store?

## 2. What is proven dead (do not revisit)

- Named/shadow/multi-use variable holders for the compared value: always v1.
- Forbidding v1..t1 with dead webs to force t2 onto a colored web: dead webs
  are copy-propagated away; survivors inflate the load web itself. Closed.
- 64-bit mask tricks: buy t2 but create a live ll pair that displaces the
  index temps one block later. No early zero-code pair is constructible
  (dead ll ANDs fold before pair allocation). Closed this session.
- as1 behavior (verified with synthetic tests): fills delay slots only from
  the immediately preceding instruction or by branch-target head duplication;
  never merges duplicated branch heads; never reorders a load across a store
  WITHOUT a ugen-emitted .noalias covering the pair.
- ugen in our shapes emits .noalias(load, $sp) but never .noalias(load, store)
  because the store goes through the loop-carried cur++ pointer, whose symbol
  provenance is lost across the back edge. No C respelling of the store through
  copies/casts restores provenance. Closed.
- Both-branch hubName stores under the OLD (named-levelName) shapes: produced
  per-branch stores plus a v1 move. as1 will not merge them. (But see A3: the
  composite with the raw-load shape and uopt-level store motion is NOT closed.)

## 3. The unexplained fact, stated honestly

Under our current law set, the target sequence should be impossible: raw
consumption gives late loads, and nothing we found hoists the load. Yet the
target exists, its 226 sibling functions in menu.c match byte-exact under this
exact compiler, and menu.c is one TU (so a per-file toolchain difference would
have collateral). Conclusion: our law set is incomplete. There is a mechanism
in uopt or ugen that we have not triggered, not a different compiler.

Three candidate mechanisms, in decreasing prior:

A1. ugen DOES emit .noalias(load, store) under conditions we have not produced.
    We inferred emission rules from observed output only. We have never read
    the emission logic itself. The banjo-kazooie repo vendors the recomp
    ugen source WITH symbol names (ido/ido5.3_recomp/ugen_c.c, ~2.7 MB); our
    own recomp generates the same file unnamed. Reading the noalias emission
    path directly will enumerate the exact trigger conditions: which base
    kinds (symbol vs pointer), which mtag classes, what defeats it. This
    replaces guesswork with the actual rule. If any reachable C shape
    satisfies the rule, we win via as1 reordering.

A2. uopt statement-level motion. uopt runs passes we have never deliberately
    exercised on this function: partial redundancy elimination (the numinsert
    counter), redundant store removal (numrdstr/numlrdstr), and whatever
    uopttail.c/uoptppss.c do (tail merging, store sinking or hoisting). If the
    original source put the hubName store in a position where one of these
    passes moved or commoned it (for example identical stores at the head of
    both branches hoisted into the predecessor after the condition
    evaluation), the resulting ucode statement order is [cond][store], and
    ugen emits [lh][li][sw][beq] naturally with the load as a pool temp — t2
    with no tricks at all. This would explain F1 and F2 with one stroke.
    Note the WIP's own oddities (the dead temp=(temp=...) and the // ????
    comment) smell like decompiled leftovers of a differently-structured
    original around exactly this spot.

A3. uopt alias classes (mtag). The load is from a global symbol array; the
    store is through a struct pointer. If uopt's memory tagging can prove
    them disjoint under some declaration shape (array-of-struct indexed
    store, const qualification if the symbol actually lives in rodata,
    distinct base types), uopt itself may schedule the load earlier. We
    have never read uoptmtag.c or checked which section gTrackSelectIDs
    actually occupies in the ROM.

## 4. The plan

Step 1 (read the rules, no more guessing):
  a. Read ugen's .noalias emission logic in the symbol-named ugen_c.c from
     the banjo vendored tree. Deliverable: the exact predicate.
  b. Read uoptmtag.c (alias classes) and the store-motion passes
     (uoptscm.c, uopttail.c, uoptppss.c, redundant-store code) in
     n64decomp/ido. Deliverable: which passes can reorder or common stores,
     and their trigger conditions.

Step 2 (targeted experiments, trace-verified):
  c. The A2 composite, never tried in the right combination: raw-load
     condition (v_g2 shape) + cur->hubName = levelName as the FIRST statement
     of BOTH branches, watching the uopt trace counters (numrdstr, numinsert)
     and the ucode statement order. Variants: identical store first in both
     branches; store in else only (checking whether the if-path store gets
     supplied by slot execution); ternary restructure of trackName.
  d. Check the ROM section of gTrackSelectIDs. If rodata: declare it const
     (legitimate) and re-test alias behavior. Also try the indexed-store form
     for the ONE hubName store with every other cur-> access untouched,
     verifying frame and emission neutrality in the listing.
  e. Construct partial redundancy of the load (an occurrence on one path
     before the store) to force a PRE insertion, and see where the inserted
     evaluation lands and in what register class.

Step 3: whichever mechanism shows movement, iterate with the listing oracle
     (sview) at every step. Success is DIFFS 0 in try.py, then main-repo
     verification.

Kill criteria: if Step 1 shows the .noalias predicate is unsatisfiable from C
AND the store-motion passes cannot produce [cond][store] order AND mtag cannot
separate the accesses, then the wall is real, the function is another
"unreproduced source or unmodeled behavior" case, and we document it with the
same rigor as racer. But we do not declare that until the rules have been read
rather than inferred.

## 5. Plan execution result (2026-07-23)

The rule-reading and targeted experiments above were completed. The original
plan text is retained to show the reasoning path, but it is no longer an open
checklist.

### Compiler-source conclusions

- A direct global-array load versus the loop-carried C pointer store reaches
  the conservative pointer-alias path.
- The `cur` store has the catch-all memory tag; its original
  `gTrackSelectRenderDetails` symbol provenance is not available in the form
  needed by ugen after the loop back edge.
- ugen therefore does not emit a usable `.noalias(load, store)` pair. The
  observed load-versus-stack pair cannot authorize the required move.
- as1 cannot produce the target order without that relation.
- The examined uopt store-motion, redundant-store, and tail/commoning paths do
  not hoist/common this ordinary indirect store into the predecessor.
- `gTrackSelectIDs` is writable and assigned in this translation unit. It is
  not a legitimate `const`/rodata lever.

### Targeted experiment conclusions

- Raw condition plus `hubName` as the first statement in both branches:
  branch-local stores survive and a `v1` move is introduced. No common hoist.
- Store in only the false branch preserves the target `t2` allocation but
  moves the store from instruction 105 to 139 and is wrong on the true path.
- Store in only the true branch produces a broad mismatch.
- Ternary/raw-value variants retain `t2` in some forms but add real branches
  or reloads.
- Direct indexed stores, local const/volatile casts, restrict/ivdep, explicit
  noalias text, assignment/comma/identity forms, and partial-value
  restructures do not bridge the load/store order.
- Removing the historical `temp = (temp = ...)` is not neutral: it changes the
  later allocator phase and causes roughly 134 raw differences.

The kill criteria are therefore met for the mechanisms proposed in this
document. `DIFFS: 2` is the honest hard floor under the understood compiler
model.

This does not prove that no original C source exists. It means another attack
must begin with a genuinely new mechanism that explains both target facts at
once: raw pool-temp allocation and evaluation of that raw load before the one
pointer store. More spelling permutations inside the closed families are not
useful.

See `REATTACK_HANDOFF.md` for the combined menu/racer handoff, exact oracle
paths, cleanup rules, and PR-readiness status.

## 6. Session 4 (2026-07-23 night): the ugen allocator model, and why every
## basin is walled

This session moved the investigation from black-box spelling search to a
mechanistic account read directly from pre-as1 listings (`cc -K`, tooling in
`<current scratchpad>/menu/klist.sh`). The result is a complete explanation of
all three known near-miss basins and a set of impossibility arguments that
close them individually. Nothing here found a match; the two-instruction floor
stands, but it now stands on an understood mechanism instead of an unexplained
observation.

### 6.1 The community ll-mask basin, finally read

The decomp.me L6qKV shape (`menuwork/v_scratch.txt`, DIFFS: 2) works like
this in the pre-as1 listing:

```
lh   $10, 0($17)      # the load IS a pool temp — t2 achieved
move $13, $10         # ll-extension lo   (pair 12,13)
sra  $12, $10, 31     # ll-extension hi — dead, DCE'd by as1
move $3, $13          # pad's home v1 — every copy as1-dissolvable
...second mask: pair (14,15), home v1 again...
sw   $2, 0($16)       # hubName store
beq  $3, -1, else     # as1 chains v1←$13←$10 → beq $10 = beq t2 ✓
```

The masks beat F1/F2 because the branch operand chains through
as1-dissolvable copies back to the pool lh, which was emitted BEFORE the
store (the pad statement precedes the store statement in source). This is the
only found C-level mechanism that yields a pool-temp lh in the right order,
and it survives uopt because the chain feeds a live branch (register-only
dead chains are DCE'd by uopt before ugen — verified, see 6.4).

### 6.2 The allocator model (read from listings, verified across 20+ shapes)

- ugen's expression temps come from an ordered pool over
  {$8..$15,$24,$25} that behaves as a cyclic pointer with an ordered free
  list (`f_add_to_free_list` / `f_move_to_end_gp_list` in the named recomp
  `ugen.c`, ido-recomp-pub/build/5.3/).
- 64-bit values grab even-aligned PAIRS from a separate monotonic pair
  cycle (12,13)→(14,15)→(24,25)→(8,9)→(10,11); a pair-align skip from an odd
  pointer queues the skipped odd reg (the index mul always lands $11 via
  this queue).
- 64-bit lo-adds write their result IN PLACE into the value chain's origin
  register; only 32-bit adds get fresh dests. as1 then forward-substitutes
  op-then-copy, so an ll sum can never present a fresh dest downstream.
- uopt-level CSE carriers (values shared between the trackName index and the
  else-if index) occupy pool registers across the trophies block whenever the
  shared node is below the address root; only the full-address CSE is carried
  in a colored web (s1) and is free.

### 6.3 The three-wall triangle (each wall independently fatal)

The target needs simultaneously: (a) pool lh $10 before the store,
(b) bb21 = mul $11 / addu $12 fresh / lw $13, (c) trophies block
$14,$15,$24,$25,$8,$9 with `and`→$8.

- Plain index + no masks (`base` family): (b),(c) perfect; (a) fails — the
  load collapses into the named holder's colored web → lh v1. DIFFS 2.
- Masks + plain index (`v_plain`): (a) holds, but bb20's mask pairs leave the
  pool pointer at an even slot entering bb21 — the add can never land on $12
  (parity argument; mask counts 1–6 all tested). DIFFS 119+.
- Masks + ll-sum index (`v_scratch`): (a),(c) hold; the ll lo-add in-places
  ($11) and as1 forward-subs the narrowing move — addu t3 not t4. DIFFS 2.
- Masks + s32-cast index (`v_zz1`, 3 masks): (a),(b) hold; the cast creates
  sub-CSE carriers (mul $11, cvt $10, ext pair (8,9)) that live into the
  trophies block, and the trophies `and` rebinds to the freed $11 instead of
  taking the pointer reg $8. DIFFS 56. The rebind is invariant under every C
  spelling that value-numbers to the same ucode (pad2/temp sum carriers,
  reassignment in the else-if, pure cast chains, all commutations — all
  produce byte-identical emissions).

Every corner of the triangle is blocked by a different ugen invariant, and
the levers that fix one corner structurally violate another.

### 6.4 New negative families (session 4; do not retry)

1. `goto L; L:;` zero-code block splitters (any placement): uopt/ugen
   renumbering shifts allocation GLOBALLY — diffs from line 35, DIFFS 340.
2. Mask-count sweep with cast index (m=1..6): 128/128/56/128/133/133 —
   no mask count aligns both bb21 and the trophies block.
3. Zero-extension tricks (`(u32)`, `& 0xFFFFFFFF`) to kill the pair's hi:
   the pair is allocated regardless. 56/128 unchanged.
4. Variable-free cast chains `(s32)(long long)(trackY*6)` in both sites:
   emission identical to v_zz1 — the carriers are ucode-level, not
   C-variable-level. 56.
5. Dead-store carriers (`pad2 = <sum>` in index, else-if reads `pad2`):
   uopt copy-propagates them away; emission identical. 56.
6. Trophies-side and index-side commutations/spellings (`3 & x`, `2*trackY`,
   `trackY<<1`, `3 == x`, `6*trackY`, `trackX + cast`): cfe canonicalizes;
   all 56.
7. Named `long long` holder (`new_var = load; if ((s32)new_var != -1)`):
   ll locals home to STACK templocs — sw/lw pairs appear. 262.
8. Chain-assign holders (`pad2 = (pad2 = load)` s32, incl. in-condition and
   3-deep): collapse completely to the v1 basin (the WIP's burn depends on
   `temp` being s16). 133–144.
9. Dead burner statements to pop the free-list head before the trophies
   `and` (s16 chain-assigns of register values, `(s32)(new_var & M)` cvt
   forms, with/without mask protection, three positions): uopt DCEs every
   register-derived dead statement before ugen; only memory reads survive
   (etable protection), and those either collapse into webs or emit real
   loads. All 56 unchanged.
10. Codex's `cond-*-comma` identity forms re-measured with windows: the
    identity folds and the branch IS `beq t2` on the raw pool temp, but uopt
    hoists the embedded store istr ahead of the condition — [sw][lh] order,
    raw 39. Expression-embedded stores can never produce [lh][sw].

A parallel score ledger of all 215 historical variants was built
(`<current scratchpad>/menu/ledger.json` + `score_all.py`): exactly two
DIFFS-2 basins exist (first_diff=102 v1-basin; first_diff=110 addu-basin),
33 variants reach one of them, and nothing scores 3–37.

### 6.5 Honest conclusion

The floor is still DIFFS: 2, now explained: the shipped bytes require an
expression-temp assignment (`and`→$8 with a pool lh and a fresh $12 add)
that this ugen build's free-list/pair-cycle/in-place conventions cannot
produce from any C spelling of this statement sequence that we have found —
across four sessions, 500+ variants, 58k permuter iterations, and nine new
mechanism families. This mirrors the racer verdict: genuine IDO output whose
allocation state is not reachable from the reconstructed source shape under
the canonical recomp binaries, with the remaining unknown now localized to
ugen's free-list ordering rather than uopt's coloring.

### 6.6 The free-queue proof (instrumented ugen, same session)

Avenue (i) was executed immediately: the recomp `ugen.c`
(ido-recomp-pub/build/5.3) was instrumented with env-gated logging
(`UGEN_FLTRACE=1`) on `f_get_free_reg` (wrapped to log its result),
`f_add_to_free_list`, `f_remove_from_free_list`, `f_move_to_end_gp_list`,
and `f_free_reg`. The instrumented toolchain is byte-identical without the
env var (verified against the repo toolchain's object). Traces for base vs
zz1 (`fltrace2_*.txt` in the current session scratchpad `menu/`) show:

- The expression-temp pool is a FIFO free-queue over {$8..$15,$24,$25}:
  `GET` pops the head; a value's death refrees its reg to the TAIL. The
  initial queue order is [14,15,24,25,8,9,10,11,12,13].
- base's downstream is the unique queue fixed point:
  bb21 entry queue = [10,11,12,13 | 14,15,24,25,8,9]; the WIP's dead s16
  burner pops/refrees $10 BEFORE the mul pops $11, which is exactly what
  makes the later else-if pop [10,11,12,13] in target order; the trophies
  block pops [14,15,24,25,8,9] because 8/9's last frees are ancient (the
  pre-call address computation). Every downstream register of the target
  follows mechanically.
- The target bytes = this same fixed point with the branch load itself
  serving as the $10 pop (a pool lh), which requires a collapse-blocker
  that costs NO other pool activity in bb20.
- The cast family's contradiction is now a one-mechanism proof: the ll-ext
  pair grab of (8,9) in bb21 is REQUIRED to make the cvt/add/reload pop
  10/12/13 (without it they pop 8/9/10 — the 2-mask cast measurement), but
  that same grab refreshes 8 in the queue AFTER 11, so the trophies `and`
  (the 5th-oldest pop) necessarily lands on $11 instead of $8. Core alignment and
  trophies alignment draw from the same queue state in opposite directions.
- The `cond-seq` comma forms (`(temp = load, cur->hubName = levelName,
  temp != -1)`) produce the EXACT target order [lh][li][beq][sw-in-slot]
  with a mnemonic-perfect stream (reg-shape metric 0) — F2 (istr ordering)
  is fully solvable in C. The residual is purely F1: the load web-collapses
  into the named holder (v1) and the burner rotation is absent (raw 134).

So the entire two-instruction floor reduces to one question: does ANY C
construct make ugen emit the branch-feeding lh as a pool temp without
burning other pool slots or emitting instructions? Every known blocker
fails one leg: ll masks burn pairs (parity + queue poison), s16 assignment
chains emit live sll/sra (or, when dead, don't feed the branch), `long
long` holders home to stack templocs, register-only dead chains are DCE'd
by uopt before ugen, and s32 identities are folded by cfe. Under this ugen
binary the answer appears to be no.

Remaining avenue: (ii) a ugen point variant in Rare's toolchain (the
compiler hunt discriminated uopt/as1/cfe; ugen only partially). A variant
whose ilod-into-web collapse triggers one statement later — or whose free
queue seeds differently — would produce the target from the natural
`selectedTrack` source with no tricks at all, which is also the most
plausible original-source story: the shipped code reads like plain C
(`x = arr[i][j]; cur->hubName = name; if (x != -1)`) compiled by a ugen
whose collapse/queue behavior differed microscopically from the canonical
recomp binary.

## 7. Session 5 (2026-07-23, multi-agent): the ugen-variant theory run to
## ground — confirmed as an oracle, falsified as a real compiler

Three independent legs (full reports: `report_oracle.md`, `report_hunt.md`
in the session-84e018d6 scratchpad `menu/`; artifacts under `menu/oracle/`
and `menu/ugenhunt/`).

### 7.1 Oracle leg: DIFFS 0 achieved from the natural source

The recomp ugen was patched (env-gated `UGEN_NOCOLLAPSE`, byte-identical
when unset) at the single decision point where `f_eval`'s STR-to-register
handler passes the colored web register down as the destination hint for a
leaf ILOD (recomp label L42ec60). Dropping the hint for the site's exact
signature (signed 16-bit ILOD stored to a $3/v1-colored web) makes the
load take a pool temp from the free queue — and the plain natural source

```c
selectedTrack = gTrackSelectIDs[trackY][trackX];
cur->hubName = levelName;
if (selectedTrack != -1) { ... }
```

compiles to the target EXACTLY: DIFFS 0, 371/371 instructions (stock
score for the same source: 133). The §6.6 queue-fixed-point prediction is
confirmed end to end: `lh $10; move $3,$10 (as1-dissolved); sw; beq` and
the entire downstream register pattern falls out mechanically. The
committed WIP's 2-diff residue is therefore an allocation-phase artifact
of one binary decision in ugen, not a source-shape problem.

Collateral of the patch across the TU (per-function word diff, 226
functions): narrowest gate 12 changed (11 besides func_8008FF1C); signed-
16-only gate 28; all-16-bit 35; all-ILOD 113. Broad modes also disturb
call-argument staging (uopt stages args through the same STR-to-register
path), rotating the queue globally.

### 7.2 Hunt leg: no real ugen variant exists to be found here

Complete on-disk inventory (all IDO/MIPSpro trees, SGI CD images, patch
archives): exactly ONE 5.3 ugen binary exists (md5 9fcff937…, identical in
every 5.3-labelled tree — no CD-vs-community split like as1's). The full
manifests of both SGI patch CDs (398 patches) show NO patch ever shipped a
ugen (260=as1, 1078=cfe, 1260=uopt; patchSG0001118 absent from both CDs).
Version axis, tested by recomping each distinct ugen and swapping it into
the reference toolchain (fidelity-gated): IDO 5.1 and 5.2 ugen produce
byte-identical func_8008FF1C output to 5.3 (and differ from 5.3 in 4 other
matched functions — excluded as Rare's toolchain); IDO 6.0/7.1/7.4.4
collapse MORE (they dissolve even the WIP's double-assign into the natural
basin) and change 52 matched functions. The lineage never moves toward
less collapse. IDO 5.1's ugen was made runnable for the first time
(relocated-libc recomp; stock recomp asserts on its low data segment).

### 7.3 Falsification leg: no uniform variant is ROM-consistent

Source-independent argument: under any ugen whose rule defers collapse for
a class containing our site, a direct `lh <webreg>` is unproducible for
sites in that class from ANY source — the deferral path emits `lh $pool`,
and as1 copy dissolution renames uses toward the pool register, never
into the web register. Scan of the matched menu.c object: 67 sites where a
signed lh lands directly in a colored web register with non-adjacent
later uses; 20 of them have dest exactly v1 (e.g. draw_menu_elements
0x29a4, menu_title_screen_loop 0x41d8, savemenu_render_element 0x5b94).
Each one falsifies every gate up to and including the narrowest
"signed-16 into v1" rule. Therefore NO uniform collapse-rule variant of
ugen can produce the shipped ROM, regardless of what sources are assumed
for the other functions.

### 7.4 Final verdict and surviving probability mass

- The target bytes ARE the natural source under a one-bit-different
  collapse decision (proven, oracle).
- That decision cannot be a uniform behavior of any real ugen consistent
  with the rest of the ROM (proven, 7.3), and no alternative 5.3-lineage
  binary exists on this machine or in the SGI patch record (proven, 7.2).
- Stock ugen collapses the natural source, and four sessions established
  that every C-level collapse blocker costs visible state (§6).

What survives, in decreasing order of prior:
1. A CONTEXT-DEPENDENT rule in some unobtained 5.3-lineage ugen build
   (pressed "IRIS Development Option 5.3" Dec-1994 CD vs the community
   "IDO 5.3 with C++" image) that distinguishes our site from the 67 —
   e.g. keyed on the web's next use lying beyond a potentially-aliasing
   istr (a correctness-flavored deferral). Unfalsifiable without the
   binary; the as1 precedent (community as1 = patchSG0001118, CD as1
   differs) keeps this alive.
2. An unconceived source construct under stock behavior (the perennial
   residual; every family C offers has been mechanistically closed).
3. Build-process oddity (hand-patched object, interrupted build) — no
   positive evidence, kept only for completeness; the byte pattern is
   fully compiler-idiomatic.

PR guidance unchanged: the committed WIP at DIFFS: 2 remains the honest
ceiling. The natural source + oracle result should NOT be committed (it
does not compile to the ROM under the project toolchain), but is the
recommended community-facing explanation of where the last two
instructions come from.

## 8. Construction-endgame update (2026-07-24)

The later skeptical handoff correctly reopened three overbroad closures. The
follow-up construction session is now complete and intentionally paused.

- Retained-direct predecessors were tested at the missing points: redundant
  address seed, direct pointer-difference and byte-pointer round trips, and a
  real direct store followed by an equal pointer assignment. None transfers
  no-alias state without target-visible address work.
- A flat continuous direct induction does reach the exact local target window,
  disproving the universal “direct always +7” wording. It fails structurally:
  restoring the target outer row graph promotes `trackY+1` into a different
  recurrence, while blocking that promotion emits real instructions.
- The real 32-bit index was separated from semantically live pair activity
  across producer, call, carrier, entry-pointer, and arithmetic-stage
  families. The strongest normalized result is 371 words and three
  differences at `(106,107,109)`.
- `const`, scope, parameter-holder, alias pragma/qualifier, hidden-driver-flag,
  and global-linkage boundaries do not change the deciding state.

No stock match was found. The exact scores and audit scope are in
`menu_research/report_construction_endgame.md`; the cautious cumulative
record is `menu_research/POSTMORTEM.md`; the next-session entry point is
`menu_research/SESSION_HANDOFF_2026-07-24.md`.

Correction to the language above: “every C-level blocker” and “honest ceiling”
are practical mechanism-level conclusions, not theorems over every C program.
The current stop is justified because new spellings have ceased producing new
normalized compiler states. Reopen only for a predicted new state or new
historical evidence.
