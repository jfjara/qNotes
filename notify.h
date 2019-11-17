#ifndef NOTIFY_H
#define NOTIFY_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "timeexpressionutils.h"

class Notify : public QObject
{
    Q_OBJECT
public:
    Notify(QString timeExpression, QString message);
    virtual ~Notify();

    long id;
    QTimer* timer = nullptr;
    QString message;
    QString timeExpression;

public slots:
    void sendNotify();

signals:
    void timeEllapsed(Notify* notify);

};

#endif // NOTIFY_H
