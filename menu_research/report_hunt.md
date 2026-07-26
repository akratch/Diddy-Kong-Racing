# ugen hunt report — "real binary" leg (func_8008FF1C, DKR)

Verdict: no ugen variant on this machine produces DIFFS 0 on v_natural or
v_base. No SGI 5.3 patch ever shipped a ugen (full manifest sweep of both patch
CDs). Non-5.3 ugens either leave func_8008FF1C byte-identical to stock (5.1/5.2)
or collapse MORE aggressively into the 133 basin (6.0/7.1/7.4.4) — opposite of
the pool-temp behavior the target requires — and all break 4-52 currently
matched functions as collateral.

## 1. Inventory — IRIX MIPS originals (deduped by md5)

| md5 | size | arch | provenance | behavior group |
|---|---|---|---|---|
| a6790eb2848622aeefcba8ed25b907de | 434176 | ECOFF | IDO 4.1 (ext/ido4.1, ext/ido4.1_decompme) | untestable (recomp.elf: "Not an ELF file") |
| 68481c4b0b133be5be423d5066b6620b | 539432 | ELF MIPS-I | IDO 5.1 (ext/ido51; fetched file-by-file — its cfe/copt are "404: Not Found" stubs; + ugen.fixed dbea3b53) | B |
| 80310c93ac61148a28d810ec123b1fae | 535192 | ELF MIPS-I | IDO 5.2 (ext/ido5.2; + ugen.fixed ef881c05) | B |
| 9fcff9373191b3e6562cb9378170a7b8 | 547616 | ELF MIPS-I | IDO 5.3 community binary — identical in ido5.3_c++ tarball, ido53repo, both recomp trees, 007 irix root | A (reference) |
| 52809b3edbd7be44ba5f6fc1de02a091 | 513032 | ELF MIPS-I | IDO 6.0 (ext/ido6.0; prior hunt mislabeled "61") | C |
| 100a4cc82296c27584a0f38081510849 | 496648 | ELF MIPS-II | IDO 7.1 (ido-recomp trees) | C |
| b53b0fec0c1a8828e07b3a8704f3ff48 | 513032 | ELF MIPS-II | MIPSpro 7.4.4 (ext/mipspro7.4.4) | C |

Exactly ONE 5.3 ugen build exists on this machine (9fcff937 everywhere).
No CD-original-vs-community split for ugen (unlike as1).

