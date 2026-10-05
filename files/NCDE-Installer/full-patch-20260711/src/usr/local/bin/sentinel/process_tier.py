"""Per-window resource tiering — moves a client PID into a transient systemd
cgroup v2 scope sized for its visibility tier, on Lelan's request over D-Bus.

Chain of command (operator, 2026-07-01): Sentinel senses and executes; Lelan is
the only thing that decides. This module never infers a tier on its own — it
only acts on an explicit SetProcessTier(pid, tier) call.

D-Bus call shape verified live against the real systemd on this host before
being used here (StartTransientUnit's PIDs=/CPUWeight= properties, and
org.freedesktop.systemd1.Unit's Freeze()/Thaw() methods — NOT on the Scope
interface, despite scopes being the unit type created).

── NCDE live patch 2026-07-11 — two operator-visible bugs fixed here ──────────
1. NEVER FREEZE. The old "hidden" tier cgroup-FROZE a minimized window's whole
   PROCESS. A frozen process cannot repaint (→ solid-black window on restore/
   uncover) and cannot service WM_DELETE (→ the ✕ does nothing). Because the
   freeze is per-PID while tiers are emitted per-window, minimizing ONE window
   of a multi-window app (e.g. Chromium) froze the still-visible sibling into a
   black zombie. Fix: hidden windows are now STARVED (CPUWeight 1), never frozen
   — they stay repaintable and closable. App-Nap intent preserved (near-zero
   CPU) without the black-hole side effect.
2. OPTIMIZE GAMES, don't nap them (operator: "Lelan was supposed to optimize
   everything including Steam"). A Steam/Proton game's window PID was being
   tiered like a text editor — dropped to background (CPUWeight 25 = 1/400) or
   frozen whenever it lost focus/was covered, starving its render+input thread
   (laggy/dropped clicks in build-a-sim / marketplace). Fix: a Steam/game PID is
   always held at FOREGROUND priority and never throttled or frozen.

── 2026-09-25 — "nothing on the desktop is clickable" (operator) ──────────────
Operator: "app nap should not cause apps to freeze and apps should not compete
with each other causing nothing to be clickable on the desktop". Root cause was
HERE, not in Lelan: StartTransientUnit on the SYSTEM manager with no Slice=
put every tiered app in /system.slice -- next to Xorg (/system.slice/
ncde-portal.service, weight 100). A busy focused app at CPUWeight 10000 then
out-weighed the X server 100:1, so clicks queued behind it everywhere; hidden
apps pulled out of the user session at weight 1 stalled shutdown (SIGTERM
needs CPU to be handled). Fix:
  * every app scope lives in ONE per-user slice, user-<uid>-ncdeapps.slice,
    a child of user-<uid>.slice. All apps together weigh the same as the
    shell's own session scope (LaPivot, picom), and the system (Xorg) is
    never in the same contest -- no app, however busy, can starve the shell.
  * gentle weights inside that slice: foreground 100 (the default -- the
    focused app never out-ranks anything outside its slice), background 50,
    hidden 10. App-Nap still means minimized apps yield first under load;
    idle, weights do nothing at all -- nothing ever stops or freezes.
  * new unit prefix ncde-nap-<pid>.scope so a pid still in an old
    /system.slice ncde-tier scope is MOVED into the new slice on its next
    call (a scope can't change slice; moving the pid lets the old one GC).
  * ClearProcessTier now hands the process back its neutral weight (100);
    it used to only forget the pid, leaving a tray-only app starved forever.
── 2026-09-30 — PER-PROCESS PRIORITY; apps stay in the login session (operator decision) ─────
Measured: moving a window's pid into ncde-nap-<pid>.scope takes it OUT of its logind session
(session membership is the cgroup path). logind: "PID does not belong to any known session";
polkit: power-off / inhibit-block-sleep -> auth_admin_keep for a napped app vs yes in-session —
video players could no longer block sleep without a password. Now App Nap never moves a
process. Each tier is a per-process CPU nice offset + I/O priority, applied to every thread of
the window's process and its existing descendants (new threads/children inherit it):
    foreground  nice +0  (the app's own nice)   I/O best-effort 4 (kernel default)
    background  nice +5  (~1/3 CPU share)       I/O best-effort 6
    hidden      nice +10 (~1/10 CPU share)      I/O best-effort 7
The Zen scheduler (scx_bpfland) and CFS both weight by nice; nothing is ever frozen or stopped;
idle, nice changes nothing. Xorg stays in system.slice, a separate cgroup, so no app can outweigh
the display server (the 2026-09-25 "nothing clickable" fix is preserved by that, not by a slice).
Apps left in ncde-nap scopes by the old mechanism are moved back into their session scope at
start-up by writing the pid to /sys/fs/cgroup/user.slice/user-<uid>.slice/session-<audit
sessionid>.scope/cgroup.procs (systemd's AttachProcessesToUnit refuses session scopes: "Process
migration not available on non-delegated units" — measured 2026-09-30).
"""

