#-------------------------------------------------
#
# Project created by QtCreator 2014-01-22T15:15:18
#
#-------------------------------------------------


QT       += core  sql
#sql dbus
#greaterThan(QT_MAJOR_VERSION, 4): QT +=widgets


TEMPLATE = app
TARGET = qprayer
DESTDIR = ../usr/bin

CONFIG += qt \
          release
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
INCLUDEPATH +=build

SOURCES += main.cpp\
    database.cpp \
    location.cpp \
    prayer.cpp



HEADERS  += \
    prayer.h \
    prayertimes.hpp \
    database.h \
    location.h \



#INSTALL Linux
 target.path = /usr/bin
 data.files=../usr/share/*
 data.path=/usr/share
 xdg.files=../etc/xdg/*
 xdg.path=/etc/xdg

 INSTALLS +=    target \
                data \
                xdg
