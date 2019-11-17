#include "rememberdialog.h"
#include <QApplication>
#include "mainapplication.h"
#include "windows.h"

int main(int argc, char *argv[])
{
    MainApplication a(argc, argv);
    ReMemberDialog dialog;
    a.mainDialog = &dialog;
    return a.exec();
}
