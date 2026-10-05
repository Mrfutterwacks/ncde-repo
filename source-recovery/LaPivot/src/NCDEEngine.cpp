// Rebuilt from oracle: decomp/NCDEEngine.c (202 functions), function by function.
// Spec: NCDE-ARCHITECTURE-DIGEST.md §2, gtk.md, gtk-designer-answers.md, Filigree Phase 1.
// 2026-10-01: colour state, presets, wallpaper sampling, filigree palettes, theme save/load and the
// GTK bridge re-done to the oracle (the previous rebuild had its own colour model: gilt was a Lab
// shade of the accent instead of HSV(accent hue, sat, V-table); glow alpha 150 instead of 0x66;
// the wallpaper path averaged the image instead of k-means; GTK palette CSS was generated; the
// terminal config went to the wrong file; active-theme.json was auto-loaded at startup although no
// QML ever calls loadTheme). Behaviour-preserving fixes kept: see NCDEEngine.h.

#include "NCDEEngine.h"

#include "ColorMath.h"

#include <QColor>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QHash>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QProcess>
#include <QRegularExpression>
#include <QRunnable>
#include <QSaveFile>
#include <QTextStream>
#include <QThreadPool>
#include <QTimer>
#include <QUrl>

#include <algorithm>
#include <cmath>

namespace
{
struct PresetData
{
    const char *id;
    const char *name;
    bool dark;
    const char *accent;
    const char *border;
    const char *panelBg;
    const char *surface;
    const char *ink;
    const char *inkSoft;
};

constexpr PresetData kPresets[] = {
#include "NCDEEngine_presets.inc"
};

// Oracle deriveAccentSurface()::V (rodata 001a41e0): HSV value for gilt0..gilt5.
constexpr float kGiltV[6] = {0.22f, 0.35f, 0.54f, 0.69f, 0.91f, 0.96f};

QString localPath(const QString &pathOrUrl)
{
    const QUrl url(pathOrUrl);
    return url.isLocalFile() ? url.toLocalFile() : pathOrUrl;
}

QString configPath(const QString &name)
{
    return QDir::homePath() + QStringLiteral("/.config/ncde/") + name;
}

QVariantMap readJsonMap(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return {};
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    return doc.isObject() ? doc.object().toVariantMap() : QVariantMap();
}

// Fix 2: GTK/Chromium bridge writes run serially off the GUI thread (same files, same bytes).
QThreadPool &bridgePool()
{
    static QThreadPool pool;
    static const bool configured = [] {
        pool.setMaxThreadCount(1);
        pool.setExpiryTimeout(-1);
        return true;
    }();
    Q_UNUSED(configured);
    return pool;
}

void writeText(const QString &path, const QString &text)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << text;
    }
}

// oracle seedGtkUserConfig (0016dbcc)
void seedGtkFiles(const QString &home)
{
    const QString src3 = QStringLiteral("/usr/share/themes/NCDE/gtk-3.0");
    const QString src4 = QStringLiteral("/usr/share/themes/NCDE/gtk-4.0");
    const QString dst3 = home + QStringLiteral("/.themes/NCDE/gtk-3.0");
    const QString dst4 = home + QStringLiteral("/.config/gtk-4.0");
    QDir().mkpath(dst3);
    QDir().mkpath(dst4);
    for (const QString &n : {QStringLiteral("_palette-dark.css"), QStringLiteral("_palette-light.css"),
                             QStringLiteral("_rules.css")}) {
        const QString dst = dst3 + QLatin1Char('/') + n;
        if (!QFile::exists(dst))
            QFile::copy(src3 + QLatin1Char('/') + n, dst);
    }
    for (const QString &n : {QStringLiteral("_palette-dark.css"), QStringLiteral("_palette-light.css")}) {
        const QString dst = dst4 + QLatin1Char('/') + n;
        if (!QFile::exists(dst))
            QFile::copy(src4 + QLatin1Char('/') + n, dst);
    }
    const QString gtk4 = dst4 + QStringLiteral("/gtk.css");
    if (!QFile::exists(gtk4))
        QFile::copy(src4 + QStringLiteral("/gtk.css"), gtk4);
}

// fix 10: ~/.gtkrc-2.0 from the live palette. p = {dark, panelBg, surface, ink, inkSoft, accent}.
// Same one-style layout the oracle wrote (gtk.md §6), with the palette in every slot.
void writeGtk2(const QString &home, const QStringList &p)
{
    const QString &bg = p.at(1), &base = p.at(2), &fg = p.at(3), &dis = p.at(4), &accent = p.at(5);
    writeText(home + QStringLiteral("/.gtkrc-2.0"),
              QStringLiteral("# NCDEEngine — managed automatically. Do not edit.\n")
              + QStringLiteral("gtk-theme-name=\"NCDE\"\n")
              + QStringLiteral("gtk-font-name=\"IM Fell English 11\"\n\n")
              + QStringLiteral("style \"ncde\" {\n")
              + QStringLiteral("  bg[NORMAL]      = \"") + bg + QStringLiteral("\"\n")
              + QStringLiteral("  fg[NORMAL]      = \"") + fg + QStringLiteral("\"\n")
              + QStringLiteral("  base[NORMAL]    = \"") + base + QStringLiteral("\"\n")
              + QStringLiteral("  text[NORMAL]    = \"") + fg + QStringLiteral("\"\n")
              + QStringLiteral("  bg[ACTIVE]      = \"") + bg + QStringLiteral("\"\n")
              + QStringLiteral("  fg[ACTIVE]      = \"") + dis + QStringLiteral("\"\n")
              + QStringLiteral("  bg[PRELIGHT]    = \"") + accent + QStringLiteral("\"\n")
              + QStringLiteral("  fg[PRELIGHT]    = \"#FFFFFF\"\n")
              + QStringLiteral("  bg[SELECTED]    = \"") + accent + QStringLiteral("\"\n")
              + QStringLiteral("  fg[SELECTED]    = \"#FFFFFF\"\n")
              + QStringLiteral("  base[SELECTED]  = \"") + accent + QStringLiteral("\"\n")
              + QStringLiteral("  text[SELECTED]  = \"#FFFFFF\"\n")
              + QStringLiteral("  bg[INSENSITIVE] = \"") + bg + QStringLiteral("\"\n")
              + QStringLiteral("  fg[INSENSITIVE] = \"") + dis + QStringLiteral("\"\n")
              + QStringLiteral("}\n")
              + QStringLiteral("widget_class \"*\" style \"ncde\"\n")
              + QStringLiteral("class \"*\" style \"ncde\"\n"));
}

