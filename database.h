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


#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDir>
#include <QString>

class Database
{
public:
    Database();

    bool checkDatabase();
    bool makeConnection();
    void closeConnection();
    QStringList getCountriesList(QStringList *countryCodeList);
    QStringList getCitiesList(int countyNo);
    QStringList getInfo(QString cityName);
    void getcountryName(int countryNo);

private:
    
    QSqlDatabase db;
    QFile dbFilePath;
        QStringList infoList;
};

#endif
