// NCDEWindowManager — the core X11 window manager: manage, container/frame reparenting, focus,
// stacking, maximize/tiled/minimized state, EWMH, GliaTalk menu reading, RandR, picom watch,
// App-Nap tiers, desktop-obscured and user-idle feeds for AnimPolicy/Settings. QML sees it as
// `windowMgr` (a QAbstractListModel of managed windows; main.qml instantiates one MotifFrame
// window per row).
//
// Rebuilt 2026-10-01 from the oracle, function by function: decomp/NCDEWindowManager.c (all 94
// NCDEWindowManager:: functions) + decomp/_global.c FUN_00291390 (the registerFrameWindowQml game
// path). Interface: interfaces/LaPivot-metaobjects.h. Spec: docs/wm-oracle-audit.md,
// files/full-patch-20260711/notes/wm-mainqml-games.md. Replaces an earlier non-oracle rewrite
// (kept as *.prebak-20261001-oracle-rebuild) that never reparented clients, had no title role and
// shifted the model role numbers.
//
// How a window appears (oracle): MapRequest -> manage() records it (not mapped yet) and emits
// windowAdded -> main.qml creates a frame Window (override-redirect) -> registerFrameWindowQml()
// -> registerFrameWindow(): container (client + 12/32 px) created, client reparented into it at
// (12,32), client + container mapped, frame stacked above the container, frame input shape = the
// decoration ring only, client activated. Steam/games (appId steam, steamwebhelper, gamescope,
// steam_app_*): no container, client mapped bare, frame shaped empty (invisible, click-through).
//
// Geometry: model x/y/w/h = the CLIENT's root geometry. Container = (x-12, y-32, w+24, h+58).
// Frame (QML) = (x-24, y-44, w+48, h+82).
//
// DEFECTS FIXED vs oracle (each a measured/observed flaw, not a preference):
//  W1 setGeom() treated any negative x/y as "unchanged": a window dragged partly off the left or
//     top edge kept its old model position (frame and client drifted apart). Explicit keep flags.
//  W2 closeWindow() sent WM_DELETE_WINDOW even to clients that don't list it in WM_PROTOCOLS ->
//     the close button did nothing for them. Now: WM_DELETE_WINDOW if supported, else kill.
//  W3 a client that withdraws itself (unmaps, ICCCM) kept its frame and dock entry forever. Now
//     self-unmaps (not ones the WM caused) unmanage it: reparent back to root, container destroyed.
//  W4 moving a containered window sent the client no synthetic ConfigureNotify -> apps kept their
//     old root position, so their popup menus/combos opened in the wrong place after a move.
//     Also sent when a resize of a maximized window is refused (ICCCM 4.1.5).
//  W5 iconify requests (WM_CHANGE_STATE IconicState, _NET_WM_STATE add/toggle _HIDDEN) were
//     ignored; a helper (ncde-iconify-bridge) wrote them to a file that main.qml polled every
//     250 ms forever (anim-policy.md §4.4 violation). The WM now minimizes directly.
//  W6 _NET_ACTIVE_WINDOW requests (an app or notification asking to be raised) were ignored.
//  W7 no _NET_CLIENT_LIST / _NET_SUPPORTING_WM_CHECK: pagers, Steam overlay, screenshot tools and
//     toolkits could not see an EWMH window manager or its windows.
//  W8 DOCK / DESKTOP / SPLASH / NOTIFICATION / TOOLTIP / menu-type windows were framed and then
//     maximized by main.qml (a splash screen filled the screen). They are now mapped as-is, unmanaged.
//  W9 every XInput raw-motion event (up to the mouse's polling rate, 1000/s) did a blocking
//     QCursor::pos() round trip; now coalesced to one read per 16 ms frame.
//  W10 FocusIn on unmanaged windows (root, override-redirect popups) overwrote the active client.
//  W11 destroyFrameWindow() on an already-destroyed client asked X to reparent a dead window
//     (BadWindow); unmanage now knows whether the client is still alive.
//  W14 WM_STATE was never written (ICCCM 4.1.3.1) and _NET_WM_STATE_HIDDEN, though listed in
//     _NET_SUPPORTED, was never set on a minimized window: apps (Steam, GTK, Electron) and pagers
//     could not tell they were minimized. Now Normal on manage, Iconic + _HIDDEN on minimize,
//     Normal on restore, Withdrawn on unmanage. Maximize no longer REPLACES _NET_WM_STATE with
//     {MAXV, MAXH} (that wiped every other state, e.g. _HIDDEN); states are added/removed.
//  W15 no global keys: Alt+F4 and the Super tap (Expose) lived only in main.qml's Keys handler, so
//     they worked only while the desktop itself had focus; Alt+F4 could never close the focused
//     app. The WM now grabs them on the root (all Caps/Num Lock combinations, re-grabbed when the
//     keymap changes): Alt+F4 closes the active window, a Super tap emits exposeToggleRequested().
#pragma once

