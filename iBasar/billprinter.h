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

#ifndef BILLPRINTER_H
#define BILLPRINTER_H

#include <QObject>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>

class BillPrinter : public QObject
{
    Q_OBJECT
public:
    explicit BillPrinter(QObject *parent = 0);
    ~BillPrinter();

    void printPdf(QStringList &entries);

    void setHeaderInfo(QString Info);
    void setEventName(QString eventName);
    void setEventLocation(QString eventLocation);
    void setEventDate(QString eventDate);
    

signals:
    
public slots:
    
private:
    QPrinter *iprinter;
    QStringList deserialize(QString serialString);
    QString createHtmlHeader();
    QString addHtmlAdresswithEventInfo();
    QString addHtmlSalesItemHeader();
    QString addHtmlSalesItem(QStringList entry);
    QString addHtmlDocumentFooter();
    QString addHtmlSummary(int count, float price);

    QStringList headerinfo;
    QString eventName;
    QString eventLocation;
    QString eventDate;

};

#endif // BILLPRINTER_H
