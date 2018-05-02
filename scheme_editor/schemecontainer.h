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

#include "schemeprocessor.h"

class SchemeContainer : public QObject
{
    Q_OBJECT

    QObject *schemePlane;
    int blockCounter = 0;
    int connectionCounter = 0;

    int draggingInput = 0;
    int draggingOutput = 0;
    int draggedPort = 0;
    QString draggedNode;

    QString outputNode;
    QString inputNode;
    int connectionPort;

public:
    explicit SchemeContainer(QObject *parent = nullptr);

    Q_INVOKABLE void addBlock(QString blockName);

    void passTheSchemePtr(QObject* q);

    Q_INVOKABLE void dragDetected(int x, int y, int id);

    Q_INVOKABLE int addInputConnection(QString block, int port);

    Q_INVOKABLE int addOutputConnection(QString block);

    Q_INVOKABLE int objectCount();

    Q_INVOKABLE int registerConnection();

    Q_INVOKABLE int deleteConnections(int id);

    Q_INVOKABLE void schemeStart();

signals:

public slots:
};

#endif // SCHEMECONTAINER_H
