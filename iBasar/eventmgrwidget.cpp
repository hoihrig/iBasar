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

#include "eventmgrwidget.h"
#include "ui_eventmgrwidget.h"

EventMgrWidget::EventMgrWidget(Databaseconnection *data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventMgrWidget)
{
    ui->setupUi(this);

    if (data != 0)
        db = data;

    ui->eventdateedit->setDate(QDate::currentDate());

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(createEventManagerWidget()));
    connect(ui->browselblbtn,SIGNAL(clicked()),this,SLOT(selectLogo()));
}

void EventMgrWidget::createEventManagerWidget()
{
    if (ui->eventnameedit->text().isEmpty())
    {
        QMessageBox::critical(this,tr("iBasar Event Management"),tr("No Event name given. Cannot create Event!"));
        return;
    }

    if (!db->isEstablished())
    {
        QMessageBox::critical(this,tr("iBasar Event Management"),tr("No Connection to Database! Cannot create Event!"));
        return;
    }

    QSqlQuery result;
    QString querycmd;
    int rowid = 0;

    querycmd = "SELECT MAX(ID) FROM `Veranstaltung`";
    db->query(querycmd,result);

    result.next();
    rowid = result.value(0).toInt() + 1;
    result.clear();

    querycmd = "INSERT INTO `Veranstaltung` (ID, Name, Datum, Ort) VALUES (" +
            QString::number(rowid) + ", '" +
            ui->eventnameedit->text() + "', '" +
            ui->eventdateedit->dateTime().toString("yyyy-MM-dd") + "', '" +
            ui->eventLocationlineedit->text() + "');";

    db->query(querycmd,result);


    if (ui->logolineEdit->text().isEmpty()) {
        querycmd = "INSERT INTO `Config` (Veranstaltung, WSymbol, Provision_Verkauft, Provision_NVerkauft) VALUES (" +
                QString::number(rowid) + ", '" +
                ui->currencyLineEdit->text() + "', " +
                ui->provSoldLineEdit->text() + ", " +
                ui->provNSoldLineEdit->text() + ");";

        db->query(querycmd,result);

    }
    else
    {
            QString fileName = ui->logolineEdit->text();

            // load image to bytearray
            QByteArray ba;
            QFile f(fileName);
            if(f.open(QIODevice::ReadOnly))
            {
                ba = f.readAll();
                f.close();
            }

            // Writing the image into table
            QSqlDatabase::database().transaction();
            QSqlQuery query;
            query.prepare( "INSERT INTO `Config` (Veranstaltung, WSymbol, Provision_Verkauft, Provision_NVerkauft, Logo ) VALUES (" +
                           QString::number(rowid) + ", '" +
                           ui->currencyLineEdit->text() + "', " +
                           ui->provSoldLineEdit->text() + ", " +
                           ui->provNSoldLineEdit->text() + ", " +
                           ":IMAGE);");
            query.bindValue(":IMAGE", ba);
            query.exec();
            if( query.lastError().isValid()) {
            qDebug() << query.lastError().text();
            QSqlDatabase::database().rollback();
            } else
            QSqlDatabase::database().commit();

    }

}

void EventMgrWidget::selectLogo()
{
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty())
        ui->logolineEdit->setText(fileName);
}

EventMgrWidget::~EventMgrWidget()
{
    delete ui;
}
