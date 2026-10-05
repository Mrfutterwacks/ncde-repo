#!/usr/bin/env bash
# ncde-hw-report — what does NCDE see on THIS machine? (2026-09-25)
# Read-only: changes nothing, needs no sudo. Run it on any NCDE laptop, logged in
# to the NCDE desktop, from the USB:
#     bash /path/to/NCDE-Installer/ncde-hw-report.sh
# It prints a report and saves it next to itself in hw-reports/<host>-<time>.txt,
# so the stick can carry it back. Nothing leaves the machine except two small
# weather/location test requests (open-meteo, ipwho.is).

HERE="$(cd "$(dirname "$0")" && pwd)"
OUT_DIR="$HERE/hw-reports"
mkdir -p "$OUT_DIR" 2>/dev/null || OUT_DIR="$HOME"
OUT="$OUT_DIR/$(hostname 2>/dev/null || echo host)-$(date +%Y%m%d-%H%M%S).txt"

sec() { printf '\n== %s ==\n' "$1"; }
kv()  { printf '%-26s %s\n' "$1" "$2"; }
cat1() { [ -r "$1" ] && tr -d '\n' < "$1" 2>/dev/null || printf '-'; }

{
echo "NCDE hardware report — $(date)"
kv "host" "$(hostname 2>/dev/null)"
kv "user / groups" "$(id -un) / $(id -Gn)"
kv "kernel" "$(uname -r)"

sec "Machine"
kv "vendor" "$(cat1 /sys/class/dmi/id/sys_vendor)"
kv "product" "$(cat1 /sys/class/dmi/id/product_name) $(cat1 /sys/class/dmi/id/product_version)"
kv "chassis type" "$(cat1 /sys/class/dmi/id/chassis_type)  (8-10,14,31,32 = laptop/convertible)"
kv "cpu" "$(grep -m1 'model name' /proc/cpuinfo | cut -d: -f2- | sed 's/^ //')"
kv "cores" "$(nproc)"
kv "ram" "$(awk '/MemTotal/{printf "%.1f GB", $2/1048576}' /proc/meminfo)"
for c in /sys/class/drm/card*/device; do
  [ -e "$c/driver" ] && kv "gpu $(basename "$(dirname "$c")")" "$(basename "$(readlink "$c/driver")") [$(cat1 "$c/vendor"):$(cat1 "$c/device")]"
done
kv "va-api drivers" "$(ls /usr/lib/dri/*_drv_video.so 2>/dev/null | xargs -n1 basename 2>/dev/null | tr '\n' ' ')"

sec "Power + backlight"
for p in /sys/class/power_supply/*; do
  [ -e "$p" ] || continue
  kv "$(basename "$p")" "type=$(cat1 "$p/type") status=$(cat1 "$p/status") capacity=$(cat1 "$p/capacity") online=$(cat1 "$p/online")"
done
[ -e /sys/class/power_supply ] && ls /sys/class/power_supply | grep -q . || echo "(no power_supply devices)"
found=0
for b in /sys/class/backlight/*; do
  [ -e "$b" ] || continue; found=1
  w="no"; [ -w "$b/brightness" ] && w="yes"
  kv "$(basename "$b")" "type=$(cat1 "$b/type") $(cat1 "$b/brightness")/$(cat1 "$b/max_brightness") writable-by-me=$w perms=$(stat -c '%A %G' "$b/brightness" 2>/dev/null)"
done
[ $found -eq 1 ] || echo "(no backlight — desktop, or no driver)"
kv "in video group" "$(id -Gn | tr ' ' '\n' | grep -qx video && echo yes || echo NO)"
kv "backlight udev rule" "$(ls /etc/udev/rules.d/90-ncde-backlight.rules 2>/dev/null || echo MISSING)"

sec "Sensors"
for h in /sys/class/hwmon/hwmon*; do kv "$(basename "$h")" "$(cat1 "$h/name")  $(ls "$h" 2>/dev/null | grep -c '_input$') inputs"; done
for z in /sys/class/thermal/thermal_zone*; do kv "$(basename "$z")" "$(cat1 "$z/type") $(( $(cat1 "$z/temp" | tr -dc 0-9 || echo 0) / 1000 ))°C"; done 2>/dev/null
kv "iio devices" "$(ls /sys/bus/iio/devices 2>/dev/null | tr '\n' ' ')"
kv "iio-sensor-proxy" "$(systemctl is-active iio-sensor-proxy 2>/dev/null)"
kv "touchscreens" "$(grep -il touch /sys/class/input/event*/device/name 2>/dev/null | xargs -r cat | tr '\n' ';')"
kv "fan pwm" "$(ls /sys/class/hwmon/hwmon*/pwm[0-9] 2>/dev/null | wc -l) channel(s)"

