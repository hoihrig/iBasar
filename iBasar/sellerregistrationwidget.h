#ifndef SELLERREGISTRATIONWIDGET_H
#define SELLERREGISTRATIONWIDGET_H

#include <QWidget>
#include "databaseconnection.h"

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

    QStringList findEvents(Databaseconnection *db);
};

#endif // SELLERREGISTRATIONWIDGET_H
