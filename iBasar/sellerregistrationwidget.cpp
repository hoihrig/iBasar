#include "sellerregistrationwidget.h"
#include "ui_sellerregistrationwidget.h"

SellerRegistrationWidget::SellerRegistrationWidget(Databaseconnection *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellerRegistrationWidget)
{
    data = db;

    regseller = new Seller;

    QStringList headerlist;
    headerlist.append("ID");
    headerlist.append("Hersteller");
    headerlist.append("Beschreibung");
    headerlist.append("Size");
    headerlist.append("Preis");

    ui->setupUi(this);

    // Setup the Table Widget
    ui->tableWidget->setHorizontalHeaderLabels(headerlist);
    ui->tableWidget->setColumnWidth(2,250);
    for (int i=0; i<5; i++)
        addRow();

    ui->eventComboBox->addItems(findEvents(db));

    connect(ui->sellersearchbtn,SIGNAL(clicked()),this,SLOT(searchSeller()));
    connect(ui->selleraddbtn,SIGNAL(clicked()),this,SLOT(createSeller()));
    connect(ui->addRowbtn,SIGNAL(clicked()),this,SLOT(addRow()));
    connect(ui->delRowbtn,SIGNAL(clicked()),this,SLOT(deleteRow()));
    connect(ui->savetblbtn,SIGNAL(clicked()),this,SLOT(saveTabletoDB()));
}

SellerRegistrationWidget::~SellerRegistrationWidget()
{
    delete regseller;
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

void SellerRegistrationWidget::updateSellerFields()
{
    if (!regseller->getName().isEmpty())
        ui->nameedit->setText(regseller->getName());

    if (!regseller->getSurname().isEmpty())
        ui->surnameedit->setText(regseller->getSurname());

    if (!regseller->getAddress().isEmpty())
        ui->addressedit->setText(regseller->getAddress());

    if (!regseller->getCity().isEmpty())
        ui->cityedit->setText(regseller->getCity());

    if (!regseller->getPlz().isEmpty())
        ui->plzedit->setText(regseller->getPlz());

    if (!regseller->getEmail().isEmpty())
        ui->emailedit->setText(regseller->getEmail());

    if (!regseller->getPhone().isEmpty())
        ui->phoneedit->setText(regseller->getPhone());

    if (!regseller->getEvent().isEmpty())
        ui->eventComboBox->setCurrentText(regseller->getEvent());

    if (regseller->isComplete())
        ui->tableWidget->setEnabled(true);

}

void SellerRegistrationWidget::searchSeller()
{
    if ((ui->nameedit->text().isEmpty()) || (ui->surnameedit->text().isEmpty()))
    {
        QMessageBox::critical(this,tr("Seller Registration"),tr("To Search you have to specify Name and Surname of the Seller. Cannot search Seller!"));
        return;
    }

    regseller->setName(ui->nameedit->text());
    regseller->setSurname(ui->surnameedit->text());

    if (!regseller->findSeller(data))
        QMessageBox::critical(this,tr("Seller Registration"),tr("Could not find a Seller with that Name!"));

    updateSellerFields();

}

void SellerRegistrationWidget::createSeller()
{
    if ( (ui->nameedit->text().isEmpty()) ||
         (ui->surnameedit->text().isEmpty()) ||
         (ui->addressedit->text().isEmpty()) ||
         (ui->cityedit->text().isEmpty()) ||
         (ui->plzedit->text().isEmpty()) ||
         (ui->emailedit->text().isEmpty()) ||
         (ui->phoneedit->text().isEmpty()) )
    {
        QMessageBox::critical(this,tr("Seller Registration"),tr("One of the required Fields to create a Seller is missing. Cannot create Seller!"));
        return;
    }

    regseller->setName(ui->nameedit->text());
    regseller->setSurname(ui->surnameedit->text());
    regseller->setAddress(ui->addressedit->text());
    regseller->setCity(ui->cityedit->text());
    regseller->setPlz(ui->plzedit->text());
    regseller->setEmail(ui->emailedit->text());
    regseller->setPhone(ui->phoneedit->text());
    regseller->setEvent(ui->eventComboBox->currentText());

    regseller->createSeller(data);

    updateSellerFields();
}

void SellerRegistrationWidget::addRow()
{
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

void SellerRegistrationWidget::deleteRow()
{
    int row = ui->tableWidget->currentRow();

    ui->tableWidget->removeRow(row);
}

void SellerRegistrationWidget::saveTabletoDB()
{

}
