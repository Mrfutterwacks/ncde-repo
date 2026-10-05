class AnimPolicy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int level READ ? NOTIFY changed)
    Q_PROPERTY(bool reduceMotion READ ? NOTIFY changed)
    Q_PROPERTY(bool idleLoops READ ? NOTIFY changed)
    Q_PROPERTY(bool decorative READ ? NOTIFY changed)
    Q_PROPERTY(bool instant READ ? NOTIFY changed)
    Q_PROPERTY(bool screenIdle READ ? NOTIFY changed)
    Q_PROPERTY(bool thermalPressure READ ? NOTIFY changed)
    Q_PROPERTY(bool lowPower READ ? NOTIFY changed)
    Q_PROPERTY(bool desktopObscured READ ? NOTIFY changed)
    signal:     public void changed();
    signal:     public void policyChanged();
    slot:       public void setLevel(int lvl);
    slot:       public void setReduceMotion(bool on);
    slot:       public void reevaluate();
    slot:       public void setThermalPressure(bool on);
    slot:       public void setDesktopObscured(bool on);
    slot:       public void onScreenSaverActivated(bool active);
    slot:       public void onUserInputIdle(bool idle);
    slot:       public void onVtActiveChanged(bool active);
    slot:       public void onSessionLocked();
    slot:       public void onSessionUnlocked();
    slot:       public void setLowPowerCpu(bool on);
    slot:       public void setLowPowerProfile(bool on);
    slot:       public void setLowPowerMemory(bool on);
    slot:       public void setLowPowerBattery(bool on);
};

class HudManager : public QObject
{
    Q_OBJECT
    signal:     public void hudRequested();
    signal:     public void hudDismissed();
    Q_INVOKABLE public void requestHud();
    Q_INVOKABLE public void dismissHud();
};

class NCDEEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor accent READ ? NOTIFY changed)
    Q_PROPERTY(QColor accentMuted READ ? NOTIFY changed)
    Q_PROPERTY(QColor background READ ? NOTIFY changed)
    Q_PROPERTY(QColor surface READ ? NOTIFY changed)
    Q_PROPERTY(QColor surfaceAlt READ ? NOTIFY changed)
    Q_PROPERTY(QColor surfaceHi READ ? NOTIFY changed)
    Q_PROPERTY(QColor panelBg READ ? NOTIFY changed)
    Q_PROPERTY(QColor panelText READ ? NOTIFY changed)
    Q_PROPERTY(QColor popupBg READ ? NOTIFY changed)
    Q_PROPERTY(QColor border READ ? NOTIFY changed)
    Q_PROPERTY(QColor glow READ ? NOTIFY changed)
    Q_PROPERTY(QColor ink READ ? NOTIFY changed)
    Q_PROPERTY(QColor inkSoft READ ? NOTIFY changed)
    Q_PROPERTY(QColor verd READ ? NOTIFY changed)
    Q_PROPERTY(QColor cer READ ? NOTIFY changed)
    Q_PROPERTY(QColor rose READ ? NOTIFY changed)
    Q_PROPERTY(QColor amber READ ? NOTIFY changed)
    Q_PROPERTY(QColor clockColor READ ? NOTIFY changed)
    Q_PROPERTY(QColor lamp READ ? NOTIFY changed)
    Q_PROPERTY(QColor gilt0 READ ? NOTIFY changed)
    Q_PROPERTY(QColor gilt1 READ ? NOTIFY changed)
    Q_PROPERTY(QColor gilt2 READ ? NOTIFY changed)
    Q_PROPERTY(QColor gilt3 READ ? NOTIFY changed)
    Q_PROPERTY(QColor gilt4 READ ? NOTIFY changed)
    Q_PROPERTY(QColor gilt5 READ ? NOTIFY changed)
    Q_PROPERTY(QColor wine1 READ ? NOTIFY changed)
    Q_PROPERTY(QColor wine2 READ ? NOTIFY changed)
    Q_PROPERTY(QColor wine3 READ ? NOTIFY changed)
    Q_PROPERTY(QColor wine4 READ ? NOTIFY changed)
    Q_PROPERTY(QColor widgetC0 READ ? NOTIFY changed)
    Q_PROPERTY(QColor widgetC1 READ ? NOTIFY changed)
    Q_PROPERTY(QColor widgetC2 READ ? NOTIFY changed)
    Q_PROPERTY(QColor widgetC3 READ ? NOTIFY changed)
    Q_PROPERTY(QColor widgetC4 READ ? NOTIFY changed)
    Q_PROPERTY(QColor widgetC5 READ ? NOTIFY changed)
    Q_PROPERTY(QColor foreground READ ? NOTIFY changed)
    Q_PROPERTY(QColor topShadow READ ? NOTIFY changed)
    Q_PROPERTY(QColor bottomShadow READ ? NOTIFY changed)
    Q_PROPERTY(QColor selectColor READ ? NOTIFY changed)
    Q_PROPERTY(QColor activeBg READ ? NOTIFY changed)
    Q_PROPERTY(QColor activeFg READ ? NOTIFY changed)
    Q_PROPERTY(QColor activeTs READ ? NOTIFY changed)
    Q_PROPERTY(QColor activeBs READ ? NOTIFY changed)
    Q_PROPERTY(QColor inactiveBg READ ? NOTIFY changed)
    Q_PROPERTY(QColor inactiveFg READ ? NOTIFY changed)
    Q_PROPERTY(QColor inactiveTs READ ? NOTIFY changed)
    Q_PROPERTY(QColor inactiveBs READ ? NOTIFY changed)
    Q_PROPERTY(bool darkMode READ ? WRITE ? NOTIFY changed)
    Q_PROPERTY(QString activeFiligreePaletteName READ ? NOTIFY filigreePalettesChanged)
    Q_PROPERTY(QVariantMap activeFiligreePalette READ ? NOTIFY filigreePalettesChanged)
    Q_PROPERTY(QVariantMap filigreePalettes READ ? NOTIFY filigreePalettesChanged)
    Q_PROPERTY(bool presetActive READ ? NOTIFY changed)
    Q_PROPERTY(bool usingCustomBase READ ? NOTIFY changed)
    Q_PROPERTY(int fontSize_sm READ ? NOTIFY changed)
    Q_PROPERTY(int fontSize_md READ ? NOTIFY changed)
    Q_PROPERTY(int fontSize_lg READ ? NOTIFY changed)
    Q_PROPERTY(int letterSpacing READ ? NOTIFY changed)
    Q_PROPERTY(double lineHeight READ ? NOTIFY changed)
    Q_PROPERTY(QString themeName READ ? NOTIFY changed)
    Q_PROPERTY(QString accentName READ ? WRITE ? NOTIFY changed)
    Q_PROPERTY(QString darkModeLock READ ? WRITE ? NOTIFY changed)
    Q_PROPERTY(QString overrideAccent READ ? NOTIFY changed)
    Q_PROPERTY(QString overrideAccentMuted READ ? NOTIFY changed)
    Q_PROPERTY(QString overrideBorder READ ? NOTIFY changed)
    Q_PROPERTY(QString overrideGlow READ ? NOTIFY changed)
    Q_PROPERTY(QString bodyFont READ ? NOTIFY changed)
    Q_PROPERTY(QString titleFont READ ? NOTIFY changed)
    Q_PROPERTY(QString monoFont READ ? NOTIFY changed)
    Q_PROPERTY(QString displayFont READ ? NOTIFY changed)
    Q_PROPERTY(QString fellFont READ ? NOTIFY changed)
    Q_PROPERTY(QString garFont READ ? NOTIFY changed)
    Q_PROPERTY(QString version READ ? CONSTANT)
    Q_PROPERTY(bool wifiEnabled READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList wifiNetworks READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantMap activeNetwork READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList vpnConnections READ ? NOTIFY wifiChanged)
    Q_PROPERTY(bool bluetoothEnabled READ ? NOTIFY wifiChanged)
    Q_PROPERTY(bool bluetoothDiscoverable READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList bluetoothDevices READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QString detectedTzName READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString detectedZone READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString detectedRegion READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString detectedOffset READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString localTime READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(bool locating READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QVariantList users READ ? NOTIFY usersChanged)
    Q_PROPERTY(QVariantList printers READ ? NOTIFY printersChanged)
    Q_PROPERTY(QVariantList appStreams READ ? NOTIFY soundChanged)
    signal:     public void changed();
    signal:     public void themeChanged();
    signal:     public void darkModeChanged();
    signal:     public void previewReady(QVariantMap palette);
    signal:     public void wifiChanged();
    signal:     public void dateTimeChanged();
    signal:     public void usersChanged();
    signal:     public void printersChanged();
    signal:     public void soundChanged();
    signal:     public void filigreePalettesChanged();
    slot:       public void setDarkMode(bool d);
    slot:       public void setAccentName(QString n);
    slot:       public void setDarkModeLock(QString lock);
    slot:       public void setBaseColor(QColor base, QColor accent, QColor panelText);
    slot:       public void clearCustomBase();
    Q_INVOKABLE public QVariantList presets();
    Q_INVOKABLE public void applyPreset(QString id);
    Q_INVOKABLE public QVariantMap currentBasePalette();
    Q_INVOKABLE public bool sampleWallpaper(QString path);
    Q_INVOKABLE public QVariantMap previewWallpaper(QString path);
    Q_INVOKABLE public void previewWallpaperAsync(QString path);
    Q_INVOKABLE public void setSurfaceGlass(QString key, QColor tint, double shine, double glow, QColor border, QColor glowColor);
    Q_INVOKABLE public QVariantMap surfaceGlass(QString key);
    Q_INVOKABLE public void setWidgetStyleMap(QString key, QVariantMap map);
    Q_INVOKABLE public void setWidgetStyle(QString key, QColor accent, QColor fill, QString font);
    Q_INVOKABLE public QVariantMap widgetStyle(QString key);
    Q_INVOKABLE public void resetWidgetStyle(QString key);
    Q_INVOKABLE public void setOverrideAccent(QString hex);
    Q_INVOKABLE public void setOverrideAccentMuted(QString hex);
    Q_INVOKABLE public void setOverrideBorder(QString hex);
    Q_INVOKABLE public void setOverrideGlow(QString hex);
    Q_INVOKABLE public void setBodyFont(QString f);
    Q_INVOKABLE public void setTitleFont(QString f);
    Q_INVOKABLE public void setMonoFont(QString f);
    Q_INVOKABLE public void setDisplayFont(QString f);
    Q_INVOKABLE public void setFellFont(QString f);
    Q_INVOKABLE public void setGarFont(QString f);
    Q_INVOKABLE public void setUiScale(double s);
    Q_INVOKABLE public void setFontSizeScale(double s);
    Q_INVOKABLE public void setLetterSpacing(double v);
    Q_INVOKABLE public void setLineHeight(double v);
    Q_INVOKABLE public void recomputeFontSizes();
    Q_INVOKABLE public QVariantMap toJson();
    Q_INVOKABLE public bool saveTheme(QString path);
    Q_INVOKABLE public bool loadTheme(QString path);
    Q_INVOKABLE public void setTerminalFont(QString font);
    Q_INVOKABLE public void setTerminalGlassTint(double tint);
    Q_INVOKABLE public QVariantMap terminalConfig();
    Q_INVOKABLE public bool saveFiligreepalette(QString name, QVariantMap colors);
    Q_INVOKABLE public bool deleteFiligreepalette(QString name);
    Q_INVOKABLE public bool setActiveFiligreepalette(QString name);
    Q_INVOKABLE public void setWifiEnabled(bool on);
    Q_INVOKABLE public void connectNetwork(QString ssid, QString pwd);
    Q_INVOKABLE public void disconnectNetwork();
    Q_INVOKABLE public void connectVpn(QString name);
    Q_INVOKABLE public void disconnectVpn(QString name);
    Q_INVOKABLE public void setBluetoothEnabled(bool on);
    Q_INVOKABLE public void setBluetoothDiscoverable(bool on);
    Q_INVOKABLE public void bluetoothConnect(QString a);
    Q_INVOKABLE public void bluetoothDisconnect(QString a);
    Q_INVOKABLE public void bluetoothPair(QString a);
    Q_INVOKABLE public void bluetoothRemove(QString a);
    Q_INVOKABLE public void bluetoothScan();
    Q_INVOKABLE public void refreshLocation();
    Q_INVOKABLE public void setTimezone(QString z);
    Q_INVOKABLE public void setNtp(bool on);
    Q_INVOKABLE public void addUser(QString n, QString d, bool a);
    Q_INVOKABLE public void removeUser(QString n);
    Q_INVOKABLE public void setUserAdmin(QString n, bool a);
    Q_INVOKABLE public void changePassword(QString n, QString p);
    Q_INVOKABLE public void setAutoLogin(QString n, bool on);
    Q_INVOKABLE public void setAutoLogin(QString n);
    Q_INVOKABLE public void setUserAvatar(QString n, QString f);
    Q_INVOKABLE public void setDefaultPrinter(QString n);
    Q_INVOKABLE public void removePrinter(QString n);
    Q_INVOKABLE public void setAppVolume(QString name, int vol);
    Q_INVOKABLE public void applyPalette(QVariantMap p);
};

class ScreenInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ ? NOTIFY changed)
    Q_PROPERTY(int height READ ? NOTIFY changed)
    signal:     public void changed();
};

class SniWatcher : public QObject
{
    Q_OBJECT
    signal:     public void itemRegistered(QString service);
    signal:     public void itemUnregistered(QString service);
    signal:     public void hostChanged();
    signal:     public void itemsChanged();
    slot:       private void onOwnerLeft(QString service);
};

