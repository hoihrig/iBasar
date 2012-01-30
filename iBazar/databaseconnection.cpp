#include "databaseconnection.h"

Databaseconnection::Databaseconnection(QObject *parent) :
    QObject(parent), db_hostname("localhost"), db_name("ibasar"), db_username("ibasar"), db_password(""), connection_ok(false)
{
    dbquery = new QSqlQuery(db);
    db.addDatabase("QMYSQL");
}

Databaseconnection::~Databaseconnection()
{
    if (dbquery)
        delete dbquery;
}

bool Databaseconnection::open()
{
    db.setHostName(db_hostname);
    db.setDatabaseName(db_name);
    db.setUserName(db_username);
    db.setPassword(db_password);
    connection_ok = db.open();

    if (connection_ok)
        return connection_ok;
    else
    {
        qDebug() << db.lastError();
        return 0;
    }
}

void Databaseconnection::close()
{
    if (db.isOpen())
    {
        db.close();
        connection_ok = false;
    }

}

QString Databaseconnection::getLastError() {
    if (db.lastError().isValid())
        return db.lastError().text();
    return QString("No Error occured!");
}

QSqlQuery* Databaseconnection::query(QString sqlquery)
{
// TODO
return 0;
}

void Databaseconnection::setHostname(QString hostname)
{
    if (!hostname.isEmpty())
        db_hostname = hostname;
}

void Databaseconnection::setDbName(QString dbname)
{
    if (!dbname.isEmpty())
        db_name = dbname;
}

void Databaseconnection::setUsername(QString username)
{
    if (!username.isEmpty())
        db_username = username;
}

void Databaseconnection::setPassword(QString password){
    if (!password.isEmpty())
        db_password = password;
}
