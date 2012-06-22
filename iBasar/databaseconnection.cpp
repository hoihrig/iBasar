#include "databaseconnection.h"

Databaseconnection::Databaseconnection(QObject *parent) :
    QObject(parent), db_hostname("localhost"), db_name("ibasar"), db_username("ibasar"), db_password(""), connection_ok(false)
{
}

Databaseconnection::~Databaseconnection()
{
}

bool Databaseconnection::open()
{
    QSqlDatabase db = QSqlDatabase::addDatabase( "QMYSQL" );;

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
    QSqlDatabase db;

    if (db.isOpen())
    {
        db.close();
        connection_ok = false;
    }

}

QString Databaseconnection::getLastError() {
    QSqlDatabase db;

    if (db.lastError().isValid())
        return db.lastError().text();
    return QString("No Error occured!");
}

void Databaseconnection::query(QString sqlquery, QSqlQuery &results)
{
    if (!sqlquery.isEmpty())
        return;

    if (!results.exec(sqlquery))
        qDebug() << results.lastError();

    return;
}

void Databaseconnection::readDbSettings(QSettings *settings)
{
    if (!settings)
        return;

    setHostname(settings->value("DbHostname").toString());
    setDbName(settings->value("DbName").toString());
    setUsername(settings->value("DbUser").toString());
    setPassword(settings->value("DbPasswd").toString());

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
