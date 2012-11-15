#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T20:44:23
#
#-------------------------------------------------

QT       += core gui sql widgets

TARGET = iBazar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databaseconnection.cpp \
    settings.cpp \
    mainwidget.cpp \
    fakeui.cpp \
    eventmgrwidget.cpp \
    sellerregistrationwidget.cpp \
    seller.cpp \
    salesitem.cpp

HEADERS  += mainwindow.h \
    databaseconnection.h \
    settings.h \
    mainwidget.h \
    fakeui.h \
    eventmgrwidget.h \
    sellerregistrationwidget.h \
    seller.h \
    salesitem.h

FORMS    += \
    settingsdialog.ui \
    mainwindow.ui \
    mainwidget.ui \
    fakeui.ui \
    eventmgrwidget.ui \
    sellerregistrationwidget.ui
