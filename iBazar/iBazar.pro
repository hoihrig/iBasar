#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T20:44:23
#
#-------------------------------------------------

QT       += core gui sql

TARGET = iBazar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databaseconnection.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    databaseconnection.h \
    settings.h

FORMS    += mainwindow.ui \
    settingsdialog.ui
