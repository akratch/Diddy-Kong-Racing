#!/usr/bin/env python3
"""Sweep targeted source-equivalent local reuse around func_80049794."""

import itertools
import re
import runpy
import sys
import tempfile
import time
from pathlib import Path


SP = (
    "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev/Diddy-Kong-Racing/"
    "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad"
)
# Correct the accidental path segment above without duplicating the long ID.
SP = SP.replace("Desktop-dev/Diddy", "Desktop-dev-Diddy")
ISO = runpy.run_path(f"{SP}/iso_sweep.py")
sys.path.insert(0, SP)
MARKER = (
    "    if (racer->approachTarget == NULL) {\n"
    "        var_f20 = obj->x_velocity;"
)
SEGMENT_DECL = "    f32 segmentZVelocity;\n"
SEGMENT_CALC = (
    "    segmentZVelocity = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +\n"
    "                       (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));\n"
    "    var_f14 = segmentZVelocity;\n"
)
REMOVABLE_DECLS = {
    "pad5": "    s32 pad5;\n",
    "pad7": "    s32 pad7;\n",
    "newSpinoutTimer": "    s8 newSpinoutTimer;\n",
    "pad2": "    s32 pad2;\n",
    "zRotationOffset": "    s32 zRotationOffset;\n",
    "var_t9": "    s32 var_t9;\n",
    "var_f6": "    f32 var_f6;\n",
    "racerTrickType": "    s32 racerTrickType;\n",
    "segmentXVelocity": "    f32 segmentXVelocity;\n",
    "pad3": "    s32 pad3;\n",
    "pad4": "    s32 pad4;\n",
}


def correct_float_tokens(source: str) -> str:
    return source.replace(
        "    spD4 = 0.01;\n"
        "    spD0 = 0.02;\n"
        "    spD8 = 0.004;\n",
        "    spD4 = 0.01f;\n"
        "    spD0 = 0.02f;\n"
        "    spD8 = 0.004f;\n",
        1,
    ).replace("        spD4 = 0.02;\n", "        spD4 = 0.02f;\n", 1)


def reuse_late(source: str, host: str) -> str:
    before, after = source.split(MARKER, 1)
    return (
        before
        + MARKER.replace("var_f20", host)
        + after.replace("var_f20", host)
    )


def reuse_segment(source: str, host: str) -> str:
    assert SEGMENT_DECL in source
    assert SEGMENT_CALC in source
    return source.replace(SEGMENT_DECL, "", 1).replace(
        SEGMENT_CALC,
        SEGMENT_CALC.replace("segmentZVelocity", host),
        1,
    )


def direct_segment(source: str) -> str:
    assert SEGMENT_DECL in source
    assert SEGMENT_CALC in source
    direct = (
        "    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +\n"
        "              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));\n"
    )
    return source.replace(SEGMENT_DECL, "", 1).replace(SEGMENT_CALC, direct, 1)


def sweep_late(host: str, start: int, end: int) -> None:
    base = reuse_late(ISO["BASE"], host)
    combos = list(itertools.combinations(ISO["FPOOL"], 3))
    hits = []
    begin = time.time()
    for index, combo in enumerate(combos[start:end], start):
        source = ISO["build"](("ox2",), combo, base=base)
        result = ISO["evaltxt"](source)
        if result and result[1]:
            hits.append((combo, result))
            print(f"HIT {host} {index} {combo} {result}", flush=True)
    print(
        f"DONE {host} {start}:{end} hits={len(hits)} "
        f"target={[item for item in hits if item[1][0] == -248 and item[1][1] == 69]} "
        f"elapsed={time.time() - begin:.1f}",
        flush=True,
    )


def sweep_segment() -> None:
    for host in ISO["FPOOL"]:
        if host in ("segmentZVelocity", "var_f14"):
            continue
        base = reuse_segment(ISO["BASE"], host)
        for label, source in (
            ("base", base),
            (
                "promo",
                ISO["build"](
                    ("ox2",),
                    ("racerVelocity", "spCC", "var_f0"),
                    base=base,
                ),
            ),
        ):
            result = ISO["evaltxt"](source)
            print(f"SEGMENT {host} {label} {result}", flush=True)


