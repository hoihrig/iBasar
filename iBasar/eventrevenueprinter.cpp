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

#include "eventrevenueprinter.h"

EventRevenuePrinter::EventRevenuePrinter(QObject *parent) :
    QObject(parent)
{
}

EventRevenuePrinter::~EventRevenuePrinter()
{
    if (iprinter != 0)
        delete iprinter;
}

void EventRevenuePrinter::setProvisionSold(const QString &value)
{
    if(!value.isEmpty())
        provisionSold = value;
}

void EventRevenuePrinter::setProvisionNotSold(const QString &value)
{
    if(!value.isEmpty())
        provisionNotSold = value;
}



QStringList EventRevenuePrinter::deserialize(QString serialString)
{
    return serialString.split(":::");
}

void EventRevenuePrinter::setEventName(QString eventName)
{
    if(!eventName.isEmpty())
        this->eventName = eventName;
}

QString EventRevenuePrinter::createHtmlHeader()
{
    QString temp;

    temp = "<html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=windows-1252\">";
    temp += "<title>" + tr("iBasar Skibörse, Gesamtabrechnung") + "</title></head><body>";
    return temp;
}

QString EventRevenuePrinter::addLogo()
{
    QString temp;

    temp = "<tr><td><table align=\"right\"><tbody><tr><td><img src=\"logo.png\" /></td></tr></tbody></table></td></tr>";

    return temp;
}

QString EventRevenuePrinter::addDocumentHeader()
{
    QString temp;

    temp = "<tr><td><h2>" + tr("Gesamtabrechnung, iBasar ") + eventName + "</h2></td></tr>";

    return temp;
}

QString EventRevenuePrinter::addContent(QString serializedData)
{
    QStringList data;
    QString temp;

    data = deserialize(serializedData);

    temp = "<tr><td><table width=\"100%\">";
    temp += "<tr><td>" + tr("Gesamtanzahl Anbieter:") + "</td><td align=\"right\">";
    temp += data[0] + "</td><td align=\"right\">&nbsp;</td><td align=\"right\">&nbsp;</td></tr>";
    temp += "<tr><td>" + tr("Gesamtzahl Artikel:") + "</td><td align=\"right\">";
    temp += data[1] + "</td><td align=\"right\">&nbsp;</td><td align=\"right\">&nbsp;</td></tr>";
    temp += "<tr><td>" + tr("Verkaufte Artikel:") + "</td><td align=\"right\"><nobr>";
    temp += data[2] + "</nobr></td><td align=\"right\">" + data[4] + "</td><td align=\"right\">&nbsp;</td></tr>";
    temp += "<tr><td>" + tr("Davon einbehaltene Provision") + " (" + provisionSold +"%):</td>";
    temp += "<td align=\"right\">&nbsp;</td><td align=\"right\">&nbsp;</td><td align=\"right\"><i>" + data[5] + "</i></td></tr>";
    temp += "<tr><td>" + tr("Nicht verkaufte Artikel") + "</td><td align=\"right\">";
    temp += data[3] + "</td><td align=\"right\"><nobr>&nbsp;</nobr></td><td align=\"right\">&nbsp;</td></tr>";
    temp += "<tr><td>" + tr("Davon einbehaltene Artikelgebühr") + " (" + provisionNotSold + " " + currencySymbol + "):</td><td align=\"right\">&nbsp;</td>";
    temp += "<td align=\"right\"><nobr>&nbsp;</td><td align=\"right\"><i>" + data[6] + "</i></td></tr>";
    temp += "<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
    temp += "<tr><td>&nbsp;</td><td align=\"right\">&nbsp;</td><td align=\"right\"><b><nobr>";
    temp += tr("Auszahlung") + ": " + data[7] + "</nobr></b></td><td align=\"right\">&nbsp;</td></tr>";
    temp += "<tr><td>&nbsp;</td><td align=\"right\">&nbsp;</td><td align=\"right\">&nbsp;</td><td align=\"right\"><b><nobr>";
    temp += tr("Erlös") + ": " + data[8] + "</nobr></b></td></tr>";


    temp += "</table></td></tr><tr><td>&nbsp;</td></tr><tr><td>&nbsp;</td></tr></table></td></tr>";

    return temp;

}

QString EventRevenuePrinter::addConfirmation()
{

    QString temp;

    temp = "<tr><td>&nbsp;</td></tr><tr><td><table><tbody><tr><td colspan=\"2`\">";
    temp += tr("Für die Richtigkeit:") + "<br /><br /><br />&nbsp;</td></tr>";
    temp += "<tr><td>________________________________________________</td></tr></tbody></table></td></tr>";

    return temp;

}

QString EventRevenuePrinter::addHtmlDocumentFooter()
{
    QString temp;

    temp = "</table></body></html>";

    return temp;
}


void EventRevenuePrinter::printPrinter(QWidget* parent, QString &serializedData)
{
    iprinter = new QPrinter();

    QPrintDialog printDialog(iprinter,parent);
    if (printDialog.exec() == QDialog::Accepted) {
        print(serializedData);
    }

}

void EventRevenuePrinter::print(QString &serializedData)
{
    QString htmlContent;

    htmlContent += createHtmlHeader();

    if (printLogo)
        htmlContent += addLogo();

    htmlContent += addDocumentHeader();

    htmlContent += addContent(serializedData);


    htmlContent += addConfirmation();
    htmlContent += addHtmlDocumentFooter();

    QTextDocument *document = new QTextDocument();
    document->setHtml(htmlContent);


    document->print(iprinter);

    delete document;
}


void EventRevenuePrinter::setPrintLogo(bool value)
{
    printLogo = value;
}


void EventRevenuePrinter::setCurrencySymbol(const QString &value)
{
    currencySymbol = value;
}


void EventRevenuePrinter::printPdf(QString &serializedData)
{
    iprinter = new QPrinter();
    iprinter->setOutputFileName("printbill.pdf");
    iprinter->setOutputFormat(QPrinter::PdfFormat);

    print(serializedData);

    // This is just temporary until a proper printing class is available.
    QDesktopServices::openUrl(QUrl("printbill.pdf", QUrl::TolerantMode));
}
