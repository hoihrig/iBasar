#ifndef ITEMPRINTER_H
#define ITEMPRINTER_H

#include <QObject>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QTextDocument>
#include <QDebug>
#include "ean13.h"

class ItemPrinter : public QObject
{
    Q_OBJECT
public:
    explicit ItemPrinter(QObject *parent = 0);
    ~ItemPrinter();
    void setHeaderInfo(QString Info);
    void paginate(QList<QStringList> *pages, QStringList &entries);
    int print(QList<QStringList> pages);

    
signals:
    
public slots:

private:
    QPrinter *iprinter;
    QPainter *ipainter;
    QStringList deserialize(QString serialString);

    QStringList headerinfo;
    int posx;
    int posy;
    static const int border = 100;
    static const int lineheight = 200;
    static const int gap = 100;
    static const int headergap = 300;
    static const int entryheight = 3000;
    static const int barcodewidth = 2400;
    static const int barcodeheigth = 1000;
};

#endif // ITEMPRINTER_H
