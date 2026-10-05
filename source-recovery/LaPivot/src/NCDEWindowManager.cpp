// NCDEWindowManager — see NCDEWindowManager.h for the design, the oracle sources and the W1..W13
// defect list. Every function below is the oracle's (decomp/NCDEWindowManager.c, same name)
// unless its comment says otherwise.
#include "NCDEWindowManager.h"

#include "AnimPolicy.h"
#include "GliaTalk.h"

#include <algorithm>

#include <QCoreApplication>
#include <QCursor>
#include <QGuiApplication>
#include <QProcess>
#include <QWindow>
#include <QtGui/qguiapplication_platform.h>

#include <xcb/randr.h>
#include <xcb/screensaver.h>
#include <xcb/shape.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xinput.h>

#include <cstdlib>
#include <cstring>

namespace {
// container/frame offsets around the client (oracle constants)
constexpr int kContX = 12, kContY = 32, kContW = 24, kContH = 58;     // container = client + these
constexpr int kFrameX = 24, kFrameY = 44, kFrameW = 48, kFrameH = 82; // QML frame = client + these
constexpr uint32_t kRootMask = XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT
                               | XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_PROPERTY_CHANGE;   // 0x780000
constexpr uint32_t kClientMask = XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_FOCUS_CHANGE
                                 | XCB_EVENT_MASK_PROPERTY_CHANGE;                              // 0x620000
constexpr int kDesktops = 4;

// FUN_00291390: windows that draw their own chrome and must not be framed
bool isSelfDecoratedApp(const QString &appId)
{
    return appId == QLatin1String("steam") || appId == QLatin1String("steamwebhelper")
        || appId == QLatin1String("gamescope") || appId.startsWith(QLatin1String("steam_app_"));
}
} // namespace

NCDEWindowManager::NCDEWindowManager(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, &NCDEWindowManager::windowStateChanged, this, &NCDEWindowManager::scheduleCoveringRecount);
    connect(this, &NCDEWindowManager::countChanged, this, &NCDEWindowManager::scheduleCoveringRecount);
    m_pointerCoalesce.setSingleShot(true);
    m_pointerCoalesce.setInterval(16);
    connect(&m_pointerCoalesce, &QTimer::timeout, this, &NCDEWindowManager::pollPointer);
}

NCDEWindowManager::~NCDEWindowManager()
{
    // W13: the oracle never removed the filter; the application outlives this object in main()
    if (m_started)
        if (QCoreApplication *app = QCoreApplication::instance())
            app->removeNativeEventFilter(this);
}

// ---------------------------------------------------------------------------------- the model

int NCDEWindowManager::rowCount(const QModelIndex &) const
{
    return int(m_windows.size());
}

QVariant NCDEWindowManager::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (row < 0 || row >= m_windows.size())
        return {};
    const WindowEntry &e = m_windows[row];
    switch (role) {
    case WinIdRole:     return e.client;
    case XRole:         return e.x;
    case YRole:         return e.y;
    case WRole:         return e.w;
    case HRole:         return e.h;
    case NameRole:      return e.name;
    case AppIdRole:     return e.appId;
    case MinimizedRole: return e.minimized;
    case MaximizedRole: return e.maximized;
    case TitleRole:     return e.name.isEmpty() ? e.appId : e.name;
    case TiledRole:     return e.tiled;
    default:            return {};
    }
}

QHash<int, QByteArray> NCDEWindowManager::roleNames() const
{
    return {{WinIdRole, "winId"}, {XRole, "x"}, {YRole, "y"}, {WRole, "w"}, {HRole, "h"},
            {NameRole, "name"}, {AppIdRole, "appId"}, {MinimizedRole, "minimized"},
            {MaximizedRole, "maximized"}, {TitleRole, "title"}, {TiledRole, "tiled"}};
}

void NCDEWindowManager::rowChanged(int row)
{
    const QModelIndex i = index(row, 0);
    emit dataChanged(i, i);
}

QString NCDEWindowManager::activeAppMenus() const
{
    if (m_activeIndex >= 0 && m_activeIndex < m_windows.size())
        return m_windows[m_activeIndex].menus;
    return {};
}

void NCDEWindowManager::invokeAppMenu(int id)
{
    if (id > 0 && m_activeIndex >= 0 && m_activeIndex < m_windows.size())
        GliaTalkProto::sendInvoke(m_xcb, m_windows[m_activeIndex].client, quint32(id));
}

void NCDEWindowManager::setSnapZone(int z)
{
    if (z == m_snapZone)
        return;
    m_snapZone = z;
    emit snapZoneChanged();
}

void NCDEWindowManager::setWindowType(uint win, uint typeAtom)
{
    if (!m_xcb || !win || !typeAtom || !m_aWindowType)
        return;
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, win, m_aWindowType, XCB_ATOM_ATOM, 32, 1, &typeAtom);
    xcb_flush(m_xcb);
}

int NCDEWindowManager::rowForClient(uint c) const
{
    for (int i = 0; i < m_windows.size(); ++i)
        if (m_windows[i].client == c)
            return i;
    return -1;
}

uint NCDEWindowManager::winIdForName(const QString &n) const
{
    for (const WindowEntry &e : m_windows)
        if (e.name == n || e.appId == n)
            return e.client;
    return 0;
}

bool NCDEWindowManager::hasWindowForName(const QString &n) const
{
    return winIdForName(n) != 0;
}

bool NCDEWindowManager::isMinimizedForName(const QString &n) const
{
    for (const WindowEntry &e : m_windows)
        if (e.name == n || e.appId == n)
            return e.minimized;
    return false;
}

bool NCDEWindowManager::isActiveForName(const QString &n) const
{
    const uint w = winIdForName(n);
    return m_activeClient != 0 && w == m_activeClient;
}

bool NCDEWindowManager::isMaximizedForName(const QString &n) const
{
    for (const WindowEntry &e : m_windows)
        if (e.name == n || e.appId == n)
            return e.maximized;
    return false;
}

// ---------------------------------------------------------------------------------- window verbs

void NCDEWindowManager::activateWindow(uint w)
{
    if (!m_xcb || !w)
        return;
    const int row = rowForClient(w);
    if (row >= 0 && m_windows[row].minimized) {
        setMin(w, false);
        if (auto *fw = qobject_cast<QWindow *>(m_frameObjects.value(w)))
            fw->setVisible(true);
        if (const uint c = m_containerOf.value(w))
            xcb_map_window(m_xcb, c);
        if (const uint f = m_frameOf.value(w))
            xcb_map_window(m_xcb, f);
        xcb_map_window(m_xcb, w);
        xcb_flush(m_xcb);
    }
    const uint container = m_containerOf.value(w);
    const uint frame = m_frameOf.value(w);
    const uint32_t above = XCB_STACK_MODE_ABOVE;
    if (!container) {
        xcb_configure_window(m_xcb, w, XCB_CONFIG_WINDOW_STACK_MODE, &above);
    } else {
        xcb_configure_window(m_xcb, container, XCB_CONFIG_WINDOW_STACK_MODE, &above);
        if (frame) {
            const uint32_t v[2] = {container, XCB_STACK_MODE_ABOVE};
            xcb_configure_window(m_xcb, frame, XCB_CONFIG_WINDOW_SIBLING | XCB_CONFIG_WINDOW_STACK_MODE, v);
        }
    }
    xcb_set_input_focus(m_xcb, XCB_INPUT_FOCUS_POINTER_ROOT, w, XCB_CURRENT_TIME);
    if (m_aNetActiveWindow)
        xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_root, m_aNetActiveWindow, XCB_ATOM_WINDOW, 32, 1, &w);
    xcb_flush(m_xcb);
    m_activeClient = w;
    setActiveIndex(rowForClient(w));
    // unconditional on purpose (oracle; wm-oracle-audit.md §4): QML re-raises its cursor overlay
    emit activeIndexChanged();
    emit activeAppMenusChanged();
}

