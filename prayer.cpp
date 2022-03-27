#include "prayer.h"
#include <QSettings>
//#include <QDir>
#include <QCoreApplication>

#include <iostream>
prayer::prayer(QObject *parent) : QObject(parent)
{
    m_today = QDate::currentDate();

    m_time = QTime::currentTime();
    m_prayerNameList << tr("Fajr") << tr("Sunrise") << tr("Dhuhr")
                     << tr("Asr") << tr("Maghrib") << tr("Ishaa");
    for(int i=0; i<6; i++)
    {
        m_prayerTimeList << QTime(0, 0, 0);
    }

    QSettings cg("qprayer","qprayer");
    cg.sync();
    cg.beginGroup("Adhan");

    m_latitude = cg.value("latitude", 36.7728).toDouble();
    m_longitude = cg.value("longitude", 3.0603).toDouble();
    m_timeZone = cg.value("timezone", 1.0).toDouble();
    m_calcMethod = cg.value("calcMethod", static_cast<int>(PrayerTimes::Makkah)).toInt();
    m_asrJuristic = cg.value("asrJuristic", static_cast<int>(PrayerTimes::Shafii)).toInt();
    m_highLat = cg.value("highLat", static_cast<int>(PrayerTimes::MidNight)).toInt();
    m_dayLight = cg.value("daylight", false).toBool();
    m_prayersToShowList << true << true << true
                        << true << true << true;

    cg.endGroup();

    calculatePrayerTime();

    nextPrayer();
    //getAllPrayerTime();
    //getIprayerTime(1);
    //remainingToNextPrayer();
    //getCountry();

}

void prayer::calculatePrayerTime()
{
    double times[PrayerTimes::TimesCount];

    PrayerTimes prayerTimes(static_cast<PrayerTimes::CalculationMethod>(m_calcMethod),
                            static_cast<PrayerTimes::JuristicMethod>(m_asrJuristic),
                            static_cast<PrayerTimes::AdjustingMethod>(m_highLat)
                            );
    prayerTimes.get_prayer_times(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day(),
                                 m_latitude, m_longitude, m_timeZone, m_dayLight, times);

    for(int i=0, j=0; i < PrayerTimes::TimesCount; ++i)
    {
        if(i != PrayerTimes::Sunset) // Skip Sunset
        {
            m_prayerTimeList.replace(j, QTime::fromString(QString::fromStdString(PrayerTimes::float_time_to_time24(times[i])), "hh:mm:ss"));
            j++;
        }
    }

}


/****************************************
  ******** next |prev |time| name *******
  ***************************************/
void prayer::nextPrayer()
{

    QTime currentTime = m_time;
    m_nextPrayerName = m_prayerNameList.at(0);
    m_nextPrayerTime = m_prayerTimeList.at(0);
    m_previousPrayerName = m_prayerNameList.at(5);
    m_previousPrayerTime = m_prayerTimeList.at(5);

    int i;
    for(i=0; i<6; i++)
    {
        if(currentTime < m_prayerTimeList.at(i) && m_prayersToShowList.at(i).toBool())
        {
            m_nextPrayerName = m_prayerNameList.at(i);
            m_nextPrayerTime = m_prayerTimeList.at(i);
            break;
        }
    }

    if(i)
    {
//        if(i!=2)
//        {
            m_previousPrayerName = m_prayerNameList.at(i-1);
            m_previousPrayerTime = m_prayerTimeList.at(i-1);
       // }

//        else // Avoid Sunrise case
//        {
//            m_previousPrayerName = m_prayerNameList.at(i-2);
//            m_previousPrayerTime = m_prayerTimeList.at(i-2);
//        }
    }
}

/****************************************
  *********** prayer info table *********
  ***************************************/
