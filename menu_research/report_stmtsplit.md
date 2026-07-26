# Racer statement-split technique on menu mask basin — 2026-07-24

> **Construction addendum:** The open escape named here—a separate 32-bit
> index plus independent, semantically live pair activity—was subsequently
> pursued across producer, call-boundary, carrier, entry-pointer, and
> shift/subtract/shift-stage families. The strongest new state is 371 words
> with three differences at indices `(106,107,109)`; no case reached zero.
> This closes those explicit predecessor classes, while not claiming a theorem
> over every C topology. See `report_construction_endgame.md` §5.

VERDICT: racer technique does NOT transfer. Mask basin CLOSED AT THE
EVENT LEVEL by an oracle-tested parity theorem. No match; FULLWORD floor
stays 2 (v_scratch).

## Why it doesn't transfer (the parity theorem, trace + oracle proven)
The mask-basin residual (idx 110/111: got addu t3/$11 in-place, want
addu t4/$12 fresh) is NOT a retimable single-register FIFO pop like
racer's. The 64-bit lo-add's datatype {5,7,15} HITS the pair mask
0x05010000 (a set bit shifts to bit 31), routing to f_get_two_free_regs
(NOT the single f_remove_head). That takes an EVEN-aligned base and homes
the value to base+1 = ALWAYS ODD {9,11,13,15,25}. The target needs $12
(EVEN), unreachable by any 64-bit pair-add -> the target's index add is
32-BIT. But the trophies block requires the 64-bit pair CONSUMPTION of
(24,25),(8,9),(10,11) to advance the queue into its matching state
(dropping it rotates trophies: C1-32bit=119, single=88). So DST=$12 <=>
32-bit AND trophies-correct <=> 64-bit: a contradiction, and no
zero-emission uop can consume the pairs on the side (register-dead ll's
DCE'd; memory-read ll's emit real loads, +12 insns).

## Oracle (the reachability decision, executed per the pre-registered rule)
Env-gated ugen hooks (CODEX_MENU_ROTK rotate, CODEX_MENU_SINGLE force
32-bit, CODEX_UGEN_HOLD_REG delay-free), fidelity env-unset byte-identical.
- baseline t3(11) FW2; ROTK=1/3/5 -> t5/t7/t9 (13/15/25) FW128 — home
  cycles the ODD set, never 12.
- SINGLE (force 32-bit) -> t3 FW88 (breaks trophies); SINGLE+ROTK=5 ->
  fixes 110, FW118 (breaks 108/111/trophies).
- HOLD_REG=11 (delay free) ABORTS — $11 immediately re-referenced by the
  widening, cannot be held out of circulation.
The oracle CANNOT reach FULLWORD 0 by any rotation/delay/force. Per the
pre-registered rule: single-position event retiming is MECHANICALLY DEAD.
Upgrades basin_merge's "jointly unsatisfiable" from code-reading to an
oracle-tested event-level theorem.

## Corrects the static review
Codex's static read (review 2) said {5,7,15} MISS the mask -> single pop
-> retimable (transfer valid). The TRACE + oracle show they HIT the mask
-> pair grab -> parity-locked (transfer invalid). Forcing the
f_get_two_free_regs call to single-reg empirically changes instruction
110, confirming the pair path. The prescribed run-the-oracle-to-decide
procedure is exactly what settled the static-vs-dynamic disagreement.

## WIP basin (v_base, lh v1 vs t2)
Not pursued — its residual is the ugen ilod->web collapse/coloring
decision (basin_merge Direction B: needs 7 zero-code interfering webs,
which don't exist), not free-queue event ordering. Racer's technique is
structurally inapplicable there too.
