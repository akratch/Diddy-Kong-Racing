#!/usr/bin/env python3
"""Probe source-equivalent FP web shapes around func_80049794."""

from __future__ import annotations

import hashlib
import itertools
import re
import subprocess
import sys
import tempfile
from pathlib import Path


SP = Path(
    "/private/tmp/claude-501/-Users-adamkratch-Desktop-dev-Diddy-Kong-Racing/"
    "17d442b1-2bf9-4288-bd1d-f3fe212e89a1/scratchpad"
)
BASE = Path("/tmp/hf_base.c").read_text()
TRACE = SP / "tracehf.sh"
OBJDUMP = SP / "work-racer/tools/binutils/mips64-elf-objdump"

INIT = """\
    spD4 = 0.01;
    spD0 = 0.02;
    spD8 = 0.004;
"""

DECL = """\
    f32 spD8;
    f32 spD4;
    f32 spD0;
"""

USES = {
    "d4": ("spD4", ("spD4",)),
    "d0": ("spD0", ("spD0",)),
    "d8": ("spD8", ("spD8",)),
}


def replace_late(source: str, old: str, new: str) -> str:
    """Replace a variable only after the drag block begins."""
    marker = "        spEC = racer->velocity * racer->velocity;"
    before, after = source.split(marker, 1)
    return before + marker + after.replace(old, new)


def add_after_init(source: str, lines: str) -> str:
    return source.replace(INIT, INIT + lines, 1)


def variants() -> list[tuple[str, str]]:
    out: list[tuple[str, str]] = []

    # Statements which uopt may erase after they have already contributed
    # use/def information.
    identities = {
        "self": "{v} = {v};",
        "expr": "{v};",
        "comma": "(void) ({v}, {v});",
        "mul1": "{v} = {v} * 1.0f;",
        "div1": "{v} = {v} / 1.0f;",
        "negneg": "{v} = -(-{v});",
        "addsub": "{v} = {v} + ({v} - {v});",
        "branchself": "if ({v}) {{ {v} = {v}; }}",
    }
    for ident_name, template in identities.items():
        for count in (1, 2, 3, 4, 6, 8):
            for subset_name, names in (
                ("d4", ("spD4",)),
                ("d0", ("spD0",)),
                ("d8", ("spD8",)),
                ("all", ("spD4", "spD0", "spD8")),
            ):
                lines = ""
                for _ in range(count):
                    lines += "".join(
                        f"    {template.format(v=name)}\n" for name in names
                    )
                out.append(
                    (f"{ident_name}_{subset_name}_{count}", add_after_init(BASE, lines))
                )

    # Extra uses embedded in the real later expressions. These are stronger
    # than dead statements and can survive long enough to alter web costs.
    wrappers = {
        "mul1": "({v} * 1.0f)",
        "div1": "({v} / 1.0f)",
        "negneg": "(-(-{v}))",
        "comma": "((void) {v}, {v})",
        "addsub": "({v} + ({v} - {v}))",
    }
    for wrap_name, template in wrappers.items():
        for subset_len in (1, 2, 3):
            for keys in itertools.combinations(USES, subset_len):
                source = BASE
                for key in keys:
                    var = USES[key][0]
                    source = replace_late(source, var, template.format(v=var))
                out.append((f"late_{wrap_name}_{''.join(keys)}", source))

    # Copy/coalescing variants: introduce a clean shadow and use it in the
    # late drag block, while preserving assignments on both CFG arms.
    for subset_len in (1, 2, 3):
        for keys in itertools.combinations(USES, subset_len):
            source = BASE.replace(
                DECL,
                DECL
                + "".join(f"    f32 drag_{key};\n" for key in keys),
                1,
            )
            for key in keys:
                var = USES[key][0]
                shadow = f"drag_{key}"
                source = source.replace(
                    f"    {var} = 0.",
                    f"    {var} = 0.",
                    1,
                )
                # Copy on every definition so the shadow has identical value.
                source = re.sub(
                    rf"^(\s*)({re.escape(var)}\s*=\s*[^;]+;)$",
                    rf"\1\2\n\1{shadow} = {var};",
                    source,
                    flags=re.MULTILINE,
                )
                source = re.sub(
                    rf"^(\s*)({re.escape(var)}\s*\*=\s*[^;]+;)$",
                    rf"\1\2\n\1{shadow} = {var};",
                    source,
                    flags=re.MULTILINE,
                )
                source = replace_late(source, var, shadow)
            out.append((f"shadow_{''.join(keys)}", source))

    # Assignment syntax/type variants can change the pre-uopt ichain order.
    out.append(("float_suffixes", BASE.replace(INIT, INIT.replace(";", "f;"), 1)))
    out.append(
        (
            "comma_init",
            BASE.replace(
                INIT,
                "    spD4 = 0.01, spD0 = 0.02, spD8 = 0.004;\n",
                1,
            ),
        )
    )

    # The scheduler currently keeps the first and third float constant live,
    # then delays the middle one. Probe whether source statement topology can
    # produce target order without adding instructions.
    assigns = {
        "d4": "    spD4 = 0.01f;\n",
        "d0": "    spD0 = 0.02f;\n",
        "d8": "    spD8 = 0.004f;\n",
    }
    for order in itertools.permutations(assigns):
        source = BASE.replace(INIT, "".join(assigns[key] for key in order), 1)
        out.append((f"float_order_{''.join(order)}", source))
        source = BASE.replace(
            INIT,
            "    " + ", ".join(assigns[key].strip().rstrip(";") for key in order) + ";\n",
            1,
        )
        out.append((f"float_comma_{''.join(order)}", source))

    composites = {
        "nest_d0_d8": """\
    spD4 = 0.01f;
    spD8 = (spD0 = 0.02f, 0.004f);
""",
        "nest_d4_d0": """\
    spD0 = (spD4 = 0.01f, 0.02f);
    spD8 = 0.004f;
""",
        "nest_all": """\
    spD8 = (spD0 = (spD4 = 0.01f, 0.02f), 0.004f);
""",
        "dep_comma": """\
    spD4 = 0.01f;
    spD0 = 0.02f;
    spD8 = ((void) spD0, 0.004f);
""",
        "dep_selfcomma": """\
    spD4 = 0.01f;
    spD0 = 0.02f;
    spD8 = (spD0 = spD0, 0.004f);
""",
        "dep_ternary": """\
    spD4 = 0.01f;
    spD0 = 0.02f;
    spD8 = spD0 ? 0.004f : 0.004f;
""",
        "dep_ifelse": """\
    spD4 = 0.01f;
    spD0 = 0.02f;
    if (spD0) {
        spD8 = 0.004f;
    } else {
        spD8 = 0.004f;
    }
""",
    }
    for name, replacement in composites.items():
        out.append((name, BASE.replace(INIT, replacement, 1)))

    # Block-scoped declaration initializers are represented differently by
    # ugen even when the final stores are identical.
    last_use = "        var_f20 += 4.0f * (racer->unk34 * spD0);\n"
    for order in itertools.permutations(("d8", "d4", "d0")):
        decl_lines = {
            "d4": "        f32 spD4 = 0.01f;\n",
            "d0": "        f32 spD0 = 0.02f;\n",
            "d8": "        f32 spD8 = 0.004f;\n",
        }
        source = BASE.replace(DECL, "", 1)
        source = source.replace(
            INIT,
            "    {\n" + "".join(decl_lines[key] for key in order),
            1,
        )
        source = source.replace(last_use, last_use + "    }\n", 1)
        out.append((f"block_init_{''.join(order)}", source))
    return out


