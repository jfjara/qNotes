#ifndef NOTIFYDIALOG_H
#define NOTIFYDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QDesktopWidget>
#include <QIcon>

namespace Ui {
class NotifyDialog;
}

class NotifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotifyDialog(QWidget *parent = 0, QString message = "", int orderDialogInScreen = 0);
    ~NotifyDialog();

    void resizeAndMove(int orderInScreen);


    long id = 0;
    int orderDialogInScreen = 0;

public slots:
    void closeWindow();

signals:

    void closeNotifyWindow(long id);

private:
    Ui::NotifyDialog *ui;
    QIcon* closeIcon = nullptr;
};

#endif // NOTIFYDIALOG_H
