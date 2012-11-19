#ifndef SALESITEM_H
#define SALESITEM_H

#include <QObject>
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
    bool setID(QString itemid);
    bool setSellerID(int sellerid);
    bool setManufacturer(QString manufacturer);
    bool setDescription(QString description);
    bool setItemSize(QString itemsize);
    bool setPrice(QString price);
    bool isComplete();


signals:
    
public slots:
    bool loadItem(Databaseconnection *data, int itemID);
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