def sweep_declarations() -> None:
    promo = ISO["build"](
        ("ox2",),
        ("racerVelocity", "spCC", "var_f0"),
    )
    baseline = ISO["evaltxt"](promo)
    print(f"DECL baseline {baseline}", flush=True)
    names = list(REMOVABLE_DECLS)
    for count in (1, 2, 3):
        for combo in itertools.combinations(names, count):
            source = promo
            for name in combo:
                declaration = REMOVABLE_DECLS[name]
                assert declaration in source
                source = source.replace(declaration, "", 1)
            result = ISO["evaltxt"](source)
            if result and (result[0] != -256 or result[1] != 76):
                print(f"DECL {combo} {result}", flush=True)


def score_declarations() -> None:
    import dash
    import probe_eval

    promo = ISO["build"](
        ("ox2",),
        ("racerVelocity", "spCC", "var_f0"),
    )
    candidates = []
    names = list(REMOVABLE_DECLS)
    for combo in itertools.combinations(names, 2):
        source = promo
        for name in combo:
            source = source.replace(REMOVABLE_DECLS[name], "", 1)
        for suffixes in (False, True):
            candidate = source
            if suffixes:
                candidate = candidate.replace(
                    "    spD4 = 0.01;\n"
                    "    spD0 = 0.02;\n"
                    "    spD8 = 0.004;\n",
                    "    spD4 = 0.01f;\n"
                    "    spD0 = 0.02f;\n"
                    "    spD8 = 0.004f;\n",
                    1,
                )
            with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
                src.write(candidate)
                src.flush()
                obj, error, output = probe_eval.compile_src(src.name)
                if obj is None:
                    print(f"SCORE FAIL {combo} float={suffixes}", flush=True)
                    continue
                words, assembly = probe_eval.words_and_asm(obj)
                Path(obj).unlink(missing_ok=True)
            result = {
                "raw": probe_eval.score_words(words),
                "norm": dash.norm_diff(assembly),
                "frame": dash.frame_of(assembly),
                "insns": len(words),
                "f20": probe_eval.f20_uses(assembly),
            }
            candidates.append((result["raw"], combo, suffixes, result, candidate))
            print(
                f"SCORE {combo} float={suffixes} {result}",
                flush=True,
            )
    candidates.sort(key=lambda item: item[0])
    for rank, item in enumerate(candidates[:10], 1):
        print(f"BEST {rank} {item[:4]}", flush=True)
    if candidates:
        Path("/tmp/racer_decl_best.c").write_text(candidates[0][4])


def score_direct_declarations() -> None:
    import dash
    import probe_eval

    promo = ISO["build"](
        ("ox2",),
        ("racerVelocity", "spCC", "var_f0"),
        base=direct_segment(ISO["BASE"]),
    )
    candidates = []
    names = list(REMOVABLE_DECLS)
    for count in (1, 2, 3):
        for combo in itertools.combinations(names, count):
            source = promo
            for name in combo:
                source = source.replace(REMOVABLE_DECLS[name], "", 1)
            candidate = source.replace(
                "    spD4 = 0.01;\n"
                "    spD0 = 0.02;\n"
                "    spD8 = 0.004;\n",
                "    spD4 = 0.01f;\n"
                "    spD0 = 0.02f;\n"
                "    spD8 = 0.004f;\n",
                1,
            )
            with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
                src.write(candidate)
                src.flush()
                obj, error, output = probe_eval.compile_src(src.name)
                if obj is None:
                    print(f"DIRECT FAIL {combo}", flush=True)
                    continue
                words, assembly = probe_eval.words_and_asm(obj)
                Path(obj).unlink(missing_ok=True)
            result = {
                "raw": probe_eval.score_words(words),
                "norm": dash.norm_diff(assembly),
                "frame": dash.frame_of(assembly),
                "insns": len(words),
                "f20": probe_eval.f20_uses(assembly),
            }
            if result["frame"] == -248 and result["f20"] == 69:
                candidates.append((result["raw"], combo, result, candidate))
                print(f"DIRECT {combo} {result}", flush=True)
    candidates.sort(key=lambda item: item[0])
    for rank, item in enumerate(candidates[:10], 1):
        print(f"DIRECT_BEST {rank} {item[:3]}", flush=True)
    if candidates:
        Path("/tmp/racer_direct_best.c").write_text(candidates[0][3])


