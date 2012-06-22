#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtSql>
#include "databaseconnection.h"

namespace Ui {
class Mainwidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(Databaseconnection *db,QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::Mainwidget *ui;
    Databaseconnection *data;

    void updateDbStatus();
    void updateItemStatus();

public slots:
    void updateValues();
};

#endif // MAINWIDGET_H
