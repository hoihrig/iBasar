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

SellerRegistrationWidget::SellerRegistrationWidget(Databaseconnection *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellerRegistrationWidget)
{
    data = db;

    regseller = new Seller;

    ui->setupUi(this);

    // Setup the Table Widget
    addRow();

    ui->eventComboBox->addItems(findEvents(db));

    connect(ui->sellersearchbtn,SIGNAL(clicked()),this,SLOT(searchSeller()));
    connect(ui->selleraddbtn,SIGNAL(clicked()),this,SLOT(createSeller()));
    connect(ui->addRowbtn,SIGNAL(clicked()),this,SLOT(addRow()));
    connect(ui->delRowbtn,SIGNAL(clicked()),this,SLOT(deleteRow()));
    connect(ui->savetblbtn,SIGNAL(clicked()),this,SLOT(saveTabletoDB()));
}

SellerRegistrationWidget::~SellerRegistrationWidget()
{
    delete regseller;
    delete ui;
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
        if (item.loadItem(data, salesItemList.value(i)))
        {
            // Create a Row for each Item and load values of SalesItem
            addRow();

            int row = ui->tableWidget->rowCount() - 1;

            ui->tableWidget->item(row,0)->setText(QString::number(item.getID()));
            ui->tableWidget->item(row,1)->setText(item.getManufacturer());
            ui->tableWidget->item(row,2)->setText(item.getDescription());
            ui->tableWidget->item(row,3)->setText(item.getItemSize());
            ui->tableWidget->item(row,4)->setText(item.getPrice());
        }
    }

    return true;
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

    ui->tableWidget->setHorizontalHeaderLabels(headerlist);
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
}

void SellerRegistrationWidget::deleteRow()
{
    int row = ui->tableWidget->currentRow();

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

            if (!sitem.saveItem(data))
            {
                QMessageBox::critical(this,tr("Seller Registration"), tr("Could not save Dataset to Database, because of missing field!"));
                return;
            }

            ui->tableWidget->item(i,0)->setText(QString::number(sitem.getID()));

        }

    }

}
