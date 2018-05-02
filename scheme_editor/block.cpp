#include "block.h"

Block::Block()
{

}

void Block::addOutputBlock(Block* outlBock){

}

void Block::bindQmlBlock(QObject* qmlBlock){
    this->qmlBlock = qmlBlock;
}

void Block::validateInputConnected(bool valid){
    allConnected = valid;
}

void Block::addOutputBlockIdAndPort(int id, int port){
    outputBlockId.push_back(id);
    outputBlockPort.push_back(port);
}

void Block::setId(int id){
    id_d = id;
}

void Block::printContent(){
    std::cout << "id: " << id_d << " valid: " << allConnected << std::endl;
    for(unsigned i = 0; i < outputBlockId.size(); i++){
        std::cout << "\t id: " << outputBlockId.at(i) << " port: " << outputBlockPort.at(i) << std::endl;
    }
}
