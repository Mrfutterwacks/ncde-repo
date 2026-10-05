#!/bin/bash
# build_main_test.sh <project-local-build-dir> <output-binary> [test-source...]
set -euo pipefail

L="$(cd "$(dirname "$0")/.." && pwd)"
W="$1"
OUT="$2"
shift 2
QT="$(pkg-config --cflags --libs Qt6Core Qt6Gui Qt6Qml Qt6Quick Qt6DBus Qt6Network Qt6OpenGL)"
XCB="$(pkg-config --cflags --libs xcb)"

mkdir -p "$W"
MOC_HEADERS=(
    "$L/src/AnimPolicy.h" "$L/src/NCDEEngine.h" "$L/src/Theme.h"
    "$L/src/CursorManager.h" "$L/src/FontManager.h" "$L/src/IconProvider.h"
    "$L/src/XSettingsManager.h" "$L/src/ScreenInfo.h" "$L/src/NCDEWindowManager.h"
    "$L/src/WindowTyper.h" "$L/src/NCDEWorkspace.h" "$L/src/IdleInhibitService.h"
    "$L/src/GliaSystemMenus.h" "$L/src/AppMenuModel.h" "$L/src/Lelan.h"
    "$L/src/Settings.h" "$L/src/NCDEGeo.h" "$L/src/CalendarBackend.h"
    "$L/src/LeapFrogPond.h" "$L/src/WidgetData.h" "$L/src/NotificationManager.h"
    "$L/src/Launcher.h" "$L/src/HudManager.h"
)

SRCS=()
for h in "${MOC_HEADERS[@]}"; do
    if [ -f "$h" ] && grep -q Q_OBJECT "$h"; then
        /usr/lib/qt6/moc "$h" -o "$W/moc_$(basename "$h" .h).cpp"
        SRCS+=("$W/moc_$(basename "$h" .h).cpp")
    fi
done

for f in "$@"; do
    SRCS+=("$f")
    if grep -q Q_OBJECT "$f" 2>/dev/null; then
        /usr/lib/qt6/moc "$f" -o "$W/$(basename "$f" .cpp).moc"
        SRCS+=("$W/$(basename "$f" .cpp).moc")
    fi
done

for f in "${SRCS[@]}"; do
    b="$(basename "$f" .cpp)"
    g++ -std=c++17 -fPIC -Wall -Wextra -Wno-sfinae-incomplete \
        -I"$L/src" -I"$W" -c "$f" -o "$W/$b.o" $QT $XCB
done

python3 - "$W" <<'PY'
from pathlib import Path
import re
import subprocess
import sys

work = Path(sys.argv[1])
objects = sorted(work.glob("*.o"))
undefined = subprocess.check_output(
    ["nm", "--undefined-only", *map(str, objects)], text=True
)
owned = re.compile(
    r"^(?:AnimPolicy|AppMenuModel|CalendarBackend|CursorManager|FontManager|"
    r"GliaSystemMenus|HudManager|IconProvider|IdleInhibitService|Launcher|"
    r"LeapFrogPond|Lelan|NCDEEngine|NCDEGeo|NCDEWindowManager|NCDEWorkspace|"
    r"NotificationManager|ScreenInfo|Settings|Theme|WidgetData|WindowTyper|"
    r"XSettingsManager)::"
)
symbols = set()
for line in undefined.splitlines():
    fields = line.split()
    if not fields:
        continue
    symbol = fields[-1]
    if not symbol.startswith("_Z"):
        continue
    demangled = subprocess.check_output(["c++filt", symbol], text=True).strip()
    if owned.match(demangled):
        symbols.add(symbol)

stubs = [".text", "ncde_stub_trap: ud2"]
stubs.extend(f".globl {symbol}\n.set {symbol}, ncde_stub_trap" for symbol in sorted(symbols))
(work / "stubs.s").write_text("\n".join(stubs) + "\n")
PY

as "$W/stubs.s" -o "$W/stubs.o"
g++ -o "$OUT" "$W"/*.o $QT $XCB
echo "Built $OUT"