class WidgetData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList removableVolumes READ ? NOTIFY changed)
    Q_PROPERTY(int volume READ ? NOTIFY changed)
    Q_PROPERTY(bool muted READ ? NOTIFY changed)
    Q_PROPERTY(bool hasBattery READ ? NOTIFY changed)
    Q_PROPERTY(int batteryLevel READ ? NOTIFY changed)
    Q_PROPERTY(bool batteryCharging READ ? NOTIFY changed)
    Q_PROPERTY(bool networkUp READ ? NOTIFY changed)
    Q_PROPERTY(bool netOnline READ ? NOTIFY changed)
    Q_PROPERTY(QString netUp READ ? NOTIFY statsChanged)
    Q_PROPERTY(QString netDown READ ? NOTIFY statsChanged)
    Q_PROPERTY(bool mediaActive READ ? NOTIFY mediaChanged)
    Q_PROPERTY(bool mediaPlaying READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaTitle READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaArtist READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaAlbum READ ? NOTIFY mediaChanged)
    Q_PROPERTY(double mediaPosition READ ? NOTIFY mediaChanged)
    Q_PROPERTY(double mediaDuration READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString timeHour READ ? NOTIFY clockChanged)
    Q_PROPERTY(QString timeMinute READ ? NOTIFY clockChanged)
    Q_PROPERTY(QString timeAMPM READ ? NOTIFY clockChanged)
    Q_PROPERTY(bool colonOn READ ? NOTIFY clockChanged)
    Q_PROPERTY(QString greeting READ ? NOTIFY clockChanged)
    Q_PROPERTY(QString dateString READ ? NOTIFY clockChanged)
    Q_PROPERTY(double cpuTotal READ ? NOTIFY statsChanged)
    Q_PROPERTY(double ramPercent READ ? NOTIFY statsChanged)
    Q_PROPERTY(double diskPercent READ ? NOTIFY statsChanged)
    Q_PROPERTY(double cpuFreqGHz READ ? NOTIFY statsChanged)
    Q_PROPERTY(double cpuTempF READ ? NOTIFY statsChanged)
    Q_PROPERTY(QString uptime READ ? NOTIFY statsChanged)
    Q_PROPERTY(QVariantList mountedVolumes READ ? NOTIFY statsChanged)
    Q_PROPERTY(QString weatherTemp READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherIcon READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherLocation READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherHigh READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherLow READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherHumidity READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherWind READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherSunrise READ ? NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherSunset READ ? NOTIFY weatherChanged)
    Q_PROPERTY(double moonAzimuth READ ? NOTIFY moonPositionChanged)
    Q_PROPERTY(double moonElevation READ ? NOTIFY moonPositionChanged)
    signal:     public void changed();
    signal:     public void clockChanged();
    signal:     public void statsChanged();
    signal:     public void weatherChanged();
    signal:     public void moonPositionChanged();
    signal:     public void mediaChanged();
    signal:     public void mediaPositionChanged();
    Q_INVOKABLE public void setVolume(int v);
    Q_INVOKABLE public void toggleMute();
    Q_INVOKABLE public void mediaTogglePlay();
    Q_INVOKABLE public void mediaNext();
    Q_INVOKABLE public void mediaPrev();
    Q_INVOKABLE public void mediaSeek(double p);
    Q_INVOKABLE public void mountVolume(QString p);
    Q_INVOKABLE public void unmountVolume(QString p);
};

class FontManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList fonts READ ? NOTIFY fontsChanged)
    Q_PROPERTY(bool busy READ ? NOTIFY statusChanged)
    Q_PROPERTY(QString status READ ? NOTIFY statusChanged)
    Q_PROPERTY(int installedCount READ ? NOTIFY fontsChanged)
    Q_PROPERTY(int total READ ? NOTIFY fontsChanged)
    signal:     public void fontsChanged();
    signal:     public void fontInstalled(QString pkg, QString family);
    signal:     public void statusChanged();
    slot:       private void onResolvePackage(uint, QString packageId, QString);
    slot:       private void onResolveFinished(uint exitCode, uint);
    slot:       private void onInstallFinished(uint exitCode, uint);
    slot:       private void onPkError(uint, QString details);
    Q_INVOKABLE public QStringList families();
    Q_INVOKABLE public void refresh();
    Q_INVOKABLE public void installFont(QString pkg);
};

class WindowTyper : public QObject
{
    Q_OBJECT
};

class AppMenuModel : public QObject
{
    Q_OBJECT
    signal:     public void changed();
    Q_INVOKABLE public void reload();
    Q_INVOKABLE public QStringList getCategories();
    Q_INVOKABLE public QVariantList getApps(QString category, QString search);
};

class LeapFrogPond : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList notes READ ? NOTIFY notesChanged)
    Q_PROPERTY(int noteCount READ ? NOTIFY notesChanged)
    Q_PROPERTY(QString notice READ ? WRITE ? NOTIFY noticeChanged)
    Q_PROPERTY(QVariantList appts READ ? NOTIFY notesChanged)
    signal:     public void notesChanged();
    signal:     public void noticeChanged();
    signal:     public void archived(int count);
    signal:     public void exported(QString path);
    signal:     public void reconciled(int count);
    Q_INVOKABLE public void addNote(QString text);
    Q_INVOKABLE public void removeNote(QString id);
    Q_INVOKABLE public void removeAppt(QString id);
    Q_INVOKABLE public void setNotice(QString t);
    Q_INVOKABLE public QVariantMap tally();
    Q_INVOKABLE public int reconcile();
    Q_INVOKABLE public int archivePast();
    Q_INVOKABLE public QString exportCsv(QString path);
    Q_INVOKABLE public QString exportCsv();
    Q_INVOKABLE public QString exportLilyPad(QString path);
    Q_INVOKABLE public QString exportLilyPad();
};

class CursorManager : public QObject
{
    Q_OBJECT
};

class NCDEWorkspace : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList names READ ? NOTIFY changed)
    Q_PROPERTY(int current READ ? NOTIFY changed)
    signal:     public void changed();
    Q_INVOKABLE public void activate(int i);
};

class CalendarBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList appointments READ ? NOTIFY changed)
    Q_PROPERTY(QVariantList todos READ ? NOTIFY changed)
    Q_PROPERTY(QVariantMap settings READ ? NOTIFY settingsChanged)
    signal:     public void changed();
    signal:     public void settingsChanged();
    Q_INVOKABLE public QString upsertAppointment(QVariantMap rec);
    Q_INVOKABLE public void deleteAppointment(QString id);
    Q_INVOKABLE public QString upsertTodo(QVariantMap rec);
    Q_INVOKABLE public void toggleTodo(QString id);
    Q_INVOKABLE public void deleteTodo(QString id);
    Q_INVOKABLE public void saveSettings(QVariantMap s);
    Q_INVOKABLE public QString undo();
    Q_INVOKABLE public bool canUndo();
    Q_INVOKABLE public QString exportICS();
    Q_INVOKABLE public bool exportICSToFile(QString path);
    Q_INVOKABLE public int importICS(QString text);
    Q_INVOKABLE public int importICSFromFile(QString path);
    Q_INVOKABLE public void fireReminder(QString title, QString body);
    Q_INVOKABLE public bool composeForHummingbird(QString apptId);
    Q_INVOKABLE public bool composeForHummingbirdRec(QVariantMap appt);
};

class GliaSystemMenus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList applications READ ? NOTIFY changed)
    Q_PROPERTY(QVariantList places READ ? NOTIFY changed)
    Q_PROPERTY(QVariantList recentFiles READ ? NOTIFY changed)
    signal:     public void changed();
    Q_INVOKABLE public void rescan();
    Q_INVOKABLE public void launch(QString execOrId);
    Q_INVOKABLE public void openPath(QString path);
};

