# Iris Chroma 90-palette uniqueness redesign — 2026-07-21, operator-approved

Operator: the 90 Iris Chroma presets "are just greens, reds, oranges, purples being repeated
… each palette must be unique and correspond to its name." Confirmed against the binary:
22 accent pairs within deltaE76 < 12 (closest 11.2), 26 of 90 in the 0-60° amber wedge.

## Where the presets live (verified, not assumed)

`/usr/local/bin/LaPivot` (orig md5 922f1366ad302c9351cd49a59b4cc0a5),
`ncde_presets::kPresets` — THREE identical copies (0x213500 = the one presets()/applyPreset
disassemble to; 0x2155c0; 0x217000), 90 entries × 72 bytes, each entry 9 pointers
(id|name|dark|accent|border|panelBg|surface|ink|inkSoft) resolved via R_X86_64_RELATIVE
addends; color strings are 8-byte "#rrggbb\0" slots; vaddr == file offset.

## Design (full method + scripts in the 2026-07-21 session scratchpad; results here)

- Per-name anchors: web research (Tiffany Blue #0ABAB5 Pantone 1837, steampunk brass,
  whimsigoth, Homeric wine-dark), named HTML/X11 colors (copper #B87333, jade #00A86B,
  sienna #A0522D, cardinal), and colormagic.app name search
  (`https://colormagic.app/api/palette/search?q=`, operator's tip).
- Region-constrained optimizer spread all 90: **min pairwise accent deltaE76 = 13.3**
  (live system: 11.2 with 22 pairs < 12). 82 palettes changed, 8 byte-identical keeps.
- border/panelBg/surface hue-rotated in LCh with **L preserved** → all contrast
  relationships intact. **ink/inkSoft byte-untouched** (worst text contrast 10.6:1) —
  also keeps the binary's shared ink-string slots consistent.
- The two cross-palette shared border slots (#8a6d1e: Crimson Codex + Hermit's Lantern;
  #8a6d24: Siren's Veil + Argent Court — same sharing in all 3 copies, verified via reloc
  audit) stay UNCHANGED (gilt-frame motif suits all four) → the entire patch is same-length
  in-place writes, zero pointer/reloc edits. No color slot has references from outside the
  three tables (audited).

## Payload + step

- `notes/apply-iris.py` — the patcher. Verifies EVERY old byte before writing; clean-skips
  an already-patched binary; hard-refuses any unknown byte. Re-extracts all 3 tables after
  writing and self-verifies. 930 slots × 8 bytes.
- `notes/iris-palettes.json` — the approved values (old + new, all 6 pigments, rationale).
- `notes/iris-chroma-review.html` — the operator-approved old-vs-new review page.
- Script step **7t/10** applies it: prebak `LaPivot.prebak-20260721-irischroma`, install,
  ELF check, re-grants cap_sys_nice (binary swap drops xattr caps — 7o parity).

## Verified before staging (2026-07-21 session)

- Patched copy re-extracted: all three kPresets copies == approved set; names/ids/inks
  untouched; file size unchanged; ELF header intact. Patch reproducible (byte-identical
  on re-run). Already-applied and corrupt-input paths both tested.
- Patched binary boots and runs 10 s under Xvfb (xvfb-run smoke test) without crashing.
- `main.qml reapplyActivePreset` looks the saved palette up BY NAME at session start and
  reapplies — names unchanged → operator's active palette picks up new pigments on relog.

## Post-deploy operator checks

1. Settings → Filigree → Iris Chroma: cards show the new spreads (e.g. Copper and Flame
   is copper, Argent Court silver, The Counting House green — not a fourth amber).
2. Tap several palettes incl. one light + one dark: instant apply, text readable everywhere.
3. Relog: active palette survives with its new pigments.

USB EFF2-E845 died (hardware) 2026-07-21 00:35 — payload could NOT be synced to the USB
mirror this session; home `~/my-project` is the current staging truth. Re-sync when a new
stick exists.
