/** EAN13
  *
  * A class to encode and draw EAN-13 barcodes.
  *
  * Technical information and inspiration from rainman_63 whose article can be found
  * at http://www.codeproject.com/KB/graphics/ean_13_barcodes.aspx. Please give credit
  * if you use this code.
  * Wiki article at http://en.wikipedia.org/wiki/European_Article_Number
  *
  **/

#ifndef EAN13_H
#define EAN13_H

#include <QtGlobal>
#include <QStringList>
#include <QImage>

class EAN13
{
public:
    EAN13(const QString &code);

public slots:
    void draw(const QRectF &rect, QPainter &painter);
    void setBarcode(const QString &code);

private:
    QRectF *codeRect;				// bounds of this device

    QStringList LCode;
    QStringList GCode;
    QStringList RCode;
    QStringList Parity;
    QString quietZone;
    QString leadTail;
    QString separator;
    QString checksumDigit;
    qreal nominalWidth;
    qreal nominalHeight;
    qreal nominalFontSize;

    QString barcode;

    void calculateChecksumDigit();
    QString convertToDigitPattern(QString number, QStringList &pattern);
    QString convertLeftPattern(QString left);
    QString calculateCountryCode(int index, QString left);
};

#endif // EAN13_H
