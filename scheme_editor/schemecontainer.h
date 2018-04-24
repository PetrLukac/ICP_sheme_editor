#ifndef SCHEMECONTAINER_H
#define SCHEMECONTAINER_H

#include <QObject>
#include <string>
#include <iostream>
#include <QString>

class SchemeContainer : public QObject
{
    Q_OBJECT
public:
    explicit SchemeContainer(QObject *parent = nullptr);

    Q_INVOKABLE void addBlock(QString blockName);

signals:

public slots:
};

#endif // SCHEMECONTAINER_H
