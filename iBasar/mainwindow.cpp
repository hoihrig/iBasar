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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new QSettings("Ibasar","Ibasar");
    db = new Databaseconnection();
    translator = new QTranslator();

    db->readDbSettings(settings);

    db->open();

    changeLanguage("Deutsch");

    mwidget = new MainWidget(db);
    msellerwidget = new SellerRegistrationWidget(db);
    mcheckoutwidget = new CheckoutWidget(db);
    mlangwidget = new LanguageSelectionWidget();

    mwidget->setGeometry(ui->stackedWidget->geometry());
    ui->stackedWidget->addWidget(mwidget);


    msellerwidget->setGeometry(ui->stackedWidget->geometry());
    ui->stackedWidget->addWidget(msellerwidget);

    mcheckoutwidget->setGeometry(ui->stackedWidget->geometry());
    ui->stackedWidget->addWidget(mcheckoutwidget);

    ui->toolBox->setCurrentIndex(0);


    connect(ui->actionAbout_Qt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(ui->actionSettings,SIGNAL(triggered()),this,SLOT(showSettings()));
    connect(ui->toolBox,SIGNAL(currentChanged(int)),this,SLOT(loadWidget(int)));
    connect(ui->actionEvent_Manager,SIGNAL(triggered()),this,SLOT(showEventManagement()));
    connect(ui->actionPrint_Labels,SIGNAL(triggered()),this,SLOT(showLabelPrint()));
    connect(ui->actionSelectLanguage,SIGNAL(triggered()),this,SLOT(showLanguageSelector()));
    connect(this,SIGNAL(updateWidgets()),mwidget,SLOT(updateValues()));
    connect(this,SIGNAL(updateWidgets()),mcheckoutwidget,SLOT(getFocus()));
    connect(this,SIGNAL(updateWidgets()),mcheckoutwidget,SLOT(updateEvents()));
    connect(this,SIGNAL(updateWidgets()),msellerwidget,SLOT(updateEvents()));
    connect(db,SIGNAL(db_error(QString,QString)),this,SLOT(errorhandling(QString,QString)));
    connect(mwidget,SIGNAL(eventChanged(QString)),this,SLOT(setTitle(QString)));
    connect(mwidget,SIGNAL(eventChanged(QString)),mcheckoutwidget,SLOT(setDefaultEvent(QString)));
    connect(mwidget,SIGNAL(eventChanged(QString)),msellerwidget,SLOT(setDefaultEvent(QString)));
    connect(mlangwidget,SIGNAL(languageChanged(QString)),this,SLOT(changeLanguage(QString)));


    emit updateWidgets();
}

MainWindow::~MainWindow()
{
    delete db;
    delete mwidget;
    delete msellerwidget;
    delete mcheckoutwidget;
    delete mlangwidget;
    delete translator;

    delete ui;
}

void MainWindow::loadWidget(int index)
{
    emit updateWidgets();

    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::setTitle(QString name)
{
    this->setWindowTitle(QString("iBazar - ") + name);
}

void MainWindow::changeLanguage(QString language)
{
    if (language == QString("Deutsch"))
        translator->load("ibasar_de");

    if (language == QString("English"))
        translator->load("ibasar_en");

    qApp->installTranslator(translator);

    ui->retranslateUi(this);

}

void MainWindow::showSettings()
{
    Settings sett(settings);

    sett.exec();

    reconnectDb();
    emit updateWidgets();
}

void MainWindow::showEventManagement()
{
    EventMgrWidget eventmgmt(db);

    eventmgmt.exec();

    emit updateWidgets();
}

void MainWindow::showLabelPrint()
{
    LabelPrintWidget labelprint(db);

    labelprint.exec();

    emit updateWidgets();
}

void MainWindow::showLanguageSelector()
{
    mlangwidget->exec();
}

void MainWindow::reconnectDb()
{
    if (db)
    {
        if (db->isEstablished())
            db->close();

        db->readDbSettings(settings);

        if (!db->open())
            qWarning("Could not Open Database, either the credentials are wrong or the Driver is not properly installed");
    }
}

void MainWindow::connectDb()
{
    if (db)
    {
        if (!db->isEstablished())
            if (!db->open())
                qWarning("Could not Open Database, either the credentials are wrong or the Driver is not properly installed");
    }
    else
    {
        qWarning("Database Object does not exist yet!");
    }
}

void MainWindow::errorhandling(QString error_msg, QString error_src)
{
    QMessageBox::critical(this, error_src, error_msg);
}

void MainWindow::aboutQt()
{
    QApplication::aboutQt();
}
