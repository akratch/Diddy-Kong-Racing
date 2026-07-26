# Codex menu / plane re-attack log

Untracked working notes; do not include this file in a PR.

> **Current racer summary:** See `RACER_FINAL_MILE_HANDOFF.md` for the
> consolidated 2026-07-24 pause checkpoint. The natural racer result advanced
> beyond the entries in this chronological log to 20 localized GPR
> differences.

## 2026-07-23 — Plane: target frame and f20 promotion are jointly reachable

This corrects the key negative conclusion in `RACER_REATTACK.md`.

The previously tested promoted source used three existing float locals for the
three `ox2 * var_f20` products and compiled with a 256-byte frame. Removing one
unused four-byte declaration does not change that frame, which led to the
conclusion that the allocation basin was unreachable. Removing **two** unused
four-byte declarations crosses IDO's stack-alignment threshold:

- frame: 248 bytes (target 248)
- robust f20/f21 reference count: 69 (target 69)
- saved-register layout: f20/f21 at 32/36, s0/s1/ra at 44/48/52 (target exact)

This works for many pairs of unused declarations; it is not specific to one
magic pair. It proves that the target allocation fixed point is source
reachable and that the frame-size problem was an alignment artifact.

Initial promoted triple:

```c
racerVelocity = racer->ox2 * var_f20;
spCC = racer->oy2 * var_f20;
var_f0 = racer->oz2 * var_f20;
obj->x_velocity -= racerVelocity;
obj->y_velocity -= spCC;
obj->z_velocity -= var_f0;
```

Results after frame recovery and all recovered float suffixes, including the
conditional `spD4 = 0.02f`:

| Shape | Triple hosts | Frame | Insns | f20 refs | Raw | Normalized |
|---|---|---:|---:|---:|---:|---:|
| two-stage interpolation | racerVelocity, spCC, var_f0 | 248 | 2608 | 69 | 917 | 471 |
| direct interpolation | racerVelocity, spCC, var_f0 | 248 | 2628 | 69 | 914 | 454 |
| direct interpolation | spCC, var_f6, segmentXVelocity | 248 | 2628 | 69 | **892** | **454** |

Target instruction count is 2625. The net three-instruction count difference
is not localized: normalized diffing still shows broad register/scheduling
differences.

Best source currently saved at `/tmp/racer_host_best.c`. The sweep ledger is
`/tmp/racer_host_scores.log`. Reproducer is `.codex_late_sweep.py
score-hosts`.

### Float suffix confirmation

All five source tokens matter:

```c
spD4 = 0.01f;
spD0 = 0.02f;
spD8 = 0.004f;
if (racer->groundedWheels != 0) {
    spD4 = 0.02f;
    spD0 = 0.01f;
}
```

The first three suffixes alone gave 2609 instructions for the recovered-frame
two-stage candidate. Adding the conditional `0.02f` suffix reduced it to 2608
and improved the raw score from 953 to 917.

### Plane negatives closed in this session

- Reusing every candidate existing float local as the late `var_f20` web:
  promotion is lost.
- Reusing every candidate existing float local for the interpolation
  temporary: no target-frame promoted solution.
- Splitting early and late `var_f20` lifetimes: promotion is lost.
- Moving the three `spD4`/`spD0`/`spD8` initializations independently among
  five nearby anchors (125 combinations), without the product triple:
  zero promotions.
- Adding 1–24 dummy floating-point functions before `func_80049794`:
  no allocation change. The result is not translation-unit context leakage.
- `register`, scalar arrays, structs, unions, and volatile variants for the
  recovered float constants did not create the target allocation.
- Removing unused declarations one at a time does not recover the frame. This
  is expected and no longer evidence against reachability; two removals are
  required to cross the alignment boundary.

## 2026-07-23 — Menu: compiler-rule confirmation and new negatives

Reading the actual IDO implementation confirms the handoff's alias diagnosis:

- In C mode, a direct global-array load versus a loop-carried pointer store
  reaches `aliaswithptr` and is conservatively considered aliased.
- The C pointer base receives the catch-all memory tag.
- No usable `.noalias` pair is emitted for this load/store pair.
- The store-motion pass does not sink/hoist this ordinary indirect `storeop`
  into the required order.
- `gTrackSelectIDs` is writable and is assigned elsewhere; declaring it
  `const` is not legitimate and the local cast experiments do not change the
  alias result.

The exact target window remains:

```asm
lh    t2, 0(s1)
li    at, -1
beq   t2, at, else
 sw   v0, 0(s0)
```

The legitimate named-holder source has the exact instruction order and differs
only by `v1` versus `t2` in the load and branch.

### Menu negatives closed in this session

- Raw condition with `cur->hubName = levelName` as the first statement in
  **both** branches: IDO keeps branch-local stores and inserts `move v1,v0`;
  373 instructions, raw score 259. It does not common/hoist the stores.
- Store only in the raw condition's false branch: preserves the target t2
  load and almost all later allocation, but moves the store from instruction
  105 to 139. It is also semantically wrong on the true path.
- Store only in the true branch: broad mismatch.
- Conditional expressions returning the raw value from both arms: retain t2
  in some variants, but generate real branches/reloads; raw scores 266–296
  and 375–378 instructions.
