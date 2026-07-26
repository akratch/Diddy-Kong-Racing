#!/usr/bin/env python3
"""Probe IDO source spellings for a fixed floating-point register variable."""

from __future__ import annotations

import runpy


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
DECL = "    f32 var_f20;\n"

FORMS = {
    "register": "    register f32 var_f20;\n",
    "asm_dollar": '    register f32 var_f20 asm("$f20");\n',
    "asm_plain": '    register f32 var_f20 asm("f20");\n',
    "dunder_asm_dollar": '    register f32 var_f20 __asm("$f20");\n',
    "dunder_asm2_dollar": '    register f32 var_f20 __asm__("$f20");\n',
    "pragma_register": "    #pragma register var_f20 f20\n    f32 var_f20;\n",
    "pragma_reg": "    #pragma reg var_f20 f20\n    f32 var_f20;\n",
}


def main() -> None:
    for tag, declaration in FORMS.items():
        source = BASE.replace(DECL, declaration, 1)
        path = f"/tmp/codex_register_binding_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        result = ORACLE["evaluate"](
            source, keep=f"/tmp/codex_register_binding_{tag}.o"
        )
        print(tag, ORACLE["concise"](result), result.get("fp"), result.get("error"))


if __name__ == "__main__":
    main()