def score_promoting_hosts() -> None:
    import dash
    import probe_eval

    promotions = []
    for combo in itertools.combinations(ISO["FPOOL"], 3):
        source = ISO["build"](("ox2",), combo)
        result = ISO["evaltxt"](source)
        if result and result[1]:
            promotions.append(combo)
            print(f"HOST_PROMOTES {combo} {result}", flush=True)
    print(f"HOST_PROMOTION_COUNT {len(promotions)}", flush=True)

    candidates = []
    for combo in promotions:
        shapes = {
            "two-stage": ISO["build"](("ox2",), combo)
            .replace(REMOVABLE_DECLS["pad3"], "", 1)
            .replace(REMOVABLE_DECLS["pad4"], "", 1),
            "direct": ISO["build"](
                ("ox2",), combo, base=direct_segment(ISO["BASE"])
            ).replace(REMOVABLE_DECLS["pad3"], "", 1),
        }
        for shape, source in shapes.items():
            candidate = correct_float_tokens(source)
            with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
                src.write(candidate)
                src.flush()
                obj, error, output = probe_eval.compile_src(src.name)
                if obj is None:
                    print(f"HOST FAIL {combo} {shape}", flush=True)
                    continue
                words, assembly = probe_eval.words_and_asm(obj)
                Path(obj).unlink(missing_ok=True)
            result = {
                "raw": probe_eval.score_words(words),
                "norm": dash.norm_diff(assembly),
                "frame": dash.frame_of(assembly),
                "insns": len(words),
                "f20": probe_eval.f20_uses(assembly),
            }
            if result["frame"] == -248 and result["f20"] == 69:
                candidates.append((result["raw"], combo, shape, result, candidate))
                print(f"HOST_SCORE {combo} {shape} {result}", flush=True)
    candidates.sort(key=lambda item: item[0])
    for rank, item in enumerate(candidates[:15], 1):
        print(f"HOST_BEST {rank} {item[:4]}", flush=True)
    if candidates:
        Path("/tmp/racer_host_best.c").write_text(candidates[0][4])


def score_best_host_declarations() -> None:
    import dash
    import probe_eval

    combo = ("spCC", "var_f6", "segmentXVelocity")
    base = ISO["build"](
        ("ox2",), combo, base=direct_segment(ISO["BASE"])
    )
    candidates = []
    for name, declaration in REMOVABLE_DECLS.items():
        if declaration not in base:
            continue
        candidate = correct_float_tokens(base.replace(declaration, "", 1))
        with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
            src.write(candidate)
            src.flush()
            obj, error, output = probe_eval.compile_src(src.name)
            if obj is None:
                print(f"BEST_DECL FAIL {name}", flush=True)
                continue
            words, assembly = probe_eval.words_and_asm(obj)
            Path(obj).unlink(missing_ok=True)
        result = {
            "raw": probe_eval.score_words(words),
            "norm": dash.norm_diff(assembly),
            "frame": dash.frame_of(assembly),
            "insns": len(words),
            "f20": probe_eval.f20_uses(assembly),
        }
        print(f"BEST_DECL {name} {result}", flush=True)
        if result["frame"] == -248 and result["f20"] == 69:
            candidates.append((result["raw"], name, result, candidate))
    candidates.sort(key=lambda item: item[0])
    print(f"BEST_DECL_RESULT {[item[:3] for item in candidates]}", flush=True)
    if candidates:
        Path("/tmp/racer_host_decl_best.c").write_text(candidates[0][3])


def score_host_permutations(which: str) -> None:
    import dash
    import probe_eval

    promoting_sets = []
    for combo in itertools.combinations(ISO["FPOOL"], 3):
        result = ISO["evaltxt"](ISO["build"]((which,), combo))
        if result and result[1]:
            promoting_sets.append(combo)
            print(f"PERM_SET {which} {combo} {result}", flush=True)
    print(f"PERM_SET_COUNT {which} {len(promoting_sets)}", flush=True)

    candidates = []
    seen = set()
    for host_set in promoting_sets:
        for combo in itertools.permutations(host_set):
            if combo in seen:
                continue
            seen.add(combo)
            source = ISO["build"](
                (which,), combo, base=direct_segment(ISO["BASE"])
            )
            source = source.replace(REMOVABLE_DECLS["pad3"], "", 1)
            candidate = correct_float_tokens(source)
            with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
                src.write(candidate)
                src.flush()
                obj, error, output = probe_eval.compile_src(src.name)
                if obj is None:
                    print(f"PERM FAIL {which} {combo}", flush=True)
                    continue
                words, assembly = probe_eval.words_and_asm(obj)
                Path(obj).unlink(missing_ok=True)
            result = {
                "raw": probe_eval.score_words(words),
                "norm": dash.norm_diff(assembly),
                "frame": dash.frame_of(assembly),
                "insns": len(words),
                "f20": probe_eval.f20_uses(assembly),
            }
            if result["frame"] == -248 and result["f20"] == 69:
                candidates.append((result["raw"], combo, result, candidate))
                print(f"PERM_SCORE {which} {combo} {result}", flush=True)
    candidates.sort(key=lambda item: item[0])
    for rank, item in enumerate(candidates[:20], 1):
        print(f"PERM_BEST {which} {rank} {item[:3]}", flush=True)
    if candidates:
        Path(f"/tmp/racer_{which}_perm_best.c").write_text(candidates[0][3])


