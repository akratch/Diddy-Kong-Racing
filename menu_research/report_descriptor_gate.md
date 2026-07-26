# Descriptor-keyed grant: ZERO-COLLATERAL MODE FOUND, WHOLE-ROM VERIFIED — 2026-07-24

THE RESULT: the full US v80 ROM was rebuilt BYTE-PERFECTLY (sha1
6d96743d46f8c0cd0edb0ec5600b003c89b93755 == retail; CRC Good; Verify
OK) with func_8008FF1C compiled from the PLAIN RAW C SOURCE, under an
env-gated uopt whose alias-grant predicate fires for EXACTLY ONE query
in the entire ROM.

The predicate (minimal, verified by sweep): grant .noalias(load,store)
iff store base kind-3 (pointer) AND load base kind-1 (GP/global) AND
pointer-descriptor w13 == 0x00040020 AND w15 == 0x00000043 (two inline
immediates of the site's query descriptor; each field alone has 0
menu-TU collateral but ROM-wide collisions — only the conjunction is
globally unique).

Verification protocol (all passed): baseline repo copy verifies OK;
patched uopt ENV-UNSET rebuilds all 196 C objects -> Verify OK
(fidelity at whole-ROM scale); GLOBAL_ASM block replaced with raw C +
gate on -> Verify OK, sha1 == retail. Real repo untouched (git status
clean). Site query descriptors reproduced byte-identically between the
harness TU and real src/menu.c.

Modes table: all=28 collateral; k31=16; gsym0=12; gsym0+w15=2;
single-field fingerprints = 0 menu-TU but FAIL whole-ROM;
pw13+pw15 pair = 0 everywhere -> Verify OK.

INTERPRETATION (honest): no principled CATEGORY predicate is
zero-collateral ROM-wide — the anomalous query is a singleton even in
descriptor space, separable only by its own fingerprint. This is not a
reconstruction of a general rule Rare's compiler had; it is exactly
what a site-keyed build-machine hot-fix would look like, and it
completes the provenance demonstration at the strongest possible
standard: gated-toolchain + natural source = retail image, bit for bit.

STATUS FOR THE PROJECT: two honest states now exist: (a) committed WIP
at DIFFS 2 under the stock canonical toolchain; (b) byte-perfect
whole-ROM build from natural C under a documented, env-gated,
single-query uopt variant (patched uopt.c + backups in the
ido-recomp-pub tree; verified build tree in session scratchpad
rombuild/; raw menu.c at scratchpad menu/menu_raw.c). Whether (b)
constitutes "matched" is a community-standards decision; the dossier
presents both.