class NCDEWindowManager : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ ? NOTIFY countChanged)
    Q_PROPERTY(int coveringCount READ ? NOTIFY coveringCountChanged)
    Q_PROPERTY(int mouseX READ ? NOTIFY mousePosChanged)
    Q_PROPERTY(int mouseY READ ? NOTIFY mousePosChanged)
    Q_PROPERTY(int activeIndex READ ? NOTIFY activeIndexChanged)
    Q_PROPERTY(QString activeAppMenus READ ? NOTIFY activeAppMenusChanged)
    Q_PROPERTY(int snapZone READ ? WRITE ? NOTIFY snapZoneChanged)
    signal:     public void countChanged();
    signal:     public void mousePosChanged();
    signal:     public void activeIndexChanged();
    signal:     public void activeAppMenusChanged();
    signal:     public void snapZoneChanged();
    signal:     public void anyWindowMapped();
    signal:     public void windowAdded(uint win, int x, int y, int w, int h, QString name, QString appId);
    signal:     public void windowRemoved(uint win);
    signal:     public void windowStateChanged();
    signal:     public void coveringCountChanged();
    signal:     public void screenConfigChanged(int w, int h);
    signal:     public void windowTierNeeded(uint pid, QString tier);
    signal:     public void windowClosed(uint pid);
    signal:     public void screensaverIdleReached();
    Q_INVOKABLE public void invokeAppMenu(int id);
    Q_INVOKABLE public void setSnapZone(int z);
    Q_INVOKABLE public int screenWidth();
    Q_INVOKABLE public int screenHeight();
    Q_INVOKABLE public uint atomNetWmWindowType();
    Q_INVOKABLE public uint atomNetWmWindowTypeDesktop();
    Q_INVOKABLE public uint atomNetWmWindowTypeDock();
    Q_INVOKABLE public uint atomNetWmWindowTypePopupMenu();
    Q_INVOKABLE public uint atomNetWmWindowTypeTooltip();
    Q_INVOKABLE public void setWindowType(uint win, uint typeAtom);
    Q_INVOKABLE public int rowForClient(xcb_window_t c);
    Q_INVOKABLE public uint winIdForName(QString n);
    Q_INVOKABLE public bool hasWindowForName(QString n);
    Q_INVOKABLE public bool isMinimizedForName(QString n);
    Q_INVOKABLE public bool isActiveForName(QString n);
    Q_INVOKABLE public bool isMaximizedForName(QString n);
    Q_INVOKABLE public void activateWindow(uint w);
    Q_INVOKABLE public void minimizeWindow(uint w);
    Q_INVOKABLE public void unminimizeWindow(uint w);
    Q_INVOKABLE public void moveWindow(uint w, int x, int y);
    Q_INVOKABLE public void resizeWindow(uint w, int wid, int hgt);
    Q_INVOKABLE public void moveTiledWindow(uint w, int x, int y, int wid, int hgt);
    Q_INVOKABLE public void setTiled(uint w, bool t);
    Q_INVOKABLE public bool isMaximized(uint w);
    Q_INVOKABLE public void setMaximized(uint client, bool maximized);
    Q_INVOKABLE public void closeWindow(uint w);
    Q_INVOKABLE public void systemCommand(QString cmd);
    Q_INVOKABLE public void registerFrameWindowQml(uint client, QObject* frame);
    Q_INVOKABLE public void destroyFrameWindow(uint client);
    Q_INVOKABLE private void switchDesktop(int target);
};

class IdleInhibitService : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.ScreenSaver")
    slot:       public uint Inhibit(QString application_name, QString reason_for_inhibit);
    slot:       public void UnInhibit(uint cookie);
    slot:       private void dropOwner(QString name);
    slot:       private void resetIdle();
};

class NotificationManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList notifications READ ? NOTIFY changed)
    Q_PROPERTY(bool hasNotifications READ ? NOTIFY changed)
    Q_PROPERTY(int unreadCount READ ? NOTIFY changed)
    Q_PROPERTY(QVariantList notifyApps READ ? NOTIFY appsChanged)
    signal:     public void changed();
    signal:     public void appsChanged();
    Q_INVOKABLE public void setAppNotify(QString name, bool on);
    Q_INVOKABLE public int notify(QString title, QString body, QString icon, int timeoutMs);
    Q_INVOKABLE public void dismiss(int id);
    Q_INVOKABLE public void dismissAll();
    Q_INVOKABLE public void markRead();
};

class StatusNotifierWatcherAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.StatusNotifierWatcher")
    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ ?)
    Q_PROPERTY(bool IsStatusNotifierHostRegistered READ ?)
    Q_PROPERTY(int ProtocolVersion READ ?)
    signal:     public void StatusNotifierItemRegistered(QString service);
    signal:     public void StatusNotifierItemUnregistered(QString service);
    signal:     public void StatusNotifierHostRegistered();
    slot:       public void RegisterStatusNotifierItem(QString service);
    slot:       public void RegisterStatusNotifierHost(QString service);
};

