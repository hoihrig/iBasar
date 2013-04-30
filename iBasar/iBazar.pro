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
drivers.files += sqldrivers/*.dll

INSTALLS += drivers qtlibs


win32: QMAKE_POST_LINK = copy $${QMAKE_LIBDIR_QT}\Qt*.dll ..\bin

SOURCES += main.cpp\
        mainwindow.cpp \
    databaseconnection.cpp \
    settings.cpp \
    mainwidget.cpp \
    eventmgrwidget.cpp \
    sellerregistrationwidget.cpp \
    seller.cpp \
    salesitem.cpp

HEADERS  += mainwindow.h \
    databaseconnection.h \
    settings.h \
    mainwidget.h \
    eventmgrwidget.h \
    sellerregistrationwidget.h \
    seller.h \
    salesitem.h

FORMS    += \
    settingsdialog.ui \
    mainwindow.ui \
    mainwidget.ui \
    eventmgrwidget.ui \
    sellerregistrationwidget.ui



win32: LIBS += -lQt5Widgetsd

win32: LIBS += -lqsqlmysqld
