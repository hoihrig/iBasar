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

#ifndef SALESITEM_H
#define SALESITEM_H

#include <QObject>
#include <QString>
#include <QPainter>
#include <QImageWriter>
#include <QImage>
#include "databaseconnection.h"

class SalesItem : public QObject
{
    Q_OBJECT
public:
    explicit SalesItem(QObject *parent = 0);
    int getID() { return mID; }
    QString getManufacturer() { return mManufacturer; }
    QString getDescription() { return mDescription; }
    QString getItemSize() { return mItemSize; }
    QString getPrice() { return mPrice; }
    QString serialize();
    bool setID(QString itemid);
    bool setSellerID(int sellerid);
    bool setManufacturer(QString manufacturer);
    bool setDescription(QString description);
    bool setItemSize(QString itemsize);
    bool setPrice(QString price);
    bool isComplete();



signals:
    
public slots:
    bool findItem(Databaseconnection *data, int itemID);
    bool saveItem(Databaseconnection *data);

private:
    int mID;
    int mSellerID;
    QString mManufacturer;
    QString mDescription;
    QString mItemSize;
    QString mPrice;

    int saveManufacturer(Databaseconnection *data);
    int saveDescription(Databaseconnection *data);
    bool saveNewItem(Databaseconnection *data);
    bool updateItem(Databaseconnection *data);
    bool existsInDb(Databaseconnection *data);
    
};

#endif // SALESITEM_H