- Mirroring the comparison to put the store-bearing comma expression on the
  left and raw load on the right: IDO still emits the store first. Raw score
  remains 39.
- Assignment chains, copies, nested self-assignments, comma assignments,
  `s16`/`u16` holders, and identity arithmetic/casts: no t2 named-holder
  allocation. Most exact-schedule forms use v1.
- Removing the otherwise dead historical `temp = (temp = ...)` statement
  changes later integer web numbering and causes about 134 raw differences.
  This dead-looking statement is therefore an important allocator-shaping
  fingerprint and must be retained until an exact replacement is found.
- Bitwise/comma, compound-assignment identities, `goto`, `restrict`,
  `#pragma ivdep`, local `const` casts, and direct indexed-store spellings
  remain negative as recorded by `.codex_menu_forms.py`.

### Tooling issue encountered

`tracehf.sh` requires both an absolute source path and an explicit trace-output
path. Calling it with only the source leaves the stderr redirection target
empty and reports `exit=1`; `/tmp/th.o` may then be stale. All subsequent
trace invocations pass both arguments and validate `exit=0`.

## 2026-07-23 — Plane: canonical recovered-source continuation

The plane results above this section were produced from the older
`/tmp/hf_base.c` line of attack. They independently prove that frame-248
promotion is reachable, but `RACER_REATTACK.md` §8 and
`/tmp/codex_racer_oracle.py` contain the cleaner, canonical recovered source.
All new work below uses that source:

```text
no pressure:
  frame=-240 insns=2653 f20/f21 instructions=0 f18 operands=3
  SHA1 prefix=500ef2fd6a02

target:
  frame=-248 insns=2625 f20/f21 instructions=69
  f0=131 f2=66 f4=188 f6=188 f8=187 f10=188
  f12=62 f14=50 f16=8 f18=190 f20=74 f21=2
```

The recovered source incorporates direct interpolation into `var_f14`,
`var_f14` immediately after `spD8`, all recovered float suffixes, and reuse
of `var_f0` for the obsolete `racerVelocity` range. This supersedes the older
source and score tables for choosing future experiments.

### New exact-count checkpoint

Holding the final `racer->unk34 * spD0` factor in the otherwise-dead `var_f2`
while retaining the known three-result `ox2` pressure form gives:

```c
var_f2 = racer->unk34 * spD0;
var_f20 = racer->unk34 * var_f2;
if (racer->unk34 < 0.0f) {
    var_f20 = -var_f20;
}
var_f20 += 4.0f * var_f2;
```

```text
frame=-248 insns=2625 f20/f21 instructions=69
f20 operands=74 f21 operands=2 f18 operands=35
SHA1 prefix=49e34230f468
```

This is the first recovered-source candidate with the target frame, target
instruction count, and exact promoted-register fingerprint simultaneously.
It is not a match: `spEC` is still globally colored in `$f18`, so the target's
five-register scratch equilibrium is absent.

The target ROM's final drag block remains inline and sequential. It does not
contain the three product temporaries. The product form is therefore an
allocator probe, not plausible recovered source.

### Allocator/source findings

- Opcode/operand-shape alignment between the recovered no-pressure object and
  target, after erasing physical register names, stack offsets, relocations,
  and branch destinations, matches 2,559 of 2,625 target instructions
  (96.97%). Most of the 28-instruction net count delta is caller-save spill
  traffic that disappears when the long factor reaches `$f20`; target adds
  only the four `$f20/$f21` prologue/epilogue instructions.
- `uoptreg2.c` confirms that constrained live ranges are selected by adjusted
  saving, then register choice is made by `cupcosts` plus the capped 60-unit
  first-use cost for a callee-saved register. The recovered factor is bit 279:
  `unk1C=81`, `adjsave=0.876543`, caller-save cost 21, forbidden mask `0xe0`,
  and it chooses reg 27 (`$f14`). The target-equivalent choice requires either
  a real `$f18` forbidden condition or caller-save cost above 60.
- Target `$f18` is demonstrably local scratch from the first FP block onward,
  while target `$f16` is used only eight times. Around the recovered constants,
  the candidate keeps `spD8` in `$f18`; the target keeps it in `$f16`.
- The target speed-magnitude block evaluates three component squares in
  separate registers and sums through `$f18`, but its opcode schedule is the
  same as the recovered source. Thus target `$f18` use there is an allocation
  consequence, not by itself proof of a different expression tree.

### Plane negatives closed on the canonical recovered source

- Replacing one of the three short drag-product webs with a held
  `unk34 * spD0` factor does not work: that factor dies before the drag
  products, so only two pressure webs overlap and promotion is lost.
- Four held-factor variants (`var_f2`, `racerBrake`, `racerThrottle`, and
  `segmentXVelocity`), both alone and combined with one earlier `var_f2`
  range merged into `spEC`, produced no correct topology. The brake/throttle
  variants often destroyed promotion entirely.
- Three axis-pair variants times four held-factor hosts (12 two-product
  forms) produced zero promotions. The non-overlapping factor lifetime cannot
  substitute for the third drag web.
- Moving the three constants before the speed magnitude, declaration
  initializers for `spD8`/`spD4`/`spD0`, label/goto/self/void separators,
  branch-phi definitions, duplicated deltas, one-iteration loops, and
  optimizer-neutral `spEC` self/CSE forms did not retain `spEC` in `$f12`
  while promoting the factor.
