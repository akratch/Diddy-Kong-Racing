#!/usr/bin/env python3
"""Recover the two-local source topology of the opening wave-index loop."""

from __future__ import annotations

import re
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
TARGET = ORACLE["TARGET_INSNS"]
FORCED_RUNNER = "/tmp/codex_run_analysis.sh"

OLD = """\
        // UNMATCHED
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }
"""

FORMS = {
    "var_v1_for": """\
        var_v1 = gRacerWaveCount - 1;
        for (var_a0 = var_v1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == var_v1) {
            var_a0--;
        }
""",
    "var_v0_for": """\
        var_v0 = gRacerWaveCount - 1;
        for (var_a0 = var_v0;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == var_v0) {
            var_a0--;
        }
""",
    "i_for": """\
        i = gRacerWaveCount - 1;
        for (var_a0 = i;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == i) {
            var_a0--;
        }
""",
    "var_v1_assign_for": """\
        var_a0 = gRacerWaveCount - 1;
        var_v1 = var_a0;
        for (;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {}

        if (var_a0 == var_v1) {
            var_a0--;
        }
""",
    "var_v1_while": """\
        var_v1 = gRacerWaveCount - 1;
        var_a0 = var_v1;
        while (var_a0 >= 0 &&
               gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5) {
            var_a0--;
        }

        if (var_a0 == var_v1) {
            var_a0--;
        }
""",
}

OUTER = """\
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->vehicleIDPrev != VEHICLE_WIZPIG && gRacerWaveCount != 0) {
"""

COMMA_FORMS = {
    "temp_v1_comma": (
        "    s32 temp_v1;\n",
        "temp_v1",
    ),
    "var_v1_comma": ("", "var_v1"),
    "var_v0_comma": ("", "var_v0"),
    "temp_t7_comma": ("", "temp_t7"),
    "i_comma": ("", "i"),
}

COMMA_BODY = """\
        for (var_a0 = {sentinel};
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {{}}

        if (var_a0 == {sentinel}) {{
            var_a0--;
        }}
"""


def registers(assembly: str) -> list[str]:
    return re.findall(
        r"(?:\$f?\d+|\b(?:zero|at|[vk][01]|a[0-3]|t\d|s\d|s8|gp|sp|fp|ra)\b)",
        assembly,
    )


def forced_metrics(obj: str) -> dict[str, object]:
    _, candidate = ORACLE["dump_object"](obj)
    exact = sum(
        expected[1] != actual[1]
        for expected, actual in zip(TARGET, candidate)
    ) + abs(len(TARGET) - len(candidate))
    reg_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if registers(expected[1]) != registers(actual[1])
    ]
    fp_bad = [
        index
        for index, (expected, actual) in enumerate(zip(TARGET, candidate))
        if re.findall(r"\$f\d+", expected[1])
        != re.findall(r"\$f\d+", actual[1])
    ]
    return {
        "insns": len(candidate),
        "exact": exact,
        "regs": len(reg_bad) + abs(len(TARGET) - len(candidate)),
        "fp": len(fp_bad) + abs(len(TARGET) - len(candidate)),
        "reg_ranges": compact_ranges(reg_bad),
    }


def compact_ranges(indices: list[int]) -> list[tuple[int, int]]:
    if not indices:
        return []
    result = []
    first = previous = indices[0]
    for index in indices[1:]:
        if index != previous + 1:
            result.append((first, previous))
            first = index
        previous = index
    result.append((first, previous))
    return result


def main() -> None:
    if BASE.count(OLD) != 1:
        raise SystemExit("opening wave block not found")
    candidates = [
        (tag, BASE.replace(OLD, replacement, 1))
        for tag, replacement in FORMS.items()
    ]
    for tag, (declaration, sentinel) in COMMA_FORMS.items():
        source = BASE
        if declaration:
            source = source.replace(
                "    s32 temp_t7;\n",
                "    s32 temp_t7;\n" + declaration,
                1,
            )
        condition = (
            "    if (gCurrentPlayerIndex != PLAYER_COMPUTER && "
            "racer->vehicleIDPrev != VEHICLE_WIZPIG && "
            f"({sentinel} = gRacerWaveCount - 1, gRacerWaveCount != 0)) {{\n"
        )
        source = source.replace(OUTER, condition, 1)
        source = source.replace(
            OLD,
            COMMA_BODY.format(sentinel=sentinel),
            1,
        )
        candidates.append((tag, source))
    candidates.insert(0, ("baseline", BASE))
    for tag, source in candidates:
        path = f"/tmp/codex_integer_wave_{tag}.c"
        with open(path, "w", encoding="utf-8") as output:
            output.write(source)
        natural = ORACLE["evaluate"](
            source,
            keep=f"/tmp/codex_integer_wave_{tag}_natural.o",
        )
        forced_obj = f"/tmp/codex_integer_wave_{tag}_forced.o"
        proc = subprocess.run(
            [FORCED_RUNNER, path, forced_obj, forced_obj + ".trace"],
            check=False,
            capture_output=True,
            text=True,
        )
        forced = (
            forced_metrics(forced_obj)
            if proc.returncode == 0
            else {"error": proc.stderr[-1000:]}
        )
        print(
            tag,
            "natural",
            ORACLE["concise"](natural),
            natural.get("fp"),
            "forced",
            forced,
        )


if __name__ == "__main__":
    main()
