#!/usr/bin/env python3
"""Phase 3 functional probe (offscreen): the dedupe must be behavior-identical.
Checks — per selected widget exactly one visible Glow row, one Frame row, one
Reset button with the right label; swatch ×/↺/caption logic still reacts to
state; the merged popup shows Reset only when a reset callback was passed,
keeps the Font-only contrast readout, and the Sections reset path actually
clears + saves; the old Section popup is fully gone (exactly one Set Colour)."""
import os, shutil, sys, tempfile

os.environ["QT_QPA_PLATFORM"] = "offscreen"
from PySide6.QtCore import QUrl
from PySide6.QtCore import qInstallMessageHandler
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlEngine, QQmlComponent, QQmlExpression, QQmlProperty

W = os.path.dirname(os.path.abspath(__file__))
SRC = "/usr/share/ncde"
shadow = tempfile.mkdtemp(prefix="filigree-probe3.")
for name in os.listdir(SRC):
    p = os.path.join(SRC, name)
    if os.path.isfile(p):
        os.symlink(p, os.path.join(shadow, name))
for staged in ("FiligreeTab.qml", "NCDESlider.qml", "SettingsColorWheel.qml"):
    dst = os.path.join(shadow, staged)
    os.remove(dst)
    shutil.copy(os.path.join(W, staged), dst)

qInstallMessageHandler(lambda m, c, s: None)
app = QGuiApplication([])
engine = QQmlEngine()
engine.addImportPath(shadow)

MOCKS = open(os.path.join(W, "harness.py")).read()
MOCKS = MOCKS.split('MOCKS = """')[1].split('"""')[0]
mockPath = os.path.join(shadow, "__Mocks.qml")
open(mockPath, "w").write(MOCKS)
mc = QQmlComponent(engine, QUrl.fromLocalFile(mockPath))
mocks = mc.create()
assert mocks, [e.toString() for e in mc.errors()]
ctx = engine.rootContext()
for name in ("ncde", "settings", "theme", "notifications", "animPolicy"):
    ctx.setContextProperty(name, mocks.property(name))

comp = QQmlComponent(engine, QUrl.fromLocalFile(os.path.join(shadow, "FiligreeTab.qml")))
root = comp.create()
assert root, [e.toString() for e in comp.errors()]
root.setProperty("width", 800); root.setProperty("height", 1400)
fails = []

from PySide6.QtQml import QQmlListReference
def walk(item, eff=True):
    """(object, effectively-visible) pairs over the QML visual children tree.
    Uses the 'children' list property + manual visibility chaining so it also
    works on delegates PySide wraps as plain QObject."""
    vis = eff and bool(item.property("visible"))
    out = [(item, vis)]
    ref = QQmlListReference(item, "children")
    for i in range(ref.count()):
        out += walk(ref.at(i), vis)
    return out

def js(expr):
    e = QQmlExpression(engine.contextForObject(root), root, expr)
    v = e.evaluate()
    if isinstance(v, tuple):
        v = v[0]
    if e.hasError():
        fails.append(f"JS ERROR [{expr}]: {e.error().toString()}")
    return v

def vis_texts(txt):
    return [t for t, v in walk(root) if t.property("text") == txt and v]

# ── Widgets tab: rows + reset button follow selWidget ──
root.setProperty("_activeTab", "widgets"); app.processEvents()
expected = {
    "clock": "Reset Clock", "space": "Reset Space", "weather": "Reset Weather",
    "stats": "Reset Stats", "salon": "Reset Salon", "laombre": "Reset La’Ombre d’Opale",
}
resets_all = set(expected.values())
for wk, label in expected.items():
    root.setProperty("selWidget", wk); app.processEvents()
    nframe = len(vis_texts("Frame"))
    # "Glow" appears twice by design: style-glow row + the widget-glass glowColor row
    nglow = len(vis_texts("Glow"))
    if nframe != 1: fails.append(f"[{wk}] visible Frame rows {nframe} != 1")
    if nglow != 2: fails.append(f"[{wk}] visible Glow labels {nglow} != 2")
    vis_resets = [t for t, v in walk(root) if t.property("text") in resets_all and v]
    if len(vis_resets) != 1 or vis_resets[0].property("text") != label:
        fails.append(f"[{wk}] reset buttons visible: {[t.property('text') for t in vis_resets]}")
