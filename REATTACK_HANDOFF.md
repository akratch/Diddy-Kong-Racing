# Menu and racer re-attack handoff

Status at 2026-07-23. This is an untracked research handoff and is not part of
any PR.

> **Racer status superseded:** The authoritative 2026-07-24 plane-physics
> checkpoint is `RACER_FINAL_MILE_HANDOFF.md`. Natural stock-compiler progress
> continued from the 28 GPR differences described below to 20 differences:
> one wave-loop backedge register and nineteen late-rotation temporary
> registers. Use the newer document for current metrics, theories, and
> follow-on work.

## Executive verdict

Neither function is ready for a matching PR.

- `func_8008FF1C` (menu) is at a rigorously established two-instruction floor.
  The checked-in WIP is otherwise byte-exact. The remaining conflict is between
  the source form that gives the target's pool temporary (`t2`) and the source
  form that gives the target's load/store order.
- `func_80049794` (plane/racer) now naturally reproduces the target's
  2,625 instructions, 248-byte frame, and complete floating-point register
  histogram with the stock compiler. The decisive topology is a separate
  assignment of the velocity-square sum to `var_f20` before
  `var_f20 = sqrtf(var_f20) - 2.0`. The remaining differences are 28
  localized GPR-register words; it is a source solution for the former
  `f20` blocker, but not yet a matching function.

No tracked repository source was changed during this attack. The handoff docs,
experiment drivers, and ledger are untracked.

## Canonical files to read

Read these in order:

1. `REATTACK_HANDOFF.md` — this executive handoff.
2. `RACER_REATTACK.md` — complete racer history, allocator model, corrections,
   campaign counts, and graveyard.
3. `MENU_REATTACK.md` — menu reduction and compiler-law analysis.
4. `CODEX_REATTACK_LOG.md` — chronological continuation, including failures and
   tooling issues from the latest attack.

The older notes in the scratchpad are useful evidence, but any statement that
conflicts with the four files above is superseded. In particular, early
`f18` counts that did not require a literal `$` were invalidated and are
already called out in `RACER_REATTACK.md`.

## Racer / plane: `func_80049794`

### What is recovered with high confidence

The best source line incorporates:

- direct interpolation into `var_f14` (no `segmentZVelocity` copy);
- the recovered `f` suffixes on `spD4`, `spD0`, and `spD8`, including the
  conditional `spD4 = 0.02f`;
- the original-style early `racerVelocity` local in the strongest diagnostic
  family;
- removal/reuse of genuinely unused float declarations to cross IDO's stack
  alignment threshold without changing behavior.

The recovered float tokens are not cosmetic. IDO keys parts of the literal
pool on source tokens, so `0.01` and `0.01f` may create distinct pool entries
even when folded to the same value.

### Canonical diagnostic checkpoint

The strongest kept pair is:

- source: `/tmp/codex_unused_spCC.c`
- natural object: `/tmp/codex_unused_spCC.o`
- forced-color object: `/tmp/codex_unused_forced_spCC.o`
- allocator trace: `/tmp/codex_unused_forced_spCC.trace`
- target: the `TARGET` path in `/tmp/codex_racer_oracle.py`

Metrics:

| Build | Frame | Instructions | `f20` operands | `f18` operands |
|---|---:|---:|---:|---:|
| Natural diagnostic source | 240 | 2,655 | 0 | 3 |
| Same source, only factor forced to `f20` | 248 | 2,625 | 74 | 186 |
| Target | 248 | 2,625 | 74 | 190 |

The forced object has 2,619 of 2,625 target mnemonics in the same order.
All six mnemonic differences reduce to two source regions:

1. The buoyancy calculation. The target loads `-1.0f` in the buoyancy branch
   delay slot and later subtracts the `/ 10` result. The recovered source
   expresses this as one late calculation:

   ```c
   var_f20 = -1 - (var_f2 / 10);
   ```

   The likely source family seeds `var_f20` earlier and then uses `-=`.

