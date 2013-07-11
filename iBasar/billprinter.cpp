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

#include "billprinter.h"

BillPrinter::BillPrinter(QObject *parent) :
    QObject(parent)
{
}

BillPrinter::~BillPrinter()
{
    if (iprinter != 0)
        delete iprinter;
}

QStringList BillPrinter::deserialize(QString serialString)
{
    return serialString.split(":::");
}

void BillPrinter::setHeaderInfo(QString Info)
{
    if (!Info.isEmpty())
        headerinfo = deserialize(Info);
}

void BillPrinter::setEventName(QString eventName)
{
    if(!eventName.isEmpty())
        this->eventName = eventName;
}

void BillPrinter::setEventLocation(QString eventLocation)
{
    if(!eventLocation.isEmpty())
        this->eventLocation = eventLocation;
}

void BillPrinter::setEventDate(QString eventDate)
{
    if(!eventDate.isEmpty())
        this->eventDate = eventDate;
}

QString BillPrinter::createHtmlHeader()
{
    QString temp;

    temp = "<html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=windows-1252\">";
    temp += "<title>iBasar, Schneesportbörse: Verkaufsbeleg</title></head><body>";
    return temp;
}

QString BillPrinter::addHtmlAdresswithEventInfo()
{
    QString temp;

    temp = "<tr><td><table><tbody><tr><td rowspan=\"2\">" + headerinfo[0];
    temp +="<br>" + headerinfo[1];
    temp +="<br>" + headerinfo[2];
    temp +="</td><td align=\"right\">";
    temp +=eventLocation + ", " + eventDate;
    temp +="</td></tr></tbody></table></td></tr>";

    return temp;
}

QString BillPrinter::addEventInfo()
{
    QString temp;

    temp = "<tr><td><table><tbody><tr><td rowspan=\"2\">";
    temp +="<br>";
    temp +="<br>";
    temp +="</td><td align=\"right\">";
    temp +=eventLocation + ", " + eventDate;
    temp +="</td></tr></tbody></table></td></tr>";

    return temp;
}

QString BillPrinter::addHtmlSalesItemHeader()
{
    QString temp;

    temp = "<tr><td><h2>Verkaufsbeleg: iBasar, Schneesportbörse</h2></td></tr>";
    temp += "<tr><td><h3>Folgende Artikel haben wir an Sie verkauft:</h3></td></tr>";
    temp += "<tr><td><table align=\"center\" border=\"0\" cellpadding=\"1\" cellspacing=\"1\" width=\"100%\">";
    temp += "<tbody><tr><th>Kennz.</th><th>Hersteller - Artikel - Zusatzinformation - Groesse</th><th>Preis</th></tr>";

    return temp;
}


QString BillPrinter::addHtmlSalesItem(QStringList entry)
{
    QString temp;

    temp = "<tr><td>" + entry[1] + "</td>";
    temp += "<td>" + entry[0] + "</td>";
    temp += "<td align=\"right\"><nobr>" + entry[2] + " €</nobr></td></tr>";

    return temp;
}

QString BillPrinter::addHtmlDocumentFooter()
{
    QString temp;

    temp = "</tbody></table></td></tr><tr><td><table border=\"0\" width=\"100%\">";
    temp += "<tbody><tr><td colspan=\"2\">Vielen Dank für Ihren Einkauf!</td></tr>";
    temp += "<tr><td colspan=\"2\">&nbsp;</td></tr><tr>";
    temp += "<td>Ihr iBasar-Demo-Verein</td>";
    temp += "<td class=\"sehrklein\" align=\"right\">Erstellt: " + QDateTime::currentDateTime().toString() + "</td>";
    temp += "</tr></tbody></table></td></tr></tbody></table></body></html>";

    return temp;
}

QString BillPrinter::addHtmlSummary(int count, float price)
{
    QString temp;

    temp = "<tr><td><b>Summe:</b></td><td>";
    temp += "<b>" + QString::number(count) + " Artikel</b></td>";
    temp += "<td align=\"right\"><b>" + QString::number(price) + " €</b></td></tr>";

    return temp;
}

void BillPrinter::printPrinter(QWidget* parent,QStringList &entries)
{
    iprinter = new QPrinter();

    QPrintDialog printDialog(iprinter,parent);
    if (printDialog.exec() == QDialog::Accepted) {
        print(entries);
    }

}

void BillPrinter::print(QStringList &entries)
{
    QString htmlContent;
    float totalPrice = 0;

    htmlContent += createHtmlHeader();

    if (headerinfo.isEmpty())
        htmlContent += addEventInfo();
    else
        htmlContent += addHtmlAdresswithEventInfo();

    htmlContent += addHtmlSalesItemHeader();

    for(int i=0; i<entries.count(); i++)
    {
        QStringList entrylist = deserialize(entries[i]);

        htmlContent += addHtmlSalesItem(entrylist);

        // The Second value contains the price of the item
        // and is here used to calculate the total costs
        totalPrice += entrylist[2].toFloat();
    }

    htmlContent += addHtmlSummary(entries.count(), totalPrice);

    htmlContent += addHtmlDocumentFooter();

    QTextDocument *document = new QTextDocument();
    document->setHtml(htmlContent);


    document->print(iprinter);

    delete document;
}

void BillPrinter::printPdf(QStringList &entries)
{
    iprinter = new QPrinter();
    iprinter->setOutputFileName("printbill.pdf");
    iprinter->setOutputFormat(QPrinter::PdfFormat);

    print(entries);

    // This is just temporary until a proper printing class is available.
    QDesktopServices::openUrl(QUrl("printbill.pdf", QUrl::TolerantMode));
}
