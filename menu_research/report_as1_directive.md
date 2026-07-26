# func_8008FF1C — the `.noalias` directive mechanism

> # SOLVED — 2026-07-25
>
> `func_8008FF1C` **matches**. `FULLWORD_DIFFS: 0`, whole-ROM `Verify: OK`,
> SHA-1 `6d96743d46f8c0cd0edb0ec5600b003c89b93755`. `src/menu.c` now carries
> the C body; the `GLOBAL_ASM` fallback and the `NON_MATCHING` ifdef are gone.
>
> Three source facts, all discovered by the mechanism work in this report:
>
> 1. **Index the global array directly (`gTrackSelectRenderDetails[k]`) instead
>    of walking a `cur` pointer.** This is what lets `uopt` prove the `hubName`
>    store cannot alias `gTrackSelectIDs`, which makes `ugen` emit
>    `.noalias $17,$16`, which lets `as1` sink the store into the branch delay
>    slot. That was the whole two-instruction problem (§1–§4).
> 2. **Use the literal `-1` as the inner loop bound**, not the `startIndex`
>    variable. This gives `uopt` the inner trip count so the flat index
>    strength-reduces to a single advancing pointer at zero cost (§5, §7).
> 3. **Compute `trackY` as `trackSelectY + i + 1` at the top of the outer loop**
>    rather than assigning `trackY = trackSelectY` inside the inner loop with a
>    trailing `trackSelectY++`. This is what defeats §8's coupling — see below.
>
> Plus one ordinary codegen fix: **swap the operands of the final `|` in the six
> `copyViewPort` statements** so the masked-high-bits term is evaluated first.
>
> **§8's closure argument was wrong, and that is the useful lesson.** It claimed
> trip-count knowledge was necessary for a free direct-index base and
> sufficient to trigger a `trackY + 1` LICM hoist the target lacks, making the
> two mutually exclusive. The error was assuming `trackY + 1` had to be
> loop-invariant. Deriving `trackY` from the outer loop counter makes it affine
> in the outer induction variable, so `uopt` materialises it as part of the
> outer IV instead of hoisting and spilling it. The argument was falsifiable, it
> was stated as falsifiable, and the very next batch of experiments falsified
> it. §8 is retained below unedited as a record of the reasoning, with a
> correction note.
>
> Progression across the final batch, all at LEN 371/371:
>
> | variant | strict diffs | note |
> |:--|--:|:--|
> | `A1b_comm_ovar_direct` | 53 | window exact for the first time; residual all in the tail |
> | `C1_swap_arrows` | 28 | four arrow statements swapped |
> | **`C2_swap_all`** | **0** | the two corner statements swapped as well |

Status: 2026-07-24, later session. This report supersedes the mechanism
sections of `SESSION_HANDOFF_2026-07-24.md`. Sections 1–14 below were written
before the match and are preserved as the mechanism record.

Scope: `src/menu.c` only.

## 1. Headline

The residual is not "two registers". It is **one instruction in the wrong
slot**, and the compiler artifact that decides that slot has been identified,
isolated, and verified.

Adding a single directive to ugen's assembly output for the raw-condition
source produces the retail function exactly:

```text
menu_research/tools/as1_probe.py <work> noalias_17_16
  LEN 371/371  FULLWORD_DIFFS: 0   MATCH
menu_research/tools/as1_probe.py <work> control
  LEN 371/371  FULLWORD_DIFFS: 38  no match
```

The directive is `.noalias $17,$16` — load base versus store base.

## 2. What was previously not visible

The prior campaign instrumented `uopt` and `ugen` but never inspected the
assembly text between `ugen` and `as1`, and never built `as1` or `cfe`.
`cc -K` retains that text (`unit.s`), and `cc -S` emits it directly.

For the raw condition, ugen emits:

```asm
	sw	$2, 0($16)          # cur->hubName = levelName
	.noalias	$17,$sp
	lh	$10, 0($17)         # $10 == t2 is ALREADY correct here
	beq	$10, -1, $1128
	.alias	$17,$sp
```

