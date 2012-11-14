#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QSettings>
#include "databaseconnection.h"
#include "settings.h"
#include "mainwidget.h"
#include "fakeui.h"
#include "eventmgrwidget.h"
#include "sellerregistrationwidget.h"

namespace Ui {
    class MainWindow;
    class SettingsDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void updateWidgets();

private:
    void connectDb();
    void reconnectDb();

    QSettings *settings;
    Ui::MainWindow *ui;
    Databaseconnection *db;

    // Here are all the Widgets loaded by the StackedWidget
    MainWidget *mwidget;
    fakeUI *mfake;
    SellerRegistrationWidget *msellerwidget;


public slots:
    void aboutQt();
    void showSettings();
    void showEventManagement();
    void loadWidget(int index);
};

#endif // MAINWINDOW_H
