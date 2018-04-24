#include "schemecontainer.h"

SchemeContainer::SchemeContainer(QObject *parent) : QObject(parent)
{

}

void SchemeContainer::addBlock(QString blockName){
    std::cout << "added block: " << blockName.toStdString() << std::endl;
    /*QObject *rect = object->findChild<QObject*>("mainPlane");
    if (rect)
        rect->setProperty("color", "red");*/
}
