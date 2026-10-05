# NCDE GTK Bridge — Full Schematics (GTK2 / GTK3 / GTK4)

> **🔴 2026-07-07 (session 81): the DESIGNER'S theme kit LANDED and is canon.** The operator's
> designer delivered the complete NCDEgtk theme (`gtk-theme-designer-kit.zip`, archived in
> `~/my-project/files/`); it replaced the agent-reconstructed files in every tree location and
> is PROVEN in real GTK 3.24.52 + 4.22.4 (see punchlist §2.2). **There is NO Adwaita import
> anywhere — NCDE ships its own complete widget styling in `_rules.css` (334 lines, every
> widget)**, per operator order (gtk-designer-answers.md Q4). This doc's Adwaita references
> below have been corrected; if any residue remains, the shipped files on the **live system** at
> `/usr/share/themes/NCDE/` win (corrected 2026-07-17 — `~/ncde-staging/LaPivot/` no longer exists;
> the live system is the only copy now, see `CLAUDE.md` banner).

**Goal: GTK apps look ABSOLUTELY NATIVE on NCDE.** They are not "themed" — they wear NCDE's
default GTK face, and that face is repainted live by the engine every time the user picks an
Iris Chroma palette. This document is the complete contract: every file, every color slot,
every line of code, and the exact mapping from NCDE's global color tokens to GTK. It is
self-contained — you do not need access to the system to work from it.

---

## 0. The one rule that governs everything

**These are NOT themes per se. They are the default GTK look of NCDE.**

Operator (system author), verbatim, from the recovered engine source:

> "These aren't themes per say… NCDE does not use themes.. it uses Filigree to change the
> shell globally.. but we had to make the gtk stuff so it would work — these are defaults."

Consequences:

1. Every per-user GTK file is **generated output** of `NCDEEngine` (the C++ theme engine).
   Nothing is hand-maintained after shipping. Never design anything that requires a human to
   edit a generated file.
2. There is **one color pipeline** for the whole OS. The GTK files are its tail end, nothing
   more:

```
Filigree  ──►  Iris Chroma  ──►  NCDEKit  ──►  NCDEEngine  ──►  GTK2 / GTK3 / GTK4 / Chromium
(palette       (90 named         (shared QML    (C++ recompute:   (generated files — this doc)
 picker UI)     presets)          token          derives ALL
                                  resolver)      global tokens)
```

3. **Parchment-class behavior is mandatory.** NCDE's material language has three classes:
   Glass (panels/dock, tintable), Parchment (native app bodies, ink-adaptive dark/light), and
   Metal (static, terminal + window frames only). GTK apps are **Parchment**. That means: the
   user clicks an Iris Chroma preset → the **entire GTK palette changes** — backgrounds,
   surfaces, ink, borders, selection — exactly like every native NCDE app. Not just the accent.
   One click, everything changes, GTK apps included.

---

## 1. The global color tokens (the source of truth)

Every Iris Chroma preset is a row of six hand-tuned "pigments." This is the complete input:

| Token       | Meaning                                                        |
|-------------|----------------------------------------------------------------|
| `accent`    | The palette's signature color — selection, hover, links, checks |
| `border`    | Border / outline color                                          |
| `panelBg`   | The main ground — window and panel background                   |
| `surface`   | Content wells — text views, lists, entries (sits on `panelBg`)  |
| `ink`       | Text on `panelBg`/`surface` (contrast ≥ 7:1, always)            |
| `inkSoft`   | Secondary/disabled text                                         |
| `dark` flag | Whether this palette is a dark ground (drives GTK dark mode)    |

Example preset rows (real data — `kPresets.inc`, 90 total):

```c
// Fields: id, name, dark, accent, border, panelBg, surface, ink, inkSoft
{ "mucha",      "Mucha",      false, "#af7e22", "#6a4400", "#fbe6d9", "#f2dacb", "#2a221c", "#735f52" },
{ "whimsigoth", "Whimsigoth", true,  "#a988c4", "#694d81", "#1d2140", "#24284a", "#ebeaf2", "#aaaaba" },
{ "nocturne",   "Nocturne",   true,  "#d7b45b", "#917623", "#000d1b", "#021624", "#e6ecf2", "#9fadbb" },
```

