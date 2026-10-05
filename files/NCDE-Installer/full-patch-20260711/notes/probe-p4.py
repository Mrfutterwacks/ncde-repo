#!/usr/bin/env python3
"""Phase 4 functional probe (offscreen) — audit-pass refinements.
Checks: _dispName mapping; popup opens on the EXACT colour it was given (full
HSV seed incl. brightness, greys, black, round-trip via currentHex); humanised
headings visible (TOP PANEL — GLASS / GHOST — GLASS); widget preview text falls
back to gilt4 when fill unset and honours an explicit fill; Blur/Offset/
Thickness rows dim+disable with their parent feature; Solei-Lune chips built;
scrim/dialog geometry mapping used by tap-outside-cancels; Spacing/Leading
slider ids resolve for the Reset Typography resync."""
import os, shutil, sys, tempfile

os.environ["QT_QPA_PLATFORM"] = "offscreen"
from PySide6.QtCore import QUrl, qInstallMessageHandler
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import (QQmlEngine, QQmlComponent, QQmlExpression,
                           QQmlListReference)

W = os.path.dirname(os.path.abspath(__file__))
SRC = "/usr/share/ncde"
shadow = tempfile.mkdtemp(prefix="filigree-probe4.")
for name in os.listdir(SRC):
    p = os.path.join(SRC, name)
    if os.path.isfile(p):
        os.symlink(p, os.path.join(shadow, name))
for staged in ("FiligreeTab.qml", "NCDESlider.qml", "SettingsColorWheel.qml"):
    dst = os.path.join(shadow, staged)
    os.remove(dst)
    shutil.copy(os.path.join(W, staged), dst)

messages = []
qInstallMessageHandler(lambda m, c, s: messages.append(s))
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

def walk(item, eff=True):
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

def row_of_label(txt):
    """the Row that owns a given label Text (its QML parent item)"""
    ts = [t for t, v in walk(root) if t.property("text") == txt]
    return ts[0].parentItem() if ts and hasattr(ts[0], "parentItem") else (ts[0].parent() if ts else None)

# ── _dispName mapping ──
exp = {"topPanel": "Top Panel", "bottomPanel": "Bottom Panel", "dock": "Dock",
       "clock": "Clock", "space": "Space", "weather": "Weather", "stats": "Stats",
       "salon": "Salon", "laombre": "Ghost"}
for k, n in exp.items():
    got = js(f"_dispName('{k}')")
    if got != n: fails.append(f"_dispName({k}) = {got!r} != {n!r}")
print("_dispName mapping checked (9 keys, laombre -> Ghost)")

# ── popup opens on the exact colour it was given ──
for hexv, hue, sat, val in [("#804020", 20.0, 0.75, 128/255),
                            ("#808080", 0.0, 0.0, 128/255),
                            ("#404040", 0.0, 0.0, 64/255),
                            ("#000000", 0.0, 0.0, 0.0)]:
    js(f"openColorPopup('T', '{hexv}', function(c){{}})"); app.processEvents()
    h = js("colorWheel.hue"); s = js("colorWheel.saturation"); v = js("colorWheel.value")
    if abs(h - hue) > 0.5 or abs(s - sat) > 0.01 or abs(v - val) > 0.01:
        fails.append(f"seed {hexv}: hue={h} sat={s} val={v} (want {hue}/{sat}/{val:.3f})")
    cur = js("colorWheel.currentHex")
    if str(cur).upper() != hexv.upper():
        fails.append(f"round-trip {hexv} -> currentHex {cur}")
    js("_colorPopupOpen = false")
print("popup HSV seeding: colour, grey, dark grey, black all round-trip")

# ── brightness no longer sticky: dark seed then bright seed ──
js("openColorPopup('T', '#000000', function(c){})"); js("_colorPopupOpen = false")
js("openColorPopup('T', '#FF0000', function(c){})")
if abs(js("colorWheel.value") - 1.0) > 0.01: fails.append("brightness stuck at previous open")
js("_colorPopupOpen = false"); app.processEvents()

# ── humanised headings ──
root.setProperty("_activeTab", "glass"); app.processEvents()
for key, name in [("topPanel", "TOP PANEL"), ("bottomPanel", "BOTTOM PANEL"), ("dock", "DOCK")]:
    root.setProperty("selSurface", key); app.processEvents()
    if len(vis_texts(name + " — GLASS")) != 1:
        fails.append(f"heading '{name} — GLASS' not visible for {key}")