#include <QAbstractListModel>
#include <initializer_list>
#include <QAbstractNativeEventFilter>
#include <QHash>
#include <QList>
#include <QString>
#include <QTimer>
#include <xcb/xcb.h>

class AnimPolicy;

class NCDEWindowManager : public QAbstractListModel, public QAbstractNativeEventFilter
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int coveringCount READ coveringCount NOTIFY coveringCountChanged)
    Q_PROPERTY(int mouseX READ mouseX NOTIFY mousePosChanged)
    Q_PROPERTY(int mouseY READ mouseY NOTIFY mousePosChanged)
    Q_PROPERTY(int activeIndex READ activeIndex NOTIFY activeIndexChanged)
    Q_PROPERTY(QString activeAppMenus READ activeAppMenus NOTIFY activeAppMenusChanged)
    Q_PROPERTY(int snapZone READ snapZone WRITE setSnapZone NOTIFY snapZoneChanged)

public:
    // oracle role numbers (QML and TilingManager.qml read them by number)
    enum Roles {
        WinIdRole = 0x101, XRole, YRole, WRole, HRole, NameRole, AppIdRole,
        MinimizedRole, MaximizedRole, TitleRole, TiledRole
    };

    struct WindowEntry {
        uint client = 0;
        int x = 0, y = 0, w = 0, h = 0;
        QString name;          // window title (_NET_WM_NAME / WM_NAME, "Window" when none)
        QString appId;         // WM_CLASS class part
        QString menus;         // GliaTalk _NCDE_MENUS JSON
        bool minimized = false;
        bool maximized = false;
        bool tiled = false;
        uint pid = 0;
        uint desktop = 0;
    };

    explicit NCDEWindowManager(QObject *parent = nullptr);
    ~NCDEWindowManager() override;

    bool start();
    void setAnimPolicy(AnimPolicy *policy);
    void setScreensaverTimeoutMs(qint64 ms);
    bool screensaverIdleActive() const { return m_screensaverIdle; }

    int count() const { return int(m_windows.size()); }
    int coveringCount() const { return m_coveringCount; }
    int mouseX() const { return m_mouseX; }
    int mouseY() const { return m_mouseY; }
    int activeIndex() const { return m_activeIndex; }
    QString activeAppMenus() const;
    int snapZone() const { return m_snapZone; }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

    Q_INVOKABLE void invokeAppMenu(int id);
    Q_INVOKABLE void setSnapZone(int z);
    Q_INVOKABLE int screenWidth() const { return m_screenW; }
    Q_INVOKABLE int screenHeight() const { return m_screenH; }
    Q_INVOKABLE uint atomNetWmWindowType() const { return m_aWindowType; }
    Q_INVOKABLE uint atomNetWmWindowTypeDesktop() const { return m_aTypeDesktop; }
    Q_INVOKABLE uint atomNetWmWindowTypeDock() const { return m_aTypeDock; }
    Q_INVOKABLE uint atomNetWmWindowTypePopupMenu() const { return m_aTypePopupMenu; }
    Q_INVOKABLE uint atomNetWmWindowTypeTooltip() const { return m_aTypeTooltip; }
    Q_INVOKABLE void setWindowType(uint win, uint typeAtom);
    Q_INVOKABLE int rowForClient(uint c) const;
    Q_INVOKABLE uint winIdForName(const QString &n) const;
    Q_INVOKABLE bool hasWindowForName(const QString &n) const;
    Q_INVOKABLE bool isMinimizedForName(const QString &n) const;
    Q_INVOKABLE bool isActiveForName(const QString &n) const;
    Q_INVOKABLE bool isMaximizedForName(const QString &n) const;
    Q_INVOKABLE void activateWindow(uint w);
    Q_INVOKABLE void minimizeWindow(uint w);
    Q_INVOKABLE void unminimizeWindow(uint w);
    Q_INVOKABLE void moveWindow(uint w, int x, int y);
    Q_INVOKABLE void resizeWindow(uint w, int wid, int hgt);
    Q_INVOKABLE void moveTiledWindow(uint w, int x, int y, int wid, int hgt);
    Q_INVOKABLE void setTiled(uint w, bool t);
    Q_INVOKABLE bool isMaximized(uint w) const;
    Q_INVOKABLE void setMaximized(uint client, bool maximized);
    Q_INVOKABLE void closeWindow(uint w);
    Q_INVOKABLE void systemCommand(const QString &cmd);
    Q_INVOKABLE void registerFrameWindowQml(uint client, QObject *frame);
    Q_INVOKABLE void destroyFrameWindow(uint client);

    // declared addition (tests/iface_additions/NCDEWindowManager.txt): live X idle, for Settings
    Q_INVOKABLE qint64 userIdleMs() const;

