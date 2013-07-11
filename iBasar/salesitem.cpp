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

#include "salesitem.h"

SalesItem::SalesItem(QObject *parent) :
    QObject(parent)
{
}

bool SalesItem::setID(QString itemid)
{
    mID = itemid.toInt();

    return true;
}

bool SalesItem::setSellerID(int sellerid)
{
    if (sellerid == 0)
        return false;

    mSellerID = sellerid;
    return true;
}

bool SalesItem::setManufacturer(QString manufacturer)
{
    if (manufacturer.isEmpty())
        return false;

    mManufacturer = manufacturer;
    return true;

}

bool SalesItem::setDescription(QString description)
{
    if (description.isEmpty())
        return false;

    mDescription = description;
    return true;
}

bool SalesItem::setItemSize(QString itemsize)
{
    if (itemsize.isEmpty())
        return false;

    mItemSize = itemsize;
    return true;
}

bool SalesItem::setPrice(QString price)
{
    if (price.isEmpty())
        return false;

    mPrice = price;
    return true;
}

void SalesItem::setSold(bool soldStatus)
{
    mSold = soldStatus;
}


bool SalesItem::isComplete()
{
    if ( !mManufacturer.isEmpty() &&
         !mDescription.isEmpty() &&
         !mItemSize.isEmpty() &&
         !mPrice.isEmpty() &&
         (mSellerID != 0) )
        return true;

    return false;
}

bool SalesItem::findItem(Databaseconnection *data, int itemID)
{
    QSqlQuery result;
    QString querycmd;
    mID = itemID;

    querycmd = "SELECT a.ID, a.Verkäufer, a.Size, b.Hersteller, c.Beschreibung, a.Preis, a.Verkauft FROM `Artikel` a, `Hersteller` b, `Artikelbezeichnung` c WHERE a.ID=" +
            QString::number(mID) + " AND " +
            "a.Hersteller = b.ID AND " +
            "a.Beschreibung = c.ID";

    data->query(querycmd,result);

    if (!(result.numRowsAffected() > 0))
        return false;

    result.next();

    mSellerID = result.value(1).toInt();
    mItemSize = result.value(2).toString();
    mManufacturer = result.value(3).toString();
    mDescription = result.value(4).toString();
    mPrice = result.value(5).toString();
    mSold = result.value(6).toInt();

    return true;
}


bool SalesItem::saveItem(Databaseconnection *data)
{
    if (!isComplete())
        return false;

    // Decide if we have a new dataset or a merge
    if (mID != 0)
    {
        // SalesItem already exists in DB with that given mID and all field identical
        if (existsInDb(data))
            return true;
        else //SalesItem ID exists, but some fields differ. Update needed!
            return updateItem(data);
    }
    else
    {
        return saveNewItem(data);
    }

}

bool SalesItem::deleteItem(Databaseconnection *data)
{
    QSqlQuery result;
    QString querycmd;

    querycmd = "DELETE FROM `Artikel` WHERE `Artikel`.`ID` = " + QString::number(mID);

    data->query(querycmd,result);

    result.next();

    if (result.value(0).toInt() > 0)
        return true;

    return false;
}


bool SalesItem::existsInDb(Databaseconnection *data)
{
    // Store Manufacturer Name in Database and get ID back
    int manufacturerID;
    manufacturerID = saveManufacturer(data);

    // Store Item Description in Database and get ID back
    int descriptionID;
    descriptionID = saveDescription(data);

    if ( (descriptionID == 0) ||
         (manufacturerID == 0) )
        return false;

    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT COUNT(ID) FROM `Artikel` WHERE ID=" +
            QString::number(mID) + " AND Verkäufer=" +
            QString::number(mSellerID) + " AND Size='" +
            mItemSize + "' AND Hersteller=" +
            QString::number(manufacturerID) + " AND Beschreibung=" +
            QString::number(descriptionID) + " AND Preis='" +
            mPrice + "' AND Verkauft=" + QString::number(mSold) + "";

    data->query(querycmd,result);

    result.next();

    if (result.value(0).toInt() > 0)
        return true;

    return false;

}

