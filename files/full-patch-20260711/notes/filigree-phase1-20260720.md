# Filigree Phase 1 — 2026-07-20 (instant-apply + truth fixes) — STAGED, awaiting deploy

Operator directive this session: **"everything in Filigree must do what it says.. But, with a
more smooth and refined interface."** Decisions (operator, explicit): (1) Fira Mono not in
repos → fetch from Google; (2) instant-apply **everywhere**; (3) **no palette deleting at all**,
and the Name-this-palette / Save Current authoring row does not belong in Iris Chroma —
**the 90 presets are intentional and hardcoded for a reason** (curated-paint model: each
palette = six pigments — accent/border/panelBg/surface/ink/inkSoft + dark flag; NCDE curates
the pigments, the user picks paint, never mixes it).

## Phase 0 ground-truth matrix (verified against live LaPivot + configs, NOT docs)

Every FiligreeTab engine/settings hook exists as real C++ in the running binary
(`nm -C /usr/local/bin/LaPivot`): surfaceGlass/setSurfaceGlass, widgetStyle/setWidgetStyleMap/
resetWidgetStyle, terminalConfig/setTerminalFont/setTerminalGlassTint, applyPreset, saveTheme,
darkModeLock, saveFiligreepalette/deleteFiligreepalette/filigreePalettes/setActiveFiligreepalette,
currentBasePalette, Settings::saveSurfaceGlass/saveWidgetStyleMap/saveSectionColors/
saveFontSettings/applyFontSettings/saveTextColor/resetWidgetStyle. The file header's
"NOT-YET-WIRED" claim was stale — corrected.

Persistence proven on disk: `~/.config/ncde/fonts.json` (written live 07-19 by the new %
sliders), `glass-surfaces.json`, `widget-styles.json`, `section-colors.json`, `active-theme.json`.
Consumers proven: widget styles/glass read by TopPanel/BottomPanel/Dock/MuchaClock/MuchaWeather/
MuchaStats/StatsPanel/SpacePanel/SalonPanel/ClockPanel/WeatherPanel/SalonNocturneCompact;
section colors by TopPanel/Dock/GliaBar/GliaDropMenu/GliaLeapFrogBar; spacing/leading via
ThemeTokens; outline/shadow shell-wide. ncde-terminal exists and file-watches its config.json.
**No saved custom palettes existed anywhere** (no palettes file on disk) → removing the
authoring UI orphaned nothing.

Font truth: "Noto Mono" and "Fira Mono" chips offered fonts that were NOT installed —
fc-match silently substituted Noto Sans Mono for both. FontsTab.qml is retired (SettingsPanel
comment, 2026-07-02) — Filigree's Fonts tab is canonical. Three text multipliers stack:
fontSizeScale × uiScale (engine recomputeFontSizes) × accessibilityTextScale (SetTheme/ThemeTokens
QML-side) — layering works; UI hint about the accessibility multiplier deferred to Phase 2.

## What changed (staged in full-patch step 7r + updated 7q dep payload)

- **FiligreeTab.qml** (1788 → 1643 lines; anchored edit script: notes/apply-edits.py):
  - INSTANT-APPLY everywhere. All four Apply buttons (Type/Sections/Glass/Widgets) retired.
    Chips/toggles/color-picks apply+persist at the moment of change. `pushSectionColor()` now
    calls `saveSectionColors()` itself. Glass/widget color picks call `pushSurface`/`pushWidget`
    immediately.
  - Sliders: live preview on drag, **persist on release** (new `released()` signal) — per-tick
    persistence would rewrite active-theme.json continuously during a drag and storm every
    native app's theme file-watcher. Fonts-tab sliders (Spacing/Leading/outline/shadow geometry)
    also persist on release via saveFontSettings(). Text Size / Interface Scale keep their
    existing per-move save+apply (already live since 07-19, proven).
  - Mono chips: `Noto Sans Mono`, `Liberation Mono`, `Ubuntu Mono`, `Fira Mono` (now real),
    `JetBrains Mono`, `DejaVu Sans Mono`.
  - MEASURE specimen now renders settings.fontFamily/fontWeight/fontItalic (was hardcoded
    Cormorant Garamond).
  - Sections tab: per-row "falls back to QUILL" caption ×4 replaced by one caption; instant
    persist noted in it.
  - Iris Chroma: MY PALETTES authoring block removed (header, name field, Save Current, saved-card
    flow incl. delete ✕). Engine palette API untouched. The 90 curated presets byte-identical.
  - Header rewritten to the truth (hooks live; instant-apply model documented).
