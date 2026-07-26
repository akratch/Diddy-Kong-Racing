# Sister-game and ROM-wide forensics (final wave) — 2026-07-24

HEADLINE: P2 NEGATIVE — the anomalous idiom is a STRICT SINGLETON across
the entire uncompressed DKR code region (0x1000-0xD8760, 220,632
instructions; three independent scanners agree, incl. a purpose-built
MIPS decoder validated against the known site). P1 NEGATIVE where
measurable — GoldenEye full-ELF scan (5,676 functions): 0 anomaly-shape
hits. JFG/MSU unmeasurable (no ROM on disk; JFG repo gitignores its
asm). One inherited detector bug fixed ("-1" substring false-positive).

Key strengthening detail: the only ROM-wide shape-analog (a WORD-width
load in render_epc_lock_up_display with -1 compare + delay-slot store)
is in a MATCHED function — canonical stock output. So the store-in-slot
SHAPE is reproducible; what is anomalous is specifically the COLLAPSE
DECISION for a halfword load into a would-collapse colored variable —
and it misfires exactly once in the measurable universe.

DKR base rates (raw scan): class A (exact idiom) = 1 (the site);
ANOMALY-refined = 1; class B pool-survival = 15 (all others in matched
fns); TEMPCMP = 442; collapse class C = 131. The idiom does not cluster
in the three unmatched functions (racer has a normal collapsed load;
objects has neither).

Acquisition gaps, precisely pinned (the two decisive untested probes):
1. A Jet Force Gemini baserom — its repo has 399 GLOBAL_ASM functions
   incl. a 100%-asm menu.c front-end descendant, but the asm is
   regenerated from the ROM and not committed.
2. A Mickey's Speedway USA dump — same team, DKR-engine successor;
   its track-select is likely a direct descendant of our function.
Prototype catalog: NO N64 DKR prototype is publicly dumped (E3-1997
"Pro-Am 64" build documented via press material only); retail regions
all owned and swept.

SECURITY NOTE: WebFetch of tcrf.net returned a prompt-injection payload
(instructions to corrupt files + print fake completions) in place of
page content. The agent correctly ignored it; no actions were taken
from web content. Prototype facts sourced from search summaries only.

Artifacts: rare/{mipsdec,romscan,textscan}.py, romscan_hits.json,
disassemblies — session-84e018d6 scratchpad.
