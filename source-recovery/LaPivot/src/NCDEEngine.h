// NCDEEngine — Colour/theme engine ONLY (no system data).
// Rebuilt from oracle: decomp/NCDEEngine.c (202 functions). Colour state, presets, wallpaper
// sampling, filigree palettes, theme save/load and the GTK bridge follow the oracle exactly
// (2026-10-01 rebuild: the earlier rebuild had invented its own colour model and did not match
// the live LaPivot — gilt, glow, wallpaper palettes, terminal config path all differed).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2, docs/gtk.md, docs/gtk-designer-answers.md.
// DEFECTS FIXED vs oracle (behaviour-preserving):
//  1. System forwarders removed from this colour engine (Lelan owns system data).
//  2. GTK/Chromium bridge file writes run serially off the GUI thread; same files, same bytes.
//  3. Presets compiled from NCDEEngine_presets.inc (verified == the live Iris-patched tables).
//  4. setWidgetStyleMap/resetWidgetStyle exist (FiligreeTab calls ncde.resetWidgetStyle unguarded;
//     on the oracle that threw and aborted the reset handler). In-memory only: Settings persists.
//  5. No hardcoded user paths (QDir::homePath()).
//  6. (2026-10-01) applyPreset on the palette that is already active (same colours) is a no-op: the
//     oracle recomputed, re-emitted and rewrote ~10 GTK files on every repeat click.
//  7. Ink floor (gtk.md §8.1, non-negotiable): recompute() keeps ink >= 7:1 over panelBg AND surface on
//     every path (custom base, woven applyPalette, wallpaper mix, loadTheme); the oracle only had it
//     in the curated presets. Ink moves first; grounds move only when no ink can reach 7:1.
//  8. saveTheme writes atomically (QSaveFile, parent dir made): the engine's own watcher reloads that
//     file, so the oracle's truncate-then-write could feed it a half-written theme.
//  9. previewWallpaper returns `valid` and `text` too: WallpapersTab's hover strip reads exactly those
//     and stayed 0 px high on the oracle (it never once showed).
// 10. ~/.gtkrc-2.0 carries the live palette (gtk.md: "live values in every slot"); the oracle wrote fixed
//     teal-grey grounds, so GTK2 apps never followed Iris. Rewritten whenever the palette changes.

#ifndef NCDEENGINE_H
#define NCDEENGINE_H

#include <QObject>
#include <QColor>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QTimer>
#include <QHash>
#include <QVector>
#include <QFileSystemWatcher>
#include <QByteArray>

class NCDEEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor accent READ accent NOTIFY changed)
    Q_PROPERTY(QColor accentMuted READ accentMuted NOTIFY changed)
    Q_PROPERTY(QColor background READ background NOTIFY changed)
    Q_PROPERTY(QColor surface READ surface NOTIFY changed)
    Q_PROPERTY(QColor surfaceAlt READ surfaceAlt NOTIFY changed)
    Q_PROPERTY(QColor surfaceHi READ surfaceHi NOTIFY changed)
    Q_PROPERTY(QColor panelBg READ panelBg NOTIFY changed)
    Q_PROPERTY(QColor panelText READ panelText NOTIFY changed)
    Q_PROPERTY(QColor popupBg READ popupBg NOTIFY changed)
    Q_PROPERTY(QColor border READ border NOTIFY changed)
    Q_PROPERTY(QColor glow READ glow NOTIFY changed)
    Q_PROPERTY(QColor ink READ ink NOTIFY changed)
    Q_PROPERTY(QColor inkSoft READ inkSoft NOTIFY changed)
    Q_PROPERTY(QColor verd READ verd NOTIFY changed)
    Q_PROPERTY(QColor cer READ cer NOTIFY changed)
    Q_PROPERTY(QColor rose READ rose NOTIFY changed)
    Q_PROPERTY(QColor amber READ amber NOTIFY changed)
    Q_PROPERTY(QColor clockColor READ clockColor NOTIFY changed)
    Q_PROPERTY(QColor lamp READ lamp NOTIFY changed)
    Q_PROPERTY(QColor gilt0 READ gilt0 NOTIFY changed)
    Q_PROPERTY(QColor gilt1 READ gilt1 NOTIFY changed)
    Q_PROPERTY(QColor gilt2 READ gilt2 NOTIFY changed)
    Q_PROPERTY(QColor gilt3 READ gilt3 NOTIFY changed)
    Q_PROPERTY(QColor gilt4 READ gilt4 NOTIFY changed)
    Q_PROPERTY(QColor gilt5 READ gilt5 NOTIFY changed)
    Q_PROPERTY(QColor wine1 READ wine1 NOTIFY changed)
    Q_PROPERTY(QColor wine2 READ wine2 NOTIFY changed)
    Q_PROPERTY(QColor wine3 READ wine3 NOTIFY changed)
    Q_PROPERTY(QColor wine4 READ wine4 NOTIFY changed)
    Q_PROPERTY(QColor widgetC0 READ widgetC0 NOTIFY changed)
    Q_PROPERTY(QColor widgetC1 READ widgetC1 NOTIFY changed)
    Q_PROPERTY(QColor widgetC2 READ widgetC2 NOTIFY changed)
    Q_PROPERTY(QColor widgetC3 READ widgetC3 NOTIFY changed)
    Q_PROPERTY(QColor widgetC4 READ widgetC4 NOTIFY changed)
    Q_PROPERTY(QColor widgetC5 READ widgetC5 NOTIFY changed)
    Q_PROPERTY(QColor foreground READ foreground NOTIFY changed)
    Q_PROPERTY(QColor topShadow READ topShadow NOTIFY changed)
    Q_PROPERTY(QColor bottomShadow READ bottomShadow NOTIFY changed)
    Q_PROPERTY(QColor selectColor READ selectColor NOTIFY changed)
    Q_PROPERTY(QColor activeBg READ activeBg NOTIFY changed)
    Q_PROPERTY(QColor activeFg READ activeFg NOTIFY changed)
    Q_PROPERTY(QColor activeTs READ activeTs NOTIFY changed)
    Q_PROPERTY(QColor activeBs READ activeBs NOTIFY changed)
    Q_PROPERTY(QColor inactiveBg READ inactiveBg NOTIFY changed)
    Q_PROPERTY(QColor inactiveFg READ inactiveFg NOTIFY changed)
    Q_PROPERTY(QColor inactiveTs READ inactiveTs NOTIFY changed)
    Q_PROPERTY(QColor inactiveBs READ inactiveBs NOTIFY changed)
    Q_PROPERTY(bool darkMode READ darkMode WRITE setDarkMode NOTIFY changed)
    Q_PROPERTY(QString activeFiligreePaletteName READ activeFiligreePaletteName NOTIFY filigreePalettesChanged)
    Q_PROPERTY(QVariantMap activeFiligreePalette READ activeFiligreePalette NOTIFY filigreePalettesChanged)
    Q_PROPERTY(QVariantMap filigreePalettes READ filigreePalettes NOTIFY filigreePalettesChanged)
    Q_PROPERTY(bool presetActive READ presetActive NOTIFY changed)
    Q_PROPERTY(bool usingCustomBase READ usingCustomBase NOTIFY changed)
    Q_PROPERTY(int fontSize_sm READ fontSize_sm NOTIFY changed)
    Q_PROPERTY(int fontSize_md READ fontSize_md NOTIFY changed)
    Q_PROPERTY(int fontSize_lg READ fontSize_lg NOTIFY changed)
    Q_PROPERTY(int letterSpacing READ letterSpacing NOTIFY changed)
    Q_PROPERTY(double lineHeight READ lineHeight NOTIFY changed)
    Q_PROPERTY(QString themeName READ themeName NOTIFY changed)
    Q_PROPERTY(QString accentName READ accentName WRITE setAccentName NOTIFY changed)
    Q_PROPERTY(QString darkModeLock READ darkModeLock WRITE setDarkModeLock NOTIFY changed)
    Q_PROPERTY(QString overrideAccent READ overrideAccent NOTIFY changed)
    Q_PROPERTY(QString overrideAccentMuted READ overrideAccentMuted NOTIFY changed)
    Q_PROPERTY(QString overrideBorder READ overrideBorder NOTIFY changed)
    Q_PROPERTY(QString overrideGlow READ overrideGlow NOTIFY changed)
    Q_PROPERTY(QString bodyFont READ bodyFont NOTIFY changed)
    Q_PROPERTY(QString titleFont READ titleFont NOTIFY changed)
    Q_PROPERTY(QString monoFont READ monoFont NOTIFY changed)
    Q_PROPERTY(QString displayFont READ displayFont NOTIFY changed)
    Q_PROPERTY(QString fellFont READ fellFont NOTIFY changed)
    Q_PROPERTY(QString garFont READ garFont NOTIFY changed)
    Q_PROPERTY(QString version READ version CONSTANT)