- **NCDESlider.qml** (root /usr/share/ncde one, NOT controls/): added `signal released()`,
  emitted on tap completion and DragHandler active→false.
- **Fira Mono** (Mozilla/Carrois, OFL) Regular/Medium/Bold from google/fonts GitHub:
  - LIVE NOW user-level: ~/.local/share/fonts/ + fc-cache (fc-match "Fira Mono" → FiraMono-Regular).
  - System-wide staged: /usr/share/fonts/ncde-firamono/ via step 7r (ISO-ready).

## Gates run (qmllint is NOT the gate)

qmllint clean on both files; PySide6 offscreen QQmlComponent instantiation with fully mocked
context objects (ncde/settings/theme/notifications/animPolicy), all 5 tabs force-built via
_activeTab, ZERO errors/warnings naming either file (notes/harness.py — reusable). First
harness run caught a real parse error (onReleased binding termination) that was fixed —
the gate earns its keep. **Not yet operator-verified visually — NOT "fixed" until it is.**

## Deploy + verify (operator)

    sudo bash /run/media/stephen/EFF2-E845/my-project/files/ncde-full-patch-20260711.sh
    # then relog (QML cache)

Visual checklist after relog — Settings → Filigree:
1. Fonts: mono row shows 6 chips incl. Fira Mono + JetBrains Mono; tapping Fira Mono actually
   changes to Fira Mono (slab-less, distinct from Noto). MEASURE box shows YOUR font.
2. No Apply buttons anywhere in Filigree. Change a font chip → survives relog with no button.
3. Drag Spacing → text spacing changes live; release; relog → still there.
4. Glass: pick a surface colour → applies instantly; drag Shine → live; release persists.
5. Widgets: change Clock accent → applies+persists instantly.
6. Sections: set a colour → instant; ↺ → instant fallback.
7. Iris Chroma: no "Name this palette" row, no delete ✕; 90 cards + toast on pick unchanged.

## Remaining (agreed plan, not yet built)

- **Phase 2**: active-palette indicator on the 90 cards; cards full-opacity idle (hover =
  border highlight, not dimming); "Reset to 100%" chip beside the two scale sliders;
  accessibility-multiplier notice; real inkSoft (fp.inkSoft === fp.ink today — captions don't
  read soft); terminal row re-read on visibility.
- **Phase 3**: dedupe the 6× copy-pasted widget Glow/Frame/Reset blocks (~400→~80 lines);
  merge the two near-identical color popups. Zero visible change; full 6-widget visual pass after.

---

# Filigree Phase 2 — 2026-07-20 (later) — STAGED in the same 7q dep payload, awaiting deploy

Phase 1 was operator-confirmed live (visual checklist passed) before Phase 2 was built.

## What changed (FiligreeTab.qml 1653 → 1701 lines; notes/apply-edits-p2.py, 10 anchored edits)

- **(a) Active-palette indicator on the 90 Iris cards.** Identity = `ncde.accentName` — the
  SAME identity Style Manager (`NCDEStyleManager.qml:103`) and main.qml's reapplyActivePreset
  use, and what active-theme.json's "accent" field stores. `irisCol.activeName` tracks it,
  refreshed by `Connections onThemeChanged` AND set instantly on card tap (no watcher latency).
  Active card: gilt border ×2 width + a 16px gilt circle with a ✓ (wine ink) top-right.
- **(b) Cards full-opacity idle.** `opacity: hovered ? 1.0 : 0.65` removed — cards are always
  1.0; hover is now a border highlight (gilt1 → gilt3). No dimming, no flash, nothing animated.
