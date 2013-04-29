/*
#################################################################################################
#   Copyright 2013 Holger Ihrig                                                                 #
#                                                                                               #
#   This file is part of iBasar.                                                                #
#                                                                                               #
#   iBasar is free software: you can redistribute it and/or modify it under the terms of        #
#   the GNU General Public License as published by the Free Software Foundation,                #
#   either version 3 of the License, or (at your option) any later version.                     #
#   Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;         #
#   without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   #
#   See the GNU General Public License for more details.                                        #
#                                                                                               #
#   You should have received a copy of the GNU General Public License along with iBasar.        #
#   If not, see http://www.gnu.org/licenses/.                                                   #
#################################################################################################
*/

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
#include <QMessageBox>

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


signals:
    void db_error(QString error_msg, QString error_src);

private:

    QString db_hostname;
    QString db_name;
    QString db_username;
    QString db_password;
    bool connection_ok;


public slots:

};

#endif // DATABASECONNECTION_H
