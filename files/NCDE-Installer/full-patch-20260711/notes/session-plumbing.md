# Session Plumbing Fixes — 2026-07-11

Scope: chromium dark-mode flip, idle lock/screensaver chain, QML disk cache,
duplicate notification daemons, appmenu-gtk-module double-load, picom.conf.
All file changes are staged under `src/` (mirroring absolute paths); nothing
live was modified. Everything privileged is in **PATCH-SCRIPT COMMANDS** at the
bottom. Every claim below was verified on the live system today; the exact
command outputs are quoted.

---

## Fix 1 — Chromium launch un-darks the whole desktop

**Staged file:** `src/usr/local/bin/ncde-chromium-sync.sh`
(→ `/usr/local/bin/ncde-chromium-sync.sh`)

**Defect.** `/usr/local/bin/chromium` (wrapper, line 13) calls the sync script
with **no argument** on every launch. The no-arg fallback greps
`"darkMode": true` in `~/.config/ncde/active-theme.json`, but the engine
writes `"mode": "dark"` — there is no `darkMode` key. The grep never matches,
mode falls to `light`, and the script then flips the chrome theme to
`theme-day`, strips `--force-dark-mode`, and sets gsettings
`color-scheme=prefer-light` — un-darking GTK4/portal apps and web pages
desktop-wide until the engine next reapplies. Verified live: the JSON contains
`"mode": "dark"` and no `darkMode` key.

**Diff (staged vs live):**
```diff
 mode="${1:-}"
 if [[ -z "$mode" ]]; then
-  if grep -q '"darkMode"[[:space:]]*:[[:space:]]*true' "$ACTIVE" 2>/dev/null; then
+  # 2026-07-11 fix: the engine writes `"mode": "dark"` in active-theme.json —
+  # no "darkMode" key exists there. The old grep for `"darkMode": true` never
+  # matched, so every no-arg call (= every Chromium launch via the wrapper)
+  # fell through to mode=light and un-darked the whole desktop (theme-day +
+  # gsettings prefer-light) until the engine next reapplied.
+  if grep -q '"mode"[[:space:]]*:[[:space:]]*"dark"' "$ACTIVE" 2>/dev/null; then
     mode="dark"; else mode="light"; fi
 fi
```
Note: the pattern cannot false-match the JSON's `"darkModeLock"` key (the
pattern requires the literal quoted key `"mode"`) and requires the value to be
exactly `"dark"` (closing quote is part of the pattern).

**Verification (actually run):**
```
$ bash -n src/usr/local/bin/ncde-chromium-sync.sh ; echo rc=$?
rc=0
$ grep -c '"darkMode"[[:space:]]*:[[:space:]]*true' ~/.config/ncde/active-theme.json
0        # old pattern: zero matches on the real engine-written file
$ grep -c '"mode"[[:space:]]*:[[:space:]]*"dark"' ~/.config/ncde/active-theme.json
1        # new pattern: matches
```
End-to-end dry-run in a sandboxed `$HOME` (copy of the real JSON, fake
`gsettings` on PATH so no live dconf was touched):
```
--- run 1: engine JSON as-is (mode=dark) ---
ncde-chromium: mode=dark  theme=/usr/share/ncde/chromium/theme-night
exit=0    chromium-theme=theme-night    --force-dark-mode present (1)
--- run 2: JSON edited to "mode": "light" ---
ncde-chromium: mode=light  theme=/usr/share/ncde/chromium/theme-day
exit=0    chromium-theme=theme-day      --force-dark-mode absent (0)
gsettings calls seen: prefer-dark (run 1), prefer-light (run 2)
```
No privileged commands needed for this fix.

---

## Fix 2 — Idle lock/screensaver chain wired up

**Staged file:** `src/usr/local/bin/ncde-x11-session`
(→ `/usr/local/bin/ncde-x11-session`), plus chmod/chown in PATCH-SCRIPT
COMMANDS.

