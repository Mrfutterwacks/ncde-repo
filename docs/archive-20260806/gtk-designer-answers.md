# NCDE GTK Bridge — Designer Q&A + the Engine Code (companion to gtk.md)

Answers to the designer's six questions, plus the actual engine code asked for — copied
verbatim from the working production source (`NCDEEngine.h`, the session-80 restored state
that ships). **Every decision about this system is the operator's. The engine code below is
READ-ONLY reference: it ships as-is, and the theme files conform to it — never the other way
around.**

---

## Q1 — Where does the GTK writer live?

It already exists in the running binary. **Do not build a generator — the engine IS the generator.**
There is no separate `GtkBridge.cpp` and no `NCDEEngine.cpp`; the engine is a single header-only
class, `NCDEEngine.h` (class `NCDEEngine`).

**[Corrected 2026-07-17]:** the `~/ncde-staging/LaPivot/compass7/lelan/` path this used to live at no
longer exists — that dev machine is gone. `NCDEEngine` today is only recoverable by Ghidra-decompiling
the live binary, in `~/ncde-wm-rebuild/`, where per `docs/lapivot-rebuild.md` it's still raw/rough
decompiled output, not clean rebuilt source. The code below is the historical reference for what
shipped, not a currently-verified live file.

The three methods, exactly the names gtk.md references, recovered from the original binary's
decompile and proven working (16/16 harness): `seedGtkUserConfig()`, `applyGtkTheme(bool)`,
`applyGtkAccent()`. Full bodies in §CODE below. Your deliverables are the **static theme
assets only** — the css/gtkrc files per gtk.md; the plumbing is done and off-limits.

## Q2 — Are the six tokens exposed by gtk.md's names?

Yes. The exact getters on NCDEEngine today, verbatim (NCDEEngine.h:178-190):

```cpp
QColor accent() const      { return m_accent; }
QColor surface() const     { return m_surface; }
QColor panelBg() const     { return m_panelBg; }
QColor border() const      { return m_border; }
QColor ink() const         { return m_ink; }
QColor inkSoft() const     { return m_inkSoft; }
```

plus the mode flag: `Q_PROPERTY(bool darkMode READ darkMode WRITE setDarkMode NOTIFY changed)`.
No aliasing needed. (`panelText` and `accentMuted` exist on the engine but are not part of the
GTK mapping.) You never call these yourself — the engine writes the files. What it writes
LIVE on every apply: the accent (`_accent.css` + the three gtkrc accent slots) and the
dark/light mode; the ground defines in the palette files are the shipped NCDE defaults
(gtk.md §1 canonical bridge palette). Author every rule against named colors only.

## Q3 — shade() left to GTK?

Confirmed. The engine computes no shades — GTK3's own `shade(@theme_bg_color, 1.10)` etc.
does buttons/headerbars/statusbar in the css. GTK2: also confirmed, no shaded slots exist —
the `style "ncde"` block in gtk.md §6.1 is the complete slot set; GTK2 buttons ride
`bg[NORMAL]` / `bg[PRELIGHT]`.

## Q4 — Adwaita resource path?

**Superseded by operator order: the complete NCDEgtk theme ships — not Adwaita.** The
Adwaita-import mechanism you saw referenced was agent reconstruction after the original theme
files were lost; it is not canon. Design the full widget styling yourself — every widget,
complete, no Adwaita import anywhere in any file. For the record, the target versions
(verified on the machine): **GTK 3.24.52, GTK 4.22.4, GTK 2.24.33**.

## Q5 — Chromium sync in scope?

Out of scope for you. `/usr/local/bin/ncde-chromium-sync.sh` already exists on the system
(verified) and the engine already calls it with `dark|light` on every apply. Its own header,
for context only:

```sh
#!/usr/bin/env bash
# ncde-chromium-sync.sh — point Chromium's livery at NCDE's current mode.
# Called by the engine whenever ncde.darkMode flips (and once at login).
#
# It does three things:
#   1. selects the matching NCDE Chromium theme (day / night chrome),
#   2. sets the freedesktop portal colour-scheme so web pages' prefers-color-scheme
#      follows NCDE (the gentle, per-site-respecting route),
#   3. optionally enables --force-dark-mode for web CONTENT (the hammer) when the
#      user has asked for it (NCDE setting: chromiumForceDark).
#
# Usage:  ncde-chromium-sync.sh [dark|light]
#         (no arg → reads ~/.config/ncde/active-theme.json)
```

## Q6 — GTK4 live-reload expectation?

Confirmed, and it is the system's design: GTK4/libadwaita follow dark/light live via the
`color-scheme` gsetting; the user-css defines apply per app launch; no expectation that a
running GTK4 app recolors its grounds mid-session. GTK4 stays **defines-only** in the user
css — full widget rules there corrupt libadwaita apps.

## Corrections to your recorded plan

These items are already done inside the engine — do **not** duplicate them: the token
generator, the gtk.css entry rewriter, the `~/.gtkrc-2.0` writer, and "wire into the 5 fire
sites." Your real deliverables: the complete NCDEgtk GTK3 theme (`_rules.css` as full widget
styling, named colors only), the shipped GTK2 `gtkrc` default, the GTK4 defines set, and the
HTML preview — good idea, one hard rule: no flashing and no abrupt full-screen white when
switching palettes in the preview.

