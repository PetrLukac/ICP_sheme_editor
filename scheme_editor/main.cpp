/************
 * file: main.cpp
 * author: Peter Lukac xlukac11
 *
 * */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "schemecontainer.h"
#include <iostream>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>


/*******
 * main function provides creation of window
 * */
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

    QObject* m = engine.rootObjects().at(0);

    QObject* column = m->findChild<QObject*>("o_root_column");
    QObject* row = column->findChild<QObject*>("o_root_row");
    QObject* scheme = row->findChild<QObject*>("o_schemeSpace");
    container.data()->passTheSchemePtr(scheme);

    return app.exec();

}
