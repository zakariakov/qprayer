# qprayer
Display Prayer Times in Terminal

### Dependencies:

- qt5

### Install

git clone https://github.com/zakariakov/qprayer.git

cd qprayer

qmake

make

sudo make install

### Help

Usage: qprayer [OPTION]
    OPTION:
     -h  --help                 Print this help.
     --country                  List country.
     --city     <country num>   List city by country num
     --info     <city name>     Get informations by city name
     -f                         Get Fajr prayer time.
     -s                         Get Sunrise time.
     -d                         Get Dhuhr prayer time.
     -a                         Get Asr prayer time.
     -m                         Get Maghrib prayer time.
     -i                         Get Ishaa prayer time.
     -p                         Get elapsed from previous prayer time.
     -n                         Get remaining to next prayer time.
     -N                         Get next prayer Name.
     -Na                        Get next prayer Name in arabic.
    
step 1

	cp /etc/xdg/qprayer/qprayer.conf ~/.config/qprayer/qprayer.conf
  
step 2

	qprayer --contry //copy your country id
	
step 3

	qprayer --city <id> //copy your city name
	
step 4

	qprayer  --info <city-name>
	copy result in ~/.config/qprayer/qprayer.conf file
	
		
    
