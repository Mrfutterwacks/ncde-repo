#include <cstdarg>
#include <cstdio>

struct Call
{
    long number;
    int which;
    int who;
    int priority;
};

static Call calls[2]{};
static int callCount = 0;
extern "C" long recordedSyscall(long number, ...) noexcept;

#define syscall recordedSyscall
#include "../src/IdleIoScope.h"
#undef syscall

extern "C" long recordedSyscall(long number, ...) noexcept
{
    va_list args;
    va_start(args, number);
    const int which = va_arg(args, int);
    const int who = va_arg(args, int);
    const int priority = va_arg(args, int);
    va_end(args);
    if (callCount < 2)
        calls[callCount++] = {number, which, who, priority};
    return 0;
}

int main()
{
    {
        IdleIoScope disabled(false);
    }
    if (callCount != 0) {
        std::puts("FAIL disabled scope issued a syscall");
        return 1;
    }
    {
        IdleIoScope idle(true);
        if (callCount != 1 || calls[0].number != SYS_ioprio_set || calls[0].which != 1
            || calls[0].who != 0 || calls[0].priority != 0x6007) {
            std::puts("FAIL idle entry did not request IOPRIO_CLASS_IDLE/7 for this process");
            return 1;
        }
    }
    if (callCount != 2 || calls[1].number != SYS_ioprio_set || calls[1].which != 1
        || calls[1].who != 0 || calls[1].priority != 0x4004) {
        std::puts("FAIL scope exit did not restore IOPRIO_CLASS_NONE/4");
        return 1;
    }
    std::puts("PASS IdleIoScope records oracle enter/restore priorities; disabled scope is inert");
    return 0;
}
