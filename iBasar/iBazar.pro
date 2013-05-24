#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T20:44:23
#
#-------------------------------------------------

QT       += core gui sql widgets

TARGET = iBazar
TEMPLATE = app

CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

qtlibs.path = $$DESTDIR
qtlibs.files =  $$[QT_INSTALL_BINS]/*.dll
qtlibs.CONFIG = no_check_exist

drivers.path = $$DESTDIR/plugins/sqldrivers
drivers.files += sqldrivers/*

INSTALLS += drivers qtlibs


SOURCES += main.cpp\
        mainwindow.cpp \
    databaseconnection.cpp \
    settings.cpp \
    mainwidget.cpp \
    eventmgrwidget.cpp \
    sellerregistrationwidget.cpp \
    seller.cpp \
    salesitem.cpp \
    labelprintwidget.cpp

HEADERS  += mainwindow.h \
    databaseconnection.h \
    settings.h \
    mainwidget.h \
    eventmgrwidget.h \
    sellerregistrationwidget.h \
    seller.h \
    salesitem.h \
    labelprintwidget.h

FORMS    += \
    settingsdialog.ui \
    mainwindow.ui \
    mainwidget.ui \
    eventmgrwidget.ui \
    sellerregistrationwidget.ui \
    labelprintwidget.ui


