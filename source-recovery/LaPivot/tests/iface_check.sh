#!/bin/bash
# iface_check.sh <Class> — prove a rebuilt class exposes EXACTLY the oracle's Qt interface.
# moc the header, link it with trap stubs for not-yet-written methods, dump its metaobject with
# the same routine that dumped the oracle (tools/metadump.cpp), diff against
# interfaces/LaPivot-metaobjects.h. No output from diff + "IDENTICAL" = QML sees the same class.
set -euo pipefail
C="$1"; L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
QT="$(pkg-config --cflags --libs Qt6Core Qt6DBus Qt6Gui Qt6Qml)"
/usr/lib/qt6/moc "$L/src/$C.h" -o "$W/moc.cpp"
g++ -std=c++17 -fPIC -c -Wno-sfinae-incomplete -I"$L/src" "$W/moc.cpp" -o "$W/moc.o" $QT
sed -e 's/__attribute__((constructor)) static void run()/void runUnused()/' \
    -e 's/^static void dump(const QMetaObject \*mo)/void dumpMeta(const QMetaObject *mo)/' \
    -e 's/        dump(reinterpret_cast/        dumpMeta(reinterpret_cast/' "$L/tools/metadump.cpp" > "$W/dump.cpp"
printf '#include "%s.h"\nvoid dumpMeta(const QMetaObject *);\nint main(){ dumpMeta(&%s::staticMetaObject); }\n' "$C" "$C" > "$W/main.cpp"
{ echo .text; echo 'ncde_stub_trap: ud2'
  nm --undefined-only "$W/moc.o" | awk -v c="${#C}$C" '$2 ~ "^_ZN"c || $2 ~ "^_ZNK"c {print ".globl "$2"\n.set "$2", ncde_stub_trap"}'; } > "$W/stubs.s"
as "$W/stubs.s" -o "$W/stubs.o"
g++ -std=c++17 -fPIC -Wno-sfinae-incomplete -I"$L/src" -o "$W/check" "$W/main.cpp" "$W/dump.cpp" "$W/moc.o" "$W/stubs.o" $QT
"$W/check" > "$W/new.txt"
sed -n "/^class $C /,/^};/p" "$L/interfaces/LaPivot-metaobjects.h" > "$W/old.txt"
# Additions are allowed ONLY if declared in tests/iface_additions/<Class>.txt (one exact dumped line
# each, with the reason in a comment). Everything the oracle has must be present unchanged, in order.
ADD="$L/tests/iface_additions/$C.txt"; touch "$W/add.txt"
[ -f "$ADD" ] && grep -v '^\s*#' "$ADD" | sed '/^\s*$/d' > "$W/add.txt"
if [ -s "$W/add.txt" ]; then grep -vxF -f "$W/add.txt" "$W/new.txt" > "$W/new_minus_add.txt" || true
else cp "$W/new.txt" "$W/new_minus_add.txt"; fi
if diff -B "$W/old.txt" "$W/new_minus_add.txt"; then
  n_decl=$(wc -l < "$W/add.txt"); n_add=0
  [ -s "$W/add.txt" ] && n_add=$(grep -cxF -f "$W/add.txt" "$W/new.txt" || true)
  [ "$n_add" = "$n_decl" ] || { echo "$C: declared additions not all present ($n_add of $n_decl)"; exit 1; }
  echo "$C: ORACLE INTERFACE PRESERVED ($(grep -c Q_PROPERTY "$W/old.txt") props, $(grep -c 'signal:' "$W/old.txt") signals, $(grep -c 'slot:' "$W/old.txt") slots, $(grep -c Q_INVOKABLE "$W/old.txt") invokables) + $n_add declared addition(s)"
else
  exit 1
fi
