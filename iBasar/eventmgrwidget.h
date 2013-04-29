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

#ifndef EVENTMGRWIDGET_H
#define EVENTMGRWIDGET_H

#include <QDialog>
#include <QtWidgets/QMessageBox>
#include "databaseconnection.h"

namespace Ui {
class EventMgrWidget;
}

class EventMgrWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit EventMgrWidget(Databaseconnection *data, QWidget *parent = 0);
    ~EventMgrWidget();
    
private:
    Ui::EventMgrWidget *ui;
    Databaseconnection *db;

private slots:
    void createEventManagerWidget();
};

#endif // EVENTMGRWIDGET_H
