#include "colorutils.h"

ColorUtils::ColorUtils()
{

}

QString ColorUtils::extractColor(QString message)
{
    QString result = nullptr;
    if (message.contains("$")) {
        int i = message.indexOf('$');
        QChar color = message.at(i + 1);
        if (color == 'y') {
            result = "yellow";
        } else if (color == 'r') {
            result = "red";
        } else if (color == 'g') {
            result = "green";
        } else if (color == 'b') {
            result = "blue";
        }
    }
    return result;
}

QString ColorUtils::getCloseIcon(QString color)
{
    QString result = "";
    if (color == "yellow") {
        result = ":resources/close_yellow.png";
    } else if (color == "blue") {
        result = ":resources/close_blue.png";
    } else if (color == "green") {
        result = ":resources/close_green.png";
    } else if (color == "red") {
        result = ":resources/close_red.png";
    } else {
        result = ":resources/close_pop.png";
    }
    return result;
}

QString ColorUtils::getFontColor(QString color)
{
    QString result = "white";
    if (color == "yellow") {
        result = "black";
    }
    return result;
}
