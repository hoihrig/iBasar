#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtGui>

#include "ui_settingsdialog.h"

class SettingsDialog : public QDialog, public Ui::SettingsDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QSettings *settings, QWidget *parent = 0);

private:
    QSettings *dialogsettings;
    Ui::SettingsDialog *ui;
    
signals:
    
public slots:
    void saveAndQuit();
    
};

#endif // SETTINGSDIALOG_H
