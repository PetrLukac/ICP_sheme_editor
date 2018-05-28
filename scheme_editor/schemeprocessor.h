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

    SchemeProcessor() {}
    SchemeProcessor(SchemeProcessor const &);
    void operator =(SchemeProcessor const&);

    int blockClk;

public:

    /***********************
     * getInstance returns singleton instance
     * */
    static SchemeProcessor& getInstance(){
        static SchemeProcessor instance;
        return instance;
    }

    /***********************
     * passSchemeElement allows to pass pointer to the scheme plane
     * */
    void passSchemeElement(QObject* scheme);

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

    /****************
     * clearBlocks clears backend information
     * */
    void clearBlocks();

    /***************
     * stepSchema step
     * */
    int stepSchema();

    int getBlockStatus(int blockId);

    double getBlockValue(int blockId);

    std::string getBlockType(int blockId);

};

#endif // SCHEMEPROCESSOR_H
