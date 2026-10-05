#!/usr/bin/env python3
"""Apply the WCAG-contrast accent-color fix (2026-08-06) to a COPY of LaPivot.
Same safe pattern as apply-iris.py: pure in-place, same-length (7-byte) string
writes; every write verifies the old bytes first and aborts on any mismatch.
Usage:
    python3 apply-iris-contrast.py <input-binary> <output-binary> [fix.json] [palettes.json]
Exits 0 on success OR if the binary already holds the new values; exits
nonzero (touching nothing) on any unexpected byte."""
import json, subprocess, sys

SRC, DST = sys.argv[1], sys.argv[2]
FIXFILE = sys.argv[3] if len(sys.argv) > 3 else "iris-contrast-fix.json"
PALFILE = sys.argv[4] if len(sys.argv) > 4 else "iris-palettes.json"
TABLES = [0x213500, 0x2155c0, 0x217000]
ENTRY = 72
ACCENT_FIELD_INDEX = 3  # per apply-iris.py's COLOR = {"accent": 3, ...}

data = bytearray(open(SRC, "rb").read())

relocs = {}
out = subprocess.run(["readelf", "-r", SRC], capture_output=True, text=True).stdout
for line in out.splitlines():
    p = line.split()
    if len(p) >= 4 and p[2] == "R_X86_64_RELATIVE":
        relocs[int(p[0], 16)] = int(p[3], 16)

fixes = json.load(open(FIXFILE))
pals = {p["id"]: p["i"] for p in json.load(open(PALFILE))}

plan = {}  # slot -> (old_bytes, new_bytes)
for f in fixes:
    e = pals[f["id"]]
    old_v, new_v = f["old"], f["new"]
    for base in TABLES:
        ptr_off = base + e * ENTRY + ACCENT_FIELD_INDEX * 8
        slot = relocs.get(ptr_off)
        if slot is None:
            sys.exit(f"ABORT: no reloc for entry {e} ({f['id']}) accent at {ptr_off:#x}")
        old_b = old_v.encode() + b"\x00"
        new_b = new_v.encode() + b"\x00"
        if len(old_b) != 8 or len(new_b) != 8:
            sys.exit(f"ABORT: bad length {old_v}->{new_v}")
        prev = plan.get(slot)
        if prev is not None and prev != (old_b, new_b):
            sys.exit(f"ABORT: conflicting plans for slot {slot:#x}")
        plan[slot] = (old_b, new_b)

n_old = sum(1 for s, (o, n) in plan.items() if bytes(data[s:s + 8]) == o)
n_new = sum(1 for s, (o, n) in plan.items() if bytes(data[s:s + 8]) == n)
if n_new == len(plan):
    open(DST, "wb").write(data)
    print(f"ALREADY APPLIED: all {len(plan)} slots hold the new contrast-fixed values.")
    sys.exit(0)
if n_old != len(plan):
    for s, (o, n) in sorted(plan.items()):
        cur = bytes(data[s:s + 8])
        if cur not in (o, n):
            sys.exit(f"ABORT: slot {s:#x} holds {cur!r}, expected {o!r} or {n!r} "
                      f"-- binary is not the known post-Iris-Chroma-redesign state; refusing to touch it")
    sys.exit(f"ABORT: mixed state ({n_new}/{len(plan)} slots already new) -- refusing")

writes = {}
for slot, (old_b, new_b) in plan.items():
    data[slot:slot + 8] = new_b
    writes[slot] = (old_b, new_b)

open(DST, "wb").write(data)
print(f"patched slots: {len(writes)} (x8 bytes = {len(writes) * 8} bytes changed)")

pdata = open(DST, "rb").read()


def cstr(off):
    end = pdata.index(b"\x00", off)
    return pdata[off:end].decode()


fixes_by_id = {f["id"]: f["new"] for f in fixes}
fails = 0
for base in TABLES:
    for pid, e in pals.items():
        ptr_off = base + e * ENTRY + ACCENT_FIELD_INDEX * 8
        got = cstr(relocs[ptr_off])
        if pid in fixes_by_id:
            want = fixes_by_id[pid]
            if got != want:
                print(f"VERIFY FAIL table@{base:#x} entry {e} ({pid}) accent: {got} != {want}")
                fails += 1

orig = open(SRC, "rb").read()
diff = sum(1 for a, b in zip(orig, pdata) if a != b)
print(f"total differing bytes vs original: {diff} (expected <= {len(writes) * 8})")
if fails or len(orig) != len(pdata):
    sys.exit(f"VERIFICATION FAILED: {fails} mismatches")
print("VERIFIED: all three kPresets copies match the WCAG-contrast-fixed accent set; "
      "everything else untouched; file size unchanged.")
