#ifndef BLOCK_H
#define BLOCK_H
#include <QList>
#include <QObject>
#include <string>
#include <vector>
#include <iostream>

class Block
{
private:
    std::vector<double> portValue;
    std::vector<std::string> portType;
    std::string opcode;
    bool allConnected;
    std::vector<int> outputBlockId;
    std::vector<int> outputBlockPort;
    std::vector<Block*> outputBlock;
    int id_d;
    QObject* qmlBlock;

public:
    Block();
    void setId(int id);
    void addOutputBlock(Block* outBlock);
    void addOutputBlockIdAndPort(int id, int port);
    void bindQmlBlock(QObject* qmlBlock);
    void validateInputConnected(bool valid);
    void printContent();
};

#endif // BLOCK_H
