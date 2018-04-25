#ifndef SCHEMECONTAINER_H
#define SCHEMECONTAINER_H

#include <QObject>
#include <string>
#include <iostream>
#include <QString>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QRect>
#include <QList>

class SchemeContainer : public QObject
{
    Q_OBJECT

    QObject *schemePlane;
    int blockCounter = 0;

public:
    explicit SchemeContainer(QObject *parent = nullptr);

    Q_INVOKABLE void addBlock(QString blockName);

    void passTheSchemePtr(QObject* q);

    Q_INVOKABLE void dragDetected();

signals:

public slots:
};

#endif // SCHEMECONTAINER_H