bool SalesItem::updateItem(Databaseconnection *data)
{
    // Store Manufacturer Name in Database and get ID back
    int manufacturerID;
    manufacturerID = saveManufacturer(data);

    // Store Item Description in Database and get ID back
    int descriptionID;
    descriptionID = saveDescription(data);

    if ( (descriptionID == 0) ||
         (manufacturerID == 0) )
        return false;

    QSqlQuery result;
    QString querycmd;

    querycmd = "UPDATE `Artikel` SET  Verkäufer=" +
            QString::number(mSellerID) + ", Size='" +
            mItemSize + "', Hersteller=" +
            QString::number(manufacturerID) + ", Beschreibung=" +
            QString::number(descriptionID) + ", Preis='" +
            mPrice + "', Verkauft=" +
            QString::number(mSold) + " WHERE ID=" +
            QString::number(mID);

    data->query(querycmd,result);

    return true;



}

bool SalesItem::saveNewItem(Databaseconnection *data)
{
    // Store Manufacturer Name in Database and get ID back
    int manufacturerID;
    manufacturerID = saveManufacturer(data);

    // Store Item Description in Database and get ID back
    int descriptionID;
    descriptionID = saveDescription(data);

    if ( (descriptionID == 0) ||
         (manufacturerID == 0) )
        return false;

    // Insert the Complete Dataset into the Artikel Table now
    QSqlQuery result;
    QString querycmd;

    // Query for the next free ID
    querycmd = "SELECT MAX(ID) FROM `Artikel`";
    data->query(querycmd,result);
    result.next();

    mID = result.value(0).toInt() + 1;

    result.clear();

    querycmd = "INSERT INTO `Artikel` (ID, Verkäufer, Size, Hersteller, Beschreibung, Preis, Aktiv, Verkauft) VALUES (" +
            QString::number(mID) + ", " +
            QString::number(mSellerID) + ", " +
            "'" + mItemSize + "', " +
            QString::number(manufacturerID) + ", " +
            QString::number(descriptionID) + ", " +
            "'" + mPrice + "', 1, 0)";
    data->query(querycmd,result);

    if (result.numRowsAffected() > 0)
        return true;

    return false;
}

int SalesItem::saveManufacturer(Databaseconnection *data)
{
    int manufacturerID = 0;
    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT ID FROM `Hersteller` WHERE Hersteller='" + mManufacturer + "'";

    data->query(querycmd,result);

    if (result.size() > 0)
    {   // In this Case the Manufacturer is already in the Database and we can simply return its ID
        result.next();
        manufacturerID = result.value("ID").toInt();
    }
    else
    {
        result.clear();

        // Query for the next free ID
        querycmd = "SELECT MAX(ID) FROM `Hersteller`";
        data->query(querycmd,result);
        result.next();
        manufacturerID = result.value(0).toInt() + 1;

        result.clear();

        // Insert the Manufacturer Name with determined ID
        querycmd = "INSERT INTO `Hersteller` (ID, Hersteller) VALUES (" +
                QString::number(manufacturerID) + "," +
                "'" + mManufacturer + "')";
        data->query(querycmd,result);


        if(result.numRowsAffected() > 0)
            return manufacturerID;

    }

    return manufacturerID;
}

int SalesItem::saveDescription(Databaseconnection *data)
{
    int descriptionID = 0;
    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT ID FROM `Artikelbezeichnung` WHERE Beschreibung='" + mDescription + "'";

    data->query(querycmd,result);

    if (result.size() > 0)
    {   // In this Case the Description is already in the Database and we can simply return its ID
        result.next();
        descriptionID = result.value("ID").toInt();
    }
    else
    {
        result.clear();

        // Query for the next free ID
        querycmd = "SELECT MAX(ID) FROM `Artikelbezeichnung`";
        data->query(querycmd,result);
        result.next();
        descriptionID = result.value(0).toInt() + 1;

        result.clear();

        // Insert the Manufacturer Name with determined ID
        querycmd = "INSERT INTO `Artikelbezeichnung` (ID, Beschreibung) VALUES (" +
                QString::number(descriptionID) + "," +
                "'" + mDescription + "')";
        data->query(querycmd,result);


        if(result.numRowsAffected() > 0)
            return descriptionID;

    }

    return descriptionID;

}

QString SalesItem::serialize()
{
    QString serialized;

    serialized = mManufacturer + " " + mDescription + " " + mItemSize + ":::" +
            QString::number(mID) + ":::" +
            mPrice;

    return serialized;

}
