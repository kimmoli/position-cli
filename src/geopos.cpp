#include "geopos.h"


Geopos::Geopos(bool repeat, bool verbose, QString selectedSource, QObject *parent) :
    QObject(parent)
{
    m_repeat = repeat;
    m_verbose = verbose;

    QGeoPositionInfoSource *source;

    if (selectedSource.isEmpty())
        source = QGeoPositionInfoSource::createDefaultSource(this);
    else
        source = QGeoPositionInfoSource::createSource(selectedSource, this);

    if (source)
    {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->setUpdateInterval(1000);
        source->startUpdates();
        if (m_verbose)
            printf("acquired source %s\n", qPrintable(source->sourceName()));
    }
    else
    {
        printf("failed to acquire source\n");
        QCoreApplication::quit();
    }
}

void Geopos::positionUpdated(const QGeoPositionInfo &info)
{
    if (m_verbose)
    {
        printf("timestamp %s\n", qPrintable(info.timestamp().toString()));
        printf("latitude %f\n", info.coordinate().latitude());
        printf("longitude %f\n", info.coordinate().longitude());
    }
    else
    {
        printf("%s %f %f\n", qPrintable(info.timestamp().toString()),
                                info.coordinate().latitude(),
                                info.coordinate().longitude());
    }

    if (!m_repeat)
        QCoreApplication::quit();
}
