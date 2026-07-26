# Provenance hunt: mechanism, truth table, opportunity count — 2026-07-24

> **Status update:** The retained-direct path labeled untested below was traced
> and then subjected to the missing predecessor constructions. The raw path is
> pre-locked to may-alias; address-only, round-trip, and equal
> direct-store/pointer coalescing seeds do not yield a zero-cost grant. Flat
> direct induction reaches the local window only by changing the target outer
> graph. See `report_retained_base.md` and
> `report_construction_endgame.md` §3–4.

Incorporates Codex/sol methodology corrections (H_SOURCE_TEST_PLAN_codex.md).
Fidelity held (env-gated, env-unset == stock).

## Truth table VALIDATED — 7.1 == 5.3 (no version quirk)
Read base_noalias in BOTH the readable 7.1 (ido-decomp uoptemit.c:247,
base_in_reg:348 early-return:352, aliaswithptr uoptkill.c:116) and the
5.3 recomp (f_base_noalias L420b0c, f_aliaswithptr L44de60). They agree
exactly.

Decision (C mode): base classes D = islda/isilda (Direct named address +
VariableLocation); P = isvar/isop/issvar/dumped (pointer/temp, NO symbol
on node).
  D/D -> aliased = overlapping(regions)  [distinct symbols provable!]
  D/P -> aliased = aliaswithptr(&D)       <- our site
  P/P -> aliased = true (always)
f_aliaswithptr in C returns 1 (may-alias) UNCONDITIONALLY for any
non-register object. So D/P against an Smt global (gTrackSelectIDs) is a
COMPILE-TIME-CONSTANT may-alias.

## Codex was right about the lever
The mtag machinery (assign_mtag/f_set_mtag) is NOT consulted by
base_noalias — it branches on base CLASS + VariableLocation. "Keep the
symbol on cur" does not help: a symbol-tagged induction pointer is still
class P. The target's grant (bare-P store vs Smt-global load) is NOT
expressible as any fresh f_base_noalias query result in C.

## The one byte-exact alias route left: RETAINED-DIRECT-BASE (untested)
base_in_reg early-returns (uoptemit.c:352):
  if (baseregexpr[reg-1] != NULL && incoming != islda/isilda) return;
i.e. if a register was EARLIER given a Direct base that established
unaltab[reg][loadreg]==2 (no-alias), and is LATER reused with a pointer
access, the no-alias PERSISTS without re-query. So a no-alias
established while a register held a Direct object survives across bare
pointer use. This is stock behavior, SOURCE-STRUCTURE-DEPENDENT, and
distinct from loop forms e/f (which pay the index cost at every field).
UNTESTED — the correctly-aimed next experiment (Codex Steps 4-7).

## OPPORTUNITY COUNT (the crux question) — our site is NOT unique
Unit resolved: k31 changes 16 functions; is_drumstick_unlocked is a
measurement artifact (byte-identical body, link shift only) -> 15 real.
Classified each by store-pointer origin (exhaustive source analysis):
- PURE-G (single-global-origin, genuinely disjoint, output-sensitive,
  retail-matched): func_8008FF1C (target), func_80083098 (introCharData
  = &gTitleCinematicText[gOpeningNameID]), load_menu_text (menuText =
  gMenuText etc). >= 3 such sites.
- C/call-derived (settings->courseFlagsPtr etc): ~6.
- M/mixed pointer-load bases: ~5. P/param: ~2.

CONCLUSION: a PRINCIPLED provenance/alias rule (single- or
distinct-global-origin disjointness) is NOT zero-collateral — it fires
on func_80083098 and load_menu_text and moves them off retail bytes.
The only zero-collateral gate ever found (descriptor w13/w15) keys on
raw internal words = a site fingerprint / hot-fix shape = a hack, as
report_descriptor_gate concluded. The general-toolchain "better alias
analysis" story is therefore FALSIFIED at the principled level.

## Verdict
H-SOURCE OPEN (not false). A fresh query cannot yield the target's
no-alias in C; a principled toolchain rule is not zero-collateral; but
the retained-direct-base STATE path is byte-exact-capable,
zero-collateral BY CONSTRUCTION (stock compiler, source-dependent), and
UNTESTED. If our function's original source seeds a retainable no-alias
(e.g. via the loop-init cur = gTrackSelectRenderDetails, an isilda) and
other G functions' sources don't, that is a legitimate non-hack match
AND explains the singleton. Byte-exactness is the open risk (the target
matches the bare-pointer control for its first 102 instructions, so any
seeding access must add zero instructions). Next: the f_base_in_reg
state-machine trace.
