#!/usr/bin/env python3
"""Evaluate direct-symbol address spellings for func_8008FF1C without touching source."""

from __future__ import annotations

import os
import re
import subprocess
import tempfile

ROOT = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
SCRATCH = (
    "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
    "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad/menuwork2"
)
BASE = open(os.path.join(SCRATCH, "base.c")).read()
TARGET = os.path.join(SCRATCH, "target.o")
COMPILE = os.path.join(SCRATCH, "compile.sh")
OBJDUMP = os.path.join(ROOT, "tools/binutils/mips64-elf-objdump")

OLD = """\
                levelName = level_name(level_world_id(trackY + 1));
                temp = (temp = gTrackSelectIDs[trackY][trackX]);
                selectedTrack = gTrackSelectIDs[trackY][trackX];
                cur->hubName = levelName;
                if (selectedTrack != -1) {"""


def asm(obj: str) -> list[tuple[int, str, str]]:
    text = subprocess.run(
        [OBJDUMP, "-d", obj], check=True, capture_output=True, text=True
    ).stdout
    active = False
    out: list[tuple[int, str, str]] = []
    for line in text.splitlines():
        if "<func_8008FF1C>:" in line:
            active = True
            continue
        if not active:
            continue
        match = re.match(
            r"\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)(?:\s+(.*))?", line
        )
        if match:
            out.append(
                (int(match.group(2), 16), match.group(3), match.group(4) or "")
            )
        elif not line.strip():
            break
    return out


WANT = asm(TARGET)
FILTER = os.environ.get("MENU_FORM_FILTER", "")


def evaluate(label: str, source: str) -> None:
    if FILTER and FILTER not in label:
        return
    with tempfile.NamedTemporaryFile(suffix=".c", mode="w", delete=False) as src:
        src.write(source)
        src_path = src.name
    with tempfile.NamedTemporaryFile(suffix=".o", delete=False) as obj:
        obj_path = obj.name
    try:
        result = subprocess.run(
            ["bash", COMPILE, src_path, "-o", obj_path],
            capture_output=True,
            text=True,
        )
        if result.returncode:
            print(f"{label:32s} COMPILE FAIL {result.stderr[-1200:].strip()}")
            return
        got = asm(obj_path)
        raw = sum(a[0] != b[0] for a, b in zip(got, WANT)) + abs(
            len(got) - len(WANT)
        )
        reg = sum(
            (a[1], re.findall(r"\\b(?:v[01]|a[0-3]|t\\d|s\\d|sp|ra|at|zero)\\b", a[2]))
            != (b[1], re.findall(r"\\b(?:v[01]|a[0-3]|t\\d|s\\d|sp|ra|at|zero)\\b", b[2]))
            for a, b in zip(got, WANT)
        ) + abs(len(got) - len(WANT))
        critical = " | ".join(
            f"{m} {o}" for _, m, o in got[98:108]
        )
        print(
            f"{label:32s} raw={raw:4d} reg={reg:4d} "
            f"len={len(got):3d} :: {critical}"
        )
        if label == "raw-store-else-only":
            for index, (have, want) in enumerate(zip(got, WANT)):
                if have[0] != want[0]:
                    print(
                        f"  {index:3d}: {have[0]:08x} {have[1]} {have[2]}"
                        f" != {want[0]:08x} {want[1]} {want[2]}"
                    )
    finally:
        os.unlink(src_path)
        os.unlink(obj_path)


def direct_store(expr: str) -> str:
    new = f"""\
                levelName = level_name(level_world_id(trackY + 1));
                gTrackSelectRenderDetails[{expr}].hubName = levelName;
                if (gTrackSelectIDs[trackY][trackX] != -1) {{"""
    assert OLD in BASE
    return BASE.replace(OLD, new, 1)


def raw_condition(source: str = BASE) -> str:
    new = """\
                levelName = level_name(level_world_id(trackY + 1));
                cur->hubName = levelName;
                if (gTrackSelectIDs[trackY][trackX] != -1) {"""
    assert OLD in source
    return source.replace(OLD, new, 1)