- **(c) "Reset to 100%" chips** beside Text Size and Interface Scale readouts. Sets the setting,
  saves+applies, AND resets the slider's value property directly (NCDESlider's internal drag
  assignment breaks the external binding — the chip must re-seat it). Chip dims to 0.45 opacity
  (static) when already at 100%.
- **(d) Accessibility-multiplier notice** under Interface Scale: visible only when
  `settings.accessibilityTextScale` ≠ 1.0 (guard style copied from SetTheme.qml:49), names the
  live % and points at Settings → Accessibility.
- **(e) Real inkSoft.** `fp.inkSoft` was `=== fp.ink`; now `Qt.rgba(foreground, 0.65)` — the
  SetTheme.qml:41 pattern. Every caption in the tab actually reads soft now.
- **(f) Terminal row staleness.** `termRow.refresh()` re-reads `ncde.terminalConfig()` and
  re-seats the tint slider value + font TextInput text (both bindings break on user interaction);
  fired from the Type tab's `onVisibleChanged`.

## Gates run (offscreen, real engine — not qmllint)

- `notes/harness.py` (PySide6 instantiation, all 5 tabs forced): PASSED. Mock gained
  `signal themeChanged()` + `property string accentName` (kept in sync in notes/).
- `notes/probe-p2.py` (functional): 90 cards built, EXACTLY one active + badge only there,
  all cards opacity 1.0, active border 2/inactive 1, indicator follows a themeChanged emit
  (P3→P7), both reset chips found with correct dim logic, notice hidden at 1.0 and correct
  text at 125%, termRow.refresh() present. ALL PASSED.

Staged: patch src tree + embedded archive regenerated (base64 round-trip extract diff-verified),
bash -n clean, USB + home ~/my-project copies both updated (identical, Jul 20 23:57).

## Deploy + verify (operator)

    sudo bash /run/media/stephen/EFF2-E845/my-project/files/ncde-full-patch-20260711.sh
    # then relog (QML cache)

Visual checklist — Settings → Filigree:
1. Iris Chroma: your current palette's card shows a gold ✓ circle + stronger border; every
   other card is full-brightness (nothing dimmed); hovering brightens a card's BORDER only.
2. Tap a different palette → the ✓ moves to it instantly (and the toast still fires).
3. Fonts tab: a "Reset to 100%" chip sits beside each of Text Size and Interface Scale; set
   Text Size to 150%, tap its chip → back to 100%, slider handle included, survives relog.
4. With Accessibility text scale at 100%: no notice line. Raise it in Settings →
   Accessibility → an italic note appears under Interface Scale naming the %.
5. Captions/hints throughout Filigree read softer than headings (real inkSoft).
6. Terminal: change glass tint, leave to another tab, come back → slider still shows the
   real saved value (no stale snap-back).

## Remaining after Phase 2 confirms

- **Phase 3** (approved): dedupe the 6× copy-pasted widget Glow/Frame/Reset blocks
  (~400→~80 lines); merge the two near-identical color popups. Zero visible change intended —
  full 6-widget visual pass afterward is mandatory.

---

# Filigree Phase 3 — 2026-07-21 — dedupe, STAGED in the same 7q dep payload, awaiting deploy

Phase 2 was deployed 2026-07-21 00:02 and operator-confirmed before Phase 3 was built.
Pure refactor: **zero visible change intended.** FiligreeTab.qml 1701 → 1310 lines
(notes/apply-edits-p3.py, anchored edits, every anchor exact-count-verified).

## What changed

