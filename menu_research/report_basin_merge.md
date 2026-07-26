# Basin-merge search (Codex plan #1/#3 glass-box core) — 2026-07-24

> **Construction addendum:** Later work separated the real 32-bit index from
> the pair activity instead of trying to retime the 64-bit low-add. Across the
> checked-in live-carrier/arithmetic predecessor families, all roads converge
> on an exact-length FW3 producer basin or worse; none merges to zero. The
> full case ledger and scope are in `report_construction_endgame.md` §5.

Verdict: NO DIFFS 0. Both DIFFS-2 basins are now closed BY CODE READING
to the single deciding instruction each. Queue model revalidated 267/267
GET events. Fidelity verified; no tracked files touched.

## Direction A (mask basin) — closed by reading the dest-selection code

The 64-bit lo-add's destination is ALWAYS f_get_free_reg (the FIFO
head): f_eval binary case L432890 -> L432c68 -> L432d2c -> f_eval2
(L50786); 64-bit dtypes {5,7,15} tested at L429e68; at L429f10 the dest
comes from f_get_dest(tree, hint) with hint=0x48 (NONE) -> f_get_free_reg
(L45612). The "in-place $11 reuse" is an EMERGENT QUEUE EFFECT, not a
liveness gate: the 32-bit mul result gets copied out of $11 into the
sign-extension pair (killing $11 into the queue head), so the lo-add's
GET pops $11. In the target, trackY*6 stays live in $11 as the add's
left input, so the head is $12.

The joint-unsatisfiability: (1) lh t2 requires the ll-masks; (2) the
trophies block aligns ONLY with exactly 2 mask pairs (counts 1/3/4/5
re-verified: 128/129/128/133); (3) with 2 pairs consumed, new_var's
pair is pinned to (24,25) and the mul must copy out of $11 (freeing it)
— so the add can never see $11-live. Pairwise satisfiable, jointly not.

## Direction B (WIP basin) — closed by reading uopt's coloring

globalcolor (ido-decomp uoptreg2.c L1948; cost scan L2094-2141;
updateforbidden L1044): a register is forbidden ONLY by a SURVIVING
interfering live range; webs deleted by copy-prop/redundant-store never
reach coloring. Forcing the holder to $10 needs SEVEN surviving
interfering webs. Decisive experiment: the WIP's s16 burner is a
ugen-pool effect INVISIBLE to coloring — stacking 1-6 burners leaves
the color invariant (all DIFFS 2, load stays v1); real interfering
locals move the color only by emitting code (4 live locals -> DIFFS
394). The zero-code lever and the color-moving lever are disjoint;
seven zero-code surviving interferers do not exist.

## Candidates scored

A1_llmul (long long)trackY*6 = 352 (real dmult); A2_6LL = 352;
A3_llx +(long long)trackX = 2 (dest still $11); mask sweep 1/3/4/5 =
128/129/128/133; s16 burner in-branch = 325 (re-emits lh); stacked
burners x1-6 = 2 each (color invariant); live4 = 394.

## Meaning

Both DIFFS-2 basins are mechanically explained to their last
instruction, and neither admits a zero-cost C construct under the
canonical toolchain. This retires Codex plan #3 (scratch-basin repair)
at the mechanism level: any remaining hope lives in topology families
that change the QUEUE STATE ITSELF (plans #2/#5/#6, in flight) or in
non-source explanations.