Three facts follow immediately:

1. `ugen` emits the store before the load, so `uopt` did not reorder. The
   ordering decision is downstream.
2. `t2` is already the correct register in the raw basin. The `v_base`
   "two register flip" is a weaker, separate basin.
3. ugen *does* emit alias directives here, but only relates `$17` to `$sp`.
   `as1` therefore cannot prove `0($16)` and `0($17)` are disjoint, cannot
   sink the store past the load, and fills the delay slot with a `lui`
   hoisted from the else-block instead.

`as1` has no alias-related option (`strings` on the 5.3 binary yields only
`-g%d`, `-O%d`, `-mips2/3/4`, `-extsyms`). The directive is the only lever
into it.

## 3. `v_base` is a dead end, provably

`$10` belongs to ugen's integer expression-temporary FIFO
(`$8..$15,$24,$25`). `uopt` webs at this site are coloured from the disjoint
set `$2,$3,$4..$7,$16..$23,$30`. A named holder's web can therefore never be
coloured `$10`. No coloring pressure on the named-holder form can produce
`lh t2`. All effort belongs in the raw basin.

## 4. What produces the directive

Measured, in microcases and in the full translation unit:

- A **pointer variable** as the store base never produces the pair. This holds
  even when the pointer is assigned from `&garr[k]` immediately before use.
  At the load, the pointer form emits no directive at all.
- A **direct global array access** as the store base does produce the pair.

This is the D-class/P-class distinction from `report_construction_endgame.md`,
now visible as a concrete artifact rather than an inference.

Direct-indexing only the aliasing store (`gTrackSelectRenderDetails[k].hubName
= levelName;`, everything else on `cur->`) does **not** work: `uopt` allocates
a separate register for the direct address, yielding `.noalias $17,$20` and
379 words. Tested as `v_di_store_only` and `v_di_store_only_ij`.

## 5. Direct indexing is not inherently expensive

The prior campaign's "direct access costs +7" is an artifact, not a law. In a
microcase, the direct-index and pointer forms compile to **identical**
instruction streams — same registers, same count — and the direct form
additionally emits the pair.

The cost in the real function was traced to a single source construct: the
**variable lower bound** `startIndex`.

```c
startIndex = -1;
for (i = startIndex, cur = ...; i < 2; i++)
    for (j = startIndex; j < 2; j++, cur++)
```

`uopt` does not constant-propagate `startIndex` into the loop bounds. With an
unknown inner trip count it cannot prove how far the flat index advances per
outer iteration, so it cannot carry the derived pointer across the outer loop
and must re-derive the row base in the inner preheader:

```asm
lw    t5,124(sp)
lui   t9,%hi(gTrackSelectRenderDetails)
sll   t6,t5,2
subu  t6,t6,t5
sll   t7,t6,2
addiu t8,t7,-16
addiu t9,t9,%lo(gTrackSelectRenderDetails)
addu  s0,t8,t9
```

Isolated in a microcase: a literal bound gives no re-derivation; a variable
bound gives one. Confirmed with `-Olimit 20000` (not an optimizer limit).

## 6. Measured basin table

All rows use the raw condition. "pair" = `.noalias $17,$16` present.

| variant | outer bound | inner bound | store base | LEN | pair |
|:--|:--|:--|:--|--:|:--|
| `ptr_ovar_ivar` (raw baseline) | var | var | pointer | **371** | no |
| `ptr_ovar_ilit` | var | literal | pointer | 373 | no |
| `mix_ovar_ilit` | var | literal | direct | 373 | **yes** |
| `mix_olit_ivar` | literal | var | direct | 378 | yes |
| `di_ij` | var | var | direct (i,j) | 377 | yes |
| `di_counter` | var | var | direct (k) | 378 | yes |
| `lit_counter` | literal | literal | direct | 373 | yes |

With a literal inner bound, direct indexing is **free**: 373 both with and
without it. The literal bound itself costs +2.