The engine (`NCDEEngine::applyPreset` → `recompute()`) takes those six pigments, optionally
mixes in 25% of the sampled wallpaper (in CIELAB), and derives the full token set that the
whole OS reads (`accent, accentMuted, background, surface, surfaceAlt, surfaceHi, panelBg,
panelText, popupBg, border, glow, ink, inkSoft`, the gilt/wine ramps, window-frame colors,
etc.). QML apps read them live through NCDEKit; GTK apps get them through the generated files
below.

**Canonical fallback bridge palette** (recovered from the original binary — used when no
preset/token is available; these are the shipped static defaults, NOT the live values):

| Slot            | Dark      | Light     |
|-----------------|-----------|-----------|
| bg (`panelBg`)  | `#263033` | `#E7E1D8` |
| fg (`ink`)      | `#E6F1F2` | `#2B2621` |
| base (`surface`)| `#1E2527` | `#F4F1EC` |
| disabled (`inkSoft`) | `#5A6670` | `#9A9088` |
| selection fg    | `#FFFFFF` | `#FFFFFF` |
| default accent  | `#6774bd` | `#6774bd` |

---

## 2. Token → GTK mapping (the master table)

This is the contract every file below implements. **Never hardcode a hex in a rule — always
route through these names**, because every one of them can change on any Iris Chroma click.

| NCDE token | GTK3/GTK4 named colors (`@define-color`) | GTK2 gtkrc slots |
|---|---|---|
| `panelBg` | `theme_bg_color`, `insensitive_bg_color`, `theme_unfocused_bg_color` | `bg[NORMAL]`, `bg[ACTIVE]`, `bg[INSENSITIVE]` |
| `surface` | `theme_base_color`, `content_view_bg`, `text_view_bg`, `insensitive_base_color`, `theme_unfocused_base_color` | `base[NORMAL]` |
| `ink` | `theme_fg_color`, `theme_text_color`, `theme_unfocused_text_color` | `fg[NORMAL]`, `text[NORMAL]` |
| `inkSoft` | `insensitive_fg_color`, `theme_unfocused_fg_color` | `fg[ACTIVE]`, `fg[INSENSITIVE]` |
| `border` | `borders`, `unfocused_borders` | (GTK2 has no border slot — omitted) |
| `accent` | `ncde_accent`, `theme_selected_bg_color` | `bg[PRELIGHT]`, `bg[SELECTED]`, `base[SELECTED]` |
| (fixed) | `theme_selected_fg_color` = `#FFFFFF`, `theme_unfocused_selected_fg_color` = `#FFFFFF` | `fg[PRELIGHT]`, `fg[SELECTED]`, `text[SELECTED]` = `"#FFFFFF"` |
| `dark` flag | selects which `_palette-*.css` the gtk.css chain imports (GTK3) + `gtk-application-prefer-dark-theme` + gsettings `color-scheme` (GTK4) | (baked into the generated colors) |

