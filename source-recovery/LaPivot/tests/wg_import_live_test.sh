#!/bin/bash
# wg_import_live_test.sh — N12 WireGuard: importVpn(<name>.conf) parses the file and adds the profile
# with autoconnect off + BLOCK_AUTOCONNECT. Phase 1 uses a harmless file (one /32 route, no DNS) and
# aborts if NetworkManager activates it at all; phase 2 (full tunnel + DNS + IPv6 + PSK) then checks
# every field NM stored against the file, secrets included. Profiles are deleted on exit.
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"
cleanup() { for n in ncdewg1 ncdewg2; do nmcli con delete "$n" >/dev/null 2>&1; done; rm -rf "$W"; }
trap cleanup EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/net_test" "$L/tests/network_live_test.cpp" "$L/src/Lelan_network.cpp" || exit 1
key() { head -c32 /dev/urandom | base64; }
activations() { journalctl --since "@$1" --no-pager -o cat -u NetworkManager | grep -cE "auto-activating connection '$2'|\($2\): Activation: starting"; }

T0=$(date +%s)
printf '[Interface]\nPrivateKey = %s\n[Peer]\nPublicKey = %s\nAllowedIPs = 10.99.99.99/32\nEndpoint = 192.0.2.1:51820\n' "$(key)" "$(key)" > "$W/ncdewg1.conf"
IMPORT_TEST="$W/ncdewg1.conf" SETTLE_MS=3000 "$W/net_test" | grep IMPORT_FINISHED
sleep 10
A=$(activations "$T0" ncdewg1)
echo "phase 1: activations of ncdewg1 in 13 s: $A"
[ "$A" = 0 ] || { echo "FAIL phase 1 activated: stopping before the full-tunnel file"; exit 1; }
echo "PASS phase 1 never activated"

T1=$(date +%s)
PK=$(key); PUB=$(key); PSK=$(key)
printf '[Interface]\nPrivateKey = %s\nListenPort = 51821\nAddress = 10.9.0.2/32, fd00:9::2/128\nDNS = 1.1.1.1, 2606:4700::1111, corp.example\nMTU = 1380\n\n[Peer]\n# comment\nPublicKey = %s\nPresharedKey = %s\nAllowedIPs = 0.0.0.0/0, ::/0\nEndpoint = 192.0.2.1:51820\nPersistentKeepalive = 25\n' "$PK" "$PUB" "$PSK" > "$W/ncdewg2.conf"
IMPORT_TEST="$W/ncdewg2.conf" SETTLE_MS=3000 "$W/net_test" | grep -E "IMPORT_FINISHED|IMPORT_LIST"
sleep 5
A=$(activations "$T1" ncdewg2); echo "phase 2: activations of ncdewg2: $A"
[ "$A" = 0 ] && echo "PASS full-tunnel profile never activated" || echo "FAIL full-tunnel profile activated"
ip route | grep -q "dev ncdewg2" && echo "FAIL routes via ncdewg2" || echo "PASS no route via ncdewg2"
python3 - "$W/ncdewg2.conf" "$PK" "$PUB" "$PSK" <<'PY'
import dbus, sys
conf, pk, pub, psk = sys.argv[1:]
bus = dbus.SystemBus()
st = dbus.Interface(bus.get_object('org.freedesktop.NetworkManager', '/org/freedesktop/NetworkManager/Settings'), 'org.freedesktop.NetworkManager.Settings')
path = [p for p in st.ListConnections() if dbus.Interface(bus.get_object('org.freedesktop.NetworkManager', p), 'org.freedesktop.NetworkManager.Settings.Connection').GetSettings()['connection']['id'] == 'ncdewg2'][0]
c = dbus.Interface(bus.get_object('org.freedesktop.NetworkManager', path), 'org.freedesktop.NetworkManager.Settings.Connection')
s = c.GetSettings(); sec = c.GetSecrets('wireguard')
wg, v4, v6, peer = s['wireguard'], s['ipv4'], s['ipv6'], s['wireguard']['peers'][0]
checks = [
  ("autoconnect off", s['connection']['autoconnect'] == False),
  ("interface-name", s['connection']['interface-name'] == 'ncdewg2'),
  ("private key", sec['wireguard']['private-key'] == pk),
  ("listen-port 51821", wg['listen-port'] == 51821),
  ("mtu 1380", wg['mtu'] == 1380),
  ("one peer, public key", len(wg['peers']) == 1 and peer['public-key'] == pub),
  ("peer preshared key", sec['wireguard']['peers'][0]['preshared-key'] == psk),
  ("peer allowed-ips", list(peer['allowed-ips']) == ['0.0.0.0/0', '::/0']),
  ("peer endpoint", peer['endpoint'] == '192.0.2.1:51820'),
  ("peer keepalive 25", peer['persistent-keepalive'] == 25),
  ("ipv4 manual 10.9.0.2/32", v4['method'] == 'manual' and [(a['address'], a['prefix']) for a in v4['address-data']] == [('10.9.0.2', 32)]),
  ("ipv6 manual fd00:9::2/128", v6['method'] == 'manual' and [(a['address'], a['prefix']) for a in v6['address-data']] == [('fd00:9::2', 128)]),
  ("ipv4 dns 1.1.1.1", list(v4.get('dns-data', [])) == ['1.1.1.1']),
  ("ipv6 dns 2606:4700::1111", list(v6.get('dns-data', [])) == ['2606:4700::1111']),
  ("dns-search corp.example", list(v4.get('dns-search', [])) == ['corp.example']),
]
for n, ok in checks: print(("PASS " if ok else "FAIL ") + "stored " + n)
PY
# removeVpn: Settings > Network "Remove"
REMOVE_TEST=ncdewg1 SETTLE_MS=3000 "$W/net_test"
nmcli -t -f NAME con show | grep -qx ncdewg1 && echo "FAIL ncdewg1 still saved" || echo "PASS removeVpn deleted ncdewg1"
# refusals must be readable
printf '[Interface]\nPrivateKey = %s\nPostUp = iptables -A x\n' "$(key)" > "$W/ncdewg3.conf"
IMPORT_TEST="$W/ncdewg3.conf" SETTLE_MS=2000 "$W/net_test" | grep IMPORT_FINISHED | sed 's/^/PostUp file: /'
printf '[Interface]\nPrivateKey = %s\n' "$(key)" > "$W/this-name-is-too-long.conf"
IMPORT_TEST="$W/this-name-is-too-long.conf" SETTLE_MS=2000 "$W/net_test" | grep IMPORT_FINISHED | sed 's/^/long name: /'