## 7. The exact remaining two instructions

Diffing the two pointer forms — identical except the inner bound — the only
instruction-level difference is:

```asm
addiu t5,s3,1        # trackY + 1, hoisted out of the inner loop
sw    t5,88(sp)      # and spilled (frame 128 -> 176)
```

`uopt` performs loop-invariant code motion on `trackY + 1` only when it can
prove the inner loop executes at least once — i.e. only when the trip count is
known. That is the *same* fact that makes direct indexing free.

A diagnostic confirms the decomposition. Replacing `level_world_id(trackY + 1)`
with `level_world_id(trackY)` (semantically wrong, diagnostic only), with a
literal inner bound and direct indexing:

```text
LEN 371/371   .noalias $17,$16 present   FULLWORD_DIFFS: 54
```

Exact target length, with the required directive. The entire remaining cost is
that one hoist.

## 8. The closure argument — FALSIFIED, see the header

> **Correction (2026-07-25).** This section is wrong and is kept only as a
> record of the reasoning. Its hidden premise is that `trackY + 1` must be
> loop-invariant with respect to the inner loop. It need not be: computing
> `trackY = trackSelectY + i + 1` at the top of the outer loop makes the call
> argument affine in the outer induction variable, so `uopt` folds it into the
> outer IV rather than hoisting and spilling it. Trip-count knowledge and the
> absence of the hoist are therefore *not* mutually exclusive, and the function
> matches. Read the header first.

The retail function computes `addiu $a0,$s3,1` **inside** the inner loop,
immediately before `jal level_world_id`. There is no hoisted copy and no spill
of it anywhere in the 371 words.

Therefore, in the build that produced the retail object, `uopt` did **not**
know the inner loop's trip count.

But:

- an unknown inner trip count forces the row-base re-derivation, so a
  direct-index store base costs +6 to +7; and
- a pointer store base never yields the directive at all.

So within this compiler, the two requirements are mutually exclusive:

> Trip-count knowledge is necessary for a zero-cost direct-index store base,
> and simultaneously sufficient to trigger the `trackY + 1` hoist that the
> target does not contain.

Attempts to break the coupling, all measured, all negative:

| attempt | result |
|:--|--:|
| `j != 2` instead of `j < 2` | 373 |
| `trackY` assignment hoisted to the outer loop | 373 |
| `level_world_id(trackSelectY + 1)` | 373 |
| inner loop counting `0..3` with biased `trackX` | 373 |
| `j < startIndex + 3` (symbolic trip count) | 383 |
| `worldRow` as an explicit outer induction variable | 374 |
| `worldRow` as the sole outer IV, `trackY = worldRow - 1` | 374 |
| lean declaration set (pressure relief) | 373 |
| `-Olimit 20000` | unchanged |

Even in the best case the hoisted value would stay in a register rather than
spill, giving 372 — still not 371.

This closes the directive route. It does not close the `uopt`-reordering route
in general, but that route requires the same alias fact and the same D-class
store base, so it inherits the same conflict.

## 9. Tooling added

All under `menu_research/tools/`:

- `passrun.sh` — emit the pre-`as1` assembly (`cc -S`) with project flags.
- `tryfw_obj.py` — strict full-word scorer taking a prebuilt `.o`.
- `as1_probe.py` — edit the ugen listing, re-run `as0`+`as1`, rescore. This is
  the oracle harness that produced the `FULLWORD_DIFFS: 0` result.
- `dirprobe.py` — compile a variant with `-K`, report the alias directives at
  the load site plus the strict score. Accepts extra `cc` flags.
- `gen_directidx.py` — generate direct-index loop families.
- `qemu_irix.sh` — run the **original IRIX** `uopt`/`ugen` under `qemu-irix`
  in Docker and emit their listing, for differential testing against the
  static recompilation (§10.0).

Pass-replay recipe (control verified byte-exact on the function text):

