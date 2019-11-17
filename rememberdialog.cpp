#include "rememberdialog.h"
#include "ui_rememberdialog.h"

ReMemberDialog::ReMemberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReMemberDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    createActions();
    createTrayIcon();
    createConnects();

    trayIcon->show();
    ui->plainTextEdit->installEventFilter(this);
    this->installEventFilter(this);

    ui->hourText->setFocus();
    createStyle();
    defineWindowPosition();

    if (!RegisterHotKey(HWND(winId()), 0, MOD_ALT | MOD_CONTROL, 0x4D))
    {
        QMessageBox::warning(this, "Warning", "Can't register hotkey ALT+CTRL+M");
    }

}

ReMemberDialog::~ReMemberDialog()
{
    delete ui;    
    delete quitAction;
    delete aboutAction;
    delete minimizeAction;
    delete restoreAction;
    delete trayIconMenu;
}

void ReMemberDialog::getFocus()
{
    this->setFocus();
    ui->hourText->setFocus();
}

void ReMemberDialog::defineWindowPosition()
{
    int x = QApplication::desktop()->screen()->rect().width() - this->rect().width();
    int y = QApplication::desktop()->screen()->rect().height() - this->rect().height() - 40;
    this->move(x, y);
}

void ReMemberDialog::createConnects()
{
    connect(NotifyManagement::getInstance(), SIGNAL(send(Notify*)), this, SLOT(showNotify(Notify*)));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void ReMemberDialog::createStyle()
{
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QGroupBox { background-color: rgb(43,43,44);"
                        "border-style: outset;"
                        "border-radius: 10px; }"
                  "QLabel { color : white; }"
                  "QLineEdit {color : rgb {43,43,44}}"
                  "QPlainTextEdit { color : rgb(43, 43, 44);");
}

bool ReMemberDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->plainTextEdit)
    {
        if(event->type() == QKeyEvent::KeyPress)
        {
            QKeyEvent * ke = static_cast<QKeyEvent*>(event);
            if(ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter)
            {
                if (validateTimeExpression(ui->hourText->text())
                        && validateMessage(ui->plainTextEdit->toPlainText())) {
                    createNotify();
                    hide();
                } else {
                    //TODO: poner de rojo el campo
                }
                return true;
            }
        }
        return false;
    }
    else
    {        
        return false;
    }
}

void ReMemberDialog::showNotify(Notify* notify)
{    
    NotifyDialog* dialog = new NotifyDialog(this, notify->message, notifyDialogList.size());
    dialog->show();
    dialog->resizeAndMove(notifyDialogList.size());
    notifyDialogList.append(dialog);
    connect(dialog, SIGNAL(closeNotifyWindow(long)), this, SLOT(reorderNotifyDialogs(long)));
    NotifyManagement::getInstance()->clean(notify);

    if (!soundPlayer.isPlaying()) {
        soundPlayer.play();
    }

}

void ReMemberDialog::removeDialogFromList(long id)
{
    for (int i = 0; i < notifyDialogList.size(); i++) {
        if (notifyDialogList.at(i)->id == id) {
            NotifyDialog* dialog = notifyDialogList.at(i);
            notifyDialogList.removeAt(i);
            break;
        }
    }
}

void ReMemberDialog::reorderNotifyDialogs(long idDialogToRemove)
{
    removeDialogFromList(idDialogToRemove);
    for (int i = 0; i < notifyDialogList.size(); i++) {
        notifyDialogList.at(i)->resizeAndMove(i);
    }
}

bool ReMemberDialog::validateTimeExpression(QString text)
{
    if (text.trimmed() == "") {
        return false;
    }

    if (TimeExpressionUtils::getType(text) == UNKNOWN_FORMAT) {
        return false;
    }

    return true;
}

bool ReMemberDialog::validateMessage(QString text)
{
    if (text.trimmed() == "") {
        return false;
    }
    return true;
}

void ReMemberDialog::createNotify()
{    
    NotifyManagement::getInstance()->add(ui->hourText->text(), ui->plainTextEdit->toPlainText());
}

void ReMemberDialog::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
//    trayIconMenu->addAction(minimizeAction);
//    trayIconMenu->addAction(restoreAction);
//    trayIconMenu->addSeparator();
    trayIconMenu->addAction(aboutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon(":resources/brain.png");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
}

void ReMemberDialog::clearFields()
{
    ui->hourText->clear();
    ui->plainTextEdit->clear();
}

bool ReMemberDialog::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        showNormal();        
        clearFields();
        getFocus();
        return true;
    }
    return false;
}

void ReMemberDialog::createActions()
{
//    minimizeAction = new QAction(tr("Mi&nimize"), this);
//    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

//    restoreAction = new QAction(tr("&Restore"), this);
//    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutWindow()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void ReMemberDialog::showAboutWindow()
{
    creditsDialog = new CreditsDialog();
    connect(creditsDialog, SIGNAL(rejected()), this, SLOT(closeCreditsWindow()));
    creditsDialog->show();
}

void ReMemberDialog::closeCreditsWindow()
{
    creditsDialog->hide();
    delete creditsDialog;
    creditsDialog = nullptr;
}


void ReMemberDialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

