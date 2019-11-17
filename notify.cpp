#include "notify.h"

Notify::Notify(QString timeExpression, QString message)
{
    this->id = QDateTime::currentDateTime().toMSecsSinceEpoch();
    this->timeExpression = timeExpression;
    this->message = message;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(sendNotify()));

    TYPE_TIME_EXPRESSION type = TimeExpressionUtils::getType(timeExpression);
    long msecs = -1;
;    if (type == HOUR_FORMAT) {
        msecs = TimeExpressionUtils::parseTime(timeExpression);
    } else if (type == DATE_FORMAT) {
        msecs = TimeExpressionUtils::parseDate(timeExpression);
    }
    timer->start(msecs);

}

Notify::~Notify()
{
    if (timer != nullptr)
        delete timer;
}

void Notify::sendNotify()
{    
    timer->stop();
    emit timeEllapsed(this);
}
