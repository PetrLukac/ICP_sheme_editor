/*****
 * file: schemeprocessor.cpp
 * author: Peter Lukac xlukac11
 * */

#include "schemeprocessor.h"

void SchemeProcessor::passSchemeElement(QObject* scheme){
    this->scheme = scheme;
}

int SchemeProcessor::loadBlocks(){
    std::cout << "loading blocks" << std::endl;
    for( int i = 0; i < scheme->children().length(); i++){
        QObject* o = scheme->children().at(i);
        std::cout << o->property("type").toInt() << std::endl;
        if( o->property("type").toInt() == 2 )
            this->blockList.append(o);
    }
    std::cout << "Loaded : " << blockList.length() << " blocks" << std::endl;
    return 1;
}

int SchemeProcessor::loadConnections(){
    std::cout << "loading connections" << std::endl;
    for( int i = 0; i < scheme->children().length(); i++){
        QObject* o = scheme->children().at(i);
        if( o->property("type").toInt() == 1 )
            this->connectionList.append(o);
    }
    std::cout << "Loaded : " << connectionList.length() << " connections" << std::endl;
    return 1;
}



int SchemeProcessor::connectBlocks(){
    int retval = 1;
    for( int i = 0; i < blockList.length(); i++ ){
        QObject* o = blockList.at(i);
        int inputCount = o->property("inputCount").toInt();
        int id = o->property("id_d").toInt();
        std::vector<int> ports;

        for( int j = 0; j < connectionList.length(); j++ ){
            QObject* c = connectionList.at(j);
            if( c->property("dst").toInt() == id )
                ports.push_back( o->property("dstPort").toInt() );
        }

        std::cout << "id: " << id << " inputCount: " << inputCount << " connected connections: " << ports.size() << std::endl;
        QObject* top = o->findChild<QObject*>("top");
        if( top == nullptr ){
            std::cout << "no top !" << std::endl;
        }
        if( (unsigned)inputCount == ports.size() )
            top->setProperty("color","#9e58f4");
        else{
            top->setProperty("color","#f72a34");
            retval = 0;
        }
        Block* b = new Block();
        b->setId(id);
        b->bindQmlBlock(o);
        b->validateInputConnected( (unsigned)inputCount == ports.size() );
        //std::vector<int> connectedBlocks;

        for( int j = 0; j < connectionList.length(); j++ ){
            QObject* c = connectionList.at(j);
            if( c->property("src").toInt() == id ){
                b->addOutputBlockIdAndPort( c->property("dst").toInt() , c->property("dstPort").toInt() );
            }
        }

        blocks.push_back(b);
    }

    for( unsigned i = 0; i < blocks.size(); i++ ){
        Block* b = blocks.at(i);
        b->addOutputBlocks( blocks );
    }

    blockClk = 1;
    return retval;
}

void SchemeProcessor::printSchema(){
    for( unsigned i = 0; i < blocks.size(); i++){
        blocks.at(i)->printContent();
    }
}

void SchemeProcessor::runSchema(){
    for( unsigned clk = 1; clk < blocks.size() + 5; clk++ ){
        for( unsigned i = 0; i < blocks.size(); i++ ){
            blocks.at(i)->interate(clk);
        }
    }
    for( unsigned i = 0; i < blocks.size(); i++ ){
        std::cout << blocks.at(i)->getStatus() << " ";
    }
    std::cout << std::endl;
}

int SchemeProcessor::stepSchema(){
    int retVal = 1;
    for( unsigned i = 0; i < blocks.size(); i++ ){
        blocks.at(i)->interate(blockClk);
    }
    blockClk++;
    for( unsigned i = 0; i < blocks.size(); i++ ){
        if( blocks.at(i)->getStatus() != 1 )
            retVal = 0;
    }
    return retVal;
}

void SchemeProcessor::clearBlocks(){
    for( int i = 0; i < blockList.size(); i++){
        QObject* o;
        o = blockList.at(i)->findChild<QObject*>("top");
        o->setProperty("color", "#16cee2");
    }

    blockList.clear();
    connectionList.clear();

    for( unsigned i = 0; i < blocks.size(); i++){
        delete blocks[i];
    }
    blocks.clear();
}

int SchemeProcessor::getBlockStatus(int blockId){
    for( unsigned i = 0; i < blocks.size(); i++){
        if( blocks.at(i)->getId() == blockId && blocks.at(i)->getStatus() == 1 )
            return 1;
    }
    return 0;
}

double SchemeProcessor::getBlockValue(int blockId){
    for( unsigned i = 0; i < blocks.size(); i++){
        if( blocks.at(i)->getId() == blockId )
            return blocks.at(i)->getValue();
    }
    return 0;
}

std::string SchemeProcessor::getBlockType(int blockId){
    for( unsigned i = 0; i < blocks.size(); i++){
        if( blocks.at(i)->getId() == blockId )
            return blocks.at(i)->getType();
    }
    return "";
}

