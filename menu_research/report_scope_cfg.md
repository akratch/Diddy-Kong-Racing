# Scope/CFG/signature sweep (Codex families #5/#6/#7) — 2026-07-24

> **Construction addendum:** Later boundary checks added truthful block
> `const`, parameter reuse, supported alias directives/qualifiers, and
> external-versus-`static` linkage for both relevant globals. Holder forms
> remain FW133; directives are unsupported/rejected; linkage changes only
> relocation addends. See `report_construction_endgame.md` §6–7.

Headline: no variant beat DIFFS 2; no FULLWORD 0. ~48 cells, all vS_-
prefixed in the menuwork harness. Three fresh confirmations, now SWEPT
rather than argued:

1. Web identity is invariant to scope, lifetime, and declaration order:
   every named-holder form (function/else/inner scope, decl reorder,
   dead-local reuse, split vars, init-at-decl, do-while/bare-block/if(1)
   wrappers) collapses the load into v1 (first_diff 102). F1/law L6
   re-derived by direct sweep.
2. Declaration reordering is allocation-neutral on the WIP body (every
   permutation stays at exactly DIFFS 2) — safe transform, no help.
3. Signature/prototype levers are inert: updateRate never enters
   dataflow; ABI-compatible respellings byte-neutral; retyped params
   fail against the fixed forward declaration.

New instruction-level pin on the raw basin (F2): raw consumption gives
lh t2/beq t2 correctly but emits the hubName store at index 102 (before
the load) + an extra lui; as1 fills delay slots only from the
immediately-preceding instruction or branch-head duplication, and the
store sits three back with the branch-defining lh between — it can
never reach the slot.

Notable cells: goto diamonds 133/2 (didn't move the load); label-using
forms 340-341 (global renumber, consistent with the splitter finding);
raw variants all 38 (t2 OK, store misplaced); store-at-successor forms
108-211; inverted-condition 262+. Nothing in (2,38); nothing reached
the addu basin from a new angle.

Verdict: F1 (pool-temp load) and F2 (store in slot) remain mutually
exclusive across the swept scope/CFG/signature dimensions. DIFFS 2
stands.