public:
    explicit NCDEEngine(QObject *parent = nullptr);
    ~NCDEEngine() override;

    // Colour getters (NOTIFY changed)
    QColor accent() const;
    QColor accentMuted() const;
    QColor background() const;
    QColor surface() const;
    QColor surfaceAlt() const;
    QColor surfaceHi() const;
    QColor panelBg() const;
    QColor panelText() const;
    QColor popupBg() const;
    QColor border() const;
    QColor glow() const;
    QColor ink() const;
    QColor inkSoft() const;
    QColor verd() const;
    QColor cer() const;
    QColor rose() const;
    QColor amber() const;
    QColor clockColor() const;
    QColor lamp() const;
    QColor gilt0() const;
    QColor gilt1() const;
    QColor gilt2() const;
    QColor gilt3() const;
    QColor gilt4() const;
    QColor gilt5() const;
    QColor wine1() const;
    QColor wine2() const;
    QColor wine3() const;
    QColor wine4() const;
    QColor widgetC0() const;
    QColor widgetC1() const;
    QColor widgetC2() const;
    QColor widgetC3() const;
    QColor widgetC4() const;
    QColor widgetC5() const;
    QColor foreground() const;
    QColor topShadow() const;
    QColor bottomShadow() const;
    QColor selectColor() const;
    QColor activeBg() const;
    QColor activeFg() const;
    QColor activeTs() const;
    QColor activeBs() const;
    QColor inactiveBg() const;
    QColor inactiveFg() const;
    QColor inactiveTs() const;
    QColor inactiveBs() const;

    // State getters (NOTIFY changed)
    bool darkMode() const;
    QString activeFiligreePaletteName() const;
    QVariantMap activeFiligreePalette() const;
    QVariantMap filigreePalettes() const;
    bool presetActive() const;
    bool usingCustomBase() const;
    int fontSize_sm() const;
    int fontSize_md() const;
    int fontSize_lg() const;
    int letterSpacing() const;
    double lineHeight() const;
    QString themeName() const;
    QString accentName() const;
    QString darkModeLock() const;
    QString overrideAccent() const;
    QString overrideAccentMuted() const;
    QString overrideBorder() const;
    QString overrideGlow() const;
    QString bodyFont() const;
    QString titleFont() const;
    QString monoFont() const;
    QString displayFont() const;
    QString fellFont() const;
    QString garFont() const;
    QString version() const;
    double uiScale() const;
    double fontSizeScale() const;

    // Theme/preset operations
    Q_INVOKABLE QVariantList presets();
    Q_INVOKABLE void applyPreset(const QString &id);
    Q_INVOKABLE QVariantMap currentBasePalette();
    Q_INVOKABLE bool sampleWallpaper(const QString &path);
    Q_INVOKABLE QVariantMap previewWallpaper(const QString &path);
    Q_INVOKABLE void previewWallpaperAsync(const QString &path);
    Q_INVOKABLE void setSurfaceGlass(const QString &key, const QColor &tint, double shine, double glow, const QColor &border, const QColor &glowColor);
    Q_INVOKABLE QVariantMap surfaceGlass(const QString &key);
    Q_INVOKABLE void setWidgetStyleMap(const QString &key, const QVariantMap &map);
    Q_INVOKABLE void setWidgetStyle(const QString &key, const QColor &accent, const QColor &fill, const QString &font);
    Q_INVOKABLE QVariantMap widgetStyle(const QString &key);
    Q_INVOKABLE void resetWidgetStyle(const QString &key);
    Q_INVOKABLE void setOverrideAccent(const QString &hex);
    Q_INVOKABLE void setOverrideAccentMuted(const QString &hex);
    Q_INVOKABLE void setOverrideBorder(const QString &hex);
    Q_INVOKABLE void setOverrideGlow(const QString &hex);
    Q_INVOKABLE void setBodyFont(const QString &f);
    Q_INVOKABLE void setTitleFont(const QString &f);
    Q_INVOKABLE void setMonoFont(const QString &f);
    Q_INVOKABLE void setDisplayFont(const QString &f);
    Q_INVOKABLE void setFellFont(const QString &f);
    Q_INVOKABLE void setGarFont(const QString &f);
    Q_INVOKABLE void setUiScale(double s);
    Q_INVOKABLE void setFontSizeScale(double s);
    Q_INVOKABLE void setLetterSpacing(double v);
    Q_INVOKABLE void setLineHeight(double v);
    Q_INVOKABLE void recomputeFontSizes();
    Q_INVOKABLE QVariantMap toJson();
    Q_INVOKABLE bool saveTheme(const QString &path);
    Q_INVOKABLE bool loadTheme(const QString &path);
    Q_INVOKABLE void setTerminalFont(const QString &font);
    Q_INVOKABLE void setTerminalGlassTint(double tint);
    Q_INVOKABLE QVariantMap terminalConfig();
    Q_INVOKABLE bool saveFiligreepalette(const QString &name, const QVariantMap &colors);
    Q_INVOKABLE bool deleteFiligreepalette(const QString &name);
    Q_INVOKABLE bool setActiveFiligreepalette(const QString &name);


    // Slots (public)
    void applyPalette(const QVariantMap &p);
    void setDarkMode(bool d);
    void setAccentName(const QString &n);
    void setDarkModeLock(const QString &lock);
    void setBaseColor(const QColor &base, const QColor &accent, const QColor &panelText);
    void clearCustomBase();

