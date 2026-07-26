# Backward ucode-level closure of the ILOD→web collapse (MENU_FINDINGS §8)

> **Construction addendum:** Later boundary tests confirmed that truthful
> block `const`, block scope, and reusing the function parameter as the holder
> all remain the ordinary FW133 collapse. A flat direct loop can reach the
> local target window, but through `uopt` alias ordering rather than a new
> non-alias producer, and its whole-function induction graph differs. Thus the
> fixed target-compatible holder frame below remains closed. Arbitrary CFG
> topology is still not a finite all-C enumeration; see
> `report_construction_endgame.md` §6.

(Agent report, 2026-07-24; archived verbatim by the orchestrating session —
the sandbox blocked the agent's own .md write. Working artifacts in the
session-84e018d6 scratchpad menu/enum/, menu/klist_enum_*.s,
menu/kwork_enum_*/; all volatile, regenerable via menu_research/tools/.)

## 0. Result (up front)

The enumeration closes EMPTY. There is no DIFFS-0 stock-toolchain shape.
The source-space leg is closed at the opcode level.

- At the ugen level, exactly ONE tree shape T produces "lh $pool +
  only-dissolvable-moves, zero pairs, no CSE carriers": an identity
  integer->integer conversion (a Ucvt whose operand datatype already
  equals its result datatype), routed through the func_436008
  same-datatype path that emits only an f_move_to_dest move.
- That single shape is unreachable from C: cfe eliminates it before ugen.
  Proven to the byte — `selectedTrack = (s32)load;` and
  `selectedTrack = load;` produce byte-identical object files and
  content-identical uopt output. No Ucvt node survives to ugen.
- Every Ucvt that does survive cfe/uopt violates a win constraint:
  64-bit widen -> allocates a register PAIR (queue poison, DIFFS 119);
  narrowing (s16/u16/s8/u8) -> folds into the load (lh->lb/lhu/lbu,
  still collapses); int<->float -> 4 real FPU ops; s16-via-variable
  widen -> live sll/sra.
- Every non-Ucvt root either collapses the load into the web (leaf load;
  unary neg/compl operate in place) or emits >=1 real instruction (all
  binary arith/logic/shift/compare, mul/div/mod, fp ops).

This is a finite, mechanistic proof (not a family sweep), immune to the
enumeration failure mode that bit racer. It upgrades MENU_FINDINGS
hypothesis 2 (context-dependent rule in an unobtained pressed-CD 5.3
ugen) to the sole surviving explanation for a stock-toolchain DIFFS 0.

All scores/emissions came from the stock repo toolchain — no patched
ugen. Harness soundness re-verified: v_base=2, v_natural=133,
v_scratch=2 (exact ledger matches).

## A. The dispatch, read from stock ugen

A.1 Collapse decision. Store handler = f_eval opcode 123 (Ustr) ->
L42eb3c; at L42ec60 it calls f_eval(rhs, fp) with fp = the colored web
reg. f_get_dest(tree, hint) (L45560) uses a real hint directly (via
f_get_reg) -> a leaf ILOD lands in the web (collapse, no queue GET).
Hint 0x48 ("none") -> f_get_free_reg (FIFO GET) -> pool temp. Collapse
vs defer == whether the hint reached the ILOD or was replaced by 0x48.

A.2 f_eval opcode -> handler map (jump table at ugen.c ~56333, 152
opcodes):

| handler | opcodes | class | root emission |
|---|---|---|---|
| L434c2c/L434390 | 59 opcodes (incl. 128-133) | invalid as expr root | cannot be a store RHS |
| L430cf8 | 54 (Uilod), 61 | leaf integer LOAD | hint->leaf => collapse, lh $web |
| L4333b0 | 134 (Ucvt) | conversion | defers operand (a1=0x48); cost by cvt kind |
| L432890 | 1,4,29,35,40,41,60,77,78,91,95,105,115,116,125,141 | binary arith/logic/compare | >=1 real instr |
| L433820 | 46,47,48,52,53,56 | integer relational | >=1 real instr |
| L42fe30 | 85,86 | fp min/max | real fp |
| L42f310 | 90,102 | compound move (f_eval_mov) | reorders to [sw][lh]; not a zero-cost defer |
| ~66 singletons | remainder | unary neg/compl, mul/div/mod/shift, fp arith, address, call | >=1 real instr or invalid |

Of 152 opcodes, only the 2 loads and the 1 cvt can emit zero real
instructions at the root. Loads collapse. Only Ucvt both defers the
operand to a pool temp AND can emit zero real code — the whole question
reduces to Ucvt.

A.3 Ucvt (decisive). Ucvt->L4333b0 dispatches to four cvt helpers, all
of which evaluate the converted operand with a1=0x48 (a Ucvt ALWAYS
defers its operand to a fresh pool reg; confirmed at func_436008
L4360a0/L4361e4 and func_436484 L43678x). Then f_eval_int_int_cvt
(L70058) picks:
- func_436008 (32-bit result): operand datatype (+33&0x1f) == result
  datatype -> emits NOTHING, only f_move_to_dest (one dissolvable move;
  L4360ec->L436190). Different -> sll+sra/srl (real) then move.
- func_436484 (64-bit result dtypes {5,7,15}): grabs a PAIR.

The unique zero-cost defer shape is the identity Ucvt via func_436008.
Reachability is singular: can C emit an identity Ucvt surviving cfe?

## B. Empirical verification (stock toolchain)

Frame: selectedTrack = <WRAP>; cur->hubName = levelName;
if (selectedTrack != -1); with L = gTrackSelectIDs[trackY][trackX].
Baseline <WRAP>=L scores 133 (first diff idx 102, lh v1 vs lh t2).

