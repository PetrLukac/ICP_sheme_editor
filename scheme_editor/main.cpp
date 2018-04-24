#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "schemecontainer.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QScopedPointer<SchemeContainer> container(new SchemeContainer);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("container",container.data());
    /*QObject *rect = engine.findChild<QObject*>("o_schemeSpace");
        if (rect)
            rect->setProperty("color", "red");
        else
            std::cout << "empty rect" << std::endl;*/
    QObject* m = engine.rootObjects().at(0);
    std::cout << "Do i have a window in my hand ?: " << m->isWindowType() << std::endl;
    std::cout << "My name is not Johny but: " << m->objectName().toStdString() << std::endl;

    return app.exec();
}
