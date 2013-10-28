#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T20:44:23
#
#-------------------------------------------------

QT       += core gui sql widgets printsupport

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

TRANSLATIONS = ibasar_de.ts \
                ibasar_en.ts


SOURCES += main.cpp\
        mainwindow.cpp \
    databaseconnection.cpp \
    settings.cpp \
    mainwidget.cpp \
    eventmgrwidget.cpp \
    sellerregistrationwidget.cpp \
    seller.cpp \
    salesitem.cpp \
    labelprintwidget.cpp \
    itemprinter.cpp \
    ean13.cpp \
    checkoutwidget.cpp \
    billprinter.cpp \
    sellercheckoutprinter.cpp \
    comboboxitemdelegate.cpp \
    sellersearchwidget.cpp \
    languageselectionwidget.cpp \
    eventstatuswidget.cpp \
    eventrevenueprinter.cpp

HEADERS  += mainwindow.h \
    databaseconnection.h \
    settings.h \
    mainwidget.h \
    eventmgrwidget.h \
    sellerregistrationwidget.h \
    seller.h \
    salesitem.h \
    labelprintwidget.h \
    itemprinter.h \
    ean13.h \
    checkoutwidget.h \
    billprinter.h \
    sellercheckoutprinter.h \
    comboboxitemdelegate.h \
    sellersearchwidget.h \
    languageselectionwidget.h \
    eventstatuswidget.h \
    eventrevenueprinter.h

FORMS    += \
    settingsdialog.ui \
    mainwindow.ui \
    mainwidget.ui \
    eventmgrwidget.ui \
    sellerregistrationwidget.ui \
    labelprintwidget.ui \
    checkoutwidget.ui \
    sellersearchwidget.ui \
    languageselectionwidget.ui \
    eventstatuswidget.ui