- **(A) 12 unrolled Glow/Frame rows → one data-driven Repeater** (Widgets tab). One
  metadata row per widget (`fil.widgetMeta`) + `fil._widgDefault(key)` carry everything
  that differed: popup display names (La’Ombre’s popups stay titled "Ghost"), per-widget
  glow default (clock=gilt3, space=cer, weather=verd, stats=wine4, salon/laombre=#6a4a8b),
  Frame default (engine amber gilt3), captions ("engine default"/"amber default").
- **(B) 6 unrolled per-widget Reset buttons → one Repeater** over the same metadata.
  Same settings+engine reset calls, same accent/font fallbacks (salon keeps
  Cormorant Garamond; label text preserved incl. "Reset La’Ombre d’Opale").
- **(C) Section-colour popup merged into the unified colour popup.** The Sections popup
  was a copy that only added a Reset button; the unified popup now takes an optional
  4th resetCallback arg to openColorPopup() — non-null shows the Reset button (styling
  carried over verbatim, incl. its text-shadow layer). The Sections rows' duplicated
  inline hex→HSV wheel-seeding math is gone (openColorPopup already had it). Contrast
  readout still Font-popups-only. `_sectionTarget/_sectionLabel/_sectionPopupOpen/
  sectionWheel` retired, zero references remain.

**Known behavioural delta (only one, cosmetic):** opening a Section colour that is
currently UNSET used to leave the wheel wherever it last was (stateful accident); it now
seeds to engine amber like every other empty-colour popup. Deterministic, arguably a fix.

## Gates run (offscreen, real engine — not qmllint)

- `notes/harness.py` (PySide6 instantiation, all 5 tabs forced): PASSED.
- `notes/probe-p3.py` (functional, new): per selected widget exactly one visible
  Glow row / Frame row / correctly-labelled Reset button (all 6 widgets); swatch
  ×/↺/caption logic reacts to set+clear; per-widget default fallbacks byte-identical;
  merged popup shows Reset only when a reset callback is passed, hides it again on the
  next non-Sections popup; Sections reset path clears the setting AND calls
  saveSectionColors; set-colour path stores; Font-only contrast readout intact;
  exactly ONE "Set Colour" in the whole tree (old popup fully gone). ALL PASSED.
- `notes/probe-p2.py` re-run as regression: 90 cards / one active / themeChanged
  follows / chips / notice / termRow — ALL STILL PASS.

## Deploy + verify (operator)

    sudo bash /run/media/stephen/EFF2-E845/my-project/files/ncde-full-patch-20260711.sh
    # then relog (QML cache)

Visual checklist — Settings → Filigree → Widgets (full 6-widget pass is mandatory
since this touched all of them, even though nothing should look different):
1. For EACH of Clock / Space / Weather / Stats / Salon Nocturne / La’Ombre d’Opale:
   chip select shows its Accent + Glow + Frame + Text + Font rows and ONE reset button
   with the right name; Glow/Frame swatches open a popup titled e.g. "Clock — Glow"
   (La’Ombre’s says "Ghost — …"); picking a colour applies instantly; × clears back to
   the engine default caption.
2. Tap one Reset button → only that widget's style resets, instantly.
3. Sections tab: tap a colour swatch → the SAME popup style as everywhere else, now with
   Set Colour / Reset / Cancel; Set applies instantly; Reset clears to QUILL; row ↺ still
   works. Font popups still show the contrast readout; Sections/Glass/Widgets don't.
4. Glass tab + Type tab: spot-check one control each — unchanged behavior.

---

# Phase 4 (2026-07-21) — full-controls audit → commercial-grade refinements

Operator: "go through the whole of Filigree's controls and audit them so that they
are all refined and commercial grade." Audited every control on all 5 tabs plus the
two reusable components the tab drives (NCDESlider — clean, untouched; and
SettingsColorWheel — two fixes). Anchored edits: `notes/apply-edits-p4.py`
(FiligreeTab.qml 1359 → 1410 lines; SettingsColorWheel.qml 181 → 182).
SettingsColorWheel.qml is NEW to the payload (own dep line, step 7v).

## Fixes (by finding)

1. **Internal keys leaked to the user.** "TOPPANEL — GLASS" heading, "TopPanel —
   Surface"/"BottomPanel — …" popups, and worst "Laombre — Accent/Text/Surface/
   Outline/Glow" while the P3 Glow/Frame popups correctly said "Ghost". New
   `_dispName()` map humanises every heading + popup title; laombre → "Ghost"
   everywhere (operator precedent). Widgets GLASS block also gains the
   "<NAME> — GLASS" heading the Glass tab block already had.
2. **Colour popup opened on the wrong colour.** openColorPopup() seeded hue+sat
   only: brightness stuck wherever the strip was last dragged (dark colours
   opened bright), and greys seeded sat 0.75 (0.75 was the no-`d` default). Now
   full HSV decomposition incl. `colorWheel.value = mx`; probe round-trips
   #804020 / #808080 / #404040 / #000000 exactly.
3. **Widget preview card lied twice.** A fully-transparent two-stop gradient
   overrode `color:` (gradient beats color on Rectangle) so the tint never
   painted; and the sample text bound `o.fill` even when unset ("" = invalid
   colour → rendered default black). Now: gradient removed; fill falls back to
   `ncde.gilt4` — the widgets' real default ink (ClockPanel.qml:165).
4. **Reset Typography desynced sliders.** Settings reset to 0 / 1.0× but the
   Spacing/Leading knobs (which hold their own value once dragged) stayed put.
   Sliders got ids; reset snaps them home (3 ↔ 0.0px, 10 ↔ 1.0×).
5. **Shadow controls looked dead.** The TEXT RENDERING sample never rendered the
   shadow. It now carries the shell's own MultiEffect pattern (blur /32, same as
   ClockPanel), so Shadow/Blur/Offset move a real shadow live; the medium+small
   sample lines also get the outline style the large line already had.