- Merging any whole earlier float (`racerBrake`, `racerThrottle`, `var_f2`,
  or `var_f14`) into `spEC`, or merging even one fresh `var_f2` SSA range into
  `spEC`, loses the target promotion. Explicit split campaigns likewise
  either leave the factor in `$f18` or globally color another web there.
- Reusing the factor source variable for the early wave `var_f0`, early wave
  `var_f2`, or steering divisor range does not improve caller-save economics.
  The early `var_f0` merge raises the factor's adjusted saving to 3.0, making
  it seize `$f14` earlier; all three merges and their combinations with every
  tested two-product host pair yielded zero promotions.
- All 18 permutations/associations of the three velocity-square terms in the
  `sqrtf` magnitude expression remained unpromoted. Right-association changes
  scheduling/hash but not the allocation basin.
- A full declaration-position sweep moved every float declaration to every
  declaration anchor: 697 compiles, 523 distinct object hashes, zero `$f20`
  promotions. Positions after the byte locals sometimes enlarge the frame to
  248 solely through padding; this is not promotion and not the target.

### External-source checks and issues

- The latest upstream `master` was fetched read-only; its intervening commits
  do not change either target function.
- All 43 GitHub forks returned by the upstream fork API were checked at their
  default branches. None contains an active/matching `func_80049794`; the
  three source variants found are the current non-equivalent source or older
  revisions.
- The linked decomp.me scratch `SlvtN` and its API endpoint currently return
  HTTP 403 from this environment, so no newer scratch state could be imported.

Reproducers for this continuation are `.codex_racer_recovered.py`,
`/tmp/codex_racer_oracle.py`, `/tmp/codex_base.trace`, and
`/tmp/codex_wavef0.trace`. Temporary `.codex_*` drivers are not intended for
the eventual PR and should be removed after their useful results are folded
into this ledger.
## 2026-07-23 — Forced-color isolation proves the plane bottleneck

- Built an isolated copy of the instrumented IDO recomp `uopt` and changed only
  the allocator's final choice for the 81-unit factor web (`unk1C == 81`) from
  `f14` to `f20`. This is an oracle experiment only; no repository compiler or
  source file was changed.
- Canonical recovered source, natural allocation:
  `frame=-240 insns=2653 f20i=0 f18=3 norm=998 sha=500ef2fd6a02`.
- Same source with only the factor color forced:
  `frame=-248 insns=2623 f20i=69 f18=188 norm=698 sha=a36cc9d662ca`.
- Target:
  `frame=-248 insns=2625 f20i=69 f18=190`.
- The forced build also exactly matches the target's `f20=74` total operand
  count. It automatically removes the unrelated global web that had occupied
  `f18`; no product-temporary source rewrite is needed to recover the target's
  scratch-register equilibrium.
- Conclusion: the remaining high-leverage plane problem is specifically the
  authentic source form that changes the 81-unit factor web's natural color
  from `f14` to `f20`. Once that happens, only two target instructions and 698
  normalized words remain, a substantially smaller structural cleanup.
- Allocator trace for the factor web:
  `forbidden=e0`, chosen `f14`, cost `21`, first-use cost `60`; the oracle forces
  `f20` at cost `60`. The current investigation is mapping each contributing
  basic-block register mask back to source lines so an equivalent source-level
  interference can be reconstructed.

### Additional failed plane attempts

- Tried a single reusable sequential drag-product temporary and two alternating
  reusable temporaries across the late drag block: 240 compiled variants, zero
  natural `f20` promotions. Best normalized distance was 978 but had 2655
  instructions, so this does not reproduce the target allocation or shape.
- Mnemonic-only comparison of the forced-factor object against the target
  matches 2,614 of 2,625 instructions. The remaining opcode-shape differences
  are localized to three source regions; the rest of the 698 normalized-word
  distance is predominantly the downstream register-color cascade.
- The first localized region strongly suggests a split buoyancy spelling:
  target loads `-1.0f` in the buoyancy branch delay slot and later subtracts
  `var_f2 / 10`, whereas the recovered source uses the single expression
  `var_f20 = -1 - (var_f2 / 10)`.
- Exhaustively tested 108 equivalent split spellings across three `-1`
  literal types, three divisor types, four seed placements, and three update
  forms (`-=`, explicit subtraction assignment, reversed addition). None
  naturally promoted the factor. Forms seeded only after the clamp optimize
  byte-identically to the canonical non-promoted source; earlier seeds change
  scheduling but leave the factor in a caller-saved register. The scheduling
  clue is still useful for eventual source recovery after the coloring trigger
  is found, but it is not that trigger by itself.
- A shell harness initially tried to assign to zsh's read-only `$status`
  parameter after a successful compiler invocation. This aborted only the
  reporting tail; the object and allocator trace had already been generated and
  were verified independently. Future harnesses use a task-specific result
  variable.

## 2026-07-23 — Final combined checkpoint and handoff

- Reconciled the parallel racer work. The strongest diagnostic is no longer
  the 2,623-instruction canonical forced object above, but the original-style
  source at `/tmp/codex_unused_spCC.c`.
- Natural stock result:
  `frame=-240 insns=2655 f20=0 f18=3 sha=c73ca5497d68`.
