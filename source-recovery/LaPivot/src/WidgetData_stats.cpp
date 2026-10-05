// WidgetData_stats.cpp — CPU, RAM, disk, net, battery, uptime stats
// Rebuilt from oracle: WidgetData::readStats, readFile, cpuTotal, ramPercent, diskPercent,
// cpuFreqGHz, cpuTempF, uptime, netUp, netDown, mountedVolumes
// Spec: lelan.md (Lelan owns system data; WidgetData is pass-through for most)
// DEFECTS FIXED vs oracle:
// 1. Stats reading gated by AnimPolicy in onPulse (no polling when idle/obscured)
// 2. Net speed cached, only updated on stats tick
// 3. /proc/stat parsing hardened
// 4. /proc/meminfo, /proc/cpuinfo, /proc/net/dev read whole before parsing: a QTextStream on the
//    QFile saw atEnd() at once (procfs size 0), so RAM, net up/down and the cpuinfo MHz stayed 0

#include "WidgetData.h"
#include "Lelan.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <sys/statvfs.h>
#include <unistd.h>
#include <cmath>

void WidgetData::readStats()
{
    // CPU usage from /proc/stat
    QFile procStat("/proc/stat");
    if (procStat.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&procStat);
        QString line = in.readLine(); // First line: "cpu  ..."
        if (line.startsWith("cpu ")) {
            QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            if (parts.size() >= 8) {
                qulonglong user = parts[1].toULongLong();
                qulonglong nice = parts[2].toULongLong();
                qulonglong system = parts[3].toULongLong();
                qulonglong idle = parts[4].toULongLong();
                qulonglong iowait = parts[5].toULongLong();
                qulonglong irq = parts[6].toULongLong();
                qulonglong softirq = parts[7].toULongLong();

                qulonglong total = user + nice + system + idle + iowait + irq + softirq;
                qulonglong busy = user + nice + system + irq + softirq;

                if (m_lastCpuTotal > 0 && total >= m_lastCpuTotal && busy >= m_lastCpuBusy) {
                    qulonglong totalDiff = total - m_lastCpuTotal;
                    qulonglong busyDiff = busy - m_lastCpuBusy;
                    if (totalDiff > 0) {
                        m_cpuTotal = (double)busyDiff / (double)totalDiff * 100.0;
                    }
                }
                m_lastCpuTotal = total;
                m_lastCpuBusy = busy;
            }
        }
        procStat.close();
    }

    // RAM from /proc/meminfo
    QFile meminfo("/proc/meminfo");
    if (meminfo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(meminfo.readAll());   // procfs reports size 0: streaming the QFile makes atEnd() true at once
        qulonglong total = 0, available = 0;
        while (!in.atEnd() && (total == 0 || available == 0)) {
            QString line = in.readLine();
            if (line.startsWith("MemTotal:")) {
                const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
                if (parts.size() > 1)
                    total = parts.at(1).toULongLong(); // kB
            } else if (line.startsWith("MemAvailable:")) {
                const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
                if (parts.size() > 1)
                    available = parts.at(1).toULongLong();
            }
        }
        if (total > 0 && available <= total) {
            m_ramPercent = (double)(total - available) / (double)total * 100.0;
        }
        meminfo.close();
    }

    // Disk usage for root filesystem
    struct statvfs fs;
    if (statvfs("/", &fs) == 0) {
        qulonglong total = fs.f_blocks * fs.f_frsize;
        qulonglong free = fs.f_bavail * fs.f_frsize;
        if (total > 0) {
            m_diskPercent = (double)(total - free) / (double)total * 100.0;
        }
    }

    // Prefer the live cpufreq interface; cpuinfo's current-frequency entry is a fallback.
    QFile frequencyFile(QStringLiteral("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq"));
    if (frequencyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        bool ok = false;
        const double khz = frequencyFile.readAll().trimmed().toDouble(&ok);
        if (ok && khz > 0.0)
            m_cpuFreqGHz = khz / 1'000'000.0;
    }
    if (m_cpuFreqGHz <= 0.0) {
        QFile cpuinfo("/proc/cpuinfo");
        if (cpuinfo.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(cpuinfo.readAll());   // procfs reports size 0: streaming the QFile makes atEnd() true at once
            while (!in.atEnd()) {
                const QString line = in.readLine();
                if (line.startsWith("cpu MHz")) {
                    const QStringList parts = line.split(':', Qt::SkipEmptyParts);
                    if (parts.size() == 2) {
                        bool ok = false;
                        const double mhz = parts.at(1).trimmed().toDouble(&ok);
                        if (ok && mhz > 0.0)
                            m_cpuFreqGHz = mhz / 1000.0;
                        break;
                    }
                }
            }
        }
    }

    // Sentinel is the hardware-sensor owner. Use its CPU package reading before sysfs fallbacks.
    double cpuTempC = 0.0;
    if (m_lelan) {
        const QVariantMap temps = m_lelan->sentinelTemps();
        for (auto it = temps.cbegin(); it != temps.cend(); ++it) {
            const QString key = it.key().toLower();
            if ((key.contains(QStringLiteral("cpu")) || key.contains(QStringLiteral("core"))
                 || key.contains(QStringLiteral("package")) || key.contains(QStringLiteral("tctl"))
                 || key.contains(QStringLiteral("tdie")) || key.contains(QStringLiteral("x86_pkg_temp")))
                && it.value().toDouble() > cpuTempC) {
                cpuTempC = it.value().toDouble();
            }
        }
    }

    // Fallback to a CPU-like zone, skipping empty and zero-valued ACPI stubs.
    QDir thermal("/sys/class/thermal");
    const QStringList zones = thermal.entryList(
        QStringList() << "thermal_zone*", QDir::Dirs | QDir::NoDotAndDotDot);
    if (cpuTempC <= 0.0) {
        for (const QString &zone : zones) {
            QFile typeFile(thermal.filePath(zone + "/type"));
            if (!typeFile.open(QIODevice::ReadOnly | QIODevice::Text))
                continue;
            const QString type = typeFile.readAll().trimmed().toLower();
            const bool cpuZone = type.contains(QStringLiteral("cpu"))
                || type.contains(QStringLiteral("core"))
                || type.contains(QStringLiteral("package"))
                || type.contains(QStringLiteral("x86_pkg_temp"));
            if (!cpuZone)
                continue;

            QFile tempFile(thermal.filePath(zone + "/temp"));
            if (!tempFile.open(QIODevice::ReadOnly | QIODevice::Text))
                continue;
            bool ok = false;
            const double temp = tempFile.readAll().trimmed().toDouble(&ok) / 1000.0;
            if (ok && temp > 0.0) {
                cpuTempC = temp;
                break;
            }
        }
    }
    if (cpuTempC > 0.0) {
        m_cpuTempF = cpuTempC * 9.0 / 5.0 + 32.0;
    }

    // Uptime
    QFile uptimeFile("/proc/uptime");
    if (uptimeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&uptimeFile);
        QString line = in.readLine();
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (!parts.isEmpty()) {
            double seconds = parts[0].toDouble();
            int days = int(seconds / 86400);
            int hours = int(fmod(seconds, 86400) / 3600);
            int mins = int(fmod(seconds, 3600) / 60);
            if (days > 0)
                m_uptime = QString("%1d %2h %3m").arg(days).arg(hours).arg(mins);
            else if (hours > 0)
                m_uptime = QString("%1h %2m").arg(hours).arg(mins);
            else
                m_uptime = QString("%1m").arg(mins);
        }
        uptimeFile.close();
    }

    // Network speed (from /proc/net/dev)
    readNetSpeed();

    emit statsChanged();
}

