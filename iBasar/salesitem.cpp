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
         !mPrice.isEmpty() )
        return true;

    return false;
}

bool SalesItem::saveItem()
{

}

int SalesItem::saveManufacturer(Databaseconnection *data)
{

}

int SalesItem::saveDescription(Databaseconnection *data)
{

}
