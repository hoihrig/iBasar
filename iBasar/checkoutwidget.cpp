#include "checkoutwidget.h"
#include "ui_checkoutwidget.h"

CheckoutWidget::CheckoutWidget(Databaseconnection *db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckoutWidget)
{
    data = db;

    ui->setupUi(this);

    ui->itemnumbertextbox->setFocus();

    connect(ui->itemnumbertextbox,SIGNAL(textChanged(QString)),this,SLOT(itemNumberTextChanged(QString)));
    connect(ui->itemnumbertextbox,SIGNAL(returnPressed()),this,SLOT(itemNumberReturnPressed()));
}

CheckoutWidget::~CheckoutWidget()
{
    delete ui;
}

void CheckoutWidget::itemNumberReturnPressed()
{
    if(ui->itemnumbertextbox->text().size() == 12)
        processItem(ui->itemnumbertextbox->text());
}

void CheckoutWidget::getFocus()
{
    ui->itemnumbertextbox->setFocus();
}

void CheckoutWidget::itemNumberTextChanged(QString itemnumber)
{
    if(itemnumber.size() == 12)
        processItem(itemnumber);
}

void CheckoutWidget::processItem(QString itemnumber)
{
    SalesItem item;

    if (item.findItem(data, itemnumber.toInt()))
    {
        // Create a Row for each Item and load values of SalesItem
        addRow();

        int row = ui->tableWidget->rowCount() - 1;

        ui->tableWidget->item(row,0)->setText(QString::number(item.getID()));
        ui->tableWidget->item(row,1)->setText(item.getManufacturer());
        ui->tableWidget->item(row,2)->setText(item.getDescription());
        ui->tableWidget->item(row,3)->setText(item.getItemSize());
        ui->tableWidget->item(row,4)->setText(item.getPrice());
    }

    salesItemList.append(item.getID());

    ui->totalpricelabel->setText(QString::number(calculateTotalPrice()) + " €");

    ui->itemnumbertextbox->clear();

}

float CheckoutWidget::calculateTotalPrice()
{
    float totalPrice = 0.0;
    int tablesize = ui->tableWidget->rowCount();

    for(int i=0; i < tablesize; i++)
    {
        totalPrice += ui->tableWidget->item(i,4)->text().toFloat();
    }
    return totalPrice;
}

void CheckoutWidget::addRow()
{
    QStringList headerlist;
    headerlist.append("ID");
    headerlist.append("Hersteller");
    headerlist.append("Beschreibung");
    headerlist.append("Size");
    headerlist.append("Preis");

    ui->tableWidget->setHorizontalHeaderLabels(headerlist);
    ui->tableWidget->setColumnWidth(2,250);

    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setFlags(item0->flags() ^ Qt::ItemIsEditable);
    ui->tableWidget->setItem(row, 0, item0);

    QTableWidgetItem *item1 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 1, item1);

    QTableWidgetItem *item2 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 2, item2);

    QTableWidgetItem *item3 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 3, item3);

    QTableWidgetItem *item4 = new QTableWidgetItem;
    ui->tableWidget->setItem(row, 4, item4);
}
