#ifndef TIMEEXPRESSIONUTILS_H
#define TIMEEXPRESSIONUTILS_H

#include <QString>
#include <QStringList>
#include <QTime>
#include <QDateTime>
#include <QRegExp>
#include "enums.h"

class TimeExpressionUtils
{
public:
    TimeExpressionUtils();

    static TYPE_TIME_EXPRESSION getType(QString timeExpression);
    static long parseTime(QString timeText);
    static long parseDate(QString dateTime);

private:
    static QRegExp reHour;
    static QRegExp reDate;
};

#endif // TIMEEXPRESSIONUTILS_H
