# func_8008FF1C (menu.c): Research Findings

Status date: 2026-07-24. Untracked research document; not for any PR.
This is the synthesis document for the multi-session campaign to match the
last menu.c function in the DKR decompilation. Detailed working notes live
in `MENU_REATTACK.md` (§1–§7) and `CODEX_REATTACK_LOG.md`; durable copies
of every cited artifact are archived in `menu_research/` (see §7). The
parallel racer campaign is covered by `RACER_REATTACK.md` and
`REATTACK_HANDOFF.md` and is referenced here only where it informs the
menu conclusions.

Final construction status: this chronological synthesis contains emphatic
claims that were later narrowed by skeptical review. The cautious terminal
record is `menu_research/POSTMORTEM.md`; the next-session entry point is
`menu_research/SESSION_HANDOFF_2026-07-24.md`. Section 16 below records the
last construction session and supersedes earlier “proven ceiling,”
“near-certain original source,” and still-open action language.

## 1. Executive summary

`func_8008FF1C` (the track-selection render/update function) compiles
byte-identically to the shipped US v80 ROM except **two instructions**:

```asm
ours:    lh v1,0(s1)   ...   beq v1,at,<else>
target:  lh t2,0(s1)   ...   beq t2,at,<else>
```

This campaign did not close those two instructions. It did something
arguably more valuable: it isolated two compiler decisions sufficient to
reproduce the target, demonstrated diagnostic compiler controls that produce
the exact 371-instruction stream from plausible plain C, and characterized why
the stock compiler's principal source constructions miss. Those controls do
not prove the historical source or compiler. The function's honest stock state
remains the committed WIP at DIFFS 2, now with a strong causal model and an
explicit uncertainty ledger.

## 2. The compiler model we established (new results)

All of the following was derived from pre-assembly listings (`cc -K`) and
a byte-fidelity-verified instrumented build of the recompiled IDO 5.3
`ugen`, and verified predictively. Evidence: `MENU_REATTACK.md` §6.1–§6.6,
traces in `menu_research/traces/`, listings tooling in
`menu_research/tools/`.

1. **The expression-temp pool is a FIFO free-queue** over registers
   {$8..$15,$24,$25} (the t-registers), seeded
   `[14,15,24,25,8,9,10,11,12,13]`. Every allocation pops the head; a
   value's death re-appends its register to the tail. Observed directly
   via env-gated logging (`UGEN_FLTRACE`) of `f_get_free_reg` /
   `f_add_to_free_list` / `f_remove_from_free_list` /
   `f_move_to_end_gp_list` in the recomp `ugen.c`
   (patch: `menu_research/ugen_instrumentation_and_nocollapse.patch`;
   raw event streams: `menu_research/traces/fltrace2_{base,zz1}.txt`).
2. **64-bit values grab even-aligned register pairs** from a separate
   monotonic pair cycle (12,13)→(14,15)→(24,25)→(8,9)→(10,11); an
   align-skip from an odd pointer queues the skipped odd register (this is
   why the index `mul` in this function always lands in $11).
3. **64-bit lo-adds write their result in place** into the value chain's
   origin register; only 32-bit adds receive fresh destinations. The
   assembler (`as1`) then forward-substitutes op-then-copy sequences, so a
   64-bit sum can never present a fresh destination register downstream.
4. **The ilod→web "collapse"**: when a ucode STR stores a leaf memory load
   into a register-resident (colored) variable, `ugen`'s statement handler
   (`f_eval`, recomp label L42ec60) passes the variable's register down as
   the destination hint, and the load lands directly in it — no queue pop
   occurs. This single decision is the entire remaining mismatch (§3).
5. **uopt DCEs register-derived dead statements before ugen ever runs**;
   only memory reads survive (etable read protection). This is why the
   committed WIP's "dead" `temp = (temp = load)` works: `temp` is
   declared **s16**, the narrowing chain survives to ugen, burns exactly
   one queue slot ($10), and is then deleted by as1 — an allocation
   side-effect with zero emitted bytes.
6. **The register pattern of the target's entire second half is the unique
   fixed point of the free-queue** given one premise: the branch-feeding
   `lh` is a queue pop ($10). The WIP approximates that premise with its
   dead-statement burner; the true source doesn't need it if the load
   itself takes the pool path.

## 3. The central result: the two instructions are one compiler bit

**Oracle experiment** (`menu_research/report_oracle.md`): the recompiled
ugen was patched (env-gated `UGEN_NOCOLLAPSE`; byte-identical output when
unset, verified) to drop the destination hint for the site's exact
signature (signed 16-bit ILOD stored to a $3/v1-colored web). Under that
one-bit change, the **plain natural source**

```c
selectedTrack = gTrackSelectIDs[trackY][trackX];
cur->hubName = levelName;
if (selectedTrack != -1) { ... }
```