// W3: an unmap the WM causes itself must not be read as the client withdrawing
void NCDEWindowManager::unmapByWm(uint win)
{
    xcb_get_window_attributes_reply_t *a =
        xcb_get_window_attributes_reply(m_xcb, xcb_get_window_attributes(m_xcb, win), nullptr);
    const bool mapped = a && a->map_state != XCB_MAP_STATE_UNMAPPED;
    std::free(a);
    if (!mapped)
        return;
    if (rowForClient(win) >= 0)
        ++m_wmUnmaps[win];
    xcb_unmap_window(m_xcb, win);
}

void NCDEWindowManager::minimizeWindow(uint w)
{
    setMin(w, true);
    if (auto *fw = qobject_cast<QWindow *>(m_frameObjects.value(w)))
        fw->setVisible(false);
    if (!m_xcb)
        return;
    if (const uint c = m_containerOf.value(w))
        xcb_unmap_window(m_xcb, c);
    if (const uint f = m_frameOf.value(w))
        xcb_unmap_window(m_xcb, f);
    unmapByWm(w);
    xcb_flush(m_xcb);
}

void NCDEWindowManager::unminimizeWindow(uint w)
{
    setMin(w, false, true);
    if (auto *fw = qobject_cast<QWindow *>(m_frameObjects.value(w)))
        fw->setVisible(true);
    if (!m_xcb)
        return;
    if (const uint c = m_containerOf.value(w))
        xcb_map_window(m_xcb, c);
    if (const uint f = m_frameOf.value(w))
        xcb_map_window(m_xcb, f);
    xcb_map_window(m_xcb, w);
    xcb_flush(m_xcb);
    activateWindow(w);
}

void NCDEWindowManager::moveWindow(uint w, int x, int y)
{
    if (!m_xcb)
        return;
    setGeom(w, x, y, 0, 0, false, true);
    const uint container = m_containerOf.value(w);
    if (!container) {
        const uint32_t v[2] = {uint32_t(x), uint32_t(y)};
        xcb_configure_window(m_xcb, w, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, v);
    } else {
        const uint32_t cv[2] = {uint32_t(x - kContX), uint32_t(y - kContY)};
        xcb_configure_window(m_xcb, container, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, cv);
        if (const uint frame = m_frameOf.value(w)) {
            const uint32_t fv[2] = {uint32_t(x - kFrameX), uint32_t(y - kFrameY)};
            xcb_configure_window(m_xcb, frame, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, fv);
        }
        const int row = rowForClient(w);
        if (row >= 0)
            sendSyntheticConfigure(w, m_windows[row]);   // W4
    }
    xcb_flush(m_xcb);
}

void NCDEWindowManager::resizeWindow(uint w, int wid, int hgt)
{
    if (!m_xcb)
        return;
    setGeom(w, 0, 0, wid, hgt, true, false);
    const uint32_t v[2] = {uint32_t(wid), uint32_t(hgt)};
    xcb_configure_window(m_xcb, w, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, v);
    if (const uint container = m_containerOf.value(w)) {
        const uint32_t cv[2] = {uint32_t(wid + kContW), uint32_t(hgt + kContH)};
        xcb_configure_window(m_xcb, container, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, cv);
        if (const uint frame = m_frameOf.value(w)) {
            const uint32_t fv[2] = {uint32_t(wid + kFrameW), uint32_t(hgt + kFrameH)};
            xcb_configure_window(m_xcb, frame, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, fv);
            setFrameInputRegion(frame, wid + kFrameW, hgt + kFrameH);
        }
    }
    xcb_flush(m_xcb);
}

void NCDEWindowManager::moveTiledWindow(uint w, int x, int y, int wid, int hgt)
{
    moveWindow(w, x, y);
    resizeWindow(w, wid, hgt);
}

void NCDEWindowManager::setTiled(uint w, bool t)
{
    const int row = rowForClient(w);
    if (row < 0 || m_windows[row].tiled == t)
        return;
    m_windows[row].tiled = t;
    rowChanged(row);
}

bool NCDEWindowManager::isMaximized(uint w) const
{
    const int row = rowForClient(w);
    return row >= 0 && m_windows[row].maximized;
}

void NCDEWindowManager::setMaximized(uint client, bool maximized)
{
    if (!m_xcb)
        return;
    const int row = rowForClient(client);
    if (row >= 0 && m_windows[row].maximized != maximized) {
        m_windows[row].maximized = maximized;
        rowChanged(row);
        emit windowStateChanged();
    }
    if (maximized)
        editNetWmState(client, {m_aStateMaxV, m_aStateMaxH}, {});   // W14: add, never replace
    else
        editNetWmState(client, {}, {m_aStateMaxV, m_aStateMaxH});
    xcb_flush(m_xcb);
}

bool NCDEWindowManager::supportsProtocol(uint win, uint atom) const
{
    xcb_icccm_get_wm_protocols_reply_t p;
    if (!xcb_icccm_get_wm_protocols_reply(m_xcb, xcb_icccm_get_wm_protocols(m_xcb, win, m_aWmProtocols), &p, nullptr))
        return false;
    bool found = false;
    for (uint32_t i = 0; i < p.atoms_len; ++i)
        found = found || p.atoms[i] == atom;
    xcb_icccm_get_wm_protocols_reply_wipe(&p);
    return found;
}

void NCDEWindowManager::closeWindow(uint w)
{
    if (!m_xcb || !w)
        return;
    if (m_aWmProtocols && m_aWmDeleteWindow && supportsProtocol(w, m_aWmDeleteWindow)) {   // W2
        xcb_client_message_event_t ev;
        std::memset(&ev, 0, sizeof ev);
        ev.response_type = XCB_CLIENT_MESSAGE;
        ev.format = 32;
        ev.window = w;
        ev.type = m_aWmProtocols;
        ev.data.data32[0] = m_aWmDeleteWindow;
        ev.data.data32[1] = XCB_CURRENT_TIME;
        xcb_send_event(m_xcb, 0, w, XCB_EVENT_MASK_NO_EVENT, reinterpret_cast<const char *>(&ev));
    } else {
        xcb_kill_client(m_xcb, w);
    }
    xcb_flush(m_xcb);
}

void NCDEWindowManager::systemCommand(const QString &cmd)
{
    QProcess::startDetached(QStringLiteral("/bin/sh"), {QStringLiteral("-c"), cmd});
}

// ---------------------------------------------------------------------------------- frames

void NCDEWindowManager::registerFrameWindowQml(uint client, QObject *frame)
{
    m_frameObjects.insert(client, frame);
    auto *w = qobject_cast<QWindow *>(frame);
    if (!w)
        return;
    const uint frameId = uint(w->winId());
    if (!frameId || m_containerOf.contains(client))
        return;
    const int row = rowForClient(client);
    if (row >= 0 && isSelfDecoratedApp(m_windows[row].appId))
        registerGameFrame(client, frameId, row);
    else
        registerFrameWindow(client, frameId);
}

// FUN_00291390's game branch: client mapped as-is, the frame made invisible and click-through
void NCDEWindowManager::registerGameFrame(uint client, uint frame, int row)
{
    const WindowEntry e = m_windows[row];
    m_frameOf.insert(client, frame);
    m_clientOfFrame.insert(frame, client);
    xcb_map_window(m_xcb, client);
    const uint32_t g[4] = {uint32_t(e.x), uint32_t(e.y), uint32_t(e.w), uint32_t(e.h)};
    xcb_configure_window(m_xcb, frame, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y
                         | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, g);
    const uint32_t st[2] = {client, XCB_STACK_MODE_ABOVE};
    xcb_configure_window(m_xcb, frame, XCB_CONFIG_WINDOW_SIBLING | XCB_CONFIG_WINDOW_STACK_MODE, st);
    xcb_shape_rectangles(m_xcb, XCB_SHAPE_SO_SET, XCB_SHAPE_SK_INPUT, XCB_CLIP_ORDERING_UNSORTED, frame, 0, 0, 0, nullptr);
    xcb_shape_rectangles(m_xcb, XCB_SHAPE_SO_SET, XCB_SHAPE_SK_BOUNDING, XCB_CLIP_ORDERING_UNSORTED, frame, 0, 0, 0, nullptr);
    setWmClass(frame, "ncde-frame");
    xcb_flush(m_xcb);
    activateWindow(client);
}

