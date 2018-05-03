#include "schemeprocessor.h"

SchemeProcessor::SchemeProcessor(QObject* scheme)
{
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
        Block* b = new Block();
        b->setId(id);
        b->bindQmlBlock(o);
        b->validateInputConnected( (unsigned)inputCount == ports.size() );
        std::vector<int> connectedBlocks;

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

    return 1;
}

void SchemeProcessor::printSchema(){
    for( unsigned i = 0; i < blocks.size(); i++){
        blocks.at(i)->printContent();
    }
}

void SchemeProcessor::runSchema(){
    for( unsigned clk = 1; clk < blocks.size() + 5; clk++ ){
        for( int i = 0; i < blocks.size(); i++ ){
            blocks.at(i)->interate(clk);
        }
    }
}

void SchemeProcessor::saveBlocks()
{
    std::ofstream file;
    file.open("schema",std::ios::out);

    if(this->blocks.size() != 0)
    {
        for(Block * block: this->blocks)
            file << (*block);
    }
    else
        std::cerr << "Why this is null, ffs" << std::endl;


}

