# func_80049794 ("plane physics"): MATCHED

**Result (2026-07-24): score 0. The function compiles from C to bytes
identical to the ROM; the `GLOBAL_ASM` stub is removed and the full
repository build produces a ROM byte-identical to the original
(sha1 `6d96743d46f8c0cd0edb0ec5600b003c89b93755`).**

The last 19 register-only differences were closed by hoisting one shift
into its own statement at the top of *each* arm of the final `R_TRIG`
if/else, so that IDO allocates and releases that temporary before the
damping statement's temporaries:

```c
if (!(gCurrentRacerInput & R_TRIG)) {
    var_t0 >>= 1;
    obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
    obj->trans.rotation.x_rotation -= ((var_t0 * 19) * updateRate) >> 1;
} else { /* ... * 30 ... */ }
```

The decisive step was a forced register-choice experiment: patching
`ugen` to impose the original's 22 register picks made the existing
source match byte-for-byte, proving the C was already structurally
correct and reducing the problem to reproducing one allocation order.
Solving the allocator's event structure for that order gave a unique
answer, which the statement split realizes.

The historical narrative below is retained as the record of how the
result was reached.

---

# (historical) from unmatched giant to a 19-instruction residual

Status: DRAFT (2026-07-24). Working document for the community-facing
write-up. Current best NATURAL result: **2625/2625 instructions, 2606
byte-exact, 19 register-only differences** compiled with the canonical
IDO 5.3 toolchain. This function is DKR's largest and was the subject of
a long-standing (ex-$50-bounty) matching mystery.

## 0. Versus the public state of the art

The best public community attempt (decomp.me scratch `SlvtN`, listed at
score 4837 / 98.16%) matches **551 of 2,625** instruction words when
measured against the real target object. This work matches **2,606 of
2,625 (99.28%)**. The public scratch never achieves the `f20` promotion
(zero `f20`/`f21` operands); see `DECOMPME_COMPARISON_2026-07-24.md` for
the full head-to-head.

## 1. Headline results

- Frame (248 bytes), instruction count (2625), and the complete
  floating-point register allocation — including the notorious `f20/f21`
  promotion — are reproduced naturally from C.
- The wave-loop region, including a backedge register that survived
  ~15,000 automated variants, is matched. The decisive levers were a
  direct `var_a0 >= 0` guard, a once-run dead double-assignment
  (registers as a real allocator-visible use, emits nothing), and three
  optimizer-erased loop-body tests.
- The 19 remaining differences are a pure register permutation in one
  if/else (two trick-rotation update arms). No opcode, immediate,
  branch, or count differences remain anywhere.

## 2. The f20 breakthrough (why the "impossible" analysis was wrong)

An earlier analysis proved f20 promotion impossible for *any* source
under the canonical compiler, given the observed live-range costs. The
flaw: costs are per-web, and the two-statement form

```c
var_f20 = (x*x) + (z*z) + (y*y);
var_f20 = sqrtf(var_f20) - 2.0;
```

merges the pre-call input and post-call factor into one long web whose
economics differ from every one-statement spelling. The impossibility
proof was correct for the webs it measured — the winning source changes
which webs exist.

## 3. The measured allocator (what we now know about IDO 5.3 ugen)

Established with an environment-gated instrumented recompile of the
original ugen binary (byte-identical output when disabled):

- Integer expression temps (t3-t9 here) live in a strict FIFO free
  queue: allocation pops the head, the temp's last use appends to the
  tail.
- Outcome depends only on the append ORDER, never timing (measured:
  deferred-flush policies produce byte-identical objects).
- Multi-use/CSE'd values never enter this queue; they are routed to a
  separate register class (v0/v1/a*/t0-t2). The FIFO class carries
  exclusively single-use scratch.
- Free order therefore equals ucode consumption order, which is fully
  determined by the statement dataflow trees.

## 4. Why the last 19 instructions resist

The target requires a temp free order that our (byte-identical-emitting)
ucode cannot produce:

- entering the region, the target queue is a non-cyclic permutation of
  ours — reachable only by delaying one specific release upstream
  (proven sufficient-for-entry by a surgical oracle patch);
- inside the arms, the target frees the `var_t0 >> 1` temp first and
  holds the result temp to the final store, while the mandatory
  store+reload between the two field updates forces our tree to free in
  allocation order.

Falsified routes (each with full experiment logs in this directory):
expression-level lifetime constructs; 13 structurally distinct arm
respellings (identical dataflow graph after IDO canonicalization); all
5040 entry-queue permutations; named-local webs (destroyed by
value-based copy propagation); free-timing compiler policies (FIFO
invariance); every obtainable alternate IDO pass (uopt 6.1/7.1/7.4.4,
patch uopts, cfe patches — residual invariant; older passes break the
whole function).

## 5. Cross-function significance

The sibling investigation of `func_8008FF1C` (menu, 2-instruction
residual) independently concluded its residue is a ugen temp free-order
anomaly. Two unrelated functions whose only unmatched bytes trace to
free-order behavior of the code generator is evidence for a systematic
toolchain-level difference in the original DKR build — all publicly
obtainable IDO 5.3 ugen binaries (community, SGI freeware, and the
pressed retail 5.3 CD) are byte-identical, so any such difference is in
an undistributed build.

## 6. Closure (2026-07-24, end of campaign)

Every genre is now closed with evidence:

- type/idiom respellings (~30 variants): semantically-neutral forms are
  byte-identical inert; queue-movers reflow the downstream uncontained,
  while the target's perturbation is absorbed — no source-expressible
  contained shift exists;
- a formal enumeration of every append/remove/defer path in ugen's
  allocator found exactly one theoretical no-emit deferral path (a
  FIFO-class node with use count 2 drained by a memoized consumer), and
  positive-control microcases prove IDO's uopt never feeds it: every
  shared subexpression is materialized into uopt's own specific
  registers before ugen;
- an independent silent-construct sweep concurs: across the entire
  function, every FIFO temp has use count exactly 1; zero deferred
  releases exist.

Conclusion: the 19-instruction residual is not reachable from C with any
obtainable IDO 5.3-era toolchain. It is a contained free-order property
of the original build's code generator — the same conclusion reached
independently for the menu function. The best-known source is preserved
in `src/racer.c` under `#ifdef NON_EQUIVALENT` (ROM verifies byte-exact
with the guard off).

Unturned stones: the decomp.me scratch family for this function
(https://decomp.me/scratch/SlvtN — Cloudflare-walled from CLI; needs a
browser check for newer community forks), and any physically new IDO
binary surfacing.

## 7. Reproduction

- Source checkpoint: `checkpoints/func_80049794_best_19_clean_arms.c`
  (equivalently `..._best_19_wave_win.c`; byte-identical objects)
- Verifiers: `tools/raw_compare.py` (raw instruction words — the true
  metric: 2606/2625) and `tools/verify_candidate.py` (normalized:
  insns=2625, norm=19, sha1=e95892dd53eb)
- Instrumented ugen + oracle env flags: `ugen_trace_build/README.md`
- Full session evidence: `TRACE_FINDINGS_2026-07-24.md` and the
  campaign notebooks in this directory.
