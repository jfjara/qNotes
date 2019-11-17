#ifndef CREDITSDIALOG_H
#define CREDITSDIALOG_H

#include <QDialog>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>

namespace Ui {
class CreditsDialog;
}

class CreditsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreditsDialog(QWidget *parent = 0);
    ~CreditsDialog();

public slots:
    void onClose();

signals:
    void closeWindow();

private:
    Ui::CreditsDialog *ui;
};

#endif // CREDITSDIALOG_H
