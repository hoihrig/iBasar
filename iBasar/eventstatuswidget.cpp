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

    provision_sold = 0;
    provision_nsold = 0;
    currencysymbol = QString("€");

    data = db;

    connect(ui->refreshpushbutton,SIGNAL(clicked()),this,SLOT(updateEventStats()));
    connect(ui->endEventPushButton,SIGNAL(clicked()),this,SLOT(createReport()));
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

        updateEventStats();
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

void EventStatusWidget::readEventConfig()
{
    int eventid = 0;
    QSqlQuery result;
    QString querycmd;

    eventid = findEventID(ui->eventComboBox->currentText());

    querycmd = "SELECT Provision_Verkauft, Provision_NVerkauft, WSymbol, Logo, Logo_Format from `Config` WHERE Veranstaltung=" + QString::number(eventid) + ";";

    data->query(querycmd,result);

    if (result.next())
    {
        provision_sold = result.value(0).toFloat();
        provision_nsold = result.value(1).toFloat();
        currencysymbol = result.value(2).toString();

        QByteArray selectedLogo;
        selectedLogo = result.value(3).toByteArray();
        logoName = QString("logo.") + result.value(4).toString().toLower();

        QPixmap pic;
        pic.loadFromData(selectedLogo);
        pic.save(logoName);
    }
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

int EventStatusWidget::findActiveSellersforEvent()
{
    int eventid = 0;
    QSqlQuery result;
    QString querycmd;

    eventid = findEventID(ui->eventComboBox->currentText());

    querycmd = "SELECT COUNT(ID) from `Verkäufer` WHERE Veranstaltung=" + QString::number(eventid) + " AND Aktiv=1;";

    data->query(querycmd, result);

    if (result.next())
        return result.value(0).toInt();
    else
        return 0;
}

int EventStatusWidget::findInactiveSellersforEvent()
{
    int eventid = 0;
    QSqlQuery result;
    QString querycmd;

    eventid = findEventID(ui->eventComboBox->currentText());

    querycmd = "SELECT COUNT(ID) from `Verkäufer` WHERE Veranstaltung=" + QString::number(eventid) + " AND Aktiv=0;";

    data->query(querycmd, result);

    if (result.next())
        return result.value(0).toInt();
    else
        return 0;
}

void EventStatusWidget::updateSellerStats()
{
    int activesellers = 0;
    int inactivesellers = 0;
    int allsellers = 0;

    activesellers = findActiveSellersforEvent();
    inactivesellers = findInactiveSellersforEvent();

    allsellers = activesellers + inactivesellers;

    ui->numbersellersresultlabel->setText(QString::number(allsellers));
    ui->selleractiveresultlabel->setText(QString::number(activesellers));
    ui->sellercheckedoutresultlabel->setText(QString::number(inactivesellers));


}

void EventStatusWidget::updateItemStats()
{
    int amountItemsTotal = 0;
    int amountItemsSold = 0;
    int amountItemsNSold = 0;
    float valueItemsTotal = 0;
    float valueItemsSold = 0;
    float provision_soldItems = 0;
    float provision_nsoldItems = 0;
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

    valueItemsTotal = getTotalValueItemsbyEvent();
    valueItemsSold = getTotalValueSoldItemsbyEvent();
    provision_soldItems = (valueItemsSold * provision_sold) / 100;
    provision_nsoldItems = amountItemsNSold * provision_nsold;


    ui->numberitemsresultlabel->setText(QString::number(amountItemsTotal));
    ui->numbersolditemsresultlabel->setText(QString::number(amountItemsSold));
    ui->numberunsolditemsresultlabel->setText(QString::number(amountItemsNSold));
    ui->totalvalueresultlabel->setText(QString::number(valueItemsTotal) + " " + currencysymbol);
    ui->totalsoldresultlabel->setText(QString::number(valueItemsSold) + " " + currencysymbol);
    ui->totalprovisionresultlabel->setText(QString::number(provision_soldItems) + " " + currencysymbol);
    ui->totalprovisionnotsoldresultlabel->setText(QString::number(provision_nsoldItems) + " " + currencysymbol);

}

QString EventStatusWidget::serialize()
{
    QString temp;

    temp = ui->numbersellersresultlabel->text() + ":::";
    temp += ui->numberitemsresultlabel->text() + ":::";
    temp += ui->numbersolditemsresultlabel->text() + ":::";
    temp += ui->numberunsolditemsresultlabel->text() + ":::";
    temp += ui->totalsoldresultlabel->text() + ":::";
    temp += ui->totalprovisionresultlabel->text() + ":::";
    temp += ui->totalprovisionnotsoldresultlabel->text() + ":::";
    temp += ui->payoutresultlabel->text() + ":::";
    temp += ui->revenueresultlabel->text();

    return temp;
}

float EventStatusWidget::getTotalValueItemsbyEvent()
{
    int eventid = 0;
    QSqlQuery result;
    QString querycmd;

    eventid = findEventID(ui->eventComboBox->currentText());

    querycmd = "SELECT SUM(b.Preis) FROM `Verkäufer` a, `Artikel` b WHERE a.Veranstaltung=" + QString::number(eventid) + " AND b.Verkäufer=a.ID;";

    data->query(querycmd, result);

    if (result.next())
        return result.value(0).toFloat();
    else
        return 0;

}

float EventStatusWidget::getTotalValueSoldItemsbyEvent()
{
    int eventid = 0;
    QSqlQuery result;
    QString querycmd;

    eventid = findEventID(ui->eventComboBox->currentText());

    querycmd = "SELECT SUM(b.Preis) FROM `Verkäufer` a, `Artikel` b WHERE a.Veranstaltung=" +
            QString::number(eventid) + " AND b.Verkäufer=a.ID AND b.Verkauft=1;";

    data->query(querycmd, result);

    if (result.next())
        return result.value(0).toFloat();
    else
        return 0;

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

void EventStatusWidget::updateEventSummary()
{
    float revenue = 0;
    float payout = 0;

    revenue = ui->totalprovisionresultlabel->text().split(" ").at(0).toFloat() + ui->totalprovisionnotsoldresultlabel->text().split(" ").at(0).toFloat();

    payout = ui->totalsoldresultlabel->text().split(" ").at(0).toFloat() - revenue;

    ui->payoutresultlabel->setText(QString::number(payout) + " " + currencysymbol);
    ui->revenueresultlabel->setText(QString::number(revenue) + " " + currencysymbol);

}

void EventStatusWidget::updateEventStats()
{
    QString oldevent = ui->eventComboBox->currentText();
    updateAvailableEvents();
    ui->eventComboBox->setCurrentText(oldevent);

    readEventConfig();

    updateItemStats();
    updateSellerStats();

    updateEventSummary();

}

void EventStatusWidget::createReport()
{
    EventRevenuePrinter revprinter;
    QString serializedData;

    revprinter.setCurrencySymbol(currencysymbol);
    revprinter.setEventName(ui->eventComboBox->currentText());
    revprinter.setProvisionSold(QString::number(provision_sold));
    revprinter.setProvisionNotSold(QString::number(provision_nsold));

    if(!logoName.isEmpty())
        revprinter.setPrintLogo(logoName);

    serializedData = serialize();

    if(ui->pdfcheckBox->isChecked())
        revprinter.printPdf(serializedData);
    else
        revprinter.printPrinter(this,serializedData);

    //cleanup
    if (!logoName.isEmpty())
    {
        QFile file(logoName);
        file.remove();
    }

}
