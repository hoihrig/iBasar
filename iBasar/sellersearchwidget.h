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

#ifndef SELLERSEARCHWIDGET_H
#define SELLERSEARCHWIDGET_H

#include <QDialog>

namespace Ui {
class SellerSearchWidget;
}

class SellerSearchWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SellerSearchWidget(QWidget *parent = 0);
    ~SellerSearchWidget();

private slots:
    void search();
private:
    Ui::SellerSearchWidget *ui;

    void changeEvent(QEvent *event);
signals:
    void searchbyID(int);
    void searchbyName(QString);
};

#endif // SELLERSEARCHWIDGET_H
