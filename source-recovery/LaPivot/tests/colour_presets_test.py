#!/usr/bin/env python3
"""colour_presets_test.py [engine-dump.json] — prove the rebuilt NCDEEngine carries the Iris Chroma
palettes IN SOURCE, so deploy_lapivot()'s three binary transforms are no longer needed.

Checks (all read-only; nothing is written outside the scratch dir given by $SCRATCH or /tmp):
 1. RAW staged LaPivot (files/full-patch-20260711/src/usr/local/bin/LaPivot) + the three transforms
    applied SEMANTICALLY from the JSON payload (apply-iris.py: accent/border/panelBg/surface -> *2;
    apply-iris-contrast.py: accent old->new; apply-iris-widen.py: accent old->new), each step
    verifying the old value first exactly like the byte patchers do  ==  src/NCDEEngine_presets.inc
 2. the PATCHED live /usr/local/bin/LaPivot (read-only)                          ==  src/NCDEEngine_presets.inc
 3. (if an engine dump JSON is given) what the COMPILED rebuilt NCDEEngine::presets() returns
                                                                                  ==  src/NCDEEngine_presets.inc
Prints PASS/FAIL lines; exit 0 only when every check passes."""
import json, os, re, subprocess, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
MP = os.path.abspath(os.path.join(ROOT, "..", ".."))           # my-project
NOTES = os.path.join(MP, "files/full-patch-20260711/notes")
RAW = os.path.join(MP, "files/full-patch-20260711/src/usr/local/bin/LaPivot")
LIVE = "/usr/local/bin/LaPivot"
INC = os.environ.get("COLOUR_INC") or os.path.join(ROOT, "src/NCDEEngine_presets.inc")
F = ["id", "name", "dark", "accent", "border", "panelBg", "surface", "ink", "inkSoft"]
fails = 0

def check(ok, msg):
    global fails
    print(("PASS " if ok else "FAIL ") + msg)
    if not ok:
        fails += 1

def extract(path):
    data = open(path, "rb").read()
    rel = {}
    for line in subprocess.run(["readelf", "-rW", path], capture_output=True, text=True).stdout.splitlines():
        p = line.split()
        if len(p) >= 4 and p[2] == "R_X86_64_RELATIVE":
            rel[int(p[0], 16)] = int(p[3], 16)
    syms = subprocess.run(["nm", path], capture_output=True, text=True).stdout.splitlines()
    tabs = sorted(int(l.split()[0], 16) for l in syms if l.endswith("_ZN12ncde_presetsL8kPresetsE"))
    assert len(tabs) == 3, tabs
    cs = lambda o: data[o:data.index(b"\0", o)].decode()
    out = []
    for base in tabs:
        t = []
        for e in range(90):
            b = base + e * 72
            t.append({k: (data[b + 16] != 0) if k == "dark" else cs(rel[b + i * 8]) for i, k in enumerate(F)})
        out.append(t)
    check(out[0] == out[1] == out[2], f"{path}: the three kPresets copies are identical")
    return out[0]

def parse_inc(path):
    rows = []
    rx = re.compile(r'^\{ "((?:[^"\\]|\\.)*)", "((?:[^"\\]|\\.)*)", (true|false), "(#[0-9a-f]{6})", '
                    r'"(#[0-9a-f]{6})", "(#[0-9a-f]{6})", "(#[0-9a-f]{6})", "(#[0-9a-f]{6})", "(#[0-9a-f]{6})" \},$')
    for line in open(path, encoding="utf-8"):
        if line.startswith("{"):
            m = rx.match(line.rstrip("\n"))
            assert m, line
            g = list(m.groups())
            g[0] = json.loads('"' + g[0] + '"'); g[1] = json.loads('"' + g[1] + '"')
            g[2] = g[2] == "true"
            rows.append(dict(zip(F, g)))
    return rows

def diff(a, b, la, lb):
    n = 0
    for i, (x, y) in enumerate(zip(a, b)):
        for k in F:
            if x[k] != y[k]:
                n += 1
                if n <= 10:
                    print(f"   row {i} {x['id']}.{k}: {la}={x[k]} {lb}={y[k]}")
    return n + abs(len(a) - len(b))

inc = parse_inc(INC)
check(len(inc) == 90, f"src/NCDEEngine_presets.inc has {len(inc)} rows (want 90)")
check(len({r['id'] for r in inc}) == 90 and len({r['name'] for r in inc}) == 90, "ids and names unique")

# 1. raw + transforms (semantic)
raw = extract(RAW)
pals = json.load(open(os.path.join(NOTES, "iris-palettes.json")))
exp = [dict(r) for r in raw]
bad = 0
for p in pals:
    r = exp[p["i"]]
    if r["id"] != p["id"] or r["name"] != p["name"] or r["dark"] != p["dark"]:
        bad += 1
    for k in ("accent", "border", "panelBg", "surface", "ink", "inkSoft"):
        if r[k] != p[k]:
            bad += 1
        r[k] = p[k + "2"]
check(bad == 0, f"transform 1 apply-iris.py: raw binary holds every 'old' value of iris-palettes.json ({bad} mismatches)")
for fname, label in (("iris-contrast-fix.json", "transform 2 apply-iris-contrast.py"),
                     ("iris-accent-widen-fix.json", "transform 3 apply-iris-widen.py")):
    fx = json.load(open(os.path.join(NOTES, fname)))
    byid = {r["id"]: r for r in exp}
    bad = 0
    for f in fx:
        if byid[f["id"]]["accent"] != f["old"]:
            bad += 1
        byid[f["id"]]["accent"] = f["new"]
    check(bad == 0, f"{label}: {len(fx)} accents, every 'old' matched the previous stage ({bad} mismatches)")
n = diff(exp, inc, "raw+3transforms", "inc")
check(n == 0, f"RAW LaPivot + 3 transforms == src/NCDEEngine_presets.inc ({n} differing fields; "
              f"{sum(1 for a, b in zip(raw, inc) if a != b)} of 90 rows differ from the unpatched raw table)")

# 2. live patched binary
live = extract(LIVE)
n = diff(live, inc, "live", "inc")
check(n == 0, f"patched live {LIVE} kPresets == src/NCDEEngine_presets.inc ({n} differing fields)")

# 3. compiled engine
if len(sys.argv) > 1:
    eng = json.load(open(sys.argv[1]))
    eng = [{k: r[k] for k in F} for r in eng]
    n = diff(eng, inc, "engine", "inc")
    check(len(eng) == 90 and n == 0, f"compiled NCDEEngine::presets() ({len(eng)} rows) == src/NCDEEngine_presets.inc ({n} differing fields)")
    n = diff(eng, live, "engine", "live")
    check(n == 0, f"compiled NCDEEngine::presets() == patched live LaPivot ({n} differing fields)")

print("RESULT:", "ALL PASS" if fails == 0 else f"{fails} FAIL")
sys.exit(1 if fails else 0)
