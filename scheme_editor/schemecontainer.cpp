#include "schemecontainer.h"

SchemeContainer::SchemeContainer(QObject *parent) : QObject(parent)
{

}

void SchemeContainer::addBlock(QString blockName){
    std::cout << "added block: " << blockName.toStdString() << std::endl;
    std::cout << "we have: " << schemePlane->children().count() << std::endl;
    //schemePlane->setProperty("color", "red");
    //this->schemePlane->children().removeAt(0);
    int lastObject = schemePlane->children().count();
    QObject* block = schemePlane->children().at(lastObject-1);
    //block = block->findChild<QObject*>("addme");
    blockCounter++;
    block->setObjectName("Block_"+QString::number(blockCounter));
}

void SchemeContainer::passTheSchemePtr(QObject* q){
    this->schemePlane = q;
}

void SchemeContainer::dragDetected(){
    std::cout << "dragged !" << std::endl;
}

int SchemeContainer::addInputConnection(QString block, int port){
    if( draggingOutput == 0 ){
        std::cout << "dragging input from: " << block.toStdString() << " port: " << port << std::endl;
        draggingInput = 1;
        draggedPort = port;
        draggedNode = block;
        return 0;
    }
    if( draggingOutput == 1 ){
        std::cout << "connection: " << draggedNode.toStdString() << " " << block.toStdString() << " " << port << std::endl;
        draggingOutput = 0;
        outputNode = draggedNode;
        inputNode = block;
        connectionPort = port;
        return 1;
    }
    return 0;
}

int SchemeContainer::addOutputConnection(QString block){
    if( draggingInput == 0 ){
        std::cout << "dragging output from: " << block.toStdString() << std::endl;
        draggingOutput = 1;
        draggedNode = block;
        return 0;
    }
    if( draggingInput == 1 ){
        std::cout << "connection: " << block.toStdString() << " " << draggedNode.toStdString() << " " << draggedPort << std::endl;
        outputNode = block;
        inputNode = draggedNode;
        connectionPort = draggedPort;
        draggingInput = 0;
        return 1;
    }
    return 0;
}

int SchemeContainer::objectCount(){
    std::cout << "object count: " << schemePlane->children().count() << std::endl;
    return 1;
}

int SchemeContainer::registerConnection(){
    int lastObject = schemePlane->children().count();
    QObject* connection = schemePlane->children().at(lastObject-1);
    connection->setObjectName(outputNode + "|" + inputNode + "|" + QString::number(connectionPort) );
    connection = connection->findChild<QObject*>("view");
    connection = connection->findChild<QObject*>("start");
    QObject* start = connection;
    connection = connection->findChild<QObject*>("end");
    QObject* end = connection;
    //std::cout << "pos " << connection->property("x").toInt() << std::endl;
    QObject* src = schemePlane->findChild<QObject*>(outputNode);
    QObject* dst = schemePlane->findChild<QObject*>(inputNode);
    std::cout << "pos " << src->property("x").toInt() << " " << src->property("y").toInt() << std::endl;
    std::cout << "pos " << dst->property("x").toInt() << " " << dst->property("y").toInt() << std::endl;
    start->setProperty("startX", src->property("x").toInt() + 210 );
    start->setProperty("startY", src->property("y").toInt() + 80 );
    if( connectionPort == 1 ){
        end->setProperty("x", dst->property("x").toInt() + 10 );
        end->setProperty("y", dst->property("y").toInt() + 55 );
    }
    if( connectionPort == 2 ){
        end->setProperty("x", dst->property("x").toInt() + 10 );
        end->setProperty("y", dst->property("y").toInt() + 105 );
    }
    return 1;
}
