#include <stdio.h>
#include <QCommandLineParser>
#include <QDebug>
#include <QCoreApplication>
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

    parser.parse(QCoreApplication::arguments());

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

    const QStringList args = parser.positionalArguments();

    Geopos geopos(parser.isSet(repeatOption), parser.isSet(verboseOption));

    return app.exec();
}