root.setProperty("_activeTab", "widgets"); app.processEvents()
for key, name in [("clock", "CLOCK"), ("laombre", "GHOST")]:
    root.setProperty("selWidget", key); app.processEvents()
    if len(vis_texts(name + " — GLASS")) != 1:
        fails.append(f"widgets-tab heading '{name} — GLASS' not visible for {key}")
print("headings humanised: TOP PANEL/BOTTOM PANEL/DOCK + CLOCK/GHOST — GLASS")

# ── widget preview text: gilt4 fallback when fill unset, honours explicit ──
root.setProperty("selWidget", "clock"); app.processEvents()
sample = [t for t, v in walk(root) if t.property("text") == "10:24" and v]
if not sample:
    fails.append("clock preview sample text not found")
else:
    c = sample[0].property("color")
    if c.name().lower() != "#e9c97c":
        fails.append(f"preview fill fallback {c.name()} != gilt4 #e9c97c")
    js("_updateWidg('clock','fill','#112233')"); app.processEvents()
    c = sample[0].property("color")
    if c.name().lower() != "#112233":
        fails.append(f"preview explicit fill {c.name()} != #112233")
    js("_updateWidg('clock','fill','')"); app.processEvents()
print("preview text colour: gilt4 fallback + explicit fill honoured")

# ── dependent rows dim+disable ──
root.setProperty("_activeTab", "type"); app.processEvents()
if vis_texts("Outline width"): fails.append("old 'Outline width' label still present")
checks = [("Thickness", "textOutlineEnabled"), ("Blur", "textShadowEnabled"),
          ("Offset X", "textShadowEnabled"), ("Offset Y", "textShadowEnabled")]
for label, flag in checks:
    js(f"settings.{flag} = false"); app.processEvents()
    r = row_of_label(label)
    if r is None: fails.append(f"row for '{label}' not found"); continue
    if abs(r.property("opacity") - 0.45) > 0.01 or r.property("enabled"):
        fails.append(f"'{label}' row not dimmed/disabled while {flag}=false")
    js(f"settings.{flag} = true"); app.processEvents()
    if abs(r.property("opacity") - 1.0) > 0.01 or not r.property("enabled"):
        fails.append(f"'{label}' row not re-enabled when {flag}=true")
    js(f"settings.{flag} = false")
app.processEvents()
print("Thickness/Blur/Offset rows dim+disable with their feature flag")

# ── Solei-Lune chips still build, one per mode ──
root.setProperty("_activeTab", "glass"); app.processEvents()
for t in ("Auto", "Light", "Dark"):
    if len(vis_texts(t)) != 1: fails.append(f"Solei-Lune chip '{t}' visible count != 1")
print("Solei-Lune chips built")

# ── scrim/dialog mapping used by tap-outside-cancels ──
js("openColorPopup('T', '#804020', function(c){})"); app.processEvents()
if js("popDialog.width") != 280: fails.append("popDialog id/geometry missing")
outside = js("(function(){ var p = popDialog.mapFromItem(popScrim, 2, 2); return (p.x < 0 || p.y < 0) })()")
inside = js("(function(){ var p = popDialog.mapFromItem(popScrim, popScrim.width/2, popScrim.height/2);"
            " return (p.x >= 0 && p.y >= 0 && p.x <= popDialog.width && p.y <= popDialog.height) })()")
if outside is not True: fails.append("corner point did not map outside dialog")
if inside is not True: fails.append("centre point did not map inside dialog")
js("_colorPopupOpen = false"); app.processEvents()
print("scrim->dialog coordinate mapping correct (outside/inside)")

# ── Reset Typography resync targets exist ──
if js("spacingSlider.minValue") != 0 or js("leadingSlider.minValue") != 8:
    fails.append("spacingSlider/leadingSlider ids do not resolve")
print("spacing/leading slider ids resolve for the reset resync")

# ── no invalid-colour or binding-loop noise from our files ──
noise = [m for m in messages if ("FiligreeTab" in m or "SettingsColorWheel" in m)
         and ("Unable to assign" in m or "Binding loop" in m or "TypeError" in m)]
if noise:
    fails.append(f"{len(noise)} QML noise messages: {noise[:5]}")
print("no invalid-colour / binding-loop / TypeError noise")

print("FAILS:", fails if fails else "none")
sys.exit(1 if fails else 0)
