/*****
 * file: block.h
 * author: Peter Lukac xlukac11
 * */

#ifndef BLOCK_H
#define BLOCK_H
#include <QList>
#include <QObject>
#include <string>
#include <vector>
#include <iostream>

#include "semantics.h"

/*****
 * class Block provides back end functions for chema computation
 * */
class Block
{
private:
    std::vector<double> portValue;
    std::vector<std::string> portType;
    std::vector<int> recivedClk;

    std::string opcode;

    bool allConnected;
    std::vector<int> outputBlockId;
    std::vector<int> outputBlockPort;
    std::vector<Block*> outputBlock;
    std::vector<int> blockDone;

    int id_d;
    QObject* qmlBlock;//TODO: Save some info to reconstruct
    int status = 0;

    int resultDone = 0;
    std::string resultType;
    double resultValue;

public:
    /*****
     * Block simple constructor
     * */
    Block();

    /*****
     * setId sets id
     * @param id id of the block
     * */
    void setId(int id);

    /*****
     * addOutputBlocks allows to connected source blocks to the output of this block
     * @param blocks array of all blocks
     * */
    void addOutputBlocks(std::vector<Block*> blocks);

    /*****
     * addOutputBlockIdAndPort adds id-s and ports of output blocks to the array used later
     * @param id id of the block to add
     * @param port port of the block to add
     * */
    void addOutputBlockIdAndPort(int id, int port);

    /*****
     * bindQmlBlock sets the pointer to the qml block to affect frontend during computation
     * @param id id of the block to add
     * */
    void bindQmlBlock(QObject* qmlBlock);

    /*****
     * validateInputConnected sets allValid attribute
     * @param valid validity
     * */
    void validateInputConnected(bool valid);

    /*****
     * printContent simple debug funtion
     * */
    void printContent();

    /*****
     * interate performs interaton of inner state of the block
     * This allow blocks to send data and change status
     * */
    void interate(int clk);

    /*****
     * reciveData allows block to recive data
     * if blocks recived data on all ports, block calls data computation
     * if all data on all ports is recived, block is able to send data
     * @param value value of data
     * @param type type of data
     * @param port port where data belongs
     * @param clk clock of iteration
     * */
    void reciveData(double value, std::string type, int port, int clk);

    friend std::ostream& operator<<(std::ostream& os, const Block& s);
    friend std::istream& operator>>(std::istream& is, Block& s);

    /*****
     * getId gets id
     * */
    int getId() const;

    /*****
     * getsStatus gets status
     * */
    int getStatus() const;

    double getValue();

    std::string getType();

    int checkForLoops(std::vector<int>* blockList );

};

#endif // BLOCK_H
