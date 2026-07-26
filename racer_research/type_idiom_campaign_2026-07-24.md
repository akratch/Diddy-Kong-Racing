
## Session (type/idiom genre) — func_80049794, 19-diff residual

Baseline: norm=19 sha=e95892dd53eb entryQ=[14 12 24 25 15 11 13]. Target entryQ (from notes) = [12 24 25 15 14 11 13] (reg 14 front->pos4).
Structural fact established: in-region op-sequence (idx 1682-1691 arm1, 1701-1709 arm2, plus hoisted updateRate loads 1656/1667) is BYTE-FOR-BYTE the SAME instructions as target — ONLY register names differ. So the residual is 100% an entry-queue (FIFO free-order) artifact. Entry queue == order of last 7 temp allocs before region (serials 229-235, src lines 745-765).

| variant | spelling | norm | sha moved | entryQ | verdict |
|---|---|---|---|---|---|
| B01_fold_selfsub | x = v1-((v1*ur)>>4) -> x -= (v1*ur)>>4 | 19 | N | base | INERT (folds) |
| B03_commute19 | 19*(t0>>1)*ur | 19 | N | base | INERT |
| B06_vt0half_s32 | ((s32)t0>>1) | 19 | N | base | INERT |
| B02_s16cast_a1 | -=(s16)(...) whole rhs | 248 | Y | base | reflow, Q unchanged |
| B04_commute_ur | (t0>>1)*ur*19 | 24 | Y | base | +5 region diffs, Q unchanged |
| A743_u16 | (u16)(t0*ur) == &0xFFFF | 19 | N | base | INERT ((u16)==andi) |
| A743_s16 | (s16)(t0*ur) | 220 | Y | **12 24 25 11 15 13 14** | Q MOVED (front-3 match tgt), reflow |
| A743_nomask | drop &0xFFFF | 226 | Y | 13 14 12 24 15 25 11 | Q MOVED, reflow |
| S743_mul_u16 | (u16)t0 * ur & 0xFFFF | 1045 | Y | 12 15 24 25 13 11 14 | Q MOVED, reflow |
| S743_ll | &0xFFFFLL | 255 | Y | 24 25 12 13 14 15 11 | Q MOVED, reflow |
| S743_u32 | (u32)(t0*ur)&0xFFFF | 19 | N | base | INERT |
| S743_and_then_neg | +=-(...&0xFFFF) | 19 | N | base | INERT |
| S737_u16 / S741_u16 | (steerAngle*6/4)&0xFFFF | 1012/1026 | Y | 12 15 25 11 24 13 14 | Q MOVED, reflow |
| S730_s16 | -(s16)(xrv&0xFFFF) | 1037 | Y | 15 24 11 13 25 14 12 | Q MOVED, reflow |
| A730_u16 / S730_nomask | (u16)/no mask | 19/1073 | N/Y | base | INERT / reflow-noQ |
| A765_explicit / A743_and | var_t0=var_t0*var_f2 | 19 | N | base | INERT |
| V_reuse_v0(_mul), V_ur_reuse | hoist t0>>1 / v1*ur into existing local | 19 | N | base | INERT (copy-prop folds) |
| V_div2 | (t0>>1)->(t0/2) | 944 | Y | base | reflow, Q unchanged (rounding code) |
| V_19u | 19u/30u literals | 21 | Y | base | +2 region diffs, Q unchanged |
| R_maskfree_a1 | mask region result &0xFFFF | 226 | Y | base | reflow, Q unchanged |

### Conclusion (this genre)
- Semantic-NEUTRAL respells (casts equal to existing masks, commutation, self-sub fold, local reuse, u16/u32 that equal andi) are ALL byte-identical INERT. Confirms the byte-identical==queue-invariant axiom holds under type/idiom respelling too (copy-prop + node canonicalization fold them).
- Semantic-CHANGING respells split into two useless classes: (a) change region-internal codegen, add diffs, entry queue UNCHANGED (B04, V_div2, V_19u, R_maskfree); (b) MOVE the entry queue but only via ZONE-A mask-node reshapes (s16/no-mask/ll @743, &mask @737/741, s16 @730) which reflow the ENTIRE downstream to 220-1045 diffs and never land on target [12 24 25 15 14 11 13].
- Best queue approach: A743_s16 reaches [12 24 25 ...] (front-3 correct) but at norm=220.
- GAP (why unreachable): entry-queue-movers are all UPSTREAM-semantic (reflow forward, uncontained); region-local changes never move the ENTRY queue. Target's queue difference is an ABSORBED perturbation (only 19 regs differ, nothing after reflows) that no local source construct in this checkpoint can express. No norm<19 found; residual INVARIANT under the type/idiom genre.