class Lelan : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap network READ ? NOTIFY networkChanged)
    Q_PROPERTY(QVariantMap vpn READ ? NOTIFY vpnStateChanged)
    Q_PROPERTY(bool wifiEnabled READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList wifiNetworks READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantMap activeNetwork READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList vpnConnections READ ? NOTIFY vpnStateChanged)
    Q_PROPERTY(QVariantList users READ ? NOTIFY usersChanged)
    Q_PROPERTY(QString userName READ ? NOTIFY userNameChanged)
    Q_PROPERTY(QVariantList printers READ ? NOTIFY printersChanged)
    Q_PROPERTY(QVariantMap battery READ ? NOTIFY batteryChanged)
    Q_PROPERTY(QString powerProfile READ ? NOTIFY powerProfileChanged)
    Q_PROPERTY(int thermalPressure READ ? NOTIFY thermalPressureChanged)
    Q_PROPERTY(QVariantMap sentinelTemps READ ? NOTIFY sentinelTempsChanged)
    Q_PROPERTY(QVariantMap sentinelFans READ ? NOTIFY sentinelFansChanged)
    Q_PROPERTY(QVariantMap audio READ ? NOTIFY audioChanged)
    Q_PROPERTY(int volume READ ? NOTIFY onAudioVolumeUpdated)
    Q_PROPERTY(int balance READ ? NOTIFY audioChanged)
    Q_PROPERTY(bool muted READ ? NOTIFY onAudioMuteUpdated)
    Q_PROPERTY(QVariantList appStreams READ ? NOTIFY appStreamsChanged)
    Q_PROPERTY(QVariantList outputDevices READ ? NOTIFY audioDevicesChanged)
    Q_PROPERTY(QVariantList inputDevices READ ? NOTIFY audioDevicesChanged)
    Q_PROPERTY(QString defaultSourceName READ ? NOTIFY audioDeviceChanged)
    Q_PROPERTY(QVariantMap media READ ? NOTIFY mediaChanged)
    Q_PROPERTY(bool mediaActive READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QVariantMap bluetooth READ ? NOTIFY bluetoothChanged)
    Q_PROPERTY(bool bluetoothEnabled READ ? NOTIFY bluetoothChanged)
    Q_PROPERTY(bool bluetoothDiscoverable READ ? NOTIFY bluetoothChanged)
    Q_PROPERTY(QVariantList bluetoothDevices READ ? NOTIFY bluetoothChanged)
    Q_PROPERTY(QVariantMap bluetoothAudioDevice READ ? NOTIFY bluetoothAudioDeviceChanged)
    Q_PROPERTY(QVariantList removableVolumes READ ? NOTIFY storageChanged)
    Q_PROPERTY(QVariantMap disk READ ? NOTIFY diskChanged)
    Q_PROPERTY(QVariantMap updates READ ? NOTIFY packageStateChanged)
    Q_PROPERTY(bool darkMode READ ? NOTIFY darkModeChanged)
    Q_PROPERTY(QString accentColor READ ? NOTIFY onAccentColorChanged)
    Q_PROPERTY(QString systemFont READ ? NOTIFY systemFontChanged)
    Q_PROPERTY(QVariantMap filigreePalette READ ? NOTIFY filigreePalettesChanged)
    Q_PROPERTY(QVariantMap location READ ? NOTIFY placeNameChanged)
    Q_PROPERTY(QString placeName READ ? NOTIFY placeNameChanged)
    Q_PROPERTY(QVariantMap clock READ ? NOTIFY clockChanged)
    Q_PROPERTY(QString timezone READ ? NOTIFY timezoneChanged)
    Q_PROPERTY(bool locating READ ? NOTIFY timezoneChanged)
    Q_PROPERTY(QVariantList tray READ ? NOTIFY trayChanged)
    Q_PROPERTY(bool sessionActive READ ? NOTIFY onSessionActiveChanged)
    Q_PROPERTY(int vtActive READ ? NOTIFY vtActiveChanged)
    Q_PROPERTY(bool screensaver READ ? NOTIFY screensaverChanged)
    Q_PROPERTY(QString hostname READ ? NOTIFY hostnameChanged)
    Q_PROPERTY(QString locale READ ? NOTIFY localeChanged)
    Q_PROPERTY(QVariantMap kickass READ ? NOTIFY kickassStatusChanged)
    Q_PROPERTY(QVariantList notifications READ ? NOTIFY notificationsChanged)
    Q_PROPERTY(int animLevel READ ? NOTIFY animLevelChanged)
    Q_PROPERTY(bool reduceMotion READ ? NOTIFY animLevelChanged)
    Q_PROPERTY(QString hardwareTier READ ? NOTIFY hardwareTierChanged)
    Q_PROPERTY(double batteryPercent READ ? NOTIFY batteryChanged)
    Q_PROPERTY(bool batteryCharging READ ? NOTIFY batteryChanged)
    Q_PROPERTY(bool hasBattery READ ? NOTIFY batteryChanged)
    Q_PROPERTY(bool networkOnline READ ? NOTIFY networkChanged)
    Q_PROPERTY(bool networkUp READ ? NOTIFY networkChanged)
    Q_PROPERTY(QString mediaTitle READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaArtist READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaAlbum READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaArtUrl READ ? NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaTrackId READ ? NOTIFY mediaChanged)
    Q_PROPERTY(qlonglong mediaDuration READ ? NOTIFY mediaChanged)
    Q_PROPERTY(qlonglong mediaPosition READ ? NOTIFY mediaPositionChanged)
    Q_PROPERTY(bool mediaPlaying READ ? NOTIFY mediaChanged)
    signal:     public void networkChanged();
    signal:     public void vpnStateChanged();
    signal:     public void wifiChanged();
    signal:     public void batteryChanged();
    signal:     public void powerProfileChanged();
    signal:     public void powerChanged();
    signal:     public void thermalPressureChanged();
    signal:     public void sentinelTempsChanged();
    signal:     public void sentinelFansChanged();
    signal:     public void driverMissing(QString device, QString modalias, QString suggestedModule);
    signal:     public void statsChanged();
    signal:     public void audioChanged();
    signal:     public void audioDeviceChanged();
    signal:     public void audioDevicesChanged();
    signal:     public void bluetoothAudioDeviceChanged();
    signal:     public void onAudioVolumeUpdated();
    signal:     public void onAudioMuteUpdated();
    signal:     public void onFallbackSinkUpdated();
    signal:     public void appStreamsChanged();
    signal:     public void mediaChanged();
    signal:     public void mediaPositionChanged();
    signal:     public void appNameChanged();
    signal:     public void appIconChanged();
    signal:     public void durationChanged();
    signal:     public void bluetoothChanged();
    signal:     public void diskChanged();
    signal:     public void diskDeviceChanged();
    signal:     public void diskMountChanged();
    signal:     public void storageChanged();
    signal:     public void kickassChanged();
    signal:     public void kickassStatusChanged();
    signal:     public void kickassSiteBlocked(QString domain, QString detail);
    signal:     public void kickassThreatBlocked(QString app, QString detail, int severity);
    signal:     public void kickassThreatBehavioral(QString subject, QString detail, QString kind);
    signal:     public void kickassNetworkAlert(QString src, QString detail);
    signal:     public void packageStateChanged();
    signal:     public void updatesChanged();
    signal:     public void clockChanged();
    signal:     public void timeJumped();
    signal:     public void pulse(qulonglong tick);
    signal:     public void leanSleeping();
    signal:     public void leanWaking();
    signal:     public void dateTimeChanged();
    signal:     public void timezoneChanged();
    signal:     public void weatherChanged();
    signal:     public void placeNameChanged();
    signal:     public void moonPositionChanged();
    signal:     public void trayChanged();
    signal:     public void onTrayBadgeChanged();
    signal:     public void onTrayPercentChanged();
    signal:     public void themeChanged();
    signal:     public void darkModeChanged();
    signal:     public void onAccentColorChanged();
    signal:     public void wallpaperChanged();
    signal:     public void systemFontChanged();
    signal:     public void slideshowChanged();
    signal:     public void filigreePalettesChanged();
    signal:     public void onSessionActiveChanged();
    signal:     public void vtActiveChanged();
    signal:     public void screensaverChanged();
    signal:     public void screenConfigChanged();
    signal:     public void screenGeometryChanged();
    signal:     public void hostnameChanged();
    signal:     public void localeChanged();
    signal:     public void userNameChanged();
    signal:     public void usersChanged();
    signal:     public void printersChanged();
    signal:     public void notificationsChanged();
    signal:     public void animLevelChanged();
    signal:     public void hardwareTierChanged();
    slot:       public void onWMScreenConfig(int, int);
    slot:       public void onWindowTierNeeded(uint pid, QString tier);
    slot:       public void onWindowClosed(uint pid);
    slot:       public void applyProperties(QVariantMap m);
    slot:       public void fetchAndApply(QString key);
    slot:       public void mediaPlayPause();
    slot:       public void mediaNext();
    slot:       public void mediaPrevious();
    slot:       public void mediaSeek(qlonglong positionUs);
    slot:       public void setVolume(int v);
    slot:       public void toggleMute();
    slot:       public void setBalance(int v);
    slot:       public void setAppVolume(QString name, int volumePct);
    slot:       public void setOutputDevice(QString name);
    slot:       public void setInputDevice(QString name);
    slot:       public void setWifiEnabled(bool on);
    slot:       public void connectWifi(QString ssid, QString password);
    slot:       public void disconnectWifi();
    slot:       public void connectVpn(QString name);
    slot:       public void disconnectVpn(QString name);
    slot:       public void setBluetoothEnabled(bool on);
    slot:       public void setBluetoothDiscoverable(bool on);
    slot:       public void bluetoothConnect(QString address);
    slot:       public void bluetoothDisconnect(QString address);
    slot:       public void bluetoothPair(QString address);
    slot:       public void bluetoothRemove(QString address);
    slot:       public void bluetoothScan();
    slot:       public void setTimezone(QString zone);
    slot:       public void setNtp(bool on);
    slot:       public void refreshLocation();
    slot:       public void addUser(QString name, QString displayName, bool isAdmin);
    slot:       public void removeUser(QString name);
    slot:       public void setUserAdmin(QString name, bool admin);
    slot:       public void changePassword(QString name, QString pwd);
    slot:       public void setAutoLogin(QString name, bool on);
    slot:       public void setAutoLogin(QString name);
    slot:       public void setUserAvatar(QString name, QString file);
    slot:       public void setDefaultPrinter(QString name);
    slot:       public void removePrinter(QString name);
    slot:       public void mountVolume(QString objectPath);
    slot:       public void unmountVolume(QString objectPath);
    slot:       public void setAnimUtilClamp(bool boost);
    slot:       public void setReduceMotionPref(bool on);
    slot:       public void retryFallbackSink();
    slot:       private void onNameOwnerChanged(QString name, QString oldOwner, QString newOwner);
    slot:       private void onSystemNameOwnerChanged(QString name, QString oldOwner, QString newOwner);
    slot:       private void onCoalescedTick();
    slot:       private void onPulse();
    slot:       private void recomputeAnimLevel();
    slot:       private void drainIdleQueue();
    slot:       private void onNetworkStateChanged(uint state);
    slot:       private void onNmPropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onVpnStateChanged(uint state, uint reason);
    slot:       private void onWifiPropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onBatteryPropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onBlueZInterfacesAdded(QDBusObjectPath path, BlueZInterfaceMap ifaces);
    slot:       private void onBlueZInterfacesRemoved(QDBusObjectPath path, QStringList ifaces);
    slot:       private void onBlueZPropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onUDisks2InterfacesAdded(QDBusObjectPath path, BlueZInterfaceMap ifaces);
    slot:       private void onUDisks2InterfacesRemoved(QDBusObjectPath path, QStringList ifaces);
    slot:       private void onUDisks2FilesystemPropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void applyPulseState(int volume, bool muted, QString sink, uint sinkIndex, int channels);
    slot:       private void applyAppStreams(QVariantList streams);
    slot:       private void applyOutputDevices(QVariantList devs);
    slot:       private void applyInputDevices(QVariantList devs);
    slot:       private void applyDefaultSource(QString name);
    slot:       private void onPowerProfilesPropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onPackageKitUpdatesChanged();
    slot:       private void onPackageKitUpdatesPackage(uint info, QString packageId, QString summary);
    slot:       private void onPackageKitUpdatesFinished(uint exit, uint runtime);
    slot:       private void onPortalSettingChanged(QString ns, QString key, QDBusVariant value);
    slot:       private void onLowMemoryWarning(uchar level);
    slot:       private void onGeoClue2Location(QDBusObjectPath oldLoc, QDBusObjectPath newLoc);
    slot:       private void onTimedate1PropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onHostname1PropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onLocale1PropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onSessionActiveChangedSlot(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onSessionLock();
    slot:       private void onSessionUnlock();
    slot:       private void onPrepareForSleep(bool before);
    slot:       private void onScreenSaverActivated(bool active);
    slot:       private void onActionInvoked(uint id, QString action);
    slot:       private void onPropertiesChanged(QString iface, QVariantMap changed, QStringList inval);
    slot:       private void onMprisSeeked(qlonglong positionUs);
    slot:       private void onLayoutUpdated();
    slot:       private void rebuildTray();
    slot:       private void onTrayItemChanged();
    slot:       private void onSentinelDisplayConnected(QString name);
    slot:       private void onSentinelDisplayDisconnected(QString name);
    slot:       private void onSentinelUsbDeviceAdded(QString id, QString name);
    slot:       private void onSentinelUsbDeviceRemoved(QString id, QString name);
    slot:       private void onSentinelInputDeviceAdded(QString name);
    slot:       private void onSentinelInputDeviceRemoved(QString name);
    slot:       private void onSentinelAudioDeviceChanged(QString id, QString name);
    slot:       private void onSentinelBatteryStateChanged(bool onBattery, int percentage);
    slot:       private void onSentinelNetworkStateChanged(QString iface, bool up);
    slot:       private void onSentinelThermalChanged(SentinelTempMap temps);
    slot:       private void onSentinelFanChanged(SentinelFanMap fans);
    slot:       private void onSentinelThermalCritical(QString sensor, double tempC);
    slot:       private void onSentinelDriverMissing(QString device, QString modalias, QString suggested);
    slot:       private void onKickassStatusChanged(bool armed, int level);
    slot:       private void onKickassThreatBlocked(QString app, QString detail, int severity);
    slot:       private void onKickassThreatBehavioral(QString subject, QString detail, QString kind);
    slot:       private void onKickassSiteBlocked(QString site, QString detail);
    slot:       private void onKickassNetworkAlert(QString src, QString detail);
    Q_INVOKABLE public QVariantMap loadConfig(QString name);
    Q_INVOKABLE public bool saveConfig(QString name, QVariantMap data);
    Q_INVOKABLE public qlonglong monoRawMs();
};

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fontFamily READ ? NOTIFY changed)
    Q_PROPERTY(QString titleFont READ ? NOTIFY changed)
    Q_PROPERTY(double letterSpacing READ ? NOTIFY changed)
    Q_PROPERTY(int fontSmall READ ? NOTIFY changed)
    Q_PROPERTY(int fontMedium READ ? NOTIFY changed)
    Q_PROPERTY(int fontLarge READ ? NOTIFY changed)
    Q_PROPERTY(QString textColor READ ? NOTIFY changed)
    Q_PROPERTY(int textStyle READ ? NOTIFY changed)
    Q_PROPERTY(QString textStyleColor READ ? NOTIFY changed)
    Q_PROPERTY(QString textShadowColor READ ? NOTIFY changed)
    Q_PROPERTY(bool textShadowEnabled READ ? NOTIFY changed)
    Q_PROPERTY(double textShadowRadius READ ? NOTIFY changed)
    Q_PROPERTY(double textShadowOffsetX READ ? NOTIFY changed)
    Q_PROPERTY(double textShadowOffsetY READ ? NOTIFY changed)
    signal:     public void changed();
    Q_INVOKABLE public double scale(double base);
};

