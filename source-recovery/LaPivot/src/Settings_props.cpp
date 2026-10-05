// Settings — the plain properties: getter + change-checked setter that emits the NOTIFY signal, exactly as the
// oracle's qt_static_metacall WriteProperty does (generated from the oracle metadata, see tests/iface_check.sh).
// Properties with side effects are written by hand in their area file (Settings_<area>.cpp).
#include "Settings.h"

QString Settings::fontFamily() const { return m_fontFamily; }
void Settings::setFontFamily(const QString & v)
{
    if (v == m_fontFamily)
        return;
    m_fontFamily = v;
    emit fontChanged();
}
QString Settings::dockHoverTextColor() const { return m_dockHoverTextColor; }
void Settings::setDockHoverTextColor(const QString & v)
{
    if (v == m_dockHoverTextColor)
        return;
    m_dockHoverTextColor = v;
    emit settingsChanged();
}
QString Settings::topPanelTextColor() const { return m_topPanelTextColor; }
void Settings::setTopPanelTextColor(const QString & v)
{
    if (v == m_topPanelTextColor)
        return;
    m_topPanelTextColor = v;
    emit settingsChanged();
}
QString Settings::gliaTextColor() const { return m_gliaTextColor; }
void Settings::setGliaTextColor(const QString & v)
{
    if (v == m_gliaTextColor)
        return;
    m_gliaTextColor = v;
    emit settingsChanged();
}
QString Settings::leapFrogTextColor() const { return m_leapFrogTextColor; }
void Settings::setLeapFrogTextColor(const QString & v)
{
    if (v == m_leapFrogTextColor)
        return;
    m_leapFrogTextColor = v;
    emit settingsChanged();
}
QString Settings::accentOverride() const { return m_accentOverride; }
void Settings::setAccentOverride(const QString & v)
{
    if (v == m_accentOverride)
        return;
    m_accentOverride = v;
    emit settingsChanged();
}
QString Settings::accentMutedOverride() const { return m_accentMutedOverride; }
void Settings::setAccentMutedOverride(const QString & v)
{
    if (v == m_accentMutedOverride)
        return;
    m_accentMutedOverride = v;
    emit settingsChanged();
}
QString Settings::glowOverride() const { return m_glowOverride; }
void Settings::setGlowOverride(const QString & v)
{
    if (v == m_glowOverride)
        return;
    m_glowOverride = v;
    emit settingsChanged();
}
QString Settings::borderOverride() const { return m_borderOverride; }
void Settings::setBorderOverride(const QString & v)
{
    if (v == m_borderOverride)
        return;
    m_borderOverride = v;
    emit settingsChanged();
}
int Settings::fontWeight() const { return m_fontWeight; }
void Settings::setFontWeight(int v)
{
    if (v == m_fontWeight)
        return;
    m_fontWeight = v;
    emit fontChanged();
}
bool Settings::fontItalic() const { return m_fontItalic; }
void Settings::setFontItalic(bool v)
{
    if (v == m_fontItalic)
        return;
    m_fontItalic = v;
    emit fontChanged();
}
double Settings::fontSizeScale() const { return m_fontSizeScale; }
void Settings::setFontSizeScale(double v)
{
    if (v == m_fontSizeScale)
        return;
    m_fontSizeScale = v;
    emit fontChanged();
}
double Settings::letterSpacing() const { return m_letterSpacing; }
void Settings::setLetterSpacing(double v)
{
    if (v == m_letterSpacing)
        return;
    m_letterSpacing = v;
    emit fontChanged();
}
double Settings::lineHeight() const { return m_lineHeight; }
void Settings::setLineHeight(double v)
{
    if (v == m_lineHeight)
        return;
    m_lineHeight = v;
    emit fontChanged();
}
double Settings::uiScale() const { return m_uiScale; }
void Settings::setUiScale(double v)
{
    if (v == m_uiScale)
        return;
    m_uiScale = v;
    emit fontChanged();
}
QString Settings::textColor() const { return m_textColor; }
void Settings::setTextColor(const QString & v)
{
    if (v == m_textColor)
        return;
    m_textColor = v;
    emit fontChanged();
}
bool Settings::textOutlineEnabled() const { return m_textOutlineEnabled; }
void Settings::setTextOutlineEnabled(bool v)
{
    if (v == m_textOutlineEnabled)
        return;
    m_textOutlineEnabled = v;
    emit fontChanged();
}
QString Settings::textOutlineColor() const { return m_textOutlineColor; }
void Settings::setTextOutlineColor(const QString & v)
{
    if (v == m_textOutlineColor)
        return;
    m_textOutlineColor = v;
    emit fontChanged();
}
double Settings::textOutlineWidth() const { return m_textOutlineWidth; }
void Settings::setTextOutlineWidth(double v)
{
    if (v == m_textOutlineWidth)
        return;
    m_textOutlineWidth = v;
    emit fontChanged();
}
bool Settings::textShadowEnabled() const { return m_textShadowEnabled; }
void Settings::setTextShadowEnabled(bool v)
{
    if (v == m_textShadowEnabled)
        return;
    m_textShadowEnabled = v;
    emit fontChanged();
}
QString Settings::textShadowColor() const { return m_textShadowColor; }
void Settings::setTextShadowColor(const QString & v)
{
    if (v == m_textShadowColor)
        return;
    m_textShadowColor = v;
    emit fontChanged();
}
double Settings::textShadowOffsetX() const { return m_textShadowOffsetX; }
void Settings::setTextShadowOffsetX(double v)
{
    if (v == m_textShadowOffsetX)
        return;
    m_textShadowOffsetX = v;
    emit fontChanged();
}
double Settings::textShadowOffsetY() const { return m_textShadowOffsetY; }
void Settings::setTextShadowOffsetY(double v)
{
    if (v == m_textShadowOffsetY)
        return;
    m_textShadowOffsetY = v;
    emit fontChanged();
}
double Settings::textShadowRadius() const { return m_textShadowRadius; }
void Settings::setTextShadowRadius(double v)
{
    if (v == m_textShadowRadius)
        return;
    m_textShadowRadius = v;
    emit fontChanged();
}
int Settings::kbRepeatDelay() const { return m_kbRepeatDelay; }
void Settings::setKbRepeatDelay(int v)
{
    if (v == m_kbRepeatDelay)
        return;
    m_kbRepeatDelay = v;
    emit inputChanged();
}
int Settings::kbRepeatRate() const { return m_kbRepeatRate; }
void Settings::setKbRepeatRate(int v)
{
    if (v == m_kbRepeatRate)
        return;
    m_kbRepeatRate = v;
    emit inputChanged();
}
int Settings::pointerSpeed() const { return m_pointerSpeed; }
void Settings::setPointerSpeed(int v)
{
    if (v == m_pointerSpeed)
        return;
    m_pointerSpeed = v;
    emit inputChanged();
}
int Settings::touchpadSpeed() const { return m_touchpadSpeed; }
void Settings::setTouchpadSpeed(int v)
{
    if (v == m_touchpadSpeed)
        return;
    m_touchpadSpeed = v;
    emit inputChanged();
}
bool Settings::naturalScroll() const { return m_naturalScroll; }
void Settings::setNaturalScroll(bool v)
{
    if (v == m_naturalScroll)
        return;
    m_naturalScroll = v;
    emit inputChanged();
}
bool Settings::tapToClick() const { return m_tapToClick; }
void Settings::setTapToClick(bool v)
{
    if (v == m_tapToClick)
        return;
    m_tapToClick = v;
    emit inputChanged();
}
bool Settings::disableWhileTyping() const { return m_disableWhileTyping; }
void Settings::setDisableWhileTyping(bool v)
{
    if (v == m_disableWhileTyping)
        return;
    m_disableWhileTyping = v;
    emit inputChanged();
}
int Settings::cursorSize() const { return m_cursorSize; }
void Settings::setCursorSize(int v)
{
    if (v == m_cursorSize)
        return;
    m_cursorSize = v;
    emit inputChanged();
}
double Settings::accessibilityTextScale() const { return m_accessibilityTextScale; }
void Settings::setAccessibilityTextScale(double v)
{
    if (v == m_accessibilityTextScale)
        return;
    m_accessibilityTextScale = v;
    emit accessibilityChanged();
}
bool Settings::highContrast() const { return m_highContrast; }
void Settings::setHighContrast(bool v)
{
    if (v == m_highContrast)
        return;
    m_highContrast = v;
    emit accessibilityChanged();
}
bool Settings::reduceMotion() const { return m_reduceMotion; }
void Settings::setReduceMotion(bool v)
{
    if (v == m_reduceMotion)
        return;
    m_reduceMotion = v;
    emit accessibilityChanged();
}
bool Settings::largerCursor() const { return m_largerCursor; }
void Settings::setLargerCursor(bool v)
{
    if (v == m_largerCursor)
        return;
    m_largerCursor = v;
    emit accessibilityChanged();
}
bool Settings::locationEnabled() const { return m_locationEnabled; }
void Settings::setLocationEnabled(bool v)
{
    if (v == m_locationEnabled)
        return;
    m_locationEnabled = v;
    emit privacyChanged();
}
bool Settings::lockScreenNotifPreview() const { return m_lockScreenNotifPreview; }
void Settings::setLockScreenNotifPreview(bool v)
{
    if (v == m_lockScreenNotifPreview)
        return;
    m_lockScreenNotifPreview = v;
    emit privacyChanged();
}
QString Settings::hourFormat() const { return m_hourFormat; }
void Settings::setHourFormat(const QString & v)
{
    if (v == m_hourFormat)
        return;
    m_hourFormat = v;
    emit settingsChanged();
}
bool Settings::showSeconds() const { return m_showSeconds; }
void Settings::setShowSeconds(bool v)
{
    if (v == m_showSeconds)
        return;
    m_showSeconds = v;
    emit settingsChanged();
}
bool Settings::ntpEnabled() const { return m_ntpEnabled; }
void Settings::setNtpEnabled(bool v)
{
    if (v == m_ntpEnabled)
        return;
    m_ntpEnabled = v;
    emit settingsChanged();
}
QString Settings::timezoneManual() const { return m_timezoneManual; }
void Settings::setTimezoneManual(const QString & v)
{
    if (v == m_timezoneManual)
        return;
    m_timezoneManual = v;
    emit settingsChanged();
}
bool Settings::proxyEnabled() const { return m_proxyEnabled; }
void Settings::setProxyEnabled(bool v)
{
    if (v == m_proxyEnabled)
        return;
    m_proxyEnabled = v;
    emit settingsChanged();
}
QString Settings::proxyHost() const { return m_proxyHost; }
void Settings::setProxyHost(const QString & v)
{
    if (v == m_proxyHost)
        return;
    m_proxyHost = v;
    emit settingsChanged();
}
int Settings::proxyPort() const { return m_proxyPort; }
void Settings::setProxyPort(int v)
{
    if (v == m_proxyPort)
        return;
    m_proxyPort = v;
    emit settingsChanged();
}
int Settings::dockIconSize() const { return m_dockIconSize; }
void Settings::setDockIconSize(int v)
{
    if (v == m_dockIconSize)
        return;
    m_dockIconSize = v;
    emit dockChanged();
}
int Settings::dockSpacing() const { return m_dockSpacing; }
void Settings::setDockSpacing(int v)
{
    if (v == m_dockSpacing)
        return;
    m_dockSpacing = v;
    emit dockChanged();
}
double Settings::dockZoomPercent() const { return m_dockZoomPercent; }
void Settings::setDockZoomPercent(double v)
{
    if (v == m_dockZoomPercent)
        return;
    m_dockZoomPercent = v;
    emit dockChanged();
}
int Settings::dockZoomRange() const { return m_dockZoomRange; }
void Settings::setDockZoomRange(int v)
{
    if (v == m_dockZoomRange)
        return;
    m_dockZoomRange = v;
    emit dockChanged();
}
int Settings::dockAnimSpeed() const { return m_dockAnimSpeed; }
void Settings::setDockAnimSpeed(int v)
{
    if (v == m_dockAnimSpeed)
        return;
    m_dockAnimSpeed = v;
    emit dockChanged();
}
double Settings::dockMagSpring() const { return m_dockMagSpring; }
void Settings::setDockMagSpring(double v)
{
    if (v == m_dockMagSpring)
        return;
    m_dockMagSpring = v;
    emit dockChanged();
}
double Settings::dockMagDamping() const { return m_dockMagDamping; }
void Settings::setDockMagDamping(double v)
{
    if (v == m_dockMagDamping)
        return;
    m_dockMagDamping = v;
    emit dockChanged();
}
double Settings::dockMagMass() const { return m_dockMagMass; }
void Settings::setDockMagMass(double v)
{
    if (v == m_dockMagMass)
        return;
    m_dockMagMass = v;
    emit dockChanged();
}
QString Settings::assetBase() const { return m_assetBase; }
QString Settings::systemLanguage() const { return m_systemLanguage; }
void Settings::setSystemLanguage(const QString & v)
{
    if (v == m_systemLanguage)
        return;
    m_systemLanguage = v;
    emit localeChanged();
}
QString Settings::systemLocale() const { return m_systemLocale; }
void Settings::setSystemLocale(const QString & v)
{
    if (v == m_systemLocale)
        return;
    m_systemLocale = v;
    emit localeChanged();
}
QString Settings::defaultBrowser() const { return m_defaultBrowser; }
void Settings::setDefaultBrowser(const QString & v)
{
    if (v == m_defaultBrowser)
        return;
    m_defaultBrowser = v;
    emit sessionChanged();
}
QString Settings::defaultMail() const { return m_defaultMail; }
void Settings::setDefaultMail(const QString & v)
{
    if (v == m_defaultMail)
        return;
    m_defaultMail = v;
    emit sessionChanged();
}
QString Settings::defaultFiles() const { return m_defaultFiles; }
void Settings::setDefaultFiles(const QString & v)
{
    if (v == m_defaultFiles)
        return;
    m_defaultFiles = v;
    emit sessionChanged();
}
QString Settings::defaultTerminal() const { return m_defaultTerminal; }
void Settings::setDefaultTerminal(const QString & v)
{
    if (v == m_defaultTerminal)
        return;
    m_defaultTerminal = v;
    emit sessionChanged();
}
bool Settings::dnd() const { return m_dnd; }
void Settings::setDnd(bool v)
{
    if (v == m_dnd)
        return;
    m_dnd = v;
    emit notifsChanged();
}
int Settings::notifPosition() const { return m_notifPosition; }
void Settings::setNotifPosition(int v)
{
    if (v == m_notifPosition)
        return;
    m_notifPosition = v;
    emit notifsChanged();
}
bool Settings::quietHoursOn() const { return m_quietHoursOn; }
void Settings::setQuietHoursOn(bool v)
{
    if (v == m_quietHoursOn)
        return;
    m_quietHoursOn = v;
    emit notifsChanged();
}
QString Settings::quietFrom() const { return m_quietFrom; }
void Settings::setQuietFrom(const QString & v)
{
    if (v == m_quietFrom)
        return;
    m_quietFrom = v;
    emit notifsChanged();
}
QString Settings::quietTo() const { return m_quietTo; }
void Settings::setQuietTo(const QString & v)
{
    if (v == m_quietTo)
        return;
    m_quietTo = v;
    emit notifsChanged();
}
int Settings::outputVolume() const { return m_outputVolume; }
void Settings::setOutputVolume(int v)
{
    if (v == m_outputVolume)
        return;
    m_outputVolume = v;
    emit soundChanged();
}
int Settings::inputVolume() const { return m_inputVolume; }
void Settings::setInputVolume(int v)
{
    if (v == m_inputVolume)
        return;
    m_inputVolume = v;
    emit soundChanged();
}
QString Settings::outputDevice() const { return m_outputDevice; }
void Settings::setOutputDevice(const QString & v)
{
    if (v == m_outputDevice)
        return;
    m_outputDevice = v;
    emit soundChanged();
}
QString Settings::inputDevice() const { return m_inputDevice; }
void Settings::setInputDevice(const QString & v)
{
    if (v == m_inputDevice)
        return;
    m_inputDevice = v;
    emit soundChanged();
}
double Settings::inputLevel() const { return m_inputLevel; }
void Settings::setInputLevel(double v)
{
    if (v == m_inputLevel)
        return;
    m_inputLevel = v;
    emit soundChanged();
}