// oracle applyGtkTheme (0016eb92)
void writeGtkTheme(const QString &home, bool dark)
{
    seedGtkFiles(home);
    const QString palette = dark ? QStringLiteral("_palette-dark.css") : QStringLiteral("_palette-light.css");
    const QString other = dark ? QStringLiteral("_palette-light.css") : QStringLiteral("_palette-dark.css");

    writeText(home + QStringLiteral("/.themes/NCDE/gtk-3.0/gtk.css"),
              QStringLiteral("/* NCDE — managed by NCDEEngine. Do not edit. */\n")
              + QStringLiteral("@import url(\"") + palette + QStringLiteral("\");\n")
              + QStringLiteral("@import url(\"_accent.css\");\n")
              + QStringLiteral("@import url(\"_rules.css\");\n"));

    QFile gtk4(home + QStringLiteral("/.config/gtk-4.0/gtk.css"));
    if (gtk4.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString css = QString::fromUtf8(gtk4.readAll());
        gtk4.close();
        css.replace(QStringLiteral("@import url(\"") + other + QStringLiteral("\")"),
                    QStringLiteral("@import url(\"") + palette + QStringLiteral("\")"));
        writeText(gtk4.fileName(), css);
    }

    const QString iniPath = home + QStringLiteral("/.config/gtk-4.0/settings.ini");
    QString ini;
    QFile iniFile(iniPath);
    if (iniFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ini = QString::fromUtf8(iniFile.readAll());
        iniFile.close();
    }
    const auto setKey = [&ini](const QString &key, const QString &value) {
        const QRegularExpression re(key + QStringLiteral("=.*"));
        if (ini.contains(re))
            ini.replace(re, key + QLatin1Char('=') + value);
        else
            ini += key + QLatin1Char('=') + value + QLatin1Char('\n');
    };
    setKey(QStringLiteral("gtk-theme-name"), QStringLiteral("NCDE"));
    setKey(QStringLiteral("gtk-application-prefer-dark-theme"),
           dark ? QStringLiteral("true") : QStringLiteral("false"));
    writeText(iniPath, ini);

    if (!qEnvironmentVariableIsSet("NCDE_NO_EXTERNAL_THEME_COMMANDS")) {
        QProcess::startDetached(QStringLiteral("gsettings"),
            {QStringLiteral("set"), QStringLiteral("org.gnome.desktop.interface"),
             QStringLiteral("color-scheme"),
             dark ? QStringLiteral("prefer-dark") : QStringLiteral("default")});
        QProcess::startDetached(QStringLiteral("gsettings"),
            {QStringLiteral("set"), QStringLiteral("org.gnome.desktop.interface"),
             QStringLiteral("gtk-theme"), QStringLiteral("NCDE")});
        QProcess::startDetached(QStringLiteral("/usr/local/bin/ncde-chromium-sync.sh"),
            {dark ? QStringLiteral("dark") : QStringLiteral("light")});
    }

    // ~/.gtkrc-2.0: written by writeGtk2 from recompute() with the live palette (fix 10)
}

// oracle applyGtkAccent (00170f3a)
void writeGtkAccent(const QString &home, const QString &accentName)
{
    seedGtkFiles(home);
    const QString css = QStringLiteral("/* NCDEEngine — wallpaper accent. Do not edit. */\n")
        + QStringLiteral("@define-color ncde_accent ") + accentName + QStringLiteral(";\n")
        + QStringLiteral("@define-color theme_selected_bg_color @ncde_accent;\n");
    writeText(home + QStringLiteral("/.themes/NCDE/gtk-3.0/_accent.css"), css);
    writeText(home + QStringLiteral("/.config/gtk-4.0/_accent.css"), css);
}
} // namespace

// ---------------------------------------------------------------- construction
NCDEEngine::NCDEEngine(QObject *parent)
    : QObject(parent)
{
    m_recomputeTimer.setSingleShot(true);
    connect(&m_recomputeTimer, &QTimer::timeout, this, &NCDEEngine::recompute);
    recompute();
    loadPersistedFiligree();
    loadActiveFiligreepalette();
}

NCDEEngine::~NCDEEngine() = default;

// ---------------------------------------------------------------- getters
#define NCDE_COLOR_GETTER(name, member) QColor NCDEEngine::name() const { return member; }
NCDE_COLOR_GETTER(accent, m_accent)
NCDE_COLOR_GETTER(accentMuted, m_accentMuted)
NCDE_COLOR_GETTER(background, m_background)
NCDE_COLOR_GETTER(surface, m_surface)
NCDE_COLOR_GETTER(surfaceAlt, m_surfaceAlt)
NCDE_COLOR_GETTER(surfaceHi, m_surfaceHi)
NCDE_COLOR_GETTER(panelBg, m_panelBg)
NCDE_COLOR_GETTER(panelText, m_ink)
NCDE_COLOR_GETTER(popupBg, m_popupBg)
NCDE_COLOR_GETTER(border, m_border)
NCDE_COLOR_GETTER(glow, m_glow)
NCDE_COLOR_GETTER(ink, m_ink)
NCDE_COLOR_GETTER(inkSoft, m_inkSoft)
NCDE_COLOR_GETTER(verd, m_verd)
NCDE_COLOR_GETTER(cer, m_cer)
NCDE_COLOR_GETTER(rose, m_rose)
NCDE_COLOR_GETTER(amber, m_amber)
NCDE_COLOR_GETTER(clockColor, m_ink)
NCDE_COLOR_GETTER(lamp, m_amber)
NCDE_COLOR_GETTER(foreground, m_foreground)
NCDE_COLOR_GETTER(topShadow, m_topShadow)
NCDE_COLOR_GETTER(bottomShadow, m_bottomShadow)
NCDE_COLOR_GETTER(selectColor, m_selectColor)
NCDE_COLOR_GETTER(activeBg, m_surface)
NCDE_COLOR_GETTER(activeFg, m_foreground)
NCDE_COLOR_GETTER(activeTs, m_topShadow)
NCDE_COLOR_GETTER(activeBs, m_bottomShadow)
NCDE_COLOR_GETTER(inactiveBg, m_panelBg)
NCDE_COLOR_GETTER(inactiveFg, m_inactiveFg)
NCDE_COLOR_GETTER(inactiveTs, m_inactiveTs)
NCDE_COLOR_GETTER(inactiveBs, m_inactiveBs)
#undef NCDE_COLOR_GETTER

