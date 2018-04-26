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

    Q_INVOKABLE void dragDetected();

    Q_INVOKABLE int addInputConnection(QString block, int port);

    Q_INVOKABLE int addOutputConnection(QString block);

    Q_INVOKABLE int objectCount();

    Q_INVOKABLE int registerConnection();

signals:

public slots:
};

#endif // SCHEMECONTAINER_H
