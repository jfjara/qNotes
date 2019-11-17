#include "creditsdialog.h"
#include "ui_creditsdialog.h"

CreditsDialog::CreditsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditsDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);
    int x = (QApplication::desktop()->screen()->rect().width() - this->width()) / 2;
    int y = (QApplication::desktop()->screen()->rect().height() - this->height()) / 2;
    this->move(x, y);
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(onClose()));
}

CreditsDialog::~CreditsDialog()
{
    delete ui;
}

void CreditsDialog::onClose()
{
    this->hide();
    emit closeWindow();
}