def score_interpolation_shapes() -> None:
    import dash
    import probe_eval

    combo = ("spCC", "var_f6", "segmentXVelocity")
    arr = "gCurrentRacerMiscAssetPtr"
    idx = "racerMiscAssetIdx"
    current = f"{arr}[{idx}]"
    next_value = f"{arr}[{idx} + 1]"
    f = "var_f0"
    expressions = {
        "next-plus-current": (
            f"({next_value} * {f}) + ({current} * (1.0 - {f}))"
        ),
        "current-plus-next": (
            f"({current} * (1.0 - {f})) + ({next_value} * {f})"
        ),
        "next-plus-current-float1": (
            f"({next_value} * {f}) + ({current} * (1.0f - {f}))"
        ),
        "current-plus-next-float1": (
            f"({current} * (1.0f - {f})) + ({next_value} * {f})"
        ),
        "cast-next-plus-current": (
            f"(f64) ({next_value} * {f}) + "
            f"({current} * (1.0 - {f}))"
        ),
        "current-plus-cast-next": (
            f"({current} * (1.0 - {f})) + "
            f"(f64) ({next_value} * {f})"
        ),
    }
    blocks = {}
    for label, expression in expressions.items():
        blocks[label] = (
            f"    var_f14 = {expression};\n",
            False,
        )

    blocks.update(
        {
            "preload-current-segment": (
                f"    segmentZVelocity = {current};\n"
                f"    var_f14 = ({next_value} * {f}) + "
                "(segmentZVelocity * (1.0 - var_f0));\n",
                True,
            ),
            "assign-expr-current-segment": (
                f"    var_f14 = ({next_value} * {f}) + "
                f"((segmentZVelocity = {current}) * (1.0 - var_f0));\n",
                True,
            ),
            "assign-expr-current-segment-first": (
                f"    var_f14 = ((segmentZVelocity = {current}) * "
                f"(1.0 - var_f0)) + ({next_value} * {f});\n",
                True,
            ),
            "comma-current-segment": (
                f"    var_f14 = (segmentZVelocity = {current}, "
                f"({next_value} * {f}) + "
                "(segmentZVelocity * (1.0 - var_f0)));\n",
                True,
            ),
            "self-preload-current-segment": (
                f"    segmentZVelocity = (segmentZVelocity = {current});\n"
                f"    var_f14 = ({next_value} * {f}) + "
                "(segmentZVelocity * (1.0 - var_f0));\n",
                True,
            ),
            "preload-next-segment": (
                f"    segmentZVelocity = {next_value};\n"
                f"    var_f14 = (segmentZVelocity * {f}) + "
                f"({current} * (1.0 - var_f0));\n",
                True,
            ),
            "preload-both-segments": (
                f"    segmentZVelocity = {current};\n"
                f"    segmentXVelocity = {next_value};\n"
                "    var_f14 = (segmentXVelocity * var_f0) + "
                "(segmentZVelocity * (1.0 - var_f0));\n",
                True,
            ),
            "preload-current-var-f14": (
                f"    var_f14 = {current};\n"
                f"    var_f14 = ({next_value} * {f}) + "
                "(var_f14 * (1.0 - var_f0));\n",
                False,
            ),
            "preload-next-segment-current-var-f14": (
                f"    var_f14 = {current};\n"
                f"    segmentZVelocity = {next_value};\n"
                "    var_f14 = (segmentZVelocity * var_f0) + "
                "(var_f14 * (1.0 - var_f0));\n",
                True,
            ),
            "split-next-then-current": (
                f"    var_f14 = {next_value} * {f};\n"
                f"    var_f14 = var_f14 + "
                f"({current} * (1.0 - {f}));\n",
                False,
            ),
            "split-current-then-next": (
                f"    var_f14 = {current} * (1.0 - {f});\n"
                f"    var_f14 = var_f14 + ({next_value} * {f});\n",
                False,
            ),
            "compound-next-then-current": (
                f"    var_f14 = {next_value} * {f};\n"
                f"    var_f14 += {current} * (1.0 - {f});\n",
                False,
            ),
            "compound-current-then-next": (
                f"    var_f14 = {current} * (1.0 - {f});\n"
                f"    var_f14 += {next_value} * {f};\n",
                False,
            ),
        }
    )

    candidates = []
    for label, (block, keep_segment) in blocks.items():
        source = ISO["BASE"].replace(SEGMENT_CALC, block, 1)
        if not keep_segment:
            source = source.replace(SEGMENT_DECL, "", 1)
        source = ISO["build"](("ox2",), combo, base=source)
        # Removing segmentZVelocity itself supplies one four-byte reduction.
        # Shapes that retain it need two other unused declarations removed.
        source = source.replace(REMOVABLE_DECLS["pad3"], "", 1)
        if keep_segment:
            source = source.replace(REMOVABLE_DECLS["pad4"], "", 1)
        candidate = correct_float_tokens(source)
        with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
            src.write(candidate)
            src.flush()
            obj, error, output = probe_eval.compile_src(src.name)
            if obj is None:
                print(f"INTERP FAIL {label}: {error[-500:]}", flush=True)
                continue
            words, assembly = probe_eval.words_and_asm(obj)
            Path(obj).unlink(missing_ok=True)
        result = {
            "raw": probe_eval.score_words(words),
            "norm": dash.norm_diff(assembly),
            "frame": dash.frame_of(assembly),
            "insns": len(words),
            "f20": probe_eval.f20_uses(assembly),
        }
        print(f"INTERP {label} {result}", flush=True)
        if result["frame"] == -248 and result["f20"] == 69:
            candidates.append((result["raw"], label, result, candidate))
            Path(f"/tmp/racer_interp_{label}.c").write_text(candidate)
    candidates.sort(key=lambda item: item[0])
    print(f"INTERP_RESULT {[item[:3] for item in candidates]}", flush=True)
    if candidates:
        Path("/tmp/racer_interp_best.c").write_text(candidates[0][3])


