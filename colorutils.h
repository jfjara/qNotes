#ifndef COLORUTILS_H
#define COLORUTILS_H

#include <QString>
#include <QChar>

class ColorUtils
{
public:
    ColorUtils();

    static QString extractColor(QString message);
    static QString getCloseIcon(QString color);
    static QString getFontColor(QString color);

};

#endif // COLORUTILS_H