---

# CODE — the engine writers, verbatim (READ-ONLY reference)

The five call sites (all recovered from the original binary — this is when your files get
(re)written): `setDarkMode`, `setDarkModeLock`, `applyPreset` (the Iris Chroma click),
`sampleWallpaper`, `loadTheme` (the once-at-login leg; every native app's `main()` calls
`loadTheme` at startup).

## seedGtkUserConfig() — first-run seeding, never clobbers user files

```cpp
// Seed the per-user GTK config from the shipped defaults (never clobbers user files).
//  GTK3 palette/rules seeds: /usr/share/themes/NCDE/gtk-3.0 → ~/.themes/NCDE/gtk-3.0
//  GTK4 palette + gtk.css:   /usr/share/themes/NCDE/gtk-4.0 → ~/.config/gtk-4.0
//  (QFile::copy silently no-ops when a source file is absent — recovered behavior.)
void seedGtkUserConfig()
{
    const QString sys3 = QStringLiteral("/usr/share/themes/NCDE/gtk-3.0");
    const QString sys4 = QStringLiteral("/usr/share/themes/NCDE/gtk-4.0");
    const QString usr3 = QDir::homePath() + QStringLiteral("/.themes/NCDE/gtk-3.0");
    const QString usr4 = QDir::homePath() + QStringLiteral("/.config/gtk-4.0");
    QDir().mkpath(usr3);
    QDir().mkpath(usr4);
    for (const QString &n : { QStringLiteral("_palette-dark.css"),
                              QStringLiteral("_palette-light.css"),
                              QStringLiteral("_rules.css") }) {
        const QString dst = usr3 + QLatin1Char('/') + n;
        if (!QFile::exists(dst)) QFile::copy(sys3 + QLatin1Char('/') + n, dst);
    }
    for (const QString &n : { QStringLiteral("_palette-dark.css"),
                              QStringLiteral("_palette-light.css") }) {
        const QString dst = usr4 + QLatin1Char('/') + n;
        if (!QFile::exists(dst)) QFile::copy(sys4 + QLatin1Char('/') + n, dst);
    }
    const QString gtk4css = usr4 + QStringLiteral("/gtk.css");
    if (!QFile::exists(gtk4css)) QFile::copy(sys4 + QStringLiteral("/gtk.css"), gtk4css);
}
```

**What this means for you:** the filenames are a fixed contract. Your GTK3 deliverables ship
to `/usr/share/themes/NCDE/gtk-3.0/` as exactly `_palette-dark.css`, `_palette-light.css`,
`_rules.css` (+ the `gtk.css` entry the engine rewrites); GTK4 palette files + `gtk.css` ship
to `/usr/share/themes/NCDE/gtk-4.0/`.

## applyGtkTheme(bool dark) — the full sync, fired at all five call sites

