#ifndef SELLERSEARCHWIDGET_H
#define SELLERSEARCHWIDGET_H

#include <QDialog>

namespace Ui {
class SellerSearchWidget;
}

class SellerSearchWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SellerSearchWidget(QWidget *parent = 0);
    ~SellerSearchWidget();

private slots:
    void search();
private:
    Ui::SellerSearchWidget *ui;

signals:
    void searchbyID(int);
    void searchbyName(QString);
};

#endif // SELLERSEARCHWIDGET_H
