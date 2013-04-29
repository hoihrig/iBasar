/*
#################################################################################################
#   Copyright 2013 Holger Ihrig                                                                 #
#                                                                                               #
#   This file is part of iBasar.                                                                #
#                                                                                               #
#   iBasar is free software: you can redistribute it and/or modify it under the terms of        #
#   the GNU General Public License as published by the Free Software Foundation,                #
#   either version 3 of the License, or (at your option) any later version.                     #
#   Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;         #
#   without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   #
#   See the GNU General Public License for more details.                                        #
#                                                                                               #
#   You should have received a copy of the GNU General Public License along with iBasar.        #
#   If not, see http://www.gnu.org/licenses/.                                                   #
#################################################################################################
*/

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