QColor NCDEEngine::gilt0() const { return m_gilt[0]; }
QColor NCDEEngine::gilt1() const { return m_gilt[1]; }
QColor NCDEEngine::gilt2() const { return m_gilt[2]; }
QColor NCDEEngine::gilt3() const { return m_gilt[3]; }
QColor NCDEEngine::gilt4() const { return m_gilt[4]; }
QColor NCDEEngine::gilt5() const { return m_gilt[5]; }
QColor NCDEEngine::wine1() const { return m_wine[0]; }
QColor NCDEEngine::wine2() const { return m_wine[1]; }
QColor NCDEEngine::wine3() const { return m_wine[2]; }
QColor NCDEEngine::wine4() const { return m_wine[3]; }
QColor NCDEEngine::widgetC0() const { return m_widgetC[0]; }
QColor NCDEEngine::widgetC1() const { return m_widgetC[1]; }
QColor NCDEEngine::widgetC2() const { return m_widgetC[2]; }
QColor NCDEEngine::widgetC3() const { return m_widgetC[3]; }
QColor NCDEEngine::widgetC4() const { return m_widgetC[4]; }
QColor NCDEEngine::widgetC5() const { return m_widgetC[5]; }

bool NCDEEngine::darkMode() const { return m_darkMode; }
QString NCDEEngine::activeFiligreePaletteName() const { return m_activeFiligreePaletteName; }
QVariantMap NCDEEngine::activeFiligreePalette() const { return m_activeFiligreePalette; }
QVariantMap NCDEEngine::filigreePalettes() const { return filigreePalettesRaw(); }
bool NCDEEngine::presetActive() const { return m_presetActive; }
bool NCDEEngine::usingCustomBase() const { return m_usingCustomBase; }
int NCDEEngine::fontSize_sm() const { return m_fontSizeSm; }
int NCDEEngine::fontSize_md() const { return m_fontSizeMd; }
int NCDEEngine::fontSize_lg() const { return m_fontSizeLg; }
int NCDEEngine::letterSpacing() const { return m_letterSpacing; }
double NCDEEngine::lineHeight() const { return m_lineHeight; }
QString NCDEEngine::themeName() const { return m_themeName; }
QString NCDEEngine::accentName() const { return m_accentName; }
QString NCDEEngine::darkModeLock() const { return m_darkModeLock; }
QString NCDEEngine::overrideAccent() const { return m_overrideAccent; }
QString NCDEEngine::overrideAccentMuted() const { return m_overrideAccentMuted; }
QString NCDEEngine::overrideBorder() const { return m_overrideBorder; }
QString NCDEEngine::overrideGlow() const { return m_overrideGlow; }
QString NCDEEngine::bodyFont() const { return m_bodyFont; }
QString NCDEEngine::titleFont() const { return m_titleFont; }
QString NCDEEngine::monoFont() const { return m_monoFont; }
QString NCDEEngine::displayFont() const { return m_displayFont; }
QString NCDEEngine::fellFont() const { return m_fellFont; }
QString NCDEEngine::garFont() const { return m_garFont; }
QString NCDEEngine::version() const { return QStringLiteral("Poseidon 14.2"); }
double NCDEEngine::uiScale() const { return m_uiScale; }
double NCDEEngine::fontSizeScale() const { return m_fontSizeScale; }

// ---------------------------------------------------------------- presets
QVariantList NCDEEngine::presets()
{
    QVariantList result;
    for (const PresetData &p : kPresets) {
        QVariantMap m;
        m.insert(QStringLiteral("id"), QString::fromUtf8(p.id));
        m.insert(QStringLiteral("name"), QString::fromUtf8(p.name));
        m.insert(QStringLiteral("accent"), QString::fromUtf8(p.accent));
        m.insert(QStringLiteral("dark"), p.dark);
        result.append(m);
    }
    return result;
}

void NCDEEngine::applyPreset(const QString &id)
{
    for (const PresetData &p : kPresets) {
        if (id != QLatin1String(p.id))
            continue;
        QColor accentC(QString::fromUtf8(p.accent));
        QColor borderC(QString::fromUtf8(p.border));
        QColor panelC(QString::fromUtf8(p.panelBg));
        QColor surfaceC(QString::fromUtf8(p.surface));
        QColor inkC(QString::fromUtf8(p.ink));
        QColor inkSoftC(QString::fromUtf8(p.inkSoft));
        if (m_wallMix) {
            accentC = mixLab(accentC, m_wallAccent, 0.25);
            borderC = mixLab(borderC, m_wallBorder, 0.25);
            panelC = mixLab(panelC, m_wallBackground, 0.25);
            surfaceC = mixLab(surfaceC, m_wallSurface, 0.25);
            inkC = mixLab(inkC, m_wallInk, 0.25);
            inkSoftC = mixLab(inkSoftC, m_wallInkSoft, 0.25);
        }
        if (m_presetActive && !m_usingCustomBase && m_themeName == QLatin1String(p.name)
            && m_darkMode == p.dark && m_baseAccent == accentC && m_baseBorder == borderC
            && m_panelBg == panelC && m_surface == surfaceC && m_inkSoft == inkSoftC)
            return;                                                        // fix 6: already showing it
        m_baseAccent = accentC;
        m_baseGlow = QColor(accentC.red(), accentC.green(), accentC.blue(), 0x66);
        m_baseBorder = borderC;
        m_panelBg = panelC;
        m_background = m_panelBg;
        m_surface = surfaceC;
        m_ink = inkC;
        m_inkSoft = inkSoftC;
        m_darkMode = p.dark;
        m_themeName = QString::fromUtf8(p.name);
        m_accentName = QString::fromUtf8(p.name);
        m_presetActive = true;
        m_usingCustomBase = false;
        recompute();
        applyGtkTheme(m_darkMode);
        return;
    }
}

QVariantMap NCDEEngine::currentBasePalette()
{
    QVariantMap m;
    m.insert(QStringLiteral("accent"), m_accent.name());
    m.insert(QStringLiteral("border"), m_border.name());
    m.insert(QStringLiteral("panelBg"), m_panelBg.name());
    m.insert(QStringLiteral("surface"), m_surface.name());
    m.insert(QStringLiteral("ink"), m_ink.name());
    m.insert(QStringLiteral("inkSoft"), m_inkSoft.name());
    m.insert(QStringLiteral("dark"), m_darkMode);
    return m;
}