- Same source with only bit 279 forced to `f20`:
  `frame=-248 insns=2625 f20=74 f21=2 f18=186 sha=14d77d835190`.
- The forced object matches 2,619/2,625 target mnemonics in order. Its six
  opcode differences occupy only the buoyancy calculation and the
  trick-rotation copy relationship.
- This sharpens, but does not remove, the caveat: the stock compiler still does
  not naturally select `f20`. The result is a diagnostic proof of causality,
  not a matching source candidate.
- Created `REATTACK_HANDOFF.md` as the clean entry point for the next agent and
  appended final status sections to both `RACER_REATTACK.md` and
  `MENU_REATTACK.md`.
- No tracked source file was changed. No candidate is ready for a PR.

## 2026-07-23 — Plane structural completion and natural `0xfc` mechanism

- Recovered the exact buoyancy spelling: seed `var_f20 = -1.0f` before the
  stick/clamp work, then use `var_f20 -= var_f2 / 10`.
- Recovered the exact trick spelling in the `trickType == 1/-1` branch:
  snapshot `racer->x_rotation_vel` into `var_t0`, update the field with
  `(trickType * 0x600) * updateRate`, and use the snapshot for every later
  sign test.
- Combined forced diagnostic: 2,625 instructions and mnemonic distance zero.
- Recovered every stack home by declaring `var_f14` after `spE0`, `var_f20`
  after `spD0`, retaining a late unused `spCC`, and removing unused `pad3`.
  `/tmp/codex_struct_layout_exact_forced.o` has zero paired stack-offset
  mismatches against target and SHA1 prefix `a362e29e7365`.
- Stock `/tmp/codex_layout_exact.c` remains unpromoted:
  `frame=-240 insns=2655 f20=0 f18=3 sha=74981a591512`.
- Added node-389 live-range dumping to the isolated analysis uopt only. The
  exact source has factor bit 279 at `forbidden=e0`, `adjsave=0.901235`;
  blockers are the long `spEC` web in `f12`, an `ilod` in `f2`, and a
  conversion in `f0`.
- A four-stage `f64` spelling of the final `forwardVel` expression naturally
  produces `forbidden=fc` and selects `f20`:
  `d0=velocity*.05; d1=forward+d0; d2=d1*.125; d3=forward-d2; forward=d3`.
- This promoted object has the exact target non-`nop` opcode multiset; its
  only opcode-count excess is five `nop`s. It is not a match because the
  three retained double webs color before `spEC`, pushing `spEC` to `f18`:
  `frame=-264 insns=2630 f20=74/2 f18=35 sha=dfb7847254a6`.
- One/two/three-stage chains, all 24 declaration orders, register/volatile,
  array/struct/union, block-scope/initializer forms, 280 identity variants,
  existing-branch CFG forms, and explicit `spEC`-split combinations did not
  produce natural `f20` with scratch-like `f18`.
- The remaining allocator target is exact: keep `spEC`'s priority/color
  (`adjsave=.944444`, `f12`) while adding three lower-priority interferences
  that take `f14/f16/f18`, forcing bit 279 to `f20`.

## 2026-07-23 night — Menu: glass-box allocator characterization (Claude session 4)

Full detail in `MENU_REATTACK.md` §6. Summary of what changed:

- Built pre-as1 listing tooling (`klist.sh`/`utrace.sh` in the current session
  scratchpad `84e018d6.../scratchpad/menu/`) and read the emission for every
  key basin. The ll-mask mechanism, the in-place ll lo-add, the pair cycle,
  the $11 align-skip queue, and the trophies `and`→$11 rebind are now all
  directly observed rather than inferred.
- Scored all 215 historical variants in parallel (`ledger.json`): exactly two
  DIFFS-2 basins (v1-basin at line 102; addu-basin at line 110); nothing
  between 2 and 38.
- Nine new mechanism families tested and falsified (~35 new variants):
  goto/label block splitters (global rotation, 340), mask counts 1–6,
  u32/zero-extension forms, variable-free cast chains, dead-store sum
  carriers, trophies/index commutations, `long long` named holders (stack
  templocs), s32 chain-assign holders, and free-list burner statements
  (uopt DCEs register-derived dead code before ugen; memory-read burners
  collapse into webs or emit real loads).
- Re-ran the codex `cond-*` families with emission windows: the `|0`/`^0`/
  `+0` identities DO fold to `beq t2` on the raw pool temp, but uopt hoists
  the embedded store istr ahead of the condition — [sw][lh][beq]. 39 raw.
  Expression-embedded stores are conclusively closed.
- Impossibility arguments now cover the full constraint triangle; the
  two-diff floor is explained by ugen's free-list/pair-cycle/in-place
  conventions. Remaining nonzero-prior avenues are recorded in
  `MENU_REATTACK.md` §6.5 (instrument recomp ugen free-list; ugen point
  variants).

No tracked source was modified. The committed WIP remains the best honest
state at DIFFS: 2.

### Addendum (same session): instrumented-ugen free-queue proof

