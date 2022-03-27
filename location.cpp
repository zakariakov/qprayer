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


#include "location.h"
#include <iostream>
LocationForm::LocationForm()
{

    db = new Database;

    if (!db->checkDatabase())
    {
        std::cout << "Unable to Read Database File"<< std::endl;
        return;
    }

    if (!db->makeConnection())
    {
        std::cout << "Unable to establish a database connection, this Application needs SQLITE support."<< std::endl;
        return;
    }

}


LocationForm::~LocationForm()
{
    db->closeConnection();
}
void LocationForm::listCountry()
{
    QStringList countryCodeList;

    QStringList countriesList = db->getCountriesList(&countryCodeList);

    for(int i=0;i < countriesList.count();++i)
    {
        QString txt=countriesList.at(i);
        QString name=QString::number(i+1)+" : "+txt;

        // Print -----------------------------------
        std::cout << name.toStdString()<< std::endl;
    }
}

void LocationForm::updateCities(int index)
{

    QStringList citiesList = db->getCitiesList(index);

    for (int i = 0; i < citiesList.count(); ++i) {
        QString txt=citiesList.at(i);

        // Print ----------------------------------
        std::cout << txt.toStdString()<< std::endl;
    }

}

void LocationForm::updateInfo(QString cityName)
{
    QStringList infoList = db->getInfo(cityName);

    if(infoList.size() == 7)
    {
        // QString country="country= "+QString::number(infoList.at(0).toDouble()/10000);
        // longitude="city= "+QString::number(infoList.at(1).toDouble()/10000);
        QString latitude="latitude= "+QString::number(infoList.at(0).toDouble()/10000);
        QString longitude="longitude= "+QString::number(infoList.at(1).toDouble()/10000);
        QString timeZone="timeZone= "+QString::number(infoList.at(2).toDouble()/100);
        QString day=(infoList.at(3).toInt() == 1) ? "true" :"false";
        QString dayLight="dayLight= "+day;
        QString countryName="countryName= "+infoList.at(4);
        QString countryCode="countryCode= "+infoList.at(5);
        QString cityName="cityName= "+infoList.at(6);

         // Print ---------------------------------------
        std::cout << countryName.toStdString() << std::endl;
        std::cout << cityName.toStdString() << std::endl;
        std::cout << countryCode.toStdString() << std::endl;
        std::cout << latitude.toStdString() << std::endl;
        std::cout << longitude.toStdString()<< std::endl;
        std::cout << timeZone.toStdString() << std::endl;
        std::cout << dayLight.toStdString() << std::endl;

    }
}
