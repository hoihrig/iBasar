#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

class Databaseconnection : public QObject
{
    Q_OBJECT
public:
    explicit Databaseconnection(QObject *parent = 0);
    ~Databaseconnection();

    QString getHostname() { return db_hostname; }
    QString getDbName() { return db_name; }
    QString getUsername() { return db_username; }
    QString getLastError();

    void setHostname(QString hostname);
    void setDbName(QString dbname);
    void setUsername(QString username);
    void setPassword(QString password);

    bool open();
    void close();
    bool isEstablished() { return connection_ok; }

    QSqlQuery* query(QString sqlquery);

private:
    QSqlDatabase db;

    QString db_hostname;
    QString db_name;
    QString db_username;
    QString db_password;
    bool connection_ok;

    QSqlQuery* dbquery;
signals:

public slots:

};

#endif // DATABASECONNECTION_H