def direct_all(expr: str, index_setup: str = "") -> str:
    source = raw_condition()
    source = source.replace(
        "    for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++) {",
        f"    {index_setup}for (i = startIndex; i < 2; i++) {{",
        1,
    )
    source = source.replace(
        "        for (j = startIndex; j < 2; j++, cur++) {",
        "        for (j = startIndex; j < 2; j++) {",
        1,
    )
    begin = source.index("    for (i = startIndex; i < 2; i++) {")
    end = source.index("    camDisableUserView", begin)
    body = source[begin:end].replace(
        "cur->", f"gTrackSelectRenderDetails[{expr}]."
    )
    return source[:begin] + body + source[end:]


def direct_counter(host: str) -> str:
    source = raw_condition()
    source = source.replace(
        "    for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++) {",
        f"    for (i = startIndex, {host} = 0; i < 2; i++) {{",
        1,
    )
    source = source.replace(
        "        for (j = startIndex; j < 2; j++, cur++) {",
        f"        for (j = startIndex; j < 2; j++, {host}++) {{",
        1,
    )
    begin = source.index(f"    for (i = startIndex, {host} = 0; i < 2; i++) {{")
    end = source.index("    camDisableUserView", begin)
    body = source[begin:end].replace(
        "cur->", f"gTrackSelectRenderDetails[{host}]."
    )
    return source[:begin] + body + source[end:]


def named_variant(declaration: str, code: str) -> str:
    source = BASE.replace("    s32 selectedTrack;", declaration, 1)
    new = (
        "                levelName = level_name(level_world_id(trackY + 1));\n"
        + code
    )
    assert OLD in source
    return source.replace(OLD, new, 1)


def condition_with_store(condition: str) -> str:
    new = (
        "                levelName = level_name(level_world_id(trackY + 1));\n"
        f"                if ({condition}) {{"
    )
    assert OLD in BASE
    return BASE.replace(OLD, new, 1)


FORMS = {
    "i3+j+4": "((i * 3) + j) + 4",
    "i3+(j+4)": "(i * 3) + (j + 4)",
    "(i+1)3+(j+1)": "((i + 1) * 3) + (j + 1)",
    "((i+1)3+j)+1": "(((i + 1) * 3) + j) + 1",
    "(i+1)3+(j-start)": "((i + 1) * 3) + (j - startIndex)",
    "(i-start)3+(j-start)": "((i - startIndex) * 3) + (j - startIndex)",
    "(i3+j)-4start": "((i * 3) + j) - (startIndex * 4)",
    "nested-cast": "((TrackRenderDetails (*)[3]) gTrackSelectRenderDetails)[i + 1][j + 1]",
}


evaluate("baseline-v_bc", BASE)
raw = raw_condition()
evaluate("raw-v_g2", raw)
else_only = raw.replace("                cur->hubName = levelName;\n", "", 1)
else_only = else_only.replace(
    "                } else {\n                    cur->trackName = gQMarkPtr;",
    "                } else {\n"
    "                    cur->hubName = levelName;\n"
    "                    cur->trackName = gQMarkPtr;",
    1,
)
evaluate("raw-store-else-only", else_only)
true_only = raw.replace("                cur->hubName = levelName;\n", "", 1)
true_only = true_only.replace(
    "                if (gTrackSelectIDs[trackY][trackX] != -1) {\n",
    "                if (gTrackSelectIDs[trackY][trackX] != -1) {\n"
    "                    cur->hubName = levelName;\n",
    1,
)
evaluate("raw-store-true-only", true_only)
both_branch_stores = raw.replace(
    "                cur->hubName = levelName;\n"
    "                if (gTrackSelectIDs[trackY][trackX] != -1) {\n",
    "                if (gTrackSelectIDs[trackY][trackX] != -1) {\n"
    "                    cur->hubName = levelName;\n",
    1,
).replace(
    "                } else {\n                    cur->trackName = gQMarkPtr;",
    "                } else {\n"
    "                    cur->hubName = levelName;\n"
    "                    cur->trackName = gQMarkPtr;",
    1,
)
evaluate("raw-store-both-branches", both_branch_stores)


