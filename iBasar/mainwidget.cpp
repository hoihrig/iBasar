#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(Databaseconnection *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidget)
{
    ui->setupUi(this);
    data = db;

    updateValues();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::updateDbStatus()
{
    ui->dblbl->setText(data->getHostname());

    if (data->isEstablished())
        ui->connectlbl->setText("true");
    else
        ui->connectlbl->setText("false");
}

void MainWidget::updateItemStatus()
{
    QSqlQuery query;

    data->query("Select COUNT(ID) from `Verkäufer`",query);
    query.next();
    ui->sellerslbl->setText(query.value(0).toString());
    query.clear();

    data->query("Select COUNT(ID) from `Veranstaltung`",query);
    query.next();
    ui->eventslbl->setText(query.value(0).toString());

}

void MainWidget::updateValues()
{
    updateDbStatus();

    updateItemStatus();
}
