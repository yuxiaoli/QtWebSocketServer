#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QQuickItem>

class Rectangle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged)

public:
    Rectangle();
    int getX() const;
    int getY() const;
    void setQMLObject(QQuickItem *object);

public slots:
    void setX(const int &x);
    void setY(const int &y);

signals:
    void xChanged();
    void yChanged();

private:
    int x;
    int y;
    QQuickItem *qmlObject;
};

#endif // RECTANGLE_H
