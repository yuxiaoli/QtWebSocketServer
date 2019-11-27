#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlComponent>
#include <QThread>

#include <rectangle.h>
#include <controller.h>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // init
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    QQuickWindow *window = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));
    QQuickItem *root = window->contentItem();

    class Rectangle *rect = new class Rectangle();
    QQmlContext *context = new QQmlContext(&engine, rect);
    context->setContextProperty("obj", rect);

    QQmlComponent component(&engine, QUrl("qrc:/rectangle.qml"));
    QQuickItem *qmlObject = qobject_cast<QQuickItem *>(component.create(context));

    QQmlEngine::setObjectOwnership(qmlObject, QQmlEngine::CppOwnership);
    qmlObject->setParent(rect);
    qmlObject->setParentItem(root);


    // Kick off a new thread
    Controller *controller = new Controller(rect);
    controller->start();

    return app.exec();
}
