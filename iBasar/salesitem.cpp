#include "salesitem.h"

SalesItem::SalesItem(QObject *parent) :
    QObject(parent)
{
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

bool SalesItem::loadItem(Databaseconnection *data, int itemID)
{
    QSqlQuery result;
    QString querycmd;
    mID = itemID;

    querycmd = "SELECT a.ID, a.Verkäufer, a.Size, b.Hersteller, c.Beschreibung, a.Preis FROM `artikel` a, `Hersteller` b, `Artikelbezeichnung` c WHERE a.ID=" +
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

    return true;
}

bool SalesItem::saveItem(Databaseconnection *data)
{
    if (!isComplete())
        return false;

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
