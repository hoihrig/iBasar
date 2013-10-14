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

#ifndef EVENTSTATUSWIDGET_H
#define EVENTSTATUSWIDGET_H

#include <QWidget>
#include "databaseconnection.h"

namespace Ui {
class EventStatusWidget;
}

class EventStatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventStatusWidget(Databaseconnection *db, QWidget *parent = 0);
    ~EventStatusWidget();

public slots:
    void updateEvent();

    void setDefaultEvent(QString name);
private slots:
    void eventChanged(int index);
private:
    Ui::EventStatusWidget *ui;
    Databaseconnection *data;
    QString defaultEvent;

    void changeEvent(QEvent *event);
    void updateSellerStats();
    void updateItemStats();
    void updateAvailableEvents();
    QStringList findEvents(Databaseconnection *db);
    int findEventID(QString eventname);
    QStringList findSellersforEvent();
};

#endif // EVENTSTATUSWIDGET_H