```cpp
// The full sync: GTK3 theme css → GTK4 user css + settings.ini → gsettings (color-scheme
// + gtk-theme, which GTK3 apps and the portal read live) → Chromium → GTK2 ~/.gtkrc-2.0.
void applyGtkTheme(bool dark)
{
    seedGtkUserConfig();
    const QString palette = dark ? QStringLiteral("_palette-dark.css")
                                 : QStringLiteral("_palette-light.css");
    const QString other   = dark ? QStringLiteral("_palette-light.css")
                                 : QStringLiteral("_palette-dark.css");

    // GTK3 — rewrite the NCDE theme's gtk.css to import the active palette
    {
        QFile f(QDir::homePath() + QStringLiteral("/.themes/NCDE/gtk-3.0/gtk.css"));
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&f);
            out << "/* NCDE — managed by NCDEEngine. Do not edit. */\n"
                << "@import url(\"" << palette << "\");\n"
                << "@import url(\"_accent.css\");\n"
                << "@import url(\"_rules.css\");\n";
        }
    }
    // GTK4 — swap the palette import inside the user gtk.css in place
    {
        QFile f(QDir::homePath() + QStringLiteral("/.config/gtk-4.0/gtk.css"));
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString content = QString::fromUtf8(f.readAll());
            f.close();
            content.replace(QStringLiteral("@import url(\"") + other + QStringLiteral("\")"),
                            QStringLiteral("@import url(\"") + palette + QStringLiteral("\")"));
            if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&f);
                out << content;
            }
        }
    }
    // GTK4 settings.ini — gtk-theme-name=NCDE + prefer-dark (recovered replace-or-append)
    {
        const QString path = QDir::homePath() + QStringLiteral("/.config/gtk-4.0/settings.ini");
        QFile f(path);
        QString content;
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            content = QString::fromUtf8(f.readAll());
            f.close();
        }
        auto replaceOrAppend = [&content](const QString &key, const QString &val) {
            const QRegularExpression re(key + QStringLiteral("=.*"));
            if (content.contains(re)) content.replace(re, key + QLatin1Char('=') + val);
            else                      content += key + QLatin1Char('=') + val + QLatin1Char('\n');
        };
        replaceOrAppend(QStringLiteral("gtk-theme-name"), QStringLiteral("NCDE"));
        replaceOrAppend(QStringLiteral("gtk-application-prefer-dark-theme"),
                        dark ? QStringLiteral("true") : QStringLiteral("false"));
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&f);
            out << content;
        }
    }
    // gsettings — dark/light for libadwaita/portal readers, and activate the NCDE GTK theme
    QProcess::startDetached(QStringLiteral("gsettings"),
        { QStringLiteral("set"), QStringLiteral("org.gnome.desktop.interface"),
          QStringLiteral("color-scheme"),
          dark ? QStringLiteral("prefer-dark") : QStringLiteral("default") });
    QProcess::startDetached(QStringLiteral("gsettings"),
        { QStringLiteral("set"), QStringLiteral("org.gnome.desktop.interface"),
          QStringLiteral("gtk-theme"), QStringLiteral("NCDE") });
    // Chromium — the sync script flips its theme-night/theme-day symlink + portal scheme
    QProcess::startDetached(QStringLiteral("/usr/local/bin/ncde-chromium-sync.sh"),
        { dark ? QStringLiteral("dark") : QStringLiteral("light") });

    // GTK2 — regenerate ~/.gtkrc-2.0 with the live accent (recovered writer, byte-matched
    // against the live file the original binary wrote; bridge palettes are the binary's own)
    const QString bg   = dark ? QStringLiteral("#263033") : QStringLiteral("#E7E1D8");
    const QString fg   = dark ? QStringLiteral("#E6F1F2") : QStringLiteral("#2B2621");
    const QString base = dark ? QStringLiteral("#1E2527") : QStringLiteral("#F4F1EC");
    const QString dis  = dark ? QStringLiteral("#5A6670") : QStringLiteral("#9A9088");
    const QString acc  = accent().name();
    QFile f2(QDir::homePath() + QStringLiteral("/.gtkrc-2.0"));
    if (f2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&f2);
        out << "# NCDEEngine — managed automatically. Do not edit.\n"
            << "gtk-theme-name=\"NCDE\"\n"
            << "gtk-font-name=\"IM Fell English 11\"\n\n"
            << "style \"ncde\" {\n"
            << "  bg[NORMAL]      = \"" << bg   << "\"\n"
            << "  fg[NORMAL]      = \"" << fg   << "\"\n"
            << "  base[NORMAL]    = \"" << base << "\"\n"
            << "  text[NORMAL]    = \"" << fg   << "\"\n"
            << "  bg[ACTIVE]      = \"" << bg   << "\"\n"
            << "  fg[ACTIVE]      = \"" << dis  << "\"\n"
            << "  bg[PRELIGHT]    = \"" << acc  << "\"\n"
            << "  fg[PRELIGHT]    = \"#FFFFFF\"\n"
            << "  bg[SELECTED]    = \"" << acc  << "\"\n"
            << "  fg[SELECTED]    = \"#FFFFFF\"\n"
            << "  base[SELECTED]  = \"" << acc  << "\"\n"
            << "  text[SELECTED]  = \"#FFFFFF\"\n"
            << "  bg[INSENSITIVE] = \"" << bg   << "\"\n"
            << "  fg[INSENSITIVE] = \"" << dis  << "\"\n"
            << "}\n"
            << "widget_class \"*\" style \"ncde\"\n"
            << "class \"*\" style \"ncde\"\n";
    }
}
```

## applyGtkAccent() — the live accent pair

```cpp
// The live accent — written to both the GTK3 theme and the GTK4 user config, regenerated
// from the engine's CURRENT color state (never a static file). Recovered @001cdda0.
void applyGtkAccent()
{
    seedGtkUserConfig();
    const QString hex = accent().name();
    const QStringList paths = {
        QDir::homePath() + QStringLiteral("/.themes/NCDE/gtk-3.0/_accent.css"),
        QDir::homePath() + QStringLiteral("/.config/gtk-4.0/_accent.css") };
    for (const QString &p : paths) {
        QFile f(p);
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&f);
            out << "/* NCDEEngine — wallpaper accent. Do not edit. */\n"
                << "@define-color ncde_accent " << hex << ";\n"
                << "@define-color theme_selected_bg_color @ncde_accent;\n";
        }
    }
}
```

---

## The behavior your theme conforms to (read the code above; this is just the summary)

On every Iris Chroma click / mode flip / wallpaper sample / login, the engine: rewrites the
GTK3 `gtk.css` import chain for the active mode → rewrites both `_accent.css` files with the
live accent → swaps the GTK4 palette import in place → sets `settings.ini` prefer-dark +
gsettings `color-scheme`/`gtk-theme` → runs the Chromium sync → regenerates `~/.gtkrc-2.0`
whole (NCDE ground palette + live accent in the three accent slots). Selection, hover, links,
checks, and mode follow every click, live. Your css must therefore take ALL color through the
named colors (`@theme_bg_color`, `@ncde_accent`, …, per gtk.md §2) — never a literal hex in a
rule — so the files keep working no matter what the engine writes into the defines.
