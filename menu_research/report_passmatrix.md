# Compiler-pass Cartesian matrix + declaration/aggregate families — 2026-07-24

TL;DR: func_8008FF1C is BYTE-INVARIANT to every runnable cfe/uopt/as1
combination (8 cells; 4 patchSG0001118-as1 cells blocked — no IRIX
original exists on disk, the bk file is a Linux recomp). Scores constant
everywhere: v_natural 133, v_base 2, v_scratch 2, raw 38 (legacy ==
fullword). The elevated raw x patchSG0001260-uopt cell: no change.
Collateral only ever ADDS broken functions and is strictly additive,
which PINS the DKR toolchain: retail cfe (887eced2), retail 5.3MR uopt
(f4ef4f08), COMMUNITY-GIT as1 (816064) — the pressed-CD original as1
breaks 3 matched functions, so Rare used the community-git build.

Task B (18 declaration/aggregate/holder variants, previously-absent
family): five forms preserve the exact signed lh at zero collateral and
every one still collapses to v1 (133); all collapse-dodging forms cost
stack homes (145+) or pointer rotation (150). Mutually exclusive, swept.

Task A2: instrumented uopt exposes no transform-disable toggles;
sweeping its coloring-frequency knobs never defers the load (133 in all
settings) — the deferral decision is confirmed downstream of uopt
coloring, in ugen's f_eval dest hint.

Recomp provenance table and natives in the report body; gotcha logged
(macOS realpath needs pre-touched -o target). Repo toolchain verified
byte-unchanged at end.
