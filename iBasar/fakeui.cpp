#include "fakeui.h"
#include "ui_fakeui.h"

fakeUI::fakeUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fakeUI)
{
    ui->setupUi(this);
}

fakeUI::~fakeUI()
{
    delete ui;
}
