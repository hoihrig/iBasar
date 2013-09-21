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

#include "sellerregistrationwidget.h"
#include "ui_sellerregistrationwidget.h"

#include <QFile>

SellerRegistrationWidget::SellerRegistrationWidget(Databaseconnection *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellerRegistrationWidget)
{
    data = db;

    regseller = new Seller;

    ui->setupUi(this);

    // Setup the Table Widget
    addRow();

    updateEvents();

    connect(ui->sellersearchbtn,SIGNAL(clicked()),this,SLOT(searchSeller()));
    connect(ui->selleraddbtn,SIGNAL(clicked()),this,SLOT(createSeller()));
    connect(ui->addRowbtn,SIGNAL(clicked()),this,SLOT(addRow()));
    connect(ui->delRowbtn,SIGNAL(clicked()),this,SLOT(deleteRow()));
    connect(ui->savetblbtn,SIGNAL(clicked()),this,SLOT(saveTabletoDB()));
    connect(ui->sellerresetbtn,SIGNAL(clicked()),this,SLOT(reset()));
    connect(ui->sellerCheckoutbtn,SIGNAL(clicked()),this,SLOT(checkoutSeller()));
}

SellerRegistrationWidget::~SellerRegistrationWidget()
{
    delete regseller;
    delete ui;
}

void SellerRegistrationWidget::reset()
{
    ui->addressedit->clear();
    ui->cityedit->clear();
    ui->emailedit->clear();
    ui->nameedit->clear();
    ui->phoneedit->clear();
    ui->plzedit->clear();
    ui->surnameedit->clear();

    for(int i=ui->tableWidget->rowCount(); i>=0; --i)
    {
        ui->tableWidget->removeRow(i);
    }

}

void SellerRegistrationWidget::updateEvents()
{
    ui->eventComboBox->clear();
    ui->eventComboBox->addItems(findEvents(data));
}

QStringList SellerRegistrationWidget::findEvents(Databaseconnection *db)
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

void SellerRegistrationWidget::updateSellerFields()
{
    if (!regseller->getName().isEmpty())
        ui->nameedit->setText(regseller->getName());

    if (!regseller->getSurname().isEmpty())
        ui->surnameedit->setText(regseller->getSurname());

    if (!regseller->getAddress().isEmpty())
        ui->addressedit->setText(regseller->getAddress());

    if (!regseller->getCity().isEmpty())
        ui->cityedit->setText(regseller->getCity());

    if (!regseller->getPlz().isEmpty())
        ui->plzedit->setText(regseller->getPlz());

    if (!regseller->getEmail().isEmpty())
        ui->emailedit->setText(regseller->getEmail());

    if (!regseller->getPhone().isEmpty())
        ui->phoneedit->setText(regseller->getPhone());

    if (!regseller->getEvent().isEmpty())
        ui->eventComboBox->setCurrentText(regseller->getEvent());

    if (regseller->isComplete())
        ui->tableWidget->setEnabled(true);

}

void SellerRegistrationWidget::searchSeller()
{
    if ((ui->nameedit->text().isEmpty()) || (ui->surnameedit->text().isEmpty()))
    {
        QMessageBox::critical(this,tr("Seller Registration"),tr("To Search you have to specify Name and Surname of the Seller. Cannot search Seller!"));
        return;
    }

    regseller->setName(ui->nameedit->text());
    regseller->setSurname(ui->surnameedit->text());
    regseller->setEvent(ui->eventComboBox->currentText());

    if (!regseller->findSeller(data))
    {
        QMessageBox::critical(this,tr("Seller Registration"),tr("Could not find a Seller with that Name!"));
        return;
    }

    updateSellerFields();

    //delete all rows that are now visible in Table
    for (int i=ui->tableWidget->rowCount() - 1; i >= 0; --i)
        ui->tableWidget->removeRow(i);

    //Now fill the TableWidget with all Items from Seller
    loadSalesItems();

}

