#include "settings.h"
#include <QDebug>

Settings::Settings(QSettings *settings, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    dialogsettings = settings;

    readSettings();

    connect(okButton,SIGNAL(clicked()),this,SLOT(save()));
    connect(abortButton,SIGNAL(clicked()),this,SLOT(close()));
}

void Settings::readSettings()
{
    if (!dialogsettings->value("DbHostname").isNull())
        inputhostname->setText(dialogsettings->value("DbHostname").toString());
    if (!dialogsettings->value("DbName").isNull())
        inputdbname->setText(dialogsettings->value("DbName").toString());
    if (!dialogsettings->value("DbUser").isNull())
        inputuser->setText(dialogsettings->value("DbUser").toString());
    if (!dialogsettings->value("DbPasswd").isNull())
        inputpasswd->setText(dialogsettings->value("DbPasswd").toString());
}

void Settings::save()
{
    if (!inputhostname->text().isEmpty())
        dialogsettings->setValue("DbHostname",inputhostname->text());
    if (!inputdbname->text().isEmpty())
        dialogsettings->setValue("DbName",inputdbname->text());
    if (!inputuser->text().isEmpty())
        dialogsettings->setValue("DbUser",inputuser->text());
    if (!inputpasswd->text().isEmpty())
        dialogsettings->setValue("DbPasswd",inputpasswd->text());

    close();

}



