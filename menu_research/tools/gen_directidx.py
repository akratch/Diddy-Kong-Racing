#!/usr/bin/env python3
"""Generate direct-index loop variants of func_8008FF1C's nested loop.

The goal is a source where uopt keeps `cur`'s base object (the global
gTrackSelectRenderDetails) so ugen can emit `.noalias <loadbase>,<storebase>`,
while strength reduction still produces the target's single advancing
pointer in $16.

Usage: gen_directidx.py <outdir>
"""
import os
import re
import sys

REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
BASE = open(REPO + "/menu_research/tools/base.c").read()

FROM = "for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++) {"
TO = "        trackSelectY++;\n    }"

i1 = BASE.index(FROM)
i2 = BASE.index(TO, i1) + len(TO)
BODY = BASE[i1:i2]

# base.c natively carries the v_base WIP window (temp burner + named holder).
# Every variant here must be built on the RAW CONDITION instead, because the
# raw form is the one that already puts the load in $10/t2.
NAMED = """                temp = (temp = gTrackSelectIDs[trackY][trackX]);
                selectedTrack = gTrackSelectIDs[trackY][trackX];
                cur->hubName = levelName;
                if (selectedTrack != -1) {"""
RAW = """                cur->hubName = levelName;
                if (gTrackSelectIDs[trackY][trackX] != -1) {"""
assert NAMED in BODY
BODY = BODY.replace(NAMED, RAW)

# The inner body with cur-> accesses, unchanged.
assert "cur->" in BODY


def subst(body, expr):
    """Replace every `cur->` with `<expr>.`"""
    return body.replace("cur->", expr + ".")


VARIANTS = {}

# --- family A: explicit linear counter k, incremented where cur++ was -------
b = BODY
b = b.replace(FROM, "k = 0;\n    for (i = startIndex; i < 2; i++) {")
b = b.replace("for (j = startIndex; j < 2; j++, cur++) {",
              "for (j = startIndex; j < 2; j++, k++) {")
VARIANTS["di_counter"] = subst(b, "gTrackSelectRenderDetails[k]")

# --- family B: counter declared+initialised in the for-init ----------------
b = BODY
b = b.replace(FROM, "for (i = startIndex, k = 0; i < 2; i++) {")
b = b.replace("for (j = startIndex; j < 2; j++, cur++) {",
              "for (j = startIndex; j < 2; j++, k++) {")
VARIANTS["di_counter_init"] = subst(b, "gTrackSelectRenderDetails[k]")

# --- family C: index computed from i and j (no extra induction var) --------
b = BODY
b = b.replace(FROM, "for (i = startIndex; i < 2; i++) {")
b = b.replace("for (j = startIndex; j < 2; j++, cur++) {",
              "for (j = startIndex; j < 2; j++) {")
VARIANTS["di_ij"] = subst(b, "gTrackSelectRenderDetails[((i + 1) * 3) + (j + 1)]")

# --- family D: keep cur for everything, direct-index ONLY the aliasing store
b = BODY
b = b.replace(FROM, "k = 0;\n    for (i = startIndex; i < 2; i++) {")
b = b.replace("for (j = startIndex; j < 2; j++, cur++) {",
              "for (j = startIndex; j < 2; j++, k++, cur++) {")
b = b.replace("cur->hubName = levelName;",
              "gTrackSelectRenderDetails[k].hubName = levelName;")
VARIANTS["di_store_only"] = b

# --- family E: as D but cur derived from the index each iteration ----------
b = BODY
b = b.replace(FROM, "k = 0;\n    for (i = startIndex; i < 2; i++) {")
b = b.replace("for (j = startIndex; j < 2; j++, cur++) {",
              "for (j = startIndex; j < 2; j++, k++) {")
b = b.replace("            trackX = trackSelectX + j;",
              "            cur = &gTrackSelectRenderDetails[k];\n"
              "            trackX = trackSelectX + j;")
b = b.replace("cur->hubName = levelName;",
              "gTrackSelectRenderDetails[k].hubName = levelName;")
VARIANTS["di_ptr_from_idx"] = b

# --- family F: direct-index only the store, index via i/j (no counter) -----
b = BODY
b = b.replace("cur->hubName = levelName;",
              "gTrackSelectRenderDetails[((i + 1) * 3) + (j + 1)].hubName = levelName;")
VARIANTS["di_store_only_ij"] = b

# --- family G: two-level induction ----------------------------------------
# k is a clean OUTER-loop induction variable (step 3), so uopt may carry the
# row base across the outer loop instead of re-deriving it in the preheader.
# That preheader re-derivation is the entire cost of families A-F.
for tag, idx in [("rowstep", "k + j + 1"),
                 ("rowstep_p", "k + (j + 1)"),
                 ("rowstep_jk", "j + 1 + k")]:
    b = BODY
    b = b.replace(FROM, "for (i = startIndex, k = 0; i < 2; i++, k += 3) {")
    b = b.replace("for (j = startIndex; j < 2; j++, cur++) {",
                  "for (j = startIndex; j < 2; j++) {")
    VARIANTS["di_" + tag] = subst(b, "gTrackSelectRenderDetails[" + idx + "]")

# --- family H: two-level, store only ---------------------------------------
b = BODY
b = b.replace(FROM, "for (i = startIndex, k = 0; i < 2; i++, k += 3) {")
b = b.replace("for (j = startIndex; j < 2; j++, cur++) {",
              "for (j = startIndex; j < 2; j++, cur++) {")
b = b.replace("cur->hubName = levelName;",
              "gTrackSelectRenderDetails[k + j + 1].hubName = levelName;")
VARIANTS["di_rowstep_store_only"] = b

# tryfw's ===DECLS=== replaces the whole declaration block, so restate it.
DECLS_K = """    s32 i;
    char *trackName;
    char *hubName;
    s32 selectedTrack;
    s32 trackSelectX;
    s32 trackSelectY;
    char *levelName;
    s32 maxTrackY;
    s8 *trackMenuIds;
    Settings *settings;
    TrackRenderDetails *cur;
    s32 trackX;
    s32 trackY;
    s32 j;
    s32 startIndex;
    s16 temp;
    s32 k;
"""

outdir = sys.argv[1]
os.makedirs(outdir, exist_ok=True)
for name, body in VARIANTS.items():
    needs_k = re.search(r"\bk\b", body) is not None
    txt = ""
    if needs_k:
        txt += "===DECLS===\n" + DECLS_K + "===CODE===\n"
    txt += "===FROM===\n" + FROM + "\n===TO===\n" + TO + "\n===CODE===\n" + body + "\n"
    p = os.path.join(outdir, "v_" + name + ".txt")
    open(p, "w").write(txt)
    print("wrote", p)
