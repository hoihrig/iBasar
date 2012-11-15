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

    querycmd = "SELECT * FROM `Verkäufer` WHERE Vorname='" + mName + "' AND Nachname='" + mSurname + "'";

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
    int rowid = 0;
    int eventid = 0;

    querycmd = "SELECT MAX(ID) FROM `Verkäufer`";
    data->query(querycmd,result);

    result.next();
    rowid = result.value(0).toInt() + 1;
    result.clear();

    querycmd = "SELECT ID FROM `Veranstaltung` WHERE Name='" + mEvent + "'";
    data->query(querycmd,result);

    result.next();
    eventid = result.value(0).toInt();
    result.clear();

    querycmd = "INSERT INTO `Verkäufer` (ID, Vorname, Nachname, Straße, PLZ, Ort, Telefon, Email, Veranstaltung) VALUES (" +
            QString::number(rowid) + ", " +
            "'" + mName + "', " +
            "'" + mSurname + "', " +
            "'" + mAddress + "', " +
            "" + mPlz + ", " +
            "'" + mCity + "', " +
            "'" + mPhone + "', " +
            "'" + mEmail + "', " +
            QString::number(eventid)  + ")";

    data->query(querycmd,result);


    return false;
}