2. The trick-rotation block. At target instruction index 1215, the target has
   `move t0,v1` after loading `racer->x_rotation_vel`; the diagnostic eliminates
   that relationship and continues testing `v1`. The relevant source is around
   the `trickType == 2 || trickType == -2` path and the preservation of the
   pre-update rotation value.

This is the basis for calling the function structurally close. It is not a
claim of byte closeness: physical-register and branch-offset cascades still
produce hundreds of raw word differences.

### The allocator result that changed the problem

The long normalization/drag factor is live range/ichain bit 279:

```text
unk1C=81
adjsave=0.876543
total saving ~=71
natural forbidden mask=0xe0
natural choice=reg27/f14 at cost 21
first callee-save cost=60
target choice=reg30/f20
```

Forcing only this range to `f20` is sufficient to:

- recover the 248-byte frame;
- reproduce the target's exact 69 instructions touching `f20/f21`;
- reproduce the target's 74/2 `f20/f21` operand counts;
- return `f18` to the local scratch pool automatically.

This proves the broad downstream register mismatch is a consequence of one
allocator choice. It also confirms that adding a long-lived `f18` source web is
the wrong model: target `f18` is scratch spread across the function.

The factor is live through 43 basic blocks. Source-line instrumentation shows
the maximum natural local mask at node 389, corresponding to the final
`unk34` drag plus `forwardVel` update; it is `0xe0`. A natural source solution
must make `f14/f16/f18` unavailable or equivalently more expensive to bit 279
without leaving a global value parked in `f18`.

### What is proven, and what is not

Proven:

- The target allocation fixed point is internally consistent.
- One factor color explains the frame, saved-register layout, and scratch
  equilibrium.
- Source-level three-product pressure can naturally produce the same `f20`
  fingerprint, proving the allocator mechanism is reachable.
- The target's final drag remains inline and sequential; explicit three-product
  temporaries are diagnostic pressure, not plausible target source.

Not proven:

- A stock-compiler source form that naturally colors the factor to `f20` while
  retaining target structure.
- That correcting the two remaining opcode regions will also trigger the
  natural color. Allocator transitions are discontinuous.
- That an exact match is one small edit away. The evidence justifies a focused
  final-mile attack, not a PR promise.

### Important negative campaigns

Do not repeat these without a new mechanism:

- 1,365 existing-local triples across the three drag blocks; every promotion
  had the wrong global `f18` occupant.
- 2,730 ordered host permutations; same wrong equilibrium.
- All two-product host pairs, including explicit `spEC` split variants:
  promotion either fails or the factor stops at `f18`.
- 2,240 split-spelling/two-result combinations; no promoted result with
  target-like scratch `f18`.
- 697 float declaration placements, producing 523 object hashes; no natural
  `f20`.
- All tested direct/block/const `f32` and `f64` interpolation formulations.
- `register`, scalar arrays, structs, unions, volatile, declaration
  initializers, labels/gotos, one-iteration loops, self/CSE expressions, and
  constant-placement variants.
- All 18 associations/permutations of the velocity-square magnitude.
- Reusing or merging the early wave, steering, brake, throttle, interpolation,
  `spEC`, and factor ranges.
- Single reusable and alternating late drag temporaries: 240 variants, zero
  promotions.
- 108 split buoyancy spellings over literal type, seed placement, divisor
  type, and update form: zero natural promotions. These were tested on the
  canonical natural source and still remain useful to retry only after the
  allocator trigger is independently solved.
- Latest upstream and all 43 discoverable GitHub forks contain no newer
  matching implementation. The decomp.me scratch `SlvtN` returned HTTP 403.

See `RACER_REATTACK.md` §§8.6–8.8 and `CODEX_REATTACK_LOG.md` for the exact
counts and discriminating objects.

### Reproduction map

Scratchpad root:

```text
/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad
```

Primary tools:

- `/tmp/codex_racer_oracle.py` — isolated compile, disassembly, register
  histogram, normalized score.