void prayer::getAllPrayerTime()
{

    QString clockFormat = "hh:mm";

    // terminal colors
    QString   Ye="\e[1;34m";
    QString   NO="\e[1;0m";

    QString F=NO+m_prayerTimeList.at(0).toString(clockFormat)+Ye;
    QString S=NO+m_prayerTimeList.at(1).toString(clockFormat)+Ye;
    QString D=NO+m_prayerTimeList.at(2).toString(clockFormat)+Ye;
    QString A=NO+m_prayerTimeList.at(3).toString(clockFormat)+Ye;
    QString M=NO+m_prayerTimeList.at(4).toString(clockFormat)+Ye;
    QString I=NO+m_prayerTimeList.at(5).toString(clockFormat)+Ye;

    QString name=QCoreApplication::applicationName()+" Version: "
            +QCoreApplication::applicationVersion()+"\n";

    // Print
    std::cout << name.toStdString()<< std::endl;

    QString line1=(Ye+"+-----------------------------------------------+");
    QString line2=(   "| Fajr  |Sunrise| Dhuhr |  Asr  |Maghrib| Ishaa |");
    QString line3=(   "+-------+-------+-------+-------+-------+-------+");
    QString line4=(   "| "+F+" | "+S+" | "+D+" | "+A+" | "+M+" | "+I+" |");
    QString line5=(   "+-----------------------------------------------+"+NO);

    // Print
    std::cout << line1.toStdString()<< std::endl;
    std::cout << line2.toStdString()<< std::endl;
    std::cout << line3.toStdString()<< std::endl;
    std::cout << line4.toStdString()<< std::endl;
    std::cout << line5.toStdString()<< std::endl;
    elapsedToPrevPrayer(true);
    remainingToNextPrayer(true);
}

/****************************************
  *********** Prev prayer time **********
  ***************************************/
void prayer::elapsedToPrevPrayer(bool arg)
{
    QTime currentTime = m_time;
    QTime elapsedTime =  QTime(0, 0, 0);
    elapsedTime = elapsedTime.addSecs(m_previousPrayerTime.secsTo(currentTime));
    if(arg){
        QString name=elapsedTime.toString("hh:mm:ss")+QString(" from %1")
                .arg(m_previousPrayerName);
        // Print
        std::cout << name.toStdString()<< std::endl;
    }else{
        QString name=elapsedTime.toString("hh:mm:ss");
        // Print
        std::cout << name.toStdString()<< std::endl;
    }
}

/****************************************
  *********** Next prayer time **********
  ***************************************/
void prayer::remainingToNextPrayer(bool arg)
{

    nextPrayer();
    m_time = QTime::currentTime();

    m_remainingTime = QTime(0, 0, 0);
    m_remainingTime = m_remainingTime.addSecs(m_time.secsTo(m_nextPrayerTime)+1);
    if(arg){
        QString name= m_remainingTime.toString("hh:mm:ss")
                +QString(" to %1").arg(m_nextPrayerName);
        // Print
        std::cout << name.toStdString()<< std::endl;
    }else{
       // QString name;
       // if(m_remainingTime.hour() == 0)
       //    name=m_remainingTime.toString("mm:ss");
       // else if(m_remainingTime.hour() > 0)
       //     name=m_remainingTime.toString("hh:mm");
       // else
         QString name=m_remainingTime.toString("hh:mm");

        // Print
        std::cout << name.toStdString()<< std::endl;
    }
}

/****************************************
  ************ Next prayer Name *********
  ***************************************/
void prayer::nextPrayerName(bool ara)
{
    QString name=m_nextPrayerName;
    if(ara){
             if(m_nextPrayerName=="Fajr") name="الفجر";
        else if(m_nextPrayerName=="Sunrise") name="الشروق";
        else if(m_nextPrayerName=="Dhuhr") name="الظهر";
        else if(m_nextPrayerName=="Asr") name="العصر";
        else if(m_nextPrayerName=="Maghrib") name="المغرب";
        else if(m_nextPrayerName=="Ishaa") name="العشاء";
    }

    std::cout << name.toStdString() << std::endl;

}

/****************************************
  ********* prayer time from p name *****
  ***************************************/
void prayer::getIprayerTime(int p)
{

    if(p<0 || p>5) return;
    QString name=QString("%1").arg(m_prayerTimeList.at(p).toString("hh:mm") );

    std::cout << name.toStdString() << std::endl;

}

/****************************************
  ************ get Country Id ***********
  ***************************************/
void prayer::getCountry()
{
    mLocationForm=new LocationForm;
    mLocationForm->listCountry();
}

/****************************************
  ************ get city name ************
  ***************************************/
void prayer::getCities(int name)
{
    mLocationForm=new LocationForm;
    mLocationForm->updateCities(name);
}

/****************************************
  ****** get info from city name ********
  ***************************************/
void prayer::getInfo(const QString &city)
{
    mLocationForm=new LocationForm;
    mLocationForm->updateInfo(city);
}
