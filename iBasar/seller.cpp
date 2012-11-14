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

}

bool Seller::createSeller(Databaseconnection *data)
{

}