signals:
    void changed();
    void themeChanged();
    void darkModeChanged();
    void previewReady(const QVariantMap &palette);
    void filigreePalettesChanged();

private:
    struct Lab { double L = 0, a = 0, b = 0; };
    struct Sample { double L = 0, a = 0, b = 0, w = 0; };

    // Oracle member layout (offsets in decomp/NCDEEngine.c)
    bool m_darkMode = true;            // 0x28
    bool m_presetActive = false;       // 0x29
    bool m_usingCustomBase = false;    // 0x2a
    QColor m_accent{"#c98a3a"};        // 0x2c
    QColor m_accentMuted{"#8a5a20"};   // 0x3c
    QColor m_background{"#0c0907"};    // 0x4c
    QColor m_surface{"#171009"};       // 0x5c  (= activeBg)
    QColor m_surfaceAlt{"#1e1409"};    // 0x6c
    QColor m_surfaceHi{"#e9c97c"};     // 0x7c
    QColor m_panelBg{"#0c0907"};       // 0x8c  (= inactiveBg)
    QColor m_popupBg{"#0a0806"};       // 0x9c
    QColor m_border{"#8a5a20"};        // 0xac
    QColor m_glow{"#c98a3a"};          // 0xbc
    QColor m_ink{"#f4e9d2"};           // 0xcc  (= panelText, clockColor)
    QColor m_inkSoft{"#b8a07a"};       // 0xdc
    QColor m_verd{"#4f9183"};          // 0xec
    QColor m_cer{"#5fb4c6"};           // 0xfc
    QColor m_rose{"#c64b63"};          // 0x10c
    QColor m_amber{"#e9a23a"};         // 0x11c (= lamp)
    QColor m_gilt[6] = {QColor("#5a3a14"), QColor("#8a5a20"), QColor("#b07a30"),
                        QColor("#c98a3a"), QColor("#e9c97c"), QColor("#f6e3b0")};
    QColor m_wine[4] = {QColor("#2a0612"), QColor("#4a0e22"), QColor("#6e1832"), QColor("#8b1e3f")};
    QColor m_widgetC[6] = {QColor("#171009"), QColor("#1e1409"), QColor("#4f9183"),
                           QColor("#5fb4c6"), QColor("#c98a3a"), QColor("#c64b63")};
    QColor m_foreground;               // 0x22c (= activeFg)
    QColor m_topShadow;                // 0x23c (= activeTs)
    QColor m_bottomShadow;             // 0x24c (= activeBs)
    QColor m_selectColor;              // 0x25c
    QColor m_inactiveFg;               // 0x26c
    QColor m_inactiveTs;               // 0x27c
    QColor m_inactiveBs;               // 0x28c
    int m_fontSizeSm = 11;             // 0x29c
    int m_fontSizeMd = 14;             // 0x2a0
    int m_fontSizeLg = 20;             // 0x2a4
    int m_letterSpacing = 0;           // 0x2a8
    double m_lineHeight = 1.0;         // 0x2b0
    QString m_themeName = QStringLiteral("NCDE Poseidon");  // 0x2b8
    QString m_accentName = QStringLiteral("Gilt");          // 0x2d0
    QString m_darkModeLock;                                 // 0x2e8
    QColor m_baseAccent{"#c98a3a"};    // 0x300
    QColor m_baseBorder{"#8a5a20"};    // 0x310
    QColor m_baseGlow{"#c98a3a"};      // 0x320
    bool m_wallMix = false;            // 0x330
    QColor m_wallAccent, m_wallBorder, m_wallGlow, m_wallSurface,
           m_wallBackground, m_wallPopup, m_wallInk, m_wallInkSoft;  // 0x334..0x3a4
    bool m_wallDark = false;           // 0x3b4
    QString m_overrideAccent;          // 0x3b8
    QString m_overrideAccentMuted;     // 0x3d0
    QString m_overrideBorder;          // 0x3e8
    QString m_overrideGlow;            // 0x400
    QString m_bodyFont = QStringLiteral("Cormorant Garamond");
    QString m_titleFont = QStringLiteral("Cinzel");
    QString m_monoFont = QStringLiteral("JetBrains Mono");
    QString m_displayFont = QStringLiteral("IM Fell DW Pica");
    QString m_fellFont = QStringLiteral("IM Fell English");
    QString m_garFont = QStringLiteral("EB Garamond");
    double m_uiScale = 1.0;            // 0x4a8
    double m_fontSizeScale = 1.0;      // 0x4b0
    QHash<QString, QVariantMap> m_surfaceGlass;   // 0x4b8
    QHash<QString, QVariantMap> m_widgetStyles;   // 0x4c0
    QFileSystemWatcher *m_themeWatcher = nullptr; // 0x20
    QVariantMap m_activeFiligreePalette;          // 0x4d8
    QString m_activeFiligreePaletteName;          // 0x4e0
    QTimer m_recomputeTimer;                      // 0x10
    QString m_gtk2Signature;                      // fix 10: last palette written to ~/.gtkrc-2.0

    void recompute();
    void scheduleRecompute();
    void deriveAccentSurface();
    void enforceInkFloor();
    void calcColors(const QColor &c, QColor &fg, QColor &ts, QColor &bs, QColor &sel) const;
    void loadPersistedFiligree();
    void loadActiveFiligreepalette();
    void applyGtkTheme(bool dark);
    void applyGtkAccent();
    void seedGtkUserConfig();
    void writeActiveFiligreepaletteName() const;
    QVariantMap filigreePalettesRaw() const;
    static QString filigreePalettesPath();
    static bool writeFiligreePalettes(const QVariantMap &palettes);
    static void setTerminalConfigField(const QString &key, const QVariant &value);

    static double brightness(const QColor &c);
    static double clamp01(double v);
    static QColor liteScale(const QColor &c, int percent);
    static QColor darkScale(const QColor &c, int percent);
    static double labF(double t);
    static void rgbToLab(int r, int g, int b, Lab &out);
    static double labDist2(const Lab &x, const Lab &y);
    static QColor labToColor(const Lab &lab);
    static QColor mixLab(const QColor &a, const QColor &b, double t);
};

#endif // NCDEENGINE_H