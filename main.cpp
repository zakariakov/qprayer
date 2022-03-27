/***************************************************************************
 *   elokab Copyright (C) 2014 AbouZakaria <yahiaui@gmail.com>             *
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
#include<stdio.h>
#include <QCoreApplication>
#include  "prayer.h"
#include <QDebug>
#include <QDir>
#include <QTextStream>
void helpMe()
{
    printf("Usage: qprayer [OPTION]\n");
    puts("OPTION:\n");
    puts(" -h  --help                 Print this help.\n");
    puts(" --country                  List country.\n");
    puts(" --city     <country num>   List city by country num\n");
    puts(" --info     <city name>     Get informations by city name\n");
    puts(" -f                         Get Fajr prayer time.\n");
    puts(" -s                         Get Sunrise time.\n");
    puts(" -d                         Get Dhuhr prayer time.\n");
    puts(" -a                         Get Asr prayer time.\n");
    puts(" -m                         Get Maghrib prayer time.\n");
    puts(" -i                         Get Ishaa prayer time.\n");
    puts(" -p                         Get elapsed from previous prayer time.\n");
    puts(" -n                         Get remaining to next prayer time.\n");
    puts(" -N                         Get next prayer Name.\n");
    puts(" -Na                        Get next prayer Name in arabic.\n");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("qprayer");
    a.setApplicationVersion("0.1");
    a.setOrganizationName("qprayer");
    prayer w;
    QStringList args = a.arguments();
    if(args.count()>1){
        for(int i = 0; i < args.count(); ++i){

            QString arg = args.at(i);
            // List country
            if (arg == "-h" || arg == "--help" ) {helpMe();return 0; }
            //
            else if (arg == "--country") {w.getCountry();}
            // List cities from contry num
            else if (arg == "--city") {
                if(i+1>args.count()-1){helpMe();return 0;}
                QString name=args.at(i+1);
                int num =name.toInt();
                w.getCities(num);
            }
            // list information from city name
            else if (arg == "--info") {
                if(i+1>args.count()-1){helpMe();return 0;}
                QString name=args.at(i+1);
                w.getInfo(name);
            }
            //  Fajr
            else if (arg == "-f")  {w.getIprayerTime(0); }
            //  Sunrise
            else if (arg == "-s") {w.getIprayerTime(1); }
            //  Dhuhr
            else if (arg == "-d") {w.getIprayerTime(2); }
            //  Asr
            else if (arg == "-a") {w.getIprayerTime(3); }
            //  Maghrib
            else if (arg == "-m") {w.getIprayerTime(4); }
            //  Ishaa
            else if (arg == "-i") {w.getIprayerTime(5); }
            //  elapsed from previous
            else if (arg == "-p") {w.elapsedToPrevPrayer(); }
            //  remaining to next
            else if (arg == "-n") {w.remainingToNextPrayer();}
            // next prayer name
            else if (arg == "-N") {w.nextPrayerName();}
            // next prayer name in arabic
            else if (arg == "-Na") {w.nextPrayerName(true);}
        }
    }else {
        w.getAllPrayerTime();
    }

    // Fajr  |Sunrise| Dhuhr |  Asr  |Maghrib| Ishaa

    return 0;
}