- `/tmp/isoeval.sh` — stock isolated compiler wrapper.
- `/tmp/codex_run_analysis.sh` — instrumented/forced compiler wrapper.
- `/tmp/codex_racer_forced_matrix.py` and
  `/tmp/codex_racer_forced_matrix.log` — forced diagnostic factorial matrix.
- `/tmp/codex_racer_merge_matrix.py` and
  `/tmp/codex_racer_merge_matrix.log` — source-local merge matrix.
- `/tmp/codex_racer_trace_compare.py` — allocator assignment summaries.
- `.codex_racer_recovered.py`, `.codex_racer_webs.py`, and
  `.codex_late_sweep.py` — broader source campaigns.
- `/tmp/codex-uopt-analysis.x6ld1B` — instrumented uopt source/build.
- `/tmp/codex-ido-analysis` and `/tmp/codex-ido-factor.vxlzef` — isolated
  compiler copies. Never replace the repository compiler with these.

Quick stock checkpoint:

```sh
python3 /tmp/codex_racer_oracle.py
```

The force-color experiment is an oracle only. Any candidate intended for a PR
must be recompiled with `/tmp/isoeval.sh` or the repository's ordinary build
and must naturally select `f20`.

### Highest-value next racer attack

1. Start from `/tmp/codex_unused_spCC.c`, not an older product-triple source.
2. Recover the exact trick-rotation copy relationship while checking both the
   natural allocator trace and the forced diagnostic. The desired local
   signature is the target's `move t0,v1` followed by later sign tests on
   `t0`.
3. Recover the buoyancy seed/subtract statement order against the forced
   diagnostic. Use opcode order, not a broad raw score, as the first oracle.
4. After each structural correction, remove the force and inspect bit 279's
   forbidden mask. A useful result must move `0xe0` toward `0xfc` without
   creating a resident `f18` web.
5. Only after a natural `f20` result, do full raw-word and repository build
   validation.

Kill criterion: if exact recovery of both structural regions leaves bit 279 at
`0xe0` under the stock compiler, the remaining problem is not localized to
those visible opcode differences. Return to source-level live-range topology;
do not polish forced-color register renumbering.

## Menu: `func_8008FF1C`

### Exact current state

The committed WIP is byte-identical except for two instructions:

```asm
ours:   lh   v1,0(s1)
        ...
        beq  v1,at,else

target: lh   t2,0(s1)
        ...
        beq  t2,at,else
```

The target window is:

```asm
jal level_world_id
jal level_name
lh  t2,0(s1)
li  at,-1
beq t2,at,else
 sw v0,0(s0)
```

The target simultaneously requires:

- raw-expression consumption so the value is a ugen pool temp (`t2`);
- the load to occur before the `hubName` store so the store fills the branch
  delay slot;
- no 64-bit temporary pair that perturbs the following index registers.

Every tested C family satisfies at most two of these.

### Compiler rules now confirmed from source

The earlier `MENU_REATTACK.md` plan asked the next agent to read the actual
compiler rules. That work is complete:

- In C mode, the direct global-array load versus the loop-carried `cur` pointer
  store reaches the conservative pointer-alias path.
- The pointer store receives the catch-all memory tag.
- No usable `.noalias(load, store)` pair is emitted. The available
  load-versus-stack noalias relation is insufficient.
- as1 does not move this load across the store without that noalias relation.
- The ordinary indirect store is not commoned/hoisted into the needed order by
  the examined uopt store-motion/tail passes.
- `gTrackSelectIDs` is writable, assigned in `menu.c`, and not a legitimate
  `const`/rodata escape hatch.

The raw-condition plus identical first stores in both branches was also tested.
uopt retained branch-local stores and introduced a move; it did not common
them into the predecessor.

### Menu graveyard

Do not repeat:

- named, shadowed, copied, or differently sized holders: exact schedule but
  `v1`, never `t2`;
- dead-web pressure, declaration reorder, or dummy register variables;
- 64-bit all-ones masks: can buy `t2` but leave a live pair that breaks the
  following index allocation;
