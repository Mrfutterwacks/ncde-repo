#!/usr/bin/env python3
"""qml_binding_audit.py [qml_dir] — every `ctx.member` / gv(ctx,"member") the shell QML uses, checked
against the REAL interface of the C++ object behind that context name (interfaces/LaPivot-metaobjects.h,
the oracle's own moc metadata). A missing member is a control/display that silently does nothing
(QML's typeof guards hide it). Context names -> classes come from LaPivot main()'s setContextProperty
calls (decomp/_global.c)."""
import re, sys, glob, os, collections, pathlib
ROOT = pathlib.Path(__file__).resolve().parent.parent
CTX = {"lelan": "Lelan", "ncde": "NCDEEngine", "settings": "Settings", "theme": "Theme",
       "fontMgr": "FontManager", "widget_data": "WidgetData", "animPolicy": "AnimPolicy",
       "launcher": "Launcher", "notifications": "NotificationManager", "windowMgr": "NCDEWindowManager",
       "calBackend": "CalendarBackend", "ncdeWorkspace": "NCDEWorkspace", "appMenuModel": "AppMenuModel",
       "pond": "LeapFrogPond", "gliaSystem": "GliaSystemMenus", "geo": "NCDEGeo", "hudManager": "HudManager"}
QOBJECT = {"objectName", "destroyed", "deleteLater", "objectNameChanged", "toString", "parent"}
# QAbstractItemModel API every list-model context object has (NCDEWindowManager, AppMenuModel, ...)
MODEL = {"index", "data", "rowCount", "columnCount", "roleNames", "count", "setData", "headerData",
         "rowsInserted", "rowsRemoved", "dataChanged", "modelReset", "layoutChanged"}
MODEL_CLASSES = {"NCDEWindowManager", "AppMenuModel"}
src = (ROOT / "interfaces" / "LaPivot-metaobjects.h").read_text()
def members(cls):
    body = re.search(r"^class %s .*?^};" % cls, src, re.S | re.M)
    if not body: return set()
    b = body.group(0)
    names = set(re.findall(r"Q_PROPERTY\([^ ]+(?: [^ ]+)*? (\w+) READ", b))
    names |= set(re.findall(r"(?:signal:|slot:|Q_INVOKABLE)\s+\w+\s+[\w:<>, *&]+?\s+(\w+)\(", b))
    names |= {"on" + n[0].upper() + n[1:] for n in list(names)}          # QML signal handlers
    add = ROOT / "tests" / "iface_additions" / (cls + ".txt")        # declared rebuild additions
    if add.exists():
        a = add.read_text()
        names |= set(re.findall(r"Q_PROPERTY\([^ ]+ (\w+) READ", a)) | set(re.findall(r"\s(\w+)\(\);", a))
    return names | QOBJECT | (MODEL if cls in MODEL_CLASSES else set())
qml_dir = sys.argv[1] if len(sys.argv) > 1 else "/usr/share/ncde"
all_files = [f for f in glob.glob(os.path.join(qml_dir, "**", "*.qml"), recursive=True) if "prebak" not in f]
# Only files LaPivot actually loads: closure from main.qml over component types (Foo { / Foo.qml)
by_type = {os.path.splitext(os.path.basename(f))[0]: f for f in all_files
           if os.path.dirname(f) == qml_dir or "/controls/" in f}
def refs(f):
    t = open(f, errors="ignore").read()
    t = re.sub(r"//[^\n]*", "", t)
    out = set(re.findall(r"\b([A-Z]\w+)\s*\{", t)) | set(re.findall(r"\b([A-Z]\w+)\.qml\b", t))   # component use + Loader/tab "X.qml"
    return {by_type[n] for n in out if n in by_type}
seen, todo = set(), [os.path.join(qml_dir, "main.qml")]
while todo:
    f = todo.pop()
    if f in seen or not os.path.exists(f): continue
    seen.add(f); todo.extend(refs(f) - seen)
files = sorted(seen)
print(f"LaPivot loads {len(files)} of {len(all_files)} QML files (closure from main.qml)")
used = collections.defaultdict(lambda: collections.defaultdict(set))
for f in files:
    s = open(f, errors="ignore").read()
    s = re.sub(r"//[^\n]*", "", s)                                        # ignore comments
    gvs = [(m.group(1), m.group(2)) for m in re.finditer(r'\bgv\(\s*(\w+)\s*,\s*"(\w+)"', s)]
    s = re.sub(r'"(?:[^"\\\n]|\\.)*"', '""', s)                          # drop string contents
    webview = "WebEngineView" in s
    for ctx in CTX:
        # a file that declares `id: <ctx>` or `property ... <ctx>` shadows the context object
        if re.search(r"\bid\s*:\s*%s\b|\bproperty\s+\w+\s+%s\b" % (ctx, ctx), s):
            continue
        if ctx == "settings" and webview:                                 # WebEngineView.settings
            continue
        for m in re.finditer(r"(?<![\w.])%s\.(\w+)" % ctx, s):
            used[ctx][m.group(1)].add(os.path.relpath(f, qml_dir))
        for c, n in gvs:
            if c == ctx:
                used[ctx][n].add(os.path.relpath(f, qml_dir))
total = 0
for ctx, cls in CTX.items():
    have = members(cls)
    miss = {n: fs for n, fs in used[ctx].items() if n not in have}
    if not miss: continue
    print(f"{ctx} ({cls}): {len(miss)} missing of {len(used[ctx])} used")
    for n, fs in sorted(miss.items()):
        elsewhere = [c for c, k in CTX.items() if k != cls and n in members(k)]
        print(f"   {n:24s} in {', '.join(sorted(fs))[:70]}" + (f"   -> exists on {', '.join(elsewhere)}" if elsewhere else ""))
    total += len(miss)
print(f"TOTAL missing bindings: {total}")
