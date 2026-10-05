// dbus_call_log.cpp — LD_PRELOAD shim for tests: logs every D-Bus method call the process makes through
// QDBusConnection::asyncCall (member + destination + path), one line each, to $DBUS_CALL_LOG, then does the
// real call. Needed because a normal user cannot eavesdrop method calls on the system bus.
//   g++ -std=c++17 -fPIC -shared -o dbus_call_log.so dbus_call_log.cpp $(pkg-config --cflags --libs Qt6DBus) -ldl
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

using Real = QDBusPendingCall (*)(const QDBusConnection *, const QDBusMessage &, int);

QDBusPendingCall QDBusConnection::asyncCall(const QDBusMessage &message, int timeout) const
{
    static Real real = reinterpret_cast<Real>(dlsym(RTLD_NEXT, "_ZNK15QDBusConnection9asyncCallERK12QDBusMessagei"));
    if (const char *path = std::getenv("DBUS_CALL_LOG")) {
        if (FILE *f = std::fopen(path, "a")) {
            std::fprintf(f, "%s %s %s\n", qPrintable(message.member()), qPrintable(message.service()), qPrintable(message.path()));
            std::fclose(f);
        }
    }
    return real(this, message, timeout);
}
