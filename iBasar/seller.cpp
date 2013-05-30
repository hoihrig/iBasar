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

#include "seller.h"

Seller::Seller()
{
}

int Seller::getID()
{
    return mID;
}

QString Seller::getName()
{
    return mName;
}

QString Seller::getSurname()
{
    return mSurname;
}

QString Seller::getAddress()
{
    return mAddress;
}

QString Seller::getCity()
{
    return mCity;
}

QString Seller::getPlz()
{
    return mPlz;
}

QString Seller::getEmail()
{
    return mEmail;
}

QString Seller::getPhone()
{
    return mPhone;
}

QString Seller::getEvent()
{
    return mEvent;
}

bool Seller::isComplete()
{
    if ( (!mName.isEmpty()) &&
         (!mSurname.isEmpty()) &&
         (!mAddress.isEmpty()) &&
         (!mCity.isEmpty()) &&
         (!mPlz.isEmpty()) &&
         (!mEmail.isEmpty()) &&
         (!mPhone.isEmpty()) )
        return true;

    return false;
}

bool Seller::setName(QString name)
{
    if (!name.isEmpty())
    {
        mName = name;
        return true;
    }
    return false;
}

bool Seller::setSurname(QString surname)
{
    if (!surname.isEmpty())
    {
        mSurname = surname;
        return true;
    }
    return false;
}

bool Seller::setAddress(QString address)
{
    if (!address.isEmpty())
    {
        mAddress = address;
        return true;
    }
    return false;
}

bool Seller::setCity(QString city)
{
    if (!city.isEmpty())
    {
        mCity = city;
        return true;
    }
    return false;
}

bool Seller::setPlz(QString plz)
{
    if (!plz.isEmpty())
    {
        mPlz = plz;
        return true;
    }
    return false;
}

bool Seller::setEmail(QString email)
{
    if (!email.isEmpty())
    {
        mEmail = email;
        return true;
    }
    return false;
}

bool Seller::setPhone(QString phone)
{
    if (!phone.isEmpty())
    {
        mPhone = phone;
        return true;
    }
    return false;
}

bool Seller::setEvent(QString eventname)
{
    if (!eventname.isEmpty())
    {
        mEvent = eventname;
        return true;
    }
    return false;
}

bool Seller::findSeller(Databaseconnection *data)
{

    QSqlQuery result;
    QString querycmd;

    if (mEvent.isEmpty()) {
        querycmd = "SELECT * FROM `Verkäufer` WHERE Vorname='" + mName + "' AND Nachname='" + mSurname + "'";
    }
    else {
        querycmd = "SELECT ID FROM `Veranstaltung` WHERE Name='" + mEvent + "'";
        data->query(querycmd,result);
        result.next();
        int eventid = result.value("ID").toInt();

        querycmd = "SELECT * FROM `Verkäufer` WHERE Vorname='" + mName + "' AND Nachname='" + mSurname + "' AND Veranstaltung=" + QString::number(eventid);
    }
    data->query(querycmd,result);

    if (!(result.size() > 0))
        return false;

    result.next();
    mID = result.value("ID").toInt();
    mAddress = result.value("Straße").toString();
    mCity = result.value("Ort").toString();
    mPlz = result.value("PLZ").toString();
    mPhone = result.value("Telefon").toString();
    mEmail = result.value("Email").toString();

    // This one just gives us the ID back, not the name. This is why we have to look up the name
    mEvent = result.value("Veranstaltung").toString();
    mEvent = findEvent(data,mEvent);

    return true;
}

QString Seller::findEvent(Databaseconnection *data, QString eventid)
{
    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT Name FROM `Veranstaltung` WHERE ID=" + eventid;

    data->query(querycmd,result);

    if (!(result.size() > 0))
        return QString("0");

    result.next();
    return result.value("Name").toString();
}

bool Seller::createSeller(Databaseconnection *data)
{
    QSqlQuery result;
    QString querycmd;
    int eventid = 0;

    querycmd = "SELECT MAX(ID) FROM `Verkäufer`";
    data->query(querycmd,result);

    result.next();
    mID = result.value(0).toInt() + 1;
    result.clear();

    querycmd = "SELECT ID FROM `Veranstaltung` WHERE Name='" + mEvent + "'";
    data->query(querycmd,result);

    result.next();
    eventid = result.value("ID").toInt();
    result.clear();

    querycmd = "INSERT INTO `Verkäufer` (ID, Vorname, Nachname, Straße, PLZ, Ort, Telefon, Email, Veranstaltung) VALUES (" +
            QString::number(mID) + ", " +
            "'" + mName + "', " +
            "'" + mSurname + "', " +
            "'" + mAddress + "', " +
            "" + mPlz + ", " +
            "'" + mCity + "', " +
            "'" + mPhone + "', " +
            "'" + mEmail + "', " +
            QString::number(eventid)  + ")";

    data->query(querycmd,result);

    if (result.numRowsAffected() > 0)
        return true;

    return false;
}

int Seller::getNumberofSalesItems(Databaseconnection *data)
{
    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT COUNT(ID) from `Artikel` WHERE Verkäufer=" + QString::number(mID);

    data->query(querycmd, result);

    if (result.next())
        return result.value(0).toInt();

    return 0;
}

QList<int> Seller::getSalesItemIDs(Databaseconnection *data)
{
    QSqlQuery result;
    QString querycmd;
    QList<int> IDList;

    querycmd = "SELECT ID from `Artikel` WHERE Verkäufer=" + QString::number(mID);

    data->query(querycmd, result);

    while(result.next())
    {
        IDList << result.value("ID").toInt();
    }

    return IDList;
}

QString Seller::toHtml()
{
    QString html;

    html = "<font size=\"+1\">" +
            mEvent.toUpper() + "<br><br>" +
            mName + " " + mSurname + "<br>" +
            mAddress + "<br>" +
            mPlz + " " + mCity + "<br><br>" +
            mPhone + "<br><br></font>";

    return html;
}

QString Seller::serialize()
{
    QString serialized;

    serialized = mEvent.toUpper() + ":::" +
            mName + " " + mSurname + ":::" +
            mAddress + ":::" +
            mPlz + " " + mCity + ":::" +
            mPhone;

    return serialized;
}
