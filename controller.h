#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <rectangle.h>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(class Rectangle *rect);
    void start();
    int getTagValue(QString name);
    void setTagValue(QString name, int value);

public slots:
    void run();

signals:
    void finished();
    void valueChanged(QString name);

private:
    class Rectangle *rect;
    QHash<QString, int> tags;
};

#endif // CONTROLLER_H
