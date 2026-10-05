#!/bin/bash
# network_live_test.sh — build tests/network_live_test.cpp against src/Lelan_network.cpp (every other
# Lelan method is a trap stub, as in iface_check.sh), run it on this machine's NetworkManager, and
# compare what Lelan publishes with nmcli / ip. Read-only. Prints PASS/FAIL per check.
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/net_test" "$L/tests/network_live_test.cpp" "$L/src/Lelan_network.cpp"

# NM's own signal rate while the test watches (the thing N1 must not turn into UI churn)
timeout 46 dbus-monitor --system "type='signal',sender='org.freedesktop.NetworkManager',interface='org.freedesktop.DBus.Properties'" \
  > "$W/mon.txt" 2>/dev/null &
SETTLE_MS=5000 WATCH_MS=40000 "$W/net_test" > "$W/out.txt"
wait || true
grep -v "^APCACHE" "$W/out.txt" | cut -c1-400

nmcli -t -f IN-USE,SSID,SIGNAL,SECURITY dev wifi list --rescan no > "$W/nm_aps.txt"
python3 - "$W" <<'EOF'
import json, subprocess, sys, re
W = sys.argv[1]
out = open(f"{W}/out.txt").read()
d = json.loads(re.search(r"^DUMP (.*)$", out, re.M).group(1))
fails = 0
def check(name, ok, detail=""):
    global fails
    print(("PASS " if ok else "FAIL ") + name + (f"  ({detail})" if detail else ""))
    fails += (not ok)
def sh(c): return subprocess.run(c, shell=True, capture_output=True, text=True).stdout.strip()

radio = sh("nmcli radio wifi") == "enabled"
check("wifiEnabled == nmcli radio wifi", d["wifiEnabled"] == radio, f"lelan {d['wifiEnabled']}, nm {radio}")
state = int(sh("busctl get-property org.freedesktop.NetworkManager /org/freedesktop/NetworkManager org.freedesktop.NetworkManager State").split()[1])
check("network.state == NM State", d["network"].get("state") == state, f"lelan {d['network'].get('state')}, nm {state}")
check("networkOnline == (State 70)", d["networkOnline"] == (state == 70))

aps = {}
inuse = ""
for line in open(f"{W}/nm_aps.txt"):
    parts = re.split(r"(?<!\\):", line.rstrip("\n"))
    if len(parts) < 4 or not parts[1]: continue
    use, ssid, sig, sec = parts[0], parts[1].replace("\\:", ":"), int(parts[2]), parts[3]
    if use == "*": inuse = ssid
    if ssid not in aps or aps[ssid][0] < sig: aps[ssid] = (sig, sec not in ("", "--"))
lel = {e["ssid"]: e for e in d["wifiNetworks"]}
check("same SSID set as nmcli", set(lel) == set(aps), f"lelan {sorted(lel)}, nm {sorted(aps)}")
for ssid, (sig, secured) in aps.items():
    if ssid in lel:
        check(f"'{ssid}' secured", lel[ssid]["secured"] == secured)
        check(f"'{ssid}' signal within 15 of nmcli", abs(lel[ssid]["signal"] - sig) <= 15, f"lelan {lel[ssid]['signal']}, nm {sig}")
conn = [s for s, e in lel.items() if e["connected"]]
check("connected flag on the in-use SSID only", conn == ([inuse] if inuse else []), f"lelan {conn}, nm in-use '{inuse}'")
check("activeNetwork.ssid == in-use SSID", d["activeNetwork"].get("ssid", "") == inuse)
check("network.ssid == in-use SSID (N7, WeatherLive)", d["network"].get("ssid", "") == inuse)
dev = sh("nmcli -t -f DEVICE,TYPE dev | awk -F: '$2==\"wifi\"{print $1; exit}'")
ip = sh(f"ip -4 -o addr show {dev} | awk '{{print $4}}' | cut -d/ -f1 | head -1") if dev else ""
check("activeNetwork.ip == ip addr", d["activeNetwork"].get("ip", "") == ip, f"lelan {d['activeNetwork'].get('ip')}, ip {ip}")
saved = set(sh("nmcli -t -f NAME,TYPE con show | awk -F: '$2==\"802-11-wireless\"{print $1}'").split("\n")) - {""}
check("saved Wi-Fi profiles known (N5)", set(d["wifiProfiles"]) >= saved, f"lelan {d['wifiProfiles']}, nm {sorted(saved)}")
vpns = set(sh("nmcli -t -f NAME,TYPE con show | awk -F: '$2==\"vpn\"||$2==\"wireguard\"{print $1}'").split("\n")) - {""}
check("vpnConnections == saved vpn/wireguard", {v["name"] for v in d["vpnConnections"]} == vpns, f"lelan {d['vpnConnections']}, nm {sorted(vpns)}")

