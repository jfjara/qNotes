#ifndef NOTIFYMANAGEMENT_H
#define NOTIFYMANAGEMENT_H

#include <QObject>
#include <QList>
#include "notify.h"

class NotifyManagement : public QObject
{
    Q_OBJECT
private:
    NotifyManagement(QObject* parent = 0);
    static NotifyManagement* instance;

    QList<Notify*> notifies;

public:
    virtual ~NotifyManagement();

    static NotifyManagement* getInstance() {
        if (instance == nullptr) {
            instance = new NotifyManagement();
        }
        return instance;
    }

    void clean();
    void clean(Notify* notify);
    void add(QString timeExpression, QString message);

public slots:
    void showNotify(Notify* notify);
signals:
    void send(Notify *notify);
};

#endif // NOTIFYMANAGEMENT_H
