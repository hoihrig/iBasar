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

#ifndef SELLERCHECKOUTPRINTER_H
#define SELLERCHECKOUTPRINTER_H

#include <QObject>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>
#include <QPrintDialog>

class SellerCheckoutPrinter : public QObject
{
    Q_OBJECT
public:
    explicit SellerCheckoutPrinter(QObject *parent = 0);
    ~SellerCheckoutPrinter();

    void printPdf(QStringList &soldentries, QStringList &unsoldentries);
    void printPrinter(QWidget *parent, QStringList &soldentries, QStringList &unsoldentries);

    void setHeaderInfo(QString Info);
    void setEventName(QString eventName);
    void setEventLocation(QString eventLocation);
    void setEventDate(QString eventDate);


    void setSoldProvision(QString provision);
    void setUnSoldProvision(QString provision);
    void setCurrencySymbol(const QString &value);

    void setPrintLogo(bool value);

signals:

public slots:

private:
    QPrinter *iprinter;
    QStringList deserialize(QString serialString);
    QString createHtmlHeader();
    QString addHtmlAdresswithEventInfo();
    QString addEventInfo();
    QString addHtmlSoldSalesItemHeader();
    QString addHtmlUnSoldSalesItem(QStringList entry);
    QString addHtmlDocumentFooter();
    QString addHtmlSoldSummary(int count, float price);
    void print(QStringList &entries, QStringList &unsoldentries);

    QStringList headerinfo;
    QString eventName;
    QString eventLocation;
    QString eventDate;
    QString soldProvision;
    QString unsoldProvision;
    QString currencySymbol;
    bool printLogo;

    QString addHtmlUnSoldSalesItemHeader();
    QString addHtmlSoldSalesItem(QStringList entry);
    QString addHtmlUnSoldSummary(int count, float price);
    QString addLogo();
};

#endif // SELLERCHECKOUTPRINTER_H
