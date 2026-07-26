# Oracle-leg report: deferring the ILOD-into-web collapse in recomp ugen 5.3

## DIFFS: 0 — v_natural MATCHES THE TARGET EXACTLY UNDER THE PATCHED UGEN.

The plain natural source (`selectedTrack = gTrackSelectIDs[trackY][trackX]; cur->hubName
= levelName; if (selectedTrack != -1)`) compiled through the patched toolchain with
`UGEN_NOCOLLAPSE=v1h` scores **DIFFS 0** on func_8008FF1C (371/371 instructions,
mnemonic+register exact vs target.o). The stock score for the same source is 133.
The queue-fixed-point theory of MENU_REATTACK §6.6 is confirmed end to end: emitting the
branch-feeding `lh` as a pool temp (`lh $10` = queue-head GET) plus an as1-dissolved
`move $3, $10` reproduces the ROM's entire downstream register pattern with zero source
tricks.

Pre-as1 emission at the site under the patch (from `-K` listing, `oracle/nat/ncand.s`):

```
 #21127                selectedTrack = gTrackSelectIDs[trackY][trackX];
        lh      $10, 0($17)
        move    $3, $10          <- dissolved by as1: final object is 371 instrs
        sw      $2, 0($16)
        beq     $3, -1, $1128    <- becomes beq $10 after the move dissolves
```

## The patch

File: `$OLD/ido-recomp-pub/build/5.3/ugen.c` (machine-recompiled IDO 5.3 ugen; pristine
backup kept as `ugen.c.pristine`, patched base as `ugen.c.orig`, tracing re-injected on
top by `$MENU/oracle/inject_trace.py`).

**Where the collapse actually happens.** Differential call-tracing (430 f_* functions
instrumented with env-gated entry/exit+arg logging; minimal repro pair
`oracle/tiny_a.c` collapsed vs `oracle/tiny_b.c` mask-idiom) localized the decision to a
single call site inside `f_eval`'s statement handler for "STR whose destination is
register-resident" (recomp label `L42eb3c`, ugen VA 0x42eb3c):

1. `f_ureg(stmt + 0x20)` reads the target leaf; for a Rmt (register memtype) leaf it
   returns `disp/4` = the colored web register (3 = v1 at our site), else 0x48 (no reg).
2. The RHS is then evaluated **with the web register passed as the destination hint**:
   `f_eval(MEM_U32(s6+0), fp)` at label `L42ec60` (VA 0x42ec60). For a leaf ILOD,
   f_eval's `f_get_dest(tree, hint)` uses the hint directly, so the load lands straight
   in the web — that IS the collapse. No free-queue GET occurs.
3. Immediately after, generic epilog code (`f_reg` + `f_move_to_dest(fp, result, type)`)
   already handles the result != dest case by emitting a move.

**Mechanism** (one line of decision change; everything else reuses existing machinery):
immediately before the `f_eval(rhs, fp)` call at `L42ec60`:

```c
if (nc_on() && MEM_U8(a0 + 32) == 0x36 /* Uilod */ &&
    nc_gate(fp & 0xff, MEM_U8(a0 + 33) & 0x1f, MEM_U32(a0 + 40)))
    a1 = 0x48;   /* drop the dest hint: RHS evaluates into a pool temp via f_get_free_reg */
```

With the hint dropped, `f_get_dest` goes through `f_get_free_reg` (normal FIFO
free-queue GET — pops $10 at the site, exactly as the queue math predicted) and
`f_move_to_dest` emits the dissolvable `move $web, $pool`. Node fields used:
+32 = ucode opcode (0x36 = Uilod), +33 & 0x1f = datatype (6 = Jdt signed int),
+40 = access size in bytes (2 = halfword -> lh).

Gate modes selected by the value of `UGEN_NOCOLLAPSE`:

| value | scope of deferral |
|---|---|
| `1` / other | every ILOD stored to a register-resident destination |
| `h` | only 16-bit ILODs (size==2) |
| `hs` | only signed 16-bit ILODs (lh) |
| `v1` | only when the destination register is $3 (v1) |
| `v1h` | dest==$3 **and** signed 16-bit (the site's exact signature) |

## Fidelity

With `UGEN_NOCOLLAPSE` unset, the patched toolchain's object for the full menu TU is
**byte-identical** to the stock repo toolchain's (`cmp` clean; verified for both the
kwork_base TU and the v_base TU, re-verified after the final rebuild). Control scores
through the patched binary with env unset reproduce stock exactly: v_natural = 133,
v_base = 2. Patched ugen md5: `69cdbc21b469165e2012d1dbd6a14901` (pre-patch instrumented
baseline: `902f81c6ef08122f7e4ebd2867028e74`).

