#include "controller.h"

Controller::Controller(Rectangle *rect)
{
    this->rect = rect;
    tags.insert("Tag", 0);
}

void Controller::start()
{
    qDebug() << "starting scanner thread" << endl;

    QThread *workerThread = new QThread();
    this->moveToThread(workerThread);
    connect(workerThread, &QThread::started, this, &Controller::run);
    connect(this, &Controller::finished, workerThread, &QThread::quit);
    connect(this, &Controller::finished, this, &Controller::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);
    workerThread->start();
}

void Controller::run()
{
    while (true) {
        setTagValue("Tag", getTagValue("Tag") + 1);
        rect->setX(getTagValue("Tag"));
        rect->setY(getTagValue("Tag"));

        emit valueChanged("Tag");

        // Ensure 60Hz refresh rate
        QThread::msleep(28);
    }
}

int Controller::getTagValue(QString name)
{
    if (!tags.contains(name)) {
        throw QString("Tag does not exist");
    }
    return tags[name];
}

void Controller::setTagValue(QString name, int value)
{
    tags[name] = value;
}