void NCDEWindowManager::registerFrameWindow(uint client, uint frame)
{
    if (!m_started || !m_xcb || !client || !frame)
        return;
    const int row = rowForClient(client);
    if (row < 0)
        return;
    const WindowEntry e = m_windows[row];
    m_frameOf.insert(client, frame);
    m_clientOfFrame.insert(frame, client);
    const uint container = createContainer(e.x - kContX, e.y - kContY, e.w + kContW, e.h + kContH, false);
    m_containerOf.insert(client, container);
    m_clientOfContainer.insert(container, client);
    xcb_change_save_set(m_xcb, XCB_SET_MODE_INSERT, client);
    if (isViewable(client))
        ++m_wmUnmaps[client];   // W3: reparenting a mapped window unmaps it once
    xcb_reparent_window(m_xcb, client, container, kContX, kContY);
    const uint32_t size[2] = {uint32_t(e.w), uint32_t(e.h)};
    xcb_configure_window(m_xcb, client, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, size);
    xcb_map_window(m_xcb, client);
    xcb_map_window(m_xcb, container);
    const uint32_t st[2] = {container, XCB_STACK_MODE_ABOVE};
    xcb_configure_window(m_xcb, frame, XCB_CONFIG_WINDOW_SIBLING | XCB_CONFIG_WINDOW_STACK_MODE, st);
    setFrameInputRegion(frame, e.w + kFrameW, e.h + kFrameH);
    setWmClass(frame, "ncde-frame");
    xcb_flush(m_xcb);
    activateWindow(client);
}

void NCDEWindowManager::destroyFrameWindow(uint client)
{
    m_frameObjects.remove(client);
    if (!m_xcb)
        return;
    if (const uint container = m_containerOf.take(client)) {
        m_clientOfContainer.remove(container);
        const int row = rowForClient(client);
        if (row >= 0) {   // W11: only a live, still-managed client goes back to the root
            xcb_reparent_window(m_xcb, client, m_root, int16_t(m_windows[row].x), int16_t(m_windows[row].y));
            xcb_change_save_set(m_xcb, XCB_SET_MODE_DELETE, client);
        }
        xcb_destroy_window(m_xcb, container);
    }
    if (const uint frame = m_frameOf.take(client))
        m_clientOfFrame.remove(frame);
    xcb_flush(m_xcb);
}

uint NCDEWindowManager::findArgbVisual() const
{
    xcb_screen_iterator_t s = xcb_setup_roots_iterator(xcb_get_setup(m_xcb));
    if (!s.rem)
        return 0;
    for (xcb_depth_iterator_t d = xcb_screen_allowed_depths_iterator(s.data); d.rem; xcb_depth_next(&d)) {
        if (d.data->depth != 32)
            continue;
        for (xcb_visualtype_iterator_t v = xcb_depth_visuals_iterator(d.data); v.rem; xcb_visualtype_next(&v))
            if (v.data->_class == XCB_VISUAL_CLASS_TRUE_COLOR)
                return v.data->visual_id;
    }
    return 0;
}

void NCDEWindowManager::setWmClass(uint win, const char *cls)
{
    QByteArray v(cls);
    v.append('\0');
    v.append(cls);
    v.append('\0');
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, win, XCB_ATOM_WM_CLASS, XCB_ATOM_STRING, 8,
                        uint32_t(v.size()), v.constData());
}

uint NCDEWindowManager::createContainer(int x, int y, int w, int h, bool argb)
{
    const uint id = xcb_generate_id(m_xcb);
    xcb_screen_iterator_t s = xcb_setup_roots_iterator(xcb_get_setup(m_xcb));
    uint visual = s.rem ? s.data->root_visual : 0;
    uint8_t depth = XCB_COPY_FROM_PARENT;
    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t values[4] = {0, 0, XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY, 0};
    if (argb) {
        if (const uint v = findArgbVisual()) {
            depth = 32;
            const uint cmap = xcb_generate_id(m_xcb);
            xcb_create_colormap(m_xcb, XCB_COLORMAP_ALLOC_NONE, cmap, m_root, v);
            mask |= XCB_CW_COLORMAP;
            values[3] = cmap;
            visual = v;
        }
    }
    xcb_create_window(m_xcb, depth, id, m_root, int16_t(x), int16_t(y), uint16_t(w), uint16_t(h), 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, visual, mask, values);
    setWmClass(id, "ncde-container");
    return id;
}

// the frame takes input only on its decoration ring; the client area and the outer glow pass through
void NCDEWindowManager::setFrameInputRegion(uint frame, int w, int h)
{
    const xcb_rectangle_t r[4] = {
        {12, 12, uint16_t(w - 24), 32},                          // title bar
        {12, 44, 12, uint16_t(h - 82)},                          // left edge
        {int16_t(w - 24), 44, 12, uint16_t(h - 82)},             // right edge
        {12, int16_t(h - 38), uint16_t(w - 24), 26},             // bottom edge
    };
    xcb_shape_rectangles(m_xcb, XCB_SHAPE_SO_SET, XCB_SHAPE_SK_INPUT, XCB_CLIP_ORDERING_UNSORTED, frame, 0, 0, 4, r);
}

// ---------------------------------------------------------------------------------- state helpers

void NCDEWindowManager::setActiveIndex(int i)
{
    if (i == m_activeIndex)
        return;
    m_activeIndex = i;
    emit activeIndexChanged();
    emit activeAppMenusChanged();
    emitTierUpdates();
}

void NCDEWindowManager::setMin(uint client, bool on, bool emitTiers)
{
    const int row = rowForClient(client);
    if (row < 0)
        return;
    m_windows[row].minimized = on;
    setWmState(client, on ? XCB_ICCCM_WM_STATE_ICONIC : XCB_ICCCM_WM_STATE_NORMAL);   // W14
    if (on)
        editNetWmState(client, {m_aStateHidden}, {});
    else
        editNetWmState(client, {}, {m_aStateHidden});
    rowChanged(row);
    emit windowStateChanged();
    if (emitTiers)
        emitTierUpdates();
}

// W14: ICCCM 4.1.3.1 — WM_STATE {state, icon window}; the WM owns it, the client only reads it
void NCDEWindowManager::setWmState(uint client, uint32_t state)
{
    if (!m_xcb || !m_aWmState)
        return;
    const uint32_t v[2] = {state, XCB_WINDOW_NONE};
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, client, m_aWmState, m_aWmState, 32, 2, v);
}

// W14: add/remove atoms in the client's _NET_WM_STATE, keeping every other state it holds
void NCDEWindowManager::editNetWmState(uint client, std::initializer_list<uint32_t> add,
                                       std::initializer_list<uint32_t> remove)
{
    if (!m_xcb || !m_aNetWmState)
        return;
    QList<uint32_t> st;
    if (xcb_get_property_reply_t *r = xcb_get_property_reply(
            m_xcb, xcb_get_property(m_xcb, 0, client, m_aNetWmState, XCB_ATOM_ATOM, 0, 32), nullptr)) {
        const auto *v = static_cast<const uint32_t *>(xcb_get_property_value(r));
        const int n = xcb_get_property_value_length(r) / 4;
        for (int i = 0; i < n; ++i)
            if (v[i] && !std::count(remove.begin(), remove.end(), v[i]) && !st.contains(v[i]))
                st.append(v[i]);
        std::free(r);
    }
    for (const uint32_t a : add)
        if (a && !st.contains(a))
            st.append(a);
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, client, m_aNetWmState, XCB_ATOM_ATOM, 32,
                        uint32_t(st.size()), st.isEmpty() ? nullptr : st.constData());
}

