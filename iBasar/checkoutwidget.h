#ifndef CHECKOUTWIDGET_H
#define CHECKOUTWIDGET_H

#include <QWidget>
#include "databaseconnection.h"
#include "salesitem.h"

namespace Ui {
class CheckoutWidget;
}

class CheckoutWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CheckoutWidget(Databaseconnection *db, QWidget *parent = 0);
    ~CheckoutWidget();
    



public slots:
    void itemNumberTextChanged(QString itemnumber);
    void itemNumberReturnPressed();
    void getFocus();

private:
    Ui::CheckoutWidget *ui;
    Databaseconnection *data;
    QList<int> salesItemList;

    void addRow();
    void processItem(QString itemnumber);
    float calculateTotalPrice();
};

#endif // CHECKOUTWIDGET_H