print("per-widget row/reset visibility checked for all 6")

# ── swatch state logic: set clock glow -> x shown, caption hidden; clear -> back ──
root.setProperty("selWidget", "clock"); app.processEvents()
if len(vis_texts("engine default")) != 1: fails.append("caption not visible while glow unset")
js("_updateWidg('clock','glow','#112233')"); app.processEvents()
if vis_texts("engine default"): fails.append("caption still visible after glow set")
if not vis_texts("×"): fails.append("clear x not visible after glow set")
js("_updateWidg('clock','glow','')"); app.processEvents()
if len(vis_texts("engine default")) != 1: fails.append("caption did not return after clear")
print("swatch x/caption logic reacts")

# ── per-widget default fallbacks preserved ──
if js("_widgDefault('salon')") != "#6a4a8b": fails.append("salon default != #6a4a8b")
if js("_widgDefault('laombre')") != "#6a4a8b": fails.append("laombre default != #6a4a8b")
if str(js("String(_widgDefault('clock'))")) != "#c98a3a": fails.append("clock default != gilt3")
if str(js("String(_widgDefault('space'))")) != "#2f8aa0": fails.append("space default != cer")
if str(js("String(_widgDefault('weather'))")) != "#3a7a5e": fails.append("weather default != verd")
if str(js("String(_widgDefault('stats'))")) != "#8b1e3f": fails.append("stats default != wine4")
print("default colour fallbacks preserved")

# ── merged popup: no reset callback -> Reset hidden ──
setcol = [t for t, v in walk(root) if t.property("text") == "Set Colour"]
if len(setcol) != 1: fails.append(f"Set Colour texts {len(setcol)} != 1 (old popup not gone?)")
js("openColorPopup('Clock — Glow', '#c98a3a', function(c){})"); app.processEvents()
if not root.property("_colorPopupOpen"): fails.append("popup did not open")
if vis_texts("Reset"): fails.append("Reset visible without reset callback")
if [t for t, v in walk(root) if str(t.property("text") or "").startswith("Contrast") and v]:
    fails.append("contrast readout visible for non-Font popup")
js("_colorPopupOpen = false"); app.processEvents()

# ── Font popup keeps the contrast readout ──
js("openColorPopup('Font — Fill', '#2a1e0e', function(c){})"); app.processEvents()
if not [t for t, v in walk(root) if str(t.property("text") or "").startswith("Contrast on background") and v]:
    fails.append("contrast readout missing for Font popup")
js("_colorPopupOpen = false"); app.processEvents()

# ── Sections path: reset callback shows Reset and clears+saves on invoke ──
js("settings.topPanelTextColor = '#123456'")
js("openColorPopup('Top Panel — Colour', settings.topPanelTextColor,"
   " function(c){ pushSectionColor('topPanelTextColor', c) },"
   " function(){ pushSectionColor('topPanelTextColor', '') })")
app.processEvents()
if len(vis_texts("Reset")) != 1: fails.append("Reset not visible for Sections popup")
title = [t for t, v in walk(root) if t.property("text") == "Top Panel — Colour" and v]
if not title: fails.append("Sections popup title wrong/missing")
js("_colorResetCallback()"); app.processEvents()
if js("settings.topPanelTextColor") != "": fails.append("reset callback did not clear the colour")
calls = mocks.property("settings").property("calls")
calls = calls.toVariant() if hasattr(calls, "toVariant") else list(calls)
if "saveSectionColors" not in calls: fails.append("saveSectionColors never called")
js("_colorPopupOpen = false")
# set-colour path too
js("openColorPopup('Glia Menus — Colour', '', function(c){ pushSectionColor('gliaTextColor', c) },"
   " function(){ pushSectionColor('gliaTextColor', '') })")
app.processEvents()
js("_colorCallback('#aabbcc')")
if js("settings.gliaTextColor") != "#aabbcc": fails.append("set-colour callback did not store")
js("_colorPopupOpen = false"); app.processEvents()
# next non-section popup must hide Reset again
js("openColorPopup('Stats — Frame', '#c98a3a', function(c){})"); app.processEvents()
if vis_texts("Reset"): fails.append("Reset leaked into a non-Sections popup")
print("merged popup: reset/set/contrast paths all correct")

print("FAILS:", fails if fails else "none")
sys.exit(1 if fails else 0)