bool SellerRegistrationWidget::loadSalesItems()
{
    int numberOfItems = 0;
    QList<int> salesItemList;

    salesItemList = regseller->getSalesItemIDs(data);
    numberOfItems = salesItemList.count();

    for (int i=0; i<numberOfItems; i++)
    {
        SalesItem item;
        if (item.findItem(data, salesItemList.value(i)))
        {
            // Create a Row for each Item and load values of SalesItem
            addRow();

            int row = ui->tableWidget->rowCount() - 1;

            ui->tableWidget->item(row,0)->setText(QString::number(item.getID()));
            ui->tableWidget->item(row,1)->setText(item.getManufacturer());
            ui->tableWidget->item(row,2)->setText(item.getDescription());
            ui->tableWidget->item(row,3)->setText(item.getItemSize());
            ui->tableWidget->item(row,4)->setText(item.getPrice());
            if (item.getSoldStatus())
                ui->tableWidget->item(row,5)->setText("1");
            else
                ui->tableWidget->item(row,5)->setText("0");
        }
    }

    return true;
}

void SellerRegistrationWidget::checkoutSeller()
{
    QList<int> salesItemList;
    SalesItem sitem;

    if ((ui->nameedit->text().isEmpty()) || (ui->surnameedit->text().isEmpty()))
    {
        QMessageBox::critical(this,tr("Seller"),tr("To Search you have to specify Name and Surname of the Seller. Cannot search Seller!"));
        return;
    }

    searchSeller();

    regseller->setName(ui->nameedit->text());
    regseller->setSurname(ui->surnameedit->text());
    regseller->findSeller(data);

    salesItemList = regseller->getSalesItemIDs(data);

    if (salesItemList.count() == 0)
    {
        QMessageBox::critical(this,tr("Seller"),tr("This Seller has either no items or has already checked out!"));
        return;
    }

    printCheckout(salesItemList);

    // Mark sold items as sold and clear all fields
    for (int i=0; i<salesItemList.count(); i++)
    {
        sitem.findItem(data, salesItemList[i]);
        sitem.deleteItem(data);
    }
    reset();
}

QString SellerRegistrationWidget::serializeHeader()
{
    QString header;

    header += ui->nameedit->text() + " ";
    header += ui->surnameedit->text() + ":::";
    header += ui->addressedit->text() + ":::";
    header += ui->plzedit->text() + " ";
    header += ui->cityedit->text() + ":::";

    return header;
}

bool SellerRegistrationWidget::getSelectedEventInfo(Databaseconnection *db)
{
    QSqlQuery result;
    QString querycmd;

    int eventid = 0;

    querycmd = "SELECT * FROM `Veranstaltung` WHERE Name='" + ui->eventComboBox->currentText() + "';";

    db->query(querycmd,result);

    if (result.next())
    {
        eventid = result.value("ID").toInt();
        selectedEventName = result.value("Name").toString();
        selectedEventLocation = result.value("Ort").toString();
        selectedEventDate = result.value("Datum").toString();
    }

    querycmd = "SELECT * FROM `Config` WHERE Veranstaltung=" + QString::number(eventid) + ";";

    db->query(querycmd, result);

    if (result.next())
    {
        soldProvision = result.value("Provision_Verkauft").toString();
        unsoldProvision = result.value("Provision_NVerkauft").toString();
        currencySymbol = result.value("WSymbol").toString();
        logo = result.value("Logo").toByteArray();

        if (!logo.isEmpty())
        {
            QPixmap pic;
            pic.loadFromData(logo);
            pic.save(QString("Logo.png"));
        }

        return true;
    }

    return false;
}

void SellerRegistrationWidget::printCheckout(QList<int> salesItemList)
{
    SellerCheckoutPrinter scprinter;

    QString header;
    QStringList soldlist;
    QStringList unsoldlist;
    SalesItem item;

    header = serializeHeader();
    scprinter.setHeaderInfo(header);


    if(getSelectedEventInfo(data))
    {
        scprinter.setEventName(selectedEventName);
        scprinter.setEventLocation(selectedEventLocation);
        scprinter.setEventDate(selectedEventDate);
        scprinter.setSoldProvision(soldProvision);
        scprinter.setUnSoldProvision(unsoldProvision);
        scprinter.setCurrencySymbol(currencySymbol);

        if (!logo.isEmpty())
            scprinter.setPrintLogo(true);

    }

    // Serialize all the items and put them in a List
    for (int i = 0; i < salesItemList.size(); i++)
    {
        item.findItem(data,salesItemList[i]);
        if (item.getSoldStatus())
            soldlist.append(item.serialize());
        else
            unsoldlist.append(item.serialize());
    }

    if(ui->pdfcheckBox->isChecked())
    {
        scprinter.printPdf(soldlist, unsoldlist);
    }
    else
    {
        scprinter.printPrinter(this, soldlist, unsoldlist);
    }

    // cleanup
    if (!logo.isEmpty())
        QFile::remove("Logo.png");
}

