#ifndef SELLER_H
#define SELLER_H

#include <QString>

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

    bool setName(QString name);
    bool setSurname(QString surname);
    bool setEvent(QString eventname);

public slots:
    bool findSeller();
    bool createSeller();

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

};

#endif // SELLER_H
