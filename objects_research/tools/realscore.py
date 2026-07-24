#!/usr/bin/env python3
"""TRUE scorer for func_80017A18 — drives the real tools/asm-differ/diff.py.

Rationale: the hand-written replica of asm-differ's weights (dscore.py) was
found to MISRANK candidates relative to decomp.me. This imports asm-differ
itself and uses its own process()/do_diff(), so the number comes from the same
code decomp.me runs.

Run with the repo venv (it has colorama/watchdog/Levenshtein):
    .venv/bin/python3 objects_research/tools/realscore.py <file.c|file.o> ...
"""
import importlib.util, os, runpy, subprocess, sys, tempfile

REPO = "/Users/adamkratch/Desktop/dev/Diddy-Kong-Racing"
SP = ("/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
      "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad")
TARGET = f"{SP}/work-objects/nonmatchings/func_80017A18/target.o"
OBJD = runpy.run_path(f"{SP}/iso_sweep.py")["OBJD"]
FUNC = "func_80017A18"

_targets = sys.argv[1:]
sys.argv = ["diff.py", FUNC]          # diff.py parses argv at import time
_spec = importlib.util.spec_from_file_location("asmdiff", f"{REPO}/tools/asm-differ/diff.py")
ad = importlib.util.module_from_spec(_spec)
sys.modules["asmdiff"] = ad           # required: dataclass resolution needs this
_spec.loader.exec_module(ad)


def make_config():
    return ad.Config(
        arch=ad.get_arch("mips"),
        diff_obj=True, file=None, make=False, source_old_binutils=False,
        diff_section=".text", inlines=False,
        max_function_size_lines=100000, max_function_size_bytes=400000,
        formatter=ad.PlainFormatter(column_width=80),
        diff_mode=ad.DiffMode.NORMAL,
        base_shift=0, skip_lines=0, compress=None,
        show_rodata_refs=False, show_branches=True, show_line_numbers=False,
        show_source=False, stop_at_ret=None, ignore_large_imms=False,
        ignore_addr_diffs=True, algorithm="levenshtein",
        reg_categories={}, diff_function_symbols=False,
    )


def objdump(obj):
    return subprocess.run(
        [OBJD, "-d", "-rz", "-j", ".text", f"--disassemble={FUNC}", obj],
        capture_output=True, text=True).stdout


def score(path, cfg):
    obj, tmp = path, None
    if path.endswith(".c"):
        fd, tmp = tempfile.mkstemp(suffix=".o", dir="/tmp"); os.close(fd)
        subprocess.run(["/tmp/objeval.sh", path, tmp], capture_output=True)
        if not os.path.exists(tmp) or os.path.getsize(tmp) == 0:
            print(f"{os.path.basename(path):46} COMPILE FAILED"); return None
        obj = tmp
    d = ad.do_diff(ad.process(objdump(TARGET), cfg),
                   ad.process(objdump(obj), cfg), cfg)
    pct = 100.0 * (1 - d.score / d.max_score) if d.max_score else 0.0
    print(f"{os.path.basename(path):46} score={d.score:>6}  {pct:6.2f}%   (max {d.max_score})")
    if tmp:
        os.unlink(tmp)
    return d.score


if __name__ == "__main__":
    cfg = make_config()
    for t in _targets:
        score(t, cfg)
