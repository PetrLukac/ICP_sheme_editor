/*****
 * file: schemeprocessor.h
 * author: Peter Lukac xlukac11
 * */

#ifndef SCHEMEPROCESSOR_H
#define SCHEMEPROCESSOR_H
#include <QList>
#include <QObject>
#include <iostream>
#include <vector>
#include <fstream>
#include "block.h"

/*************
 * SchemeProcessor provides scheme processing
 * */
class SchemeProcessor
{
private:
    QObject* scheme;
    QList<QObject*> blockList;
    QList<QObject*> connectionList;
    std::vector<Block*> blocks;

public:

    /********
     * SchemeProcessor simple constructor
     * @param cheme pointer to the main plane with scheme
     * */
    SchemeProcessor(QObject* scheme);

    /****************
     * loadBlocks loads blocks from the cheme int private array
     * */
    int loadBlocks();

    /****************
     * loadConnections loads connections from the cheme int private array
     * */
    int loadConnections();

    /****************
     * connectBlocks runs through attributes of connections and connects blocks based on that
     * */
    int connectBlocks();

    /****************
     * printSchema simple debug function
     * */
    void printSchema();

    /****************
     * runSchema performs computation
     * */
    void runSchema();

};

#endif // SCHEMEPROCESSOR_H