def preload_current_interpolation(source: str) -> str:
    block = (
        "    segmentZVelocity = "
        "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx];\n"
        "    var_f14 = "
        "(gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) + "
        "(segmentZVelocity * (1.0 - var_f0));\n"
    )
    assert SEGMENT_CALC in source
    return source.replace(SEGMENT_CALC, block, 1)


def score_preload_holders() -> None:
    import dash
    import probe_eval

    combo = ("spCC", "var_f6", "segmentXVelocity")
    current = "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx]"
    next_value = "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1]"
    candidates = []
    for holder in ISO["FPOOL"]:
        if holder in ("var_f14", "var_f20", "segmentZVelocity"):
            continue
        block = (
            f"    {holder} = {current};\n"
            f"    var_f14 = ({next_value} * var_f0) + "
            f"({holder} * (1.0 - var_f0));\n"
        )
        source = ISO["BASE"].replace(SEGMENT_CALC, block, 1)
        source = source.replace(SEGMENT_DECL, "", 1)
        source = ISO["build"](("ox2",), combo, base=source)
        source = source.replace(REMOVABLE_DECLS["pad3"], "", 1)
        candidate = correct_float_tokens(source)
        with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
            src.write(candidate)
            src.flush()
            obj, error, output = probe_eval.compile_src(src.name)
            if obj is None:
                print(f"HOLDER FAIL {holder}: {error[-300:]}", flush=True)
                continue
            words, assembly = probe_eval.words_and_asm(obj)
            Path(obj).unlink(missing_ok=True)
        result = {
            "raw": probe_eval.score_words(words),
            "norm": dash.norm_diff(assembly),
            "frame": dash.frame_of(assembly),
            "insns": len(words),
            "f20": probe_eval.f20_uses(assembly),
        }
        print(f"HOLDER {holder} {result}", flush=True)
        if result["frame"] == -248 and result["f20"] == 69:
            candidates.append((result["norm"], result["raw"], holder, result, candidate))
            Path(f"/tmp/racer_holder_{holder}.c").write_text(candidate)
    candidates.sort(key=lambda item: (item[0], item[1]))
    print(f"HOLDER_RESULT {[item[:4] for item in candidates]}", flush=True)
    if candidates:
        Path("/tmp/racer_holder_best.c").write_text(candidates[0][4])


