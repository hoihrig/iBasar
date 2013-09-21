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

#include "sellercheckoutprinter.h"

SellerCheckoutPrinter::SellerCheckoutPrinter(QObject *parent) :
    QObject(parent)
{
}

SellerCheckoutPrinter::~SellerCheckoutPrinter()
{
    if (iprinter != 0)
        delete iprinter;
}

QStringList SellerCheckoutPrinter::deserialize(QString serialString)
{
    return serialString.split(":::");
}

void SellerCheckoutPrinter::setHeaderInfo(QString Info)
{
    if (!Info.isEmpty())
        headerinfo = deserialize(Info);
}

void SellerCheckoutPrinter::setEventName(QString eventName)
{
    if(!eventName.isEmpty())
        this->eventName = eventName;
}

void SellerCheckoutPrinter::setEventLocation(QString eventLocation)
{
    if(!eventLocation.isEmpty())
        this->eventLocation = eventLocation;
}

void SellerCheckoutPrinter::setSoldProvision(QString provision)
{
    if(!provision.isEmpty())
        this->soldProvision = provision;
}

void SellerCheckoutPrinter::setUnSoldProvision(QString provision)
{
    if(!provision.isEmpty())
        this->unsoldProvision = provision;
}

void SellerCheckoutPrinter::setEventDate(QString eventDate)
{
    if(!eventDate.isEmpty())
        this->eventDate = eventDate;
}

QString SellerCheckoutPrinter::createHtmlHeader()
{
    QString temp;

    temp = "<html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=windows-1252\">";
    temp += "<title>iBasar, Schneesportbörse: Abrechnungsbeleg</title></head><body>";
    return temp;
}

QString SellerCheckoutPrinter::addLogo()
{
    QString temp;

    temp = "<tr><td><table align=\"right\"><tbody><tr><td><img src=\"logo.png\" /></td></tr></tbody></table></td></tr>";

    return temp;
}

QString SellerCheckoutPrinter::addHtmlAdresswithEventInfo()
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

QString SellerCheckoutPrinter::addEventInfo()
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

QString SellerCheckoutPrinter::addHtmlSoldSalesItemHeader()
{
    QString temp;

    temp = "<tr><td><h2>Abrechnung: iBasar, Schneesportbörse</h2></td></tr>";
    temp += "<td><table width=\"100%\"><tr><td><b>Einnahmen aus verkauften Artikeln:</b></td><td align=\"right\">&nbsp;</td>";
    temp += "<td align=\"right\">&nbsp;</td></tr>";


    return temp;
}

QString SellerCheckoutPrinter::addHtmlUnSoldSalesItemHeader()
{
    QString temp;

    temp = "<tr><td><h3>Folgende Ihrer Artikel konnten wir leider nicht verkaufen:</h3></td></tr>";
    temp += "<tr><td><table align=\"left\"><tr><th>Kennz.</th><th><nobr>Hersteller - Artikel - Zusatzinformation</nobr></th><th>Gr&ouml;&szlig;e</th><th>Preis</th></tr>";

    return temp;
}



QString SellerCheckoutPrinter::addHtmlUnSoldSalesItem(QStringList entry)
{
    QString temp;

    temp = "<tr><td>" + entry[1] + "</td><td>";
    temp += "<nobr>" + entry[0] + "</nobr></td><td></td>";
    temp += "<td align=\"right\"><nobr>" + QString::number(entry[2].toInt(),'f',2) + " " + currencySymbol + "</nobr></td></tr>";

    return temp;
}

QString SellerCheckoutPrinter::addHtmlSoldSalesItem(QStringList entry)
{
    QString temp;

    temp = "<tr><td><nobr>" + entry[1] + ": ";
    temp += entry[0] + "</nobr></td><td align=\"right\">&nbsp;</td>";
    temp += "<td align=\"right\"><nobr>" + QString::number(entry[2].toInt(),'f',2) + " " + currencySymbol + "</nobr></td></tr>";

    return temp;
}

QString SellerCheckoutPrinter::addHtmlDocumentFooter()
{
    QString temp;

    temp = "</tbody></table></td></tr><tr><td><table border=\"0\" width=\"100%\">";
    temp += "<tbody><tr><td colspan=\"2\">Vielen Dank und bis n&auml;chstes Jahr!</td></tr>";
    temp += "<tr><td colspan=\"2\">&nbsp;</td></tr><tr>";
    temp += "<td>Ihr iBasar-Demo-Verein</td>";
    temp += "<td class=\"sehrklein\" align=\"right\">Erstellt: " + QDateTime::currentDateTime().toString() + "</td>";
    temp += "</tr></tbody></table></td></tr></tbody></table></body></html>";

    return temp;
}