// ---------------------------------------------------------------- wallpaper
bool NCDEEngine::sampleWallpaper(const QString &path)
{
    QImage img(localPath(path));
    if (img.isNull())
        return false;
    img = img.convertToFormat(QImage::Format_RGB32)
              .scaled(160, 120, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QHash<uint, int> hist;
    for (int y = 0; y < img.height(); ++y) {
        const QRgb *line = reinterpret_cast<const QRgb *>(img.constScanLine(y));
        for (int x = 0; x < img.width(); ++x) {
            const QRgb px = line[x];
            const uint key = uint(qBlue(px) >> 3) | (uint(qRed(px) >> 3) << 10) | (uint(qGreen(px) >> 3) << 5);
            ++hist[key];
        }
    }
    QList<Sample> samples;
    for (auto it = hist.constBegin(); it != hist.constEnd(); ++it) {
        const uint k = it.key();
        Lab lab;
        rgbToLab(int((k >> 10 & 0x1f) << 3), int((k >> 5 & 0x1f) << 3), int((k & 0x1f) << 3), lab);
        samples.append({lab.L, lab.a, lab.b, double(it.value())});
    }
    if (samples.isEmpty())
        return false;
    std::sort(samples.begin(), samples.end(),
              [](const Sample &a, const Sample &b) { return b.w < a.w; });

    const int k = std::min(6, int(samples.size()));
    QList<Lab> centers(k);
    QList<double> weights(k, 0.0);
    for (int i = 0; i < k; ++i)
        centers[i] = {samples[i].L, samples[i].a, samples[i].b};
    for (int iter = 0; iter < 12; ++iter) {
        QList<Lab> sums(k, Lab{});
        QList<double> wsum(k, 0.0);
        for (const Sample &s : samples) {
            int best = 0;
            double bestD = 1e18;
            const Lab sl{s.L, s.a, s.b};
            for (int c = 0; c < k; ++c) {
                const double d = labDist2(sl, centers[c]);
                if (d < bestD) {
                    best = c;
                    bestD = d;
                }
            }
            sums[best].L += s.w * s.L;
            sums[best].a += s.w * s.a;
            sums[best].b += s.w * s.b;
            wsum[best] += s.w;
        }
        for (int c = 0; c < k; ++c) {
            if (wsum[c] > 0.0) {
                centers[c] = {sums[c].L / wsum[c], sums[c].a / wsum[c], sums[c].b / wsum[c]};
                weights[c] = wsum[c];
            }
        }
    }
    int heavy = 0, vivid = 0;
    double heavyW = -1.0, vividC = -1.0;
    for (int c = 0; c < k; ++c) {
        if (heavyW < weights[c]) {
            heavyW = weights[c];
            heavy = c;
        }
        const double chroma2 = centers[c].a * centers[c].a + centers[c].b * centers[c].b;
        if (vividC < (weights[c] > 0.0 ? 1.0 : 0.0) * chroma2) {   // oracle comparison, verbatim
            vividC = chroma2;
            vivid = c;
        }
    }
    const QColor ground = labToColor(centers[heavy]);
    QColor accentC = labToColor(centers[vivid]);
    float h, s, v;
    accentC.getHsvF(&h, &s, &v);
    if (h < 0.0f)
        h = accentC.hueF() >= 0.0f ? accentC.hueF() : 0.0f;
    const float vB = qBound(0.55f, v, 0.92f);
    const float sB = qBound(0.45f, s, 0.95f);
    accentC = QColor::fromHsvF(std::max(0.0f, h), sB, vB, 1.0f);

    m_baseAccent = accentC;
    m_baseGlow = QColor(accentC.red(), accentC.green(), accentC.blue(), 0x66);
    m_baseBorder = liteScale(accentC, 15);
    m_inkSoft = darkScale(accentC, 12);
    const bool dark = brightness(ground) < 0.45;
    m_darkMode = dark;
    m_surface = ground;
    m_panelBg = dark ? liteScale(ground, 55) : darkScale(ground, 35);
    m_background = m_panelBg;
    m_popupBg = dark ? liteScale(ground, 70) : darkScale(ground, 20);
    m_ink = dark ? darkScale(accentC, 80) : liteScale(accentC, 80);
    m_usingCustomBase = true;
    m_presetActive = false;
    m_themeName = QStringLiteral("From Wallpaper");
    m_accentName = ColorMath::poeticName(double(accentC.hsvHueF()) * 360.0, double(accentC.lightnessF()));
    m_wallAccent = m_baseAccent;
    m_wallBorder = m_baseBorder;
    m_wallGlow = m_baseGlow;
    m_wallSurface = m_surface;
    m_wallBackground = m_background;
    m_wallPopup = m_popupBg;
    m_wallInk = m_ink;
    m_wallInkSoft = m_inkSoft;
    m_wallDark = m_darkMode;
    m_wallMix = true;
    recompute();
    applyGtkTheme(m_darkMode);
    applyGtkAccent();
    emit previewReady(currentBasePalette());
    return true;
}

QVariantMap NCDEEngine::previewWallpaper(const QString &path)
{
    const QColor baseAccent = m_baseAccent, baseBorder = m_baseBorder, baseGlow = m_baseGlow;
    const QColor surfaceC = m_surface, panelC = m_panelBg, popupC = m_popupBg;
    const QColor inkC = m_ink, inkSoftC = m_inkSoft;
    const bool dark = m_darkMode, custom = m_usingCustomBase, preset = m_presetActive;
    const QString themeName = m_themeName, accentName = m_accentName;
    QVariantMap result;
    if (sampleWallpaper(path)) {
        result = currentBasePalette();
        result.insert(QStringLiteral("text"), m_ink.name());              // fix 9: WallpapersTab reads
        result.insert(QStringLiteral("valid"), true);                     //        .valid + ["text"]
    }
    m_baseAccent = baseAccent;
    m_baseBorder = baseBorder;
    m_baseGlow = baseGlow;
    m_surface = surfaceC;
    m_panelBg = panelC;
    m_background = m_panelBg;
    m_popupBg = popupC;
    m_ink = inkC;
    m_inkSoft = inkSoftC;
    m_darkMode = dark;
    m_usingCustomBase = custom;
    m_presetActive = preset;
    m_themeName = themeName;
    m_accentName = accentName;
    recompute();
    return result;
}

void NCDEEngine::previewWallpaperAsync(const QString &path)
{
    emit previewReady(previewWallpaper(path));
}

// ---------------------------------------------------------------- glass / widget styles
void NCDEEngine::setSurfaceGlass(const QString &key, const QColor &tint, double shine,
                                double glowAmount, const QColor &borderColor, const QColor &glowColor)
{
    QVariantMap m;
    m.insert(QStringLiteral("tint"), tint.name(QColor::HexArgb));
    m.insert(QStringLiteral("shine"), shine);
    m.insert(QStringLiteral("glow"), glowAmount);
    m.insert(QStringLiteral("border"), borderColor.name());
    m.insert(QStringLiteral("glowColor"), glowColor.name());
    m_surfaceGlass.insert(key, m);
    emit changed();
}

QVariantMap NCDEEngine::surfaceGlass(const QString &key)
{
    if (m_surfaceGlass.contains(key))
        return m_surfaceGlass.value(key);
    QVariantMap m;
    m.insert(QStringLiteral("tint"), m_panelBg.name(QColor::HexArgb));
    m.insert(QStringLiteral("shine"), 0.35);
    m.insert(QStringLiteral("glow"), 0.5);
    m.insert(QStringLiteral("border"), m_border.name());
    m.insert(QStringLiteral("glowColor"), m_glow.name());
    return m;
}

void NCDEEngine::setWidgetStyleMap(const QString &key, const QVariantMap &map)
{
    // Fix 4 (declared addition): FiligreeTab pushes the whole map here; Settings persists it.
    m_widgetStyles.insert(key, map);
    emit changed();
}

void NCDEEngine::setWidgetStyle(const QString &key, const QColor &accentColor,
                               const QColor &fill, const QString &font)
{
    QVariantMap m = m_widgetStyles.value(key);
    m.insert(QStringLiteral("accent"), accentColor.name());
    m.insert(QStringLiteral("fill"), fill.name());
    m.insert(QStringLiteral("font"), font);
    m_widgetStyles.insert(key, m);
    emit changed();
}

QVariantMap NCDEEngine::widgetStyle(const QString &key)
{
    return m_widgetStyles.value(key);
}

void NCDEEngine::resetWidgetStyle(const QString &key)
{
    // Fix 4 (declared addition): oracle had no such method, so the Filigree reset handler threw.
    if (m_widgetStyles.remove(key))
        emit changed();
}

// ---------------------------------------------------------------- overrides / fonts / scale
void NCDEEngine::setOverrideAccent(const QString &value) { m_overrideAccent = value; scheduleRecompute(); }
void NCDEEngine::setOverrideAccentMuted(const QString &value) { m_overrideAccentMuted = value; scheduleRecompute(); }
void NCDEEngine::setOverrideBorder(const QString &value) { m_overrideBorder = value; scheduleRecompute(); }
void NCDEEngine::setOverrideGlow(const QString &value) { m_overrideGlow = value; scheduleRecompute(); }

void NCDEEngine::setBodyFont(const QString &f) { m_bodyFont = f; emit changed(); }
void NCDEEngine::setTitleFont(const QString &f) { m_titleFont = f; emit changed(); }
void NCDEEngine::setMonoFont(const QString &f) { m_monoFont = f; emit changed(); }
void NCDEEngine::setDisplayFont(const QString &f) { m_displayFont = f; emit changed(); }
void NCDEEngine::setFellFont(const QString &f) { m_fellFont = f; emit changed(); }
void NCDEEngine::setGarFont(const QString &f) { m_garFont = f; emit changed(); }

void NCDEEngine::setUiScale(double s) { m_uiScale = s; recomputeFontSizes(); }
void NCDEEngine::setFontSizeScale(double s) { m_fontSizeScale = s; recomputeFontSizes(); }
void NCDEEngine::setLetterSpacing(double v) { m_letterSpacing = int(v); emit changed(); }
void NCDEEngine::setLineHeight(double v) { m_lineHeight = v; emit changed(); }

void NCDEEngine::recomputeFontSizes()
{
    const double k = m_fontSizeScale * m_uiScale;
    m_fontSizeSm = std::max(1, qRound(k * 11.0));
    m_fontSizeMd = std::max(1, qRound(k * 14.0));
    m_fontSizeLg = std::max(1, qRound(k * 20.0));
    emit changed();
    emit themeChanged();
}

// ---------------------------------------------------------------- theme file
QVariantMap NCDEEngine::toJson()
{
    QVariantMap m;
    m.insert(QStringLiteral("accent"), m_accentName);
    m.insert(QStringLiteral("customAccent"), m_baseAccent.name());
    m.insert(QStringLiteral("customBase"), m_background.name());
    m.insert(QStringLiteral("darkModeLock"), m_darkModeLock);
    m.insert(QStringLiteral("mode"), m_darkMode ? QStringLiteral("dark") : QStringLiteral("light"));
    m.insert(QStringLiteral("sampledPanelText"), m_ink.name());
    m.insert(QStringLiteral("usingCustomBase"), m_usingCustomBase);
    m.insert(QStringLiteral("bodyFont"), m_bodyFont);
    m.insert(QStringLiteral("titleFont"), m_titleFont);
    m.insert(QStringLiteral("monoFont"), m_monoFont);
    m.insert(QStringLiteral("displayFont"), m_displayFont);
    m.insert(QStringLiteral("fellFont"), m_fellFont);
    m.insert(QStringLiteral("garFont"), m_garFont);
    return m;
}

bool NCDEEngine::saveTheme(const QString &path)
{
    const QString file = localPath(path);
    QDir().mkpath(QFileInfo(file).absolutePath());
    QSaveFile out(file);                                                   // fix 8: atomic
    if (!out.open(QIODevice::WriteOnly))
        return false;
    out.write(QJsonDocument(QJsonObject::fromVariantMap(toJson())).toJson(QJsonDocument::Indented));
    return out.commit();
}

bool NCDEEngine::loadTheme(const QString &path)
{
    const QString file = localPath(path);
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly))
        return false;
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    if (!doc.isObject())
        return false;
    const QVariantMap m = doc.object().toVariantMap();
    m_accentName = m.value(QStringLiteral("accent"), m_accentName).toString();
    m_darkModeLock = m.value(QStringLiteral("darkModeLock")).toString();
    m_darkMode = m.value(QStringLiteral("mode")).toString() != QLatin1String("light");
    m_usingCustomBase = m.value(QStringLiteral("usingCustomBase")).toBool();
    m_presetActive = !m_usingCustomBase;
    if (m.contains(QStringLiteral("customAccent")))
        m_baseAccent = QColor(m.value(QStringLiteral("customAccent")).toString());
    if (m.contains(QStringLiteral("customBase"))) {
        m_panelBg = QColor(m.value(QStringLiteral("customBase")).toString());
        m_background = m_panelBg;
        m_surface = m_background;
    }
    if (m.contains(QStringLiteral("sampledPanelText")))
        m_ink = QColor(m.value(QStringLiteral("sampledPanelText")).toString());
    if (m.contains(QStringLiteral("bodyFont"))) m_bodyFont = m.value(QStringLiteral("bodyFont")).toString();
    if (m.contains(QStringLiteral("titleFont"))) m_titleFont = m.value(QStringLiteral("titleFont")).toString();
    if (m.contains(QStringLiteral("monoFont"))) m_monoFont = m.value(QStringLiteral("monoFont")).toString();
    if (m.contains(QStringLiteral("displayFont"))) m_displayFont = m.value(QStringLiteral("displayFont")).toString();
    if (m.contains(QStringLiteral("fellFont"))) m_fellFont = m.value(QStringLiteral("fellFont")).toString();
    if (m.contains(QStringLiteral("garFont"))) m_garFont = m.value(QStringLiteral("garFont")).toString();
    m_baseGlow = QColor(m_baseAccent.red(), m_baseAccent.green(), m_baseAccent.blue(), 0x66);
    m_baseBorder = liteScale(m_baseAccent, 15);
    recompute();
    applyGtkTheme(m_darkMode);
    applyGtkAccent();
    if (!m_themeWatcher) {
        m_themeWatcher = new QFileSystemWatcher(this);
        connect(m_themeWatcher, &QFileSystemWatcher::fileChanged, this, [this](const QString &changedPath) {
            loadTheme(changedPath);
            if (!m_themeWatcher->files().contains(changedPath))
                m_themeWatcher->addPath(changedPath);
        });
    }
    if (!m_themeWatcher->files().contains(file))
        m_themeWatcher->addPath(file);
    return true;
}

