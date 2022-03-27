/***************************************************************************
 *   Copyright (C) 2010-2011 by Amine Roukh     <amineroukh@gmail.com>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>

//#include "ui_locationform.h"
//#include "manualcalc.h"
#include "database.h"
#include "prayertimes.hpp"

class LocationForm : public QObject
{
    Q_OBJECT
public:
    LocationForm();
    
~LocationForm();
   // void saveSettings();
    

signals:
  void  accepteChange();
public slots:
    void listCountry();
    void updateCities(int countryNo);
    void updateInfo(QString cityName);
private slots:

    //double longitude() const;
   // double latitude() const;
   // double timeZone() const;
   // int calcMethodIndex() const;
    //int calcMethod() const;
    //int asrJuristicIndex() const;
   // int asrJuristic() const;
    //int highLatIndex() const;
    //int highLat() const;
    //int countryNumber() const;
    //int cityNumber() const;
    //bool dayLight() const;
    //QString country() const;
   // QString city() const;
    //QStringList manualTimeList() const;
   // QList<bool> fixedTimeList() const;
   // bool manualCalculation() const;

//  QPixmap getPixmapForCountryCode(const QString & countryCode);
 //QString  getTranslation(const QString & countryCode, const QString &countryName);


  // void manualCalcForm();


  // void loadSettings();

  //  void on_buttonBox_clicked(QAbstractButton *button);

private:
QString m_resourceDir;
    QStringList m_manualTimeList;
    QList<bool> m_fixedTimeList;
    bool m_manualCalculation;
    
   // Ui::LocationForm m_locationUi;
   // ManualCalcForm *m_manualCalc;
    Database *db;
};


#endif
