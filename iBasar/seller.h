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

#ifndef SELLER_H
#define SELLER_H

#include <QString>
#include "databaseconnection.h"

class Seller
{
public:
    Seller();
    int getID();
    QString getName();
    QString getSurname();
    QString getAddress();
    QString getCity();
    QString getPlz();
    QString getEmail();
    QString getPhone();
    QString getEvent();
    bool isComplete();

    bool setName(QString name);
    bool setSurname(QString surname);
    bool setAddress(QString address);
    bool setCity(QString city);
    bool setPlz(QString plz);
    bool setEmail(QString email);
    bool setPhone(QString phone);
    bool setEvent(QString eventname);

    bool findSeller(Databaseconnection *data);
    bool createSeller(Databaseconnection *data);
    int getNumberofSalesItems(Databaseconnection *data);
    QList<int> getSalesItemIDs(Databaseconnection *data);

private:
    int mID;
    QString mName;
    QString mSurname;
    QString mAddress;
    QString mCity;
    QString mPlz;
    QString mEmail;
    QString mPhone;
    QString mEvent;

    QString findEvent(Databaseconnection *data, QString eventid);

};

#endif // SELLER_H
