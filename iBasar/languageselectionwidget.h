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

#ifndef LANGUAGESELECTIONWIDGET_H
#define LANGUAGESELECTIONWIDGET_H

#include <QDialog>

namespace Ui {
class LanguageSelectionWidget;
}

class LanguageSelectionWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LanguageSelectionWidget(QWidget *parent = 0);
    ~LanguageSelectionWidget();

private:
    Ui::LanguageSelectionWidget *ui;
    void changeEvent(QEvent *event);
private slots:
    void languageSelected();

signals:
    void languageChanged(QString language);
};

#endif // LANGUAGESELECTIONWIDGET_H
