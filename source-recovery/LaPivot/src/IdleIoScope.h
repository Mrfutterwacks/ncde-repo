// IdleIoScope — RAII scope that lowers the calling thread's I/O priority to IDLE (class 3) while idle
// work runs, and restores it to NONE (class 0, level 4) on exit. Used by Lelan::drainIdleQueue
// so deferred jobs don't compete with the UI thread's I/O.
// Rebuilt from oracle: IdleIoScope::IdleIoScope(bool), ~IdleIoScope() — the decompile shows syscall
// IOPRIO_SET (SYS_ioprio_set) with the oracle's exact constants: 0x6007 = SET class=IDLE level=7
// on enter, 0x4004 = SET class=NONE level=4 on exit.
#pragma once

#include <sys/syscall.h>
#include <unistd.h>

class IdleIoScope
{
public:
    explicit IdleIoScope(bool on = true) noexcept : m_on(on)
    {
        if (m_on) {
            // SET I/O priority to IDLE class (3), priority level 7 (lowest within IDLE)
            // syscall(SYS_ioprio_set, which=IOPRIO_WHO_PROCESS=1, who=0=self, ioprio=0x6007)
            syscall(SYS_ioprio_set, 1, 0, 0x6007);
        }
    }
    ~IdleIoScope() noexcept
    {
        if (m_on) {
            // Restore to NONE class (0), priority level 4 (default)
            syscall(SYS_ioprio_set, 1, 0, 0x4004);
        }
    }
    IdleIoScope(const IdleIoScope &) = delete;
    IdleIoScope &operator=(const IdleIoScope &) = delete;

private:
    bool m_on = false;
};