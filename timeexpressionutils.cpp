#include "timeexpressionutils.h"
#include <QDebug>

QRegExp TimeExpressionUtils::reDate;
QRegExp TimeExpressionUtils::reHour;

TimeExpressionUtils::TimeExpressionUtils()
{  

}

TYPE_TIME_EXPRESSION TimeExpressionUtils::getType(QString timeExpression)
{
    reHour.setPattern("^(0[0-9]|1[0-9]|2[0-3]|[0-9]):[0-5][0-9]$");
    reDate.setPattern("^([0-2][0-9]|(3)[0-1])/(((0)[0-9])|((1)[0-2]))/\\d{4} (0[0-9]|1[0-9]|2[0-3]|[0-9]):[0-5][0-9]$");
    TYPE_TIME_EXPRESSION result = UNKNOWN_FORMAT;
    if (reHour.exactMatch(timeExpression)) {
        result = HOUR_FORMAT;
    } else if (reDate.exactMatch(timeExpression)) {
        result = DATE_FORMAT;
    }
    return result;
}

/**
 * @brief TimeExpressionUtils::parseTime
 * @param timeText
 * @return milliseconds from current time to timeText
 */
long TimeExpressionUtils::parseTime(QString timeText)
{
    QStringList timeSplitted = timeText.split(":");
    int hour = timeSplitted.at(0).toInt();
    int minutes = timeSplitted.at(1).toInt();
    QDateTime now = QDateTime::currentDateTime();
    QDateTime nextNotificationHour = QDateTime::currentDateTime();
    nextNotificationHour.setTime(QTime(hour, minutes));
    return now.msecsTo(nextNotificationHour);
}

long TimeExpressionUtils::parseDate(QString timeText)
{
    QStringList timeSplitted = timeText.split(" ");
    QString dateText = timeSplitted.at(0);
    QString hourText = timeSplitted.at(1);
    QDateTime nextNotificationDate;
    nextNotificationDate.setDate(QDate::fromString(dateText, "dd/MM/yyyy"));
    nextNotificationDate.setTime(QTime::fromString(hourText, "HH:mm"));
    QDateTime now = QDateTime::currentDateTime();
    return now.msecsTo(nextNotificationDate);
}