The recomp ugen was instrumented (env-gated `UGEN_FLTRACE`, byte-identical
otherwise; fidelity verified against the repo toolchain object) and free-list
traces were captured for base and zz1. Findings, detailed in
`MENU_REATTACK.md` §6.6: the temp pool is a FIFO free-queue seeded
[14,15,24,25,8,9,10,11,12,13]; the committed WIP's downstream is the unique
queue fixed point (its dead s16 burner's $10-before-$11 free order produces
the else-if registers; the trophies block pops the six oldest = 14,15,24,25,
8,9); the cast family's core/trophies requirements are provably contradictory
through one queue state; and the comma `cond-seq` forms already achieve the
exact target instruction order ([lh][li][beq][sw-slot], mnemonic-perfect),
reducing the entire floor to the web-collapse question. No zero-cost
collapse-blocker exists under this ugen binary. The most plausible account of
the shipped bytes is now a microscopic ugen point-variant difference over
plain natural source, not an exotic source spelling.

## 2026-07-23 late night — Menu: ugen-variant theory run to ground (two agents + synthesis)

Full detail: `MENU_REATTACK.md` §7; agent reports `report_oracle.md` /
`report_hunt.md` in the session-84e018d6 scratchpad `menu/`.

- ORACLE (agent 1): patched the recomp ugen at the single STR-to-register
  hint decision (f_eval, recomp label L42ec60), env-gated. The plain
  natural source scores **DIFFS 0** (371/371) under the site-signature
  gate — the §6.6 queue fixed point confirmed end to end. Collateral:
  narrowest gate still changes 11 other matched functions; broad gates
  28–113 (arg staging shares the code path).
- HUNT (agent 2): only ONE 5.3 ugen binary exists on disk (no CD/community
  split); no SGI patch ever shipped ugen (398 manifests swept; 1118 absent
  from both patch CDs); 5.1/5.2 ugen = byte-identical here and excluded by
  4-function collateral; 6.0/7.1/7.4.4 collapse MORE and change 52
  functions. 5.1 ugen made runnable for the first time (relocated-libc
  recomp).
- FALSIFICATION (synthesis): under any deferral gate, a direct `lh <web>`
  is unproducible from ANY source for gated sites; the matched menu.c
  object contains 67 such sites (20 with dest v1) → every uniform variant
  up to the narrowest "signed-16 into v1" rule is ROM-inconsistent.

Verdict: theory confirmed as oracle, dead as a uniform real compiler.
Surviving mass: context-dependent rule in an unobtained pressed-CD 5.3
ugen (as1 precedent keeps it alive); unconceived source construct; build
oddity. WIP at DIFFS: 2 remains the honest ceiling and the natural-source
oracle is the recommended public explanation of the residual.

## 2026-07-24 — Plane: canonical forced match and allocator-route closures

The strongest checkpoint is now `/tmp/codex_unk34_left_associative.c`.
Under the isolated diagnostic force-color switch it has all 2,625 target
instructions in order, the exact floating-register counts/sequences, and only
90 raw word mismatches: 39 constant-pool relocation addends plus 51 GPR
mismatches. Its forced SHA1 prefix is `0f5cd81b7383`.

With the stock allocator, the same source is:

```text
frame=-240 insns=2657 f20=0 f18=3 norm=875
sha1=28ae550756b5
```

The decisive allocator state is now fully characterized. The factor is the
`var_f20` web at address `-44`; naturally it is internal register 27 (`f14`),
cost 21. The target requires internal register 30 (`f20`), whose first-use
callee-save cost is 60. The target coloring sequence is factor `f20`,
`var_f14` `f14`, expression `f16`, with `f18` left as local scratch. The
natural sequence is factor `f14`, `var_f14` `f16`, and a later expression
web in `f18`.

New negative campaigns:

- 91 optimizer-erased factor uses placed in the real wave and wheel loops
  never raised the factor's caller cost or selected `f20`.
- 504 zero-expression pressure trees at the final stores produced 56
  promotions. The best 2,627-instruction cases promoted by globally coloring
  three velocity-load webs into `f14/f16/f18`, so target scratch allocation
  was impossible.
- 441 factor-use expressions around tail calls produced 42 promotions. Three
  cases had exactly 2,625 instructions and `f20=74`, but retained the same
  wrong global `f18` web (`frame=-248`, `f18=3`, `norm=898`). The extra calls
  raised the factor cost only from 21 to 27.
- All 15 partitions of the factor's four disjoint source regions among
  independent locals failed to select `f20`.
- Every distinct historical `func_80049794` body in local git history was
  extracted and transplanted into the same standalone translation unit. There
  are only six bodies; the four compilable forms all converge on the same
  unpromoted archive basin. Current upstream has no newer racer solution.
- A new isolated `CODEX_DUMP_ALL` allocator trace found no initially uncolored
  floating range already carrying the desired `0xfc` forbidden mask. That
  mask is created dynamically as earlier ranges receive colors.
- 1,638 one-pass loop topologies around the late landing call produced 728
  promotions. Explicit loops can reach exactly 2,625 instructions and the
  correct scratch-like `f18=192`, but retain loop mechanics and enlarge the
  frame. The best was `frame=-256`, `norm=1007`. Block forms whose mechanics
  optimize away revert byte-for-byte to the unpromoted canonical allocation.
  Thus the loop-frequency signal does not survive source-neutral loop removal.

