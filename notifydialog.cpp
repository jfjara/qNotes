#include "notifydialog.h"
#include "ui_notifydialog.h"
#include "colorutils.h"

NotifyDialog::NotifyDialog(QWidget *parent, QString message, int orderDialogInScreen) :
    QDialog(parent),
    ui(new Ui::NotifyDialog)
{
    id = QDateTime::currentDateTime().toMSecsSinceEpoch();
    this->orderDialogInScreen = orderDialogInScreen;
    ui->setupUi(this);

    ui->messageLabel->setText(message);

    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    QString color = ColorUtils::extractColor(message);
    if (color == nullptr) {
        color = "rgb(43,43,44)";        
    }
    QString fontColor = ColorUtils::getFontColor(color);
    closeIcon = new QIcon(ColorUtils::getCloseIcon(color));

    QString styles = "QGroupBox { background-color: $color;"
                     "border-style: outset;"
                     "border-radius: 10px; }"
               "QLabel { color :  $fontColor; }"
               "QPushButton { background-color: transparent;"
                       "color: $fontColor;"
                       "border-style: outset;}";

    styles = styles.replace("$color", color);
    styles = styles.replace("$fontColor", fontColor);
    ui->closeButton->setIcon(*closeIcon);

    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet(styles);

    resizeAndMove(orderDialogInScreen);
}

void NotifyDialog::resizeAndMove(int orderInScreen)
{
    int linespacesBetweenDialogs = 0;
    int sumPixelsPreviousDialogs =(orderInScreen) * this->rect().height();

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    int x = QApplication::desktop()->screen()->rect().width() - ui->notifyGroupBox->rect().width() - 25;
    int y = QApplication::desktop()->screen()->rect().height() - (ui->notifyGroupBox->rect().height() -10) - sumPixelsPreviousDialogs - linespacesBetweenDialogs - 70;
    this->move(x, y);
    this->repaint();
}

NotifyDialog::~NotifyDialog()
{
    delete ui;
    delete closeIcon;
}

void NotifyDialog::closeWindow()
{
    emit closeNotifyWindow(id);
    hide();
}
