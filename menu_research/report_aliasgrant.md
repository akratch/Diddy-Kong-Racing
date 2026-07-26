# H1-alias grant test (final wave) — 2026-07-24

VERDICT: NEAR — H1-alias VALIDATED TO FULLWORD_DIFFS 0, not
zero-collateral in uniform form.

THE HEADLINE: the plain RAW source (`cur->hubName = levelName;
if (gTrackSelectIDs[trackY][trackX] != -1)`) with the byte-required
bare pointer induction compiles to the shipped func_8008FF1C
BYTE-PERFECTLY (FULLWORD_DIFFS 0, 371/371, reloc-masked; site =
lh t2 / li at / beq / sw-in-slot exactly) the moment uopt grants
load/store disjointness for the (GP-global, induction-pointer) pair.

THE DECISION PINNED (correction to the ugen-first framing): the
.noalias is DECIDED IN UOPT — f_base_in_reg -> f_base_noalias
(L420b0c; returns disjoint iff accumulator==0 at L420e28) — and
emitted as ucode alias directives (ops 99/137) that ugen merely
translates (f_eval case 137 -> L42d6b8). ugen's own scan-based noalias
fires only for temp-register bases, never the site's $17.

COLLATERAL: the minimal uniform predicate covering the site (k31:
pointer-kind vs GP-global-kind) changes 16 other matched menu.c
functions (list in report body; 'all' mode: 28). Whole-ROM verify
skipped as provably failing. NOT an adoption candidate in uniform form.

ERRATUM to report_loopmatrix: "provenance retention and byte-compatible
loop structure are mutually exclusive" holds only for SOURCE-level
levers; a TOOLCHAIN-level grant achieves both (0 diffs).

STATE OF THE TWO ONE-BIT ROUTES (both now demonstrated to 0 diffs from
plausible source): ugen collapse-deferral (narrowest uniform gate: 11
collateral) and uopt alias-grant (narrowest uniform gate: 16
collateral). PROFOUND CONSEQUENCE: since the shipped menu.o contains
the anomaly AND all 16/11 stock-behaving sites in the same TU, NO
UNIFORM one-bit rule change on either axis can produce the whole
shipped object. Whatever Rare's build did, it was stock everywhere
except this one site.

OPEN REFINEMENT (dispatched as follow-up): our site's alias-query
descriptors are distinctive (global side = kind 1 with SYMBOL 0, pure
GP+offset; the ptrglob mode requiring nonzero symbol LOSES the site) —
if the 16 collateral sites' descriptors differ systematically
(symbol!=0, different kinds/provenance), a descriptor-keyed predicate
could cover the site with ZERO collateral -> whole-ROM verify ->
adoption candidate. Also viable: characterize whether a
provenance-tracking rule (grant only single-symbol-origin induction
pointers) separates ours from the 16 (theirs may be call-derived,
e.g. settings->courseFlagsPtr).

Artifacts: patched env-gated uopt.c (+pristine backup), agscore.py
scorer, descriptor dump machinery — session scratchpads. No tracked
files modified.
