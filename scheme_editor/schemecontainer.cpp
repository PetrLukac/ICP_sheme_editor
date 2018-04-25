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
    block->setObjectName("Block "+QString::number(blockCounter));
}

void SchemeContainer::passTheSchemePtr(QObject* q){
    this->schemePlane = q;
}

void SchemeContainer::dragDetected(){
    std::cout << "dragged !" << std::endl;
}