sec "Network"
for n in /sys/class/net/*; do kv "$(basename "$n")" "$(cat1 "$n/operstate") $( [ -d "$n/wireless" ] && echo wifi)"; done
kv "ssid" "$(nmcli -t -f active,ssid dev wifi 2>/dev/null | awk -F: '$1=="yes"{print $2}')"

sec "Sentinel"
kv "service" "$(systemctl is-active ncde-sentinel 2>/dev/null) / $(systemctl is-enabled ncde-sentinel 2>/dev/null)"
missing=""
for m in __init__ __main__ _utils drivers gamemode hw_tier hwmon kernel_caps process_tier pwm_guard reference_devices scx_select udev_monitor zen_hints; do
  [ -f "/usr/local/bin/sentinel/$m.py" ] || missing="$missing $m"
done
kv "missing modules" "${missing:- none}"
kv "hw tier" "$(cd /usr/local/bin && timeout 10 python3 -c 'from sentinel import hw_tier as h; print(h.detect())' 2>&1 | tail -1)"
echo "-- last Sentinel log lines --"
journalctl -u ncde-sentinel -b --no-pager -n 25 2>/dev/null | tail -25 || echo "(journal not readable)"

sec "Location + weather"
kv "/etc/geolocation" "$( [ -f /etc/geolocation ] && grep -v '^#' /etc/geolocation | head -2 | tr '\n' ' ' || echo MISSING)"
kv "geoclue" "$(systemctl is-active geoclue 2>/dev/null)"
kv "geoclue ncde drop-in" "$(ls /etc/geoclue/conf.d/90-ncde-static.conf 2>/dev/null || echo none)"
wai=$(ls /usr/lib/geoclue-2.0/demos/where-am-i 2>/dev/null)
kv "geoclue fix" "$( [ -n "$wai" ] && timeout 15 "$wai" -t 10 2>&1 | grep -E 'Latitude|Longitude|Description' | tr -s ' ' | tr '\n' ' ' || echo 'where-am-i not installed')"
kv "session sets XHR file read" "$(grep -c QML_XHR_ALLOW_FILE_READ /usr/local/bin/ncde-x11-session 2>/dev/null) (session script), xinitrc.d: $(ls /etc/X11/xinit/xinitrc.d/90-ncde-qml-xhr.sh 2>/dev/null || echo MISSING)"
kv "location memory" "$(cat "$HOME/.config/ncde/location-memory.json" 2>/dev/null | tr -d '\n ' | cut -c1-200)"
kv "open-meteo reachable" "$(curl -s -o /dev/null -w '%{http_code}' --max-time 10 'https://api.open-meteo.com/v1/forecast?latitude=40&longitude=-89&current=temperature_2m')"
kv "IP says" "$(curl -s --max-time 10 'https://ipwho.is/?fields=city,region,latitude,longitude' | tr -d '\n ')"

sec "NCDE"
kv "LaPivot running" "$(pgrep -x LaPivot >/dev/null && echo yes || echo NO)"
kv "master copy sha" "$(sha256sum /usr/local/share/ncde-fix/ncde-full-patch-20260711.sh 2>/dev/null | cut -c1-8)"
kv "stats helper" "$(systemctl --user is-active ncde-stats 2>/dev/null)  json: $(tr -d '\n ' < "${XDG_RUNTIME_DIR:-/run/user/$(id -u)}/ncde-stats.json" 2>/dev/null | grep -o '"brightness":{[^}]*}' || echo 'no brightness')"
echo "-- shell log errors (last 20) --"
grep -a -iE 'error|TypeError|ReferenceError|failed' "$HOME/ncde-debug.log" 2>/dev/null | tail -20
} 2>&1 | tee "$OUT"

echo
echo "Saved: $OUT"
