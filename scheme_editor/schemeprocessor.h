#ifndef SCHEMEPROCESSOR_H
#define SCHEMEPROCESSOR_H
#include <QList>
#include <QObject>
#include <iostream>
#include <vector>
#include "block.h"

class SchemeProcessor
{
private:
    QObject* scheme;
    QList<QObject*> blockList;
    QList<QObject*> connectionList;
    std::vector<Block*> blocks;

public:
    SchemeProcessor(QObject* scheme);

    int loadBlocks();
    int loadConnections();
    int connectBlocks();
    void printSchema();
};

#endif // SCHEMEPROCESSOR_H
