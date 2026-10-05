#!/bin/bash
# bluetooth_live_test.sh — Lelan_bluetooth.cpp on this machine's BlueZ. Never pairs or connects a real
# device. Parts: state vs bluetoothctl; 30 s scan stops by itself with no full-tree reloads; the agent
# (BlueZ accepts it as default; confirm/reject/passkey answered as the tab would); rfkill soft block
# -> setBluetoothEnabled(true) unblocks and powers (restores the original state afterwards).
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/bt" "$L/tests/bluetooth_live_test.cpp" "$L/src/Lelan_bluetooth.cpp" || exit 1
pass() { echo "PASS $*"; }; fail() { echo "FAIL $*"; FAILS=$((FAILS+1)); }; FAILS=0

echo "== state"
S=$(BT_MODE=state "$W/bt" | sed -n 's/^STATE //p')
python3 - "$S" <<'PY' || FAILS=$((FAILS+1))
import json, subprocess, sys
s = json.loads(sys.argv[1]); show = subprocess.run(["bluetoothctl", "show"], capture_output=True, text=True).stdout
val = lambda k: next((l.split(":", 1)[1].strip() for l in show.splitlines() if l.strip().startswith(k + ":")), "")
ok = True
for name, got, want in [("powered", s["enabled"], val("Powered") == "yes"), ("discoverable", s["discoverable"], val("Discoverable") == "yes"),
                        ("address", s["bluetooth"].get("address"), show.split()[1] if show.startswith("Controller") else None),
                        ("agent default", s["agentDefault"], True)]:
    print(("PASS " if got == want else "FAIL ") + f"{name}: lelan {got}, bluez {want}"); ok &= got == want
paired = set(l.split()[1] for l in subprocess.run(["bluetoothctl", "devices", "Paired"], capture_output=True, text=True).stdout.splitlines() if l.startswith("Device"))
mine = set(d["address"] for d in s["devices"] if d["paired"])
print(("PASS " if mine == paired else "FAIL ") + f"paired devices: lelan {sorted(mine)}, bluez {sorted(paired)}"); ok &= mine == paired
sys.exit(0 if ok else 1)
PY

echo "== scan (40 s; BlueZ method calls watched for GetManagedObjects)"
timeout 46 dbus-monitor --system "type='method_call',interface='org.freedesktop.DBus.ObjectManager',member='GetManagedObjects',destination='org.bluez'" \
  "type='signal',sender='org.bluez'" > "$W/mon.txt" 2>/dev/null &
BT_MODE=scan "$W/bt" | tee "$W/scan.txt" | grep -E "SCAN|FAILED"
wait
GMO=$(grep -c "member=GetManagedObjects" "$W/mon.txt"); SIG=$(grep -c "^signal.*sender=:" "$W/mon.txt")
echo "INFO BlueZ signals in window: $SIG; GetManagedObjects calls: $GMO (1 = the start-up read)"
[ "$GMO" -le 1 ] && pass "no full-tree reloads during the scan (B1)" || fail "GetManagedObjects called $GMO times"
grep -q "SCAN t=10s scanning=1" "$W/scan.txt" && pass "scanning while the scan runs" || fail "not scanning at 10 s"
grep -q "SCAN t=40s scanning=0" "$W/scan.txt" && pass "discovery stopped by itself (B3)" || fail "still discovering at 40 s"
[ "$(busctl get-property org.bluez /org/bluez/hci0 org.bluez.Adapter1 Discovering)" = "b false" ] && pass "BlueZ Discovering false after the test" || fail "BlueZ still discovering"

echo "== agent (the script plays BlueZ)"
AGENT_ANSWERS="accept,reject,passkey:123456" RUN_MS=15000 BT_MODE=agent "$W/bt" > "$W/agent.txt" &
sleep 4
BUS=$(sed -n 's/^AGENT bus=\([^ ]*\) default=.*/\1/p' "$W/agent.txt"); DEF=$(sed -n 's/^AGENT bus=[^ ]* default=//p' "$W/agent.txt")
[ "$DEF" = 1 ] && pass "BlueZ accepted RegisterAgent + RequestDefaultAgent" || fail "agent not default ($DEF)"
python3 - "$BUS" <<'PY' | tee "$W/agentpy.txt"
import dbus, sys
agent = dbus.Interface(dbus.SessionBus().get_object(sys.argv[1], "/org/ncde/lelan/bluetooth_agent"), "org.bluez.Agent1")
dev = dbus.ObjectPath("/org/bluez/hci0/dev_00_11_22_33_44_55")
def call(what, f):
    try: r = f(); print(f"PASS {what} -> accepted ({r})" if what != "reject" else f"FAIL reject -> accepted ({r})")
    except dbus.DBusException as e:
        ok = what == "reject" and e.get_dbus_name() == "org.bluez.Error.Rejected"
        print(("PASS " if ok else "FAIL ") + f"{what} -> {e.get_dbus_name()}")
call("confirm 042817", lambda: agent.RequestConfirmation(dev, dbus.UInt32(42817), timeout=10))
call("reject", lambda: agent.RequestAuthorization(dev, timeout=10))
r = agent.RequestPasskey(dev, timeout=10)
print(("PASS" if int(r) == 123456 else "FAIL") + f" passkey typed 123456 -> BlueZ receives {int(r)}")
try:
    agent.AuthorizeService(dev, "0000110b-0000-1000-8000-00805f9b34fb", timeout=5); print("FAIL unpaired device service authorised")
except dbus.DBusException as e: print(("PASS" if e.get_dbus_name() == "org.bluez.Error.Rejected" else "FAIL") + " unpaired device service refused (" + e.get_dbus_name() + ")")
PY
wait
FAILS=$((FAILS + $(grep -c '^FAIL' "$W/agentpy.txt")))
[ "$(grep -c '^PASS' "$W/agentpy.txt")" = 4 ] || fail "agent: expected 4 PASS lines from the BlueZ stand-in"
grep '^PROMPT' "$W/agent.txt" | head -6
grep -q '"code":"042817","kind":"confirm"' "$W/agent.txt" && pass "tab prompt shows the 6-digit code to confirm" || fail "confirm prompt missing"

echo "== rfkill soft block -> setBluetoothEnabled(true)"
ORIG=$(cat /sys/class/rfkill/rfkill*/soft 2>/dev/null | head -1)
rfkill block bluetooth; sleep 2
echo "INFO BlueZ when blocked: $(busctl set-property org.bluez /org/bluez/hci0 org.bluez.Adapter1 Powered b true 2>&1 | head -1)  (what the oracle's call got)"
BT_MODE=enable "$W/bt" | grep -E "BEFORE|AFTER|FAILED" | cut -c1-160
SOFT=$(rfkill -n -o TYPE,SOFT | awk '$1=="bluetooth"{print $2}')
POW=$(busctl get-property org.bluez /org/bluez/hci0 org.bluez.Adapter1 Powered 2>&1)
[ "$SOFT" = unblocked ] && pass "rfkill unblocked by Lelan (B10)" || fail "still $SOFT"
[ "$POW" = "b true" ] && pass "adapter powered after unblock" || fail "Powered: $POW"
rfkill unblock bluetooth
echo "RESULT $([ $FAILS = 0 ] && echo PASS || echo "FAIL ($FAILS)")"