Natives: reference $REPO/tools/ido-recomp/macos/ugen (f8e8a9f8, universal;
self-reports "IDO 5.3 ugen static recompilation, Decompals version") = recomp of
9fcff937. hunt/natives has ugen_52/61/71/71nc/744 (all run) and ugen_51
(broken: asserts start >= MEM_REGION_START — 5.1 data starts at 0x300000, below
the libc's 0xfb00000). Built this session: $MENU/ugenhunt/ugen_51low from
ugen.fixed + private libc_impl (MEM_REGION_START 0x200000, LIBC_ADDR
0x10100000) — works for real compiles. Linux recomps (ext/bk, 007) are
redundant community-5.3 recomps, not runnable on macOS.

Searched: all of $OLD, $REPO/tools, ~/Desktop/dev (incl. n64_stuff/007), /opt,
/usr/local, ~/Downloads, ~/Documents, /Volumes, mdfind. Nothing further exists.

## 2. Patch manifests — does any 5.3 patch ship ugen? NO.

Swept every .idb under dec97 5.3 patch set (207 patches), supportfolio 5.3 CD
(191 patches), supportfolio 6.2 CD for ugen/uopt/as1/as0/cfe/copt/ujoin/umerge/
uloop/usplit:

- patchSG0000260: usr/lib/as1 only
- patchSG0001078: usr/lib/cfe (+ sysgen copy) only
- patchSG0001260: usr/lib/uopt only
- every other patch: no compiler pass files
- patchSG0001118 absent from both patch CDs (dirs jump 1113 -> 1122)

Other media negative for compilers: SGI-Nintendo-Ultra-64.iso (EFS; only
cimpact/mekton/impact_demos, idbs have zero compiler files), noa9801.iso
(NuSystem PC SDK), n64sdk 7z (PC installer), irix_tape ultra.idb.

## 3. Fidelity gate

Candidate toolchain = copy of $REPO/tools/ido-recomp/macos with only ugen
replaced; USR_LIB redirect (run_candidate.sh mechanism). Control TU
$MENU/kwork_base/kcand.c: reference compile byte-deterministic (md5 a9c6a3c9
twice); CTRL toolchain (instrumented out/ugen, env unset) byte-identical.
Private mw harness reproduces stock scores exactly (133 / 2). $OLD/menuwork
untouched; no tracked repo file modified.

## 4. Test matrix

| candidate | kcand.c object | v_natural | v_base | fingerprint | collateral (226 fns) |
|---|---|---|---|---|---|
| CTRL (5.3 instr.) | byte-identical | 133 | 2 | = stock | 0 differ |
| IDO 5.1 (ugen_51low) | group B bc872ac0 | 133 | 2 | = stock both | 4 differ (load_menu_text, init_title_screen_variables, menu_options_loop, get_language — all matched C); func_8008FF1C untouched |
| IDO 5.2 (ugen_52) | group B (same bytes as 5.1) | 133 | 2 | = stock both | same 4; func_8008FF1C untouched |
| IDO 6.0 (ugen_61 + fresh re-recomp verified) | group C e2a2f764 | 133 | 133 | v_natural = stock; v_base output == stock v_natural output (same basin) | 52 differ incl. func_8008FF1C; as1 warns "version stamps wrong in binasm file" |
| IDO 7.1 / 7.1nc / 7.4.4 | group C (identical bytes to 6.0) | 133 | 133 | same as 6.0 | same as 6.0 |
| IDO 5.1 stock native | COMPILE FAIL (libc assert) | — | — | — | superseded by ugen_51low |
| IDO 4.1 | untestable (ECOFF) | — | — | — | — |

No DIFFS 0 anywhere; collateral-zero check never triggered (whole-object
function diffs run anyway, above).

## 5. Findings

1. ugen genuinely had never been isolated before (prior table: uopt/as1/cfe
   isolates + "full" swaps only). Now definitive.
2. Three behavior groups: A=5.3, B=5.1/5.2 (outputs byte-identical to each
   other), C=6.0/7.1/7.4.4 (outputs byte-identical to each other — codegen for
   this -mips1 -O2 TU unchanged 6.0 through 7.4.4).
3. Group B: precise negative — older ugen compiles func_8008FF1C to the same
   bytes as stock; the ilod-into-web collapse is stable across 5.1->5.3.
4. Group C: wrong direction — dissolves even the v_base double-assignment
   trick; later ugens collapse MORE, never less. Target needs LESS collapse
   (pool temp $t2 for the branch-feeding lh).
5. Version axis exhausted in both directions on this machine; patch record says
   SGI never patched 5.3 ugen. A "different retail ugen" now requires a
   5.3-lineage build that is none of the seven binaries above.

## 6. What would need to be obtained externally

- IDO 5.3 original pressed CD images other than the community "IDO 5.3 with
  C++" redistribution (e.g. "IRIS Development Option 5.3", Dec 1994 media, and
  the IDO 5.3/C++ 4.0 variants) — to check the pressed-CD ugen against
  9fcff937 (the as1 precedent shows community binaries can be patch builds).
- patchSG0001118 (absent here) — to read its manifest and close the "3
  compiler patches" bookkeeping (on-disk evidence: 260=as1, 1078=cfe,
  1260=uopt).
- IDO 6.x-for-IRIX-5.3 intermediates (6.0.1/6.1) — low priority; 6.x lineage
  already diverges in 52 functions, essentially excluded.
- Rare-specific: unnumbered SGI support hot-fix binaries — untraceable except
  via archival Rare material.

## 7. Artifacts

$MENU/ugenhunt/: tc_* toolchains, obj_*.o, score_*.txt, ugen_51low +
libc_impl_lowmem.c, ugen51.c/ugen41.c intermediates, mw/ private harness,
ccflags.sh. Nothing tracked modified; nothing needed restoring.
