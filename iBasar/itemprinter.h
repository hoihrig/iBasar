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
#include <QPrintDialog>
#include "ean13.h"

class ItemPrinter : public QObject
{
    Q_OBJECT
public:
    explicit ItemPrinter(QObject *parent = 0);
    ~ItemPrinter();
    void setHeaderInfo(QString Info);
    void paginate(QList<QStringList> *pages, QStringList &entries);
    void printPdf(QList<QStringList> pages);
    void print(QWidget *parent, QList<QStringList> pages);
    
signals:
    
public slots:

private:
    QPrinter *iprinter;
    QPainter *ipainter;
    QStringList deserialize(QString serialString);
    int printpages(QList<QStringList> pages);

    QStringList headerinfo;
    int posx;
    int posy;
    int border;
    int lineheight;
    int gap;
    int headergap;
    int entryheight;
    int barcodewidth;
    int barcodeheigth;
};

#endif // ITEMPRINTER_H