**Defect (three stacked breaks, each verified live today):**
1. Nothing launches xss-lock — `pgrep -a xss-lock` → rc=1 (not running);
   `/usr/bin/xss-lock` itself is installed and executable.
2. The two helpers can't execute:
   ```
   -rw-r--r-- 1 1000 1000 185 Jun 15 15:36 /usr/bin/ncde-lock-xss
   -rw-r--r-- 1 1000 1000 212 Jun 15 15:36 /usr/bin/ncde-screensaver-notify
   ```
   mode 644, owned by uid/gid 1000 (build-machine artifact; stephen is 1001).
3. X idle trigger zeroed: `xset q` → `timeout: 0`, DPMS Standby/Suspend/Off
   all 0 (per `/etc/X11/xorg.conf.d/10-ncde.conf`, "let xss-lock handle
   idle") — but xss-lock only fires on X screensaver events, so with
   timeout 0 it would never trigger even if running.

User-facing symptom: `screensaver.json` says `timeout: 3` (minutes) but the
screen never blanks, never runs Saisons, never locks.

**Diff (staged vs live)** — inserted after the geoclue block, using the file's
own `pkill -x` + `ncde_respawn` idiom (same as picom/xfce-polkit/
xembedsniproxy); plus the QML-cache hunk described in Fix 3:
```diff
+# Idle screensaver + lock chain (2026-07-11). Three stacked breaks left the
+# screen on forever: (1) nothing ever launched xss-lock; (2) the helper pair
+# /usr/bin/ncde-lock-xss + /usr/bin/ncde-screensaver-notify shipped mode 644
+# owned by a build-machine uid, so exec failed (master patch chown/chmods
+# them — the -x guard below keeps this block inert until that has run);
+# (3) /etc/X11/xorg.conf.d/10-ncde.conf zeroes the X screensaver timer
+# ("let xss-lock handle idle") but xss-lock only FIRES on X screensaver
+# events, so the session must arm the timer here. Timeout follows the
+# Screensaver setting (screensaver.json "timeout", minutes; 3 = first-boot
+# default; 0 disables the idle trigger, sleep/lock events still work).
+# xss-lock(1): -n CMD runs at the first idle mark (Saisons screensaver via
+# ncde-screensaver-notify), the locker runs at the cycle mark / on sleep;
+# --transfer-sleep-lock hands the sleep-delay fd to the locker (ncde-portal
+# honors XSS_SLEEP_LOCK_FD). NO logind Handle*/power settings are read,
+# written, or depended on anywhere in this chain — deliberately.
+if command -v xss-lock >/dev/null 2>&1 && [ -x /usr/bin/ncde-lock-xss ] \
+   && [ -x /usr/bin/ncde-screensaver-notify ]; then
+    _ss_min=$(jq -r '.timeout // 3' "$HOME/.config/ncde/screensaver.json" 2>/dev/null)
+    case "$_ss_min" in ''|*[!0-9]*) _ss_min=3 ;; esac
+    xset s $(( _ss_min * 60 )) 2>/dev/null || true
+    pkill -x xss-lock 2>/dev/null || true
+    ncde_respawn xss-lock --transfer-sleep-lock -n /usr/bin/ncde-screensaver-notify -- /usr/bin/ncde-lock-xss
+fi
```

**Semantics / safety:**
- The `-x` guards keep the whole block **inert until the operator runs the
  chown/chmod** — installing the script edit before (or without) the
  privileged step can never half-enable the chain.
- Syntax was verified against the installed tools, not guessed:
  - `xss-lock --help` (run live): `xss-lock [OPTION…] LOCK_CMD [ARG...]`,
    `-n, --notifier=CMD`, `-l, --transfer-sleep-lock`. Order
    `--transfer-sleep-lock -n CMD -- LOCKER` is valid.
  - `man xset`, `s` section (quoted live): arguments are **seconds**; "If only
    one numerical parameter is given, it will be used for the length." So
    `xset s 180` arms a 180 s idle mark and leaves the existing cycle (600 s,
    from `xset q`) alone → Saisons at 3 min (notifier), lock at the following
    cycle mark and on sleep/loginctl lock events.
- Timeout parse tested (real run):
  live json → 180 s; missing file → 180 s (default 3 min); `timeout: 0` → 0 s
  (X idle trigger off; xss-lock still locks on sleep/explicit lock).
- `/usr/bin/ncde-lock-xss` is `exec ncde-lock --lock "$@"` (no fork, per
  xss-lock(1) rule); `ncde-screensaver-notify` is
  `exec ncde-portal --screensaver "$@"` — both read live, both are pure exec
  wrappers, safe under `ncde_respawn`.
- **logind:** nothing here touches or depends on logind Handle*/power
  settings or `/etc/systemd/logind.conf.d` (documented disaster — avoided).
  `--transfer-sleep-lock` only passes the sleep-delay fd through.

**Verification:** `bash -n src/usr/local/bin/ncde-x11-session` → rc=0.
Runtime activation requires relogin (or the optional current-session commands
below); "chain fires after 3 idle minutes" is **not** claimed verified — it
cannot be until the privileged step runs.

---

## Fix 3 — Dead QML disk cache (every launch recompiles all QML)

**Staged file:** same `src/usr/local/bin/ncde-x11-session`.

**Defect.** The script exported
`QML_DISK_CACHE_PATH=/var/cache/ncde/qmlcache`; verified live:
```
drwxr-xr-x 1 root root 0 Jul  8 21:40 /var/cache/ncde/qmlcache   # root:root, EMPTY
```
LaPivot runs as the session user (1001) and cannot write there, so Qt
silently skips the disk cache and recompiles every QML file at every launch
(slow session start / first-open of shell surfaces).

**Diff (staged vs live):**
```diff
-export QML_DISK_CACHE_PATH=/var/cache/ncde/qmlcache
+# QML disk cache fix (2026-07-11): the old path /var/cache/ncde/qmlcache is
+# root:root mode 755 and was verified EMPTY since creation — the session user
+# can't write it, so Qt silently skipped the cache and recompiled every QML
+# file on every launch. A per-user cache dir is always writable, needs no
+# chown in the image, and is correct on multi-user systems too.
+export QML_DISK_CACHE_PATH="${XDG_CACHE_HOME:-$HOME/.cache}/ncde/qmlcache"
+mkdir -p "$QML_DISK_CACHE_PATH" 2>/dev/null || true
```
**Why per-user instead of chown:** a chown-to-stephen `/var/cache` dir breaks
the multi-user case and would need re-fixing in the ISO image; a per-user
path under `$XDG_CACHE_HOME` is always writable, survives image rebuilds, and
needs **no privileged command at all**. The old `/var/cache/ncde/qmlcache`
dir is left in place (empty, inert — never delete rule).

**Verification:** covered by the same `bash -n` rc=0 and the diff above. Cache
population can only be confirmed after next login (`ls ~/.cache/ncde/qmlcache`
should be non-empty after LaPivot starts) — not claimed verified yet.

---

## Fix 4 — Duplicate org.freedesktop.Notifications providers

**No stageable file content change exists for this one** (the fix is
retiring installed package files) → all of it is in PATCH-SCRIPT COMMANDS.

**Defect (verified live).** Both notification daemons are installed:
dunst (D-Bus activatable via `org.knopwob.dunst.service`) and xfce4-notifyd —
`/usr/share/dbus-1/services/org.xfce.xfce4-notifyd.Notifications.service` and
`...Notifyd.service` present, plus `/etc/xdg/autostart/xfce4-notifyd.desktop`
and a generated `app-xfce4\x2dnotifyd@autostart.service` user unit. The
journal (audit) shows `dbus-broker-launch: Ignoring duplicate name
'org.freedesktop.Notifications'` — which daemon wins bus activation is
packaging-order luck. At check time dunst was **not** running (rc=1 from
pgrep; it is activated on the first notification), so the race is real, not
theoretical.

**Dependency check (why not a plain `pacman -Rns xfce4-notifyd`):**
```
$ pactree -r xfce4-notifyd
xfce4-notifyd
└─xfce4-power-manager
```
`xfce4-power-manager` requires it — and xfce4-power-manager is itself not
running (`pgrep` rc=1), launched by nothing in the session script, and power
is Sentinel/Zen's job on this OS. Primary fix below is the safe file-aside +
NoExtract + user-mask route; full package removal of **both** is listed as
the alternative for the operator to choose.

---

## Fix 5 — appmenu-gtk-module double-load (D-Bus menu publisher)

**No stageable file content change** (retirement of package files) → all in
PATCH-SCRIPT COMMANDS.

**Defect (verified live).** `/etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh`
is present and executable (the `.retired-20260710` aside was created but the
original was never removed — the package was reinstalled, `pacman -Qo`
confirms it belongs to `appmenu-gtk-module 25.04-3`). It appends
`appmenu-gtk-module` to `GTK_MODULES` and exports stale `UBUNTU_MENUPROXY=1`,
so every GTK3 app loads **both** `libappmenu-gtk-module.so` (Canonical,
publishes menus over D-Bus — violates the no-D-Bus rule) **and**
`ncde-gtk-module.so` (the in-house, no-D-Bus publisher from
`80-ncde-globalmenu.sh`) — both .so files confirmed in
`/usr/lib/gtk-3.0/modules/`. Result: double menu export into Glia's bar.

**Durable retirement facts gathered:**
- `pactree -r appmenu-gtk-module` → leaf package, nothing depends on it →
  clean `pacman -Rns` is possible.
- Its user unit `appmenu-gtk-module.service` is disabled/inactive (checked).
- Package files that matter (from `pacman -Ql`):
  `etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh`,
  `usr/lib/gtk-3.0/modules/libappmenu-gtk-module.so`,
  `usr/lib/systemd/user/appmenu-gtk-module.service`.
- NoExtract syntax cited from `man pacman.conf` (read live): "All files
  listed with a NoExtract directive will never be extracted from a package
  into the filesystem. ... do not include the leading slash".
- The xsession glob sources `?*.sh`, so the `.retired-aside-…` rename suffix
  (no `.sh` ending) is sufficient to deactivate the script even before
  package removal.
- Takes effect at next login (GTK_MODULES is baked into already-running
  session environments).

---

## Fix 6 — picom.conf: NOT touched (deliberately)

Neither audit report names a defect **inside** `/etc/picom.conf`. The
glx-freeze issue is already handled at the session-script layer (live
`ncde-x11-session` lines 86-104 pick `--backend glx|xrender` at runtime; the
conf file is shared by both paths). Verified before starting:
`diff /etc/picom.conf src/etc/picom.conf` → identical (`PICOM-PRISTINE`).
The staged copy remains byte-identical to live.

---

## Out of scope / not done (explicit)

- Report P7 (SSH_AUTH_SOCK import-environment omission, `ncde_promote`
  ordering) — real, live-fixable, but not in this task's four items; left for
  its own pass so this diff stays reviewable.
- Report P2 (Ctrl+Alt+R recovery legs), P6 C++ items — separate tickets.
- dunst was not explicitly added to the session script: it is D-Bus
  activatable and becomes the *only* `org.freedesktop.Notifications`
  provider once the xfce4-notifyd services are retired; the report's fix is
  the retirement, not a new launcher.

---

# PATCH-SCRIPT COMMANDS

Exact commands for the master patch script (operator-run, in this order).
None of these were executed by this session.

## A. Idle lock chain — REQUIRED (enables Fix 2's guarded block)

```sh
# A1: give the two xss-lock helpers sane ownership (uid 1000 is a dead
#     build-machine uid; they must be root-owned system binaries)
chown root:root /usr/bin/ncde-lock-xss /usr/bin/ncde-screensaver-notify

# A2: make them executable (they ship 644 — exec fails; this is the switch
#     that arms the -x-guarded block staged in ncde-x11-session)
chmod 755 /usr/bin/ncde-lock-xss /usr/bin/ncde-screensaver-notify
```

## B. Idle lock chain — OPTIONAL, current session only (else just relogin)

```sh
# B1: arm the X idle timer in the ALREADY-RUNNING session (the staged script
#     does this at every future login; run as stephen, not root)
DISPLAY=:0 xset s 180

# B2: start the chain once for this session (unguarded one-off; future
#     logins get the ncde_respawn-guarded version; run as stephen)
DISPLAY=:0 xss-lock --transfer-sleep-lock -n /usr/bin/ncde-screensaver-notify -- /usr/bin/ncde-lock-xss &
```

## C. xfce4-notifyd retirement — REQUIRED (Fix 4; aside route, no deletion)

```sh
# C1-C3: move the bus-activation / autostart entry points aside so dunst is
#        the only org.freedesktop.Notifications provider (mv, never rm)
mv /usr/share/dbus-1/services/org.xfce.xfce4-notifyd.Notifications.service /usr/share/dbus-1/services/org.xfce.xfce4-notifyd.Notifications.service.retired-aside-20260711
mv /usr/share/dbus-1/services/org.xfce.xfce4-notifyd.Notifyd.service /usr/share/dbus-1/services/org.xfce.xfce4-notifyd.Notifyd.service.retired-aside-20260711
mv /etc/xdg/autostart/xfce4-notifyd.desktop /etc/xdg/autostart/xfce4-notifyd.desktop.retired-aside-20260711

# C4: mask the static user unit so nothing can start it by unit name
#     (run as stephen, NO sudo — it writes ~/.config/systemd/user/)
systemctl --user mask xfce4-notifyd.service

# C5: keep pacman upgrades from resurrecting the retired files
#     (NoExtract paths have no leading slash — pacman.conf(5))
grep -q 'xfce4-notifyd' /etc/pacman.conf || sed -i '/^\[options\]/a NoExtract = usr/share/dbus-1/services/org.xfce.xfce4-notifyd.* etc/xdg/autostart/xfce4-notifyd.desktop usr/lib/systemd/user/xfce4-notifyd.service' /etc/pacman.conf
```

Alternative to C1-C5 (operator decision — removes both unused packages;
xfce4-power-manager is xfce4-notifyd's only dependent, is not running, and
power is Sentinel/Zen's job):
```sh
pacman -Rns xfce4-notifyd xfce4-power-manager
```

## D. appmenu-gtk-module retirement — REQUIRED (Fix 5; durable)

```sh
# D1: remove the package — leaf, nothing depends on it (pactree -r verified);
#     this drops the xinitrc.d script, the GTK3 .so, and its user unit at once
pacman -Rns appmenu-gtk-module

# D2: if a future dependency ever reinstalls it, never let its loader script,
#     module, or unit reach the filesystem again (durable retirement)
grep -q 'appmenu-gtk-module' /etc/pacman.conf || sed -i '/^\[options\]/a NoExtract = etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh usr/lib/gtk-3.0/modules/libappmenu-gtk-module.so usr/lib/systemd/user/appmenu-gtk-module.service' /etc/pacman.conf
```

If the operator declines package removal, the minimum effective step instead
of D1 is (glob `?*.sh` no longer matches the renamed file):
```sh
mv /etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh /etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh.retired-aside-20260711
```

## E. Install the staged files (master script's copy step, for completeness)

```sh
# E1/E2: staged, verified copies over the live ones (bash -n rc=0 on both)
install -o root -g root -m 755 <patchdir>/src/usr/local/bin/ncde-chromium-sync.sh /usr/local/bin/ncde-chromium-sync.sh
install -o root -g root -m 755 <patchdir>/src/usr/local/bin/ncde-x11-session /usr/local/bin/ncde-x11-session
```

No command needed for Fix 3 (QML cache — per-user path, self-creating) or
Fix 6 (picom.conf untouched).
