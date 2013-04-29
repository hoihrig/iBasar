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

#ifndef SELLERREGISTRATIONWIDGET_H
#define SELLERREGISTRATIONWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "databaseconnection.h"
#include "seller.h"
#include "salesitem.h"

namespace Ui {
class SellerRegistrationWidget;
}

class SellerRegistrationWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SellerRegistrationWidget(Databaseconnection *db, QWidget *parent = 0);
    ~SellerRegistrationWidget();
    
private:
    Ui::SellerRegistrationWidget *ui;
    Databaseconnection *data;
    Seller *regseller;

    QStringList findEvents(Databaseconnection *db);
    bool loadSalesItems();

private slots:
    void updateSellerFields();
    void searchSeller();
    void createSeller();
    void addRow();
    void deleteRow();
    void saveTabletoDB();
};

#endif // SELLERREGISTRATIONWIDGET_H