mon = open(f"{W}/mon.txt").read()
nm_ap = len(re.findall(r"path=/org/freedesktop/NetworkManager/AccessPoint/", mon))
m = re.search(r"WATCH (\d+) ms: wifiChanged=(\d+) networkChanged=(\d+) vpnStateChanged=(\d+)", out)
print(f"INFO NM AccessPoint PropertiesChanged in window: {nm_ap}; Lelan wifiChanged {m.group(2)}, networkChanged {m.group(3)}, vpnStateChanged {m.group(4)}")
check("wifiChanged fewer than NM AP signals (bar-step only)", int(m.group(2)) <= max(nm_ap, 1))
check("networkChanged quiet at steady state (N2)", int(m.group(3)) == 0)
# N1: every Strength NM broadcast in the window reached the cache (last value per AP wins)
last = {}
tfinal = float(re.search(r"^FINALTIME (\S+)$", out, re.M).group(1))
for blk in re.split(r"\nsignal ", mon):
    tm = re.search(r"time=(\d+\.\d+)", blk)
    if not tm or float(tm.group(1)) > tfinal: continue      # broadcast after Lelan's final dump
    pm = re.search(r"path=(/org/freedesktop/NetworkManager/AccessPoint/\d+)", blk)
    sm = re.search(r'string "Strength"\s+variant\s+byte (\d+)', blk)
    if pm and sm: last[pm.group(1)] = int(sm.group(1))
cache = dict((a, int(b)) for a, b in re.findall(r"^APCACHE (\S+) (\d+)$", out, re.M))
check("cache holds NM's last broadcast Strength for every AP that changed", bool(last) and all(cache.get(p) == v for p, v in last.items()),
      f"{len(last)} AP(s) changed; mismatches {[(p, v, cache.get(p)) for p, v in last.items() if cache.get(p) != v]}")
# N9: link speed follows NM's Bitrate
rates = []
for blk in re.split(r"\nsignal ", mon):
    tm = re.search(r"time=(\d+\.\d+)", blk); bm = re.search(r'string "Bitrate"\s+variant\s+uint32 (\d+)', blk)
    if tm and bm and float(tm.group(1)) <= tfinal: rates.append(bm.group(1))
fs = int(re.search(r"^FINALSPEED (\d+)$", out, re.M).group(1))
if rates:
    check("activeNetwork.speed == NM's last Bitrate/1000 (N9)", fs == int(rates[-1]) // 1000, f"lelan {fs}, nm {int(rates[-1])//1000} ({len(rates)} changes)")
else:
    print("INFO no Bitrate change in window; N9 not exercised")
# N11: wired record matches nmcli
eth = sh("nmcli -t -f DEVICE,TYPE,STATE dev | awk -F: '$2==\"ethernet\"{print $1\":\"$3; exit}'")
wn = d["wiredNetwork"]
if not eth:
    check("wiredNetwork.present false on a machine without Ethernet (N11)", wn.get("present") is False and wn.get("connected") is False, str(wn))
else:
    dev_, st = eth.split(":", 1)
    check("wiredNetwork matches nmcli (N11)", wn.get("present") and wn.get("iface") == dev_ and wn.get("connected") == (st == "connected"), f"{wn} vs {eth}")
print("RESULT", "PASS" if fails == 0 else f"FAIL ({fails})")
sys.exit(1 if fails else 0)
EOF