compiles to the shipped bytes **exactly — DIFFS 0, 371/371 instructions**
(stock score for the same source: 133). Pre-as1 evidence shows the
predicted emission verbatim: `lh $10; move $3,$10` (dissolved by as1);
`sw $2,0($16)`; `beq $3,-1` → final `lh t2 … beq t2 … sw` in the delay
slot. The free-queue fixed point then reproduces every downstream register
mechanically. This makes the plain C above a strong historical hypothesis, but
does not identify the original source: the experiment changes a compiler
decision after inspecting the mismatch. The WIP's dead-statement trick and
the community's 64-bit-mask idiom are demonstrably reconstructions of the
*allocation state*, not positive evidence for the original spelling.

Additional reduction: the `cond-seq` comma forms
(`(temp = load, cur->hubName = levelName, temp != -1)`) produce the exact
target instruction *order* (store in the branch delay slot,
mnemonic-perfect stream) under the stock compiler — so the historical "F2
ordering wall" is fully solvable in C, and the entire residual reduces to
the collapse decision alone (`MENU_REATTACK.md` §6.6).

## 4. Why the compiler-variant escape hatch is closed

Three independent legs (`MENU_REATTACK.md` §7):

1. **On-disk binary hunt** (`menu_research/report_hunt.md`): exactly one
   IDO 5.3 ugen binary exists across every toolchain tree on this machine
   (md5 9fcff937…), with no CD-vs-community split (unlike as1, where the
   community binary is patch build patchSG0001118). The full manifests of
   both SGI patch CDs (398 patches) show **no patch ever shipped a ugen**
   (patchSG0000260 = as1, patchSG0001078 = cfe, patchSG0001260 = uopt;
   patchSG0001118 absent from both CDs). Version-axis tests with only
   ugen swapped (fidelity-gated): IDO 5.1 and 5.2 produce byte-identical
   output for this function (and are excluded as Rare's toolchain by
   4-function collateral); IDO 6.0/7.1/7.4.4 collapse *more*, not less,
   and change 52 matched functions. Bonus: IDO 5.1's ugen was made
   runnable for the first time via a relocated-libc recomp
   (`menu_research/report_hunt.md` §1).
2. **Collateral measurement**: even the narrowest oracle gate changes 11
   other currently-matched menu.c functions; plausible broad gates change
   28–113 (call-argument staging shares the same code path).
3. **Source-independent falsification**: under any ugen whose rule defers
   collapse for a class containing our site, a direct `lh <webreg>` is
   *unproducible from any source* for sites in that class (the deferral
   path emits `lh $pool`, and as1 dissolution renames uses toward the
   pool register, never into the web register). The matched menu.c object
   contains **67 sites** of a signed `lh` landing directly in a colored
   web register with non-adjacent later uses — **20 with dest exactly
   v1** (e.g. `draw_menu_elements` +0x29a4, `menu_title_screen_loop`
   +0x41d8, `savemenu_render_element` +0x5b94). Each falsifies every
   uniform gate up to and including "signed-16 into v1". Therefore **no
   uniform collapse-rule variant of ugen is consistent with the shipped
   ROM**, regardless of what sources are assumed for other functions.

## 5. Where we are blocked, and the surviving hypotheses

The one remaining gap: under the stock, canonical ugen, no C construct
was found that blocks the collapse at zero cost. Every family C offers
was closed *mechanistically* (not just empirically): 64-bit masks burn
pairs (parity + queue poison — this is the community decomp.me `L6qKV`
basin, DIFFS 2 with an in-place add); `(s32)` cast forms create
cross-block CSE carriers that rotate the trophies block (DIFFS 56);
s16 chains emit live `sll/sra`; `long long` holders home to stack
templocs; register-only dead statements are DCE'd before ugen; s32
identities are folded by cfe. Nine structurally new families were added
and falsified this campaign (goto/label block splitters — which rotate
allocation globally, mask counts 1–6, zero-extension forms,
variable-free cast chains, dead-store carriers, commutation sweeps,
chain-assign holders, free-list burner statements, embedded-store
identity forms). Full graveyard: `MENU_REATTACK.md` §2, §6.4;
machine-scored ledger of all 241 archived variants:
`menu_research/ledger.txt` (exactly two DIFFS-2 basins; nothing scores
3–37).

Surviving explanations, ranked (ordering revised after the racer
precedent — see below):

1. **An unconceived source construct under stock behavior.** The racer
   function's history forces this to the top: its f20 allocation was
   "proven unmatchable for any source" with the same style of
   instrumented-compiler evidence, and later fell to an untried source
   topology (separate assignment of the velocity-square sum before the
   `sqrtf`; see `REATTACK_HANDOFF.md`, racer section). Family
   enumerations under-count source space. The menu counterpart is,
   however, narrower: the ugen decision is *local* to one statement's
   ucode tree, which enables a finite backward closure (§8).
