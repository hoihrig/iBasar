#ifndef EVENTMGRWIDGET_H
#define EVENTMGRWIDGET_H

#include <QDialog>
#include <QtWidgets/QMessageBox>
#include "databaseconnection.h"

namespace Ui {
class EventMgrWidget;
}

class EventMgrWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit EventMgrWidget(Databaseconnection *data, QWidget *parent = 0);
    ~EventMgrWidget();
    
private:
    Ui::EventMgrWidget *ui;
    Databaseconnection *db;

private slots:
    void createEventManagerWidget();
};

#endif // EVENTMGRWIDGET_H