Reproducers and full output are
`.codex_racer_existing_loop_factor_fake.py`,
`.codex_racer_tail_zero_pressure.py`,
`.codex_racer_tail_call_factor_use.py`,
`.codex_racer_factor_partition.py`,
`.codex_racer_history_eval.py`, and
`.codex_racer_landing_loop_topology.py`, with logs under `/tmp/codex_*`.
No tracked source or repository compiler was modified.

## 2026-07-24 — Plane: prepayment mechanism proved; direct natural seeds exhausted

- Built source-reachable `Qdt` prepayment cases. Six noninterfering ranges can
  make internal register 30 already-paid; an arithmetic-neutral double
  conversion or double negation in the existing wheel loop raises the factor
  above the competing ranges. Forty variants then choose factor `f20`
  naturally at cost zero.
- Best mechanism proof:

  ```text
  mut_double_r1_before
  factor reg=30 cost=0
  frame=-248 insns=2645 f20 operands=78 f18=0 norm=1595
  ```

  This is not a source candidate: the prepayment ranges globally consume the
  caller FP pool, so target-local `f18` scratch is unavailable.
- Existing-loop `Qdt` weighting can produce priority 40 / caller cost 80 and
  reach `f20`, but it overlaps the factor and pushes the factor to `f24`.
  A single `Qdt` spanning all available pre-factor calls reaches only cost
  11–12.
- Tested direct register/type routes: `register` is byte-identical; GCC
  asm-register spellings fail; the tested register pragmas are ignored; SGI
  IDO 5.3 exposes no fixed-register pragma; `long double` is byte-identical to
  `f64`; all complex spellings fail.
- Expanded the isolated allocator's `CODEX_DUMP_ALL` trace with per-register
  costs, dtype, and factor interference. Disabled-trace compilation remains
  byte-identical. Initial-range ranking:
  - `updateRateF` bit 4: caller cost 41, factor interference yes;
  - real zero constant bit 1267: caller cost 41, factor interference yes;
  - every other range with nonzero caller cost: factor interference yes;
  - every noninterfering range: caller cost zero.
  Thus no existing initial web can prepay `f20`; a new or materially
  retopologized lifetime is required.
- Localized the exact-FP forced object's 51 GPR residuals to wave loop (8),
  one branch operand (1), spinout rotation (11), and steering/tilt (31).
  Combining `steer:reuse+rotation` with a `var_v1` spinout-offset local
  preserves 2,625 instructions and exact FP while reducing the GPR residual
  to 43. The remaining spinout residual is a nine-word `v0`/`v1` swap.
  Explicit wave-count caching either removes one instruction or causes global
  allocation rotation and does not recover the target.

New artifacts:

```text
/tmp/codex_qdt_prepay_factor_priority_mut_double_r1_before.trace
/tmp/codex_racer_direct_f20_typeclass.log
/tmp/codex_racer_single_qdt_callspan.log
/tmp/codex_all_costs_v2.trace
/tmp/codex_unk34_forced_diff_exact.txt
/tmp/codex_racer_gpr_recovery.log
/tmp/codex_racer_gpr_topologies_v2.log
/tmp/codex_gpr_combined_001_spin_offset_var_v1.c
```

No tracked source was changed; the repository compiler remains untouched.

## 2026-07-24 — Plane: natural `f20` solved; GPR-only final mile

- The missing stock-compiler topology is a two-statement magnitude
  calculation:

  ```c
  var_f20 = (obj->x_velocity * obj->x_velocity) +
            (obj->z_velocity * obj->z_velocity) +
            (obj->y_velocity * obj->y_velocity);
  var_f20 = sqrtf(var_f20) - 2.0;
  ```

  Unlike the single `sqrtf(expression)` assignment, this joins the pre-call
  square sum and post-call factor into one long allocator web. It emits no
  additional instructions and naturally selects `f20`.
- The natural checkpoint is now:

  ```text
  source=/tmp/codex_gpr_natural_combined.c
  frame=-248 insns=2625 norm=45 sha1=29b6e852e795
  FP register counts: exact
  GPR-register words: 43 mismatches
  ```

  The previously observed 39 other raw-word differences are constant-pool
  relocation addends, not instruction differences.
- Replacing the steering clamp's saved `var_v1` with direct
  `obj->trans.rotation.x_rotation` uses gives the current natural best:

  ```text
  source=/tmp/codex_gpr_final_steer_direct_mz.c
  frame=-248 insns=2625 norm=42 sha1=150526a6f7b7
  FP register counts: exact
  GPR-register words: 42 mismatches
  ```

  This recovers the target scheduling and trades six local mismatches for five
  `v0`/`v1` color mismatches.
- The remaining natural GPR differences are localized to:
  - wave loop: 8 words (`v1` retained endpoint versus `a0` counter);
  - computer-player comparison: 1 reversed equality operand;
  - steering clamp: 5 `v0`/`v1` words in the direct-field form;
  - late rotation block: 19 words.
- Allocator traces explain the two clearest swaps. In the wave loop the local
  counter has priority 11.67 and is colored before the retained endpoint at
  priority 1.0. In the spinout block the offset local has priority 4 and is
  colored before the original rotation load at priority 2. The target requires
  the opposite physical roles.