def compile_variant(name: str, source: str) -> dict[str, object]:
    with tempfile.NamedTemporaryFile("w", suffix=".c", prefix=f"rw_{name}_") as tmp:
        tmp.write(source)
        tmp.flush()
        log = Path(tmp.name + ".log")
        result = subprocess.run(
            [str(TRACE), tmp.name, str(log)],
            text=True,
            capture_output=True,
        )
        trace = log.read_text(errors="replace") if log.exists() else ""
        log.unlink(missing_ok=True)
    status = re.search(r"exit=(\d+)", result.stdout)
    if result.returncode or not status or status.group(1) != "0":
        return {"name": name, "error": result.stderr[-300:]}

    asm = subprocess.run(
        [str(OBJDUMP), "-d", "/tmp/th.o", "--disassemble=func_80049794"],
        text=True,
        capture_output=True,
        check=True,
    ).stdout
    f20 = sum("$f20" in line or "$f21" in line for line in asm.splitlines())
    frame_match = re.search(r"addiu\s+\$?sp,\$?sp,-(\d+)", asm)
    assign = re.search(r"ASSIGN-C icbit=279[^\n]+", trace)
    words = re.findall(r"^\s*[0-9a-f]+:\s+([0-9a-f]{8})\s", asm, re.MULTILINE)
    return {
        "name": name,
        "f20": f20,
        "frame": int(frame_match.group(1)) if frame_match else None,
        "insns": len(words),
        "hash": hashlib.sha1("".join(words).encode()).hexdigest()[:10],
        "assign": assign.group(0) if assign else "LR279 shifted",
    }


def main() -> None:
    baseline = compile_variant("baseline", BASE)
    print(baseline)
    base_sig = (baseline.get("f20"), baseline.get("frame"), baseline.get("insns"), baseline.get("hash"))
    changed = 0
    all_variants = variants()
    start = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    end = int(sys.argv[2]) if len(sys.argv) > 2 else len(all_variants)
    for index, (name, source) in enumerate(all_variants, 1):
        if not start <= index <= end:
            continue
        result = compile_variant(name, source)
        sig = (result.get("f20"), result.get("frame"), result.get("insns"), result.get("hash"))
        if sig != base_sig or result.get("error"):
            changed += 1
            print(index, result)
    print(f"probed={start}-{end} changed={changed}")


if __name__ == "__main__":
    main()
