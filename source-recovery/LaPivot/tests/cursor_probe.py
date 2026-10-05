#!/usr/bin/env python3
# cursor_probe.py <label> x,y[:name] ... — warp the pointer to each point on $DISPLAY and print the cursor the
# X server is showing there (XFixesGetCursorImage): size, hotspot, cursor name atom, pixel hash, mean colour.
# Used by cursor_parity.sh to compare the oracle LaPivot with the rebuild (Kith cursor, 2026-10-01).
import ctypes, ctypes.util, hashlib, struct, sys, time

X = ctypes.CDLL(ctypes.util.find_library("X11")); XF = ctypes.CDLL(ctypes.util.find_library("Xfixes"))

class XFixesCursorImage(ctypes.Structure):
    _fields_ = [("x", ctypes.c_short), ("y", ctypes.c_short), ("width", ctypes.c_ushort), ("height", ctypes.c_ushort),
                ("xhot", ctypes.c_ushort), ("yhot", ctypes.c_ushort), ("cursor_serial", ctypes.c_ulong),
                ("pixels", ctypes.POINTER(ctypes.c_ulong)), ("atom", ctypes.c_ulong), ("name", ctypes.c_char_p)]

X.XOpenDisplay.restype = ctypes.c_void_p; X.XOpenDisplay.argtypes = [ctypes.c_char_p]
X.XDefaultRootWindow.restype = ctypes.c_ulong; X.XDefaultRootWindow.argtypes = [ctypes.c_void_p]
X.XWarpPointer.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.c_ulong, ctypes.c_int, ctypes.c_int,
                           ctypes.c_uint, ctypes.c_uint, ctypes.c_int, ctypes.c_int]
X.XSync.argtypes = [ctypes.c_void_p, ctypes.c_int]
XF.XFixesGetCursorImage.restype = ctypes.POINTER(XFixesCursorImage); XF.XFixesGetCursorImage.argtypes = [ctypes.c_void_p]

d = X.XOpenDisplay(None)
if not d:
    sys.exit("cannot open display")
root = X.XDefaultRootWindow(d)
label = sys.argv[1]
for spec in sys.argv[2:]:
    pt, _, name = spec.partition(":")
    x, y = map(int, pt.split(","))
    X.XWarpPointer(d, 0, root, 0, 0, 0, 0, x, y); X.XSync(d, 0); time.sleep(0.6)
    ci = XF.XFixesGetCursorImage(d).contents
    n = ci.width * ci.height
    px = [ci.pixels[i] & 0xffffffff for i in range(n)]
    h = hashlib.sha256(struct.pack("<%dI" % n, *px)).hexdigest()[:12]
    op = [p for p in px if (p >> 24) > 200]
    mean = tuple(sum((p >> s) & 255 for p in op) // max(1, len(op)) for s in (16, 8, 0)) if op else (0, 0, 0)
    nm = ci.name.decode() if ci.name else ""
    print("%s %-10s @%4d,%-4d %3dx%-3d hot %2d,%-2d name=%-12s px=%s mean=#%02x%02x%02x opaque=%d"
          % (label, name or "-", x, y, ci.width, ci.height, ci.xhot, ci.yhot, nm or "-", h, *mean, len(op)))
