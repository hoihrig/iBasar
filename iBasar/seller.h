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
