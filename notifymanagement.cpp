#include "notifymanagement.h"

NotifyManagement* NotifyManagement::instance = nullptr;

NotifyManagement::NotifyManagement(QObject* parent)
{

}
NotifyManagement::~NotifyManagement() {

}

void NotifyManagement::add(QString timeExpression, QString message)
{
    Notify* notify = new Notify(timeExpression, message);
    connect(notify, SIGNAL(timeEllapsed(Notify*)), this, SLOT(showNotify(Notify*)));
    this->notifies.append(notify);
}

void NotifyManagement::showNotify(Notify* notify)
{
    emit send(notify);
}

void NotifyManagement::clean(Notify* notify)
{
    for (int i = 0; i < notifies.size(); i++) {
        if (notifies.at(i)->id == notify->id) {
            notifies.removeAt(i);
            break;
        }
    }
}

void NotifyManagement::clean()
{
    foreach (Notify* notify, notifies) {
      delete notify;
    }
    notifies.clear();
}