def goto_name_branch(store_else: bool) -> str:
    source = raw.replace("                cur->hubName = levelName;\n", "", 1)
    source = source.replace(
        "                if (gTrackSelectIDs[trackY][trackX] != -1) {\n",
        "                if (gTrackSelectIDs[trackY][trackX] == -1) {\n"
        "                    goto track_name_missing;\n"
        "                }\n"
        "                cur->hubName = levelName;\n",
        1,
    )
    old_tail = """\
                } else {
                    cur->trackName = gQMarkPtr;
                }
                cur->xOff"""
    else_line = (
        "                cur->hubName = levelName;\n" if store_else else ""
    )
    new_tail = (
        "                goto track_name_done;\n"
        "track_name_missing:\n"
        + else_line
        + "                cur->trackName = gQMarkPtr;\n"
        "track_name_done:\n"
        "                cur->xOff"
    )
    assert old_tail in source
    return source.replace(old_tail, new_tail, 1)


evaluate("raw-goto-both-stores", goto_name_branch(True))
evaluate("raw-goto-true-store", goto_name_branch(False))
for qualifier in ("restrict", "__restrict", "__restrict__"):
    restricted = raw.replace(
        "    TrackRenderDetails *cur;",
        f"    TrackRenderDetails * {qualifier} cur;",
        1,
    )
    evaluate(f"raw-{qualifier}", restricted)
evaluate(
    "raw-ivdep-inner",
    raw.replace(
        "        for (j = startIndex; j < 2; j++, cur++) {",
        "#pragma ivdep\n        for (j = startIndex; j < 2; j++, cur++) {",
        1,
    ),
)
evaluate(
    "raw-ivdep-outer",
    raw.replace(
        "    for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++) {",
        "#pragma ivdep\n    for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++) {",
        1,
    ),
)
evaluate(
    "raw-inline-noalias",
    raw.replace(
        "                levelName = level_name(level_world_id(trackY + 1));",
        '                asm(".noalias $17,$16");\n'
        "                levelName = level_name(level_world_id(trackY + 1));",
        1,
    ),
)
evaluate(
    "raw-block-extern-const",
    raw.replace(
        "    settings = get_settings();",
        "    extern const s16 gTrackSelectIDs[4][6];\n"
        "    settings = get_settings();",
        1,
    ),
)
for cast_name, cast_expr in {
    "raw-const-s16-ptr": "*(const s16 *) &gTrackSelectIDs[trackY][trackX]",
    "raw-const-array-ptr": (
        "((const s16 (*)[6]) gTrackSelectIDs)[trackY][trackX]"
    ),
    "raw-volatile-const-ptr": (
        "*(const volatile s16 *) &gTrackSelectIDs[trackY][trackX]"
    ),
}.items():
    evaluate(
        cast_name,
        raw.replace(
            "gTrackSelectIDs[trackY][trackX] != -1",
            f"{cast_expr} != -1",
            1,
        ),
    )
for named_name, named_decl, named_code in [
    (
        "named-register-s32",
        "    register s32 selectedTrack;",
        "                selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "named-register-s16",
        "    register s16 selectedTrack;",
        "                selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "named-volatile-register",
        "    volatile register s32 selectedTrack;",
        "                selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "named-block-const-s32",
        "",
        "                {\n"
        "                    const s32 selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                    cur->hubName = levelName;\n"
        "                    if (selectedTrack != -1) {",
    ),
    (
        "named-block-const-s16",
        "",
        "                {\n"
        "                    const s16 selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                    cur->hubName = levelName;\n"
        "                    if (selectedTrack != -1) {",
    ),
    (
        "named-reuse-temp",
        "    s32 selectedTrack;",
        "                temp = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (temp != -1) {",
    ),
]:
    candidate = named_variant(named_decl, named_code)
    if "named-block-const" in named_name:
        candidate = candidate.replace(
            "                cur->yOff = ((-trackY * gTrackSelectViewportY) - gTrackSelectY);",
            "                    }\n"
            "                }\n"
            "                cur->yOff = ((-trackY * gTrackSelectViewportY) - gTrackSelectY);",
            1,
        )
    evaluate(named_name, candidate)