- Closed natural campaigns from the 43-word checkpoint:
  - all equivalent equality spellings canonicalize to the same reversed
    `bne`; direct field use rotates hundreds of later allocations;
  - 144 existing-local wave hosts plus loop syntax, predecrement, and
    comparison variants do not improve the 43-word checkpoint;
  - 544 explicit original/offset host pairs and 122 nested spinout assignments
    either add an instruction or retain the swap;
  - steering statement-order permutations canonicalize; direct field use is
    the only improvement;
  - damping/update expression spellings do not improve the tilt block;
  - `register` on every single and paired integer local is byte-identical at
    IDO `-O2`.
- Reproducers and traces:

  ```text
  .codex_racer_sqrt_factor_input.py
  .codex_racer_gpr_natural_combined.py
  .codex_racer_gpr_final_campaign.py
  /tmp/codex_racer_sqrt_factor_input.log
  /tmp/codex_gpr_final_equality_v3.log
  /tmp/codex_gpr_final_wave_hosts.log
  /tmp/codex_gpr_final_wave_syntax.log
  /tmp/codex_gpr_final_steer_v2.log
  /tmp/codex_gpr_final_rotation.log
  /tmp/codex_gpr_final_spin.log
  /tmp/codex_gpr_final_spin_nested.log
  /tmp/codex_gpr_final_register_storage.log
  ```

### Natural spinout-offset breakthrough

- Starting from `/tmp/codex_gpr_final_steer_direct_mz.c`, putting the
  spinout offset in `var_v0` instead of `var_v1` is instruction-neutral:

  ```c
  var_v0 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
  if (var_v0 > 0x8000) {
      var_v0 -= 0xFFFF;
  }
  if (var_v0 < -0x8000) {
      var_v0 += 0xFFFF;
  }
  obj->trans.rotation.x_rotation += (var_v0 * updateRate) >> 4;
  ```

  This changes the shared direct `x_rotation` load web from `v0` to `v1` and
  gives the offset `v0`, exactly as the target requires. It removes all nine
  spinout differences and, through the shared field-load web, all five
  steering-clamp differences at once.
- The current natural stock-compiler checkpoint is:

  ```text
  source=/tmp/codex_gpr_final_spinoffset_var_v0.c
  frame=-248 insns=2625 norm=28 sha1=8ea0281b4084
  exact FP register counts; 28 GPR-register mismatches
  ```

  The residual is wave loop 8, computer equality 1, and late rotation 19.
- A diagnostic-only allocator priority sweep proves the wave target is obtained
  by coloring the retained `gRacerWaveCount - 1` range between the endpoint
  range (priority 12) and counter range (priority 11.6667). Adding 10.67 to
  that retained range's priority removes all eight wave differences and leaves
  exactly the equality and late-rotation residuals. This is evidence about the
  source topology required; it is not used in any accepted build.
- Additional natural campaigns from the 28-word checkpoint closed:
  equivalent equality/subtraction/XOR spellings; erased wave-loop expressions;
  external wave-loop empty conditions; 60 original-style
  steering/spinout/damping topologies; 1,015 empty-fake placements; and 103
  integer identity forms. None improves 28. Scanning 26,568 same-size objects
  from all retained campaigns found no accidental exact late-rotation region.
  The best historical local rotation score is 16 words, but those objects have
  hundreds of differences elsewhere.
- New reproducer and logs:

  ```text
  .codex_run_gpr_diag.sh
  .codex_scan_object_regions.py
  /tmp/codex_gpr_final_spin_offset_hosts_direct42.log
  /tmp/codex_gpr_final_wave_erased_base28.log
  /tmp/codex_gpr_final_wave_priority_base28.log
  /tmp/codex_gpr_final_equality_base28.log
  /tmp/codex_gpr_final_original_topology_base28.log
  /tmp/codex_gpr_final_fake_placements_base28.log
  /tmp/codex_gpr_final_integer_fake_base28.log
  /tmp/codex_scan_rotation_v2.log
  ```

No tracked source was changed; all accepted measurements use the ordinary
isolated compiler. The instrumented compiler is used only to report allocator
priorities and colors.

## 2026-07-24 — Plane: post-sqrt pressure graph isolated

- A direct field-pressure campaign after the factor's first definition tested
  1,590 variants without promotion.
- A five-value input/sum bridge across `sqrtf` promotes naturally. The best
  form has `frame=-248`, `insns=2641`, exactly 69 factor instructions and
  `f20/f21=74/2`, but `f18=3`. Fresh block/function locals reproduce the
  allocation with a 272-byte frame, proving the later scratch loss is caused
  by the pressure topology rather than reuse of broad locals.
- Moving the pressure after `sqrtf` avoids call spills. Four independent
  fields suffice; the smallest representative is 2,636 instructions with a
  272-byte frame. In 316 existing-local samples, 14 promote, but all activate
  a dormant stack home and remain at a 248-byte frame.
- Allocator traces make the mechanism exact. The baseline factor has forbidden
  mask `0xe0` and chooses internal 27 (`f14`) for cost 21. Four short ranges
  color internal 25–28 and shift another interfering range to 29. The factor
  then has mask `0xfc`, leaving only fresh callee-save `f20` at cost 60.
  Promotion is therefore caller-pool saturation, not factor-web merging.
- Explicit double intermediates do not compress the mechanism: a `f64` range
  occupies one allocator color. Forty-six mixed `f64`/`f32` forms still need
  four independent ranges.
