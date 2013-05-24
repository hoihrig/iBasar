#ifndef LABELPRINTWIDGET_H
#define LABELPRINTWIDGET_H

#include <QDialog>
#include <QStringList>
#include "databaseconnection.h"

namespace Ui {
class Labelprintwidget;
}

class LabelPrintWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit LabelPrintWidget(Databaseconnection *data, QWidget *parent = 0);
    ~LabelPrintWidget();
    
private:
    Ui::Labelprintwidget *ui;
    Databaseconnection *db;
    QStringList findEvents(Databaseconnection *db);
    QStringList findSellers(Databaseconnection *data);

private slots:
    void printlabel();
    void updateSellers(int index);
};

#endif // LABELPRINTWIDGET_H
