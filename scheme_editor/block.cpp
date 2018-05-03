#include "block.h"

Block::Block()
{

}

int Block::getId() const{
    return this->id_d;
}

void Block::addOutputBlocks(std::vector<Block*> blocks){
    for( unsigned i = 0; i < outputBlockId.size(); i++ ){
        int id = outputBlockId.at(i);
        for( unsigned j = 0; j < blocks.size(); j++ ){
            Block* b = blocks.at(j);
            if( b->getId() == id )
                outputBlock.push_back(b);
        }
        blockDone.push_back(0);
    }
}

void Block::bindQmlBlock(QObject* qmlBlock){
    this->qmlBlock = qmlBlock;
    this->opcode = qmlBlock->property("opcode").toString().toStdString();
    int inputCount = qmlBlock->property("inputCount").toInt();
    for(int i = 0; i < inputCount; i++){
        portValue.push_back(0);
        portType.push_back("");
        recivedClk.push_back(0);
    }
    if( this->opcode == "src" ){
        resultType = qmlBlock->findChild<QObject*>("typeField")->property("text").toString().toStdString();
        resultValue = qmlBlock->findChild<QObject*>("valueField")->property("text").toDouble();
        std::cout << "value: " << resultValue << " type: " << resultType << std::endl;
        portValue.push_back(0);
        portType.push_back("");
        recivedClk.push_back(-1);
        resultDone = 1;
    }
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
    std::cout << "id: " << id_d << " opcode: " << opcode << " valid: " << allConnected << std::endl;
    for(unsigned i = 0; i < outputBlock.size(); i++){
        std::cout << "\t id: " << outputBlock.at(i)->getId() << " port: " << outputBlockPort.at(i) << std::endl;
    }
}

int Block::getStatus() const{
    return this->status;
}

std::ostream & operator<<(std::ostream &os, const Block &s)
{
    os << s.id_d << '\n';
    os << s.opcode << '\n';
    os << s.resultType << '\n';
    os << s.resultValue << '\n';
    os << s.status << '\n';
    os << s.allConnected << '\n';
    os << s.resultDone << '\n';

    os << "PortVals\n";
    Saver::printVectorToOut(os,s.portValue);
    os << "PortValsEnd\n";

    os << "PortTypes\n";
    Saver::printVectorToOut(os,s.portType);
    os << "PortTypesEnd\n";

    os << "RecCLK\n";
    Saver::printVectorToOut(os,s.recivedClk);
    os << "RecCLKEnd\n";

    os << "OutBIds\n";
    Saver::printVectorToOut(os,s.outputBlockId);
    os << "OutBIdsEnd\n";

    os << "PortVals\n";
    Saver::printVectorToOut(os,s.outputBlockPort);
    os << "PortValsEnd\n";

    os << "OBlocksIds\n";
    std::vector<int> outBlockId;

    for(Block *block:s.outputBlock)
        outBlockId.push_back(block->getId());

    Saver::printVectorToOut(os,outBlockId);
    os << "OBlocksIdsEnd\n";

    os << "BlockDonesId\n";
    Saver::printVectorToOut(os,s.blockDone);
    os << "BlockDonesIdEnd\n";

}

std::istream & operator>>(std::istream &is, Block &s)
{

}

void Block::interate(int clk){
    if( status == 1 || status == -1 )
        return;

    if( resultDone == 1 ){
        status = 1;
        for( unsigned i = 0; i < recivedClk.size(); i++ ){
            if( recivedClk.at(i) == 0 )
                status = 0;
            if( recivedClk.at(i) == clk )
                status = 0;
        }
    }
    if( status == 0 )
        return;
    for( unsigned i = 0; i < outputBlockId.size(); i++ ){
        outputBlock.at(i)->reciveData( resultValue, resultType, outputBlockPort.at(i), clk );
    }

}

void Block::reciveData(double value, std::string type, int port, int clk){
    std::cout << "id_d: " << id_d << " reciving data" << std::endl;
    portValue.at(port-1) = value;
    portType.at(port-1) = type;
    recivedClk.at(port-1) = clk;

    int allRecived = 1;
    for( unsigned i = 0; i < recivedClk.size(); i++ ){
        if( recivedClk.at(i) == 0 )
            allRecived = 0;
    }
    if( allRecived == 1 ){
        if( opcode != "dst" ){
            resultValue = Semantics::getInstance().computeData( portValue, portType, opcode );
        }
        else
            resultValue = portValue.at(0);
        resultDone = 1;
        resultType = portType.at(0);
        std::cout << "id: " << id_d << " recived all, value: " << resultValue << " type: " << resultType << std::endl;

        if( opcode == "dst" ){
            this->qmlBlock->findChild<QObject*>("valueField")->setProperty("text", resultValue);
            this->qmlBlock->findChild<QObject*>("typeField")->setProperty("text", QString::fromStdString(resultType));
        }
    }
}