## Scores

| variant | toolchain / mode | DIFFS |
|---|---|---|
| v_natural | stock (env unset, control) | 133 |
| **v_natural** | **patched, `v1h`** | **0** |
| v_natural | patched, `hs` | 13 |
| v_natural | patched, `h` | 13 |
| v_natural | patched, `v1` | 23 |
| v_natural | patched, `1` (all ILOD) | 154 (len 370 vs 371) |
| v_base | stock (env unset, control) | 2 |
| v_base | patched, `v1h` | 131 |
| v_base | patched, `1` | 160 |

Why the broad mode overshoots: parameter staging (`lb/lw $a0..$a3` before calls) flows
through the SAME STR-to-register statement path (uopt emits stores to physical-register
leaves for arguments), so unrestricted deferral also rewrites e.g. `lb $4, 0($17)` into
`lb $14; move $4, $14`, popping extra GETs and rotating the whole downstream queue
(first diff at index 117, net length change 371->370). The site-signature gate (`v1h`)
leaves everything else untouched and lands the exact fixed point. The broader gates fail
through other in-function fires: `hs`/`h` perturb a later signed-lh site (first diff
334), `v1` additionally perturbs `lw`-into-$3 sites (first diff 301).

## Collateral (full menu.c .text, per-function word diff vs stock object, v_base TU)

| mode | functions changed (of 226) |
|---|---|
| `v1h` | **12** (11 other than func_8008FF1C) |
| `hs` | 28 |
| `h` | 35 |
| `v1` | 57 |
| `1` | 113 |

The 11 non-target functions changed under `v1h` (same set for the v_natural TU):
draw_menu_elements, menu_title_screen_loop, savemenu_render_element,
menu_magic_codes_loop, charselect_input, charselect_music_channels,
trackmenu_setup_render, menu_asset_free, menu_asset_load,
render_track_selection_viewport_border, is_drumstick_unlocked. (The TU has 19
signed-16-bit ILOD->$3 stores; the extra fires cluster in these functions.)

## Analysis

1. **The theory is proven at the codegen level.** The 133-diff basin is entirely an
   artifact of one binary decision inside ugen — whether the STR-to-web statement hands
   the web register down as the eval destination hint for a leaf ILOD. Deferring it at
   the one site produces the ROM's exact 371-instruction stream; as1 dissolves the move
   with zero net bytes, exactly as predicted.
2. **This is an oracle result, not a shipping toolchain.** No plausible real compiler
   variant is gated on "dest register is v1" — `v1h` is a surgical probe. A genuine
   point-variant ugen would defer more broadly (modes like `1`/`h`), and under those
   modes 28-113 currently-matched menu functions change, i.e. the committed sources
   (written to match stock ugen) would not survive. If Rare's real toolchain had
   deferral semantics, the natural sources of those functions would have to re-match
   under it — untested here and beyond this leg's scope.
3. **Practical implication:** func_8008FF1C's target stream IS reachable from the
   natural source; the remaining 2-instruction gap of the committed WIP is a
   register-allocation phase artifact, not a source-shape problem.

## Artifacts

- Patched recomp source: `$OLD/ido-recomp-pub/build/5.3/ugen.c` (+ `.orig` patched base,
  `.pristine` untouched backup); binary `$OLD/ido-recomp-pub/build/5.3/out/ugen`.
- Harness: `$MENU/oracle/score_nc.py`, `$MENU/oracle/collateral.py`,
  `$MENU/oracle/cc.sh`, `$MENU/oracle/inject_trace.py` (`UGEN_CALLTRACE` gated).
- Evidence: `$MENU/oracle/nat/ncand.s` (pre-as1 site emission),
  `$MENU/oracle/trace_{a,b}.txt`, `$MENU/oracle/tiny_{a,b}.c`,
  `$MENU/oracle/nat/nc_cand.txt` (928 TU-wide ILOD->reg candidate histogram).
