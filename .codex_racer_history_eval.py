#!/usr/bin/env python3
"""Compile every distinct historical func_80049794 body in git history."""

from __future__ import annotations

import concurrent.futures
import hashlib
import runpy
import subprocess


ORACLE = runpy.run_path("/tmp/codex_racer_oracle.py")
BASE = open("/tmp/codex_unk34_left_associative.c", encoding="utf-8").read()
SIGNATURE = "void func_80049794("


def extract_function(source: str) -> str | None:
    start = source.find(SIGNATURE)
    if start < 0:
        return None
    brace = source.find("{", start)
    if brace < 0:
        return None
    depth = 0
    state = "code"
    index = brace
    while index < len(source):
        char = source[index]
        next_char = source[index + 1] if index + 1 < len(source) else ""
        if state == "code":
            if char == "/" and next_char == "/":
                state = "line_comment"
                index += 2
                continue
            if char == "/" and next_char == "*":
                state = "block_comment"
                index += 2
                continue
            if char == '"':
                state = "string"
            elif char == "'":
                state = "character"
            elif char == "{":
                depth += 1
            elif char == "}":
                depth -= 1
                if depth == 0:
                    return source[start : index + 1] + "\n"
        elif state == "line_comment":
            if char == "\n":
                state = "code"
        elif state == "block_comment":
            if char == "*" and next_char == "/":
                state = "code"
                index += 2
                continue
        elif state in ("string", "character"):
            if char == "\\":
                index += 2
                continue
            if (state == "string" and char == '"') or (
                state == "character" and char == "'"
            ):
                state = "code"
        index += 1
    return None


def replace_base(function: str) -> str:
    current = extract_function(BASE)
    if current is None:
        raise ValueError("base function missing")
    return BASE.replace(current, function, 1)


def git_text(*args: str) -> str:
    return subprocess.run(
        ("git", *args),
        check=True,
        capture_output=True,
        text=True,
    ).stdout


def collect() -> list[tuple[str, str, str]]:
    revisions = git_text("rev-list", "--all", "--", "src/racer.c").splitlines()
    unique: dict[str, tuple[str, str, str]] = {}
    for revision in revisions:
        proc = subprocess.run(
            ("git", "show", f"{revision}:src/racer.c"),
            check=False,
            capture_output=True,
            text=True,
        )
        if proc.returncode != 0:
            continue
        function = extract_function(proc.stdout)
        if function is None:
            continue
        digest = hashlib.sha1(function.encode()).hexdigest()[:12]
        if digest in unique:
            continue
        subject = git_text("show", "-s", "--format=%cs %s", revision).strip()
        unique[digest] = (revision, subject, function)
    return list(unique.values())


def evaluate(case: tuple[str, str, str]) -> tuple:
    revision, subject, function = case
    source = replace_base(function)
    tag = revision[:12]
    path = f"/tmp/codex_racer_history_{tag}.c"
    with open(path, "w", encoding="utf-8") as output:
        output.write(source)
    result = ORACLE["evaluate"](
        source, keep=f"/tmp/codex_racer_history_{tag}.o"
    )
    return revision, subject, function, result


def main() -> None:
    cases = collect()
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        rows = list(executor.map(evaluate, cases))
    rows.sort(
        key=lambda row: (
            not row[3].get("ok"),
            row[3].get("mismatch", 999999),
            abs(row[3].get("insns", 9999) - 2625),
            row[3].get("norm", 9999),
            row[0],
        )
    )
    for revision, subject, function, result in rows:
        if result.get("ok"):
            print(
                revision[:12],
                subject,
                ORACLE["concise"](result),
                result.get("fp"),
            )
        else:
            error = str(result.get("error", "")).splitlines()
            print(
                revision[:12],
                subject,
                "ERROR",
                error[-1] if error else "",
            )
    print(
        "tested",
        len(rows),
        "compiled",
        sum(row[3].get("ok") for row in rows),
        "promoted",
        sum(row[3].get("f20_operands", 0) > 0 for row in rows),
    )


if __name__ == "__main__":
    main()
