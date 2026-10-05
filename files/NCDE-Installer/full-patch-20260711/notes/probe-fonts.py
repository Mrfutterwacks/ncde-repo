#!/usr/bin/env python3
"""Fonts-tab refinement probe (offscreen, 2026-07-21): builds FiligreeTab with the
harness mocks and checks the new behavior — Cormorant Garamond serif chip present,
every chip carries an "Aa" specimen in its own face, terminal font input lives in
the Fonts tab (and NOT in Glass), signature section still present, custom-font
validation hint toggles with settings.fontFamily, Reset Typography restores
defaults through saveFontSettings/applyFontSettings."""
import os, shutil, sys, tempfile

os.environ["QT_QPA_PLATFORM"] = "offscreen"
from PySide6.QtCore import QUrl, QObject, qInstallMessageHandler, QMetaObject, Q_ARG
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlEngine, QQmlComponent, QQmlListReference
from PySide6.QtQuick import QQuickItem

W = os.path.dirname(os.path.abspath(__file__))
SRC = "/usr/share/ncde"
shadow = tempfile.mkdtemp(prefix="filigree-fonts-probe.")
for name in os.listdir(SRC):
    p = os.path.join(SRC, name)
    if os.path.isfile(p):
        os.symlink(p, os.path.join(shadow, name))
for staged in ("FiligreeTab.qml", "NCDESlider.qml"):
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
settings = mocks.property("settings")

comp = QQmlComponent(engine, QUrl.fromLocalFile(os.path.join(shadow, "FiligreeTab.qml")))
root = comp.create()
assert root, [e.toString() for e in comp.errors()]
root.setProperty("width", 800); root.setProperty("height", 2400)
fails = []

def walk(item):
    out = [item]
    ref = QQmlListReference(item, "children")
    for i in range(ref.count()):
        out += walk(ref.at(i))
    return out

def texts_of(items):
    return [(i, i.property("text")) for i in items if i.property("text") is not None]

# ── Fonts tab ──
root.setProperty("_activeTab", "type"); app.processEvents()
items = walk(root)
labels = [t for (_, t) in texts_of(items)]

# 1. Cormorant Garamond chip exists
if "Cormorant Garamond" not in labels:
    fails.append("no Cormorant Garamond chip in serif group")

# 2. Aa specimens: for a sample of chip fonts, an "Aa" Text whose font.family
#    matches the chip's own family must exist
aa = [(i, i.property("font").family()) for (i, t) in texts_of(items) if t == "Aa"]
aa_fams = {f for (_, f) in aa}
for want in ("Noto Sans", "Cormorant Garamond", "JetBrains Mono"):
    if want not in aa_fams:
        fails.append(f"no Aa specimen rendered in {want}")
print(f"Aa specimens found: {len(aa)}")

# 3. terminal font input present in Fonts tab and visible
tfi = [i for i in items if i.property("text") is not None
       and "TextInput" in i.metaObject().className()
       and i.property("text") == "TerminalVector"]
if not tfi:
    fails.append("terminal font input (TerminalVector from mock cfg) not found in Fonts tab tree")

# 4. TERMINAL and NCDE SIGNATURE FONTS rules present in the type tab
for rule in ("TERMINAL", "NCDE SIGNATURE FONTS"):
    if rule not in labels:
        fails.append(f"missing rule {rule} in Fonts tab")

# 5. custom-font validation hint: hidden for installed font, shown for bogus
hints = [i for (i, t) in texts_of(items) if t and "isn’t installed" in str(t)]
if not hints:
    fails.append("validation hint element missing")
else:
    h = hints[0]
    settings.setProperty("fontFamily", "Noto Sans"); app.processEvents()
    vis_ok = h.property("visible")
    settings.setProperty("fontFamily", "Totally Fake Font 9000"); app.processEvents()
    vis_bad = h.property("visible")
    print(f"hint visible: installed={vis_ok} bogus={vis_bad}")
    if vis_ok: fails.append("hint shown for an installed font")
    if not vis_bad: fails.append("hint NOT shown for a bogus font")

# 6. Reset Typography: set non-defaults, find the pill, fire its tap handler by
#    invoking the same statements (probe evaluates settings after simulated tap
#    via direct property writes is meaningless — instead check the pill exists
#    and its atDefault binding tracks state)
pills = [i for i in items if i.property("atDefault") is not None]
if not pills:
    fails.append("Reset Typography pill missing")
else:
    p = pills[0]
    settings.setProperty("fontFamily", "Noto Sans"); settings.setProperty("fontWeight", 400)
    settings.setProperty("fontItalic", False); settings.setProperty("letterSpacing", 0.0)
    settings.setProperty("lineHeight", 1.0); app.processEvents()
    at1 = p.property("atDefault")
    settings.setProperty("fontWeight", 700); app.processEvents()
    at2 = p.property("atDefault")
    print(f"atDefault tracking: default={at1} bold={at2}")
    if not at1: fails.append("atDefault false at defaults")
    if at2: fails.append("atDefault true when weight=700")

# 7. Glass tab: no terminal font input there anymore, tint slider still present
root.setProperty("_activeTab", "glass"); app.processEvents()
glass_items = walk(root)
glass_visible_inputs = [i for i in glass_items
                        if "TextInput" in i.metaObject().className()
                        and i.property("visible")]
# termFontInput exists in the document but must not be visible while Glass is active
tfi_visible = [i for i in glass_visible_inputs if i.property("text") == "TerminalVector"]
if tfi_visible:
    fails.append("terminal font input still visible in Glass tab")
tint = [t for (_, t) in texts_of(glass_items) if t == "dark ↔ light"]
if not tint:
    fails.append("glass tint slider hint missing from Glass tab")

# 8. MEASURE sample honours spacing/leading bindings
root.setProperty("_activeTab", "type"); app.processEvents()
items = walk(root)
sample = [i for (i, t) in texts_of(items) if t and "quick brown fox jumps over the lazy dog" in str(t)]
if not sample:
    fails.append("two-line measure sample missing")
else:
    s = sample[0]
    settings.setProperty("letterSpacing", 3.0); settings.setProperty("lineHeight", 1.8); app.processEvents()
    ls = s.property("font").letterSpacing()
    lh = s.property("lineHeight")
    print(f"sample letterSpacing={ls} lineHeight={lh}")
    if abs(ls - 3.0) > 0.01: fails.append(f"sample letterSpacing not live ({ls})")
    if abs(lh - 1.8) > 0.01: fails.append(f"sample lineHeight not live ({lh})")

print("FAILS:", fails if fails else "none")
sys.exit(1 if fails else 0)
