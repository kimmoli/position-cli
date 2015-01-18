#include <stdio.h>
#include <QCommandLineParser>
#include <QDebug>
#include <QCoreApplication>
#include <QGeoPositionInfoSource>

#include "geopos.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("position");
    QCoreApplication::setApplicationVersion(APPVERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription("commandline position tool");

    const QCommandLineOption helpOption = parser.addHelpOption();

    QCommandLineOption versionOption("version", "Show application version");
    parser.addOption(versionOption);
    QCommandLineOption repeatOption(QStringList() << "r" << "repeat", "Repeatedly update position");
    parser.addOption(repeatOption);
    QCommandLineOption verboseOption(QStringList() << "v" << "verbose", "Print some more text");
    parser.addOption(verboseOption);
    QCommandLineOption listOption(QStringList() << "list", "Show list of available sources");
    parser.addOption(listOption);
    QCommandLineOption sourceOption(QStringList() << "s" << "source", "Set positioning source", "source");
    parser.addOption(sourceOption);

    parser.parse(QCoreApplication::arguments());

    QString selectedSource = QString();

    if (parser.isSet(helpOption))
    {
        parser.showHelp();
        return 0;
    }

    if (parser.isSet(versionOption))
    {
        printf("%s %s\n", qPrintable(QCoreApplication::applicationName()),
               qPrintable(QCoreApplication::applicationVersion()));
        return 0;
    }

    if (parser.isSet(listOption))
    {
        QStringList sources = QGeoPositionInfoSource::availableSources();
        foreach (const QString &source, sources)
        {
            printf("  %s\n", qPrintable(source));
        }
        return 0;
    }

    if (parser.isSet(sourceOption))
    {
        const QString source = parser.value(sourceOption);
        QStringList sources = QGeoPositionInfoSource::availableSources();
        if (sources.contains(source))
            selectedSource = source;
        else
        {
            printf("Invalid source %s\n", qPrintable(source));
            return 1;
        }
    }

    const QStringList args = parser.positionalArguments();

    Geopos geopos(parser.isSet(repeatOption), parser.isSet(verboseOption), selectedSource);

    return app.exec();
}

