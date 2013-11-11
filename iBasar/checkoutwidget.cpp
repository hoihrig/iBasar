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

#include "checkoutwidget.h"
#include "ui_checkoutwidget.h"

#include <QFile>

CheckoutWidget::CheckoutWidget(Databaseconnection *db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckoutWidget)
{

    data = db;
    pdf = false;

    ui->setupUi(this);

    ui->itemnumbertextbox->setFocus();

    updateEvents();
    setTableHeader();

    connect(ui->itemnumbertextbox,SIGNAL(textChanged(QString)),this,SLOT(itemNumberTextChanged(QString)));
    connect(ui->itemnumbertextbox,SIGNAL(returnPressed()),this,SLOT(itemNumberReturnPressed()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(reset()));
    connect(ui->checkoutButton,SIGNAL(clicked()),this,SLOT(checkout()));
    connect(ui->checkoutPdfButton,SIGNAL(clicked()),this,SLOT(checkoutPdf()));

}

CheckoutWidget::~CheckoutWidget()
{
    delete ui;
}

void CheckoutWidget::setDefaultEvent(QString name){

    if (!name.isEmpty())
    {
        defaultEvent = name;

        reset();
    }
}

void CheckoutWidget::checkoutPdf()
{
    pdf = true;
    checkout();
}

void CheckoutWidget::checkout()
{
    bool retval = false;
    SalesItem sitem;

    retval = validatefields();

    if(retval == false)
    {
        QMessageBox::critical(this,tr("Checkout Window"),
                              tr("Could not validate all input fields. Please make "
                                 "sure that all fields are filled."),QMessageBox::Ok);
        return;
    }

    printCheckout();

    // Mark sold items as sold and clear all fields
    for (int i=0; i<salesItemList.count(); i++)
    {
        sitem.findItem(data, salesItemList[i]);
        sitem.setSold(true);
    }
    reset();

}


void CheckoutWidget::itemNumberReturnPressed()
{
    if(ui->itemnumbertextbox->text().size() == 12)
    {
        processItem(ui->itemnumbertextbox->text());
    }
    else
    {
        QString prodnr = QString("%1").arg(ui->itemnumbertextbox->text(), 12, QChar('0')).toUpper();
        processItem(prodnr);
    }
}

void CheckoutWidget::getFocus()
{
    ui->itemnumbertextbox->setFocus();
}


void CheckoutWidget::reset()
{
    ui->nameedit->clear();
    ui->surnameedit->clear();
    ui->addressedit->clear();
    ui->cityedit->clear();
    ui->itemnumbertextbox->clear();
    ui->plzedit->clear();
    ui->totalpricelabel->setText(QString("0 €"));

    for(int i=ui->tableWidget->rowCount(); i>=0; --i)
    {
        ui->tableWidget->removeRow(i);
    }

    salesItemList.clear();
}

void CheckoutWidget::itemNumberTextChanged(QString itemnumber)
{
    if(itemnumber.size() == 12)
        processItem(itemnumber);
}

bool CheckoutWidget::itemExistsInCurrentEvent(QString itemnumber)
{
    QSqlQuery result;
    QString querycmd;
    QString eventid;

    querycmd = "SELECT ID from `Veranstaltung` WHERE Name='" + ui->eventComboBox->currentText() +"';";

    data->query(querycmd,result);

    if(result.next())
        eventid = result.value(0).toString();
    else
        return false;


    querycmd = "SELECT a.ID FROM `Verkäufer` a, `Artikel` b WHERE a.Veranstaltung=" + eventid + " AND a.ID=b.Verkäufer AND b.ID=" + itemnumber + ";";

    data->query(querycmd,result);

    if (result.next())
        return true;
    else
        return false;

}

void CheckoutWidget::processItem(QString itemnumber)
{
    SalesItem item;

    if(!itemExistsInCurrentEvent(itemnumber))
    {
        QMessageBox::critical(this,tr("CheckoutWidget"), tr("This Item does not exist for the currently selected Event"));
        return;
    }

    if (item.findItem(data, itemnumber.toInt()))
    {
        // Create a Row for each Item and load values of SalesItem
        addRow();

        int row = ui->tableWidget->rowCount() - 1;

        ui->tableWidget->item(row,0)->setText(QString::number(item.getID()));
        ui->tableWidget->item(row,1)->setText(item.getManufacturer());
        ui->tableWidget->item(row,2)->setText(item.getDescription());
        ui->tableWidget->item(row,3)->setText(item.getItemSize());
        ui->tableWidget->item(row,4)->setText(item.getPrice());

        salesItemList.append(item.getID());

        ui->totalpricelabel->setText(QString::number(calculateTotalPrice()) + " €");

        ui->itemnumbertextbox->clear();
    }
}

float CheckoutWidget::calculateTotalPrice()
{
    float totalPrice = 0.0;
    int tablesize = ui->tableWidget->rowCount();

    for(int i=0; i < tablesize; i++)
    {
        totalPrice += ui->tableWidget->item(i,4)->text().toFloat();
    }
    return totalPrice;
}

bool CheckoutWidget::validatefields()
{
    if(ui->addressedit->text().isEmpty() ||
            ui->cityedit->text().isEmpty() ||
            ui->nameedit->text().isEmpty() ||
            ui->surnameedit->text().isEmpty() ||
            ui->plzedit->text().isEmpty())
        headerPresent = false;
    else
        headerPresent = true;


    if((ui->tableWidget->rowCount() == 0))
        return false;

    return true;
}

QStringList CheckoutWidget::findEvents(Databaseconnection *db)
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

bool CheckoutWidget::getSelectedEventInfo(Databaseconnection *db)
{
    QSqlQuery result;
    QString querycmd;


    querycmd = "SELECT * FROM `Veranstaltung` WHERE Name='" + ui->eventComboBox->currentText() + "';";

    db->query(querycmd,result);

    if (!result.next())
        return false;


    selectedEventName = result.value("Name").toString();
    selectedEventLocation = result.value("Ort").toString();
    selectedEventDate = result.value("Datum").toString();

    QString eventid = result.value("ID").toString();

    querycmd = "SELECT LOGO, Logo_Format, Veranstalter FROM `Config` WHERE Veranstaltung=" + eventid + ";";

    db->query(querycmd,result);

    if (result.next()) {
        selectedLogo = result.value(0).toByteArray();
        logoName = QString("logo.") + result.value(1).toString().toLower();
        selectedOrganizer = result.value(2).toString();

        QPixmap pic;
        pic.loadFromData(selectedLogo);
        pic.save(logoName);
    }

    return true;
}

void CheckoutWidget::updateEvents()
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

void CheckoutWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void CheckoutWidget::printCheckout()
{
    BillPrinter bprinter;

    QString header;
    QStringList serializedlist;
    SalesItem item;

    if (headerPresent)
    {
        header = serializeHeader();
        bprinter.setHeaderInfo(header);
    }

    if(getSelectedEventInfo(data))
    {
        bprinter.setEventName(selectedEventName);
        bprinter.setEventLocation(selectedEventLocation);
        bprinter.setEventDate(selectedEventDate);
        bprinter.setOrganizerName(selectedOrganizer);

        if (!selectedLogo.isEmpty())
        {
            bprinter.setPrintLogo(logoName);
        }
    }

    // Serialize all the items and put them in a List
    for (int i = 0; i < salesItemList.size(); i++)
    {

        item.findItem(data,salesItemList[i]);
        item.setSold(true);
        item.updateItem(data);
        serializedlist.append(item.serialize());

    }

    if(pdf)
    {
        bprinter.printPdf(serializedlist);
        pdf = false;
    }
    else
    {
        bprinter.printPrinter(this,serializedlist);
    }

    //cleanup
    if (!selectedLogo.isEmpty())
    {
        QFile file(logoName);
        file.remove();
    }
}

QString CheckoutWidget::serializeHeader()
{
    QString header;

    header += ui->nameedit->text() + " ";
    header += ui->surnameedit->text() + ":::";
    header += ui->addressedit->text() + ":::";
    header += ui->plzedit->text() + " ";
    header += ui->cityedit->text() + ":::";

    return header;
}

void CheckoutWidget::setTableHeader()
{
    QStringList headerlist;
    headerlist.append("ID");
    headerlist.append("Hersteller");
    headerlist.append("Beschreibung");
    headerlist.append("Size");
    headerlist.append("Preis");

    ui->tableWidget->setHorizontalHeaderLabels(headerlist);
    ui->tableWidget->setColumnWidth(2,250);
}

void CheckoutWidget::addRow()
{
    setTableHeader();

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