import logging
import os
import time

import dbus
from gi.repository import GLib

log = logging.getLogger(__name__)

SYSTEMD_BUS_NAME = "org.freedesktop.systemd1"
SYSTEMD_OBJ_PATH = "/org/freedesktop/systemd1"
SYSTEMD_MANAGER_IFACE = "org.freedesktop.systemd1.Manager"
SYSTEMD_UNIT_IFACE = "org.freedesktop.systemd1.Unit"

# cgroup v2 cpu.weight range is 1-10000 (default 100). Weights are relative
# to siblings in user-<uid>-ncdeapps.slice only (see the 2026-09-25 note):
# foreground = default, background yields 2:1, hidden yields 10:1. Never frozen.
TIER_WEIGHTS = {"foreground": 100, "background": 50, "hidden": 10}
NEUTRAL_WEIGHT = 100


def _apps_slice(pid):
    """user-<uid>-ncdeapps.slice for the pid's owner (child of user-<uid>.slice)."""
    try:
        uid = os.stat("/proc/%d" % pid).st_uid
    except OSError:   # exited mid-call: fail like any other D-Bus error
        raise dbus.DBusException("pid %d is gone" % pid,
                                 name="org.freedesktop.DBus.Error.InvalidArgs")
    return "user-%d-ncdeapps.slice" % uid
VALID_TIERS = ("foreground", "background", "hidden")

# How often a still-unresolvable rejected pid is allowed to re-log (2026-07-14
# fix) — the outcome can't change faster than this, so re-warning every single
# call (observed: 29k+/session for one pid) is pure journal spam.
REJECT_LOG_COOLDOWN_S = 60


def _is_steam_or_game(pid):
    """True if this PID belongs to Steam or a game (Proton/Wine/gamescope), so it
    can be OPTIMIZED (held at foreground, never throttled/frozen) rather than
    resource-napped. Detection uses only kernel-set facts under /proc — the
    process's cgroup (Flatpak Steam lives under a com.valvesoftware.Steam scope),
    its comm, and its exe path (pressure-vessel / steamapps / Proton). Cheap,
    spoofing-irrelevant (a user throttling their own game only hurts themselves),
    and fail-open-to-normal-tiering on any read error."""
    try:
        with open("/proc/%d/cgroup" % pid) as f:
            cg = f.read()
        if "valvesoftware.Steam" in cg or "com.valvesoftware" in cg:
            return True
    except OSError:
        pass
    try:
        comm = open("/proc/%d/comm" % pid).read().strip().lower()
        if comm in ("steam", "gamescope", "wine", "wine64", "wineserver",
                    "proton", "reaper", "pressure-vessel") or "steam" in comm:
            return True
    except OSError:
        pass
    try:
        exe = os.readlink("/proc/%d/exe" % pid)
        if "steamapps" in exe or "pressure-vessel" in exe or "Proton" in exe \
                or "/steam" in exe.lower():
            return True
    except OSError:
        pass
    return False


def _caller_may_tier(caller_uid, pid):
    """Authorization gate (2026-07-04): io.ncde.Sentinel.conf's <policy
    context="default"> allows ANY local user to call SetProcessTier with an
    arbitrary caller-supplied pid — Sentinel runs as root and this method
    freezes/throttles that pid's cgroup, so without this check any
    unprivileged user could freeze or throttle a process they don't own
    (including another user's, or root's) — a real local DoS/privilege-
    escalation hole, not a style nit. This project has no polkit integration
    anywhere (checked), and it's a single-seat desktop where the only
    legitimate caller (Lelan, running as the logged-in user) only ever tiers
    that SAME user's own application windows — so "caller uid owns the
    target pid" is the correct, minimal, real check, not a stopgap. uid is
    resolved by the D-Bus daemon itself (BusConnection.get_unix_user(sender),
    verified against dbus-python's real API), never anything the caller could
    spoof; the pid's owning uid is read from /proc/<pid>'s own inode owner,
    set by the kernel, not from anything the caller supplies. Root callers
    (uid 0) always pass, matching root's real ambient authority."""
    if caller_uid == 0:
        return True
    try:
        return os.stat("/proc/%d" % pid).st_uid == caller_uid
    except OSError:
        return False   # pid doesn't exist (already gone / racing exit) — nothing to tier


