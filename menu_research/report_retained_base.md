# Retained-direct-base: the last byte-exact ALIAS route — CLOSED (proof) — 2026-07-24

> **Construction addendum:** The raw-pointer state-machine proof below remains
> valid. Its universal `LEN>=377` wording was too broad: a flat continuous
> direct induction can avoid per-element address recomputation. That topology
> reaches the desired local no-alias window but changes the target's nested
> outer-induction/allocation graph. The previously missing zero-cost
> predecessors—address-only redundant seed, direct pointer-difference round
> trips, and a direct-store/equal-pointer coalescing opportunity—were tested
> and all failed. The corrected scope and exact scores are in
> `report_construction_endgame.md` §3–4.

Codex Test-Plan Steps 4-7. Glass-box f_base_in_reg instrumentation
(env-gated BIR_TRACE, fidelity-verified env-unset==stock; toolchain
restored to stock byte-identical afterward). Whole-ROM verifier as the
only acceptance gate — never triggered because no candidate passed the
FULLWORD_DIFFS-0 pre-filter.

## Verdict: H-SOURCE CLOSED at the decision level for the alias route.
The byte-exact raw source (bare cur++, LEN 371) and a retained no-alias
for the cur-store are MUTUALLY EXCLUSIVE under the stock toolchain.

## Seed-timing finding (raw-source trace, stock behavior)
51 base_in_reg calls, exactly 4 base_noalias queries, ZERO no-alias;
unaltab never reaches 2. cur = color reg14; its FIRST base_in_reg is
isvar(P) (the first cur->visible), so baseregbase[14]=isvar and every
later cur-> takes the :352 early-return — cur's register never holds a
Direct base during the induction. Two decisive kills:
1. `cur = gTrackSelectRenderDetails` NEVER enters the alias machinery —
   it materializes &arr[0] with an `la` (address computation), not a
   memory access; base_in_reg fires only on accesses. The hypothesized
   isilda seed does not exist as an event.
2. The cur<->gTrackSelectIDs pair is PRE-LOCKED to may-alias: a P/P
   query (reg15 isvar vs resident reg14 cur) sets unaltab[15][14]=1
   (irreversible) BEFORE gTrackSelectIDs is resident; when the islda
   load later enters reg15, the unaltab!=1 guard (uoptemit.c:374) SKIPS
   re-query. The one site query asked is islda(D)/isvar(P) vs Smt-global
   = the constant may-alias.

## Candidates (stock toolchain, tryfw)
| candidate | LEN | FULLWORD | no-alias seeded | store base |
|---|---|---|---|---|
| raw (byte-exact) | 371 | 2 | 0/4 | isvar(P) |
| linear-k direct index (form f) | 378 | 336 | 2 (D/D) | islda(D) |
| seed-store-only direct index | 379 | 307 | 1 (D/D) | islda(D) |
The seeding variants CONFIRM the mechanism is live (the instant cur's
register hosts a Direct base, the site query flips D/D -> NO-ALIAS and
.noalias emits) but each costs >=7 instructions, breaking LEN 371 and
the byte-exact 102-instruction prefix. None reached 0.

## Proof (state-machine invariant for the raw target-shaped pointer loop)
R_cur carries baseregbase=isvar(P) for the entire first loop (set at the
first cur-> deref, preserved by the :352 early-return). A Direct base on
R_cur requires a syntactic gTrackSelectRenderDetails[idx] access, which
re-derives the address per iteration; unaltab[R_cur][R_load] is driven
to 1 (irreversible) by an early P/P query before the load is resident;
the !=1 guard blocks re-query. Therefore, within the raw target-shaped
nested pointer loop, unaltab=2 requires a real direct-memory predecessor.
The tested nested direct-index shape pays the per-iteration index/address
recompute. Later construction work showed that flattening can amortize this
address computation, but only by changing the target's outer induction and
allocation graph. Byte-exactness and a retained no-alias remain mutually
exclusive for the enumerated target-compatible predecessor classes; the older
universal claim over every direct topology is withdrawn.

## Scope
Closes the last byte-exact ALIAS lever. The NON-alias producer routes
(ugen collapse-deferral, as1 scheduler arms; Test-Plan Step 8) are a
separate axis. Within the alias family, H-SOURCE is closed at the
decision level.