// W1: keepPos/keepSize replace the oracle's "negative means unchanged"
void NCDEWindowManager::setGeom(uint client, int x, int y, int w, int h, bool keepPos, bool keepSize)
{
    const int row = rowForClient(client);
    if (row < 0)
        return;
    WindowEntry &e = m_windows[row];
    bool changed = false;
    if (!keepPos && (e.x != x || e.y != y)) {
        e.x = x;
        e.y = y;
        changed = true;
    }
    if (!keepSize && w >= 0 && h >= 0 && (e.w != w || e.h != h)) {
        e.w = w;
        e.h = h;
        changed = true;
    }
    if (changed)
        rowChanged(row);
}

// W12: one tier per process (foreground > background > hidden); the oracle walked windows and
// emitted per window, so a process with an active and an inactive window flipped every call
void NCDEWindowManager::emitTierUpdates()
{
    QHash<uint, int> best;   // pid -> 2 foreground, 1 background, 0 hidden
    for (int i = 0; i < m_windows.size(); ++i) {
        const WindowEntry &e = m_windows[i];
        if (!e.pid)
            continue;
        const int t = e.minimized ? 0 : (i == m_activeIndex ? 2 : 1);
        best[e.pid] = qMax(best.value(e.pid, 0), t);
    }
    static const QString names[3] = {QStringLiteral("hidden"), QStringLiteral("background"),
                                     QStringLiteral("foreground")};
    for (auto it = best.cbegin(); it != best.cend(); ++it) {
        const QString &tier = names[it.value()];
        auto old = m_tiers.find(it.key());
        if (old != m_tiers.end() && *old == tier)
            continue;
        m_tiers[it.key()] = tier;
        emit windowTierNeeded(it.key(), tier);
    }
}

void NCDEWindowManager::scheduleCoveringRecount()
{
    if (m_coveringPending)
        return;
    m_coveringPending = true;
    QTimer::singleShot(0, this, [this] {
        m_coveringPending = false;
        recomputeCoveringCount();
    });
}

bool NCDEWindowManager::isViewable(uint win) const
{
    xcb_get_window_attributes_reply_t *a =
        xcb_get_window_attributes_reply(m_xcb, xcb_get_window_attributes(m_xcb, win), nullptr);
    const bool v = a && a->map_state == XCB_MAP_STATE_VIEWABLE;
    std::free(a);
    return v;
}

void NCDEWindowManager::recomputeCoveringCount()
{
    int n = 0;
    for (const WindowEntry &e : m_windows)
        if (!e.minimized && e.maximized && (!m_xcb || isViewable(e.client)))
            ++n;
    if (n != m_coveringCount) {
        m_coveringCount = n;
        emit coveringCountChanged();
    }
}

void NCDEWindowManager::recomputeDesktopObscured()
{
    if (!m_animPolicy)
        return;
    bool obscured = false;
    for (const WindowEntry &e : m_windows)
        if (e.maximized && !e.minimized) {
            obscured = true;
            break;
        }
    m_animPolicy->setDesktopObscured(obscured);
}

void NCDEWindowManager::sendSyntheticConfigure(uint client, const WindowEntry &e)
{
    xcb_configure_notify_event_t ev;
    std::memset(&ev, 0, sizeof ev);
    ev.response_type = XCB_CONFIGURE_NOTIFY;
    ev.event = client;
    ev.window = client;
    ev.x = int16_t(e.x);
    ev.y = int16_t(e.y);
    ev.width = uint16_t(e.w);
    ev.height = uint16_t(e.h);
    xcb_send_event(m_xcb, 0, client, XCB_EVENT_MASK_STRUCTURE_NOTIFY, reinterpret_cast<const char *>(&ev));
}

void NCDEWindowManager::updateClientList()   // W7
{
    if (!m_xcb || !m_aClientList)
        return;
    QList<uint32_t> ids;
    ids.reserve(m_windows.size());
    for (const WindowEntry &e : m_windows)
        ids.append(e.client);
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_root, m_aClientList, XCB_ATOM_WINDOW, 32,
                        uint32_t(ids.size()), ids.isEmpty() ? nullptr : ids.constData());
}

// ---------------------------------------------------------------------------------- X properties

QString NCDEWindowManager::getWindowTitle(uint win) const
{
    if (!m_xcb || !win)
        return QStringLiteral("Window");
    xcb_get_property_reply_t *r = xcb_get_property_reply(
        m_xcb, xcb_get_property(m_xcb, 0, win, m_aNetWmName, m_aUtf8, 0, 256), nullptr);
    if (r && xcb_get_property_value_length(r) > 0) {
        const QString s = QString::fromUtf8(static_cast<const char *>(xcb_get_property_value(r)),
                                            xcb_get_property_value_length(r));
        std::free(r);
        return s;
    }
    std::free(r);
    r = xcb_get_property_reply(m_xcb, xcb_get_property(m_xcb, 0, win, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 0, 256), nullptr);
    if (r && xcb_get_property_value_length(r) > 0) {
        const QString s = QString::fromLatin1(static_cast<const char *>(xcb_get_property_value(r)),
                                              xcb_get_property_value_length(r));
        std::free(r);
        return s;
    }
    std::free(r);
    return QStringLiteral("Window");
}

QString NCDEWindowManager::getWindowClass(uint win) const
{
    if (!m_xcb || !win)
        return {};
    xcb_get_property_reply_t *r = xcb_get_property_reply(
        m_xcb, xcb_get_property(m_xcb, 0, win, XCB_ATOM_WM_CLASS, XCB_ATOM_STRING, 0, 256), nullptr);
    QString cls;
    if (r && xcb_get_property_value_length(r) > 0) {
        const QByteArray v(static_cast<const char *>(xcb_get_property_value(r)), xcb_get_property_value_length(r));
        const int nul = v.indexOf('\0');
        if (nul >= 0 && nul + 1 < v.size())
            cls = QString::fromLatin1(v.constData() + nul + 1);   // the class part, up to its NUL
        else
            cls = QString::fromLatin1(v);
    }
    std::free(r);
    return cls;
}

uint NCDEWindowManager::getWindowPid(uint win) const
{
    if (!m_xcb || !win)
        return 0;
    xcb_get_property_reply_t *r = xcb_get_property_reply(
        m_xcb, xcb_get_property(m_xcb, 0, win, m_aNetWmPid, XCB_ATOM_CARDINAL, 0, 1), nullptr);
    uint pid = 0;
    if (r && xcb_get_property_value_length(r) >= 4)
        pid = *static_cast<const uint32_t *>(xcb_get_property_value(r));
    std::free(r);
    return pid;
}

// W8: windows that are not application windows are mapped as they ask, never framed/maximized
bool NCDEWindowManager::isUnframedType(uint win) const
{
    xcb_get_property_reply_t *r = xcb_get_property_reply(
        m_xcb, xcb_get_property(m_xcb, 0, win, m_aWindowType, XCB_ATOM_ATOM, 0, 16), nullptr);
    bool unframed = false;
    if (r) {
        const auto *v = static_cast<const uint32_t *>(xcb_get_property_value(r));
        const int n = xcb_get_property_value_length(r) / 4;
        for (int i = 0; i < n; ++i) {
            const uint t = v[i];
            if (t == m_aTypeNormal || t == m_aTypeDialog || t == m_aTypeUtility || t == m_aTypeToolbar)
                break;   // first recognised type wins (EWMH preference order)
            if (t && (t == m_aTypeDock || t == m_aTypeDesktop || t == m_aTypeSplash || t == m_aTypeNotification
                      || t == m_aTypeTooltip || t == m_aTypePopupMenu || t == m_aTypeDropdownMenu
                      || t == m_aTypeMenu || t == m_aTypeCombo || t == m_aTypeDnd)) {
                unframed = true;
                break;
            }
        }
        std::free(r);
    }
    return unframed;
}

// ---------------------------------------------------------------------------------- manage

