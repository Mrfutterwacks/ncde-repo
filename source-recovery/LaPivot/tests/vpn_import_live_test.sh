#!/bin/bash
# vpn_import_live_test.sh — N12 OpenVPN: importVpn(<name>.ovpn) through nmcli's plugin importer, then
# autoconnect off. Throwaway file: TEST-NET remote 192.0.2.1 (unroutable), throwaway CA. Checks nmcli
# has it, autoconnect is off, it never activated, Lelan lists it; then deletes it.
# (WireGuard files: wg_import_live_test.sh.)
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; N=ncdeovimp
cleanup() { nmcli con delete "$N" >/dev/null 2>&1 || true; rm -rf "$W"; }
trap cleanup EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/net_test" "$L/tests/network_live_test.cpp" "$L/src/Lelan_network.cpp"
openssl req -x509 -newkey ed25519 -nodes -keyout "$W/ca.key" -out "$W/ca.crt" -days 1 -subj /CN=ncdetest 2>/dev/null
printf 'client\ndev tun\nproto udp\nremote 192.0.2.1 1194\nauth-user-pass\nca %s\n' "$W/ca.crt" > "$W/$N.ovpn"
T0=$(date +%s)
IMPORT_TEST="file://$W/$N.ovpn" SETTLE_MS=4000 "$W/net_test" | tee "$W/out.txt"
nmcli -t -f NAME,TYPE con show | grep "^$N:" && echo "PASS nmcli has the imported profile" || echo "FAIL not in nmcli"
grep -q "IMPORT_FINISHED ok=1" "$W/out.txt" && echo "PASS vpnImportFinished ok" || echo "FAIL vpnImportFinished"
grep -q "\"name\":\"$N\"" "$W/out.txt" && echo "PASS Lelan lists it (Settings NewConnection -> refresh, V2)" || echo "FAIL not listed"
grep -q "\"connected\":false,\"name\":\"$N\"" "$W/out.txt" && echo "PASS listed as not connected" || echo "FAIL imported VPN is connected"
[ "$(nmcli -g connection.autoconnect con show "$N")" = "no" ] && echo "PASS autoconnect off" || echo "FAIL autoconnect still on"
nmcli -t -f NAME con show --active | grep -qx "$N" && echo "FAIL active after import" || echo "PASS not active after import"
A=$(journalctl --since "@$T0" --no-pager -o cat -u NetworkManager | grep -cE "auto-activating connection '$N'|\($N\): Activation: starting|'$N'.*Activation" || true)
[ "$A" = 0 ] && echo "PASS never activated (journal)" || echo "FAIL activated $A time(s)"
# a bad file must come back as a readable failure, not silence
echo "garbage" > "$W/bad.ovpn"
IMPORT_TEST="$W/bad.ovpn" SETTLE_MS=3000 "$W/net_test" | grep IMPORT_FINISHED | sed 's/^/bad file: /'
