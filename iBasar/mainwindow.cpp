#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new QSettings("Ibasar","Ibasar");
    db = new Databaseconnection();

    db->readDbSettings(settings);

    connect(ui->actionAbout_Qt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(ui->actionSettings,SIGNAL(triggered()),this,SLOT(showSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSettings()
{
    Settings sett(settings);

    sett.exec();

    reconnectDb();
}

void MainWindow::reconnectDb()
{
    if (db)
    {
        if (db->isEstablished())
            db->close();

        db->readDbSettings(settings);

        if (!db->open())
            qWarning("Could not Open Database");
    }
}

void MainWindow::connectDb()
{
    if (db)
    {
        if (!db->isEstablished())
            if (!db->open())
                qWarning("Could not Open Database");
    }
    else
    {
        qWarning("Database Object does not exist yet!");
    }
}

void MainWindow::aboutQt()
{
    QApplication::aboutQt();
}