void SellerRegistrationWidget::createSeller()
{
    if ( (ui->nameedit->text().isEmpty()) ||
         (ui->surnameedit->text().isEmpty()) ||
         (ui->addressedit->text().isEmpty()) ||
         (ui->cityedit->text().isEmpty()) ||
         (ui->plzedit->text().isEmpty()) ||
         (ui->emailedit->text().isEmpty()) ||
         (ui->phoneedit->text().isEmpty()) )
    {
        QMessageBox::critical(this,tr("Seller Registration"),tr("One of the required Fields to create a Seller is missing. Cannot create Seller!"));
        return;
    }

    regseller->setName(ui->nameedit->text());
    regseller->setSurname(ui->surnameedit->text());
    regseller->setAddress(ui->addressedit->text());
    regseller->setCity(ui->cityedit->text());
    regseller->setPlz(ui->plzedit->text());
    regseller->setEmail(ui->emailedit->text());
    regseller->setPhone(ui->phoneedit->text());
    regseller->setEvent(ui->eventComboBox->currentText());

    regseller->createSeller(data);

    updateSellerFields();

    //delete all rows that are now visible in Table
    for (int i=0; i < ui->tableWidget->rowCount();i++)
        ui->tableWidget->removeRow(i);
    // Create 4 Rows in Table for new items
    ui->tableWidget->clear();
    for (int i=0; i<4; i++)
        addRow();
}

void SellerRegistrationWidget::addRow()
{
    QStringList headerlist;
    headerlist.append("ID");
    headerlist.append("Hersteller");
    headerlist.append("Beschreibung");
    headerlist.append("Size");
    headerlist.append("Preis");
    headerlist.append("Verkauft");

    ui->tableWidget->setHorizontalHeaderLabels(headerlist);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(2,250);

    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setFlags(item0->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(row, 0, item0);

    QTableWidgetItem *item1 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 1, item1);

    QTableWidgetItem *item2 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 2, item2);

    QTableWidgetItem *item3 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 3, item3);

    QTableWidgetItem *item4 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 4, item4);

    QTableWidgetItem *item5 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 5, item5);
}

void SellerRegistrationWidget::deleteRow()
{
    int row = ui->tableWidget->currentRow();

    if (!ui->tableWidget->item(row,0)->text().isEmpty())
    {
        SalesItem sitem;
        sitem.findItem(data,ui->tableWidget->item(row,0)->text().toInt());
        sitem.deleteItem(data);
    }

    ui->tableWidget->removeRow(row);
}

void SellerRegistrationWidget::saveTabletoDB()
{

    for (int i=0; i<(ui->tableWidget->rowCount());i++)
    {
        // Checking if there is a Manufacturer present. If yes, process row, else ignore
        if (!ui->tableWidget->item(i,1)->text().isEmpty())
        {
            SalesItem sitem;

            sitem.setID(ui->tableWidget->item(i,0)->text());
            sitem.setSellerID(regseller->getID());
            sitem.setManufacturer(ui->tableWidget->item(i,1)->text());
            sitem.setDescription(ui->tableWidget->item(i,2)->text());
            sitem.setItemSize(ui->tableWidget->item(i,3)->text());
            sitem.setPrice(ui->tableWidget->item(i,4)->text());

            if (ui->tableWidget->item(i,5)->text() == "1")
                sitem.setSold(true);
            else
                sitem.setSold(false);

            if (!sitem.saveItem(data))
            {
                QMessageBox::critical(this,tr("Seller Registration"), tr("Could not save Dataset to Database, because of missing field!"));
                return;
            }

            ui->tableWidget->item(i,0)->setText(QString::number(sitem.getID()));

        }

    }

}
