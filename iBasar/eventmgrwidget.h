#ifndef EVENTMGRWIDGET_H
#define EVENTMGRWIDGET_H

#include <QDialog>
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
    void createEvent();
};

#endif // EVENTMGRWIDGET_H
