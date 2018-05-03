#ifndef BLOCK_H
#define BLOCK_H
#include <QList>
#include <QObject>
#include <string>
#include <vector>
#include <iostream>
#include "semantics.h"

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
    QObject* qmlBlock;
    int status = 0;

    int resultDone = 0;
    std::string resultType;
    double resultValue;

public:
    Block();
    void setId(int id);
    int getId();

    void addOutputBlocks(std::vector<Block*> blocks);
    void addOutputBlockIdAndPort(int id, int port);
    void bindQmlBlock(QObject* qmlBlock);
    void validateInputConnected(bool valid);
    void printContent();

    int getStatus();
    void interate(int clk);
    void reciveData(double value, std::string type, int port, int clk);
};

#endif // BLOCK_H