void NCDEWindowManager::manage(uint win)
{
    if (rowForClient(win) >= 0)
        return;
    WindowEntry e;
    e.client = win;
    if (xcb_get_geometry_reply_t *g = xcb_get_geometry_reply(m_xcb, xcb_get_geometry(m_xcb, win), nullptr)) {
        e.w = g->width;
        e.h = g->height;
        std::free(g);
    }
    if (e.w < 2 || e.h < 2) {
        e.w = 800;
        e.h = 560;
    }
    e.w = qMax(e.w, 200);
    e.h = qMax(e.h, 100);
    // a window with a real maximum size smaller than the screen keeps its size; all others open max
    bool fixedSize = false;
    xcb_size_hints_t hints;
    if (xcb_icccm_get_wm_normal_hints_reply(m_xcb, xcb_icccm_get_wm_normal_hints(m_xcb, win), &hints, nullptr)
        && (hints.flags & XCB_ICCCM_SIZE_HINT_P_MAX_SIZE) && hints.max_width > 0 && hints.max_height > 0
        && hints.max_width < m_screenW && hints.max_height < m_screenH)
        fixedSize = true;
    if (!fixedSize) {
        e.w = m_screenW - kContW;
        e.h = m_screenH - kContH;
        e.maximized = true;
    }
    e.x = kContX;
    e.y = kContY;
    if (e.maximized)
        editNetWmState(win, {m_aStateMaxV, m_aStateMaxH}, {m_aStateHidden});   // W14
    else
        editNetWmState(win, {}, {m_aStateHidden});
    setWmState(win, XCB_ICCCM_WM_STATE_NORMAL);                                // W14
    xcb_change_window_attributes(m_xcb, win, XCB_CW_EVENT_MASK, &kClientMask);
    e.name = getWindowTitle(win);
    e.appId = getWindowClass(win);
    e.pid = getWindowPid(win);
    e.menus = GliaTalkProto::readMenus(m_xcb, win);
    e.desktop = m_currentDesktop;
    if (m_aNetWmDesktop)
        xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, win, m_aNetWmDesktop, XCB_ATOM_CARDINAL, 32, 1, &m_currentDesktop);

    const int row = int(m_windows.size());
    beginInsertRows(QModelIndex(), row, row);
    m_windows.append(e);
    endInsertRows();
    updateClientList();
    xcb_flush(m_xcb);
    emit countChanged();
    emit windowAdded(e.client, e.x, e.y, e.w, e.h, e.name, e.appId);
    emit anyWindowMapped();
    emitTierUpdates();
}

void NCDEWindowManager::scanExisting()
{
    xcb_query_tree_reply_t *tree = xcb_query_tree_reply(m_xcb, xcb_query_tree(m_xcb, m_root), nullptr);
    if (!tree)
        return;
    const xcb_window_t *kids = xcb_query_tree_children(tree);
    const int n = xcb_query_tree_children_length(tree);
    for (int i = 0; i < n; ++i) {
        xcb_get_window_attributes_reply_t *a =
            xcb_get_window_attributes_reply(m_xcb, xcb_get_window_attributes(m_xcb, kids[i]), nullptr);
        if (a && a->map_state == XCB_MAP_STATE_VIEWABLE && !a->override_redirect && !isUnframedType(kids[i]))
            manage(kids[i]);
        std::free(a);
    }
    std::free(tree);
}

void NCDEWindowManager::unmanage(uint client, bool clientAlive)
{
    const int row = rowForClient(client);
    if (row < 0)
        return;
    if (m_xcb) {
        if (const uint frame = m_frameOf.take(client)) {
            m_clientOfFrame.remove(frame);
            xcb_unmap_window(m_xcb, frame);
        }
        if (const uint container = m_containerOf.take(client)) {
            m_clientOfContainer.remove(container);
            if (clientAlive) {   // W3: a withdrawn client goes back to the root, unmapped
                setWmState(client, XCB_ICCCM_WM_STATE_WITHDRAWN);   // W14
                xcb_reparent_window(m_xcb, client, m_root, int16_t(m_windows[row].x), int16_t(m_windows[row].y));
                xcb_change_save_set(m_xcb, XCB_SET_MODE_DELETE, client);
            }
            xcb_unmap_window(m_xcb, container);
            xcb_destroy_window(m_xcb, container);
        }
        xcb_flush(m_xcb);
    }
    m_frameObjects.remove(client);
    m_wmUnmaps.remove(client);
    const uint pid = m_windows[row].pid;
    beginRemoveRows(QModelIndex(), row, row);
    m_windows.removeAt(row);
    endRemoveRows();
    if (m_activeIndex == row) {
        m_activeIndex = -1;
        m_activeClient = 0;
    } else if (m_activeIndex > row) {
        --m_activeIndex;   // the active window's row moved up
    }
    updateClientList();
    emit countChanged();
    emit windowRemoved(client);
    if (pid)
        emit windowClosed(pid);
    for (int i = int(m_windows.size()) - 1; i >= 0; --i)
        if (!m_windows[i].minimized) {
            activateWindow(m_windows[i].client);
            return;
        }
    emit activeIndexChanged();
    emit activeAppMenusChanged();
}

void NCDEWindowManager::onDestroy(uint win)
{
    unmanage(win, false);
}

void NCDEWindowManager::onUnmapNotify(const xcb_unmap_notify_event_t *ev)   // W3
{
    const bool synthetic = ev->response_type & 0x80;
    if (!synthetic && ev->event != ev->window)
        return;   // the same unmap seen through the container's/root's substructure mask
    const uint win = ev->window;
    if (rowForClient(win) < 0)
        return;
    if (!synthetic) {
        auto it = m_wmUnmaps.find(win);
        if (it != m_wmUnmaps.end() && *it > 0) {
            if (--*it == 0)
                m_wmUnmaps.erase(it);
            return;
        }
    }
    unmanage(win, true);
}

void NCDEWindowManager::onConfigureRequest(const xcb_configure_request_event_t *ev)
{
    const int row = rowForClient(ev->window);
    const uint container = m_containerOf.value(ev->window);
    const uint16_t mask = ev->value_mask;
    uint16_t sendMask = 0;
    uint32_t values[5];
    int n = 0;
    if (!container) {   // before framing (or a game) the client places itself
        if (mask & XCB_CONFIG_WINDOW_X) { sendMask |= XCB_CONFIG_WINDOW_X; values[n++] = uint32_t(ev->x); }
        if (mask & XCB_CONFIG_WINDOW_Y) { sendMask |= XCB_CONFIG_WINDOW_Y; values[n++] = uint32_t(ev->y); }
    }
    const bool wantW = mask & XCB_CONFIG_WINDOW_WIDTH;
    const bool wantH = mask & XCB_CONFIG_WINDOW_HEIGHT;
    // a maximized window keeps its size
    bool refused = false;
    if (row >= 0 && (wantW || wantH) && m_windows[row].maximized) {
        const int rw = wantW ? ev->width : m_windows[row].w;
        const int rh = wantH ? ev->height : m_windows[row].h;
        refused = rw != m_windows[row].w || rh != m_windows[row].h;
    }
    if (wantW) { sendMask |= XCB_CONFIG_WINDOW_WIDTH;  values[n++] = refused ? uint32_t(m_windows[row].w) : ev->width; }
    if (wantH) { sendMask |= XCB_CONFIG_WINDOW_HEIGHT; values[n++] = refused ? uint32_t(m_windows[row].h) : ev->height; }
    if (mask & XCB_CONFIG_WINDOW_BORDER_WIDTH) {
        sendMask |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
        values[n++] = ev->border_width;
    }
    xcb_configure_window(m_xcb, ev->window, sendMask, values);
    xcb_flush(m_xcb);
    if (row < 0)
        return;
    WindowEntry &e = m_windows[row];
    if (!container) {
        if (mask & XCB_CONFIG_WINDOW_X) e.x = ev->x;
        if (mask & XCB_CONFIG_WINDOW_Y) e.y = ev->y;
    }
    if (!refused) {
        if (wantW) e.w = ev->width;
        if (wantH) e.h = ev->height;
    }
    if ((wantW || wantH) && container) {
        const uint32_t cv[2] = {uint32_t(e.w + kContW), uint32_t(e.h + kContH)};
        xcb_configure_window(m_xcb, container, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, cv);
        if (const uint frame = m_frameOf.value(ev->window))
            setFrameInputRegion(frame, e.w + kFrameW, e.h + kFrameH);
        xcb_flush(m_xcb);
    }
    rowChanged(row);
    // ICCCM 4.1.5: a framed client whose move was ignored, or whose resize was refused (W4),
    // is told where it really is
    if (container && ((mask & (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y)) || refused)) {
        sendSyntheticConfigure(ev->window, e);
        xcb_flush(m_xcb);
    }
}

