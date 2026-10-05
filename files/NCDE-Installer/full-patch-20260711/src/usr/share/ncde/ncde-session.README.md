# ncde-session — session save/restore helper

Standalone helper (like Sentinel / Vesper / App-Nap). Restores the user's apps
across logout. **Zero window-manager modification**: it only READS X11 + /proc
and WRITES its own JSON under `~/.config/ncde/`.

## Mechanism
Driven by the systemd **user** unit `ncde-session.service`
(`Type=oneshot`, `RemainAfterExit=yes`):

* `ExecStart=ncde-session restore` — runs at login; relaunches the saved apps.
* `ExecStop=ncde-session save` — runs on logout (when the user session stops,
  while `$DISPLAY` is still up); snapshots the current apps.

## save
Enumerate top-level client windows (EWMH `_NET_CLIENT_LIST` if published, else an
`XQueryTree` walk from the root, since LaPivot publishes no client list), map each
to its PID via `_NET_WM_PID`, read `/proc/PID/cmdline` (the real launch command),
de-duplicate, and write `{cmdline, wm_class, geometry}` records to
`~/.config/ncde/session.json`. Only genuine user apps are captured (see filter).

## restore
Read `session.json`, re-apply the HARD-DENY filter (defence in depth), launch each
resolvable `cmdline` detached, skip anything already running, then rotate the
snapshot aside (`session.json.<stamp>.restored`, last 5 kept) so a re-trigger
never double-launches.

## Safety
`HARD-DENY` always wins and is applied at **both** save and restore: LaPivot,
ncde-frame, ncde-container, ncde-x11-session, every `/usr/local/bin/ncde-*` daemon
(sentinel/appnap/mic/automount/stats/proxy/news/portal/session), picom, dbus,
systemd(-*), xss-lock, xdg-desktop-portal, and this helper itself. A curated
ALLOWLIST of house/dock apps is a fast-accept path; any other genuine GUI app
(normal top-level window + real exec) is also accepted. Every code path is
wrapped to exit 0 — the helper never crashes the session, and never relaunches
the WM, panels, the session script, daemons, or itself. When the display cannot
be read at save time, an existing good snapshot is left untouched.
