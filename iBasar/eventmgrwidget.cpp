#include "eventmgrwidget.h"
#include "ui_eventmgrwidget.h"

EventMgrWidget::EventMgrWidget(Databaseconnection *data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventMgrWidget)
{
    ui->setupUi(this);

    db = data;

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(createEventManagerWidget()));
}

void EventMgrWidget::createEventManagerWidget()
{
    if (ui->eventnameedit->text().isEmpty())
    {
        QMessageBox::critical(this,QString("iBasar Event Management"),tr("No Event name given. Cannot create Event!"));
        return;
    }

    if (!db->isEstablished())
    {
        QMessageBox::critical(this,QString("iBasar Event Management"),tr("No Connection to Database! Cannot create Event!"));
        return;
    }

    QSqlQuery result;
    QString querycmd;
    int rowid = 0;

    querycmd = "SELECT MAX(ID) FROM `Veranstaltung`";
    db->query(querycmd,result);

    result.next();
    rowid = result.value(0).toInt() + 1;
    result.clear();

    querycmd = "INSERT INTO `Veranstaltung` (ID, Name, Datum) VALUES (" +
            QString::number(rowid) + ", '" +
            ui->eventnameedit->text() + "', '" +
            ui->eventdateedit->dateTime().toString("yyyy-MM-dd") + "');";

    db->query(querycmd,result);


}

EventMgrWidget::~EventMgrWidget()
{
    delete ui;
}
