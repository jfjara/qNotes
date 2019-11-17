#include "rememberwindow.h"
#include "ui_rememberwindow.h"

ReMemberWindow::ReMemberWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReMemberWindow)
{
    ui->setupUi(this);
}

ReMemberWindow::~ReMemberWindow()
{
    delete ui;
}
