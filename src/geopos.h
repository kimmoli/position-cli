#include <QGeoCoordinate>
#include <QGeoPositionInfoSource>
#include <QCoreApplication>
#include <QDebug>
#include <stdio.h>

class Geopos : public QObject
{
    Q_OBJECT
public:
    explicit Geopos(bool repeat = false, bool verbose = true, QString selectedSource = QString(), QObject *parent = 0);


private slots:
    void positionUpdated(const QGeoPositionInfo &info);

private:
    bool m_repeat;
    bool m_verbose;

};