// ---------------------------------------------------------------- terminal
void NCDEEngine::setTerminalFont(const QString &font)
{
    setTerminalConfigField(QStringLiteral("fontFamily"), font);
}

void NCDEEngine::setTerminalGlassTint(double tint)
{
    setTerminalConfigField(QStringLiteral("glassTint"), qBound(0.0, tint, 1.0));
}

QVariantMap NCDEEngine::terminalConfig()
{
    return readJsonMap(QDir::homePath() + QStringLiteral("/.config/ncde-terminal/config.json"));
}

void NCDEEngine::setTerminalConfigField(const QString &key, const QVariant &value)
{
    const QString path = QDir::homePath() + QStringLiteral("/.config/ncde-terminal/config.json");
    QDir().mkpath(QFileInfo(path).absolutePath());
    QJsonObject obj;
    QFile in(path);
    if (in.open(QIODevice::ReadOnly)) {
        const QJsonDocument doc = QJsonDocument::fromJson(in.readAll());
        in.close();
        if (doc.isObject())
            obj = doc.object();
    }
    obj[key] = QJsonValue::fromVariant(value);
    QFile out(path);
    if (out.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        out.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
        out.close();
    }
}

// ---------------------------------------------------------------- filigree palettes
QString NCDEEngine::filigreePalettesPath()
{
    return QDir::homePath() + QStringLiteral("/.config/ncde/filigree-palettes.json");
}

