# Sister-ROM deep interpretation: MSU + JFG (final wave) — 2026-07-24

HEADLINE: no sister-game site is a second instance of the DKR anomaly.
Both Mickey's Speedway USA and Jet Force Gemini fingerprint as
IDO-lineage 5.3-CLASS output (decisive marker: the byte-identical IDO
division macro bne;break — zero real teq guards anywhere; every teq hit
was compressed-data misdecode). MSU compiled -mips2 (like GoldenEye),
JFG -mips1 (like DKR) — compile-flag differences only. So these were
the RIGHT ROMs to test H1 persistence — and the anomaly's defining
conjunction appears ZERO times across ~2.7MB of additional 5.3-class
Rare code.

PREMISE CORRECTION (durable erratum to the campaign's "laws"): the
briefing claimed stock 5.3 always emits li at,-1 adjacent to its beq
and never hoists raw-condition loads. FALSE — that is as1 LOCAL
SCHEDULING, present in all IDO versions: DKR's own 5.3 output contains
56 non-adjacent at/-1 compares (distances up to 29 instructions) and
~53% of div guards split. The idealized single-function laws omit as1
scheduling; sister-hit adjudication must use measured behavior. (This
does not affect the DKR-site conclusions: the F2 wall is about crossing
a POINTER store without .noalias, which stands; sp-stores are
schedulable and always were.)

THE MSU 0x1893c6c WINDOW ADJUDICATED: menu-descendant code walking a
-1-terminated table, but a RAW condition — the loaded value is not
reused (the fall-through RELOADS it); the intervening stores are all
sp-based (noalias, schedulable). Stock 5.3 reproduces the shape (DKR
has it 56x). Not a collapse decision at all. All other MSU hits: div
divisor false-positive, and one struct-copy CSE family comparing to a
RUNTIME value (not -1). JFG: zero strict hits in either region.

The anomaly needs ALL FOUR ingredients simultaneously: signed lh into a
pool temp + a would-collapse (web-homed, reused) value + the -1
sentinel + survival across a POINTER (non-schedulable) store. Each
ingredient is individually common (DKR: 98 -1-compares, 4 reused
temps); the conjunction occurs exactly once in the measurable universe:
DKR 0x9116c.

Compressed code: both sister ROMs store their complete code image
uncompressed (two regions each; the remaining ~28-30MB is Rare's
hand-rolled gzip-variant ASSETS — not stock-inflatable; caveat noted
that a compressed code overlay cannot be 100% excluded).

SINGLETON NOW STANDS ON FOUR GAMES: DKR + GoldenEye + MSU + JFG, all
IDO 5.3-class, one anomalous collapse decision in ~5MB+ of code.
Tooling added: fingerprint suite (fp/fp2/divdump/sched/idiom/win .py)
in session-84e018d6 scratchpad rare/.
