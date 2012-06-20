#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QSettings>

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

    void query(QString sqlquery, QSqlQuery &results);
    void setHostname(QString hostname);
    void setDbName(QString dbname);
    void setUsername(QString username);
    void setPassword(QString password);

    bool open();
    void close();
    bool isEstablished() { return connection_ok; }

    void readDbSettings(QSettings *settings);

private:

    QString db_hostname;
    QString db_name;
    QString db_username;
    QString db_password;
    bool connection_ok;

signals:

public slots:

};

#endif // DATABASECONNECTION_H
