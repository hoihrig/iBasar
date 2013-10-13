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

#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(Databaseconnection *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidget)
{
    ui->setupUi(this);
    data = db;

    updateValues();

    connect(ui->eventcomboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateTitle(QString)));
    connect(ui->eventcomboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateEventDetails(QString)));

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::updateTitle(QString name)
{
    defaultEvent = name;

    emit eventChanged(name);
}

void MainWidget::updateDbStatus()
{
    ui->dblbl->setText(data->getHostname());

    if (data->isEstablished())
        ui->connectlbl->setText("true");
    else
        ui->connectlbl->setText("false");
}

void MainWidget::updateItemStatus()
{
    QSqlQuery query;

    data->query("Select COUNT(ID) from `Artikel`",query);
    query.next();
    ui->itemslbl->setText(query.value(0).toString());
    query.clear();

    data->query("Select COUNT(ID) from `Verkäufer`",query);
    query.next();
    ui->sellerslbl->setText(query.value(0).toString());
    query.clear();

    data->query("Select COUNT(ID) from `Veranstaltung`",query);
    query.next();
    ui->eventslbl->setText(query.value(0).toString());

}

void MainWidget::updateEvents()
{


    QStringList eventslist;

    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT ID, Name from `Veranstaltung`";

    data->query(querycmd,result);

    while (result.next())
    {
        eventslist.append(result.value(1).toString());
    }

    if (eventslist.count() != ui->eventcomboBox->count())
    {
        ui->eventcomboBox->clear();
        ui->eventcomboBox->addItems(eventslist);

        updateTitle(ui->eventcomboBox->currentText());
    }


    if (!defaultEvent.isEmpty())
    {
        int eventid = ui->eventcomboBox->findText(defaultEvent);

        if (eventid >= 0)
            ui->eventcomboBox->setCurrentText(defaultEvent);
    }
}

void MainWidget::updateEventDetails(QString name)
{
    QSqlQuery result;
    QString querycmd;
    int eventid;

    querycmd = "SELECT ID from `Veranstaltung` WHERE Name='" + name + "';";

    data->query(querycmd, result);

    if (result.next())
            eventid = result.value(0).toInt();
    else
        return;


    querycmd = "SELECT * from `Config` WHERE Veranstaltung=" + QString::number(eventid) + ";";

    data->query(querycmd,result);

    if (result.next())
    {
        ui->provisionSoldresultlabel->setText(result.value("Provision_Verkauft").toString());

        ui->provisionNotSoldresultlabel->setText(result.value("Provision_NVerkauft").toString());

        ui->currencySymbolresultlabel->setText(result.value("WSymbol").toString());

        QByteArray temp;

        temp = result.value("Logo").toByteArray();

        if (temp.size() > 0)
            ui->logoresultlabel->setText("true");
        else
            ui->logoresultlabel->setText("false");
    }

}

void MainWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void MainWidget::updateValues()
{
    updateDbStatus();

    updateItemStatus();

    updateEvents();

    updateEventDetails(ui->eventcomboBox->currentText());

}
