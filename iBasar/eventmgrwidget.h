#ifndef EVENTMGRWIDGET_H
#define EVENTMGRWIDGET_H

#include <QDialog>
<<<<<<< HEAD
#include <QtWidgets/QMessageBox>
=======
>>>>>>> HEAD@{6}
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
<<<<<<< HEAD
    void createEventManagerWidget();
=======
    void createEvent();
>>>>>>> HEAD@{6}
};

#endif // EVENTMGRWIDGET_H
