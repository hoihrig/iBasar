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

#ifndef CHECKOUTWIDGET_H
#define CHECKOUTWIDGET_H

#include <QWidget>
#include "databaseconnection.h"
#include "salesitem.h"
#include "billprinter.h"

namespace Ui {
class CheckoutWidget;
}

class CheckoutWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CheckoutWidget(Databaseconnection *db, QWidget *parent = 0);
    ~CheckoutWidget();
    



    void setTableHeader();
public slots:
    void itemNumberTextChanged(QString itemnumber);
    void itemNumberReturnPressed();
    void getFocus();
    void reset();
    void checkout();
    void checkoutPdf();
    void updateEvents();

private:
    Ui::CheckoutWidget *ui;
    Databaseconnection *data;
    QList<int> salesItemList;
    QString selectedEventName;
    QString selectedEventLocation;
    QString selectedEventDate;

    void addRow();
    void processItem(QString itemnumber);
    void printCheckout();
    QString serializeHeader();
    QStringList findEvents(Databaseconnection *db);
    float calculateTotalPrice();
    bool validatefields();
    bool getSelectedEventInfo(Databaseconnection *db);
    bool pdf;
    bool headerPresent;
};

#endif // CHECKOUTWIDGET_H
