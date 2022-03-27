#ifndef PRAYER_H
#define PRAYER_H
//#include "prayertimes.hpp"
#include "location.h"
#include <QObject>
#include <QTime>
#include <QDate>
#include <QVariant>
class prayer : public QObject
{
    Q_OBJECT
public:
    explicit prayer(QObject *parent = nullptr);

signals:

public slots:

    void getAllPrayerTime();
    void remainingToNextPrayer(bool arg=false);
    void nextPrayerName(bool ara=false);
    void elapsedToPrevPrayer(bool arg=false);
    void getIprayerTime(int p);
    void getCountry();
    void getCities(int name);
    void getInfo(const QString &city);
private slots:
     void calculatePrayerTime();
     void nextPrayer();


private:
    QString m_country;
    QString m_city;
    QString m_resourceDir;
    double m_longitude;
    double m_latitude;
    double m_timeZone;
    int m_calcMethod;
    int m_asrJuristic;
    int m_highLat;
    bool m_dayLight;
    int m_countryNumber;
    int m_cityNumber;
    int m_calcMethodIndex;
    int m_asrJuristicIndex;
    int m_highLatIndex;
    QDate m_today;
    QTime m_time;
    QList<QTime> m_prayerTimeList;
    QStringList m_prayerNameList;

    QString m_nextPrayerName;
    QString m_previousPrayerName;
    QTime m_nextPrayerTime;
    QTime m_previousPrayerTime;
     QList<QVariant> m_prayersToShowList;
     QTime m_remainingTime;
    QTime m_lastTimeSeen;
 LocationForm *mLocationForm;
};

#endif // PRAYER_H