def _resolve_ns_pid(pid):
    """Translate a pid namespace's own pid (e.g. a Flatpak/bwrap sandbox's
    _NET_WM_PID, meaningless on the host) to the real host pid via
    /proc/*/status's NSpid field (proc_pid_status(5)): "the process's pid in
    each pid namespace of which it is a member" — leftmost = host namespace,
    rightmost = innermost/sandbox namespace. If some host process's innermost
    NSpid entry equals `pid`, that process's own (host) pid is the real pid
    Lelan actually meant. Returns None if no match (not namespaced, or the
    owning process is already gone) — never raises, never assumes /proc is
    fully readable (skips entries that vanish mid-scan)."""
    try:
        candidates = os.listdir("/proc")
    except OSError:
        return None
    for entry in candidates:
        if not entry.isdigit():
            continue
        try:
            with open("/proc/%s/status" % entry) as f:
                for line in f:
                    if line.startswith("NSpid:"):
                        ns_pids = line.split()[1:]
                        if len(ns_pids) > 1 and ns_pids[-1] == str(pid):
                            return int(entry)
                        break
        except (OSError, ValueError):
            continue
    return None


TIER_NICE = {"foreground": 0, "background": 5, "hidden": 10}
TIER_IO_LEVEL = {"foreground": 4, "background": 6, "hidden": 7}   # best-effort class levels
IOPRIO_CLASS_BE = 2
IOPRIO_WHO_PROCESS = 1
_SYS_IOPRIO_SET = {"x86_64": 251, "aarch64": 30, "armv7l": 314, "i686": 289, "riscv64": 30}


def _ioprio_set(tid, level):
    """Best-effort I/O priority for one thread. Silent no-op where unsupported."""
    import ctypes, platform
    nr = _SYS_IOPRIO_SET.get(platform.machine())
    if nr is None:
        return
    libc = ctypes.CDLL(None, use_errno=True)
    libc.syscall(nr, IOPRIO_WHO_PROCESS, tid, (IOPRIO_CLASS_BE << 13) | level)


def _threads(pid):
    try:
        return [int(t) for t in os.listdir("/proc/%d/task" % pid)]
    except OSError:
        return []


def _descendants(pid):
    """pid plus every live descendant process (via /proc/<pid>/task/*/children)."""
    out, todo, seen = [], [pid], set()
    while todo:
        p = todo.pop()
        if p in seen:
            continue
        seen.add(p)
        out.append(p)
        for t in _threads(p):
            try:
                with open("/proc/%d/task/%d/children" % (p, t)) as f:
                    todo.extend(int(c) for c in f.read().split())
            except (OSError, ValueError):
                pass
    return out


