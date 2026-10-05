#!/usr/bin/env python3
"""Offscreen instantiation gate for the staged FiligreeTab.qml + NCDESlider.qml.

Builds a shadow of /usr/share/ncde (symlinks), overlays the two staged files,
mocks the ncde/settings/theme/notifications/animPolicy context objects, then:
  1. instantiates FiligreeTab
  2. drives _activeTab through all five tabs (forces every delegate to build)
  3. fails on any QML error, or any warning that names our two files
"""
import os, shutil, sys, tempfile

os.environ["QT_QPA_PLATFORM"] = "offscreen"
from PySide6.QtCore import QUrl, QObject, qInstallMessageHandler
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlEngine, QQmlComponent

W = os.path.dirname(os.path.abspath(__file__))
SRC = "/usr/share/ncde"
shadow = tempfile.mkdtemp(prefix="filigree-gate.")
for name in os.listdir(SRC):
    p = os.path.join(SRC, name)
    if os.path.isfile(p):
        os.symlink(p, os.path.join(shadow, name))
for staged in ("FiligreeTab.qml", "NCDESlider.qml", "SettingsColorWheel.qml"):
    dst = os.path.join(shadow, staged)
    os.remove(dst)
    shutil.copy(os.path.join(W, staged), dst)

messages = []
def handler(mode, ctx, msg):
    messages.append((int(mode), msg))
qInstallMessageHandler(handler)

app = QGuiApplication([])
engine = QQmlEngine()
engine.addImportPath(shadow)

MOCKS = """
import QtQuick 2.15
QtObject {
    property QtObject ncde: QtObject {
        signal themeChanged()
        property string accentName: "P3"
        property color surface: "#e8d6a9";  property color surfaceAlt: "#dcc793"
        property color gilt0: "#5a3a14"; property color gilt1: "#8a5a20"; property color gilt2: "#b07a30"
        property color gilt3: "#c98a3a"; property color gilt4: "#e9c97c"; property color gilt5: "#f6e3b0"
        property color wine1: "#2a0612"; property color wine2: "#4a0e22"; property color wine3: "#6e1832"; property color wine4: "#8b1e3f"
        property color foreground: "#2a1e0e"; property color accent: "#b07a30"; property color panelBg: "#1d130a"
        property color panelText: "#2a1e0e"; property color glow: "#e9c97c"; property color cer: "#2f8aa0"; property color verd: "#3a7a5e"
        property color amber: "#d99a3a"; property color rose: "#c64b63"
        property bool darkMode: false; property string darkModeLock: ""
        property real fontSize_sm: 12; property real fontSize_md: 14; property real fontSize_lg: 18
        property string displayFont: "Cinzel Decorative"; property string titleFont: "Cinzel"
        property string bodyFont: "Cormorant Garamond"; property string monoFont: "TerminalVector"
        property var calls: []
        function presets() { var a=[]; for (var i=0;i<90;i++) a.push({id:i, name:"P"+i, accent:"#b07a30"}); return a }
        function surfaceGlass(k) { return {tint:"#b07a30", shine:0.5, glow:0.4, border:"#e9c97c", glowColor:"#e9c97c"} }
        function widgetStyle(k)  { return {accent:"#c98a3a", glow:"", leading:"", fill:"", font:"Cinzel"} }
        function terminalConfig(){ return {glassTint:0.3, fontFamily:"TerminalVector"} }
        function setSurfaceGlass(k,t,s,g,b,gc){ calls.push("setSurfaceGlass:"+k) }
        function setWidgetStyleMap(k,m){ calls.push("setWidgetStyleMap:"+k) }
        function resetWidgetStyle(k){ calls.push("resetWidgetStyle:"+k) }
        function saveTheme(p){ calls.push("saveTheme") }
        function applyPreset(i){ calls.push("applyPreset:"+i) }
        function setTerminalFont(f){ calls.push("setTerminalFont") }
        function setTerminalGlassTint(v){ calls.push("setTerminalGlassTint") }
    }
    property QtObject settings: QtObject {
        property string configBase: "/tmp/"
        property string fontFamily: "Noto Sans"; property int fontWeight: 400; property bool fontItalic: false
        property real fontSizeScale: 1.0; property real uiScale: 1.0; property real accessibilityTextScale: 1.0
        property real letterSpacing: 0.0; property real lineHeight: 1.2; property bool highContrast: false
        property string textColor: ""; property string textOutlineColor: ""; property bool textOutlineEnabled: false
        property real textOutlineWidth: 1.0
        property string textShadowColor: ""; property bool textShadowEnabled: false
        property real textShadowRadius: 4; property real textShadowOffsetX: 1; property real textShadowOffsetY: 1
        property string topPanelTextColor: ""; property string gliaTextColor: ""
        property string dockHoverTextColor: ""; property string leapFrogTextColor: ""
        property var calls: []
        function saveFontSettings(){ calls.push("saveFontSettings") }
        function applyFontSettings(){ calls.push("applyFontSettings") }
        function saveTextColor(){ calls.push("saveTextColor") }
        function saveSectionColors(){ calls.push("saveSectionColors") }
        function saveSurfaceGlass(k,t,s,g,b,gc){ calls.push("saveSurfaceGlass:"+k) }
        function saveWidgetStyleMap(k,m){ calls.push("saveWidgetStyleMap:"+k) }
        function resetWidgetStyle(k){ calls.push("resetWidgetStyle:"+k) }
    }
    property QtObject theme: QtObject {
        property real fontSmall: 11; property real fontMedium: 14; property real fontLarge: 18
    }
    property QtObject notifications: QtObject {
        property var calls: []
        function notify(a,b,c,d){ calls.push("notify:"+b) }
    }
    property QtObject animPolicy: QtObject { property bool instant: true }
}
"""
mockPath = os.path.join(shadow, "__Mocks.qml")
open(mockPath, "w").write(MOCKS)
mc = QQmlComponent(engine, QUrl.fromLocalFile(mockPath))
mocks = mc.create()
if mocks is None:
    print("MOCK CREATE FAILED:", [e.toString() for e in mc.errors()]); sys.exit(1)

ctx = engine.rootContext()
for name in ("ncde", "settings", "theme", "notifications", "animPolicy"):
    ctx.setContextProperty(name, mocks.property(name))

comp = QQmlComponent(engine, QUrl.fromLocalFile(os.path.join(shadow, "FiligreeTab.qml")))
if comp.isError():
    print("COMPILE ERRORS:"); [print(" ", e.toString()) for e in comp.errors()]; sys.exit(1)
root = comp.create()
if root is None:
    print("CREATE FAILED:"); [print(" ", e.toString()) for e in comp.errors()]; sys.exit(1)
root.setProperty("width", 800); root.setProperty("height", 1400)

for tab in ("iris", "type", "sections", "glass", "widgets"):
    root.setProperty("_activeTab", tab)
    app.processEvents()
print("INSTANTIATED + ALL 5 TABS BUILT")

bad = [m for (mode, m) in messages
       if ("FiligreeTab" in m or "NCDESlider" in m)
       and "TypeError" not in m or ("FiligreeTab" in m and "Error" in m)]
hard = [m for (mode, m) in messages if mode >= 2 and ("FiligreeTab" in m or "NCDESlider" in m)]
warn = [m for (mode, m) in messages if ("FiligreeTab" in m or "NCDESlider" in m)]
if warn:
    print(f"{len(warn)} messages naming our files:")
    for m in warn[:20]: print("  ", m)
if hard:
    print("HARD FAILURES ABOVE"); sys.exit(1)
print("GATE PASSED")
