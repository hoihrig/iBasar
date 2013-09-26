#include "sellersearchwidget.h"
#include "ui_sellersearchwidget.h"

#include <QMessageBox>

SellerSearchWidget::SellerSearchWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellerSearchWidget)
{
    ui->setupUi(this);

    connect(ui->cancelbtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->idsearchrbtn,SIGNAL(toggled(bool)),ui->idlineedit,SLOT(setEnabled(bool)));
    connect(ui->namerbtn,SIGNAL(toggled(bool)),ui->namelineedit,SLOT(setEnabled(bool)));
    connect(ui->namerbtn,SIGNAL(toggled(bool)),ui->surnamelineedit,SLOT(setEnabled(bool)));
    connect(ui->searchbtn,SIGNAL(clicked()),this,SLOT(search()));
}

SellerSearchWidget::~SellerSearchWidget()
{
    delete ui;
}

void SellerSearchWidget::search()
{
    if (ui->idsearchrbtn->isChecked())
    {
        if (ui->idlineedit->text().isEmpty()) {
            QMessageBox::critical(this,tr("Seller Search"),tr("Um einen Verkäufer zu suchen eine Kundennummer eingegeben werden!"));
            return;
        }
        else {
            emit searchbyID(ui->idlineedit->text().toInt());
        }
    }

    if (ui->namerbtn->isChecked()) {

        if (ui->namelineedit->text().isEmpty()
                || ui->surnamelineedit->text().isEmpty()) {
            QMessageBox::critical(this,tr("Seller Search"),tr("Um einen Verkäufer zu suchen müssen Vorname und Nachname eingegeben werden!"));
            return;
        }
        else {
            emit searchbyName(ui->surnamelineedit->text() + ", " + ui->namelineedit->text());
        }

    }

    ui->idlineedit->clear();
    ui->surnamelineedit->clear();
    ui->namelineedit->clear();

    this->close();
}
