# Trace ugen oracles (2026-07-24)

Env-gated diagnostics in ugen_trace_binary (drop into a copy of the stock
toolchain, e.g. /tmp/codex-ido-trace; drive with racer_research/tools/traceeval.sh):

- CODEX_UGEN_TRACE=1       full alloc/free/queue-dump tracing to stderr
- CODEX_UGEN_HOLD_REG=14 CODEX_UGEN_HOLD_NTH=34 CODEX_UGEN_HOLD_POPS=4
                           surgical delayed release of one queue append
                           (34 = ordinal of the line-745 mask append in
                           func_80049794_best_19_wave_win.c; recount if the
                           source upstream of line 745 changes)
- CODEX_UGEN_DEFER=1|2     deferred-free flush policies (PROVEN NO-OP:
                           FIFO outcome depends only on append order)
- CODEX_UGEN_ROT=1         legacy one-shot line-765/766 rotate hack

All modes off => verified byte-identical output to the stock compiler.
