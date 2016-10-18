#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T07:36:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab3WineGui
TEMPLATE = app

QTPLUGIN += QSQLMYSQL

SOURCES += main.cpp\
        mainwindow.cpp \
    wineProcess.cpp

HEADERS  += mainwindow.h \
    wineProcess.h

FORMS    += mainwindow.ui