Derived shades used by the rules layer (computed by GTK's own `shade()`, no extra tokens):
buttons `shade(@theme_bg_color, 1.10)` (hover `1.22`), headerbars/toolbars
`shade(@theme_bg_color, 0.92)`, statusbar `0.95`.

---

## 3. File map — where everything lives

**System defaults (shipped read-only, in the OS image):**

```
/usr/share/themes/NCDE/gtk-2.0/gtkrc              ← GTK2: resolves gtk-theme-name="NCDE"
/usr/share/themes/NCDE/gtk-3.0/gtk.css            ← GTK3 theme entry (import chain)
/usr/share/themes/NCDE/gtk-3.0/_palette-dark.css
/usr/share/themes/NCDE/gtk-3.0/_palette-light.css
/usr/share/themes/NCDE/gtk-3.0/_accent.css
/usr/share/themes/NCDE/gtk-3.0/_rules.css         ← the widget re-grounding (shared by both modes)
/usr/share/themes/NCDE/gtk-4.0/gtk.css            ← GTK4 seed for the USER css
/usr/share/themes/NCDE/gtk-4.0/_palette-dark.css
/usr/share/themes/NCDE/gtk-4.0/_palette-light.css
/usr/share/themes/NCDE/gtk-4.0/_accent.css
```

**Per-user, engine-managed (seeded on first run by `seedGtkUserConfig()`, then live-rewritten
by `applyGtkTheme()` / `applyGtkAccent()`):**

```
~/.themes/NCDE/gtk-3.0/gtk.css                 ← REWRITTEN on every theme change
~/.themes/NCDE/gtk-3.0/_palette-{dark,light}.css
~/.themes/NCDE/gtk-3.0/_accent.css             ← REWRITTEN (live accent)
~/.themes/NCDE/gtk-3.0/_rules.css
~/.config/gtk-4.0/gtk.css                      ← palette import swapped in place
~/.config/gtk-4.0/_palette-{dark,light}.css
~/.config/gtk-4.0/_accent.css                  ← REWRITTEN (live accent)
~/.config/gtk-4.0/settings.ini                 ← gtk-theme-name=NCDE + prefer-dark
~/.gtkrc-2.0                                   ← FULLY REGENERATED on every theme change
```

Seeding never clobbers: a file is copied from `/usr/share/themes/NCDE/` only if the per-user
copy does not exist yet. The same seeds also ship in `/etc/skel/.themes/NCDE/gtk-3.0/` so new
accounts start correct.

**The engine fires the bridge at exactly five sites** (all recovered from the original
binary): `setDarkMode`, `setDarkModeLock`, `applyPreset` (the Iris Chroma click),
`sampleWallpaper`, and `loadTheme` (the once-at-login leg — every native app's `main()` calls
`loadTheme` at startup).

---

## 4. GTK3 — the full theme, file by file

GTK3 is the richest target and the reference implementation. **NCDE ships its OWN complete
theme — no Adwaita import anywhere** (operator order, 2026-07-07; the earlier Adwaita-import
mechanism was agent reconstruction from before the designer's files were recovered, and is not
canon). The split stays: per-mode palettes carry the `@define-color` grounds, `_accent.css`
carries the live accent, and one shared `_rules.css` (the designer's complete 334-line widget
styling — every widget, named colors only) grounds every surface for both modes.

### 4.1 `gtk.css` — the entry point (engine-rewritten; shown here with the dark palette active)

```css
/* NCDE — managed by NCDEEngine. Do not edit. */
@import url("_palette-dark.css");
@import url("_accent.css");
@import url("_rules.css");
```

The engine rewrites just this file to flip modes: dark → `_palette-dark.css`, light →
`_palette-light.css`. Import order is load-bearing: palette (grounds + Adwaita), then accent
(live), then rules (re-grounding, which references both).

### 4.2 `_palette-dark.css` — dark grounds

```css
/* NO Adwaita import — NCDE ships its own complete widget styling in _rules.css. */

@define-color theme_bg_color #263033;              /* ← panelBg  */
@define-color theme_fg_color #E6F1F2;              /* ← ink      */
@define-color theme_base_color #1E2527;            /* ← surface  */
@define-color theme_text_color #E6F1F2;            /* ← ink      */
@define-color content_view_bg #1E2527;             /* ← surface  */
@define-color text_view_bg #1E2527;                /* ← surface  */
@define-color insensitive_bg_color #263033;        /* ← panelBg  */
@define-color insensitive_fg_color #5A6670;        /* ← inkSoft  */
@define-color insensitive_base_color #1E2527;      /* ← surface  */
@define-color theme_unfocused_bg_color #263033;    /* ← panelBg  */
@define-color theme_unfocused_fg_color #5A6670;    /* ← inkSoft  */
@define-color theme_unfocused_base_color #1E2527;  /* ← surface  */
@define-color theme_unfocused_text_color #E6F1F2;  /* ← ink      */
@define-color borders #5A6670;                     /* ← border   */
@define-color unfocused_borders #5A6670;           /* ← border   */
@define-color theme_selected_fg_color #FFFFFF;
@define-color theme_unfocused_selected_fg_color #FFFFFF;
/* theme_selected_bg_color + ncde_accent come from _accent.css (engine-generated, live). */
```

The hexes shown are the shipped fallback defaults; the `← token` comments are the real
contract. `_palette-light.css` is identical in structure with the light column of the token
values. The designer's shipped palettes also define legibility names the rules layer uses so
the rules stay hex-free: `tooltip_bg_color`/`tooltip_fg_color` and
`warning_color`/`error_color`/`success_color` (per-mode values).

### 4.3 `_accent.css` — the live accent (engine-regenerated, never static)

```css
/* NCDEEngine — wallpaper accent. Do not edit. */
@define-color ncde_accent #6774bd;
@define-color theme_selected_bg_color @ncde_accent;
```

Two lines. The engine rewrites this file with the **current** engine accent — which is the
Iris Chroma preset's accent, wallpaper-mixed — on every change (`applyGtkAccent()`).

### 4.4 `_rules.css` — the complete widget styling (shared by both modes)

**The canonical file is the designer's 334-line deliverable, live at
`/usr/share/themes/NCDE/gtk-3.0/_rules.css` — that file is the spec.** (Corrected 2026-07-17: the
old `~/ncde-staging/LaPivot/` staging path is gone; the live system is the only copy now.)
It styles EVERY widget from scratch (no Adwaita underneath): surfaces, entries, buttons,
header/tool/status bars, notebooks, menus/popovers, treeviews + headers, scrollbars, scales,
progress, switches/checks/radios, tooltips, infobars, sidebars, windowcontrols. Only named
colors and `shade()`/`alpha()` of named colors — its only literal hexes are the two fixed
selection-class whites the contract itself fixes (§8.4). The excerpt below shows the shape of
the earlier conservative reconstruction for orientation; where they differ, the shipped
designer file wins.

```css
/* NCDE GTK3 shared rules — mode-independent widget grounding, complete, no Adwaita. */

/* main surfaces */
window, dialog, .background {
  background-color: @theme_bg_color;
  color: @theme_fg_color;
}
/* content views */
textview, textview text, treeview.view, list, list row, iconview {
  background-color: @theme_base_color;
  color: @theme_text_color;
}
entry {
  background-color: @theme_base_color;
  color: @theme_text_color;
  border-color: @borders;
}
/* raised controls */
button {
  background-image: none;
  background-color: shade(@theme_bg_color, 1.10);
  color: @theme_fg_color;
  border-color: @borders;
}
button:hover { background-color: shade(@theme_bg_color, 1.22); }
button:active, button:checked { background-color: @ncde_accent; color: @theme_selected_fg_color; }
/* bars, menus, popups */
headerbar, .titlebar, toolbar, .primary-toolbar, notebook > header {
  background-image: none;
  background-color: shade(@theme_bg_color, 0.92);
  color: @theme_fg_color;
}
menubar, menu, .menu, .context-menu, popover, popover.background {
  background-color: @theme_bg_color;
  color: @theme_fg_color;
}
menuitem:hover, menu > menuitem:hover {
  background-color: @ncde_accent;
  color: @theme_selected_fg_color;
}
statusbar, .statusbar { background-color: shade(@theme_bg_color, 0.95); }
/* selection + accent */
selection, *:selected, *:selected:focus {
  background-color: @theme_selected_bg_color;
  color: @theme_selected_fg_color;
}
*:link { color: @ncde_accent; }
*:disabled { color: @insensitive_fg_color; }
scale highlight, progressbar > trough > progress, checkbutton check:checked, radiobutton radio:checked {
  background-color: @ncde_accent;
  border-color: @ncde_accent;
}
switch:checked { background-color: @ncde_accent; }
```

Design rules for extending `_rules.css`:
- **Only named colors and `shade()`/`alpha()` of named colors.** One literal hex here breaks
  Parchment-class behavior for that widget forever (the two fixed selection whites are the
  sole contract-sanctioned exception).
- Since NCDE ships its own complete theme, an unstyled state falls to the GTK defaults — so
  every widget/state a user can reach must be grounded here; no state may fall to unstyled
  white (accessibility floor §8.3).
- Keep `background-image: none` where a default gradient could sit over your
  `background-color` (buttons, headerbars).

### 4.5 How GTK3 apps are activated and updated

- Activation: the engine runs `gsettings set org.gnome.desktop.interface gtk-theme "NCDE"`
  and writes `gtk-theme-name=NCDE`; GTK3 resolves the theme from `~/.themes/NCDE/gtk-3.0/`
  (user copy wins over `/usr/share/themes/`).
- Mode + palette updates: the engine rewrites `gtk.css` (palette import) and `_accent.css`,
  and sets `gsettings set org.gnome.desktop.interface color-scheme prefer-dark|default`.

---

## 5. GTK4 — defines only, deliberately

GTK4 must be handled differently and this is the single most important thing to know:

> **The GTK4 per-user css (`~/.config/gtk-4.0/gtk.css`) is stacked on top of EVERY GTK4
> app's own stylesheet — including libadwaita apps. Importing a full theme or widget rules
> there corrupts libadwaita apps. So the GTK4 side ships NAMED-COLOR DEFINES ONLY.**

Dark/light for GTK4 apps rides on `settings.ini` `prefer-dark` plus the gsettings
`color-scheme` the engine sets; the defines re-ground apps that consume the compat named
colors.

### 5.1 `~/.config/gtk-4.0/gtk.css` (seeded, then palette import swapped in place)

```css
/* NCDE — managed by NCDEEngine. Do not edit. */
@import url("_palette-dark.css");
@import url("_accent.css");
```

The engine flips modes by replacing `_palette-dark.css` ↔ `_palette-light.css` inside this
file in place (string swap, nothing else touched).

### 5.2 `~/.config/gtk-4.0/_palette-dark.css` (complete — note: NO Adwaita import, NO rules)

```css
@define-color theme_bg_color #263033;         /* ← panelBg */
@define-color theme_fg_color #E6F1F2;         /* ← ink     */
@define-color theme_base_color #1E2527;       /* ← surface */
@define-color theme_text_color #E6F1F2;       /* ← ink     */
@define-color insensitive_bg_color #263033;   /* ← panelBg */
@define-color insensitive_fg_color #5A6670;   /* ← inkSoft */
@define-color borders #5A6670;                /* ← border  */
@define-color theme_selected_fg_color #FFFFFF;
/* theme_selected_bg_color + ncde_accent come from _accent.css (engine-generated, live). */
```

`_palette-light.css`: same names, light token values. `_accent.css`: byte-identical format to
the GTK3 one (§4.3) — the engine writes both copies in the same pass.

### 5.3 `~/.config/gtk-4.0/settings.ini` (engine-managed, replace-or-append per key)

```ini
gtk-theme-name=NCDE
gtk-application-prefer-dark-theme=true
```

`true`/`false` follows the active palette's `dark` flag. The engine also runs, on every apply:

```sh
gsettings set org.gnome.desktop.interface color-scheme prefer-dark   # or: default
gsettings set org.gnome.desktop.interface gtk-theme NCDE
```

`color-scheme` is what libadwaita and the xdg-desktop-portal read — it is how sandboxed and
libadwaita apps follow NCDE's mode even though they ignore theme css.

---

## 6. GTK2 — one style block, fully generated

Two files. The shipped default exists only so `gtk-theme-name="NCDE"` resolves for GTK2 apps;
the per-user `~/.gtkrc-2.0` is **fully regenerated by the engine on every theme change** and
overrides it. GTK2 has no named-color indirection, so the live token values are written
directly into the slots.

### 6.1 `~/.gtkrc-2.0` — the engine's generated output (complete; dark defaults + accent shown)

```
# NCDEEngine — managed automatically. Do not edit.
gtk-theme-name="NCDE"
gtk-font-name="IM Fell English 11"

style "ncde" {
  bg[NORMAL]      = "#263033"    # ← panelBg
  fg[NORMAL]      = "#E6F1F2"    # ← ink
  base[NORMAL]    = "#1E2527"    # ← surface
  text[NORMAL]    = "#E6F1F2"    # ← ink
  bg[ACTIVE]      = "#263033"    # ← panelBg
  fg[ACTIVE]      = "#5A6670"    # ← inkSoft
  bg[PRELIGHT]    = "#6774bd"    # ← accent (LIVE — current engine accent)
  fg[PRELIGHT]    = "#FFFFFF"
  bg[SELECTED]    = "#6774bd"    # ← accent (LIVE)
  fg[SELECTED]    = "#FFFFFF"
  base[SELECTED]  = "#6774bd"    # ← accent (LIVE)
  text[SELECTED]  = "#FFFFFF"
  bg[INSENSITIVE] = "#263033"    # ← panelBg
  fg[INSENSITIVE] = "#5A6670"    # ← inkSoft
}
widget_class "*" style "ncde"
class "*" style "ncde"
```

(The generated bytes are verified against the original binary's own live output — a 16-test
harness byte-matches them.)

### 6.2 `/usr/share/themes/NCDE/gtk-2.0/gtkrc` — the shipped static default

Same `style "ncde"` block with the canonical dark bridge palette and the default accent
`#6774bd` baked in, plus the same two `widget_class`/`class "*"` bindings. It exists so the
theme name resolves before the engine's first per-user write; after first login the per-user
file always wins.

GTK2 note: `IM Fell English` is NCDE's Parchment body face; keep the `gtk-font-name` line
exactly — it is part of looking native, not decoration.

---

## 7. Parchment-class liveness — the "one click changes everything" contract

This section is the spec the whole document exists for.

**Requirement (operator, definitive):** GTK3, GTK4, AND GTK2 must change colors like all
Parchment-class apps do. You click an Iris Chroma palette — everything changes, GTK apps
included. Full grounds and ink, not accent-only.

What that means mechanically: on every engine apply (any of the five call sites in §3), the
per-user palette-bearing files are regenerated **from the live engine tokens** — the same
tokens NCDEKit hands to every native QML app — using the §2 mapping. Nothing in the GTK
layer may pin a color the engine can't move:

- **GTK3:** the `@define-color` block of the active `~/.themes/NCDE/gtk-3.0/_palette-*.css`
  carries the live `panelBg / surface / ink / inkSoft / border`; `_accent.css` carries the
  live accent. `_rules.css` never changes — it only references names, which is why it can be
  static while everything recolors.
- **GTK4:** same for `~/.config/gtk-4.0/_palette-*.css` + `_accent.css` (defines only, §5).
- **GTK2:** `~/.gtkrc-2.0` is rewritten whole with live values in every slot (it already is —
  the generated file in §6.1 IS the live writer's output).

### Worked example — the user clicks "Whimsigoth" (dark preset)

Preset pigments: accent `#a988c4`, border `#694d81`, panelBg `#1d2140`, surface `#24284a`,
ink `#ebeaf2`, inkSoft `#aaaaba` (wallpaper-mixed 25% in CIELAB if a wallpaper base was
sampled; pure pigment shown here). The engine emits:

`~/.themes/NCDE/gtk-3.0/_palette-dark.css` (defines block):

```css
@define-color theme_bg_color #1d2140;
@define-color theme_fg_color #ebeaf2;
@define-color theme_base_color #24284a;
@define-color theme_text_color #ebeaf2;
@define-color content_view_bg #24284a;
@define-color text_view_bg #24284a;
@define-color insensitive_bg_color #1d2140;
@define-color insensitive_fg_color #aaaaba;
@define-color insensitive_base_color #24284a;
@define-color theme_unfocused_bg_color #1d2140;
@define-color theme_unfocused_fg_color #aaaaba;
@define-color theme_unfocused_base_color #24284a;
@define-color theme_unfocused_text_color #ebeaf2;
@define-color borders #694d81;
@define-color unfocused_borders #694d81;
@define-color theme_selected_fg_color #FFFFFF;
@define-color theme_unfocused_selected_fg_color #FFFFFF;
```

`_accent.css` (both GTK3 and GTK4 copies):

```css
/* NCDEEngine — wallpaper accent. Do not edit. */
@define-color ncde_accent #a988c4;
@define-color theme_selected_bg_color @ncde_accent;
```

`~/.gtkrc-2.0` color slots: `bg=#1d2140, fg/text=#ebeaf2, base=#24284a,
inkSoft slots=#aaaaba, accent slots=#a988c4, selection fg=#FFFFFF`.

Plus: `gtk.css` files point at `_palette-dark.css`, `settings.ini` gets
`gtk-application-prefer-dark-theme=true`, gsettings gets `color-scheme prefer-dark`, and
`ncde-chromium-sync.sh dark` flips Chromium's livery and the portal color-scheme in the same
pass.

### Update propagation (what "live" means per toolkit)

| Toolkit | Channel | Effect |
|---|---|---|
| GTK3 | theme css rewritten + gsettings/XSETTINGS `gtk-theme`/`color-scheme` | running apps restyle |
| GTK4 / libadwaita | `settings.ini` + gsettings `color-scheme` + user css | mode follows live; defines apply per-app-load |
| GTK2 | `~/.gtkrc-2.0` rewritten | apps pick it up at launch (GTK2 has no reliable live-reload path) |
| Chromium | `ncde-chromium-sync.sh dark\|light` | theme-day/night livery + portal `prefers-color-scheme` |

---

## 8. Accessibility floor (non-negotiable, applies to every palette)

Nothing in NCDE's visual system is cosmetic — every color decision is accessibility
engineering. The GTK face inherits the same floor the 90 Iris Chroma palettes are proven
against:

1. **Ink contrast ≥ 7:1** (`ink` over both `panelBg` and `surface`) — WCAG AAA. The shipped
   presets are CIELAB-verified to this; anything you author must hold the same line.
2. **Dark palettes get light ink globally, automatically** — the mode comes from the
   palette's `dark` flag (in QML, NCDEKit even derives it from the actual `panelBg`
   luminance). Never a separate manual toggle, never a mismatched ink.
3. **No flashes, no flicker, no bright opaque white surprise surfaces.** If a GTK state has
   no defined color, it must fall to a palette ground — never to unstyled white.
4. **Selection text is always `#FFFFFF` over the accent** — accents are chosen dark/saturated
   enough to carry it.
5. Fonts and sizes are user-scaled system-wide (Filigree's font-scale sliders); don't fight
   them with hardcoded pixel sizes in css.

---

## 9. Hard don'ts

- **Don't hand-edit generated files** (`~/.themes/NCDE/gtk-3.0/gtk.css`, `_accent.css`,
  `~/.config/gtk-4.0/gtk.css`, `settings.ini`, `~/.gtkrc-2.0`). The engine overwrites them
  on the next apply. Design changes go into the shipped seeds (`_rules.css`, the palette
  structure) or into the engine's writers.
- **Don't fork a parallel theming system.** No second theme name, no per-app css, no
  "NCDE-Dark"/"NCDE-Light" theme pair — mode is a palette import inside the ONE `NCDE` theme.
- **Don't rename or split the files.** `gtk.css`, `_palette-dark.css`, `_palette-light.css`,
  `_accent.css`, `_rules.css`, `gtkrc` — the engine writes and imports these exact names.
- **Don't put widget rules in the GTK4 layer.** Defines only (§5). Full rules there corrupt
  libadwaita apps.
- **Don't add an Adwaita import anywhere** (operator order, 2026-07-07). NCDE ships its own
  complete theme; `_rules.css` carries all widget styling itself.
- **Don't hardcode hex values in `_rules.css`** — named colors and `shade()` only.
- **No user-visible "Arch"/"Linux"/toolkit jargon anywhere** a user could see (NCDE hides its
  base like macOS hides BSD).

---

## Appendix — quick reference card

```
PIPELINE   Filigree → Iris Chroma (90 presets) → NCDEKit → NCDEEngine → GTK2/3/4 + Chromium
TOKENS     accent · border · panelBg · surface · ink · inkSoft · dark
GTK3       ~/.themes/NCDE/gtk-3.0/{gtk.css → _palette-*.css + _accent.css + _rules.css}
           palettes: @define-color grounds (NO Adwaita); rules: complete widget styling
GTK4       ~/.config/gtk-4.0/{gtk.css, _palette-*.css, _accent.css, settings.ini} — DEFINES ONLY
GTK2       ~/.gtkrc-2.0 fully regenerated: one style "ncde" block, live values in every slot
LIVE       one Iris Chroma click ⇒ full palette regenerated everywhere (Parchment-class), plus
           gsettings color-scheme/gtk-theme + chromium sync
FLOOR      ink ≥ 7:1 · dark⇒light-ink automatic · selection fg #FFFFFF · no white flashes
```
