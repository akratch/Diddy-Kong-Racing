# Loop induction/provenance matrix (Codex family #2) — 2026-07-24

> **Construction addendum:** A later flat continuous direct induction also
> reaches the exact local window without paying the same per-element +7
> address sequence. This narrows the “irreducible conflict” below: direct
> access and byte-compatible **nested outer induction/allocation** are
> incompatible in the tested predecessors, rather than direct access always
> costing +7. Restoring the outer row graph promotes `trackY+1` into a new
> recurrence or adds real instructions. See
> `report_construction_endgame.md` §4.

HEADLINE: two loop topologies ACHIEVE [lh][sw] — the exact target
microstructure (lh pool-temp; li at,-1; beq; sw in delay slot) — under
the STOCK toolchain, via uopt granting `.noalias $17,$16`
(load-address vs store-base disjointness). First C-level break of the
F2 order wall. NOT a match: both forms abandon the pointer induction.

Winning forms (raw-condition block):
- (e) fully direct indexed (arr[(i+1)*3+(j+1)].field for every field):
  .noalias YES, [lh][sw] YES, DIFFS 329.
- (f) linear k induction (arr[k].field, k++): .noalias YES, [lh][sw]
  YES, DIFFS 327, store offset exact.
All other 8 forms (incl. control cur++, recompute-per-iteration,
row-pointer, reset-outer, pointer-to-row, moved/pre increments,
do-while): no .noalias(load,store), [sw][lh], 38-332.

Mechanism: uopt attaches the gTrackSelectRenderDetails memory tag only
when the SYMBOL appears at the point of use (a surviving integer index
re-derives the address each iteration). Strength reduction actively
DESTROYS symbol-based recomputation back into a bare induction pointer
(forms b/d listings show the la + addu $16,$16,16 rewrite). The
surviving index costs ~7 instructions (k spill/reload/recompute) →
LEN 377/378 and a global rename cascade.

The irreducible conflict: the TARGET uses the bare pointer induction
(control form aR matches it byte-for-byte through 102 instructions) AND
got the [lh][sw] order — i.e. the shipped compiler granted
.noalias(load,store) FOR A BARE POINTER INDUCTION, which canonical
uopt/ugen never does. Provenance retention and byte-compatible loop
structure are mutually exclusive under the stock toolchain.

ERRATUM to MENU_REATTACK §2: "No C respelling of the store restores
provenance. Closed." was true only under the fixed loop structure;
whole-loop restructures DO restore it. Another family-closure
overreach corrected by sweep.

NEW FRAMING — a second one-bit route to the target: besides the
ilod-collapse deferral (ugen eval hint; the oracle), the target is
equally explained by an ALIAS-TAG grant in uopt for pointer inductions
(raw source + that grant = pool lh + correct order with no holder
tricks at all). This elevates the uopt axis of the compiler-pass matrix
(patchSG0001260 uopt × raw seed) — the prior hunt tested 1260 only
against holder-shaped sources.

Natural-holder block: inert to all ten topologies (no .noalias ever;
problem remains F1/v1). Artifacts: vL_* variants in menuwork;
klist_L*.s listings + gen/scan/win tools in session-84e018d6
scratchpad menu/.
