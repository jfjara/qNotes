#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QApplication>
#include <QEvent>
#include <QObject>
#include "rememberdialog.h"
#include <QDebug>

class MainApplication : public QApplication
{
    Q_OBJECT
public:
    MainApplication( int argc, char * argv[] )
        : QApplication( argc, argv )
        {}


    ReMemberDialog* mainDialog;

    bool event( QEvent * pEvent )
    {
        if ( pEvent->type() == QEvent::ApplicationActivate ) {
            qDebug() << "ApplicationActivate";
            mainDialog->setWindowState(Qt::WindowActive);
            mainDialog->getFocus();
        }
        else if ( pEvent->type() == QEvent::ApplicationDeactivate ) {
            mainDialog->hide();
            qDebug() << "ApplicationDeactivate";
        }
        return QApplication::event( pEvent );
    }
};

#endif // MAINAPPLICATION_H
