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

#include "sellersearchwidget.h"
#include "ui_sellersearchwidget.h"

#include <QMessageBox>

SellerSearchWidget::SellerSearchWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellerSearchWidget)
{
    ui->setupUi(this);

    connect(ui->cancelbtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->idsearchrbtn,SIGNAL(toggled(bool)),ui->idlineedit,SLOT(setEnabled(bool)));
    connect(ui->namerbtn,SIGNAL(toggled(bool)),ui->namelineedit,SLOT(setEnabled(bool)));
    connect(ui->namerbtn,SIGNAL(toggled(bool)),ui->surnamelineedit,SLOT(setEnabled(bool)));
    connect(ui->searchbtn,SIGNAL(clicked()),this,SLOT(search()));
}

SellerSearchWidget::~SellerSearchWidget()
{
    delete ui;
}

void SellerSearchWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void SellerSearchWidget::search()
{
    if (ui->idsearchrbtn->isChecked())
    {
        if (ui->idlineedit->text().isEmpty()) {
            QMessageBox::critical(this,tr("Seller Search"),tr("Um einen Verkäufer zu suchen eine Kundennummer eingegeben werden!"));
            return;
        }
        else {
            emit searchbyID(ui->idlineedit->text().toInt());
        }
    }

    if (ui->namerbtn->isChecked()) {

        if (ui->namelineedit->text().isEmpty()
                || ui->surnamelineedit->text().isEmpty()) {
            QMessageBox::critical(this,tr("Seller Search"),tr("Um einen Verkäufer zu suchen müssen Vorname und Nachname eingegeben werden!"));
            return;
        }
        else {
            emit searchbyName(ui->surnamelineedit->text() + ", " + ui->namelineedit->text());
        }

    }

    ui->idlineedit->clear();
    ui->surnamelineedit->clear();
    ui->namelineedit->clear();

    this->close();
}