def score_segment_declaration_positions() -> None:
    import dash
    import probe_eval

    combo = ("spCC", "var_f6", "segmentXVelocity")
    shaped = preload_current_interpolation(ISO["BASE"])
    assert SEGMENT_DECL in shaped
    shaped = shaped.replace(SEGMENT_DECL, "", 1)

    function_start = shaped.index("void func_80049794")
    body_start = shaped.index("{\n", function_start) + 2
    declarations_end = shaped.index("\n\n    if (func_8000E138())", body_start)
    declaration_text = shaped[body_start:declarations_end]
    lines = declaration_text.splitlines(keepends=True)
    boundaries = [
        index
        for index, line in enumerate(lines)
        if re.match(r"    (?:s|u|f|Object|Mtx|Vec|Triangle)", line)
    ]

    variants = []
    for index in boundaries:
        moved_lines = list(lines)
        moved_lines.insert(index, SEGMENT_DECL)
        source = (
            shaped[:body_start]
            + "".join(moved_lines)
            + shaped[declarations_end:]
        )
        variants.append((f"top-{index:02d}-before-{lines[index].strip()}", source))

    # C90-compatible inner blocks permit a declaration at the exact point of
    # use. Test both assignment and declaration-with-initializer spellings.
    current = "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx]"
    next_value = "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1]"
    inner_assign = (
        "    {\n"
        "        f32 segmentZVelocity;\n"
        f"        segmentZVelocity = {current};\n"
        f"        var_f14 = ({next_value} * var_f0) + "
        "(segmentZVelocity * (1.0 - var_f0));\n"
        "    }\n"
    )
    inner_init = (
        "    {\n"
        f"        f32 segmentZVelocity = {current};\n"
        f"        var_f14 = ({next_value} * var_f0) + "
        "(segmentZVelocity * (1.0 - var_f0));\n"
        "    }\n"
    )
    original_shaped_block = (
        "    segmentZVelocity = "
        "gCurrentRacerMiscAssetPtr[racerMiscAssetIdx];\n"
        "    var_f14 = "
        "(gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) + "
        "(segmentZVelocity * (1.0 - var_f0));\n"
    )
    variants.append(
        ("inner-assign", shaped.replace(original_shaped_block, inner_assign, 1))
    )
    variants.append(
        ("inner-init", shaped.replace(original_shaped_block, inner_init, 1))
    )

    candidates = []
    for label, source in variants:
        source = ISO["build"](("ox2",), combo, base=source)
        source = source.replace(REMOVABLE_DECLS["pad3"], "", 1)
        source = source.replace(REMOVABLE_DECLS["pad4"], "", 1)
        candidate = correct_float_tokens(source)
        with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
            src.write(candidate)
            src.flush()
            obj, error, output = probe_eval.compile_src(src.name)
            if obj is None:
                print(f"DECLPOS FAIL {label}: {error[-300:]}", flush=True)
                continue
            words, assembly = probe_eval.words_and_asm(obj)
            Path(obj).unlink(missing_ok=True)
        result = {
            "raw": probe_eval.score_words(words),
            "norm": dash.norm_diff(assembly),
            "frame": dash.frame_of(assembly),
            "insns": len(words),
            "f20": probe_eval.f20_uses(assembly),
        }
        print(f"DECLPOS {label} {result}", flush=True)
        if result["frame"] == -248 and result["f20"] == 69:
            candidates.append((result["norm"], result["raw"], label, result, candidate))
    candidates.sort(key=lambda item: (item[0], item[1]))
    for rank, item in enumerate(candidates[:20], 1):
        print(f"DECLPOS_BEST {rank} {item[:4]}", flush=True)
    if candidates:
        Path("/tmp/racer_declpos_best.c").write_text(candidates[0][4])


