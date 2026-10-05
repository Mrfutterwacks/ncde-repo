"""NCDE GameMode — the system-wide half of "NCDE is its own GameMode".

process_tier.py already handles the PER-WINDOW half (a Steam/game PID is pinned
to the foreground cgroup tier: CPUWeight/IOWeight ceiling, never throttled/frozen).
This module adds the SESSION-WIDE half, the equivalent of Feral GameMode's global
actuators, activated while an ACTUAL game is running and RESTORED the moment the
last one exits:

  • CPU governor + EPP → performance   (overriding zen_hints' AC/battery pick)
  • GPU → max performance              (i915 pin min:=max; AMD dpm force=high)
  • screensaver / DPMS inhibited        (X session, since NCDE idle-lock is xss-lock
                                         driven by X DPMS — NOT logind, so a logind
                                         inhibitor would not stop it)

Design rules (learned the hard way on this project):
  1. NEVER leave the system pinned. Every actuator saves the prior value and is
     restored on deactivate, on daemon shutdown (_shutdown in __main__), and via
     atexit. Restore is idempotent.
  2. Actual games only. `_is_steam_or_game` in process_tier is broad (it includes
     the Steam CLIENT so the launcher UI stays responsive) — but firing governor/
     GPU/screensaver just because the Steam library window is open would be
     wasteful. `is_actual_game()` here is the stricter gate: Proton/Wine/gamescope
     or a steamapps/Proton exe — i.e. a game is really running.
  3. Detect-and-skip like the rest of Sentinel: every knob no-ops cleanly on
     hardware/sessions that don't have it, never assumed present.

Chain of command: this is Sentinel SENSING a game and EXECUTING optimization —
the same detection-based, autonomous game handling process_tier already does
(operator: "Lelan was supposed to optimize everything including Steam"). A
GameModeChanged(active) signal is emitted so the session side can react too.
"""

import atexit
import glob
import logging
import os
import subprocess

from ._utils import read_sysfs

log = logging.getLogger(__name__)


def _write(path, value):
    try:
        with open(path, "w") as f:
            f.write(value)
        return True
    except OSError:
        return False


# ── actual-game detection (stricter than process_tier._is_steam_or_game) ──────
_GAME_COMMS = ("gamescope", "wine", "wine64", "wineserver", "proton",
               "wineboot", "win.exe")


def is_actual_game(pid):
    """True only for a real running game (Proton/Wine/gamescope or a steamapps/
    Proton exe) — NOT the plain Steam client/steamwebhelper. Used to gate the
    session-wide actuators so they fire when you're gaming, not when the library
    is merely open. Fail-open-to-not-a-game on any read error."""
    try:
        comm = open("/proc/%d/comm" % pid).read().strip().lower()
        if comm in _GAME_COMMS or comm.endswith(".exe"):
            return True
    except OSError:
        pass
    try:
        exe = os.readlink("/proc/%d/exe" % pid).lower()
        if "steamapps" in exe or "/proton" in exe or "proton" in exe:
            return True
    except OSError:
        pass
    return False


def _pid_alive(pid):
    return os.path.exists("/proc/%d" % pid)


