// MagpieMessengerWeb.qml — the Messenger engine behind MagpieMessenger.qml.
// The real Messenger web client in a persistent Magpie-only profile, re-skinned
// with Magpie's palette + type through Facebook's own CSS custom properties
// (--primary-text, --web-wash, --chat-outgoing-message-bubble-background-color …),
// which survive Facebook's class-name churn. Kept in its own file so only a
// Loader ever imports QtWebEngine.
import QtQuick
import QtCore
import QtWebEngine

WebEngineView {
    id: view

    property var kit
    property color cer: "#2f8aa0"
    property color cerDeep: "#1f5f70"
    property real scale: 1.0

    readonly property string home: "https://www.messenger.com/"
    property int  unread: 0
    readonly property bool signedIn: /^https:\/\/(www\.)?(messenger|facebook)\.com\/(t|e2ee|messages)\b/.test(url.toString())
    signal messageArrived(string title, string body)

    function goHome() { url = home }

    zoomFactor: Math.max(0.5, Math.min(3.0, scale))
    backgroundColor: kit ? kit.surface : "white"
    // url is set by applySkin() once the palette has arrived — Messenger's first
    // paint is already in Magpie's colours, never a flash of Facebook blue
    property bool _started: false

    // ── the Magpie-only profile: Facebook sign-in survives restarts ──────
    profile: WebEngineProfile {
        id: prof
        storageName: "MagpieMessenger"
        offTheRecord: false
        persistentCookiesPolicy: WebEngineProfile.ForcePersistentCookies
        httpCacheType: WebEngineProfile.DiskHttpCache
        // Facebook serves its full client to Chrome; drop Qt's own token so it does.
        Component.onCompleted: httpUserAgent = httpUserAgent.replace(/ ?QtWebEngine\/[0-9.]+/, "")
        onPresentNotification: function(n) {
            n.show()
            view.messageArrived(n.title, n.message)
        }
        onDownloadRequested: function(d) {
            d.downloadDirectory = decodeURIComponent(StandardPaths.writableLocation(StandardPaths.DownloadLocation)
                                                     .toString().replace(/^file:\/\//, ""))
            d.accept()
        }
    }

    settings.javascriptCanAccessClipboard: true
    settings.javascriptCanPaste: true
    settings.playbackRequiresUserGesture: false
    settings.screenCaptureEnabled: true
    settings.showScrollBars: true

    // ── who is Messenger ──────────────────────────────────────────────────
    function trusted(u) {
        var h = ""
        try { h = new URL(u.toString()).hostname } catch (e) { return false }
        return /(^|\.)(messenger\.com|facebook\.com|fbcdn\.net|fbsbx\.com|facebook\.net|meta\.com)$/.test(h)
    }
    // Facebook wraps outbound links (l.facebook.com/l.php?u=…) — hand the real target to the browser.
    function unwrap(u) {
        var s = u.toString()
        try {
            var p = new URL(s)
            if (/^l\.(facebook|messenger)\.com$/.test(p.hostname) && p.searchParams.get("u"))
                return p.searchParams.get("u")
        } catch (e) {}
        return s
    }

    onTitleChanged: {
        var m = /^\((\d+)\)/.exec(title)
        unread = m ? parseInt(m[1]) : 0
    }

    onNavigationRequested: function(req) {
        if (!req.isMainFrame) return
        var s = req.url.toString()
        if (/^(about|data|blob):/.test(s) || trusted(req.url) && !/^https?:\/\/l\.(facebook|messenger)\.com\//.test(s)) return
        req.reject()
        Qt.openUrlExternally(unwrap(req.url))
    }

    onNewWindowRequested: function(req) {
        if (trusted(req.requestedUrl) && !/^https?:\/\/l\.(facebook|messenger)\.com\//.test(req.requestedUrl.toString())) {
            // calls, photo viewers, sign-in helpers — a Messenger window of our own
            var w = popupWin.createObject(null)
            req.openIn(w.webView)
            w.show()
        } else {
            Qt.openUrlExternally(unwrap(req.requestedUrl))
        }
    }

    // mic, camera, notifications, screen share — only ever for Messenger itself
    onPermissionRequested: function(p) {
        if (trusted(p.origin)) p.grant(); else p.deny()
    }
    onDesktopMediaRequested: function(req) {
        if (req.screensModel.rowCount() > 0) req.selectScreen(req.screensModel.index(0, 0))
        else req.cancel()
    }

    onRenderProcessTerminated: function(status, code) { crashTimer.start() }
    Timer { id: crashTimer; interval: 1500; onTriggered: view.reload() }

    Component {
        id: popupWin
        Window {
            id: pw
            property alias webView: pv
            width: 960; height: 680
            title: pv.title.length ? pv.title : "Messenger"
            color: view.backgroundColor
            onClosing: destroy()
            WebEngineView {
                id: pv; anchors.fill: parent
                profile: prof
                zoomFactor: view.zoomFactor
                backgroundColor: view.backgroundColor
                onWindowCloseRequested: pw.close()
                onPermissionRequested: function(p) { if (view.trusted(p.origin)) p.grant(); else p.deny() }
                onDesktopMediaRequested: function(req) { view.desktopMediaRequested(req) }
                onNewWindowRequested: function(req) { view.newWindowRequested(req) }
                Component.onCompleted: userScripts.collection = view.userScripts.collection
            }
        }
    }

    // ── the skin ──────────────────────────────────────────────────────────
    function rgba(c, a) { return "rgba(" + Math.round(c.r*255) + "," + Math.round(c.g*255) + "," + Math.round(c.b*255) + "," + a + ")" }
    function hex(c)     { return rgba(c, c.a) }
    function fam(f)     { return "'" + String(f).replace(/'/g, "") + "'" }

    function skinCss() {
        if (!kit) return ""
        var k = kit
        var paper    = hex(k.surface), paper2 = hex(k.surface2), panel = hex(k.panelBg)
        var vellum   = hex(k.dark ? k.surface2 : Qt.rgba(1, 0.980, 0.918, 1))
        var ink      = hex(k.ink), soft = hex(k.inkSoft)
        var gilt     = hex(k.dark ? k.gilt1 : k.gilt2), giltSoft = rgba(k.gilt2, 0.45)
        var accent   = hex(k.dark ? Qt.lighter(cer, 1.15) : cer)
        var mine     = hex(cerDeep), onMine = "#fbf3de"
        var serif    = fam(k.gar) + "," + fam(k.serif) + ",serif"
        var titles   = fam(k.titles) + "," + fam(k.gar) + ",serif"
        var v = function(n, val) { return "--" + n + ":" + val + "!important;" }
        var css = ":root,.__fb-light-mode,.__fb-dark-mode{"
            + v("web-wash", paper) + v("wash", paper2) + v("surface-background", paper)
            + v("card-background", vellum) + v("card-background-flat", vellum) + v("messenger-card-background", paper)
            + v("popover-background", vellum) + v("popover-card-background", vellum) + v("popover-border-color", gilt)
            + v("nav-bar-background", panel) + v("nav-bar-background-gradient", panel) + v("nav-bar-background-gradient-wash", panel)
            + v("comment-background", paper2) + v("messenger-reply-background", paper2) + v("chat-replied-message-background-color", paper2)
            + v("input-background", paper2) + v("input-background-hover", paper2) + v("input-background-active", vellum)
            + v("input-border-color", gilt) + v("text-input-bar-background", paper2)
            + v("primary-text", ink) + v("secondary-text", soft) + v("placeholder-text", soft) + v("disabled-text", soft)
            + v("primary-icon", ink) + v("secondary-icon", soft) + v("placeholder-icon", soft)
            + v("divider", giltSoft) + v("media-inner-border", giltSoft) + v("media-outer-border", giltSoft)
            + v("scroll-thumb", giltSoft) + v("scroll-shadow", "transparent")
            + v("accent", accent) + v("blue-link", accent) + v("primary-web-focus-indicator", accent)
            + v("primary-button-background", mine) + v("primary-button-text", onMine) + v("primary-button-icon", onMine)
            + v("primary-button-pressed", rgba(cerDeep, 0.8))
            + v("secondary-button-background", paper2) + v("secondary-button-text", ink) + v("secondary-button-stroke", gilt)
            + v("hover-overlay", rgba(cer, 0.10)) + v("highlight-bg", rgba(cer, 0.18)) + v("text-highlight", rgba(cer, 0.25))
            + v("toggle-active-background", rgba(cer, 0.18)) + v("toggle-active-icon", accent) + v("toggle-active-text", accent)
            + v("toggle-button-active-background", mine)
            + v("notification-badge", hex(k.rose)) + v("badge-background-color-red", hex(k.rose))
            + v("badge-background-color-blue", mine) + v("positive", hex(k.verd)) + v("negative", hex(k.rose))
            + v("chat-incoming-message-bubble-background-color", vellum)
            + v("chat-outgoing-message-bubble-background-color", mine)
            + v("bubbleContentUserBackgroundColor", mine) + v("bubbleContentUserColor", onMine)
            + v("buttonSendBackgroundColor", mine)
            + v("font-family-default", serif) + v("font-family-segoe", serif) + v("font-family-apple", serif)
            + v("font-family-system-fds", serif) + v("body-font-family", serif) + v("meta-font-family", serif)
            + v("primary-label-font-family", serif) + v("secondary-label-font-family", serif)
            + v("text-input-field-font-family", serif) + v("text-input-label-font-family", serif)
            + v("body-emphasized-font-family", titles) + v("body-large-font-family", serif)
            + v("headline1-font-family", titles) + v("headline2-font-family", titles) + v("headline3-font-family", titles)
            + v("headline-large-font-family", titles) + v("headline-small-font-family", titles)
            + v("headline-extra-small-font-family", titles)
            + "}"
            // outgoing bubbles take the thread's own theme colour from an inline variable;
            // the wire's colour wins everywhere
            + "*{--chat-outgoing-message-bubble-background-color:" + mine + "!important}"
            // the signed-in Messenger app carries Facebook's theme class; the sign-in
            // page doesn't and keeps its own light paper (its text colours are fixed)
            + ":root:is(.__fb-light-mode,.__fb-dark-mode),:root:is(.__fb-light-mode,.__fb-dark-mode) body{background:" + paper + "!important}"
            + "body :is(div,span,a,p,h1,h2,h3,h4,h5,h6,label,input,textarea,button,li,strong,em,b,i,[contenteditable]){font-family:" + serif + "!important}"
            + "::selection{background:" + rgba(cer, 0.35) + "}"
            // the sign-in page: Magpie cerulean on its headline + Log in button
            + ":root:not(.__fb-light-mode):not(.__fb-dark-mode) h1{color:" + hex(Qt.darker(cer, 1.25)) + "!important}"
            + ":root:not(.__fb-light-mode):not(.__fb-dark-mode) :is(button[type=submit],#loginbutton,button[name=login]){background:"
            + mine + "!important;color:" + onMine + "!important;border:1.5px solid " + hex(k.gilt3) + "!important}"
        return css
    }

    // Injected at document creation (before <html> exists) and re-run on palette
    // changes. Keeps one <style id=magpie-skin> alive through Facebook's re-renders.
    function skinScript(css) {
        return "(function(){window.__magpieSkin=" + JSON.stringify(css) + ";"
             + "function put(){var r=document.head||document.documentElement;if(!r)return;"
             + "var s=document.getElementById('magpie-skin');"
             + "if(!s){s=document.createElement('style');s.id='magpie-skin';r.appendChild(s);}"
             + "if(s.textContent!==window.__magpieSkin)s.textContent=window.__magpieSkin;}"
             + "put();if(window.__magpieSkinObs)return;"
             + "var early=new MutationObserver(put);early.observe(document,{childList:true,subtree:true});window.__magpieSkinObs=early;"
             + "function settle(){put();early.disconnect();"
             + "var keep=new MutationObserver(function(){if(!document.getElementById('magpie-skin'))put();});"
             + "keep.observe(document.documentElement,{childList:true});if(document.head)keep.observe(document.head,{childList:true});"
             + "window.__magpieSkinObs=keep;}"
             + "if(document.readyState==='loading')document.addEventListener('DOMContentLoaded',settle);else settle();})();"
    }

    function applySkin() {
        var src = skinScript(skinCss())
        userScripts.collection = [ { name: "magpie-skin", sourceCode: src,
                                     injectionPoint: WebEngineScript.DocumentCreation,
                                     worldId: WebEngineScript.MainWorld, runsOnSubFrames: true } ]
        runJavaScript(src)
        if (!_started && kit) { _started = true; url = home }
    }
    // Iris palette / dark-light changes re-dress the live page
    Timer { id: reskin; interval: 250; onTriggered: view.applySkin() }
    onKitChanged: reskin.restart()
    onCerChanged: reskin.restart()
    Connections {
        target: view.kit
        ignoreUnknownSignals: true
        function onSurfaceChanged() { reskin.restart() }
        function onInkChanged()     { reskin.restart() }
        function onDarkChanged()    { reskin.restart() }
    }
    Component.onCompleted: applySkin()
}