def score_preload_current_hosts() -> None:
    import dash
    import probe_eval

    shaped_base = preload_current_interpolation(ISO["BASE"])
    promoting = []
    for combo in itertools.combinations(ISO["FPOOL"], 3):
        # segmentZVelocity is live in the shaped interpolation, so do not
        # overwrite it with a drag product even though the regions appear
        # disjoint at source level; test it separately only if needed.
        if "segmentZVelocity" in combo:
            continue
        source = ISO["build"](("ox2",), combo, base=shaped_base)
        result = ISO["evaltxt"](source)
        if result and result[1]:
            promoting.append(combo)
            print(f"PRELOAD_PROMOTES {combo} {result}", flush=True)
    print(f"PRELOAD_PROMOTION_COUNT {len(promoting)}", flush=True)

    candidates = []
    for combo in promoting:
        source = ISO["build"](("ox2",), combo, base=shaped_base)
        source = source.replace(REMOVABLE_DECLS["pad3"], "", 1)
        source = source.replace(REMOVABLE_DECLS["pad4"], "", 1)
        candidate = correct_float_tokens(source)
        with tempfile.NamedTemporaryFile("w", suffix=".c") as src:
            src.write(candidate)
            src.flush()
            obj, error, output = probe_eval.compile_src(src.name)
            if obj is None:
                print(f"PRELOAD FAIL {combo}", flush=True)
                continue
            words, assembly = probe_eval.words_and_asm(obj)
            Path(obj).unlink(missing_ok=True)
        result = {
            "raw": probe_eval.score_words(words),
            "norm": dash.norm_diff(assembly),
            "frame": dash.frame_of(assembly),
            "insns": len(words),
            "f20": probe_eval.f20_uses(assembly),
        }
        print(f"PRELOAD_SCORE {combo} {result}", flush=True)
        if result["frame"] == -248 and result["f20"] == 69:
            candidates.append((result["norm"], result["raw"], combo, result, candidate))
    candidates.sort(key=lambda item: (item[0], item[1]))
    for rank, item in enumerate(candidates[:20], 1):
        print(f"PRELOAD_BEST {rank} {item[:4]}", flush=True)
    if candidates:
        Path("/tmp/racer_preload_host_best.c").write_text(candidates[0][4])


def sweep_constant_placements() -> None:
    source = direct_segment(ISO["BASE"])
    init = (
        "    spD4 = 0.01;\n"
        "    spD0 = 0.02;\n"
        "    spD8 = 0.004;\n"
    )
    assert init in source
    source = source.replace(init, "", 1)
    anchors = (
        "    var_f14 = racer->velocity;\n",
        "    racerMiscAssetIdx = var_f14;\n",
        "    var_f0 = var_f14 - (s32) var_f14;",
        "    var_f14 = (gCurrentRacerMiscAssetPtr",
        "    if (racer->groundedWheels != 0) {",
    )
    assignments = (
        "    spD4 = 0.01f;\n",
        "    spD0 = 0.02f;\n",
        "    spD8 = 0.004f;\n",
    )
    hits = []
    for positions in itertools.product(range(len(anchors)), repeat=3):
        candidate = source
        for position in reversed(range(len(anchors))):
            lines = "".join(
                assignments[index]
                for index, assigned_position in enumerate(positions)
                if assigned_position == position
            )
            if lines:
                candidate = candidate.replace(
                    anchors[position], lines + anchors[position], 1
                )
        candidate = candidate.replace(
            "        spD4 = 0.02;\n", "        spD4 = 0.02f;\n", 1
        )
        result = ISO["evaltxt"](candidate)
        if result and result[1]:
            hits.append((positions, result, candidate))
            print(f"CONST_HIT {positions} {result}", flush=True)
    print(f"CONST_DONE hits={len(hits)}", flush=True)
    if hits:
        Path("/tmp/racer_constant_hit.c").write_text(hits[0][2])


def main() -> None:
    mode = sys.argv[1]
    if mode == "segment":
        sweep_segment()
        return
    if mode == "decls":
        sweep_declarations()
        return
    if mode == "score-decls":
        score_declarations()
        return
    if mode == "score-direct":
        score_direct_declarations()
        return
    if mode == "score-hosts":
        score_promoting_hosts()
        return
    if mode == "score-best-decls":
        score_best_host_declarations()
        return
    if mode == "score-ox2-perms":
        score_host_permutations("ox2")
        return
    if mode == "score-ox3-perms":
        score_host_permutations("ox3")
        return
    if mode == "score-interp":
        score_interpolation_shapes()
        return
    if mode == "score-preload-hosts":
        score_preload_current_hosts()
        return
    if mode == "score-holders":
        score_preload_holders()
        return
    if mode == "score-declpos":
        score_segment_declaration_positions()
        return
    if mode == "constants":
        sweep_constant_placements()
        return
    sweep_late(mode, int(sys.argv[2]), int(sys.argv[3]))


if __name__ == "__main__":
    main()