2. **A context-dependent rule in an unobtained pressed-CD 5.3 ugen**
   (the Dec-1994 "IRIS Development Option 5.3" pressing vs the community
   "IDO 5.3 with C++" redistribution). The uniform-variant falsification
   (§4.3) does not cover rules keyed on properties that distinguish our
   site from all 67 counterexamples — e.g. "defer collapse when the
   stored web's next use lies beyond a potentially-aliasing istr", which
   is precisely our site's signature. The as1 precedent (community
   binary = a patch build; the CD's original as1 breaks matched code)
   keeps this alive. Requires obtaining physical media to test.
3. **Build-process oddity** (hand-patched object, interrupted build).
   No positive evidence; the byte pattern is fully compiler-idiomatic.
   Kept for completeness only.

## 6. What can be contributed back to the community

- **The ugen allocator model** (§2): the FIFO free-queue, pair cycle,
  align-skip queue, in-place ll-add convention, and the ilod→web collapse
  rule apply to *every* IDO 5.3 project (SM64, OoT-era titles, all Rare
  decomps). Nothing this concrete about ugen's temp allocation appears in
  community documentation; the closest public material is uopt-focused
  ([n64decomp/ido](https://github.com/n64decomp/ido)).
- **The glass-box technique**: env-gated instrumentation and behavioral
  patches on [decompals/ido-static-recomp](https://github.com/decompals/ido-static-recomp)
  builds, with byte-fidelity gates (`menu_research/ugen_instrumentation_and_nocollapse.patch`,
  reports). This generalizes: any "why did the compiler pick this
  register" question is now directly observable rather than inferred.
- **Toolchain archaeology facts**: no SGI 5.3 patch ever shipped ugen;
  the complete 5.3 patch-manifest sweep; patchSG0001118 absent from both
  patch CDs; only one 5.3 ugen exists in community circulation; the
  working IDO 5.1 ugen recomp (relocated libc) for anyone probing 5.1-era
  titles. (`menu_research/report_hunt.md`.)
- **The ROM-anchored falsification pattern** (§4.3): a reusable method
  for testing "different compiler variant" hypotheses source-independently
  — enumerate sites in *matched* code that the hypothesized variant could
  not produce from any source. This is stronger than collateral counts
  and costs one disassembly scan.
- **For DKR specifically**: the natural source of `func_8008FF1C` is
  identified with near-certainty, and the community's decomp.me scratch
  (L6qKV, 99.69%) is explained — both its success (as1-dissolvable copy
  chains reaching the pool lh) and its irreducible 2-diff residue (the
  in-place 64-bit lo-add). This write-up plus `MENU_REATTACK.md` §6–§7
  is suitable material for a decomp.me/community post.
- **Racer** (parallel Codex campaign, reported in `REATTACK_HANDOFF.md` /
  `RACER_REATTACK.md`): the separate-assignment topology that naturally
  yields the f20 residency, frame, and FP histogram with the stock
  compiler — reportedly down to 28 localized GPR words. Not independently
  verified in this session; cited as reported.

## 7. Experiment and artifact log

Durable archive (untracked, in-repo): **`menu_research/`**

| Artifact | Contents |
|---|---|
| `report_oracle.md` | Oracle leg: patch location (f_eval/L42ec60), mechanism, DIFFS 0 result, gate modes, collateral table, fidelity statement |
| `report_hunt.md` | Hunt leg: full ugen inventory w/ md5s, patch-manifest sweep, per-candidate test matrix, 5.1 recomp fix |
| `UGEN_HUNT_BRIEF.md` | The shared brief both agents executed against |
| `ledger.txt` / `ledger.json` | Machine scores for all archived variants (name, DIFFS, first-diff index) |
| `variants/` (241 files) | Every source variant ever scored, incl. `v_base` (WIP, 2), `v_scratch` (community mask idiom, 2), `v_zz1` (cast form, 56), `v_natural` (predicted true source, 133 stock / 0 under oracle) |
| `tools/` | `try.py` (scorer), `compile.sh`, `base.c` (TU basis), `target.o` (reference), `score_all.py` (parallel ledger builder), `klist.sh` (pre-as1 listings), `utrace.sh` (ucode listings), `masktab.py` |
| `traces/fltrace2_{base,zz1}.txt` | Raw free-queue event streams from the instrumented ugen |
| `ugen_instrumentation_and_nocollapse.patch` | Full diff (pristine → instrumented+patched) of the recomp `ugen.c` |

Narrative logs (untracked, repo root): `MENU_REATTACK.md` (the full
technical account, §1 problem reduction → §7 final verdict),
`CODEX_REATTACK_LOG.md` (chronological, all sessions),
`REATTACK_HANDOFF.md` (menu+racer executive state), `RACER_REATTACK.md`.

Volatile (session tmp — regenerable via `tools/`, will not survive
reboot): full pre-as1 listings (`klist_*.s`), 7 MB ucode listings
(`ubase.lst`/`uzz1.lst`), the built patched compiler
(`…/17d442b1…/scratchpad/ido-recomp-pub/build/5.3/out/ugen`, rebuildable
from the archived patch with `make build/5.3/out/ugen VERSION=5.3`), the
oracle/hunt working dirs (`…/84e018d6…/scratchpad/menu/{oracle,ugenhunt}/`).

Campaign totals for this function across all sessions: 500+ source
variants scored, ~58k permuter iterations, 9 new mechanism families
falsified this campaign, 2 instrumented-compiler builds (uopt previously,
ugen now), 7 distinct ugen binaries inventoried (3 behavior groups), 398
SGI patch manifests swept, one DIFFS-0 oracle demonstration.

## 8. The final experiment: backward ucode-level closure (EXECUTED — closes EMPTY)

Executed 2026-07-24 (full report: `menu_research/report_ucode_enum.md`).
The stock ugen's entire expression dispatch (152 opcodes, jump table at
`f_eval` ~L56333) was read and empirically verified with stock-toolchain
probes. Findings:

- Only **one** tree shape in the whole dispatch defers the load to a pool
  temp at zero cost (no real instructions, no register pair, no CSE
  carriers): an **identity integer→integer `Ucvt`** taking the
  `func_436008` same-datatype path, which emits a single as1-dissolvable
  move.
- That shape is **unreachable from C**: cfe deletes identity 32-bit int
  casts before ucode exists. Proven to the byte — `x = (s32)load;` and
  `x = load;` compile to byte-identical objects with content-identical
  uopt listings. Every `Ucvt` that *survives* cfe changes representation
  and pays a fatal cost: 64-bit widen allocates a pair (→ 119),
  narrowing folds into the load and still collapses, int↔float costs
  four FPU ops, s16-widen-via-variable emits live `sll/sra`.
- Every non-`Ucvt` root either collapses the load into the web or emits
  ≥1 real instruction. Nothing scores between 3 and 118 across the probe
  matrix; the four win conditions (defer, zero-real, zero-pair,
  no-carrier) are **jointly unsatisfiable over C-reachable shapes**.

SCOPE CORRECTION (2026-07-24, after external audit — see §10): this
enumeration is a **lemma, not the theorem**. It formally closes the
RHS-wrapper dimension of the fixed frame
`holder = <WRAP>; store; if (holder != -1)` — every wrapper class in
the dispatch either collapses, costs real instructions/pairs, or is
cfe-unreachable. It does NOT enumerate alternate statement topologies,
CFGs, web-coloring perturbations, or compensating allocator effects
elsewhere in the function; those are closed only by the earlier
family-based campaigns (§6), which is the racer-vulnerable evidence
class. Concretely, topology *does* cross the wrapper boundary: the raw
condition form already produces `lh t2` (with the store misplaced), and
the mask basin produces the exact `lh t2`/`beq t2` core (missing only
two later `addu` operands). Hypothesis 1 of §5 is therefore *heavily
constrained and unlikely*, not formally dead; the honest statement is
that no known topology reaches the full fixed point, and the two
DIFFS-2 basins approach it from complementary sides without meeting.

## 9. The pressed-CD test (EXECUTED — negative) and final standing

An online survey (2026-07-24; full report
`menu_research/report_online_survey.md`) obtained the two most
independent IDO 5.3 distributions in existence: a **pressed retail
"IRIS Development Option 5.3" CD** (EFS image, build tree
`joist/5.3MR`, via the jrra.zone SGI mirror) and **SGI's own Sep-1997
freeware release** (`iris-development-option-5.3.tardist`, via the
ftp.zx.net.nz mirror of the dead ftp.sgi.com). Result: their entire
compiler pass sets are **byte-for-byte identical** to each other and to
the community baseline — ugen md5 `9fcff937…` in all three. Every other
online source (GitHub repos, archive.org, recomp releases) is the same
blob or carries no ugen. The 5.3 ugen is a single build that SGI never
re-pressed; **hypothesis 2 is now dead by direct test.**

(Genuinely new community-relevant side-finding: THREE distinct 5.3 as1
builds are now catalogued — the pressed-CD/freeware original (807,808
bytes), the community-git as1 (816,064 — a different build from both
others), and the banjo-kazooie tree's patchSG0001118 as1 (904,272).)

**Final standing** *(SUPERSEDED by §10's revised verdict — retained for
the record; "every testable hypothesis" overstated the topology
closure)*. Every hypothesis testable at the time was tested and
negative: source space (closed at the opcode level, §8), uniform
compiler variants (ROM-falsified, §4), on-disk binaries (§4), online
binaries including the pressed CD itself (§9). What remains is only the
untestable residue: an SGI-support or Rare-local hot-fix ugen that never
entered distribution, a hypothetical pre-MR 5.3 pressing not present in
any online index, or a build-process oddity. The committed WIP at
**DIFFS 2 is the proven ceiling** of every obtainable toolchain, and
the oracle result (§3) stands as the definitive explanation of the
residual: the shipped bytes are the plain natural source plus one
collapse decision that no surviving compiler build makes.

## 10. External audit (Codex, 2026-07-24) — accepted corrections

An independent audit reproduced and stress-tested this document's claims.
Accepted findings, now reflected above:

- CONFIRMED: the two-instruction diagnosis (independently reproduced),
  the oracle's causal validity (sufficiency), the pressed-CD negative
  (independently re-downloaded and re-hashed: same 9fcff937 ugen), and
  the conclusions' survival under a full-word comparison (try.py's
  metric ignores immediates/branch targets/relocations — a known
  limitation; future DIFFS-0 claims must be link-normalized exact).
- CORRECTED: §8's "covers all of C by construction" was an overclaim —
  the enumeration closes the RHS-wrapper dimension of one statement
  frame (a lemma), not topology/CFG/coloring space (see the scope
  correction in §8). "The original was near-certainly plain C" is
  downgraded to "the most parsimonious explanation": the oracle proves
  sufficiency, not uniqueness or provenance.
- ADDED NEGATIVES (Codex): build-mode escape hatches -O0/-O1/-O3,
  -Olimit sweeps, -mips2, debug modes — none produce the target; modes
  preserving the 371-instruction shape stay in the 133 basin. The 43
  ledger-missing variants were scored: no zero; best another DIFFS 2.
- HYGIENE DEBT (recorded, not yet done): try.py full-word mode;
  klist.sh/utrace.sh depend on volatile scratch paths and should be
  re-rooted to menu_research/.
- REVISED VERDICT: DIFFS 2 is a very credible *practical* ceiling
  today, not a proven source-space ceiling. The remaining substantive
  vein is the two-basin merge topology search (WIP basin: perfect
  downstream, wrong load register; mask basin: perfect load register,
  two wrong addu operands) — pursued glass-box-first as of this date.
  Worthwhile external-binary leads are Rare/Nintendo SDK or build
  archives searched by compiler-pass hash, and cross-revision ROM
  comparison (v77/PAL — requires media not currently on disk); ordinary
  retail IDO 5.3 CDs are conclusively not worth chasing.

## 11. The parallel wave (2026-07-24, five agents) — final synthesis

Executed per the externally-audited plan (§10). Reports:
`menu_research/report_{basin_merge,scope_cfg,loopmatrix,rare_mining,passmatrix}.md`.
Verifier upgraded first (`tools/tryfw.py`: full-word, reloc-masked).

1. **Basin-merge (glass-box)**: both DIFFS-2 basins closed BY CODE
   READING. The 64-bit lo-add's dest is always the FIFO queue head
   (f_eval2 L429f10 → f_get_dest hint 0x48 → f_get_free_reg); the
   "in-place" behavior is an emergent queue effect, and the three needs
   (lh t2 / trophies alignment / $11-live at the add) are pairwise but
   not jointly satisfiable. uopt's globalcolor forbids registers only
   for SURVIVING interfering webs; the WIP's s16 burner is invisible to
   coloring (1–6 stacked burners: color invariant), and real
   interference costs code (394). Queue model revalidated 267/267.
2. **Scope/CFG/signature sweep**: ~48 cells, all negative; scope,
   lifetime, declaration order, dead-local reuse, CFG forms, and
   signature levers are swept (not argued). Declaration reordering is
   provably allocation-neutral. F2 pinned to the instruction.
3. **Loop/provenance matrix — the discovery**: two index-based loop
   topologies make uopt grant `.noalias(load,store)` and achieve the
   EXACT [lh pool][li][beq][sw-slot] microstructure under the stock
   toolchain — the first C-level break of the order wall. But
   provenance requires a surviving symbolic index (~7 instructions);
   the target uses the bare pointer induction, whose provenance
   strength-reduction destroys. ERRATUM to MENU_REATTACK §2 recorded.
   Consequence: there are TWO one-bit routes to the target — the ugen
   collapse-deferral (§3 oracle) or a uopt alias-tag grant for pointer
   inductions.
4. **Rare corpus mining**: GoldenEye (full second Rare game, vendors
   the byte-identical original ugen) contains ZERO pool-temp idioms in
   345 objects; corpus-wide, no compare-feeding signed lh ever stays in
   a pool temp; and a matched GE function with the EXACT DKR topology
   ships collapsed (the "collapsed twin"). Banjo-Kazooie: no analog.
   The DKR site is a SINGLETON across all measurable Rare output.
5. **Pass matrix**: func_8008FF1C byte-invariant to every cfe/uopt/as1
   combination including raw×patchSG0001260-uopt (the route-2 test).
   Side result: DKR's toolchain is PINNED to retail cfe + retail 5.3MR
   uopt + the community-git as1 (the pressed as1 breaks 3 matched
   functions). The aggregate/bitfield/declaration family: swept,
   negative. uopt coloring knobs cannot defer the load.

### Final verdict (supersedes §5/§9 rankings)

Codex's pre-registered stop condition has triggered: no candidate
reached a new free-queue state with the target prefix; no matched Rare
function demonstrates the idiom; the loop matrix produced [lh][sw] only
by abandoning the byte-required induction; the pass matrix is negative.
Residual probability of a recoverable clean-C match: **below ~1%**.

The best-supported account of the two instructions: a **site-specific
build anomaly** — the singleton evidence (one occurrence across two
games of an idiom the same binary collapses everywhere else, including
in Rare's own matched code) now outweighs both the systematic-toolchain
and the exotic-source explanations. The two one-bit compiler routes
(ugen dest-hint, uopt alias-tag) remain the mechanical description of
WHAT differs; the singleton statistics say it differed ONCE.

Rational endpoint, per the audited plan: **document the DIFFS-2
nonmatch as the ceiling** (done, this archive), with reopening
conditions: a legally-owned other-revision ROM (the singleton
hypothesis PREDICTS other revisions may show `lh v1` — a testable,
falsifiable prediction), Rare/Nintendo archival material, or a
community-found hole in the swept closures.

## 12. The cross-revision sweep (2026-07-24) — the pre-registered prediction, tested

User-supplied legally-owned dumps of all five retail variants were
screened for the site (raw byte-pattern search, calibrated on the v80
baserom: exactly one hit, zero false positives).

| ROM | md5 | site form | addu | function vs v80 |
|---|---|---|---|---|
| US Rev 1 (v80) | b31f8cca (== baserom) | **lh t2** | addu $12,$11,s2 | reference |
| US v1.0 (v77) | 4f0e07f0 | **lh t2** | addu $12,$11,s2 | identical mod relink (35 addr-class diffs, 0 hard) |
| PAL v1.0 | 0f0b7b78 | **lh t2** | addu $12,$11,s2 | identical mod relink (35 addr, 0 hard) |
| PAL Rev 1 | 6b2bafe5 | **lh t2** | addu $12,$11,s2 | identical mod relink (27 addr, 0 hard) |
| JP | 10747662 | **lh t2** | addu $12,$11,s2 | identical mod relink (50 addr, 0 hard) |

All five shipped builds carry the anomalous pool-temp form,
bit-identically modulo link addresses (jal targets + hi/lo immediates
only — pure relink artifacts; zero register/opcode/structural diffs in
the 371 instructions). Aligned-span analysis: the identity region
around the function extends −22..+4KB (US/PAL v1.0), −46..+59KB (PAL
Rev1), but only −1..+4KB (JP) — i.e. the JP build has structural code
churn within ~1KB of the function (same-TU territory), so menu.c was
genuinely recompiled for JP and STILL reproduced the anomaly exactly.

### Interpretation update (supersedes §11's ranking)

The §11 prediction ("other revisions may show lh v1") is FALSIFIED, and
with it the one-off build-fluke account: the anomaly is deterministic
and persistent across five builds spanning the release year, surviving
at least one genuine recompilation of its TU. Combined with the
GoldenEye collapsed-twin (§11.4: the canonical binary collapses this
topology in Rare's own matched code), the surviving explanations are
now exactly two, both persistent:

1. **A persistent DKR-build-machine toolchain difference** — e.g. an
   SGI-support hot-fix or locally-patched pass installed on the DKR
   team's build machine (but not GE's) for the project's lifetime.
   Matches both one-bit routes (§11.3); unobtainable except via Rare
   archival material.
2. **A deterministic source construct we have not conceived** — swept
   to <~1% by §8/§11 closures, but the only C-side survivor.

The stale-object account survives only in weakened form (an object
carried across US/PAL builds is consistent with the relink-only diffs,
but the JP recompile argues the source itself still produced the form).

## 13. The H-SOURCE investigation (2026-07-24) — the clean-story test

Prompted by the objection that a site-keyed compiler patch is a hack and
the cleanest account is source-derived, we tested H-SOURCE: that a
legitimate natural source compiles to the target under the STOCK
toolchain. Codex/sol designed the test protocol
(menu_research/H_SOURCE_TEST_PLAN_codex.md); two glass-box agents
executed it. Two decisive results.

### 13.1 The principled-toolchain story is falsified (opportunity count)
report_provenance_hunt: the alias truth table was validated (7.1==5.3,
no version quirk). base_noalias in C: D/D -> disjoint iff regions don't
overlap (distinct symbols ARE provable); D/P against an Smt global ->
CONSTANT may-alias (aliaswithptr returns true unconditionally in C). So
the retail grant (global load vs pointer store) is NOT expressible as
any fresh alias query. The collateral of a uniform grant was then
classified by pointer provenance: >= 3 output-sensitive, retail-matched,
genuinely-disjoint single-global-origin (G) sites exist in menu.c alone
(the target, func_80083098, load_menu_text). A PRINCIPLED
provenance/disjointness rule therefore is NOT zero-collateral — it moves
those matched functions off retail bytes. The only zero-collateral gate
(descriptor w13/w15) is a raw site fingerprint = a hack. The "Rare had a
better general alias analysis" story is dead at the principled level.

### 13.2 The retained-direct-base source route is closed (state-machine proof)
report_retained_base: the one byte-exact alias route left was the
retained-no-alias state path (base_in_reg keeps a no-alias established
while a register held a Direct base). Glass-box trace of the raw source:
cur's register never holds a Direct base during the induction (the loop
init `cur = gTrackSelectRenderDetails` is an `la` address computation,
not an alias event), and the cur<->gTrackSelectIDs pair is pre-locked to
may-alias (unaltab=1, irreversible) by an early P/P query before the
global is resident. Seeding the no-alias requires a syntactic
direct-index access that re-derives the address per iteration (+>=7
instructions, breaking LEN 371). PROOF: byte-exactness and a retained
no-alias for the cur-store are mutually exclusive under the stock
toolchain. This elevates the loop-matrix observation to a theorem and
closes the last byte-exact ALIAS lever at the decision level.

### 13.3 Where H-SOURCE stands
The target is reachable in the compiler by two mechanisms (ugen
collapse-deferral, uopt alias-grant), both demonstrated to exact bytes
under site-keyed gates. From STOCK-legal source: the alias route is now
CLOSED (13.2 proof + fresh-query impossibility); the collapse-deferral
route's RHS-wrapper frame is closed (report_ucode_enum) but its
topology/statement-motion/as1-scheduler predecessors (Codex Step 8) are
not exhaustively enumerated. So H-SOURCE is not fully closed, but its
most promising lever is dead by proof, and every principled toolchain
explanation is falsified. The convergent evidence: the site is reachable
only by non-principled (site-specific) compiler behavior, from no
stock-legal source found or provable-reachable on the closed axes. The
remaining open surface is the non-alias producer enumeration (Step 8),
a completeness exercise with low match-probability given both routes'
primary frames are closed.

## 14. Racer-technique transfer + review corrections (2026-07-24)

Racer (func_80049794) matched today via a statement split that retimes
ucode alloc/free events in the ugen FIFO free-queue. Tested on menu.

### 14.1 Racer technique does NOT transfer — mask basin closed at event level
report_stmtsplit: menu's 2-diff mask basin residual is NOT a retimable
single-register FIFO pop. The 64-bit lo-add hits the pair mask
0x05010000 -> f_get_two_free_regs -> even-base, home=base+1=ALWAYS ODD;
the target's $12 is EVEN -> requires a 32-bit add, but the trophies block
requires the 64-bit pair consumption. Contradiction. Oracle (rotate/
delay/force-32bit) CANNOT reach FULLWORD 0. This is a parity-lock, not an
event-ordering anomaly — categorically unlike racer's single-pop residual.
Both DIFFS-2 basins are now mechanism-closed for the racer axis (mask =
parity oracle proof; WIP = collapse/coloring needing 7 impossible
zero-code interferers). Static-vs-dynamic note: Codex's static read said
the datatypes miss the mask (retimable); the trace+oracle proved they hit
it (parity-locked) — the dynamic result governs (forcing the pair call
empirically moves instruction 110).

### 14.2 Corrections to §13 (Codex review 2, sound)
- §13.1 "principled-toolchain story falsified" is OVERBROAD. The narrow
  fact holds (a fresh D/P alias query can't grant no-alias). But the
  collateral classification was coarse: load_menu_text's base is a LOADED
  global pointer (POINTER_LOAD root, excluded from "G" by the plan's own
  definition) - misclassified; func_80083098's introCharData is a bounded
  single index, not a loop-carried induction. A REFINED principled rule
  ("loop-carried induction over one fixed global, proven disjoint from
  another fixed global") could isolate the target with zero collateral and
  is a legitimate alias-analysis improvement, not a fingerprint. The
  "Rare had a better general alias analysis" story is NOT dead; only the
  coarse single/distinct-global-origin rule is.
- §13.2 the retained-base RAW path is genuinely closed, but the UNIVERSAL
  theorem ("every D seed requires the +7-instruction direct-index shape")
  is asserted, not enumerated per the plan's static-predecessor
  requirement. Strong evidence, not an airtight all-topology proof.

### 14.3 Standing
Both 2-diff basins mechanism-closed. Racer's transferable technique
tested and refuted for a characterized reason (pair-parity vs single-pop).
Remaining un-exhausted surfaces, both low match-probability: Step 8
(collapse-deferral topology predecessors of the WIP basin) and the
refined-principled-alias-rule question (a toolchain-story refinement, not
a source match). No stock-toolchain match found; committed WIP DIFFS 2
remains the ceiling.

## 15. Sister-corpus incorporation (Codex prior-session sweep, folded 2026-07-24)

A prior Codex sister-game sweep is incorporated here for the parts not
already covered by report_sister_deep / report_rare_mining. Its core
recommendation ("compiler-provenance, not a source idiom") is confirmed
but SUPERSEDED by this project's deeper mechanism work (§8, §11-14).
Three genuinely additive results:

### 15.1 CORRECTION: Perfect Dark is an IDO 5.3 negative corpus, not out-of-scope
Earlier notes marked PD "GCC lineage, out of scope." That is wrong: PD's
RETAIL matching compiler is IDO 5.3 -O2 -mips2 (GCC is only the optional
nonmatching port). All 229 PD game C files were compiled with the
IDO 5.3 toolchain: ZERO strict normal-branch matches (one branch-likely
direct-field cousin in rocket_tick_fbw; a loop-carried assign in
rooms_copy; a direct global test in koh_tick — all ordinary). PD is thus
a fourth substantial IDO 5.3 corpus confirming the singleton.

### 15.2 The positive-control table (stronger than "zero second sites")
The identical source shape (signed s16 field -> named local -> intervening
stores -> compare with -1) is PRESENT and collapses NORMALLY in every
measurable DKR-engine relative:
  JFG mempool_slot_clear (shipped + fresh 5.3 -O2 -mips1) -> colored a2
  Mickey memory-pool descendant                          -> colored a3
  GoldenEye setupRoomTransformationMatrix                -> colored s0
  Stock DKR compilation of the menu source               -> colored v1
  Retail DKR menu object                                 -> pool temp t2
So the singleton is not merely the ABSENCE of the anomaly elsewhere; it
is the PRESENCE of the normal collapse for the identical pattern in three
sibling games (JFG explicitly a modified DKR engine; both ROMs SHA-1
verified). This is the strongest form of the singleton evidence.

### 15.3 Broader Rare corpus (weaker negatives, no matching ROMs)
Audited with no strict match found: Banjo-Kazooie, Banjo-Tooie (-mips2),
DK64 (-mips2), Conker (incomplete), Dinosaur Planet (mixed 5.3/7.1,
DLL-oriented), Blast Corps (-O1, older). None combines the ingredients.
Toolchain corroboration: the IDO 5.3 ugen in the Mickey and PD toolchains
is byte-identical (sha256 4d6ae5a5...), consistent with the single-ugen
finding (§4). No public Rare-wide patched compiler exists — a private
DKR-era patch/wrapper/build-environment installation remains the
strongest provenance hypothesis, unchanged by this corpus.

### 15.4 Net effect
Adds a fourth IDO-5.3 corpus (PD) and converts the sister-game evidence
from absence-of-anomaly to presence-of-normal-collapse across three
DKR-engine relatives. Does not change the standing (§14.3): no
stock-toolchain match; committed WIP DIFFS 2 is the ceiling; the anomaly
is a persistent DKR-build-environment compiler behavior, now controlled
against five sibling/self corpora.

## 16. Final construction session and safe stopping point

The skeptical handoff reopened the three places where earlier closure claims
were soft. All three were pursued without a stock match.

1. **Retained/direct alias state.** Address assignments do not seed alias
   state; real direct memory seeds retain target-visible address work;
   pointer-difference round trips do not cancel; and a direct store followed
   by an equal pointer assignment does not coalesce or transfer retained
   no-alias state. A flat continuous direct induction can reach the exact local
   target window, correcting the old “direct always costs +7” claim, but only
   by changing the target's nested outer-induction/allocation graph.
2. **32-bit index plus independent pair activity.** Producer, call-boundary,
   carrier, entry-pointer, and shift/subtract/shift-stage families converge on
   a 371-word three-difference basin at indices `(106,107,109)` or worse. No
   semantically live handoff preserves both the even `$12` result and the
   downstream trophies queue state.
3. **Non-alias producer.** The fixed holder-frame opcode enumeration remains
   empty except for the identity `Ucvt` deleted by `cfe`. `const`, block scope,
   and parameter reuse remain FW133 collapse forms. The flat-loop success uses
   alias ordering, not a fourth producer.

Boundary checks also eliminated supported alias pragmas/qualifiers, hidden
driver alias flags, and global `static` linkage as missing inputs.

This is a mechanism-level stopping point, not an all-C theorem. The earlier
phrase “DIFFS 2 is the proven ceiling” should be read as “DIFFS 2 is the
audited practical ceiling under the target-compatible normalized predecessor
classes tested.” An unconceived topology remains logically possible.

Further broad syntax, mask, declaration-order, or loop-form sweeps are now
wheel-spinning. Reopen only for a proposal that predicts a new normalized
compiler state while preserving all 371 words, or for new Rare/Nintendo
source, object, build, or compiler evidence.

Primary final records:
`menu_research/report_construction_endgame.md`,
`menu_research/POSTMORTEM.md`, and
`menu_research/SESSION_HANDOFF_2026-07-24.md`.