| <WRAP> | DIFFS | site pre-as1 | classification |
|---|---:|---|---|
| L (natural) | 133 | lh $3 | collapse baseline |
| (s32)L | 133 | lh $3 | FOLDED — object byte-identical to natural |
| (u32)L, (s32)(u32)L, (u32)(s32)L | 133 | lh $3 | folded (same-size int cast) |
| L+0, L\|0, L*1, L<<0, L&0xFFFFFFFF, L^(L&0), 1?L:L | 133 | lh $3 | folded (identities) |
| *(volatile s16*)&L | 133 | lh $3 | collapse (volatile is not a blocker) |
| (s16)L | 133 | lh $3 | narrowing folds into load |
| (u16)L / (s8)L / (u8)L | 133 | lhu/lb/lbu $3 | folds into load, collapses |
| (s32)(long long)L | 119 | lh $10; move $13,$10; sra $12; move $3,$13 | defers but PAIR(12,13) |
| (s32)(unsigned long long)L, (long long)L | 119 | same | defer + PAIR |
| (s32)((long long)(s32)L) | 119 | same | pair bound to the EXISTENCE of a 64-bit subexpr, not spelling |
| (s32)(L & 0xFFFFFFFFFFFFFFFFLL) | 119 | same | mask idiom on natural frame: defer + PAIR |
| (s32)(f32)L | 274 | lh $10; mtc1; cvt.s.w; trunc.w.s; mfc1 | defers, 4 real FPU |
| - -(L) | 258 | lh $3; negu; negu | collapse + 2 real (unary in place) |
| ~~(L) | 258 | lh $3; not; not | collapse + 2 real |
| (trackSelectY = L) live chain | 339 | lh into saved-reg web | collapse |
| (L)?(L):(L) | 272 | real branches + moves | real branches |

Nothing lands in 3-118. Every deferring shape (119+) carries a pair or
real ops; every zero-real shape collapses (133) or folds.

B.1 Reachability proof for the identity cvt: objects for L vs (s32)L are
byte-identical (cmp clean); uopt -Wo,-l -zdbug:5 listings content-
identical after normalizing timing counters (0 content lines differ; the
genuinely-surviving (s32)(long long)L differs in 1348 lines).

B.2 Why no other 32-bit cvt is reachable: s32/u32 share one
representation, so cfe elides every 32-bit int->int cast. A Ucvt
survives only on a real representation change: crossing 32 bits
(widen->pair) or narrowing-from-memory (folds into a smaller load,
still collapses). A surviving int Ucvt with MATCHING operand/result
datatype cannot exist — matching datatype IS the identity cfe deletes.
The func_436008 move-only path is structurally unreachable from C.

## C. Constraint reconciliation

Win requires simultaneously: (1) defer the ILOD to pool, (2) zero real
instructions, (3) zero pairs, (4) zero cross-statement CSE carriers.
Every enumerated row satisfying (1) fails at least one of (2)/(3)/(4);
the single row satisfying all four (identity cvt) fails reachability.
Jointly unsatisfiable over C-reachable shapes.

## D. Opcode-level closure table

| opcode class | ILOD operand | root emission | verdict |
|---|---|---|---|
| leaf load (54,61) | hint reaches leaf | 0 real | collapses (load in web, never pool) |
| Ucvt identity 32-bit (func_436008 move-only) | deferred to pool | move only | defers-zero-cost but UNREACHABLE (cfe folds; object-identical proof) |
| Ucvt widen->64-bit (func_436484) | deferred to pool | lo-move + hi-sra, PAIR | defers-with-cost (pair) -> 119 |
| Ucvt narrow -> s16/u16/s8/u8 | — | folds into LOAD | collapses |
| Ucvt s16->s32 via variable | deferred to pool | sll+sra (real) | defers-with-cost |
| Ucvt int<->float | deferred to pool | mtc1/cvt/trunc/mfc1 | defers-with-cost (fp) |
| binary arith/logic (16 opcodes) | operands eval | >=1 real root | defers-with-cost |
| relational (6) | operands eval | slt... | defers-with-cost |
| unary neg/compl | hint->leaf | in-place real | collapses + real |
| mul/div/mod/shift, fp arith | operands eval | real root | defers-with-cost |
| compound move (90,102) | — | reorders to [sw][lh] | not a zero-cost defer |
| 59 statement opcodes | — | — | invalid as expression root |

No row is {defers, zero real, zero pair, reachable}. Enumeration
complete and empty.

## E. Conclusion

Under stock IDO 5.3 ugen, the branch-feeding lh becomes a pool temp only
by deferring its ILOD, and the sole deferring wrapper emitting zero real
code and zero pairs is an identity integer conversion — precisely the
construct cfe deletes before a Ucvt ever reaches ugen. The DIFFS-2 floor
is therefore not a source-shape problem under the canonical toolchain.
The sole surviving path to a stock-toolchain DIFFS 0 is a
context-dependent collapse rule in an unobtained pressed-CD 5.3 ugen
(MENU_FINDINGS §5 hypothesis 2); the committed WIP at DIFFS 2 remains
the honest ceiling.

Dispatch read locations in $OLD/ido-recomp-pub/build/5.3/ugen.c: f_eval
switch ~L56333; Ucvt -> L4333b0; f_eval_int_int_cvt L70058; func_436008
L69317 (move-only path L4360ec->L436190); func_436484 L69761 (pair);
f_get_dest L45560; store handler L42eb3c/L42ec60.