```sh
cc -K -c <flags> unit.c -o unit.o     # keeps unit.s (listing), unit.G (binasm), unit.T
as0 -G 0 -EB -g0 -O2 unit.s -o X.G -t X.T
as1 -elf -G 0 -p0 -EB -g0 -O2 X.G -o X.o -t X.T
```

## 10. Toolchain closure

### 10.0 The `qemu-irix` differential — real IRIX binaries

This is the "truth experiment": run the *original MIPS IRIX* `uopt` and `ugen`
under `qemu-irix` and compare against the static recompilation. It was
previously listed as the strongest unexecuted test. **It has now been run.**

Setup: `qemu-irix` (Linux x86-64) under Docker `--platform linux/amd64` on an
arm64 host, with the original IRIX tree at `ido/5.3` as the `-L` root:

```sh
docker run --rm --platform linux/amd64 -v <qemu>:/q -v <ido5.3>:/irix -v <work>:/w -w /w \
  debian:bookworm-slim sh -c '
    apt-get install -y libglib2.0-0
    /q/usr/bin/qemu-irix -L /irix /irix/usr/lib/uopt -G 0 -EB -g0 -O2 unit.B U.O -t unit.T U.os
    /q/usr/bin/qemu-irix -L /irix /irix/usr/lib/ugen -G 0 -EB -g0 -O2 U.O -o U.G -l U.s -t unit.T -temp Utmp'
```

Results, comparing the `func_8008FF1C` body of the real-IRIX listing against
the static-recomp listing (excluding `.loc`/`.file`/source-comment lines):

| input | real IRIX vs recomp | alias directives (real IRIX) |
|:--|:--|:--|
| microcase `m_idx.c` | listing **identical** | `$17,$18` pair present |
| **`v_construct_raw` full TU** | **328/328 lines identical** | `$16,$sp`, `$17,$sp`, `$2,$sp` — **no `$17,$16`** |
| direct-index full TU (`mix_ovar_ilit`) | — | **`$17,$16` present** |

Two conclusions, both from the historical binaries rather than a
reimplementation:

1. **The static recompilation is faithful at this site.** Real IRIX `uopt` and
   `ugen` produce the identical instruction stream and the identical alias
   directives. The "the recomp is subtly wrong" escape hatch is closed.
2. **The mechanism is a property of the real compiler, not the recomp.** The
   pointer store base yields no pair and the direct store base yields the pair
   under the original binaries exactly as under the recomp.

(The `.O` ucode files differ in a leading header field between the two, but
the emitted assembly is identical, so the difference is not semantic.)

### 10.1 Static-recompilation fidelity (independent recomp builds)

Three *independent* static recompilations of IDO were run on the raw source
through the full project pipeline:

| toolchain | result |
|:--|--:|
| `tools/ido-recomp/macos` (project, == `ido-release-v12`) | 371 / FW 38 |
| `ido-release-v1.0` (different recomp build) | 371 / FW 38 |
| `ido-release-v1.1` (different recomp build) | 371 / FW 38 |

The 371 instruction words of `func_8008FF1C` are **byte-identical** across all
three. This substantially closes the "the static recomp is subtly wrong"
hypothesis without needing `qemu-irix`. It does not fully replace a real IRIX
differential, because all three descend from the same recompiler project.

### 10.2 `as1` binaries

Run directly on the *same* raw binasm (`unit.G`), so only `as1` varies:

| `as1` | result |
|:--|--:|
| project (`c2cc8b62`, community-circulated) | 371 / FW 38 |
| `IDO53-origAs1` (original/freeware 5.3) | 371 / FW 38 |
| `IDO52-full` | 371 / FW 38 |
| `IDO61-full` | 371 / FW 38 |
| `P260-as1` (patch 260) | 371 / FW 38 |
| `IDO51-full` | crashes in the recomp libc |
| `IDO71-full`, `IDO71-full2`, `IDO744-full` | reject 5.3 binasm |