QString SellerCheckoutPrinter::addHtmlSoldSummary(int count, float price)
{
    QString temp;

    float fee = count * unsoldProvision.toFloat();
    float provision = price * (soldProvision.toFloat() / 100);
    float totalcost = fee + provision;
    float totalpayout = price - totalcost;

    temp = "<tr><td>Annahmegeb&uuml;hr (" + QString::number(count) +
            " x " + unsoldProvision + " " + currencySymbol + "):</td>";
    temp += "<td align=\"right\"><nobr>" + QString::number(fee,'f',2) + " " + currencySymbol + "</nobr></td><td align=\"right\">&nbsp;</td></tr>";

    temp += "<tr><td>Verkaufsprovision (" + soldProvision + "% von " + QString::number(price,'f',2) + "&euro;):</td>";
    temp += "<td align=\"right\"><nobr>" + QString::number(provision,'f',2) + " " + currencySymbol + "</nobr></td><td align=\"right\">&nbsp;</td></tr>";
    temp += "<tr><td><b>Kosten:</b></td><td align=\"right\"><nobr>&nbsp;</nobr></td><td align=\"right\">";
    temp += "<nobr><b>-" + QString::number(totalcost,'f',2) + " " + currencySymbol + "</b></nobr></td></tr>";
    temp += "<tr><td><b>Gesamtbetrag:</b></td><td align=\"right\">&nbsp;</td><td align=\"right\">";
    temp += "<nobr><b>" + QString::number(totalpayout,'f',2) + " " + currencySymbol + "</b></nobr></td></tr></table>";
    temp += "</td></tr><tr><td>&nbsp;</td></tr><tr><td>&nbsp;</td></tr>";

    return temp;
}

QString SellerCheckoutPrinter::addHtmlUnSoldSummary(int count, float price)
{
    QString temp;

    temp = "<tr><td>&nbsp;</td></tr>";
    temp += "<tr><td><b>Summe:</b></td><td><b>" + QString::number(count) + " Artikel</b></td>";
    temp += "<td>&nbsp;</td><td align=\"right\">";
    temp += "<nobr><b>" + QString::number(price,'f',2) + " " + currencySymbol + "</nobr></b></td></tr></table>";
    temp += "</td></tr><tr><td>&nbsp;</td></tr><tr><td>";

    return temp;
}

void SellerCheckoutPrinter::printPrinter(QWidget* parent, QStringList &soldentries, QStringList &unsoldentries)
{
    iprinter = new QPrinter();

    QPrintDialog printDialog(iprinter,parent);
    if (printDialog.exec() == QDialog::Accepted) {
        print(soldentries, unsoldentries);
    }

}

void SellerCheckoutPrinter::print(QStringList &soldentries, QStringList &unsoldentries)
{
    QString htmlContent;
    float totalPrice = 0;

    htmlContent += createHtmlHeader();

    if (printLogo)
        htmlContent += addLogo();

    if (headerinfo.isEmpty())
        htmlContent += addEventInfo();
    else
        htmlContent += addHtmlAdresswithEventInfo();

    // First Print the sold Items
    htmlContent += addHtmlSoldSalesItemHeader();

    for(int i=0; i<soldentries.count(); i++)
    {
        QStringList entrylist = deserialize(soldentries[i]);

        htmlContent += addHtmlSoldSalesItem(entrylist);

        // The Second value contains the price of the item
        // and is here used to calculate the total costs
        totalPrice += entrylist[2].toFloat();
    }

    // Only the Unsold Items are charged for adding to the basar, sold Items only use Provision
    htmlContent += addHtmlSoldSummary(unsoldentries.count(), totalPrice);


    // Now the Unsold Items
    totalPrice = 0;
    htmlContent += addHtmlUnSoldSalesItemHeader();

    for(int i=0; i<unsoldentries.count(); i++)
    {
        QStringList entrylist = deserialize(unsoldentries[i]);

        htmlContent += addHtmlUnSoldSalesItem(entrylist);

        // The Second value contains the price of the item
        // and is here used to calculate the total costs
        totalPrice += entrylist[2].toFloat();
    }

    htmlContent += addHtmlUnSoldSummary(unsoldentries.count(), totalPrice);


    htmlContent += addHtmlDocumentFooter();

    QTextDocument *document = new QTextDocument();
    document->setHtml(htmlContent);


    document->print(iprinter);

    delete document;
}


void SellerCheckoutPrinter::setPrintLogo(bool value)
{
    printLogo = value;
}


void SellerCheckoutPrinter::setCurrencySymbol(const QString &value)
{
    currencySymbol = value;
}


void SellerCheckoutPrinter::printPdf(QStringList &soldentries, QStringList &unsoldentries)
{
    iprinter = new QPrinter();
    iprinter->setOutputFileName("printbill.pdf");
    iprinter->setOutputFormat(QPrinter::PdfFormat);

    print(soldentries, unsoldentries);

    // This is just temporary until a proper printing class is available.
    QDesktopServices::openUrl(QUrl("printbill.pdf", QUrl::TolerantMode));
}
