#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "databaseconnection.h"
#include "settings.h"

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




private:
    void connectDb();
    void reconnectDb();

    QSettings *settings;
    Ui::MainWindow *ui;
    Databaseconnection *db;


public slots:
    void aboutQt();
    void showSettings();
};

#endif // MAINWINDOW_H
