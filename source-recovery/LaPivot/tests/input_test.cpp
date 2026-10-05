// input_test — Settings_input.cpp. xinput is only QUERIED on this machine (list, read-only); applying goes to a
// recorder with canned list-props answers; settings.ini is written in a scratch HOME.
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QRegularExpression>
#include <cstdio>

#define private public
#include "Lelan.h"
#include "Settings.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;
Settings::Settings(QObject *parent) : QObject(parent) {}
Settings::~Settings() = default;

static int g_fails = 0;
static void check(bool ok, const QString &what) { if (!ok) ++g_fails; std::printf("%s %s\n", ok ? "PASS" : "FAIL", qPrintable(what)); }

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    std::setvbuf(stdout, nullptr, _IOLBF, 0);
    QProcess q; q.start("xinput", {"list"}); q.waitForFinished();
    const QString realList = QString::fromUtf8(q.readAllStandardOutput());
    const auto ptrs = Settings::parsePointers(realList);
    QStringList names; for (const auto &p : ptrs) names << p.second + "#" + p.first;
    std::printf("  pointers: %s\n", qPrintable(names.join(" | ")));
    check(names.filter("Touchpad").size() == 1 && names.filter("Wireless Mouse").size() == 1
          && names.filter("keyboard", Qt::CaseInsensitive).isEmpty() && names.filter("Virtual core").isEmpty()
          && names.filter("Power Button").isEmpty(), "real xinput: touchpad + mice only, no keyboards / buttons / virtual core (N2)");

    Settings s;
    QStringList log;
    s.runDetached = [&](const QString &p, const QStringList &a) { log << p + " " + a.join(' '); };
    s.runInput = [&](const QString &p, const QStringList &a, const QByteArray &in) { log << p + " " + a.join(' ') + " <<" + QString::fromUtf8(in).trimmed().replace('\n', ';'); };
    s.runQuery = [&](const QString &p, const QStringList &a, std::function<void(const QString &)> done) {
        if (a.value(0) == "list") { done(realList); return; }
        // canned: the touchpad has everything, mice have accel + natural scroll only
        const bool tp = names.filter("Touchpad#" + a.value(1)).size();
        done(QString("libinput Accel Speed (300):\t0.0\nlibinput Natural Scrolling Enabled (301):\t0\n")
             + (tp ? "libinput Tapping Enabled (302):\t1\nlibinput Disable While Typing Enabled (303):\t1\n" : ""));
    };
    s.m_kbRepeatDelay = 250; s.m_kbRepeatRate = 40; s.m_pointerSpeed = 75; s.m_touchpadSpeed = 25;
    s.m_naturalScroll = true; s.m_tapToClick = true; s.m_disableWhileTyping = false; s.m_cursorSize = 48;
    s.applyInput();
    for (const QString &l : log) std::printf("  %s\n", qPrintable(l));
    QString tpId; for (const auto &p : ptrs) if (p.second.contains("Touchpad")) tpId = p.first;
    check(log.contains("xset r rate 250 40"), "key repeat: xset r rate 250 40");
    check(log.contains("xinput set-prop " + tpId + " libinput Accel Speed -0.5"), "touchpad speed 25 -> accel -0.5");
    check(log.filter("Accel Speed 0.5").size() == int(ptrs.size()) - 1, "every other pointer: speed 75 -> accel 0.5");
    check(log.filter("Tapping Enabled 1").size() == 1 && log.filter("Disable While Typing Enabled 0").size() == 1,
          "tap / disable-while-typing only where the device has them (touchpad)");
    check(log.filter("Natural Scrolling Enabled 1").size() == int(ptrs.size()), "natural scroll on every pointer");
    check(log.filter("set-prop").filter(QRegularExpression("set-prop (\\d+) ")).size() == log.filter("set-prop").size(), "set-prop only on listed pointer ids");
    check(log.contains("xrdb -merge <<Xcursor.theme: Kith;Xcursor.size: 48") && log.contains("gsettings set org.gnome.desktop.interface cursor-size 48"),
          "cursor size 48: xrdb + gsettings");

    // settings.ini keeps other keys
    const QString ini = QDir::homePath() + "/.config/gtk-3.0/settings.ini";
    QDir().mkpath(QDir::homePath() + "/.config/gtk-3.0");
    { QFile f(ini); f.open(QIODevice::WriteOnly); f.write("[Settings]\ngtk-theme-name=NCDE\ngtk-cursor-theme-size=24\ngtk-font-name=Cormorant 11\n"); }
    s.applyCursorSize();
    QFile f(ini); f.open(QIODevice::ReadOnly); const QString t = QString::fromUtf8(f.readAll());
    check(t.contains("gtk-theme-name=NCDE") && t.contains("gtk-font-name=Cormorant 11") && t.contains("gtk-cursor-theme-size=48")
          && t.contains("gtk-cursor-theme-name=Kith") && t.count("gtk-cursor-theme-size") == 1, "GTK 3 settings.ini: size replaced, name added, other keys kept");
    std::printf("RESULT %s\n", g_fails ? "FAIL" : "PASS");
    return g_fails ? 1 : 0;
}
