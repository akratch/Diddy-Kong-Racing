# `func_80017A18` — CLOSED (matched 2026-07-24)

**MATCHED. Score 0 / 100.00%.** Compiled from C in `src/objects.c` with
`GLOBAL_ASM` removed; the full ROM builds and verifies OK. Adventure One is
99.48%.

There is nothing left to resume. The full account — what the function does,
how each structural decision was pinned to a specific instruction, the path
from 1472 to 0, and the two reusable techniques — is in
`WRITEUP_func_80017A18.md`.

The one thing worth carrying to other functions: **a store/reload pair around a
loop is not necessarily a source-level copy.** Here the `swc1 f18/f20/f22`
after the facet-count `blez` and the matching reloads after the loop were the
compiler spilling the origin values, not a second set of variables. Modelling
them as copies is what blocked this function for two sessions.

Verify at any time with:

```sh
.venv/bin/python3 objects_research/tools/realscore.py <candidate.c>
```

Mirror of the function alone, the translation unit, and the notes:
`https://github.com/akratch/dkr-func80017A18-wip`.
