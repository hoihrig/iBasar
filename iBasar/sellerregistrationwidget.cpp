#include "sellerregistrationwidget.h"
#include "ui_sellerregistrationwidget.h"

SellerRegistrationWidget::SellerRegistrationWidget(Databaseconnection *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellerRegistrationWidget)
{
    data = db;

    QStringList headerlist;
    headerlist.append("ID");
    headerlist.append("Hersteller");
    headerlist.append("Beschreibung");
    headerlist.append("Size");
    headerlist.append("Preis");
    headerlist.append("Aktiv");
    headerlist.append("Verkauft");

    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderLabels(headerlist);
    ui->tableWidget->setColumnWidth(2,250);

    ui->eventComboBox->addItems(findEvents(db));
}

SellerRegistrationWidget::~SellerRegistrationWidget()
{
    delete ui;
}

QStringList SellerRegistrationWidget::findEvents(Databaseconnection *db)
{
    QStringList eventslist;

    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT Name from `Veranstaltung`";

    db->query(querycmd,result);

    while (result.next())
    {
        eventslist.append(result.value(0).toString());
    }

    return eventslist;
}
