#ifndef FAKEUI_H
#define FAKEUI_H

#include <QWidget>

namespace Ui {
class fakeUI;
}

class fakeUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit fakeUI(QWidget *parent = 0);
    ~fakeUI();
    
private:
    Ui::fakeUI *ui;
};

#endif // FAKEUI_H