QVariantMap NCDEEngine::filigreePalettesRaw() const
{
    QVariantMap m = readJsonMap(filigreePalettesPath());
    m.remove(QStringLiteral("_active"));
    return m;
}

bool NCDEEngine::writeFiligreePalettes(const QVariantMap &palettes)
{
    const QString path = filigreePalettesPath();
    QDir().mkpath(QFileInfo(path).absolutePath());
    QJsonObject obj = QJsonObject::fromVariantMap(palettes);
    QFile in(path);
    if (in.open(QIODevice::ReadOnly)) {
        const QJsonDocument doc = QJsonDocument::fromJson(in.readAll());
        in.close();
        if (doc.isObject() && doc.object().contains(QStringLiteral("_active")))
            obj[QStringLiteral("_active")] = doc.object().value(QStringLiteral("_active"));
    }
    QFile out(path);
    if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    out.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
    out.close();
    return true;
}

void NCDEEngine::writeActiveFiligreepaletteName() const
{
    const QString path = filigreePalettesPath();
    QDir().mkpath(QFileInfo(path).absolutePath());
    QJsonObject obj;
    QFile in(path);
    if (in.open(QIODevice::ReadOnly)) {
        const QJsonDocument doc = QJsonDocument::fromJson(in.readAll());
        in.close();
        if (doc.isObject())
            obj = doc.object();
    }
    obj[QStringLiteral("_active")] = m_activeFiligreePaletteName;
    QFile out(path);
    if (out.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        out.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
        out.close();
    }
}

bool NCDEEngine::saveFiligreepalette(const QString &name, const QVariantMap &colors)
{
    const QString clean = name.trimmed();
    if (clean.isEmpty() || colors.isEmpty())
        return false;
    QVariantMap all = filigreePalettesRaw();
    all[clean] = colors;
    m_activeFiligreePaletteName = clean;
    m_activeFiligreePalette = colors;
    if (!writeFiligreePalettes(all))
        return false;
    writeActiveFiligreepaletteName();
    emit filigreePalettesChanged();
    return true;
}

bool NCDEEngine::deleteFiligreepalette(const QString &name)
{
    QVariantMap all = filigreePalettesRaw();
    if (!all.contains(name))
        return false;
    all.remove(name);
    if (!writeFiligreePalettes(all))
        return false;
    if (m_activeFiligreePaletteName == name) {
        m_activeFiligreePaletteName.clear();
        m_activeFiligreePalette.clear();
        writeActiveFiligreepaletteName();
    }
    emit filigreePalettesChanged();
    return true;
}

bool NCDEEngine::setActiveFiligreepalette(const QString &name)
{
    const QVariantMap all = filigreePalettesRaw();
    if (!all.contains(name))
        return false;
    const QVariantMap p = all.value(name).toMap();
    m_activeFiligreePaletteName = name;
    m_activeFiligreePalette = p;
    writeActiveFiligreepaletteName();
    const QColor panelC(p.value(QStringLiteral("panelBg")).toString());
    const QColor accentC(p.value(QStringLiteral("accent")).toString());
    const QColor inkC(p.value(QStringLiteral("ink")).toString());
    if (panelC.isValid() && accentC.isValid() && inkC.isValid())
        setBaseColor(panelC, accentC, inkC);
    if (p.contains(QStringLiteral("dark")))
        setDarkMode(p.value(QStringLiteral("dark")).toBool());
    emit filigreePalettesChanged();
    return true;
}

void NCDEEngine::loadPersistedFiligree()
{
    const QVariantMap glass = readJsonMap(configPath(QStringLiteral("glass-surfaces.json")));
    for (auto it = glass.constBegin(); it != glass.constEnd(); ++it)
        m_surfaceGlass.insert(it.key(), it.value().toMap());
    const QVariantMap styles = readJsonMap(configPath(QStringLiteral("widget-styles.json")));
    for (auto it = styles.constBegin(); it != styles.constEnd(); ++it)
        m_widgetStyles.insert(it.key(), it.value().toMap());
}

