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

    mwidget = new MainWidget(db);
    mfake = new fakeUI;

    mwidget->setGeometry(ui->stackedWidget->geometry());
    ui->stackedWidget->addWidget(mwidget);

    mfake->setGeometry(ui->stackedWidget->geometry());
    ui->stackedWidget->addWidget(mfake);



    connect(ui->actionAbout_Qt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(ui->actionSettings,SIGNAL(triggered()),this,SLOT(showSettings()));
    connect(ui->toolBox,SIGNAL(currentChanged(int)),this,SLOT(loadWidget(int)));
    connect(this,SIGNAL(updateWidgets()),mwidget,SLOT(updateValues()));
}

MainWindow::~MainWindow()
{
    delete db;
    delete mwidget;
    delete mfake;

    delete ui;
}

void MainWindow::loadWidget(int index)
{
    switch (index)
    {
    case 0:
        emit updateWidgets();
        break;
    default:
        break;
    }

    ui->stackedWidget->setCurrentIndex(index);
}


void MainWindow::showSettings()
{
    Settings sett(settings);

    sett.exec();

    reconnectDb();
    emit updateWidgets();
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
