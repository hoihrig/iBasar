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

    ui->tableWidget->setHorizontalHeaderLabels(headerlist);
    ui->tableWidget->setColumnWidth(2,250);

    ui->eventComboBox->addItems(findEvents(db));

    connect(ui->sellersearchbtn,SIGNAL(clicked()),this,SLOT(searchSeller()));
    connect(ui->selleraddbtn,SIGNAL(clicked()),this,SLOT(createSeller()));
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
