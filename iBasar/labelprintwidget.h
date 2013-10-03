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

#ifndef LABELPRINTWIDGET_H
#define LABELPRINTWIDGET_H

#include <QDialog>
#include <QStringList>
#include "databaseconnection.h"
#include "itemprinter.h"
#include "seller.h"
#include "salesitem.h"


namespace Ui {
class Labelprintwidget;
}

class LabelPrintWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit LabelPrintWidget(Databaseconnection *data, QWidget *parent = 0);
    ~LabelPrintWidget();
    
private:
    Ui::Labelprintwidget *ui;
    Databaseconnection *db;
    QStringList findEvents(Databaseconnection *db);
    QStringList findSellers(Databaseconnection *data);

    void changeEvent(QEvent *event);
private slots:
    void printlabel();
    void updateSellers(int index);
};

#endif // LABELPRINTWIDGET_H