**No `as1` binary sinks the store.** This answers the `as1` dimension of the
four previously-blocked pass-matrix cells: they are now runnable and negative.

### 10.3 `uopt` and `cfe` binaries

Full compiles of the raw source with one pass swapped, scored on the new
observable (reg-reg `.noalias` present? store before load?):

| toolchain | insns | reg-pair noalias | order |
|:--|--:|:--|:--|
| `CANON` (project) | 279 | none | `sw` then `lh` |
| `IDO52-uopt` | 278 | none | `sw` then `lh` |
| `IDO61-uopt` | 279 | none | `sw` then `lh` |
| `IDO71-uopt` | 279 | none | `sw` then `lh` |
| `IDO744-uopt` | 279 | none | `sw` then `lh` |
| `P1260-uopt` | 279 | none | `sw` then `lh` |
| `P1078-cfe` | 279 | none | `sw` then `lh` |

No available compiler binary emits the required alias fact.

## 11. Option-space closure

This answers reopen-criterion 3 with a binary-derived enumeration rather than
flag guesses. Option tables were extracted from the original IRIX binaries.

### 11.1 Which driver letters reach which pass

Measured with `cc -v`:

- `-Wf,` → `cfe`
- `-Wo,` → `uopt`
- `-Wa,` and `-Wb,` → **`as1`**
- `-Wu,`, `-Wg,` → silently dropped
- **no letter reaches `ugen`**

`ugen`'s options (`-cpalias`, `-nocpalias`, `-nooffsetopt`, `-notailopt`,
`-nounsignedconv`, `-align*`, `-domtag`, `-fp32regs`, …) are therefore
**unreachable from a legitimate build**. Direct invocation of `ugen` aborts,
because it needs an auxiliary `uopt` output that `-K` does not retain.

### 11.2 `uopt` (full table, screened)

```text
-regr -rege -nomultibbunroll -unrolllimit -loopunroll -Olimit -varref -trapuv
-fp32reg -strictIEEE -64data -dwopcode -mips1 -mips2 -mips3 -nokpicopt
-kpicopt -pic2 -mips4 -static -no_r23 -moremotion -fortran_lang -noPalias
-f77alias -createbb -nordstore -domtag -notail -nogenvreg -norecur
-docodehoist -no_const_in_reg -do_opt_saved_regs -noheurAB -norlodrstropt
-noprecolor -dowhyuncolor -doassoc -docopy
```

21 semantically relevant options were screened. **None** causes a pointer
store base to gain the alias pair. Notably `-noPalias` and `-f77alias` produce
**byte-identical output**, independently confirming `POSTMORTEM.md` §9.11.
`-docodehoist` was tested on the full translation unit and is worse
(raw 373, duplicated-store forms 375/373). `-Olimit 20000` changes nothing.

### 11.3 `as1`

`strings` yields only `-g%d`, `-O%d`, `-mips2/3/4`, `-extsyms`, plus the
driver-supplied `-elf -p0 -EB -G -o -t -pic0 -noglobal`. Sweeping
`-cpalias`, `-nocpalias`, `-O3`, `-nooffsetopt`, `-notailopt`, `-extsyms`,
`-domtag`, `-nogenvreg` on the raw binasm: **all 371 / FW 38**. `as1` has no
alias-control option.

### 11.4 `cfe`

18 options screened. Only `-Xvolatile` altered the alias directives, and on
the real translation unit it inflates the function to **589 instructions** by
suppressing optimization — a register-renumbering coincidence in the
microcase, not a real lead.

## 12. Additional source routes closed

### 12.1 Duplicated store + code hoisting

A route that needs **no alias fact at all**: duplicate `cur->hubName =
levelName;` into both arms of the `if` and let uopt hoist it into the
predecessor block, which places it after the load.

Measured: uopt does not hoist. It **sinks** instead, keeping `levelName` in a
register (`move $20,$2`) and storing separately in each arm.