6. **Dependent rows always active.** Blur/Offset X/Offset Y now dim (0.45) +
   disable while Shadow is off; "Outline width" → "Thickness" (old label
   overflowed its 78px column) and dims while Outline is off. Static dimming
   only — nothing flashes or animates (lampPulse law).
7. **Empty input accepted.** Custom-font and Terminal-font fields now trim and
   reject empty/whitespace (revert to current value, no save).
8. **Sections popup seeded amber.** The one documented P3 delta — unset section
   colours now seed the popup from `fPalette[4]` (QUILL), i.e. exactly the
   colour the swatch shows. Delta retired.
9. **Solei-Lune broken segmented look.** End segments had all four corners
   rounded (QML Rectangle can't round per-corner). Converted to three spaced
   chips — the same chip language as every other selector row in the tab.
10. **Popup scrim dead zone.** Tap outside the dialog now cancels (identical to
    Cancel); the scrim still swallows every tap, nothing reaches the tab.
11. **"Glow Int."** → "Intensity" (Glass + Widgets blocks).
12. **SettingsColorWheel** (shared; also used by Wallpapers tab): shader-status
    console.log removed (journal noise on every settings open); saturation clamp
    0.15 → 0 so the wheel centre reaches true neutrals — pure white/grey text
    colours were previously unpickable.

## Gates run (offscreen, real engine — not qmllint)

- `notes/harness.py` (all 5 tabs; now overlays SettingsColorWheel.qml too): PASSED.
- `notes/probe-p2.py` + `notes/probe-p3.py` regression (also overlay the wheel): PASSED.
- NEW `notes/probe-p4.py`: _dispName map (9 keys); HSV seed round-trip incl.
  grey/dark-grey/black + brightness-no-longer-sticky; humanised headings visible
  per surface/widget (incl. GHOST — GLASS); preview text gilt4 fallback + honours
  explicit fill; Thickness/Blur/Offset dim+disable and re-enable with their
  flags; old "Outline width" label gone; Solei-Lune chips build; scrim→dialog
  coordinate mapping (outside/inside); spacing/leading slider ids resolve; zero
  invalid-colour/binding-loop/TypeError noise. ALL PASSED.

## Deploy + verify (operator)

    sudo bash /run/media/stephen/NCDE-BACKUP/my-project/files/ncde-full-patch-20260711.sh
    # then relog (QML cache)

Visual checklist = item 3d in the script's POST-RELOGIN block: humanised
headings/popups (TOP PANEL — GLASS, Ghost — Accent), dark-colour popup reopens
dark, wheel centre gives white/grey, tinted preview card with gold default text,
real shadow moves on the sample, dependent rows dim, Reset Typography snaps
knobs home, Solei-Lune chips, tap-outside-closes-popup.
Only the operator's confirmation closes Phase 4. Rollback: `*.prebak-*` siblings
(script sibling: ncde-full-patch-20260711.sh.prebak-20260721-p4).
