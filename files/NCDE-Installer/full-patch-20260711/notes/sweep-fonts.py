#!/usr/bin/env python3
# NCDE fonts wiring sweep (2026-07-21). For every QML site using the body font
# token (font.family: theme.fontFamily), add the weight/italic/letterSpacing
# bindings ThemeTokens already exports -- and lineHeight only on wrapped text.
# Block-aware: a site whose enclosing element already sets any of these keeps
# its own value (intentional bold titles etc. are untouched). Conservative:
# ambiguous sites are SKIPPED and logged, never guessed at.
import os, re, sys, json

LIVE = "/usr/share/ncde"
PAYLOAD = os.path.expanduser("~/my-project/files/full-patch-20260711/src/usr/share/ncde")
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "sweep-out")
EXCLUDE = {"FiligreeTab.qml", "FontsTab.qml", "ThemeTokens.qml", "SetTheme.qml"}
TOKEN = "font.family: theme.fontFamily"

def enclosing_block(text, pos):
    """Return (start,end) of the innermost {...} containing pos."""
    depth = 0
    start = None
    for i in range(pos, -1, -1):
        c = text[i]
        if c == '}':
            depth += 1
        elif c == '{':
            if depth == 0:
                start = i
                break
            depth -= 1
    if start is None:
        return None
    depth = 0
    for i in range(start, len(text)):
        if text[i] == '{':
            depth += 1
        elif text[i] == '}':
            depth -= 1
            if depth == 0:
                return (start, i)
    return None

def sweep_file(path):
    src = open(path).read()
    out = []
    last = 0
    stats = {"wired": 0, "skipped": 0, "lineheight": 0}
    for m in re.finditer(re.escape(TOKEN) + r"(?![\w.])", src):
        blk = enclosing_block(src, m.start())
        if blk is None:
            stats["skipped"] += 1
            print(f"  SKIP (no block): {path} @ {m.start()}")
            continue
        block = src[blk[0]:blk[1]]
        adds = []
        if not re.search(r"font\.(weight|bold)\s*:", block):
            adds.append("font.weight: theme.fontWeight")
        if "font.italic" not in block:
            adds.append("font.italic: theme.fontItalic")
        if "font.letterSpacing" not in block:
            adds.append("font.letterSpacing: theme.letterSpacing")
        lh = ("wrapMode" in block and "lineHeight" not in block)
        out.append(src[last:m.end()])
        if adds:
            out.append("; " + "; ".join(adds))
            stats["wired"] += 1
        if lh:
            out.append("; lineHeight: theme.lineHeight")
            stats["lineheight"] += 1
        last = m.end()
    out.append(src[last:])
    return "".join(out), stats

def main():
    os.makedirs(OUT, exist_ok=True)
    report = {}
    names = set()
    for base in (LIVE, os.path.join(LIVE, "controls")):
        for f in os.listdir(base):
            if f.endswith(".qml") and ".prebak" not in f:
                rel = f if base == LIVE else "controls/" + f
                names.add(rel)
    for rel in sorted(names):
        if os.path.basename(rel) in EXCLUDE:
            continue
        pay = os.path.join(PAYLOAD, rel)
        live = os.path.join(LIVE, rel)
        srcpath = pay if os.path.exists(pay) else live
        if TOKEN not in open(srcpath).read():
            continue
        new, stats = sweep_file(srcpath)
        dst = os.path.join(OUT, rel)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        open(dst, "w").write(new)
        report[rel] = {"base": "payload" if srcpath == pay else "live", **stats}
    print(json.dumps(report, indent=1))
    total = sum(r["wired"] for r in report.values())
    skipped = sum(r["skipped"] for r in report.values())
    print(f"TOTAL files={len(report)} wired={total} lineheight={sum(r['lineheight'] for r in report.values())} skipped={skipped}", file=sys.stderr)

main()
