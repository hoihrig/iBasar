#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtGui>

#include "ui_settingsdialog.h"

class Settings : public QDialog, public Ui::SettingsDialog
{
    Q_OBJECT
public:
    explicit Settings(QSettings *settings, QWidget *parent = 0);


private:
    QSettings *dialogsettings;

    void readSettings();
    
signals:
    
public slots:
    void save();
    
};

#endif // SETTINGSDIALOG_H