class GameMode:
    """Refcounts running games; drives the global actuators on 0→1 and restores
    them on 1→0. `restore_power` is a no-arg callable that re-applies the normal
    governor/EPP/dirty_ratio for the current AC/battery state (zen_hints.apply),
    used to undo the performance override. `emit_changed` is an optional
    callable(active: bool) for the GameModeChanged D-Bus signal."""

    def __init__(self, restore_power, emit_changed=None):
        self._restore_power = restore_power
        self._emit_changed = emit_changed
        self._pids = set()          # live actual-game pids
        self._active = False
        self._saved_gpu = {}        # sysfs path -> prior value (for restore)
        self._saved_screensaver = None   # (display, xauth) currently inhibited
        atexit.register(self.shutdown_restore)

    @property
    def active(self):
        return self._active

    # ── membership ────────────────────────────────────────────────────────────
    def note(self, pid):
        """Called from process_tier when a foreground game PID is tiered."""
        if not is_actual_game(pid):
            return
        if pid not in self._pids:
            self._pids.add(pid)
            if not self._active:
                self._activate()

    def forget(self, pid):
        """Called from process_tier.drop (window/process gone)."""
        if pid in self._pids:
            self._pids.discard(pid)
            if self._active and not self._pids:
                self._deactivate()

    def reap(self):
        """Timer-driven liveness sweep: a game has helper PIDs that Lelan never
        explicitly clears, so drop any dead ones and deactivate when none remain.
        Returns True so it can be used directly as a GLib timeout."""
        dead = {p for p in self._pids if not _pid_alive(p)}
        if dead:
            self._pids -= dead
            if self._active and not self._pids:
                self._deactivate()
        return True

    # ── activate / deactivate ──────────────────────────────────────────────────
    def _activate(self):
        self._active = True
        log.info("GameMode ON — game pid(s) %s", sorted(self._pids))
        self._governor_performance()
        self._gpu_performance()
        self._screensaver_inhibit(True)
        self._signal(True)

    def _deactivate(self):
        self._active = False
        log.info("GameMode OFF — restoring normal power/GPU/screensaver")
        self._gpu_restore()
        self._screensaver_inhibit(False)
        try:
            self._restore_power()        # zen_hints.apply(on_battery) — governor/EPP back to policy
        except Exception:
            log.warning("GameMode: restore_power failed", exc_info=True)
        self._signal(False)

    def shutdown_restore(self):
        """Idempotent hard restore for daemon shutdown / atexit — never leave the
        box pinned. Restores GPU + screensaver directly; governor/EPP are left to
        the normal startup apply_zen (a stopping daemon can't re-run it reliably)."""
        if self._saved_gpu:
            self._gpu_restore()
        if self._saved_screensaver:
            self._screensaver_inhibit(False)
        self._active = False

    def reassert_governor(self):
        """Called after a power-profile change so a battery/AC event mid-game does
        not drop the game off the performance governor."""
        if self._active:
            self._governor_performance()

    # ── actuators (each detect-and-skip, fail-safe) ────────────────────────────
    def _governor_performance(self):
        for cpufreq in glob.glob("/sys/devices/system/cpu/cpu*/cpufreq"):
            avail = (read_sysfs("%s/scaling_available_governors" % cpufreq) or "").split()
            for cand in ("performance", "schedutil", "ondemand"):
                if cand in avail:
                    _write("%s/scaling_governor" % cpufreq, cand)
                    break
            epp_avail = (read_sysfs("%s/energy_performance_available_preferences" % cpufreq) or "").split()
            for cand in ("performance", "balance_performance"):
                if cand in epp_avail:
                    _write("%s/energy_performance_preference" % cpufreq, cand)
                    break

    def _gpu_performance(self):
        for card in glob.glob("/sys/class/drm/card?"):
            # Intel i915: pin the min render clock up to the max while gaming.
            gmin, gmax = "%s/gt_min_freq_mhz" % card, "%s/gt_max_freq_mhz" % card
            cur_min, cur_max = read_sysfs(gmin), read_sysfs(gmax)
            if cur_min is not None and cur_max:
                self._saved_gpu.setdefault(gmin, cur_min)
                _write(gmin, cur_max)
            # AMD: force the DPM performance level high.
            dpm = "%s/device/power_dpm_force_performance_level" % card
            cur_dpm = read_sysfs(dpm)
            if cur_dpm is not None:
                self._saved_gpu.setdefault(dpm, cur_dpm)
                _write(dpm, "high")

    def _gpu_restore(self):
        for path, value in list(self._saved_gpu.items()):
            _write(path, value)
            self._saved_gpu.pop(path, None)

    def _session_x_env(self):
        """Best-effort DISPLAY + XAUTHORITY of the graphical session, read from
        the WM's own /proc/<pid>/environ (root can read it). Returns (display,
        xauth) or None — Sentinel is a root system service with no X of its own,
        so screensaver control has to borrow the session's cookie."""
        for name in ("LaPivot", "ncde-wm"):
            for pid in glob.glob("/proc/[0-9]*"):
                try:
                    if open("%s/comm" % pid).read().strip() != name:
                        continue
                    env = dict(
                        kv.split("=", 1)
                        for kv in open("%s/environ" % pid).read().split("\0")
                        if "=" in kv)
                except OSError:
                    continue
                disp = env.get("DISPLAY")
                if disp:
                    return disp, env.get("XAUTHORITY", "")
        return None

    def _screensaver_inhibit(self, inhibit):
        if inhibit:
            envinfo = self._session_x_env()
            if not envinfo:
                log.info("GameMode: no X session found — screensaver inhibit skipped")
                return
            disp, xauth = envinfo
            if self._xset(disp, xauth, ["s", "off", "-dpms"]):
                self._saved_screensaver = (disp, xauth)
                log.info("GameMode: screensaver/DPMS inhibited on %s", disp)
        else:
            if not self._saved_screensaver:
                return
            disp, xauth = self._saved_screensaver
            self._xset(disp, xauth, ["s", "on", "+dpms"])
            self._saved_screensaver = None
            log.info("GameMode: screensaver/DPMS restored on %s", disp)

    @staticmethod
    def _xset(display, xauth, args):
        env = {"DISPLAY": display, "PATH": "/usr/bin:/bin"}
        if xauth:
            env["XAUTHORITY"] = xauth
        try:
            subprocess.run(["xset"] + args, env=env,
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                           timeout=5, check=False)
            return True
        except (OSError, subprocess.SubprocessError):
            return False

    def _signal(self, active):
        if self._emit_changed:
            try:
                self._emit_changed(bool(active))
            except Exception:
                log.debug("GameModeChanged signal failed", exc_info=True)