void NCDEWindowManager::onPropertyNotify(uint win, uint atom)
{
    const int row = rowForClient(win);
    if (row < 0)
        return;
    bool changed = false;
    if (atom == m_aNetWmName || atom == XCB_ATOM_WM_NAME) {
        const QString t = getWindowTitle(win);
        if (t != m_windows[row].name) {
            m_windows[row].name = t;
            changed = true;
        }
    } else if (atom == XCB_ATOM_WM_CLASS) {
        const QString c = getWindowClass(win);
        if (c != m_windows[row].appId) {
            m_windows[row].appId = c;
            changed = true;
        }
    } else if (atom == m_aNcdeMenus) {
        const QString m = GliaTalkProto::readMenus(m_xcb, win);
        if (m != m_windows[row].menus) {
            m_windows[row].menus = m;
            if (row == m_activeIndex)
                emit activeAppMenusChanged();
        }
    }
    if (changed) {
        rowChanged(row);
        emit windowStateChanged();
    }
}

void NCDEWindowManager::onClientMessage(const xcb_client_message_event_t *ev)
{
    if (ev->format != 32)
        return;
    if (ev->type == m_aCurrentDesktop) {
        switchDesktop(int(ev->data.data32[0]));
        return;
    }
    const uint win = ev->window;
    const int row = rowForClient(win);
    if (row < 0)
        return;
    if (ev->type == m_aWmChangeState) {                                  // W5
        if (ev->data.data32[0] == XCB_ICCCM_WM_STATE_ICONIC && !m_windows[row].minimized)
            minimizeWindow(win);
    } else if (ev->type == m_aNetWmState) {                              // W5
        const uint32_t action = ev->data.data32[0];   // 0 remove, 1 add, 2 toggle
        if (ev->data.data32[1] != m_aStateHidden && ev->data.data32[2] != m_aStateHidden)
            return;
        const bool hide = action == 1 || (action == 2 && !m_windows[row].minimized);
        if (hide && !m_windows[row].minimized)
            minimizeWindow(win);
        else if (!hide && m_windows[row].minimized)
            unminimizeWindow(win);
    } else if (ev->type == m_aNetActiveWindow) {                         // W6
        if (m_windows[row].minimized)
            unminimizeWindow(win);
        else
            activateWindow(win);
    }
}

void NCDEWindowManager::onFocusIn(uint win)
{
    if (win == m_activeClient)
        return;
    const int row = rowForClient(win);
    if (row < 0)
        return;   // W10
    if (m_windows[row].minimized && !isViewable(win))
        return;
    m_activeClient = win;
    activateWindow(win);
}

void NCDEWindowManager::onRandRScreenChange(int w, int h)
{
    if (w == 0 || h == 0 || (w == m_screenW && h == m_screenH))
        return;
    m_screenW = w;
    m_screenH = h;
    const QList<WindowEntry> snapshot = m_windows;
    for (const WindowEntry &e : snapshot) {
        if (e.minimized)
            continue;
        const int nx = qBound(0, e.x, qMax(w - e.w, 0));
        const int ny = qBound(32, e.y, qMax(h - e.h, 32));
        if (nx != e.x || ny != e.y)
            moveWindow(e.client, nx, ny);
    }
    emit screenConfigChanged(w, h);
}

void NCDEWindowManager::switchDesktop(int target)
{
    if (!m_xcb || target < 0 || target >= kDesktops || uint(target) == m_currentDesktop)
        return;
    m_currentDesktop = uint(target);
    if (m_aCurrentDesktop)
        xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_root, m_aCurrentDesktop, XCB_ATOM_CARDINAL, 32, 1, &m_currentDesktop);
    const QList<WindowEntry> snapshot = m_windows;
    for (const WindowEntry &e : snapshot) {
        if (e.minimized)
            continue;
        const uint c = m_containerOf.value(e.client);
        const uint f = m_frameOf.value(e.client);
        if (e.desktop == m_currentDesktop) {
            if (c) xcb_map_window(m_xcb, c);
            if (f) xcb_map_window(m_xcb, f);
            xcb_map_window(m_xcb, e.client);
        } else {
            if (c) xcb_unmap_window(m_xcb, c);
            if (f) xcb_unmap_window(m_xcb, f);
            unmapByWm(e.client);
        }
    }
    xcb_flush(m_xcb);
}

void NCDEWindowManager::watchPicomOwner()
{
    if (!m_xcb || !m_aCmS0)
        return;
    xcb_get_selection_owner_reply_t *r =
        xcb_get_selection_owner_reply(m_xcb, xcb_get_selection_owner(m_xcb, m_aCmS0), nullptr);
    m_picomOwner = r ? r->owner : 0;
    std::free(r);
    if (m_picomOwner) {
        const uint32_t mask = XCB_EVENT_MASK_STRUCTURE_NOTIFY;
        xcb_change_window_attributes(m_xcb, m_picomOwner, XCB_CW_EVENT_MASK, &mask);
        xcb_flush(m_xcb);
    }
}

void NCDEWindowManager::onPicomDied()
{
    m_picomOwner = 0;
    QTimer::singleShot(800, this, [this] { watchPicomOwner(); });
}

// ---------------------------------------------------------------------------------- events