- raw condition with the store before, inside one branch, or duplicated in
  both branches;
- assignment chains, nested/self/comma expressions, ternaries, compound
  assignments, bitwise identities, casts, `restrict`, `#pragma ivdep`, goto,
  inline noalias text, or direct indexed-store spellings;
- local `const` or volatile pointer casts;
- re-deriving `cur` from the global array, which adds index work or perturbs
  `s0`;
- removing the odd historical `temp = (temp = ...)`: despite looking dead, it
  changes later allocation and causes roughly 134 raw differences.

### Menu reproduction

Primary oracle:

```text
<scratchpad>/menuwork2/try.py <variant-file>
```

Success is `DIFFS: 0`. The target is
`<scratchpad>/menuwork2/target.o`; the base is
`<scratchpad>/menuwork2/base.c`.

Broader reproducer:

```sh
python3 .codex_menu_forms.py
```

The stock best remains the checked-in WIP at `DIFFS: 2`.

### Highest-value next menu attack

Treat this as a compiler/source-provenance problem, not another arithmetic
spelling sweep. A new attack should begin only with a mechanism that can
explain both target facts at once:

1. a source topology that causes uopt to evaluate the raw condition before the
   pointer store while emitting one store;
2. a way to preserve/recover symbol provenance for the loop-carried store with
   no target-visible index code; or
3. evidence of a compiler behavior not represented by the current recomp.

Kill criterion: absent one of those mechanisms, `DIFFS: 2` is the honest hard
floor. Do not replace the matching WIP with a semantically dubious branch-only
store or an inline assembly workaround.