- Thirty-five `sqrtf` assignment splits/intermediate-local forms canonicalize
  to the unpromoted baseline or worsen it. One hundred twenty-six real
  downstream-definition hoists retain a 240-byte frame and can raise `f18`
  usage to 107, but none promotes. Factor identity swaps and regional
  partitions also remain unpromoted.
- New logs:

  ```text
  /tmp/codex_racer_sqrt_bridge_pressure_v2.log
  /tmp/codex_racer_postsqrt_pressure.log
  /tmp/codex_racer_postsqrt_existing_pressure.log
  /tmp/codex_racer_sqrt_assignment_topology.log
  /tmp/codex_racer_real_hoist_pressure.log
  /tmp/codex_racer_sqrt_f64_topology.log
  /tmp/codex_racer_factor_identity.log
  /tmp/codex_base_all.trace
  /tmp/codex_postsqrt36_all.trace
  ```

No tracked source was changed; the repository compiler remains untouched.

## 2026-07-24 — Menu: backward ucode-level closure (final experiment, opus agent)

Enumerated stock ugen's full f_eval dispatch (152 opcodes) for zero-cost
non-collapse RHS shapes and their C-reachability. Result: EMPTY. The
unique zero-cost defer shape (identity int->int Ucvt, func_436008
move-only path) is deleted by cfe before ucode exists (byte-identical
object proof); every surviving Ucvt pays a pair/sll-sra/FPU cost; every
non-Ucvt root collapses or emits real code. The four win conditions are
jointly unsatisfiable over C-reachable shapes — the source leg is now
CLOSED at the opcode level (immune to the racer-style family-enumeration
failure). Sole survivor for a stock DIFFS 0: pressed-CD 5.3 ugen with a
context-dependent collapse rule. Report archived at
menu_research/report_ucode_enum.md; MENU_FINDINGS.md §8 updated with the
outcome. Campaign concluded; WIP at DIFFS 2 is the proven canonical
ceiling.

## 2026-07-24 — Menu: pressed-CD test executed (online survey agent) — NEGATIVE, campaign fully closed

Obtained the pressed retail "IRIS Development Option 5.3" CD (jrra.zone
EFS image, joist/5.3MR) AND SGI's Sep-1997 freeware tardist. Both carry
compiler pass sets byte-identical to the community baseline — ugen
9fcff937 in all three. Hypothesis 2 (pressed-CD ugen variant) is dead by
direct test. Side-finding: three distinct 5.3 as1 builds catalogued
(pressed/freeware 807808; community-git 816064; bk patchSG0001118
904272). Remaining residue is untestable (undistributed hot-fix, pre-MR
pressing not in any index, build oddity). Full report:
menu_research/report_online_survey.md; MENU_FINDINGS.md §9 added.

## 2026-07-24 — Cross-revision ROM sweep (user-supplied dumps) + parallel-wave close

All five retail variants (US v77/v80, PAL v1.0/Rev1, JP) carry the
anomalous lh t2 + addu t4 form BIT-IDENTICALLY modulo relink (0 hard
diffs in the function, all revisions). JP shows structural churn ~1KB
from the function → menu.c genuinely recompiled for JP, anomaly
reproduced. Build-fluke account DEAD; survivors: persistent
DKR-build-machine toolchain difference (Rare-internal hot-fix) or
unconceived deterministic source construct. Full wave synthesis in
MENU_FINDINGS §11-§12; five agent reports archived in menu_research/.

## 2026-07-24 — Menu construction endgame and deliberate pause

Resumed from `menu_research/MENU_HANDOFF_FOR_CONSTRUCTION.md` and attacked its
three remaining soft routes with mechanism-first constructions.

- Retained-direct alias state: redundant address seeds create no memory-state
  event; direct pointer/byte round trips remain visible; a real direct store
  followed by an equal `cur=&g[k]` does not coalesce or transfer state.
- Flat direct induction can reach the exact local `lh/li/beq/sw` window,
  correcting the old universal +7 theorem, but cannot preserve the target
  nested-loop induction/allocation graph. `trackY+1` becomes an `s8`
  recurrence; non-`Uadd` identities cost real instructions.
- Live 32-bit-index/pair constructions converge on a 371-word FW3 state at
  `(106,107,109)` across post-call, cross-call, carrier, entry-pointer,
  multiply, and arithmetic-stage families. No match.
- Fixed-frame producer closure survives outer boundary tests: `const`, scope,
  and parameter reuse all remain FW133.
- `#pragma noalias`, `#pragma distinct`, `__restrict`, `-noaliasok`,
  `-noPalias`, and external/`static` global linkage do not change the
  optimizer decision.

A documentation replay reverified 12,675 late-family cases through the
entry-pointer family. A redundant replay of the 6,480-case stage-split family
was stopped intentionally at the documentation boundary; its prior result and
downstream scripts remain archived. No compiler or tracked game source was
changed.

Safe-point assessment: further syntax/mask/declaration sweeps are now
wheel-spinning because they revisit characterized normalized states. The
result is a strong mechanism-level stopping point, not an all-C proof.

Final records:

```text
menu_research/SESSION_HANDOFF_2026-07-24.md
menu_research/report_construction_endgame.md
menu_research/POSTMORTEM.md
```