for name, form in FORMS.items():
    evaluate(name, direct_store(form))
for name, form in {
    "direct-cur-difference": "(cur - gTrackSelectRenderDetails)",
    "direct-cur-difference-cast": "(s32) (cur - gTrackSelectRenderDetails)",
    "direct-cur-bytes": (
        "((s32) ((u8 *) cur - (u8 *) gTrackSelectRenderDetails) / "
        "sizeof(TrackRenderDetails))"
    ),
}.items():
    evaluate(name, direct_store(form))
evaluate("all-direct-i3+j+4", direct_all("((i * 3) + j) + 4"))
evaluate("all-direct-(i+1)3+j+1", direct_all("((i + 1) * 3) + (j + 1)"))
evaluate("all-direct-selected-count", direct_counter("selectedTrack"))
evaluate("all-direct-start-count", direct_counter("startIndex"))

# Both operands of these operators are evaluated.  The right side reduces to
# a constant but retains the unconditional hubName store, allowing ugen to
# choose the raw array condition first without changing C semantics.
raw_test = "gTrackSelectIDs[trackY][trackX] != -1"
array_lvalue = "gTrackSelectIDs[trackY][trackX]"
store_one = "((cur->hubName = levelName), 1)"
store_zero = "((cur->hubName = levelName), 0)"
store_true = "((cur->hubName = levelName) == levelName)"
for label, condition in {
    "cond-bitand-comma": f"({raw_test}) & {store_one}",
    "cond-bitand-eq": f"({raw_test}) & {store_true}",
    "cond-bitor-comma": f"({raw_test}) | {store_zero}",
    "cond-bitxor-comma": f"({raw_test}) ^ {store_zero}",
    "cond-add-comma": f"({raw_test}) + {store_zero}",
    "cond-sub-comma": f"({raw_test}) - {store_zero}",
    "cond-mul-comma": f"({raw_test}) * {store_one}",
    "cond-and-reverse": f"{store_one} & ({raw_test})",
    "cond-or-reverse": f"{store_zero} | ({raw_test})",
    "cond-ternary": (
        f"({raw_test}) ? ((cur->hubName = levelName), 1) "
        ": ((cur->hubName = levelName), 0)"
    ),
}.items():
    evaluate(label, condition_with_store(condition))

# Assignment/CSE topologies for the exact schedule.  These all put the array
# read in a statement before the pointer store; the question is whether uopt
# represents the surviving value as a colored local or as the assignment
# expression's pool temporary.
for label, declaration, code in [
    (
        "color-chain-selected-temp",
        "    s32 selectedTrack;",
        "                selectedTrack = temp = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "color-chain-temp-selected",
        "    s32 selectedTrack;",
        "                temp = selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (temp != -1) {",
    ),
    (
        "color-copy-selected-from-temp",
        "    s32 selectedTrack;",
        "                temp = gTrackSelectIDs[trackY][trackX];\n"
        "                selectedTrack = temp;\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "color-copy-temp-from-selected",
        "    s32 selectedTrack;",
        "                selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                temp = selectedTrack;\n"
        "                cur->hubName = levelName;\n"
        "                if (temp != -1) {",
    ),
    (
        "color-double-chain-selected",
        "    s32 selectedTrack;",
        "                selectedTrack = (temp = (temp = "
        "gTrackSelectIDs[trackY][trackX]));\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "color-self-selected",
        "    s32 selectedTrack;",
        "                selectedTrack = (selectedTrack = "
        "gTrackSelectIDs[trackY][trackX]);\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "color-self-temp",
        "    s32 selectedTrack;",
        "                temp = (temp = gTrackSelectIDs[trackY][trackX]);\n"
        "                cur->hubName = levelName;\n"
        "                if (temp != -1) {",
    ),
    (
        "color-comma-assign-selected",
        "    s32 selectedTrack;",
        "                (temp = gTrackSelectIDs[trackY][trackX], "
        "selectedTrack = temp);\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "color-comma-assign-temp",
        "    s32 selectedTrack;",
        "                (selectedTrack = gTrackSelectIDs[trackY][trackX], "
        "temp = selectedTrack);\n"
        "                cur->hubName = levelName;\n"
        "                if (temp != -1) {",
    ),
    (
        "color-s16-selected",
        "    s16 selectedTrack;",
        "                selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != -1) {",
    ),
    (
        "color-u16-selected",
        "    u16 selectedTrack;",
        "                selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
        "                cur->hubName = levelName;\n"
        "                if (selectedTrack != (u16) -1) {",
    ),
]:
    evaluate(label, named_variant(declaration, code))

