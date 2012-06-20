#include "settingsdialog.h"


SettingsDialog::SettingsDialog(QSettings *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    setupUi(this);

    dialogsettings = settings;

    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(saveAndQuit()));
    connect(ui->abortButton,SIGNAL(clicked()),this,SLOT(close()));
}

void SettingsDialog::saveAndQuit()
{
    if (!ui->inputhostname->text().isEmpty())
        dialogsettings->setValue("DbHostname",ui->inputhostname->text());
    if (!ui->inputdbname->text().isEmpty())
        dialogsettings->setValue("DbName",ui->inputdbname->text());
    if (!ui->inputuser->text().isEmpty())
        dialogsettings->setValue("DbUser",ui->inputuser->text());
    if (!ui->inputpasswd->text().isEmpty())
        dialogsettings->setValue("DbPasswd",ui->inputpasswd->text());

    this->close();
}



