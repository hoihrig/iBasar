#ifndef SELLERREGISTRATIONWIDGET_H
#define SELLERREGISTRATIONWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "databaseconnection.h"
#include "seller.h"

namespace Ui {
class SellerRegistrationWidget;
}

class SellerRegistrationWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SellerRegistrationWidget(Databaseconnection *db, QWidget *parent = 0);
    ~SellerRegistrationWidget();
    
private:
    Ui::SellerRegistrationWidget *ui;
    Databaseconnection *data;
    Seller *regseller;

    QStringList findEvents(Databaseconnection *db);

private slots:
    void updateSellerFields();
    void searchSeller();
    void createSeller();
};

#endif // SELLERREGISTRATIONWIDGET_H