UPDATE (2026-07-23 night): a fourth session characterized the wall
mechanistically from pre-as1 listings — the floor is caused by ugen's
free-list/pair-cycle/in-place-ll-add conventions, and each of the three
near-miss basins (v1-holder, ll-mask addu, cast-form 56) is blocked by a
distinct, C-invariant ugen invariant. Nine further mechanism families were
tested and falsified, and all 215 historical variants were re-scored into a
single ledger. See `MENU_REATTACK.md` §6 for the model, the impossibility
arguments, the new graveyard, and the only remaining nonzero-prior avenues
(instrumenting the recomp ugen's free list; ugen point variants).

## PR readiness and cleanup

- No candidate in this handoff is PR-ready.
- Do not commit the instrumented compilers, forced objects, `.codex_*` campaign
  scripts, or the handoff markdown unless the project explicitly wants research
  notes in version control.
- Before a real PR, require a stock compiler result, byte comparison against the
  target, the normal project build, and a clean diff containing only the
  recovered source changes.
- The current worktree has only untracked research files from this effort; no
  tracked source edits were made.

## 2026-07-24 racer addendum

The racer checkpoint has advanced beyond the earlier structural summary.
Use `/tmp/codex_unk34_left_associative.c` as the canonical source. Its isolated
force-color build has 2,625 instructions and exact target FP sequences/counts;
the stock build is `frame=-240`, `insns=2657`, `f20=0`, `f18=3`,
`norm=875`. The only forced-build raw differences are 39 constant-pool
relocation addends and 51 GPR words.

The exact remaining issue is the factor web's 21-versus-60 register cost:
natural `f14` versus target callee-saved `f20`, while preserving `f18` as
scratch. Tail pressure, tail-call fake uses, factor-region partitioning,
existing-loop fake uses, all historical bodies, and 1,638 late-call loop
topologies have been exhausted. Several variants reach exact instruction count
and `f20=74`, but only by globally occupying `f18`; explicit weighted loops
that preserve scratch leave mechanics and larger frames. Full results are in
`RACER_REATTACK.md` §11 and the 2026-07-24 entry of
`CODEX_REATTACK_LOG.md`.

### Later 2026-07-24 addendum

The hypothesized callee-save-prepayment path is now proven but still not
target-shaped. Six noninterfering double ranges can prepay internal register
30, and a neutral factor use in the existing wheel loop can raise the factor
enough to claim the prepaid `f20` at zero cost. Forty cases do so naturally;
the best is 2,645 instructions with `f20=78`, but it globally eliminates
`f18` scratch and is diagnostic only.

Direct seeds are now tightly closed. `register`/pragma/fixed-register syntax
does not bind an IDO FP register; `long double` collapses to `f64`; complex
types are rejected; and one double range spanning all pre-factor calls costs
only 11–12. A full initial-range cost/interference trace found that the only
41-cost ranges (`updateRateF` and the shared real zero constant), plus every
other range with nonzero caller cost, interfere with the factor. Every
noninterfering range costs zero. Any honest prepayment solution must therefore
change a lifetime or control-flow topology; there is no dormant existing seed.

The exact-FP forced residual is also fully localized. The current combined
best is `/tmp/codex_gpr_combined_001_spin_offset_var_v1.c`; focused topology
changes reduce 51 GPR mismatches to 43 without changing the instruction count
or FP match. The residual is 8 wave-loop words, 1 reversed branch operand, 9
spinout `v0`/`v1` swap words, and 25 steering/tilt words. Explicit wave-count
caching is closed: clean forms optimize one instruction short, and
retained-cache forms rotate allocation globally.

Use `RACER_REATTACK.md` §12 and the latest `CODEX_REATTACK_LOG.md` entry for
the detailed artifacts and kill criteria.

### Post-`sqrtf` allocator addendum

A five-value input/sum bridge across `sqrtf` and a four-value post-call bridge
both promote the factor naturally with its exact 69 instructions and 74
`f20` operands. They are diagnostic only: the former is 2,641 instructions
with a 248-byte frame; the latter is at best 2,636 instructions with a
272-byte frame. Existing-local forms still activate a dormant stack home and
remain at 248 bytes.

The promotion mechanism is now explicit. Four short ranges occupy internal
caller-save colors 25–28 and shift another factor-interfering range to 29,
changing the factor's forbidden mask from `0xe0` to `0xfc`. It must then take
fresh callee-save internal 30 (`f20`) for cost 60. The mechanism saturates the
same caller pool needed for target-local `f18` scratch; it does not merge or
raise the factor web.

Do not repeat direct post-definition fields, post-call aliases, explicit
`f64` compression, `sqrtf` statement splits, real downstream hoists, or factor
identity swaps. These campaigns comprise more than 2,100 new source variants
and are recorded in `RACER_REATTACK.md` §13 with reproducible scripts/logs.

### Natural-factor and GPR addendum

The post-`sqrtf` pressure hypothesis is superseded by an exact, neutral source
topology:

```c
var_f20 = (obj->x_velocity * obj->x_velocity) +
          (obj->z_velocity * obj->z_velocity) +
          (obj->y_velocity * obj->y_velocity);
var_f20 = sqrtf(var_f20) - 2.0;
```

With the earlier structural recoveries this compiles naturally to the target
frame, instruction count, and exact FP register counts. The canonical natural
checkpoint is `/tmp/codex_gpr_natural_combined.c` (43 GPR-register
mismatches). The current best is
`/tmp/codex_gpr_final_spinoffset_var_v0.c` (28), which combines direct
`x_rotation` field loads in the steering clamp with `var_v0` as the spinout
offset host.

Residual GPR words are localized to wave loop 8, computer equality 1, and
late rotation 19. A diagnostic priority adjustment proves the exact wave
ordering: the retained count range must color after the endpoint range and
before the counter range. Equality spellings, wave loop syntax and
existing-local hosts, steering statement orders, damping spellings, hundreds
of spinout host/nesting forms, original-style topology combinations, over a
thousand empty-fake placements, integer identities, and `register s32`
declarations are closed. Start new work from the 28-word natural source and
use `.codex_racer_gpr_final_campaign.py`; see `RACER_REATTACK.md` §14 and the
latest `CODEX_REATTACK_LOG.md` entry.
