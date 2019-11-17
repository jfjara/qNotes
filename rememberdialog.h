#ifndef REMEMBERDIALOG_H
#define REMEMBERDIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QTimer>
#include <QFocusEvent>
#include <QDateTime>
#include <QList>
#include "notifydialog.h"
#include "notify.h"
#include "notifymanagement.h"
#include "soundplayer.h"
#include "creditsdialog.h"
#include "windows.h"

namespace Ui {
class ReMemberDialog;
}

class ReMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReMemberDialog(QWidget *parent = 0);
    ~ReMemberDialog();

    void getFocus();
    bool eventFilter(QObject *watched, QEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showNotify(Notify* notify);
    void createNotify();
    void reorderNotifyDialogs(long idDialogToRemove);
    void showAboutWindow();
    void closeCreditsWindow();

private:
    Ui::ReMemberDialog *ui;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    CreditsDialog* creditsDialog = nullptr;

    QAction* minimizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QAction* aboutAction;

    QList<NotifyDialog*> notifyDialogList;
    SoundPlayer soundPlayer;

private:
    void createTrayIcon();
    void createActions();
    void createConnects();
    void createStyle();
    void defineWindowPosition();
    void removeDialogFromList(long id);
    void clearFields();
    bool validateTimeExpression(QString text);
    bool validateMessage(QString text);

};

#endif // REMEMBERDIALOG_H
