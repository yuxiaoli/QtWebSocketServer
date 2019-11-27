#include "rectangle.h"

Rectangle::Rectangle()
{
    x = 0;
    y = 0;
}

void Rectangle::setQMLObject(QQuickItem *object)
{
    qmlObject = object;
}

int Rectangle::getX() const
{
    return x;
}

int Rectangle::getY() const
{
    return y;
}

void Rectangle::setX(const int &x)
{
    this->x = x;
    emit xChanged();
}

void Rectangle::setY(const int &y)
{
    this->y = y;
    emit yChanged();
}
