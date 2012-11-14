#include "sellerregistrationwidget.h"
#include "ui_sellerregistrationwidget.h"

SellerRegistrationWidget::SellerRegistrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellerRegistrationWidget)
{
    ui->setupUi(this);
}

SellerRegistrationWidget::~SellerRegistrationWidget()
{
    delete ui;
}
