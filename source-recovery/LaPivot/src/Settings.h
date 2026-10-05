// Settings — NCDE's settings store and appliers: every Settings tab reads and writes these properties, and
// load*/save* keep them in ~/.config/ncde/<area>.json (through Lelan's config helpers). Some areas also apply
// the value to the system (xset, xinput/libinput, xrandr, gsettings, systemctl --user).
//
// Rebuilt from LaPivot oracle 3507b4c6…. The block between GENERATED markers is produced by
// tools/gen_header.py from the oracle's moc metadata (duplicate setter declarations removed) — the QML binds
// to exactly these names. Implementation is split by area: Settings_<area>.cpp. Field defaults are the
// oracle constructor's.
#pragma once

#include <QColor>
#include <QFileSystemWatcher>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QRegularExpression>
#include <QVariant>
#include <QVector>

#include <functional>

class Lelan;
class QProcess;
class QTimer;
class QJsonArray;

#include "IdlePolicy.h"

class Settings : public QObject
{
// ---- GENERATED: tools/gen_header.py Settings ----
    Q_OBJECT
    Q_PROPERTY(QVariantList displays READ displays NOTIFY displaysChanged)
    Q_PROPERTY(bool nightLightOn READ nightLightOn WRITE setNightLightOn NOTIFY settingsChanged)
    Q_PROPERTY(int nightWarmth READ nightWarmth WRITE setNightWarmth NOTIFY settingsChanged)
    Q_PROPERTY(bool nightLightAuto READ nightLightAuto WRITE setNightLightAuto NOTIFY settingsChanged)
    Q_PROPERTY(int batBlank READ batBlank WRITE setBatBlank NOTIFY powerChanged)
    Q_PROPERTY(int batSuspend READ batSuspend WRITE setBatSuspend NOTIFY powerChanged)
    Q_PROPERTY(int acBlank READ acBlank WRITE setAcBlank NOTIFY powerChanged)
    Q_PROPERTY(int acSuspend READ acSuspend WRITE setAcSuspend NOTIFY powerChanged)
    Q_PROPERTY(QString lidAction READ lidAction WRITE setLidAction NOTIFY powerChanged)
    Q_PROPERTY(QString powerButtonAction READ powerButtonAction WRITE setPowerButtonAction NOTIFY powerChanged)
    Q_PROPERTY(bool showBatteryPct READ showBatteryPct WRITE setShowBatteryPct NOTIFY powerChanged)
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontChanged)
    Q_PROPERTY(QString dockHoverTextColor READ dockHoverTextColor WRITE setDockHoverTextColor NOTIFY settingsChanged)
    Q_PROPERTY(QString topPanelTextColor READ topPanelTextColor WRITE setTopPanelTextColor NOTIFY settingsChanged)
    Q_PROPERTY(QString gliaTextColor READ gliaTextColor WRITE setGliaTextColor NOTIFY settingsChanged)
    Q_PROPERTY(QString leapFrogTextColor READ leapFrogTextColor WRITE setLeapFrogTextColor NOTIFY settingsChanged)
    Q_PROPERTY(QString accentOverride READ accentOverride WRITE setAccentOverride NOTIFY settingsChanged)
    Q_PROPERTY(QString accentMutedOverride READ accentMutedOverride WRITE setAccentMutedOverride NOTIFY settingsChanged)
    Q_PROPERTY(QString glowOverride READ glowOverride WRITE setGlowOverride NOTIFY settingsChanged)
    Q_PROPERTY(QString borderOverride READ borderOverride WRITE setBorderOverride NOTIFY settingsChanged)
    Q_PROPERTY(bool slideshowPaused READ slideshowPaused WRITE setSlideshowPaused NOTIFY settingsChanged)
    Q_PROPERTY(int fontWeight READ fontWeight WRITE setFontWeight NOTIFY fontChanged)
    Q_PROPERTY(bool fontItalic READ fontItalic WRITE setFontItalic NOTIFY fontChanged)
    Q_PROPERTY(double fontSizeScale READ fontSizeScale WRITE setFontSizeScale NOTIFY fontChanged)
    Q_PROPERTY(double letterSpacing READ letterSpacing WRITE setLetterSpacing NOTIFY fontChanged)
    Q_PROPERTY(double lineHeight READ lineHeight WRITE setLineHeight NOTIFY fontChanged)
    Q_PROPERTY(double uiScale READ uiScale WRITE setUiScale NOTIFY fontChanged)
    Q_PROPERTY(QString textColor READ textColor WRITE setTextColor NOTIFY fontChanged)
    Q_PROPERTY(bool textOutlineEnabled READ textOutlineEnabled WRITE setTextOutlineEnabled NOTIFY fontChanged)
    Q_PROPERTY(QString textOutlineColor READ textOutlineColor WRITE setTextOutlineColor NOTIFY fontChanged)
    Q_PROPERTY(double textOutlineWidth READ textOutlineWidth WRITE setTextOutlineWidth NOTIFY fontChanged)
    Q_PROPERTY(bool textShadowEnabled READ textShadowEnabled WRITE setTextShadowEnabled NOTIFY fontChanged)
    Q_PROPERTY(QString textShadowColor READ textShadowColor WRITE setTextShadowColor NOTIFY fontChanged)
    Q_PROPERTY(double textShadowOffsetX READ textShadowOffsetX WRITE setTextShadowOffsetX NOTIFY fontChanged)
    Q_PROPERTY(double textShadowOffsetY READ textShadowOffsetY WRITE setTextShadowOffsetY NOTIFY fontChanged)
    Q_PROPERTY(double textShadowRadius READ textShadowRadius WRITE setTextShadowRadius NOTIFY fontChanged)
    Q_PROPERTY(bool autoMountUsb READ autoMountUsb WRITE setAutoMountUsb NOTIFY storageChanged)
    Q_PROPERTY(int kbRepeatDelay READ kbRepeatDelay WRITE setKbRepeatDelay NOTIFY inputChanged)
    Q_PROPERTY(int kbRepeatRate READ kbRepeatRate WRITE setKbRepeatRate NOTIFY inputChanged)
    Q_PROPERTY(int pointerSpeed READ pointerSpeed WRITE setPointerSpeed NOTIFY inputChanged)
    Q_PROPERTY(int touchpadSpeed READ touchpadSpeed WRITE setTouchpadSpeed NOTIFY inputChanged)
    Q_PROPERTY(bool naturalScroll READ naturalScroll WRITE setNaturalScroll NOTIFY inputChanged)
    Q_PROPERTY(bool tapToClick READ tapToClick WRITE setTapToClick NOTIFY inputChanged)
    Q_PROPERTY(bool disableWhileTyping READ disableWhileTyping WRITE setDisableWhileTyping NOTIFY inputChanged)
    Q_PROPERTY(int cursorSize READ cursorSize WRITE setCursorSize NOTIFY inputChanged)
    Q_PROPERTY(double accessibilityTextScale READ accessibilityTextScale WRITE setAccessibilityTextScale NOTIFY accessibilityChanged)
    Q_PROPERTY(bool highContrast READ highContrast WRITE setHighContrast NOTIFY accessibilityChanged)
    Q_PROPERTY(bool reduceMotion READ reduceMotion WRITE setReduceMotion NOTIFY accessibilityChanged)
    Q_PROPERTY(bool largerCursor READ largerCursor WRITE setLargerCursor NOTIFY accessibilityChanged)
    Q_PROPERTY(bool locationEnabled READ locationEnabled WRITE setLocationEnabled NOTIFY privacyChanged)
    Q_PROPERTY(bool lockScreenNotifPreview READ lockScreenNotifPreview WRITE setLockScreenNotifPreview NOTIFY privacyChanged)
    Q_PROPERTY(int screensaverTimeout READ screensaverTimeout WRITE setScreensaverTimeout NOTIFY settingsChanged)
    Q_PROPERTY(QString screensaverSeason READ screensaverSeason WRITE setScreensaverSeason NOTIFY settingsChanged)
    Q_PROPERTY(bool screensaverClockVisible READ screensaverClockVisible WRITE setScreensaverClockVisible NOTIFY settingsChanged)
    Q_PROPERTY(int screensaverFps READ screensaverFps WRITE setScreensaverFps NOTIFY settingsChanged)
    Q_PROPERTY(bool requirePassword READ requirePassword WRITE setRequirePassword NOTIFY securityChanged)
    Q_PROPERTY(int requirePasswordDelay READ requirePasswordDelay WRITE setRequirePasswordDelay NOTIFY securityChanged)
    Q_PROPERTY(bool kickassArmed READ kickassArmed WRITE setKickassArmed NOTIFY securityChanged)
    Q_PROPERTY(QString hourFormat READ hourFormat WRITE setHourFormat NOTIFY settingsChanged)
    Q_PROPERTY(bool showSeconds READ showSeconds WRITE setShowSeconds NOTIFY settingsChanged)
    Q_PROPERTY(bool ntpEnabled READ ntpEnabled WRITE setNtpEnabled NOTIFY settingsChanged)
    Q_PROPERTY(QString timezoneManual READ timezoneManual WRITE setTimezoneManual NOTIFY settingsChanged)
    Q_PROPERTY(bool proxyEnabled READ proxyEnabled WRITE setProxyEnabled NOTIFY settingsChanged)
    Q_PROPERTY(QString proxyHost READ proxyHost WRITE setProxyHost NOTIFY settingsChanged)
    Q_PROPERTY(int proxyPort READ proxyPort WRITE setProxyPort NOTIFY settingsChanged)
    Q_PROPERTY(int dockIconSize READ dockIconSize WRITE setDockIconSize NOTIFY dockChanged)
    Q_PROPERTY(int dockSpacing READ dockSpacing WRITE setDockSpacing NOTIFY dockChanged)
    Q_PROPERTY(double dockZoomPercent READ dockZoomPercent WRITE setDockZoomPercent NOTIFY dockChanged)
    Q_PROPERTY(int dockZoomRange READ dockZoomRange WRITE setDockZoomRange NOTIFY dockChanged)
    Q_PROPERTY(int dockAnimSpeed READ dockAnimSpeed WRITE setDockAnimSpeed NOTIFY dockChanged)
    Q_PROPERTY(double dockMagSpring READ dockMagSpring WRITE setDockMagSpring NOTIFY dockChanged)
    Q_PROPERTY(double dockMagDamping READ dockMagDamping WRITE setDockMagDamping NOTIFY dockChanged)
    Q_PROPERTY(double dockMagMass READ dockMagMass WRITE setDockMagMass NOTIFY dockChanged)
    Q_PROPERTY(QVariantList dockApps READ dockApps NOTIFY dockChanged)
    Q_PROPERTY(QString assetBase READ assetBase CONSTANT)
    Q_PROPERTY(QString configBase READ configBase CONSTANT)
    Q_PROPERTY(QString systemLanguage READ systemLanguage WRITE setSystemLanguage NOTIFY localeChanged)
    Q_PROPERTY(QString systemLocale READ systemLocale WRITE setSystemLocale NOTIFY localeChanged)
    Q_PROPERTY(QStringList kbLayouts READ kbLayouts NOTIFY localeChanged)
    Q_PROPERTY(QString activeKbLayout READ activeKbLayout WRITE setActiveKbLayout NOTIFY localeChanged)
    Q_PROPERTY(QString defaultBrowser READ defaultBrowser WRITE setDefaultBrowser NOTIFY sessionChanged)
    Q_PROPERTY(QString defaultMail READ defaultMail WRITE setDefaultMail NOTIFY sessionChanged)
    Q_PROPERTY(QString defaultFiles READ defaultFiles WRITE setDefaultFiles NOTIFY sessionChanged)
    Q_PROPERTY(QString defaultTerminal READ defaultTerminal WRITE setDefaultTerminal NOTIFY sessionChanged)
    Q_PROPERTY(bool dnd READ dnd WRITE setDnd NOTIFY notifsChanged)
    Q_PROPERTY(int notifPosition READ notifPosition WRITE setNotifPosition NOTIFY notifsChanged)
    Q_PROPERTY(bool quietHoursOn READ quietHoursOn WRITE setQuietHoursOn NOTIFY notifsChanged)
    Q_PROPERTY(QString quietFrom READ quietFrom WRITE setQuietFrom NOTIFY notifsChanged)
    Q_PROPERTY(QString quietTo READ quietTo WRITE setQuietTo NOTIFY notifsChanged)
    Q_PROPERTY(QString userName READ userName CONSTANT)
    Q_PROPERTY(QStringList customWallpapers READ customWallpapers NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(bool slideshowEnabled READ slideshowEnabled WRITE setSlideshowEnabled NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(int slideshowInterval READ slideshowInterval WRITE setSlideshowInterval NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(QString fitMode READ fitMode WRITE setFitMode NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(int outputVolume READ outputVolume WRITE setOutputVolume NOTIFY soundChanged)
    Q_PROPERTY(int inputVolume READ inputVolume WRITE setInputVolume NOTIFY soundChanged)
    Q_PROPERTY(QString outputDevice READ outputDevice WRITE setOutputDevice NOTIFY soundChanged)
    Q_PROPERTY(QString inputDevice READ inputDevice WRITE setInputDevice NOTIFY soundChanged)
    Q_PROPERTY(double inputLevel READ inputLevel WRITE setInputLevel NOTIFY soundChanged)

public:
    QVariantList displays() const;
    bool nightLightOn() const;
    void setNightLightOn(bool v);
    int nightWarmth() const;
    void setNightWarmth(int v);
    bool nightLightAuto() const;
    void setNightLightAuto(bool v);
    int batBlank() const;
    void setBatBlank(int v);
    int batSuspend() const;
    void setBatSuspend(int v);
    int acBlank() const;
    void setAcBlank(int v);
    int acSuspend() const;
    void setAcSuspend(int v);
    QString lidAction() const;
    void setLidAction(const QString &v);
    QString powerButtonAction() const;
    void setPowerButtonAction(const QString &v);
    bool showBatteryPct() const;
    void setShowBatteryPct(bool v);
    QString fontFamily() const;
    void setFontFamily(const QString &v);
    QString dockHoverTextColor() const;
    void setDockHoverTextColor(const QString &v);
    QString topPanelTextColor() const;
    void setTopPanelTextColor(const QString &v);
    QString gliaTextColor() const;
    void setGliaTextColor(const QString &v);
    QString leapFrogTextColor() const;
    void setLeapFrogTextColor(const QString &v);
    QString accentOverride() const;
    void setAccentOverride(const QString &v);
    QString accentMutedOverride() const;
    void setAccentMutedOverride(const QString &v);
    QString glowOverride() const;
    void setGlowOverride(const QString &v);
    QString borderOverride() const;
    void setBorderOverride(const QString &v);
    bool slideshowPaused() const;
    int fontWeight() const;
    void setFontWeight(int v);
    bool fontItalic() const;
    void setFontItalic(bool v);
    double fontSizeScale() const;
    void setFontSizeScale(double v);
    double letterSpacing() const;
    void setLetterSpacing(double v);
    double lineHeight() const;
    void setLineHeight(double v);
    double uiScale() const;
    void setUiScale(double v);
    QString textColor() const;
    void setTextColor(const QString &v);
    bool textOutlineEnabled() const;
    void setTextOutlineEnabled(bool v);
    QString textOutlineColor() const;
    void setTextOutlineColor(const QString &v);
    double textOutlineWidth() const;
    void setTextOutlineWidth(double v);
    bool textShadowEnabled() const;
    void setTextShadowEnabled(bool v);
    QString textShadowColor() const;
    void setTextShadowColor(const QString &v);
    double textShadowOffsetX() const;
    void setTextShadowOffsetX(double v);
    double textShadowOffsetY() const;
    void setTextShadowOffsetY(double v);
    double textShadowRadius() const;
    void setTextShadowRadius(double v);
    bool autoMountUsb() const;
    void setAutoMountUsb(bool v);
    int kbRepeatDelay() const;
    void setKbRepeatDelay(int v);
    int kbRepeatRate() const;
    void setKbRepeatRate(int v);
    int pointerSpeed() const;
    void setPointerSpeed(int v);
    int touchpadSpeed() const;
    void setTouchpadSpeed(int v);
    bool naturalScroll() const;
    void setNaturalScroll(bool v);
    bool tapToClick() const;
    void setTapToClick(bool v);
    bool disableWhileTyping() const;
    void setDisableWhileTyping(bool v);
    int cursorSize() const;
    void setCursorSize(int v);
    double accessibilityTextScale() const;
    void setAccessibilityTextScale(double v);
    bool highContrast() const;
    void setHighContrast(bool v);
    bool reduceMotion() const;
    void setReduceMotion(bool v);
    bool largerCursor() const;
    void setLargerCursor(bool v);
    bool locationEnabled() const;
    void setLocationEnabled(bool v);
    bool lockScreenNotifPreview() const;
    void setLockScreenNotifPreview(bool v);
    int screensaverTimeout() const;
    void setScreensaverTimeout(int v);
    QString screensaverSeason() const;
    void setScreensaverSeason(const QString &v);
    bool screensaverClockVisible() const;
    void setScreensaverClockVisible(bool v);
    int screensaverFps() const;
    void setScreensaverFps(int v);
    bool requirePassword() const;
    void setRequirePassword(bool v);
    int requirePasswordDelay() const;
    void setRequirePasswordDelay(int v);
    bool kickassArmed() const;
    QString hourFormat() const;
    void setHourFormat(const QString &v);
    bool showSeconds() const;
    void setShowSeconds(bool v);
    bool ntpEnabled() const;
    void setNtpEnabled(bool v);
    QString timezoneManual() const;
    void setTimezoneManual(const QString &v);
    bool proxyEnabled() const;
    void setProxyEnabled(bool v);
    QString proxyHost() const;
    void setProxyHost(const QString &v);
    int proxyPort() const;
    void setProxyPort(int v);
    int dockIconSize() const;
    void setDockIconSize(int v);
    int dockSpacing() const;
    void setDockSpacing(int v);
    double dockZoomPercent() const;
    void setDockZoomPercent(double v);
    int dockZoomRange() const;
    void setDockZoomRange(int v);
    int dockAnimSpeed() const;
    void setDockAnimSpeed(int v);
    double dockMagSpring() const;
    void setDockMagSpring(double v);
    double dockMagDamping() const;
    void setDockMagDamping(double v);
    double dockMagMass() const;
    void setDockMagMass(double v);
    QVariantList dockApps() const;
    QString assetBase() const;
    QString configBase() const;
    QString systemLanguage() const;
    void setSystemLanguage(const QString &v);
    QString systemLocale() const;
    void setSystemLocale(const QString &v);
    QStringList kbLayouts() const;
    QString activeKbLayout() const;
    QString defaultBrowser() const;
    void setDefaultBrowser(const QString &v);
    QString defaultMail() const;
    void setDefaultMail(const QString &v);
    QString defaultFiles() const;
    void setDefaultFiles(const QString &v);
    QString defaultTerminal() const;
    void setDefaultTerminal(const QString &v);
    bool dnd() const;
    void setDnd(bool v);
    int notifPosition() const;
    void setNotifPosition(int v);
    bool quietHoursOn() const;
    void setQuietHoursOn(bool v);
    QString quietFrom() const;
    void setQuietFrom(const QString &v);
    QString quietTo() const;
    void setQuietTo(const QString &v);
    QString userName() const;
    QStringList customWallpapers() const;
    bool slideshowEnabled() const;
    int slideshowInterval() const;
    QString fitMode() const;
    int outputVolume() const;
    void setOutputVolume(int v);
    int inputVolume() const;
    void setInputVolume(int v);
    QString outputDevice() const;
    void setOutputDevice(const QString &v);
    QString inputDevice() const;
    void setInputDevice(const QString &v);
    double inputLevel() const;
    void setInputLevel(double v);

    Q_INVOKABLE void saveSurfaceGlass(const QString &key, const QColor &tint, double shine, double glow, const QColor &border, const QColor &glowColor);
    Q_INVOKABLE void saveWidgetStyleMap(const QString &key, const QVariantMap &map);
    Q_INVOKABLE void resetWidgetStyle(const QString &key);
    Q_INVOKABLE void saveColorOverrides();
    Q_INVOKABLE void saveSectionColors();
    Q_INVOKABLE void saveFiligreepalette(const QString &name, double hue, double sat, const QVariantList &palette);
    Q_INVOKABLE void setSlideshowPaused(bool p);
    Q_INVOKABLE void saveDateTime();
    Q_INVOKABLE void saveNetwork();
    Q_INVOKABLE void saveScreensaver();
    Q_INVOKABLE void loadScreensaver();
    Q_INVOKABLE void previewScreensaver(const QString &season);
    Q_INVOKABLE void previewScreensaver();
    Q_INVOKABLE bool screensaverRunning();
    Q_INVOKABLE void savePrivacy();
    Q_INVOKABLE void saveSecurity();
    Q_INVOKABLE void saveConfig();
    Q_INVOKABLE void setKickassArmed(bool a);
    Q_INVOKABLE void loadKickass();
    Q_INVOKABLE void initWatcher();

signals:
    void displaysChanged();
    void settingsChanged();
    void dockPrefsChanged();
    void wallpaperChanged(const QString &path);
    void slideshowAdvanced(const QString &path);
    void powerChanged();
    void fontChanged();
    void storageChanged();
    void inputChanged();
    void accessibilityChanged();
    void privacyChanged();
    void securityChanged();
    void dockChanged();
    void localeChanged();
    void sessionChanged();
    void notifsChanged();
    void wallpaperPrefsChanged();
    void soundChanged();
    void screensaverFinished(int exitCode, bool crashed);

public slots:
    void onScreenIdleChanged();
    void refreshDisplays();
    void applyDisplayMode(const QString &name, const QString &mode, double hz);
    void applyDisplayOrientation(const QString &name, const QString &orient);
    void applyDisplayScale(const QString &name, int pct);
    void saveDisplay();
    void loadDisplay();
    void loadPower();
    void applyPowerSettings();
    void savePower();
    void applyFontSettings();
    void saveFontSettings();
    void saveTextColor();
    void loadStorage();
    void saveStorage();
    void loadFonts();
    void loadInput();
    void saveInput();
    void loadAccessibility();
    void saveAccessibility();
    void loadPrivacy();
    void saveConfPrivacy();
    void loadDock();
    void setDockApps(const QVariantList &apps);
    void saveDockPrefs();
    QVariantList installedApps();
    void loadLocale();
    void saveLocale();
    void setActiveKbLayout(const QString &code);
    void addKbLayout(const QString &code);
    void removeKbLayout(const QString &code);
    void loadDefaults();
    void saveDefaults();
    QString loadAutostart();
    void saveAutostart(const QString &json);
    void loadNotifications();
    void saveNotifications();
    QString getWallpaper();
    void setWallpaper(const QString &path);
    void loadWallpaperPrefs();
    void saveWallpaperPrefs();
    void setSlideshowEnabled(bool v);
    void setSlideshowInterval(int v);
    void setFitMode(const QString &v);
    void loadSound();
    void saveSound();
// ---- END GENERATED ----

public:
    // ---- additions beyond the oracle (declared in tests/iface_additions/Settings.txt) ----
    // Settings > Display: a mode / rate / rotation / scale change reverts after 15 s unless kept (D2)
    Q_INVOKABLE void confirmDisplayChange();
    Q_INVOKABLE void revertDisplayChange();
signals:
    void displayChangePending(int seconds);          // 0 = nothing pending (kept or reverted)

public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings() override;
    void setLelan(Lelan *lelan);
    void setAnimPolicy(QObject *policy);

    // ---- idle (Settings_power.cpp; IdlePolicy.h) ----
    // The window manager's X idle sample (NCDEWindowManager::pollUserIdle, every 2 s). main() connects it.
    void onIdleSample(qint64 idleMs);
    // what Settings runs for an idle action; tests replace it (never suspends / locks for real there)
    std::function<void(const QString &program, const QStringList &args)> runDetached;
    // a read-only query whose output Settings parses (xinput list, ...), asynchronous
    std::function<void(const QString &program, const QStringList &args, std::function<void(const QString &out)> done)> runQuery;
    // a program fed `input` on stdin (xrdb -merge)
    std::function<void(const QString &program, const QStringList &args, const QByteArray &input)> runInput;
    // X idle ms right now (the WM's xcb query) — lets a crashed screensaver tell "nobody is back" (I4)
    std::function<qint64()> idleMsSource;
    QString saverProgram = QStringLiteral("ncde-portal");   // the screensaver (tests use a stand-in)

private:
    // ---- oracle helpers that are not in the meta-object (declared as the decompile names them) ----
    void applyNightLight();
    void applyLibinput(const QString &device, const QString &prop);
    void applyLibinputFiltered(const QString &device, const QString &prop, bool touchpad);
    void applyInput();
    void applyAccessibility();
    void applyKbLayout();
    void syncAutostartDesktops(const QJsonArray &entries);
    void saveFontsJson();
    void applyKickassArmed();
    void loadDateTime();
    void loadNetwork();
    void loadSectionColors();

    // ---- input, cursor, storage switch (Settings_input.cpp) ----
    static QList<QPair<QString, QString>> parsePointers(const QString &xinputList);
    static void setIniKeys(const QString &path, const QList<QPair<QString, QString>> &kv);
    void applyCursorSize();

    // ---- core (Settings_core.cpp): tracked config IO + hot reload (K1) ----
    QVariantMap readArea(const QString &name);
    bool writeArea(const QString &name, const QVariantMap &data);
    void watchConfigFiles();
    void reloadChangedAreas();
    QHash<QString, QByteArray> m_seen;       // area -> file content Settings last read or wrote
    QTimer *m_reloadTimer = nullptr;
    bool m_watcherStarted = false;

    // ---- prefs: default apps, slideshow (Settings_prefs.cpp) ----
    static QString desktopFileFor(const QString &app);
    void applyDefaults();
    void updateSlideshowTimer();
    void advanceSlideshow();
    QStringList slideshowPictures(const QString &current) const;
    void writeWallpaper(const QString &path, bool userChoice);
    QTimer *m_slideshowTimer = nullptr;
    qint64 m_slideshowDue = 0;               // when the next slideshow step is due (ms since epoch), 0 = not counting
    qint64 m_slideshowRemainingMs = -1;      // saved while idle; -1 means no paused countdown
public:
    qint64 slideshowMinuteMs = 60000;        // one slideshow "minute" (tests shorten it)
private:

    // ---- proxy (Settings_misc.cpp) ----
    void applyProxy();

    // ---- display + night light (Settings_display.cpp) ----
    static QVariantList parseXrandr(const QString &text, const QMap<QString, QVariant> &scales);
    static QVector<double> nightGains(int kelvin);
    void followDayNight();
    void changeDisplay(const QString &name, const QStringList &args, const QStringList &revertArgs);
    QVariantMap displayByName(const QString &name) const;
    QMap<QString, QVariant> m_scales;        // output -> scale percent (oracle +0x30)
    QStringList m_displayRevert;             // xrandr args that restore the state before a change
    int m_displayRevertScale = 100;
    QTimer *m_displayRevertTimer = nullptr;

    // ---- power / idle / screensaver / security (Settings_power.cpp) ----
    void applyIdleConfig();
    void startSaver();
    void stopSaver();
    void onSaverFinished(int exitCode, bool crashed);
    void loadSecurity();
    IdlePolicy m_idle;
    QProcess *m_saver = nullptr;             // ncde-portal --screensaver
    bool m_saverStopping = false;
    int m_appliedBlank = -1;                 // what xset dpms was last given (seconds), -1 = never
    Lelan *m_lelan = nullptr;
    QObject *m_animPolicy = nullptr;
    QString m_configBase;

    // ---- property fields (oracle names without offsets) ----
    QVariantList m_displays;
    bool m_nightLightOn = false;
    int m_nightWarmth = 4000;
    bool m_nightLightAuto = false;
    int m_batBlank = 10;
    int m_batSuspend = 20;
    int m_acBlank = 15;
    int m_acSuspend = 0;
    QString m_lidAction = QStringLiteral("suspend");
    QString m_powerButtonAction = QStringLiteral("poweroff");
    bool m_showBatteryPct = true;
    QString m_fontFamily = QStringLiteral("Cormorant Garamond");
    QString m_dockHoverTextColor;
    QString m_topPanelTextColor;
    QString m_gliaTextColor;
    QString m_leapFrogTextColor;
    QString m_accentOverride;
    QString m_accentMutedOverride;
    QString m_glowOverride;
    QString m_borderOverride;
    bool m_slideshowPaused = false;
    int m_fontWeight = 400;
    bool m_fontItalic = false;
    double m_fontSizeScale = 1.0;
    double m_letterSpacing = 0.0;
    double m_lineHeight = 1.0;
    double m_uiScale = 1.0;
    QString m_textColor;
    bool m_textOutlineEnabled = false;
    QString m_textOutlineColor;
    double m_textOutlineWidth = 0.0;
    bool m_textShadowEnabled = false;
    QString m_textShadowColor;
    double m_textShadowOffsetX = 0.0;
    double m_textShadowOffsetY = 0.0;
    double m_textShadowRadius = 0.0;
    bool m_autoMountUsb = false;
    int m_kbRepeatDelay = 300;
    int m_kbRepeatRate = 30;
    int m_pointerSpeed = 50;
    int m_touchpadSpeed = 50;
    bool m_naturalScroll = true;
    bool m_tapToClick = true;
    bool m_disableWhileTyping = true;
    int m_cursorSize = 32;
    double m_accessibilityTextScale = 1.0;
    bool m_highContrast = false;
    bool m_reduceMotion = false;
    bool m_largerCursor = false;
    bool m_locationEnabled = true;
    bool m_lockScreenNotifPreview = true;
    int m_screensaverTimeout = 5;                 // P4: minutes (ScreensaverTab 1-60, default 5); oracle 300
    QString m_screensaverSeason = QStringLiteral("auto");
    bool m_screensaverClockVisible = true;
    int m_screensaverFps = 30;
    bool m_requirePassword = true;
    int m_requirePasswordDelay = 0;
    bool m_kickassArmed = true;
    QString m_hourFormat = QStringLiteral("auto");
    bool m_showSeconds = false;
    bool m_ntpEnabled = true;
    QString m_timezoneManual;
    bool m_proxyEnabled = false;
    QString m_proxyHost;
    int m_proxyPort = 8080;
    int m_dockIconSize = 48;
    int m_dockSpacing = 1;
    double m_dockZoomPercent = 1.1;
    int m_dockZoomRange = 59;
    int m_dockAnimSpeed = 80;
    double m_dockMagSpring = 2.0;
    double m_dockMagDamping = 0.15;
    double m_dockMagMass = 0.4;
    QVariantList m_dockApps;
    QString m_assetBase = QStringLiteral("/usr/share/ncde/");
    QString m_systemLanguage = QStringLiteral("en_US.UTF-8");
    QString m_systemLocale = QStringLiteral("en_US.UTF-8");
    QStringList m_kbLayouts{QStringLiteral("us")};
    QString m_activeKbLayout = QStringLiteral("us");
    QString m_defaultBrowser = QStringLiteral("chromium");
    QString m_defaultMail = QStringLiteral("hummingbird-courier");
    QString m_defaultFiles = QStringLiteral("orchidee");
    QString m_defaultTerminal = QStringLiteral("ncde-terminal");
    bool m_dnd = false;
    int m_notifPosition = 1;
    bool m_quietHoursOn = true;
    QString m_quietFrom = QStringLiteral("10:00 PM");
    QString m_quietTo = QStringLiteral("7:00 AM");
    QStringList m_customWallpapers;
    bool m_slideshowEnabled = false;
    int m_slideshowInterval = 5;
    QString m_fitMode = QStringLiteral("fill");
    int m_outputVolume = 100;
    int m_inputVolume = 80;
    QString m_outputDevice;
    QString m_inputDevice;
    double m_inputLevel = 0.0;

    QFileSystemWatcher m_watcher;
};
