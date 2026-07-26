# Online IDO 5.3 ugen survey (2026-07-24, opus agent)

## Headline verdict

No distinct 5.3-lineage ugen exists online. Every obtainable IDO 5.3
source hashes to the exact baseline md5
9fcff9373191b3e6562cb9378170a7b8 / 547,616 bytes.

Decisive: the two most INDEPENDENT 5.3 distributions — a pressed retail
CD ("IRIS Development Option 5.3.iso" from the jrra.zone mirror, EFS,
build tree `joist/5.3MR`) and SGI's own later freeware
`iris-development-option-5.3.tardist` (files dated Sep 9 1997, via the
ftp.zx.net.nz mirror of dead ftp.sgi.com) — carry a byte-for-byte
identical compiler pass set (ugen, uopt, cfe, copt, as0, as1, ujoin,
umerge all share md5s across both; cmp-verified against the local
baseline). The 5.3 ugen is a single build SGI never re-pressed.

## Screen results

| source | provenance | ugen md5 | verdict |
|---|---|---|---|
| SGI freeware tardist (ftp.zx.net.nz mirror) | SGI-official, Sep 1997 | 9fcff937... | baseline-identical |
| Pressed CD, jrra.zone "IRIS Development Option 5.3.iso" | retail EFS CD, 5.3MR | 9fcff937... | baseline-identical |
| github n64decomp/ido5.3_cc usr/lib/ugen | community canonical | 9fcff937... | baseline-identical |
| github devwizard64/ido53, decompals/ido-matching-decomp | non-fork repos | same git blob | baseline-identical |
| ido-static-recomp releases (v0.4-v1.2) | native recompiles | no MIPS original embedded | no-ugen |
| archive.org IDO 4.0.1 | 1991 ECOFF | wrong lineage | out of scope |
| archive.org IRIX 5.3 OS CDs | OS foundation media | no compiler_dev subsystem | no-ugen |
| jrra.zone IDO 5.0/5.1/6.0/6.1/6.2 ISOs | pressed CDs, other versions | already covered locally (groups B/C) | out of scope |

Full pressed-CD/tardist pass hashes: ugen 9fcff937/547616;
uopt f4ef4f08/756800; cfe 887eced2/902800; copt fd31bc2f/3597360;
as0 dea099d4/175296; as1 08b36cb5/807808; ujoin 9100c92e/101832;
umerge 37d9b162/167408. Build path all passes: joist/5.3MR/work/cmplrs/.

## New as1 provenance signal (community-relevant)

THREE distinct 5.3 as1 builds now catalogued:
1. 08b36cb5 / 807,808 — pressed CD + SGI freeware tardist + local
   ido53repo (the pressed-media original);
2. git blob c246db5371e0 / 816,064 — the n64decomp/decompals community
   git as1 (a DIFFERENT build from both others);
3. 19804fc9 / 904,272 — the banjo-kazooie tree's patchSG0001118 as1.

## Unobtainable / listing-only leads (for human chase)

- No 5.3 IDO C-compiler CD is indexed on archive.org at all (only the
  4.0.1 item exists there).
- patchSG0001118 itself was not located online (only its output as1
  survives in the bk tree); not a ugen source regardless (no 5.3 patch
  ever shipped ugen).
- The obtained pressed CD is the 5.3MR (maintenance release) pressing;
  a hypothetical pre-MR 5.3 pressing was not found in any online index.

Download budget: ~562 MB total, both images deleted post-extraction.
Extracted binaries retained (volatile, session scratchpad):
survey/extracted/{jrra53,tardist53}/usr_lib_*. survey/finds/ empty.