// W15: passive grabs on the root for the shell's global keys
void NCDEWindowManager::grabGlobalKeys()
{
    if (!m_xcb)
        return;
    xcb_ungrab_key(m_xcb, XCB_GRAB_ANY, m_root, XCB_MOD_MASK_ANY);
    m_kcF4.clear();
    m_kcSuper.clear();
    xcb_key_symbols_t *syms = xcb_key_symbols_alloc(m_xcb);
    if (!syms)
        return;
    const auto codes = [syms](xcb_keysym_t sym) {
        QList<uint8_t> out;
        if (xcb_keycode_t *kc = xcb_key_symbols_get_keycode(syms, sym)) {
            for (xcb_keycode_t *k = kc; *k != XCB_NO_SYMBOL; ++k)
                if (!out.contains(*k))
                    out.append(*k);
            std::free(kc);
        }
        return out;
    };
    m_kcF4 = codes(0xffc1);                         // XK_F4
    m_kcSuper = codes(0xffeb) + codes(0xffec);      // XK_Super_L, XK_Super_R
    xcb_key_symbols_free(syms);
    // the grab must hold whatever the Caps Lock / Num Lock state is
    static const uint16_t locks[] = {0, XCB_MOD_MASK_LOCK, XCB_MOD_MASK_2, XCB_MOD_MASK_LOCK | XCB_MOD_MASK_2};
    for (const uint16_t lock : locks) {
        for (const uint8_t kc : std::as_const(m_kcF4))
            xcb_grab_key(m_xcb, 1, m_root, XCB_MOD_MASK_1 | lock, kc, XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
        for (const uint8_t kc : std::as_const(m_kcSuper))
            xcb_grab_key(m_xcb, 1, m_root, lock, kc, XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
    }
    xcb_flush(m_xcb);
}

// W15: true = the key was the shell's; while Super is held the keyboard is ours (grab), so any other
// key only marks the Super press as a chord and Expose stays shut
bool NCDEWindowManager::onGlobalKey(const xcb_key_press_event_t *ev, bool press)
{
    const uint8_t kc = ev->detail;
    if (m_kcSuper.contains(kc)) {
        if (press) {
            if (!m_superDown)
                m_superUsed = false;
            m_superDown = true;          // auto-repeat presses land here too
        } else {
            if (m_superDown && !m_superUsed)
                emit exposeToggleRequested();
            m_superDown = false;
        }
        return true;
    }
    if (press && m_superDown)
        m_superUsed = true;
    if (press && m_kcF4.contains(kc) && (ev->state & XCB_MOD_MASK_1)) {
        if (m_activeClient && rowForClient(m_activeClient) >= 0)
            closeWindow(m_activeClient);
        return true;
    }
    return m_superDown;
}

bool NCDEWindowManager::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *)
{
    if (!m_started || eventType != "xcb_generic_event_t")
        return false;
    auto *gev = static_cast<xcb_generic_event_t *>(message);
    const uint8_t type = gev->response_type & 0x7f;
    if (m_hasRandr && type == m_randrEventBase + XCB_RANDR_SCREEN_CHANGE_NOTIFY) {
        auto *ev = reinterpret_cast<xcb_randr_screen_change_notify_event_t *>(gev);
        onRandRScreenChange(ev->width, ev->height);
        return false;
    }
    if (m_hasScreensaver && type == m_screensaverEventBase + XCB_SCREENSAVER_NOTIFY) {
        auto *ev = reinterpret_cast<xcb_screensaver_notify_event_t *>(gev);
        if (m_animPolicy)
            m_animPolicy->onScreenSaverActivated(ev->state == XCB_SCREENSAVER_STATE_ON);
        return false;
    }
    switch (type) {
    case XCB_KEY_PRESS:
    case XCB_KEY_RELEASE: {
        auto *ev = reinterpret_cast<xcb_key_press_event_t *>(gev);
        if (ev->event == m_root)
            return onGlobalKey(ev, type == XCB_KEY_PRESS);
        break;
    }
    case XCB_MAPPING_NOTIFY:
        if (reinterpret_cast<xcb_mapping_notify_event_t *>(gev)->request != XCB_MAPPING_POINTER)
            grabGlobalKeys();   // W15: keymap changed, keycodes may have moved
        break;
    case XCB_GE_GENERIC: {
        auto *ge = reinterpret_cast<xcb_ge_generic_event_t *>(gev);
        if (m_hasXi2 && ge->extension == m_xiOpcode && ge->event_type == XCB_INPUT_RAW_MOTION
            && !m_pointerCoalesce.isActive())
            m_pointerCoalesce.start();   // W9
        break;
    }
    case XCB_CLIENT_MESSAGE:
        onClientMessage(reinterpret_cast<xcb_client_message_event_t *>(gev));
        break;
    case XCB_PROPERTY_NOTIFY: {
        auto *ev = reinterpret_cast<xcb_property_notify_event_t *>(gev);
        onPropertyNotify(ev->window, ev->atom);
        break;
    }
    case XCB_CONFIGURE_REQUEST:
        onConfigureRequest(reinterpret_cast<xcb_configure_request_event_t *>(gev));
        break;
    case XCB_MAP_REQUEST: {
        const uint win = reinterpret_cast<xcb_map_request_event_t *>(gev)->window;
        const int row = rowForClient(win);
        if (row >= 0) {
            // a managed client maps its window again (after hiding it itself): show it
            if (m_windows[row].minimized) {
                unminimizeWindow(win);
            } else {
                xcb_map_window(m_xcb, win);
                xcb_flush(m_xcb);
            }
        } else if (isUnframedType(win)) {
            xcb_map_window(m_xcb, win);   // W8
            xcb_flush(m_xcb);
        } else {
            manage(win);
        }
        break;
    }
    case XCB_MAP_NOTIFY:
        emit anyWindowMapped();
        break;
    case XCB_UNMAP_NOTIFY:
        onUnmapNotify(reinterpret_cast<xcb_unmap_notify_event_t *>(gev));
        break;
    case XCB_FOCUS_IN:
        onFocusIn(reinterpret_cast<xcb_focus_in_event_t *>(gev)->event);
        break;
    case XCB_DESTROY_NOTIFY: {
        const uint win = reinterpret_cast<xcb_destroy_notify_event_t *>(gev)->window;
        if (win && win == m_picomOwner)
            onPicomDied();
        onDestroy(win);
        break;
    }
    default:
        break;
    }
    return false;
}

void NCDEWindowManager::pollPointer()
{
    const QPoint p = QCursor::pos();
    if (p.x() == m_mouseX && p.y() == m_mouseY)
        return;
    m_mouseX = p.x();
    m_mouseY = p.y();
    emit mousePosChanged();
}

void NCDEWindowManager::pollUserIdle()
{
    if (!m_hasScreensaver)
        return;
    xcb_screensaver_query_info_reply_t *r =
        xcb_screensaver_query_info_reply(m_xcb, xcb_screensaver_query_info(m_xcb, m_root), nullptr);
    if (!r)
        return;
    const uint32_t idleMs = r->ms_since_user_input;
    std::free(r);
    emit idleSample(qint64(idleMs));
    if (!m_animPolicy)
        return;
    const bool idle = idleMs >= 30000;
    if (idle != m_userInputIdle) {
        m_userInputIdle = idle;
        m_animPolicy->onUserInputIdle(idle);
    }
    if (m_screensaverTimeoutMs < 1 || qint64(idleMs) < m_screensaverTimeoutMs) {
        m_screensaverIdle = false;
    } else if (!m_screensaverIdle) {
        m_screensaverIdle = true;
        emit screensaverIdleReached();
    }
}

qint64 NCDEWindowManager::userIdleMs() const
{
    if (!m_xcb || !m_hasScreensaver)
        return 0;
    xcb_screensaver_query_info_reply_t *r =
        xcb_screensaver_query_info_reply(m_xcb, xcb_screensaver_query_info(m_xcb, m_root), nullptr);
    if (!r)
        return 0;
    const qint64 ms = r->ms_since_user_input;
    std::free(r);
    return ms;
}

void NCDEWindowManager::setScreensaverTimeoutMs(qint64 ms)
{
    if (ms == m_screensaverTimeoutMs)
        return;
    m_screensaverTimeoutMs = ms;
    m_screensaverIdle = false;
}

void NCDEWindowManager::setAnimPolicy(AnimPolicy *policy)
{
    m_animPolicy = policy;
    if (!policy)
        return;
    connect(policy, &AnimPolicy::policyChanged, this, [this] {
        if (!m_started || m_hasXi2)
            return;
        if (m_animPolicy && m_animPolicy->screenIdle())
            m_pointerTimer.stop();
        else if (!m_pointerTimer.isActive())
            m_pointerTimer.start();
    });
    connect(this, &NCDEWindowManager::windowStateChanged, this, &NCDEWindowManager::recomputeDesktopObscured);
    connect(this, &NCDEWindowManager::countChanged, this, &NCDEWindowManager::recomputeDesktopObscured);
    recomputeDesktopObscured();
}

// ---------------------------------------------------------------------------------- start-up

void NCDEWindowManager::internAtoms()
{
    static const char *const names[] = {
        "WM_PROTOCOLS", "WM_DELETE_WINDOW", "_NET_WM_NAME", "_NET_ACTIVE_WINDOW", "UTF8_STRING",
        "_NET_SUPPORTED", "_NET_WM_STATE", "_NET_WM_PID", "_NET_WM_STATE_MAXIMIZED_VERT",
        "_NET_WM_STATE_MAXIMIZED_HORZ", "_NET_WM_CM_S0", "_NET_WM_WINDOW_TYPE",
        "_NET_WM_WINDOW_TYPE_NORMAL", "_NET_WM_WINDOW_TYPE_DESKTOP", "_NET_WM_WINDOW_TYPE_DOCK",
        "_NET_WM_WINDOW_TYPE_DIALOG", "_NET_WM_WINDOW_TYPE_UTILITY", "_NET_WM_WINDOW_TYPE_TOOLBAR",
        "_NET_WM_WINDOW_TYPE_SPLASH", "_NET_WM_WINDOW_TYPE_POPUP_MENU", "_NET_WM_WINDOW_TYPE_TOOLTIP",
        "_NET_WM_WINDOW_TYPE_NOTIFICATION", "_NET_NUMBER_OF_DESKTOPS", "_NET_CURRENT_DESKTOP",
        "_NET_WM_DESKTOP", "_NCDE_MENUS", "_NCDE_MENU_INVOKE",
        // additions (W5, W7, W8)
        "WM_CHANGE_STATE", "_NET_WM_STATE_HIDDEN", "_NET_CLIENT_LIST", "_NET_SUPPORTING_WM_CHECK",
        "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", "_NET_WM_WINDOW_TYPE_MENU", "_NET_WM_WINDOW_TYPE_COMBO",
        "_NET_WM_WINDOW_TYPE_DND",
        "WM_STATE",   // W14
    };
    uint *const atomSlots[] = {
        &m_aWmProtocols, &m_aWmDeleteWindow, &m_aNetWmName, &m_aNetActiveWindow, &m_aUtf8,
        &m_aNetSupported, &m_aNetWmState, &m_aNetWmPid, &m_aStateMaxV,
        &m_aStateMaxH, &m_aCmS0, &m_aWindowType,
        &m_aTypeNormal, &m_aTypeDesktop, &m_aTypeDock,
        &m_aTypeDialog, &m_aTypeUtility, &m_aTypeToolbar,
        &m_aTypeSplash, &m_aTypePopupMenu, &m_aTypeTooltip,
        &m_aTypeNotification, &m_aNumberOfDesktops, &m_aCurrentDesktop,
        &m_aNetWmDesktop, &m_aNcdeMenus, &m_aNcdeMenuInvoke,
        &m_aWmChangeState, &m_aStateHidden, &m_aClientList, &m_aSupportingWmCheck,
        &m_aTypeDropdownMenu, &m_aTypeMenu, &m_aTypeCombo,
        &m_aTypeDnd,
        &m_aWmState,
    };
    constexpr int n = int(sizeof names / sizeof names[0]);
    static_assert(n == int(sizeof atomSlots / sizeof atomSlots[0]), "atom table");
    xcb_intern_atom_cookie_t cookies[n];
    for (int i = 0; i < n; ++i)   // all requests first, then the replies: one round trip, not 35
        cookies[i] = xcb_intern_atom(m_xcb, 0, uint16_t(std::strlen(names[i])), names[i]);
    for (int i = 0; i < n; ++i) {
        xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(m_xcb, cookies[i], nullptr);
        *atomSlots[i] = r ? r->atom : 0;
        std::free(r);
    }
    setupEwmh();
}

void NCDEWindowManager::setupEwmh()
{
    if (!m_xcb || !m_aNetSupported)
        return;
    const uint32_t supported[] = {
        m_aNetSupported, m_aNetActiveWindow, m_aNetWmName, m_aNetWmState, m_aStateMaxV, m_aStateMaxH,
        m_aWindowType, m_aTypeNormal, m_aTypeDesktop, m_aTypeDock, m_aTypeDialog, m_aTypeUtility,
        m_aTypeToolbar, m_aTypeSplash, m_aTypePopupMenu, m_aTypeTooltip, m_aTypeNotification,
        m_aNumberOfDesktops, m_aCurrentDesktop, m_aNetWmDesktop,
        m_aStateHidden, m_aClientList, m_aSupportingWmCheck,
    };
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_root, m_aNetSupported, XCB_ATOM_ATOM, 32,
                        uint32_t(sizeof supported / sizeof supported[0]), supported);
    const uint32_t desktops = kDesktops;
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_root, m_aNumberOfDesktops, XCB_ATOM_CARDINAL, 32, 1, &desktops);
    xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_root, m_aCurrentDesktop, XCB_ATOM_CARDINAL, 32, 1, &m_currentDesktop);
    // W7: _NET_SUPPORTING_WM_CHECK — a never-mapped child of the root naming the WM
    if (m_aSupportingWmCheck && !m_wmCheckWindow) {
        m_wmCheckWindow = xcb_generate_id(m_xcb);
        const uint32_t ovr = 1;
        xcb_create_window(m_xcb, XCB_COPY_FROM_PARENT, m_wmCheckWindow, m_root, -1, -1, 1, 1, 0,
                          XCB_WINDOW_CLASS_INPUT_ONLY, XCB_COPY_FROM_PARENT, XCB_CW_OVERRIDE_REDIRECT, &ovr);
        xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_wmCheckWindow, m_aSupportingWmCheck, XCB_ATOM_WINDOW, 32, 1, &m_wmCheckWindow);
        xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_root, m_aSupportingWmCheck, XCB_ATOM_WINDOW, 32, 1, &m_wmCheckWindow);
        xcb_change_property(m_xcb, XCB_PROP_MODE_REPLACE, m_wmCheckWindow, m_aNetWmName, m_aUtf8, 8, 7, "LaPivot");
    }
    updateClientList();
    xcb_flush(m_xcb);
}