class ProcessTiers:
    """Per-process App Nap: nice offset + I/O priority per visibility tier (see module doc)."""

    def __init__(self, bus, gamemode=None):
        self._bus = bus
        self._manager = dbus.Interface(
            bus.get_object(SYSTEMD_BUS_NAME, SYSTEMD_OBJ_PATH),
            SYSTEMD_MANAGER_IFACE,
        )
        self._base_nice = {}   # pid -> the process's own nice before we touched it
        self._tier = {}        # pid -> last applied tier
        # NCDE GameMode session manager (2026-07-12): the per-window tier here is
        # the CPU/IO half; gamemode drives the system-wide half (governor/GPU/
        # screensaver) for actual games. Optional so this module still works
        # standalone / in tests.
        self._gamemode = gamemode
        # Flatpak/sandboxed-pid translation (2026-07-14): a Flatpak window's _NET_WM_PID is
        # the sandbox-internal pid; resolve it to the real host pid once per process.
        self._ns_resolved = {}     # original (sandbox) pid -> real host pid
        self._rejected_at = {}     # pid -> monotonic time of last rejection log
        GLib.idle_add(self._return_napped_to_sessions)

    def _resolve_sandboxed_pid(self, pid, caller_uid):
        """Translate a rejected (sandbox) pid via NSpid and re-check ownership; cached."""
        cached = self._ns_resolved.get(pid)
        if cached is not None:
            if os.path.exists("/proc/%d" % cached):
                return cached if _caller_may_tier(caller_uid, cached) else None
            self._ns_resolved.pop(pid, None)   # stale — target exited, re-resolve
        real = _resolve_ns_pid(pid)
        if real is not None and real != pid and _caller_may_tier(caller_uid, real):
            self._ns_resolved[pid] = real
            return real
        return None

    def set_tier(self, pid, tier, caller_uid):
        """Apply `tier` to `pid` (and its descendants). True on success, False to mean
        "leave it alone" (unknown tier, not the caller's process, already gone). Never raises."""
        if tier not in VALID_TIERS or pid <= 0:
            if tier not in VALID_TIERS:
                log.warning("SetProcessTier: unknown tier %r for pid %d", tier, pid)
            return False
        if not _caller_may_tier(caller_uid, pid):
            real_pid = self._resolve_sandboxed_pid(pid, caller_uid)
            if real_pid is None:
                now = time.monotonic()
                last = self._rejected_at.get(pid)
                if last is None or (now - last) >= REJECT_LOG_COOLDOWN_S:
                    log.warning("SetProcessTier(%d): rejected — caller uid %d does not own this pid",
                                pid, caller_uid)
                    self._rejected_at[pid] = now
                return False
            log.info("SetProcessTier(%d): resolved sandboxed pid -> real host pid %d", pid, real_pid)
            pid = real_pid

        # OPTIMIZE GAMES (2026-07-11): Steam/Proton/Wine is always foreground.
        if _is_steam_or_game(pid):
            tier = "foreground"
            if self._gamemode is not None:
                self._gamemode.note(pid)

        if self._tier.get(pid) == tier:
            return True
        if pid not in self._base_nice:
            try:
                self._base_nice[pid] = os.getpriority(os.PRIO_PROCESS, pid)
            except OSError:
                return False
        ok = self._apply(pid, tier)
        if ok:
            self._tier[pid] = tier
        return ok

    def _apply(self, pid, tier):
        nice = min(19, self._base_nice.get(pid, 0) + TIER_NICE[tier])
        level = TIER_IO_LEVEL[tier]
        touched = 0
        for proc in _descendants(pid):
            for tid in _threads(proc):
                try:
                    os.setpriority(os.PRIO_PROCESS, tid, nice)
                    _ioprio_set(tid, level)
                    touched += 1
                except OSError:
                    pass   # thread exited mid-walk
        if not touched:
            self._forget(pid)
        return touched > 0

    def drop(self, pid):
        """Window/process gone (ClearProcessTier): hand a still-living process its own priority
        back (tray apps outlive their windows), then forget it."""
        if pid in self._base_nice and os.path.exists("/proc/%d" % pid):
            self._apply(pid, "foreground")
        self._forget(pid)
        if self._gamemode is not None:
            self._gamemode.forget(pid)

    def _forget(self, pid):
        self._base_nice.pop(pid, None)
        self._tier.pop(pid, None)

    def _return_napped_to_sessions(self):
        """One-shot migration: processes the old mechanism left in ncde-nap-<pid>.scope go back
        into their login session's scope (cgroupfs write, root), restoring session membership."""
        moved, failed = 0, 0
        for entry in os.listdir("/proc"):
            if not entry.isdigit():
                continue
            pid = int(entry)
            try:
                with open("/proc/%d/cgroup" % pid) as f:
                    if "/ncde-nap-" not in f.read():
                        continue
                with open("/proc/%d/sessionid" % pid) as f:
                    sid = int(f.read().strip())
                # the SESSION's user (loginuid survives sudo/su), not the process owner — a
                # `sudo` run from a napped terminal is uid 0 but belongs to the user's session
                with open("/proc/%d/loginuid" % pid) as f:
                    uid = int(f.read().strip())
                if sid <= 0 or sid == 4294967295 or uid == 4294967295:
                    continue
                procs = "/sys/fs/cgroup/user.slice/user-%d.slice/session-%d.scope/cgroup.procs" % (uid, sid)
                with open(procs, "w") as f:
                    f.write("%d\n" % pid)
                moved += 1
            except (OSError, ValueError) as exc:
                failed += 1
                log.warning("App Nap: could not return pid %d to its session: %s", pid, exc)
        if moved or failed:
            log.info("App Nap: returned %d process(es) from ncde-nap scopes to their login session"
                     " (%d failed)", moved, failed)
        return False   # one-shot GLib idle
