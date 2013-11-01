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

#include "itemprinter.h"

ItemPrinter::ItemPrinter(QObject *parent) :
    QObject(parent)
{

}

ItemPrinter::~ItemPrinter()
{
    if (ipainter != 0)
        delete ipainter;

    if (iprinter != 0)
        delete iprinter;

}

void ItemPrinter::print(QWidget* parent,QList<QStringList> pages)
{
    iprinter = new QPrinter();

    QPrintDialog printDialog(iprinter,parent);
    if (printDialog.exec() == QDialog::Accepted) {
        ipainter = new QPainter(iprinter);

        border = 10;
        lineheight = 20;
        gap = 10;
        headergap = 30;
        entryheight = 300;
        barcodewidth = 240;
        barcodeheigth = 100;

        printpages(pages);
    }

}

void ItemPrinter::printPdf(QList<QStringList> pages)
{
    iprinter = new QPrinter(QPrinter::HighResolution);
    iprinter->setOutputFileName("print.pdf");
    iprinter->setOutputFormat(QPrinter::PdfFormat);

    ipainter = new QPainter(iprinter);

    border = 100;
    lineheight = 200;
    gap = 100;
    headergap = 300;
    entryheight = 3000;
    barcodewidth = 2400;
    barcodeheigth = 1000;

    printpages(pages);

    // This is just temporary until a proper printing class is available.
    QDesktopServices::openUrl(QUrl("print.pdf", QUrl::TolerantMode));

}

QStringList ItemPrinter::deserialize(QString serialString)
{
    return serialString.split(":::");
}

void ItemPrinter::setHeaderInfo(QString Info)
{
    if (!Info.isEmpty())
        headerinfo = deserialize(Info);
}

void ItemPrinter::paginate(QList<QStringList> *pages, QStringList &entries)
{
    QStringList temp;
    int pageindex = 0;

    for (int i=0; i < entries.size();i++) {

        if ( ((int)(i/12)) >= 1) {
            pages->append(temp);
            pageindex++;
            temp.clear();
        }

        temp.append(entries[i]);
    }

    pages->append(temp);
}

int ItemPrinter::printpages(QList<QStringList> pages)
{
    if (!ipainter)
        return false;

    QFont serifFont("Times", 10, QFont::Bold);
    QFont priceFont("Times",16, QFont::Bold);
    int width = iprinter->width();

    ipainter->begin(iprinter);

    ipainter->translate(0,100);
    ipainter->setFont(serifFont);
    ipainter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    ipainter->setBrush(Qt::SolidPattern);

    posx = border;
    posy = border;

    for (int i = 0; i < pages.size(); i++) {

        // Create a new page for each List except for the fist one
        if (i>0)
            iprinter->newPage();

        // Print Header on each Page
        for (int j = 0; j < headerinfo.size(); j++) {
            ipainter->setFont(serifFont);
            QRect textRect = ipainter->boundingRect(posx,posy,width,20,Qt::TextWordWrap, headerinfo[j]);
            ipainter->drawText(textRect,Qt::TextWordWrap, headerinfo[j]);
            posy += lineheight;
        }

        posy += headergap;

        //Print Items for each page
        for (int k = 0; k < pages[i].size(); k++) {

            // If my next Itemlabel would be outside the right side of the page, advance a row
            if (posx + ((width/3)-border) > width) {
                posx = border;
                posy += entryheight;

            }

            // Deserialize the data
            QStringList entrylist = deserialize(pages[i][k]);
            int rely = 0;

            // Set Font for the itemtext and print itemtext
            ipainter->setFont(serifFont);
            QRect textRect = ipainter->boundingRect(posx,posy + rely,width/3,20,Qt::TextWordWrap, entrylist[0]);
            ipainter->drawText(textRect,Qt::TextWordWrap, entrylist[0]);
            rely += (2*lineheight); // Advance Relative-y before printing the barcode

            // Prepend zeros to get a proper EAN13 barcode
            QString prodnr = QString("%1").arg(entrylist[1], 12, QChar('0')).toUpper();

            // Draw the EAN-13 Barcode using the helper class
            EAN13 code(prodnr);
            code.draw(QRectF(posx, posy + rely, barcodewidth, barcodeheigth), *ipainter);
            rely += barcodeheigth;

            // Print the product number in front of the price
            textRect = ipainter->boundingRect(posx,(posy + rely),width/3,20,Qt::AlignLeft,prodnr);
            ipainter->drawText(textRect,Qt::AlignLeft,prodnr);
            rely += lineheight;

            // Print the Price in a little bit bigger font.
            ipainter->setFont(priceFont);
            textRect = ipainter->boundingRect(posx,(posy + rely),barcodewidth,40,Qt::AlignRight, entrylist[2] + QString(" EUR"));
            ipainter->drawText(textRect,Qt::AlignRight, entrylist[2] + QString(" EUR"));

            // Advance to the next Label in the same row
            posx += width/3;
        }

        // A new Row has started, so reset to the border
        posx = border;
        posy = border;
    }

    ipainter->end();

    return true;
}
