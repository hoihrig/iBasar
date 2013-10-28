#ifndef REVENUEPRINTER_H
#define REVENUEPRINTER_H

#include <QObject>
#include <QStringList>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QUrl>
#include <QDesktopServices>

class EventRevenuePrinter : public QObject
{
    Q_OBJECT
public:
    explicit EventRevenuePrinter(QObject *parent = 0);

    void printPdf(QString &serializedData);
    void setCurrencySymbol(const QString &value);
    void setPrintLogo(bool value);
    void printPrinter(QWidget *parent, QString &serializedData);
    void setEventDate(QString eventDate);
    void setEventLocation(QString eventLocation);
    void setEventName(QString eventName);
    void setProvisionSold(const QString &value);
    void setProvisionNotSold(const QString &value);
    ~EventRevenuePrinter();

signals:

public slots:

private:
    QPrinter *iprinter;
    QStringList headerinfo;
    QString eventName;
    QString currencySymbol;
    QString provisionSold;
    QString provisionNotSold;
    bool printLogo;

    void print(QString &serializedData);
    QString addLogo();
    QString createHtmlHeader();
    QStringList deserialize(QString serialString);
    QString addHtmlDocumentFooter();
    QString addDocumentHeader();
    QString addContent(QString serializedData);
    QString addConfirmation();
};

#endif // REVENUEPRINTER_H