bool NCDEWindowManager::start()
{
    if (auto *x11 = qGuiApp ? qGuiApp->nativeInterface<QNativeInterface::QX11Application>() : nullptr)
        m_xcb = x11->connection();
    if (!m_xcb)
        return false;
    xcb_screen_iterator_t s = xcb_setup_roots_iterator(xcb_get_setup(m_xcb));
    if (!s.rem)
        return false;
    m_root = s.data->root;
    m_screenW = s.data->width_in_pixels;
    m_screenH = s.data->height_in_pixels;
    xcb_generic_error_t *err = xcb_request_check(
        m_xcb, xcb_change_window_attributes_checked(m_xcb, m_root, XCB_CW_EVENT_MASK, &kRootMask));
    if (err) {   // another window manager owns the root
        std::free(err);
        m_started = false;
        return false;
    }
    internAtoms();
    scanExisting();

    const xcb_query_extension_reply_t *randr = xcb_get_extension_data(m_xcb, &xcb_randr_id);
    if (randr && randr->present) {
        m_hasRandr = true;
        m_randrEventBase = randr->first_event;
        xcb_randr_select_input(m_xcb, m_root, XCB_RANDR_NOTIFY_MASK_SCREEN_CHANGE);
    }
    const xcb_query_extension_reply_t *ss = xcb_get_extension_data(m_xcb, &xcb_screensaver_id);
    if (ss && ss->present) {
        m_hasScreensaver = true;
        m_screensaverEventBase = ss->first_event;
        std::free(xcb_screensaver_query_version_reply(m_xcb, xcb_screensaver_query_version(m_xcb, 1, 1), nullptr));
        xcb_screensaver_select_input(m_xcb, m_root, XCB_SCREENSAVER_EVENT_NOTIFY_MASK);
    }
    grabGlobalKeys();   // W15
    const xcb_query_extension_reply_t *xi = xcb_get_extension_data(m_xcb, &xcb_input_id);
    if (xi && xi->present) {
        xcb_generic_error_t *verr = nullptr;
        xcb_input_xi_query_version_reply_t *v =
            xcb_input_xi_query_version_reply(m_xcb, xcb_input_xi_query_version(m_xcb, 2, 0), &verr);
        if (v && !verr) {
            struct {
                xcb_input_event_mask_t head;
                uint32_t mask;
            } em{{XCB_INPUT_DEVICE_ALL_MASTER, 1}, XCB_INPUT_XI_EVENT_MASK_RAW_MOTION};
            xcb_input_xi_select_events(m_xcb, m_root, 1, &em.head);
            m_hasXi2 = true;
            m_xiOpcode = xi->major_opcode;
        }
        std::free(v);
        std::free(verr);
    }
    watchPicomOwner();
    QCoreApplication::instance()->installNativeEventFilter(this);
    xcb_flush(m_xcb);

    m_pointerTimer.setInterval(16);
    connect(&m_pointerTimer, &QTimer::timeout, this, &NCDEWindowManager::pollPointer);
    if (!m_hasXi2)
        m_pointerTimer.start();
    pollPointer();
    m_idleTimer.setInterval(2000);
    connect(&m_idleTimer, &QTimer::timeout, this, &NCDEWindowManager::pollUserIdle);
    if (m_hasScreensaver)
        m_idleTimer.start();
    m_started = true;
    return true;
}