for label, expression in {
    "color-expr-plus-zero": "selectedTrack + 0",
    "color-expr-minus-zero": "selectedTrack - 0",
    "color-expr-or-zero": "selectedTrack | 0",
    "color-expr-xor-zero": "selectedTrack ^ 0",
    "color-expr-and-minus1": "selectedTrack & -1",
    "color-expr-mul-one": "selectedTrack * 1",
    "color-expr-cast-s16": "(s16) selectedTrack",
    "color-expr-cast-s32-s16": "(s32) (s16) selectedTrack",
    "color-expr-comma": "(0, selectedTrack)",
}.items():
    evaluate(
        label,
        named_variant(
            "    s32 selectedTrack;",
            "                selectedTrack = gTrackSelectIDs[trackY][trackX];\n"
            "                cur->hubName = levelName;\n"
            f"                if ({expression} != -1) {{",
        ),
    )

# A conditional expression can retain the array value itself rather than
# first reducing it to a boolean.  The two arms have the same mandatory
# side effect, so uopt may common the store while keeping the raw-load web
# anonymous (the property that gives the target t2 allocation).
for label, condition in {
    "ternary-value-same-raw": (
        f"(({array_lvalue} != -1) "
        f"? ((cur->hubName = levelName), {array_lvalue}) "
        f": ((cur->hubName = levelName), {array_lvalue})) != -1"
    ),
    "ternary-value-temp": (
        f"((temp = {array_lvalue}) != -1 "
        f"? ((cur->hubName = levelName), temp) "
        f": ((cur->hubName = levelName), temp)) != -1"
    ),
    "ternary-value-selected": (
        f"((selectedTrack = {array_lvalue}) != -1 "
        f"? ((cur->hubName = levelName), selectedTrack) "
        f": ((cur->hubName = levelName), selectedTrack)) != -1"
    ),
    "ternary-raw-or-minus1": (
        f"({array_lvalue} != -1 "
        f"? ((cur->hubName = levelName), {array_lvalue}) "
        ": ((cur->hubName = levelName), -1)) != -1"
    ),
    "ternary-temp-or-minus1": (
        f"((temp = {array_lvalue}) != -1 "
        "? ((cur->hubName = levelName), temp) "
        ": ((cur->hubName = levelName), -1)) != -1"
    ),
    "ternary-minus1-or-raw": (
        f"({array_lvalue} == -1 "
        "? ((cur->hubName = levelName), -1) "
        f": ((cur->hubName = levelName), {array_lvalue})) != -1"
    ),
    "ternary-minus1-or-temp": (
        f"((temp = {array_lvalue}) == -1 "
        "? ((cur->hubName = levelName), -1) "
        ": ((cur->hubName = levelName), temp)) != -1"
    ),
}.items():
    evaluate(label, condition_with_store(condition))

