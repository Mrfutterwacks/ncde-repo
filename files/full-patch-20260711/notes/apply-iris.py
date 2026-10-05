#!/usr/bin/env python3
"""Apply the approved Iris Chroma palette values to a COPY of LaPivot.
Pure in-place, same-length (7-byte) string writes; every write verifies the
old bytes first and aborts on any mismatch. Usage:
    python3 apply_iris.py <input-binary> <output-binary> [palettes.json]
Exits 0 on success OR if the binary already holds the new values; exits
nonzero (touching nothing) on any unexpected byte."""
import json, struct, subprocess, sys

SRC, DST = sys.argv[1], sys.argv[2]
PALETTES = sys.argv[3] if len(sys.argv) > 3 else "palettes-new.json"
TABLES = [0x213500, 0x2155c0, 0x217000]
ENTRY, COUNT = 72, 90
FIELDS = ["id", "name", "dark", "accent", "border", "panelBg", "surface", "ink", "inkSoft"]
COLOR = {"accent": 3, "border": 4, "panelBg": 5, "surface": 6}

data = bytearray(open(SRC, "rb").read())

relocs = {}
out = subprocess.run(["readelf", "-r", SRC], capture_output=True, text=True).stdout
for line in out.splitlines():
    p = line.split()
    if len(p) >= 4 and p[2] == "R_X86_64_RELATIVE":
        relocs[int(p[0], 16)] = int(p[3], 16)

pals = json.load(open(PALETTES))
assert len(pals) == COUNT

# collect all intended writes first so we can detect the three legal states:
# pristine (all slots = old), already-applied (all slots = new), or corrupt (abort).
plan = {}   # slot file offset -> (old bytes, new bytes)
for base in TABLES:
    for p in pals:
        e = p["i"]
        for field, fi in COLOR.items():
            old_v, new_v = p[field], p[field + "2"]
            if old_v == new_v:
                continue
            ptr_off = base + e*ENTRY + fi*8
            slot = relocs.get(ptr_off)
            if slot is None:
                sys.exit(f"ABORT: no reloc for entry {e} {field} at {ptr_off:#x}")
            old_b = old_v.encode() + b"\x00"
            new_b = new_v.encode() + b"\x00"
            if len(old_b) != 8 or len(new_b) != 8:
                sys.exit(f"ABORT: bad length {old_v}->{new_v}")
            prev = plan.get(slot)
            if prev is not None and prev != (old_b, new_b):
                sys.exit(f"ABORT: conflicting plans for slot {slot:#x}")
            plan[slot] = (old_b, new_b)

n_old = sum(1 for s, (o, n) in plan.items() if bytes(data[s:s+8]) == o)
n_new = sum(1 for s, (o, n) in plan.items() if bytes(data[s:s+8]) == n)
if n_new == len(plan):
    open(DST, "wb").write(data)
    print(f"ALREADY APPLIED: all {len(plan)} slots hold the new palette values.")
    sys.exit(0)
if n_old != len(plan):
    for s, (o, n) in sorted(plan.items()):
        cur = bytes(data[s:s+8])
        if cur not in (o, n):
            sys.exit(f"ABORT: slot {s:#x} holds {cur!r}, expected {o!r} or {n!r} "
                     f"— binary is not the known original; refusing to touch it")
    sys.exit(f"ABORT: mixed state ({n_new}/{len(plan)} slots already new) — refusing")

writes = {}
for slot, (old_b, new_b) in plan.items():
    data[slot:slot+8] = new_b
    writes[slot] = (old_b, new_b)

open(DST, "wb").write(data)
print(f"patched slots: {len(writes)} (x8 bytes = {len(writes)*8} bytes changed)")

# ---- verification: re-extract every table copy from the patched file ----
pdata = open(DST, "rb").read()
def cstr(off):
    end = pdata.index(b"\x00", off)
    return pdata[off:end].decode()

fails = 0
for base in TABLES:
    for p in pals:
        e = p["i"]
        for field, fi in COLOR.items():
            ptr_off = base + e*ENTRY + fi*8
            got = cstr(relocs[ptr_off])
            want = p[field + "2"]
            if got != want:
                print(f"VERIFY FAIL table@{base:#x} entry {e} {field}: {got} != {want}")
                fails += 1
        # ink/inkSoft/name/id must be untouched
        for field, fi in (("ink", 7), ("inkSoft", 8), ("name", 1), ("id", 0)):
            got = cstr(relocs[base + e*ENTRY + fi*8])
            want = p[field] if field in p else None
            if want is not None and got != want:
                print(f"VERIFY FAIL untouched field {field} entry {e}: {got} != {want}")
                fails += 1

orig = open(SRC, "rb").read()
diff = sum(1 for a, b in zip(orig, pdata) if a != b)
print(f"total differing bytes vs original: {diff} (expected <= {len(writes)*8})")
if fails or len(orig) != len(pdata):
    sys.exit(f"VERIFICATION FAILED: {fails} mismatches")
print("VERIFIED: all three kPresets copies match the approved palette set; "
      "names/ids/inks untouched; file size unchanged.")