void NCDEEngine::loadActiveFiligreepalette()
{
    const QVariantMap file = readJsonMap(filigreePalettesPath());
    const QString active = file.value(QStringLiteral("_active")).toString();
    if (active.isEmpty())
        return;
    const QVariantMap all = filigreePalettesRaw();
    if (all.contains(active)) {
        m_activeFiligreePaletteName = active;
        m_activeFiligreePalette = all.value(active).toMap();
    }
}

// ---------------------------------------------------------------- palette / mode slots
void NCDEEngine::applyPalette(const QVariantMap &p)
{
    const auto take = [&p](const char *key, QColor &target) {
        const QString k = QString::fromLatin1(key);
        if (p.contains(k)) {
            const QColor c(p.value(k).toString());
            if (c.isValid())
                target = c;
        }
    };
    take("accent", m_accent);
    take("accentMuted", m_accentMuted);
    take("background", m_background);
    take("surface", m_surface);
    take("surfaceAlt", m_surfaceAlt);
    take("panelBg", m_panelBg);
    take("popupBg", m_popupBg);
    take("border", m_border);
    take("glow", m_glow);
    take("ink", m_ink);
    take("verd", m_verd);
    take("cer", m_cer);
    take("rose", m_rose);
    if (p.contains(QStringLiteral("darkMode")))
        m_darkMode = p.value(QStringLiteral("darkMode")).toBool();
    recompute();
}

void NCDEEngine::setDarkMode(bool d)
{
    if (d == m_darkMode)
        return;
    m_darkMode = d;
    recompute();
    applyGtkTheme(d);
    applyGtkAccent();
    emit darkModeChanged();
}

void NCDEEngine::setAccentName(const QString &n)
{
    if (n == m_accentName)
        return;
    m_accentName = n;
    emit changed();
}

void NCDEEngine::setDarkModeLock(const QString &lock)
{
    m_darkModeLock = lock;
    if (lock == QLatin1String("light"))
        m_darkMode = false;
    else if (lock == QLatin1String("dark"))
        m_darkMode = true;
    recompute();
    applyGtkTheme(m_darkMode);
    applyGtkAccent();
}

void NCDEEngine::setBaseColor(const QColor &base, const QColor &accentColor, const QColor &panelText)
{
    m_background = base;
    m_surface = base;
    m_panelBg = base;
    m_baseAccent = accentColor;
    m_ink = panelText;
    m_baseBorder = liteScale(accentColor, 15);
    m_baseGlow = QColor(accentColor.red(), accentColor.green(), accentColor.blue(), 0x66);
    m_usingCustomBase = true;
    m_presetActive = false;
    m_accentName = ColorMath::poeticName(double(accentColor.hueF()) * 360.0, double(accentColor.lightnessF()));
    recompute();
}

void NCDEEngine::clearCustomBase()
{
    m_usingCustomBase = false;
    recompute();
}

// ---------------------------------------------------------------- GTK bridge
void NCDEEngine::seedGtkUserConfig()
{
    const QString home = QDir::homePath();
    bridgePool().start(QRunnable::create([home] { seedGtkFiles(home); }));
}

void NCDEEngine::applyGtkTheme(bool dark)
{
    const QString home = QDir::homePath();
    bridgePool().start(QRunnable::create([home, dark] { writeGtkTheme(home, dark); }));
}

void NCDEEngine::applyGtkAccent()
{
    const QString home = QDir::homePath();
    const QString accentHex = m_accent.name();
    bridgePool().start(QRunnable::create([home, accentHex] { writeGtkAccent(home, accentHex); }));
}

// ---------------------------------------------------------------- recompute
void NCDEEngine::scheduleRecompute()
{
    if (!m_recomputeTimer.isActive())
        m_recomputeTimer.start();
}

// fix 7: ink >= 7:1 over panelBg and surface (gtk.md §8.1). Ink walks toward white or black in Lab,
// whichever end can carry the grounds; if even pure white/black can't, the grounds walk the other way.
void NCDEEngine::enforceInkFloor()
{
    constexpr double kFloor = 7.0;
    const auto worst = [this](const QColor &ink) {
        return std::min(ColorMath::contrastRatio(ink, m_panelBg), ColorMath::contrastRatio(ink, m_surface));
    };
    if (!m_ink.isValid() || worst(m_ink) >= kFloor)
        return;
    const QColor white(Qt::white), black(Qt::black);
    const bool lightInk = worst(white) >= worst(black);
    const QColor end = lightInk ? white : black;
    for (int step = 1; step <= 20; ++step) {
        const QColor c = ColorMath::mixLab(m_ink, end, step / 20.0);
        if (worst(c) >= kFloor) {
            m_ink = c;
            return;
        }
    }
    m_ink = end;
    const QColor away = lightInk ? black : white;
    const QColor panel0 = m_panelBg, surface0 = m_surface;
    for (int step = 1; step <= 20 && worst(m_ink) < kFloor; ++step) {
        m_panelBg = ColorMath::mixLab(panel0, away, step / 20.0);
        m_surface = ColorMath::mixLab(surface0, away, step / 20.0);
    }
    m_background = m_panelBg;
}

void NCDEEngine::recompute()
{
    enforceInkFloor();
    m_accent = m_overrideAccent.isEmpty() ? m_baseAccent : QColor(m_overrideAccent);
    m_border = m_overrideBorder.isEmpty() ? m_baseBorder : QColor(m_overrideBorder);
    m_glow = m_overrideGlow.isEmpty() ? m_baseGlow : QColor(m_overrideGlow);
    m_surfaceAlt = m_darkMode ? darkScale(m_surface, 8) : liteScale(m_surface, 10);
    deriveAccentSurface();
    if (!m_overrideAccentMuted.isEmpty())
        m_accentMuted = QColor(m_overrideAccentMuted);
    calcColors(m_surface, m_foreground, m_topShadow, m_bottomShadow, m_selectColor);
    QColor unused;
    calcColors(m_panelBg, m_inactiveFg, m_inactiveTs, m_inactiveBs, unused);
    const QStringList gtk2 = {m_darkMode ? QStringLiteral("1") : QStringLiteral("0"), m_panelBg.name(),
                              m_surface.name(), m_ink.name(), m_inkSoft.name(), m_accent.name()};
    const QString sig = gtk2.join(QLatin1Char(','));
    if (sig != m_gtk2Signature) {                                          // fix 10
        m_gtk2Signature = sig;
        const QString home = QDir::homePath();
        bridgePool().start(QRunnable::create([home, gtk2] { writeGtk2(home, gtk2); }));
    }
    emit changed();
    emit themeChanged();
}

