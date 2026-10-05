"""PWM fan-control backstop — the thermal guardian's manual-override path.

Per sentinel-plan.md §1.C: leave firmware/driver fan control in charge
normally (pwmN_enable=2, automatic). Only intervene when a temp crosses
CRITICAL: take manual control (pwmN_enable=1), drive pwmN to full speed,
hold until every critical sensor cools back below its hysteresis band, then
hand back to automatic. This is a backstop, not a custom fan curve — opt-in
curves are explicitly out of scope here (sentinel-plan.md's own v1 framing).

ABI (verified against the real kernel hwmon sysfs-interface docs, not
guessed): pwmN_enable: 0 = no control (fan at full speed), 1 = manual
(pwmN written directly), 2+ = automatic, chip-specific. pwmN: integer
0-255, 255 = 100%.

MANDATORY fail-safe (sentinel-plan.md's "#1 hazard"): pwmN_enable MUST be
restored to automatic on ANY exit/crash/signal — a daemon that dies holding
a fan in manual-low state risks a real overheat. Also a never-off floor:
this module only ever drives pwmN to full speed (255) while engaged, never
a lower value, and never 0.

Real, live sysfs probing only, same discipline as hwmon.py/hw_tier.py/
scx_select.py — no hardcoded chip/pwm paths. Silently a no-op if this
machine has no controllable PWM fan at all (verified live on the reference
dev machine, a Jasper Lake whitebox: zero pwm*/fan*_input files exist under
/sys/class/hwmon — matches zen_hints.py's RAPL-cap rationale for the same
machine, and sentinel-plan.md §4d's own live probe).
"""

import atexit
import glob
import logging
import os
import signal

from ._utils import read_sysfs

log = logging.getLogger(__name__)

PWM_FULL_SPEED     = "255"   # never-off floor: engaged always means full speed, never a lower value
PWM_ENABLE_MANUAL  = "1"
PWM_ENABLE_AUTO    = "2"


def _write(path, value):
    with open(path, "w") as f:
        f.write(value)


class PwmGuard:
    """Manual-override fan backstop. Discovers every writable pwmN on this
    machine at construction; engage()/release_all() only ever touch
    pwmN_enable/pwmN, nothing else. Registers an atexit hook + SIGTERM/SIGINT
    handlers so ANY process exit restores automatic control — the mandatory
    fail-safe. Safe no-op (never engages) if no controllable fan is found."""

    def __init__(self):
        self._pwms = []          # [{name, enable, pwm}]
        self._engaged = set()    # enable-file paths currently held manual by us
        self._discover()
        if self._pwms:
            atexit.register(self.release_all)
            for sig in (signal.SIGTERM, signal.SIGINT):
                signal.signal(sig, self._on_signal)

    def _discover(self):
        for chip in sorted(glob.glob("/sys/class/hwmon/hwmon*")):
            name = read_sysfs(os.path.join(chip, "name")) or os.path.basename(chip)
            for enable_path in sorted(glob.glob(os.path.join(chip, "pwm*_enable"))):
                pwm_path = enable_path[: -len("_enable")]
                if not os.path.exists(pwm_path):
                    continue
                if not os.access(enable_path, os.W_OK) or not os.access(pwm_path, os.W_OK):
                    continue   # present but not writable — skip, don't force it
                self._pwms.append({"name": name, "enable": enable_path, "pwm": pwm_path})
        if self._pwms:
            log.info("pwm_guard: %d controllable PWM fan(s) found (thermal backstop armed)",
                      len(self._pwms))
        else:
            log.info("pwm_guard: no controllable PWM fan found on this machine — backstop is a no-op")

    def available(self):
        return bool(self._pwms)

    def engage(self):
        """Take manual control and drive every discovered fan to full speed.
        Idempotent — safe to call repeatedly while still critical, and a
        pure no-op if no fan was ever discovered."""
        for p in self._pwms:
            try:
                if p["enable"] not in self._engaged:
                    _write(p["enable"], PWM_ENABLE_MANUAL)
                    self._engaged.add(p["enable"])
                _write(p["pwm"], PWM_FULL_SPEED)
            except OSError:
                log.warning("pwm_guard: failed to engage %s", p["name"], exc_info=True)

    def release_all(self):
        """Hand every engaged fan back to automatic control. Must be safe to
        call repeatedly (atexit + signal handler + normal cool-down all call
        this) and must never raise."""
        for enable_path in list(self._engaged):
            try:
                _write(enable_path, PWM_ENABLE_AUTO)
            except OSError:
                log.warning("pwm_guard: failed to release %s back to automatic",
                            enable_path, exc_info=True)
            finally:
                self._engaged.discard(enable_path)

    def _on_signal(self, signum, _frame):
        self.release_all()
        signal.signal(signum, signal.SIG_DFL)
        os.kill(os.getpid(), signum)   # re-raise so systemd still sees the expected termination
