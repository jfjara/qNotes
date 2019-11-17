#ifndef REMEMBERWINDOW_H
#define REMEMBERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReMemberWindow;
}

class ReMemberWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReMemberWindow(QWidget *parent = 0);
    ~ReMemberWindow();

private:
    Ui::ReMemberWindow *ui;
};

#endif // REMEMBERWINDOW_H
