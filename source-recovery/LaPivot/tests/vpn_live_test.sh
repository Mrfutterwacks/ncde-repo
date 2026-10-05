#!/bin/bash
# vpn_live_test.sh — V1/V2/V3 on this machine's NetworkManager: adds a throwaway WireGuard profile
# (random key, no addresses, no routes, never autoconnects: carries no traffic), lets Lelan list,
# connect and disconnect it, records NM's own Connection.Active "Vpn" flag for it (what the oracle
# tested), then deletes the profile.
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; N=ncde-wgtest
cleanup() { nmcli con delete "$N" >/dev/null 2>&1 || true; rm -rf "$W"; }
trap cleanup EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/net_test" "$L/tests/network_live_test.cpp" "$L/src/Lelan_network.cpp"

nmcli con add type wireguard con-name "$N" ifname wgtest0 autoconnect no \
  ipv4.method disabled ipv6.method disabled wireguard.private-key "$(head -c32 /dev/urandom | base64)" >/dev/null
( sleep 7.5; A=$(nmcli -g GENERAL.DBUS-PATH con show --active "$N" 2>/dev/null || true)
  if [ -n "$A" ]; then echo "NM_ACTIVE_VPN_FLAG $(busctl get-property org.freedesktop.NetworkManager "$A" org.freedesktop.NetworkManager.Connection.Active Vpn)"
  else echo "NM_ACTIVE_VPN_FLAG not-active"; fi ) &
VPN_TEST="$N" SETTLE_MS=5000 "$W/net_test"
wait
