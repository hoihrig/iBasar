#include "labelprintwidget.h"
#include "ui_labelprintwidget.h"

LabelPrintWidget::LabelPrintWidget(Databaseconnection *data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Labelprintwidget)
{
    ui->setupUi(this);

    if (data != 0)
        db = data;

    ui->eventcombobox->addItems(findEvents(db));

    connect(ui->eventcombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateSellers(int)));

    emit ui->eventcombobox->currentIndexChanged(0);
}

LabelPrintWidget::~LabelPrintWidget()
{
    delete ui;
}

QStringList LabelPrintWidget::findEvents(Databaseconnection *db)
{
    QStringList eventslist;

    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT Name from `Veranstaltung`";

    db->query(querycmd, result);

    while (result.next())
    {
        eventslist.append(result.value(0).toString());
    }

    return eventslist;
}

QStringList LabelPrintWidget::findSellers(Databaseconnection *db)
{
    QStringList sellerlist;

    QSqlQuery result;
    QString querycmd;

    querycmd = "SELECT ID from `Veranstaltung` WHERE Name='" + ui->eventcombobox->currentText() + "'";
    db->query(querycmd, result);
    result.next();

    querycmd = "SELECT Nachname, Vorname from `Verkäufer` WHERE Veranstaltung =" + result.value(0).toString();
    db->query(querycmd,result);

    while (result.next())
    {
        sellerlist.append(result.value(0).toString() + ", " + result.value(1).toString());
    }

    return sellerlist;
}

void LabelPrintWidget::updateSellers(int index)
{
    Q_UNUSED(index);

    ui->sellercombobox->addItems(findSellers(db));

}

void LabelPrintWidget::printlabel()
{
// TODO: Write a Class that Draws to a surface and writes that as PDF
}
