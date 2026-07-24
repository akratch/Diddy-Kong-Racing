#!/usr/bin/env python3
"""Detailed asm-differ report for func_80017A18 candidates.

This deliberately imports the same asm-differ module and uses the same
objdump flags as realscore.py.  It is a diagnostic companion to that scorer:
the total score must agree exactly, while this tool also prints the individual
penalty buckets and the non-matching aligned instruction pairs.
"""

import importlib.util
import os
import runpy
import subprocess
import sys
import tempfile


REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
SP = (
    "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
    "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad"
)
TARGET = f"{SP}/work-objects/nonmatchings/func_80017A18/target.o"
OBJD = runpy.run_path(f"{SP}/iso_sweep.py")["OBJD"]
FUNC = "func_80017A18"


def load_asmdiff():
    original_argv = sys.argv[:]
    sys.argv = ["diff.py", FUNC]
    spec = importlib.util.spec_from_file_location(
        "asmdiff", f"{REPO}/tools/asm-differ/diff.py"
    )
    module = importlib.util.module_from_spec(spec)
    sys.modules["asmdiff"] = module
    try:
        spec.loader.exec_module(module)
    finally:
        sys.argv = original_argv
    return module


AD = load_asmdiff()


def make_config():
    return AD.Config(
        arch=AD.get_arch("mips"),
        diff_obj=True,
        file=None,
        make=False,
        source_old_binutils=False,
        diff_section=".text",
        inlines=False,
        max_function_size_lines=100000,
        max_function_size_bytes=400000,
        formatter=AD.PlainFormatter(column_width=80),
        diff_mode=AD.DiffMode.NORMAL,
        base_shift=0,
        skip_lines=0,
        compress=None,
        show_rodata_refs=False,
        show_branches=True,
        show_line_numbers=False,
        show_source=False,
        stop_at_ret=None,
        ignore_large_imms=False,
        ignore_addr_diffs=True,
        algorithm="levenshtein",
        reg_categories={},
        diff_function_symbols=False,
    )


def objdump(obj):
    return subprocess.run(
        [OBJD, "-d", "-rz", "-j", ".text", f"--disassemble={FUNC}", obj],
        capture_output=True,
        text=True,
        check=True,
    ).stdout


def compile_candidate(path):
    if not path.endswith(".c"):
        return path, None
    fd, tmp = tempfile.mkstemp(suffix=".o", dir="/tmp")
    os.close(fd)
    result = subprocess.run(
        ["/tmp/objeval.sh", path, tmp], capture_output=True, text=True
    )
    if result.returncode or not os.path.exists(tmp) or os.path.getsize(tmp) == 0:
        if os.path.exists(tmp):
            os.unlink(tmp)
        raise SystemExit(f"compile failed for {path}\n{result.stderr}")
    return tmp, tmp


def component_score(base, candidate, **penalties):
    config = make_config()
    config.penalty_stackdiff = penalties.get("stack", 0)
    config.penalty_regalloc = penalties.get("reg", 0)
    config.penalty_reordering = penalties.get("reorder", 0)
    config.penalty_insertion = penalties.get("insert", 0)
    config.penalty_deletion = penalties.get("delete", 0)
    return AD.do_diff(base, candidate, config).score


def main():
    if len(sys.argv) != 2:
        raise SystemExit(f"usage: {sys.argv[0]} <candidate.c|candidate.o>")
    obj, tmp = compile_candidate(sys.argv[1])
    try:
        config = make_config()
        base = AD.process(objdump(TARGET), config)
        candidate = AD.process(objdump(obj), config)
        diff = AD.do_diff(base, candidate, config)
        components = {
            "stack": component_score(base, candidate, stack=1),
            "reg": component_score(base, candidate, reg=5),
            "reorder": component_score(base, candidate, reorder=60),
            "insert": component_score(base, candidate, insert=100),
            "delete": component_score(base, candidate, delete=100),
        }
        pct = 100.0 * (1.0 - diff.score / diff.max_score)
        print(
            f"score={diff.score} {pct:.2f}% max={diff.max_score} "
            + " ".join(f"{key}={value}" for key, value in components.items())
        )
        print(f"target_insns={len(base)} candidate_insns={len(candidate)}")
        print()
        for row in diff.lines:
            if row.boring:
                continue
            marker = row.fmt2.plain()[:1]
            left = ""
            right = ""
            if row.line1 is not None:
                left = f"{row.line1.line_num:04x}  {row.line1.original}"
            if row.line2 is not None:
                right = f"{row.line2.line_num:04x}  {row.line2.original}"
            print(f"{marker}  {left:<46} | {right}")
    finally:
        if tmp:
            os.unlink(tmp)


if __name__ == "__main__":
    main()
