# Brief: testing the "ugen variant" theory for func_8008FF1C (DKR decomp)

## The theory being tested

The DKR menu function `func_8008FF1C` is 2 instructions from matching:
ours `lh v1,0(s1) ... beq v1,at`, target `lh t2,0(s1) ... beq t2,at`
(t2 = $10). Everything else in the 371-instruction function is byte-exact.

We have proven (see MENU_REATTACK.md §6 in the repo root, esp. §6.6):

- ugen (IDO 5.3 code generator) allocates expression temps from a FIFO
  free-queue seeded [14,15,24,25,8,9,10,11,12,13]: GET pops the head, a
  value's death refrees its reg to the tail.
- The target's entire downstream register pattern is the unique fixed point
  of that queue GIVEN that the branch-feeding load `lh` is emitted as a POOL
  temp (popping $10) rather than collapsed into the named holder's colored
  web (v1). Stock ugen collapses `var = load;` into `lh $web` directly.
- The natural source (`selectedTrack = gTrackSelectIDs[trackY][trackX];
  cur->hubName = levelName; if (selectedTrack != -1)`) compiles to the
  known "133 basin": lh v1 + whole downstream rotated one queue position
  down. If ugen instead emitted `lh $pool10; move $web,$pool10` (the move
  is dissolved by as1, so ZERO extra bytes), the queue math predicts the
  EXACT target, with no source tricks at all.

Hypothesis: Rare's toolchain had a ugen point variant (different patch/CD
revision) whose ilod-into-web collapse triggers differently (or whose queue
behaves microscopically differently), and the original source is the plain
natural form.

## Key paths

- Repo: /Users/adamkratch/Desktop/dev/Diddy-Kong-Racing (do NOT modify
  tracked files; all work in scratchpads)
- Old scratchpad (large infra):
  /private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad
  (call it $OLD). Contains: menuwork/ (scoring harness), hunt/ (SGI CD
  extraction + ido-static-recomp infra: recomp_one.sh, run_candidate.sh,
  swextract.py, efsextract), ido-recomp-pub/ (recomp source build, ugen.c
  instrumented with env-gated UGEN_FLTRACE logging — byte-identical when
  env unset, fidelity verified), ido-traced*/ (full native 5.3 toolchains).
- Current scratchpad: .../84e018d6-3923-40cd-a174-5850defac48f/scratchpad/menu
  (call it $MENU). Contains: klist.sh (compile a variant with -K, keep
  pre-as1 .s), utrace.sh (ucode listing via traced toolchain), kwork_*/
  (ready-to-compile kcand.c copies), fltrace2_{base,zz1}.txt (free-queue
  traces), ledger.json, this brief.
- Canonical repo toolchain: $REPO/tools/ido-recomp/macos (native macOS
  recomp binaries: cc, ugen, uopt, as1, ...).

## Scoring harness (the only oracle that matters)

```
cd $OLD/menuwork
python3 try.py v_natural.txt     # prints DIFFS: N  (0 = MATCH)
```

try.py builds a full menu.c TU from base.c + the variant file, compiles it
with the REPO toolchain via compile.sh, and compares mnemonic+register
streams of func_8008FF1C against target.o. To test an ALTERNATE toolchain,
copy $OLD/menuwork/compile.sh, point its cc path at the alternate toolchain
dir, and either temporarily swap compile.sh or replicate try.py's logic
(source construction: see build_src() in $MENU/score_all.py, which is
standalone). kwork_base/kcand.c in $MENU is a prebuilt full-TU source for
the WIP shape; you can also generate the natural shape by deleting the line
`temp = (temp = gTrackSelectIDs[trackY][trackX]);` from it.

Variants to score against each candidate ugen:
1. v_natural.txt (predicted original; stock score 133)
2. v_base.txt (committed WIP; stock score 2)
Success = DIFFS 0 on either.

## Fidelity + collateral rules (mandatory)

- Any patched/swapped toolchain must first reproduce the STOCK object
  byte-identically with the feature disabled / on a control compile, to
  prove the harness itself is sound.
- If a candidate produces DIFFS 0 on func_8008FF1C, immediately check
  collateral: the same compile's OTHER menu.c functions must still match
  the shipped ROM. Practical check: compile the UNMODIFIED src/menu.c
  (GLOBAL_ASM path intact — actually use the base.c TU with the v_base
  variant, which reproduces the committed state) under the candidate and
  raw-word-diff the whole .text of the object against the repo-toolchain
  object; report how many OTHER functions changed. A true positive changes
  only func_8008FF1C (or nothing else that is currently matched).
- Report every negative precisely: candidate identity (path, md5), what was
  tested, scores.

## Report format

Markdown table: candidate | provenance | md5 | v_natural DIFFS | v_base
DIFFS | collateral summary. Plus a short findings narrative. Write your
report to $MENU/report_<yourtask>.md AND return it as your final message.
