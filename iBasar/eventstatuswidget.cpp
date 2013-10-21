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

#include "eventstatuswidget.h"
#include "ui_eventstatuswidget.h"

EventStatusWidget::EventStatusWidget(Databaseconnection *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventStatusWidget)
{
    ui->setupUi(this);
    data = db;

    connect(ui->refreshpushbutton,SIGNAL(clicked()),this,SLOT(updateEventStats()));
}

EventStatusWidget::~EventStatusWidget()
{
    delete ui;
}

void EventStatusWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void EventStatusWidget::setDefaultEvent(QString name){

    if (!name.isEmpty())
    {
        defaultEvent = name;
    }
}

QStringList EventStatusWidget::findEvents(Databaseconnection *db)
{
    QStringList eventslist;

    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT Name from `Veranstaltung`";

    db->query(querycmd,result);

    while (result.next())
    {
        eventslist.append(result.value(0).toString());
    }

    return eventslist;
}

int EventStatusWidget::findEventID(QString eventname)
{
    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT ID from `Veranstaltung` WHERE Name='" + eventname + "';";

    data->query(querycmd,result);

    if (result.next())
        return result.value(0).toInt();
    else
        return -1;

}

QStringList EventStatusWidget::findSellersforEvent()
{
    int eventid = 0;
    QStringList sellerlist;
    QSqlQuery result;
    QString querycmd;

    eventid = findEventID(ui->eventComboBox->currentText());

    querycmd = "SELECT ID from `Verkäufer` WHERE Veranstaltung=" + QString::number(eventid) + ";";

    data->query(querycmd, result);

    while (result.next())
        sellerlist.append(result.value(0).toString());

    return sellerlist;
}

void EventStatusWidget::updateSellerStats()
{
    int eventid = 0;
    QSqlQuery result;
    QString querycmd;

    eventid = findEventID(ui->eventComboBox->currentText());

    querycmd = "SELECT COUNT(ID) from `Verkäufer` WHERE Veranstaltung=" + QString::number(eventid) + ";";

    data->query(querycmd, result);

    if (result.next())
        ui->numbersellersresultlabel->setText(result.value(0).toString());
    else
        ui->numbersellersresultlabel->setText(tr("Error"));

}

void EventStatusWidget::updateItemStats()
{
    int eventid = 0;
    int amountItemsTotal = 0;
    int amountItemsSold = 0;
    int amountItemsNSold = 0;
    QStringList sellerlist;
    QSqlQuery result;
    QString querycmd;

    sellerlist = findSellersforEvent();

    for (int i = 0; i < sellerlist.count(); i++)
    {
        // Get Total number of items and add to amountItemsTotal
        querycmd = "SELECT COUNT(ID) from `Artikel` WHERE Verkäufer=" + sellerlist[i] + ";";
        data->query(querycmd, result);
        if (result.next())
            amountItemsTotal += result.value(0).toInt();

        // Get Total number of sold items and add to amountItemsSold
        querycmd = "SELECT COUNT(ID) from `Artikel` WHERE Verkäufer=" + sellerlist[i] + " AND Verkauft=1;";
        data->query(querycmd, result);
        if (result.next())
            amountItemsSold += result.value(0).toInt();

        // Get Total number of unsold items and add to amountItemsNSold
        querycmd = "SELECT COUNT(ID) from `Artikel` WHERE Verkäufer=" + sellerlist[i] + " AND Verkauft=0;";
        data->query(querycmd, result);
        if (result.next())
            amountItemsNSold += result.value(0).toInt();

    }

    ui->numberitemsresultlabel->setText(QString::number(amountItemsTotal));
    ui->numbersolditemsresultlabel->setText(QString::number(amountItemsSold));
    ui->numberunsolditemsresultlabel->setText(QString::number(amountItemsNSold));

}

void EventStatusWidget::updateAvailableEvents()
{
    ui->eventComboBox->clear();
    ui->eventComboBox->addItems(findEvents(data));

    if (!defaultEvent.isEmpty())
    {
        int eventid = ui->eventComboBox->findText(defaultEvent);

        if (eventid >= 0)
            ui->eventComboBox->setCurrentIndex(eventid);
    }

}

void EventStatusWidget::updateEventStats()
{
    QString oldevent = ui->eventComboBox->currentText();
    updateAvailableEvents();
    ui->eventComboBox->setCurrentText(oldevent);
    updateItemStats();
    updateSellerStats();

}