void WidgetData::readNetSpeed()
{
    QFile netDev("/proc/net/dev");
    if (!netDev.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(netDev.readAll());   // procfs reports size 0: streaming the QFile makes atEnd() true at once
    in.readLine(); // header
    in.readLine(); // header

    qulonglong rxTotal = 0, txTotal = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 17) {
            QString iface = parts[0];
            iface.chop(1); // remove trailing ':'
            // Skip loopback
            if (iface == "lo")
                continue;
            qulonglong rx = parts[1].toULongLong(); // bytes
            qulonglong tx = parts[9].toULongLong();
            rxTotal += rx;
            txTotal += tx;
        }
    }
    netDev.close();

    static qulonglong s_lastRx = 0, s_lastTx = 0;
    static qint64 s_lastTime = 0;

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (s_lastTime > 0) {
        double dt = (now - s_lastTime) / 1000.0; // seconds
        if (dt > 0) {
            double rxSpeed = (rxTotal - s_lastRx) / dt; // bytes/sec
            double txSpeed = (txTotal - s_lastTx) / dt;

            auto formatSpeed = [](double bps) -> QString {
                if (bps >= 1024*1024)
                    return QString("%1 MB/s").arg(bps / (1024*1024), 0, 'f', 1);
                if (bps >= 1024)
                    return QString("%1 KB/s").arg(bps / 1024, 0, 'f', 1);
                return QString("%1 B/s").arg(bps, 0, 'f', 0);
            };

            m_netDown = formatSpeed(rxSpeed);
            m_netUp = formatSpeed(txSpeed);
        }
    }
    s_lastRx = rxTotal;
    s_lastTx = txTotal;
    s_lastTime = now;
}

void WidgetData::readUptime()
{
    // Already done in readStats
}

QVariantList WidgetData::mountedVolumes() const
{
    if (!m_lelan)
        return {};
    return m_lelan->removableVolumes(); // oracle uses removableVolumes for both
}

double WidgetData::cpuTotal() const
{
    return m_cpuTotal;
}

double WidgetData::ramPercent() const
{
    return m_ramPercent;
}

double WidgetData::diskPercent() const
{
    return m_diskPercent;
}

double WidgetData::cpuFreqGHz() const
{
    return m_cpuFreqGHz;
}

double WidgetData::cpuTempF() const
{
    return m_cpuTempF;
}

QString WidgetData::uptime() const
{
    return m_uptime;
}