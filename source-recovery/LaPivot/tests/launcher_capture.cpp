#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QJsonArray args;
    for (int i = 1; i < argc; ++i)
        args.append(QString::fromLocal8Bit(argv[i]));

    QJsonObject result;
    result.insert(QStringLiteral("args"), args);
    result.insert(QStringLiteral("pid"), QCoreApplication::applicationPid());

    QFile output(QString::fromLocal8Bit(qgetenv("NCDE_TEST_OUTPUT")));
    if (!output.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return 1;
    output.write(QJsonDocument(result).toJson(QJsonDocument::Compact));
    output.close();
    return 0;
}
