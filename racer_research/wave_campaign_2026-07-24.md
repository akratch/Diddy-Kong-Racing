# Wave-loop backedge campaign — index 72 (`bltz a0` vs `bltz v1`)

Task: eliminate diff index 72 in func_80049794 without introducing new diffs
outside {1656,1667,1682-1691,1701-1709}. Baseline checkpoint
`func_80049794_best_20.c`: insns=2625 norm=20 sha1=ebfa69e218fc,
indices include 72.

## Pipeline notes
- verify_candidate.py must be given an ABSOLUTE path to the .c (isoeval cd's into
  work-racer, so relative source paths silently "COMPILE FAILED").
- objdump: work-racer/tools/binutils/mips64-elf-objdump.
- Instrumented trace: `.codex_run_gpr_diag.sh src.c out.o trace.log`
  (must invoke via `bash`, exec bit fine). Priority lines: `RACER-COLOR ... adjsave=P uses=U`.

## Disassembly of the wave region (baseline vs target)
Baseline (invariant guard `(gRacerWaveCount-1) >= 0`) matches the target register
for register across the WHOLE wave region EXCEPT index 72:
  target  [72]: bltz a0,148
  cand    [72]: bltz v1,148
Baseline coloring == target coloring exactly: endpoint=v1, addr-ptr=v0,
counter=a0. Only the backedge tests the endpoint (v1) instead of the counter (a0),
because the loop's integer termination condition is the endpoint invariant.

## Key mechanism (measured)
Three integer live ranges compete for {v0=$2, v1=$3, a0=$4}:
  - endpoint  = gRacerWaveCount-1 (def at 54; used guard/init/bne)  -> target v1
  - addr-ptr  = gRacerCurrentWave[var_a0] self-stepping pointer     -> target v0
  - counter   = var_a0 decrementing                                 -> target a0
Register allocator priority for the endpoint LR = adjsave = N/uses with N=2
(constant; = adjsave*uses stayed 2.0 across all loop-body test counts).
So endpoint priority takes only DISCRETE values 2/uses.

Switching the guard from the endpoint invariant to `var_a0 >= 0` (any equivalent
form) makes the backedge test the counter (semantically correct) but ROTATES the
3-way coloring off identity. Adding empty `if (gRacerWaveCount-1){}` tests in the
loop body raises the endpoint's `uses`, lowering its priority in 2/uses steps:
  - uses=17 (E=3, prio 0.11765): counter WRONG (a0 not counter), v0/v1 RIGHT  -> 8 diffs
  - uses=18 (E=4, prio 0.11111): counter RIGHT (72 = bltz a0!), v0/v1 SWAPPED -> 14 diffs
The db3->db4 trace diff shows EXACTLY ONE color line changes (endpoint LR bit=1257,
uses 17->18) and it reorders past a stack slot (bit=218, addr=-48). That single
reorder flips BOTH the counter assignment AND the endpoint/addr-ptr assignment.
=> counter-fix and v0/v1-swap are COUPLED at one threshold. Both competitor
priorities sit inside the open interval (2/18, 2/17)=(0.1111,0.1176); the endpoint's
2/uses quantum skips the whole interval, so no integer loop-body count lands the
identity permutation.

## Near-miss saved
`checkpoints/func_80049794_wave_E4_counterfix.c` = direct guard + 4 loop-body
endpoint tests. Index 72 = `bltz a0` CORRECT, counter role fully correct
(59,71,72,83 match), but endpoint<->addr-ptr are a clean v0/v1 swap
(no spills, insns=2625). norm=33, extra=[50,51,53,54,55,56,61,62,73,74,85,86,88,89].

## Families tried (all with direct/counter guard unless noted) — outcomes
| family | result |
|---|---|
| empty endpoint tests BEFORE loop (weight 1) | no effect (deleted before freq acct) |
| empty endpoint tests AFTER loop (weight 1)  | no effect (deleted) |
| empty endpoint tests in post-`if` body      | n=1 no effect; n>=2 worse (spills) |
| endpoint tests in LOOP BODY (E-sweep)       | E<=3 counter-wrong/v0v1-right; E=4+ counter-right/v0v1-swap. COUPLED. |
| endpoint x raw-gRacerWaveCount body tests   | raw dilution breaks its own load (50,51,53) |
| endpoint x counter (var_a0) body tests      | counter dilution reverts counter fix, worse |
| guard operand variants (>=0,>-1,!(<0),0<=)  | all identical to `var_a0>=0` |
| combined conditions (inv && ctr && fl etc)  | invariant operand emits a real branch -> insns=2628 |
| real endpoint refs (post compound, spA2, comma update) | change insns or shift everything; `var_a0=var_a0-1` update identical to base |
| loop structure: while                       | identical coupling to for |
| loop structure: do-while / manual peel      | different rotation, insns change, huge norm |