signals:
    void countChanged();
    void mousePosChanged();
    void activeIndexChanged();
    void activeAppMenusChanged();
    void snapZoneChanged();
    void anyWindowMapped();
    void windowAdded(uint win, int x, int y, int w, int h, const QString &name, const QString &appId);
    void windowRemoved(uint win);
    void windowStateChanged();
    void coveringCountChanged();
    void screenConfigChanged(int w, int h);
    void windowTierNeeded(uint pid, const QString &tier);
    void windowClosed(uint pid);
    void screensaverIdleReached();
    // declared addition: every idle poll (2 s), Settings/IdlePolicy owns the decisions
    void idleSample(qint64 idleMs);
    // W15: Super pressed and released on its own, whichever window has focus
    void exposeToggleRequested();

private slots:
    void switchDesktop(int target);

private:
    void internAtoms();
    void setupEwmh();
    void scanExisting();
    void manage(uint win);
    void onConfigureRequest(const xcb_configure_request_event_t *ev);
    void onPropertyNotify(uint win, uint atom);
    void onClientMessage(const xcb_client_message_event_t *ev);
    void onUnmapNotify(const xcb_unmap_notify_event_t *ev);
    void onFocusIn(uint win);
    void onDestroy(uint win);
    void onRandRScreenChange(int w, int h);
    void grabGlobalKeys();                                                                  // W15
    bool onGlobalKey(const xcb_key_press_event_t *ev, bool press);                          // W15
    void watchPicomOwner();
    void onPicomDied();
    void registerFrameWindow(uint client, uint frame);
    void registerGameFrame(uint client, uint frame, int row);
    void unmanage(uint client, bool clientAlive);
    uint createContainer(int x, int y, int w, int h, bool argb);
    uint findArgbVisual() const;
    void setWmClass(uint win, const char *cls);
    void setFrameInputRegion(uint frame, int w, int h);
    void setActiveIndex(int i);
    void setMin(uint client, bool on, bool emitTiers = true);
    void setWmState(uint client, uint32_t state);                                       // W14
    void editNetWmState(uint client, std::initializer_list<uint32_t> add,
                        std::initializer_list<uint32_t> remove);                         // W14
    void setGeom(uint client, int x, int y, int w, int h, bool keepPos, bool keepSize);
    void emitTierUpdates();
    void scheduleCoveringRecount();
    void recomputeCoveringCount();
    void recomputeDesktopObscured();
    void pollPointer();
    void pollUserIdle();
    void updateClientList();
    void sendSyntheticConfigure(uint client, const WindowEntry &e);
    void unmapByWm(uint win);
    void rowChanged(int row);
    bool isViewable(uint win) const;
    bool supportsProtocol(uint win, uint atom) const;
    bool isUnframedType(uint win) const;
    QString getWindowTitle(uint win) const;
    QString getWindowClass(uint win) const;
    uint getWindowPid(uint win) const;

    xcb_connection_t *m_xcb = nullptr;
    uint m_root = 0;
    uint m_activeClient = 0;
    int m_screenW = 0, m_screenH = 0;
    int m_mouseX = 0, m_mouseY = 0;
    int m_activeIndex = -1;
    int m_snapZone = 0;
    bool m_started = false;
    bool m_hasRandr = false;       uint8_t m_randrEventBase = 0;
    bool m_hasScreensaver = false; uint8_t m_screensaverEventBase = 0;
    QList<uint8_t> m_kcF4, m_kcSuper;              // W15: keycodes of the grabbed keys
    bool m_superDown = false, m_superUsed = false; // W15: Super held / another key pressed meanwhile
    bool m_hasXi2 = false;         uint8_t m_xiOpcode = 0;
    AnimPolicy *m_animPolicy = nullptr;
    QTimer m_pointerTimer;        // 16 ms fallback poll when XInput2 is missing
    QTimer m_idleTimer;           // 2000 ms user-idle poll
    QTimer m_pointerCoalesce;     // W9
    bool m_userInputIdle = false;
    qint64 m_screensaverTimeoutMs = 0;
    bool m_screensaverIdle = false;
    QList<WindowEntry> m_windows;
    int m_coveringCount = 0;
    bool m_coveringPending = false;
    QHash<uint, QObject *> m_frameObjects;   // client -> QML frame window
    QHash<uint, QString> m_tiers;            // pid -> last tier sent
    QHash<uint, uint> m_containerOf;         // client -> container
    QHash<uint, uint> m_clientOfContainer;   // container -> client
    QHash<uint, uint> m_frameOf;             // client -> frame X window
    QHash<uint, uint> m_clientOfFrame;       // frame -> client
    QHash<uint, int> m_wmUnmaps;             // W3: unmaps the WM itself caused, per client
    uint m_picomOwner = 0;
    uint m_currentDesktop = 0;
    uint m_wmCheckWindow = 0;

    // atoms
    uint m_aWmProtocols = 0, m_aWmDeleteWindow = 0, m_aWmChangeState = 0, m_aWmState = 0;
    uint m_aNetWmName = 0, m_aUtf8 = 0, m_aNetActiveWindow = 0, m_aNetSupported = 0;
    uint m_aNetWmState = 0, m_aStateMaxV = 0, m_aStateMaxH = 0, m_aStateHidden = 0;
    uint m_aCmS0 = 0, m_aNetWmPid = 0;
    uint m_aWindowType = 0, m_aTypeNormal = 0, m_aTypeDesktop = 0, m_aTypeDock = 0;
    uint m_aTypeDialog = 0, m_aTypeUtility = 0, m_aTypeToolbar = 0, m_aTypeSplash = 0;
    uint m_aTypePopupMenu = 0, m_aTypeTooltip = 0, m_aTypeNotification = 0;
    uint m_aTypeDropdownMenu = 0, m_aTypeMenu = 0, m_aTypeCombo = 0, m_aTypeDnd = 0;
    uint m_aNumberOfDesktops = 0, m_aCurrentDesktop = 0, m_aNetWmDesktop = 0;
    uint m_aNcdeMenus = 0, m_aNcdeMenuInvoke = 0;
    uint m_aClientList = 0, m_aSupportingWmCheck = 0;
};