# A compound assignment evaluates the array lvalue once and exposes the
# loaded value as the expression result.  If uopt removes the identity
# operation and redundant write, its pre-optimization topology can still
# force the raw array load ahead of the hubName side effect.
for label, condition in {
    "compound-add0": (
        f"({array_lvalue} += ((cur->hubName = levelName), 0)) != -1"
    ),
    "compound-sub0": (
        f"({array_lvalue} -= ((cur->hubName = levelName), 0)) != -1"
    ),
    "compound-or0": (
        f"({array_lvalue} |= ((cur->hubName = levelName), 0)) != -1"
    ),
    "compound-xor0": (
        f"({array_lvalue} ^= ((cur->hubName = levelName), 0)) != -1"
    ),
    "compound-andm1": (
        f"({array_lvalue} &= ((cur->hubName = levelName), -1)) != -1"
    ),
    "compound-mul1": (
        f"({array_lvalue} *= ((cur->hubName = levelName), 1)) != -1"
    ),
    "compound-div1": (
        f"({array_lvalue} /= ((cur->hubName = levelName), 1)) != -1"
    ),
}.items():
    evaluate(label, condition_with_store(condition))

# Put the unconditional store in the noncommutative comparison's constant
# operand.  Unlike a preceding C statement, this gives cfe an expression
# graph whose left operand is the raw load and whose right operand performs
# the store before producing -1.
for label, condition in {
    "compare-rhs-store-raw": (
        f"{array_lvalue} != ((cur->hubName = levelName), -1)"
    ),
    "compare-rhs-store-temp": (
        f"(temp = {array_lvalue}) != ((cur->hubName = levelName), -1)"
    ),
    "compare-rhs-store-temp2": (
        f"(temp = (temp = {array_lvalue})) != "
        "((cur->hubName = levelName), -1)"
    ),
    "compare-rhs-store-selected": (
        f"(selectedTrack = {array_lvalue}) != "
        "((cur->hubName = levelName), -1)"
    ),
    "compare-lhs-store-raw": (
        f"((cur->hubName = levelName), -1) != {array_lvalue}"
    ),
    "compare-lhs-store-temp": (
        f"((cur->hubName = levelName), -1) != "
        f"(temp = {array_lvalue})"
    ),
    "compare-lhs-store-selected": (
        f"((cur->hubName = levelName), -1) != "
        f"(selectedTrack = {array_lvalue})"
    ),
    "compare-lhs-store-raw-eq": (
        f"((cur->hubName = levelName), -1) == {array_lvalue}"
    ),
    "subtract-rhs-store": (
        f"({array_lvalue} - ((cur->hubName = levelName), -1)) != 0"
    ),
}.items():
    evaluate(label, condition_with_store(condition))

for label, condition in {
    "cond-short-and-store-else": (
        "(gTrackSelectIDs[trackY][trackX] != -1) && "
        "((cur->hubName = levelName), 1)"
    ),
    "cond-short-and-eq-else": (
        "(gTrackSelectIDs[trackY][trackX] != -1) && "
        "((cur->hubName = levelName) == levelName)"
    ),
}.items():
    candidate = condition_with_store(condition)
    candidate = candidate.replace(
        "                } else {\n                    cur->trackName = gQMarkPtr;",
        "                } else {\n"
        "                    cur->hubName = levelName;\n"
        "                    cur->trackName = gQMarkPtr;",
        1,
    )
    evaluate(label, candidate)

for label, condition in {
    "cond-seq-temp": (
        "(temp = gTrackSelectIDs[trackY][trackX], "
        "cur->hubName = levelName, temp != -1)"
    ),
    "cond-seq-temp-result": (
        "(temp = gTrackSelectIDs[trackY][trackX], "
        "cur->hubName = levelName, temp) != -1"
    ),
    "cond-seq-selected": (
        "(selectedTrack = gTrackSelectIDs[trackY][trackX], "
        "cur->hubName = levelName, selectedTrack != -1)"
    ),
    "cond-seq-selected-result": (
        "(selectedTrack = gTrackSelectIDs[trackY][trackX], "
        "cur->hubName = levelName, selectedTrack) != -1"
    ),
}.items():
    evaluate(label, condition_with_store(condition))