void NCDEEngine::deriveAccentSurface()
{
    float h, s, v;
    m_accent.getHsvF(&h, &s, &v);
    if (h < 0.0f)
        h = 0.0f;
    const float sat = std::max(0.35f, s);
    for (int i = 0; i < 6; ++i)
        m_gilt[i] = QColor::fromHsvF(h, sat, kGiltV[i], 1.0f);
    static const QColor kVerd = QColor::fromHsvF(0.39f, 0.55f, 0.65f, 1.0f);
    static const QColor kCer = QColor::fromHsvF(0.65f, 0.55f, 0.65f, 1.0f);
    static const QColor kRose = QColor::fromHsvF(0.92f, 0.6f, 0.78f, 1.0f);
    static const QColor kAmber = QColor::fromHsvF(0.11f, 0.75f, 0.91f, 1.0f);
    m_verd = kVerd;
    m_cer = kCer;
    m_rose = kRose;
    m_amber = kAmber;
    m_accentMuted = QColor::fromHsvF(h, sat * 0.7f, v * 0.7f, 1.0f);
    m_surfaceHi = m_gilt[4];
    m_widgetC[0] = m_surface;
    m_widgetC[1] = m_surfaceAlt;
    m_widgetC[2] = m_verd;
    m_widgetC[3] = m_cer;
    m_widgetC[4] = m_accent;
    m_widgetC[5] = m_rose;
}

void NCDEEngine::calcColors(const QColor &c, QColor &fg, QColor &ts, QColor &bs, QColor &sel) const
{
    const double b = brightness(c);
    fg = b <= 0.7 ? QColor(Qt::white) : QColor(Qt::black);
    if (b < 0.2) {
        ts = darkScale(c, 50);
        bs = darkScale(c, 30);
        sel = darkScale(c, 15);
    } else if (b < 0.46) {
        const double t = (b - 0.2) / 0.26;
        ts = darkScale(c, int(t * 30.0 + 20.0));
        bs = liteScale(c, 40);
        sel = liteScale(c, int(t * 25.0 + 15.0));
    } else {
        ts = liteScale(c, 20);
        bs = liteScale(c, 40);
        sel = liteScale(c, 15);
    }
}

// ---------------------------------------------------------------- colour math (oracle verbatim)
double NCDEEngine::brightness(const QColor &c)
{
    const double r = c.redF(), g = c.greenF(), b = c.blueF();
    return ((b * 0.11 + r * 0.3 + g * 0.59) * 25.0 + ((r + g + b) / 3.0) * 75.0) / 100.0;
}

double NCDEEngine::clamp01(double v)
{
    return v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v);
}

QColor NCDEEngine::liteScale(const QColor &c, int percent)
{
    const double k = 1.0 - double(percent) / 100.0;
    const double b = clamp01(double(c.blueF()) * k);
    const double g = clamp01(double(c.greenF()) * k);
    const double r = clamp01(double(c.redF()) * k);
    return QColor::fromRgbF(float(r), float(g), float(b), 1.0f);
}

QColor NCDEEngine::darkScale(const QColor &c, int percent)
{
    const double k = double(percent) / 100.0;
    const double b = clamp01(double(1.0f - c.blueF()) * k + double(c.blueF()));
    const double g = clamp01(double(1.0f - c.greenF()) * k + double(c.greenF()));
    const double r = clamp01(double(1.0f - c.redF()) * k + double(c.redF()));
    return QColor::fromRgbF(float(r), float(g), float(b), 1.0f);
}

double NCDEEngine::labF(double t)
{
    return t <= 0.008856 ? t * 7.787 + 0.13793103448275862 : std::cbrt(t);
}

void NCDEEngine::rgbToLab(int r, int g, int b, Lab &out)
{
    const auto lin = [](double v) {
        v /= 255.0;
        return v > 0.04045 ? std::pow((v + 0.055) / 1.055, 2.4) : v / 12.92;
    };
    const double rl = lin(r), gl = lin(g), bl = lin(b);
    double x = (bl * 0.1805 + rl * 0.4124 + gl * 0.3576) / 0.95047;
    double y = bl * 0.0722 + rl * 0.2126 + gl * 0.7152;
    double z = (bl * 0.9505 + rl * 0.0193 + gl * 0.1192) / 1.08883;
    x = labF(x);
    y = labF(y);
    z = labF(z);
    out.L = y * 116.0 - 16.0;
    out.a = (x - y) * 500.0;
    out.b = (y - z) * 200.0;
}

double NCDEEngine::labDist2(const Lab &p, const Lab &q)
{
    return (p.b - q.b) * (p.b - q.b) + (p.L - q.L) * (p.L - q.L) + (p.a - q.a) * (p.a - q.a);
}

QColor NCDEEngine::labToColor(const Lab &lab)
{
    const auto finv = [](double t) {
        const double c = t * t * t;
        return c <= 0.008856 ? (t - 0.13793103448275862) / 7.787 : c;
    };
    const auto gam = [](double v) {
        v = v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v);
        return v > 0.0031308 ? std::pow(v, 0.4166666666666667) * 1.055 - 0.055 : v * 12.92;
    };
    const double fy = (lab.L + 16.0) / 116.0;
    const double fx = lab.a / 500.0 + fy;
    const double fz = fy - lab.b / 200.0;
    const double x = finv(fx) * 0.95047;
    const double y = finv(fy);
    const double z = finv(fz) * 1.08883;
    const double r = z * -0.4986 + x * 3.2406 + y * -1.5372;
    const double g = z * 0.0415 + x * -0.9689 + y * 1.8758;
    const double b = z * 1.057 + x * 0.0557 + y * -0.204;
    return QColor::fromRgbF(float(gam(r)), float(gam(g)), float(gam(b)), 1.0f);
}

QColor NCDEEngine::mixLab(const QColor &a, const QColor &b, double t)
{
    Lab la, lb;
    rgbToLab(a.red(), a.green(), a.blue(), la);
    rgbToLab(b.red(), b.green(), b.blue(), lb);
    const Lab m{(lb.L - la.L) * t + la.L, (lb.a - la.a) * t + la.a, (lb.b - la.b) * t + la.b};
    QColor out = labToColor(m);
    out.setAlpha(a.alpha());
    return out;
}