| form | LEN | strict |
|:--|--:|--:|
| store first in both arms | 373 | 259 |
| store last in both arms | **371** | 104 |
| inverted condition | 371 | 178 |
| all three with `-Wo,-docodehoist` | 373–375 | 299–326 |

The store-last form is a genuine new 371-word basin, but the delay slot is not
the store. Route closed.

### 12.2 `volatile` on `gQMarkPtr`

Community suggestion. In the target, the else-block `lui %hi(gQMarkPtr)` is
*not* hoisted into the delay slot because the store occupies it; in the raw
candidate `as1` hoists that `lui` there instead. Making the qmark read
`volatile` was intended to block that hoist.

Measured: `*(char * volatile *)&gQMarkPtr` gives **372 words**, and the `lui`
is *still* hoisted into the delay slot — only the `lw` is volatile, the
address computation is not.

This is also settled by deduction: injecting `.noalias $17,$16` changes as1's
choice, so `as1` prefers the store *when legal*. It is rejecting the store as
illegal, not as less-preferred. Removing the competing candidate therefore
yields a `nop`, not the store.

### 12.3 The community `possibly_better.c` scratch

Its structural departures from the current decomp were tested individually:

- the store written inline, `cur->hubName = level_name(level_world_id(trackY
  + 1));`, with no `levelName` temporary;
- `trackY = trackCursorY + i` instead of a separate `trackSelectY` counter,
  with a dead `trackY++` in the outer `for` increment.

Both compile to **LEN 371 / FW 38 with the identical diff pattern** — that is,
byte-identical to `v_construct_raw`. These forms may well be closer to Rare's
original source (they are cleaner, and the dead `trackY++` is the kind of
artifact real source carries), but they do **not** change the compiler state at
this site. Its `vp1`/`vp2` bitfield decomposition of `copyViewPort` was not
tested because it requires a `src/menu.h` struct change affecting other
functions.

## 13. What is still open

Completed in this session, all negative: the `as1` pass-matrix cells (§10.2),
binary-derived option enumeration for all four passes (§11), and a
three-way static-recomp fidelity check (§10.1).

The `qemu-irix` differential against the original MIPS binaries (§10.0) was
also completed, and is negative: real IRIX `uopt`/`ugen` reproduce the static
recomp exactly on this function.

Genuinely not attempted:

1. **Instrumenting `as1`** (buildable via `ido-static-recomp`). It would
   confirm the delay-slot rejection reason directly rather than by inference,
   but §12.2 already establishes the rejection is legality-based, and §11.3
   shows `as1` has no lever. Low expected value.
2. **The `vp1`/`vp2` bitfield struct decomposition** from the community
   scratch (§12.3), which needs a `src/menu.h` change affecting other
   functions. It cannot affect the alias fact, but it does change how the
   `copyViewPort` block compiles, and that block is upstream of nothing
   relevant — so also low value.
3. **Non-`-O2` optimisation levels** combined with the direct-index form.
   Previously covered by `report_passmatrix.md` for the four principal source
   states, but not with the directive observable.

The single highest-value fact for any future session: **the target stream is
reachable from the raw source's own ucode by adding exactly one
`.noalias $17,$16` directive.** Any source form, compiler binary, or driver
option that emits that directive while leaving the inner trip count unknown is
an immediate, verifiable match. §8 argues those two requirements are mutually
exclusive in this compiler; that argument is the thing to attack.

## 14. Honest standing

No match was found. The best strict result is unchanged at 371 words with 2
differences (`v_base`, now known to be a terminal basin) and 371 words with 38
differences (`v_construct_raw`, one misplaced instruction).

What changed is the quality of the negative result. Before this session the
residual was "two registers, mechanism unknown, source space searched
broadly". It is now:

- one misplaced instruction,
- with the deciding artifact identified and verified by oracle,
- with the source-level requirement for that artifact measured,
- with the cost of that requirement traced to a specific construct, and
- with a stated conflict between two uopt facts explaining why no source can
  satisfy both.

That conflict is falsifiable. It is the correct target for any further work.
