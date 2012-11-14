#ifndef SELLERREGISTRATIONWIDGET_H
#define SELLERREGISTRATIONWIDGET_H

#include <QWidget>

namespace Ui {
class SellerRegistrationWidget;
}

class SellerRegistrationWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SellerRegistrationWidget(QWidget *parent = 0);
    ~SellerRegistrationWidget();
    
private:
    Ui::SellerRegistrationWidget *ui;
};

#endif // SELLERREGISTRATIONWIDGET_H