class NCDEGeo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double latitude READ ? NOTIFY changed)
    Q_PROPERTY(double longitude READ ? NOTIFY changed)
    Q_PROPERTY(QString localTime READ ? NOTIFY changed)
    Q_PROPERTY(bool locating READ ? NOTIFY changed)
    Q_PROPERTY(QString offset READ ? NOTIFY changed)
    Q_PROPERTY(QString place READ ? NOTIFY changed)
    Q_PROPERTY(QString tzName READ ? NOTIFY changed)
    Q_PROPERTY(QString zone READ ? NOTIFY changed)
    signal:     public void changed();
};

class Launcher : public QObject
{
    Q_OBJECT
    Q_INVOKABLE public void launchExec(QString cmd);
    Q_INVOKABLE public void launch(QString cmd);
    Q_INVOKABLE public void systemCommand(QString cmd);
    Q_INVOKABLE public void launchWithFiles(QString exec, QVariantList files);
    Q_INVOKABLE public QString homePath();
    Q_INVOKABLE public void logout();
};

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList displays READ ? NOTIFY displaysChanged)
    Q_PROPERTY(bool nightLightOn READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(int nightWarmth READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(bool nightLightAuto READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(int batBlank READ ? WRITE ? NOTIFY powerChanged)
    Q_PROPERTY(int batSuspend READ ? WRITE ? NOTIFY powerChanged)
    Q_PROPERTY(int acBlank READ ? WRITE ? NOTIFY powerChanged)
    Q_PROPERTY(int acSuspend READ ? WRITE ? NOTIFY powerChanged)
    Q_PROPERTY(QString lidAction READ ? WRITE ? NOTIFY powerChanged)
    Q_PROPERTY(QString powerButtonAction READ ? WRITE ? NOTIFY powerChanged)
    Q_PROPERTY(bool showBatteryPct READ ? WRITE ? NOTIFY powerChanged)
    Q_PROPERTY(QString fontFamily READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(QString dockHoverTextColor READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString topPanelTextColor READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString gliaTextColor READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString leapFrogTextColor READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString accentOverride READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString accentMutedOverride READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString glowOverride READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString borderOverride READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(bool slideshowPaused READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(int fontWeight READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(bool fontItalic READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double fontSizeScale READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double letterSpacing READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double lineHeight READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double uiScale READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(QString textColor READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(bool textOutlineEnabled READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(QString textOutlineColor READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double textOutlineWidth READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(bool textShadowEnabled READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(QString textShadowColor READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double textShadowOffsetX READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double textShadowOffsetY READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(double textShadowRadius READ ? WRITE ? NOTIFY fontChanged)
    Q_PROPERTY(bool autoMountUsb READ ? WRITE ? NOTIFY storageChanged)
    Q_PROPERTY(int kbRepeatDelay READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(int kbRepeatRate READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(int pointerSpeed READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(int touchpadSpeed READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(bool naturalScroll READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(bool tapToClick READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(bool disableWhileTyping READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(int cursorSize READ ? WRITE ? NOTIFY inputChanged)
    Q_PROPERTY(double accessibilityTextScale READ ? WRITE ? NOTIFY accessibilityChanged)
    Q_PROPERTY(bool highContrast READ ? WRITE ? NOTIFY accessibilityChanged)
    Q_PROPERTY(bool reduceMotion READ ? WRITE ? NOTIFY accessibilityChanged)
    Q_PROPERTY(bool largerCursor READ ? WRITE ? NOTIFY accessibilityChanged)
    Q_PROPERTY(bool locationEnabled READ ? WRITE ? NOTIFY privacyChanged)
    Q_PROPERTY(bool lockScreenNotifPreview READ ? WRITE ? NOTIFY privacyChanged)
    Q_PROPERTY(int screensaverTimeout READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString screensaverSeason READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(bool screensaverClockVisible READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(int screensaverFps READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(bool requirePassword READ ? WRITE ? NOTIFY securityChanged)
    Q_PROPERTY(int requirePasswordDelay READ ? WRITE ? NOTIFY securityChanged)
    Q_PROPERTY(bool kickassArmed READ ? WRITE ? NOTIFY securityChanged)
    Q_PROPERTY(QString hourFormat READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(bool showSeconds READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(bool ntpEnabled READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString timezoneManual READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(bool proxyEnabled READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(QString proxyHost READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(int proxyPort READ ? WRITE ? NOTIFY settingsChanged)
    Q_PROPERTY(int dockIconSize READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(int dockSpacing READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(double dockZoomPercent READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(int dockZoomRange READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(int dockAnimSpeed READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(double dockMagSpring READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(double dockMagDamping READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(double dockMagMass READ ? WRITE ? NOTIFY dockChanged)
    Q_PROPERTY(QVariantList dockApps READ ? NOTIFY dockChanged)
    Q_PROPERTY(QString assetBase READ ? CONSTANT)
    Q_PROPERTY(QString configBase READ ? CONSTANT)
    Q_PROPERTY(QString systemLanguage READ ? WRITE ? NOTIFY localeChanged)
    Q_PROPERTY(QString systemLocale READ ? WRITE ? NOTIFY localeChanged)
    Q_PROPERTY(QStringList kbLayouts READ ? NOTIFY localeChanged)
    Q_PROPERTY(QString activeKbLayout READ ? WRITE ? NOTIFY localeChanged)
    Q_PROPERTY(QString defaultBrowser READ ? WRITE ? NOTIFY sessionChanged)
    Q_PROPERTY(QString defaultMail READ ? WRITE ? NOTIFY sessionChanged)
    Q_PROPERTY(QString defaultFiles READ ? WRITE ? NOTIFY sessionChanged)
    Q_PROPERTY(QString defaultTerminal READ ? WRITE ? NOTIFY sessionChanged)
    Q_PROPERTY(bool dnd READ ? WRITE ? NOTIFY notifsChanged)
    Q_PROPERTY(int notifPosition READ ? WRITE ? NOTIFY notifsChanged)
    Q_PROPERTY(bool quietHoursOn READ ? WRITE ? NOTIFY notifsChanged)
    Q_PROPERTY(QString quietFrom READ ? WRITE ? NOTIFY notifsChanged)
    Q_PROPERTY(QString quietTo READ ? WRITE ? NOTIFY notifsChanged)
    Q_PROPERTY(QString userName READ ? CONSTANT)
    Q_PROPERTY(QStringList customWallpapers READ ? NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(bool slideshowEnabled READ ? WRITE ? NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(int slideshowInterval READ ? WRITE ? NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(QString fitMode READ ? WRITE ? NOTIFY wallpaperPrefsChanged)
    Q_PROPERTY(int outputVolume READ ? WRITE ? NOTIFY soundChanged)
    Q_PROPERTY(int inputVolume READ ? WRITE ? NOTIFY soundChanged)
    Q_PROPERTY(QString outputDevice READ ? WRITE ? NOTIFY soundChanged)
    Q_PROPERTY(QString inputDevice READ ? WRITE ? NOTIFY soundChanged)
    Q_PROPERTY(double inputLevel READ ? WRITE ? NOTIFY soundChanged)
    signal:     public void displaysChanged();
    signal:     public void settingsChanged();
    signal:     public void dockPrefsChanged();
    signal:     public void wallpaperChanged(QString path);
    signal:     public void slideshowAdvanced(QString path);
    signal:     public void powerChanged();
    signal:     public void fontChanged();
    signal:     public void storageChanged();
    signal:     public void inputChanged();
    signal:     public void accessibilityChanged();
    signal:     public void privacyChanged();
    signal:     public void securityChanged();
    signal:     public void dockChanged();
    signal:     public void localeChanged();
    signal:     public void sessionChanged();
    signal:     public void notifsChanged();
    signal:     public void wallpaperPrefsChanged();
    signal:     public void soundChanged();
    signal:     public void screensaverFinished(int exitCode, bool crashed);
    slot:       public void onScreenIdleChanged();
    slot:       public void refreshDisplays();
    slot:       public void applyDisplayMode(QString name, QString mode, double hz);
    slot:       public void applyDisplayOrientation(QString name, QString orient);
    slot:       public void applyDisplayScale(QString name, int pct);
    slot:       public void saveDisplay();
    slot:       public void loadDisplay();
    slot:       public void loadPower();
    slot:       public void applyPowerSettings();
    slot:       public void savePower();
    slot:       public void applyFontSettings();
    slot:       public void saveFontSettings();
    slot:       public void saveTextColor();
    slot:       public void loadStorage();
    slot:       public void saveStorage();
    slot:       public void loadFonts();
    slot:       public void loadInput();
    slot:       public void saveInput();
    slot:       public void loadAccessibility();
    slot:       public void saveAccessibility();
    slot:       public void loadPrivacy();
    slot:       public void saveConfPrivacy();
    slot:       public void loadDock();
    slot:       public void setDockApps(QVariantList apps);
    slot:       public void saveDockPrefs();
    slot:       public QVariantList installedApps();
    slot:       public void loadLocale();
    slot:       public void saveLocale();
    slot:       public void setActiveKbLayout(QString code);
    slot:       public void addKbLayout(QString code);
    slot:       public void removeKbLayout(QString code);
    slot:       public void loadDefaults();
    slot:       public void saveDefaults();
    slot:       public QString loadAutostart();
    slot:       public void saveAutostart(QString json);
    slot:       public void loadNotifications();
    slot:       public void saveNotifications();
    slot:       public QString getWallpaper();
    slot:       public void setWallpaper(QString path);
    slot:       public void loadWallpaperPrefs();
    slot:       public void saveWallpaperPrefs();
    slot:       public void setSlideshowEnabled(bool v);
    slot:       public void setSlideshowInterval(int v);
    slot:       public void setFitMode(QString v);
    slot:       public void loadSound();
    slot:       public void saveSound();
    Q_INVOKABLE public void saveSurfaceGlass(QString key, QColor tint, double shine, double glow, QColor border, QColor glowColor);
    Q_INVOKABLE public void saveWidgetStyleMap(QString key, QVariantMap map);
    Q_INVOKABLE public void resetWidgetStyle(QString key);
    Q_INVOKABLE public void saveColorOverrides();
    Q_INVOKABLE public void saveSectionColors();
    Q_INVOKABLE public void saveFiligreepalette(QString name, double hue, double sat, QVariantList palette);
    Q_INVOKABLE public void setSlideshowPaused(bool p);
    Q_INVOKABLE public void saveDateTime();
    Q_INVOKABLE public void saveNetwork();
    Q_INVOKABLE public void saveScreensaver();
    Q_INVOKABLE public void loadScreensaver();
    Q_INVOKABLE public void previewScreensaver(QString season);
    Q_INVOKABLE public void previewScreensaver();
    Q_INVOKABLE public bool screensaverRunning();
    Q_INVOKABLE public void savePrivacy();
    Q_INVOKABLE public void saveSecurity();
    Q_INVOKABLE public void saveConfig();
    Q_INVOKABLE public void setKickassArmed(bool a);
    Q_INVOKABLE public void loadKickass();
    Q_INVOKABLE public void initWatcher();
};

class NcdeTheme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor accent READ ? NOTIFY changed)
    Q_PROPERTY(QColor accentMuted READ ? NOTIFY changed)
    Q_PROPERTY(QColor border READ ? NOTIFY changed)
    Q_PROPERTY(bool darkMode READ ? NOTIFY changed)
    Q_PROPERTY(int fontSize READ ? NOTIFY changed)
    Q_PROPERTY(QColor foreground READ ? NOTIFY changed)
    Q_PROPERTY(QColor gilt READ ? NOTIFY changed)
    Q_PROPERTY(QColor glow READ ? NOTIFY changed)
    Q_PROPERTY(QColor panelBg READ ? NOTIFY changed)
    Q_PROPERTY(QColor popupBg READ ? NOTIFY changed)
    Q_PROPERTY(bool presetActive READ ? NOTIFY changed)
    Q_PROPERTY(QColor surface READ ? NOTIFY changed)
    Q_PROPERTY(QColor surfaceAlt READ ? NOTIFY changed)
    Q_PROPERTY(QColor surfaceGlass READ ? NOTIFY changed)
    Q_PROPERTY(QColor verd READ ? NOTIFY changed)
    Q_PROPERTY(QString version READ ? CONSTANT)
    Q_PROPERTY(QString widgetStyle READ ? NOTIFY changed)
    Q_PROPERTY(QColor wine READ ? NOTIFY changed)
    Q_PROPERTY(QObject* KickassGuard READ ? CONSTANT)
    Q_PROPERTY(bool wifiEnabled READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList wifiNetworks READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantMap activeNetwork READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList vpnConnections READ ? NOTIFY wifiChanged)
    Q_PROPERTY(bool bluetoothEnabled READ ? NOTIFY wifiChanged)
    Q_PROPERTY(bool bluetoothDiscoverable READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QVariantList bluetoothDevices READ ? NOTIFY wifiChanged)
    Q_PROPERTY(QString detectedTzName READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString detectedZone READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString detectedRegion READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString detectedOffset READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QString localTime READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(bool locating READ ? NOTIFY dateTimeChanged)
    Q_PROPERTY(QVariantList users READ ? NOTIFY usersChanged)
    Q_PROPERTY(QVariantList printers READ ? NOTIFY printersChanged)
    Q_PROPERTY(QVariantList appStreams READ ? NOTIFY soundChanged)
    Q_PROPERTY(int letterSpacing READ ? NOTIFY changed)
    signal:     public void changed();
    signal:     public void wifiChanged();
    signal:     public void dateTimeChanged();
    signal:     public void usersChanged();
    signal:     public void printersChanged();
    signal:     public void soundChanged();
    slot:       public void applyPalette(QVariantMap p);
    Q_INVOKABLE public void setWifiEnabled(bool on);
    Q_INVOKABLE public void connectNetwork(QString ssid, QString pwd);
    Q_INVOKABLE public void disconnectNetwork();
    Q_INVOKABLE public void connectVpn(QString name);
    Q_INVOKABLE public void disconnectVpn(QString name);
    Q_INVOKABLE public void setBluetoothEnabled(bool on);
    Q_INVOKABLE public void setBluetoothDiscoverable(bool on);
    Q_INVOKABLE public void bluetoothConnect(QString a);
    Q_INVOKABLE public void bluetoothDisconnect(QString a);
    Q_INVOKABLE public void bluetoothPair(QString a);
    Q_INVOKABLE public void bluetoothRemove(QString a);
    Q_INVOKABLE public void bluetoothScan();
    Q_INVOKABLE public void refreshLocation();
    Q_INVOKABLE public void setTimezone(QString z);
    Q_INVOKABLE public void setNtp(bool on);
    Q_INVOKABLE public void addUser(QString n, QString d, bool a);
    Q_INVOKABLE public void removeUser(QString n);
    Q_INVOKABLE public void setUserAdmin(QString n, bool a);
    Q_INVOKABLE public void changePassword(QString n, QString p);
    Q_INVOKABLE public void setAutoLogin(QString n);
    Q_INVOKABLE public void setUserAvatar(QString n, QString f);
    Q_INVOKABLE public void setDefaultPrinter(QString n);
    Q_INVOKABLE public void removePrinter(QString n);
    Q_INVOKABLE public void setAppVolume(QString name, int vol);
};