## *** SOLVED — index 72 eliminated (norm 20 -> 19) ***
Coordinator lead #1 (dead double-assignment from the sibling menu campaign) is the key.
Winning source `checkpoints/func_80049794_best_19_wave_win.c`:
```c
if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->vehicleIDPrev != VEHICLE_WIZPIG && gRacerWaveCount != 0) {
    var_t9 = (var_t9 = gRacerWaveCount - 1);         // dead double-assign into dead-slot local var_t9
    for (var_a0 = gRacerWaveCount - 1;
         var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {
        if (gRacerWaveCount - 1) {}                   // 3 empty endpoint tests in loop body
        if (gRacerWaveCount - 1) {}
        if (gRacerWaveCount - 1) {}
    }
    if (var_a0 == gRacerWaveCount - 1) { var_a0--; }
    ...
```
STOCK verify_candidate.py output:
```
insns=2625 (target 2625)
norm=19
indices=[1656, 1667, 1682, 1683, 1684, 1685, 1687, 1688, 1689, 1690, 1691, 1701, 1702, 1703, 1704, 1706, 1707, 1708, 1709]
fp={f0:131,f2:66,f4:188,f6:188,f8:187,f10:188,f12:62,f14:50,f16:8,f18:190,f20:74,f21:2}
sha1=e95892dd53eb
```
Index 72 now = `bltz a0` (matches target exactly). No new diffs outside the allowed
rotation set. Frame size unchanged (addiu sp,sp,-248). var_t9 was a fully-dead local
(declared, never referenced) so the double-assign emits ZERO instructions but registers
a real extra endpoint use at the uopt level.

Ingredients (both required):
  1. direct guard `var_a0 >= 0` (makes the backedge test the counter -> `bltz a0`).
  2. `var_t9 = (var_t9 = gRacerWaveCount - 1);` once-run before the loop.
  3. exactly 3 empty `if (gRacerWaveCount-1){}` tests in the loop body.
Together they place the endpoint LR so the 3-way {v0,v1,a0} coloring lands on the
identity permutation. Notably the measured endpoint adjsave stayed N=2/u=17 (0.1176) —
the double-assign's effect is NOT a clean N=2->3 numerator bump as hypothesized; it
perturbs the interfering dead-slot/stack-slot allocation order (the bit=218 reorder
partner) so the endpoint no longer trades places with the addr-ptr. The empty-test
count (3) and the double-assign together were both necessary: neither alone wins
(dead-tmp double-assign with n=2 -> norm 27; n=3 -> WIN).

## Conclusion / narrowest remaining hypothesis (superseded by SOLVED above)
The identity coloring {addr=v0, endpoint=v1, counter=a0} WITH a counter-tested
backedge requires the endpoint LR priority to fall strictly BETWEEN the counter
and addr-ptr priorities, both of which lie in (0.1111, 0.1176). Endpoint priority
is N/uses with N pinned at 2 for every zero-cost (empty-test) lever, giving only
2/17 and 2/18 — which bracket but never enter the window. The ONLY way to hit the
window is to change N (=3 would give 3/26=0.1154, inside the window). N increases
only with a REAL, non-deleted once-run reference to gRacerWaveCount-1, and every
such reference tried adds a net instruction (breaks insns=2625).

Decisive next instrumentation: measure the exact adjsave of the counter LR and the
addr-ptr LR in db3/db4 (map lrbit->hw reg via RACER-COLOR-LU node line ranges +
bb2line.json) to confirm the window bounds and its width; then search specifically
for a source expression that adds ONE real once-run use of gRacerWaveCount-1 while
folding into an EXISTING instruction (net-zero insns) — e.g. reusing the endpoint
value as an operand the compiler already materializes in the peeled first iteration.
