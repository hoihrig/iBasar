/*
#################################################################################################
#   Copyright 2013 Holger Ihrig                                                                 #
#                                                                                               #
#   This file is part of iBasar.                                                                #
#                                                                                               #
#   iBasar is free software: you can redistribute it and/or modify it under the terms of        #
#   the GNU General Public License as published by the Free Software Foundation,                #
#   either version 3 of the License, or (at your option) any later version.                     #
#   Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;         #
#   without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   #
#   See the GNU General Public License for more details.                                        #
#                                                                                               #
#   You should have received a copy of the GNU General Public License along with iBasar.        #
#   If not, see http://www.gnu.org/licenses/.                                                   #
#################################################################################################
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QSettings>
#include <QTranslator>
#include "databaseconnection.h"
#include "settings.h"
#include "mainwidget.h"
#include "eventmgrwidget.h"
#include "sellerregistrationwidget.h"
#include "labelprintwidget.h"
#include "checkoutwidget.h"
#include "languageselectionwidget.h"

namespace Ui {
    class MainWindow;
    class SettingsDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void updateWidgets();

private:
    void connectDb();
    void reconnectDb();

    QSettings *settings;
    Ui::MainWindow *ui;
    Databaseconnection *db;

    QTranslator *translator;

    // Here are all the Widgets loaded by the StackedWidget
    MainWidget *mwidget;
    SellerRegistrationWidget *msellerwidget;
    CheckoutWidget *mcheckoutwidget;
    LanguageSelectionWidget *mlangwidget;

public slots:
    void loadWidget(int index);
    void errorhandling(QString error_msg, QString error_src);
    void setTitle(QString name);
    void changeLanguage(QString language);
private slots:
    void showLanguageSelector();
    void aboutQt();
    void showSettings();
    void showEventManagement();
    void showLabelPrint();
};

#endif // MAINWINDOW_H
