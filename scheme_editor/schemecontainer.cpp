/*****
 * file: schemecontainer.cpp
 * author: Peter Lukac xlukac11
 * */

#include "schemecontainer.h"


void moveConnectionStart(QObject* connection, int x, int y);
void moveConnectionEnd(QObject* connection, int x, int y, int portNumer);

SchemeContainer::SchemeContainer(QObject *parent) : QObject(parent)
{

}

void SchemeContainer::addBlock(QString blockName){
    std::cout << "added block: " << blockName.toStdString() << std::endl;
    std::cout << "we have: " << schemePlane->children().count() << std::endl;
    int lastObject = schemePlane->children().count();
    QObject* block = schemePlane->children().at(lastObject-1);
    blockCounter++;
    block->setProperty("id_d", blockCounter);
    block->setProperty("type", 2);
    block->setObjectName("Block_"+QString::number(blockCounter));
}

void SchemeContainer::passTheSchemePtr(QObject* q){
    this->schemePlane = q;
}

void SchemeContainer::dragDetected(int x, int y, int id){
    //std::cout << "dragged: " << x << " " << y <<  std::endl;
    QList<QObject*> srcConnection;
    QList<QObject*> dstConnection;
    for(int i = 0; i < schemePlane->children().count(); i++){
        QObject* o = schemePlane->children().at(i);
        if( o->property("type") == 1){
            if( o->property("dst") == id)
                srcConnection.append(o);
            if( o->property("src") == id)
                dstConnection.append(o);
        }
    }
    //std::cout << srcConnection.length() << " " << dstConnection.length() << std::endl;
    for( int i = 0; i < srcConnection.length(); i++ ){
        QObject* o = srcConnection.at(i);
        moveConnectionEnd(o, x, y, o->property("dstPort").toInt());
    }
    for( int i = 0; i < dstConnection.length(); i++ ){
        QObject* o = dstConnection.at(i);
        moveConnectionStart(o, x, y);
    }
}

int SchemeContainer::deleteConnections(int id){
    QList<QObject*> connectionToDelete;
    for(int i = 0; i < schemePlane->children().count(); i++){
        QObject* o = schemePlane->children().at(i);
        if( o->property("type") == 1){
            if( o->property("dst") == id)
                connectionToDelete.append(o);
            if( o->property("src") == id)
                connectionToDelete.append(o);
        }
    }
    for( int i = 0; i < connectionToDelete.length(); i++ ){
        QObject* o = connectionToDelete.at(i);
        o->deleteLater();
    }
    return 1;
}


int SchemeContainer::addInputConnection(QString block, int port){
    QObject* node =  schemePlane->findChild<QObject*>(block);
    int id = node->property("id_d").toInt();
    for(int i = 0; i < schemePlane->children().count(); i++){
        QObject* o = schemePlane->children().at(i);
        if( o->property("type") == 1){
            if( o->property("dst") == id && o->property("dstPort") == port )
                return 0;
        }
    }

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

    QObject* src = schemePlane->findChild<QObject*>(outputNode);
    QObject* dst = schemePlane->findChild<QObject*>(inputNode);
    std::cout << "pos " << src->property("x").toInt() << " " << src->property("y").toInt() << std::endl;
    std::cout << "pos " << dst->property("x").toInt() << " " << dst->property("y").toInt() << std::endl;

    moveConnectionStart(connection, src->property("x").toInt(), src->property("y").toInt());
    moveConnectionEnd(connection, dst->property("x").toInt(), dst->property("y").toInt(), connectionPort);

    connection->setObjectName(outputNode + "|" + inputNode + "|" + QString::number(connectionPort) );
    connectionCounter++;
    connection->setProperty("id_d",connectionCounter);
    connection->setProperty("type", 1 );
    connection->setProperty("src", src->property("id_d").toInt() );
    connection->setProperty("dst", dst->property("id_d").toInt() );
    connection->setProperty("dstPort", connectionPort );


    return 1;
}

void moveConnectionStart(QObject* connection, int x, int y){
    connection = connection->findChild<QObject*>("view");
    connection = connection->findChild<QObject*>("start");
    connection->setProperty("startX", x + 210 );
    connection->setProperty("startY", y + 80 );
}


void moveConnectionEnd(QObject* connection, int x, int y, int portNumer){
    int offset = 55;
    for( int i = 1; i < portNumer; i++ )
        offset += 50;

    connection = connection->findChild<QObject*>("view");
    connection = connection->findChild<QObject*>("start");
    connection = connection->findChild<QObject*>("end");
    connection->setProperty("x", x + 10 );
    connection->setProperty("y", y + offset );

}




void SchemeContainer::schemeStart(){
    std::cout << "scheme started" << std::endl;
    proc = new SchemeProcessor(schemePlane);
    proc->loadBlocks();
    proc->loadConnections();
    proc->connectBlocks();
    proc->printSchema();
    proc->runSchema();
    delete proc;
}



void SchemeContainer::saveScheme(QString fileName){
    std::cout << "saving: " << fileName.toStdString() << std::endl;

    std::fstream file;
    file.open(fileName.toStdString(), std::fstream::out);

    for(int i = 0; i < schemePlane->children().count(); i++){
        QObject* o = schemePlane->children().at(i);
        int type = o->property("type").toInt();
        std::string oFile = o->property("file").toString().toStdString();
        if( type == 2 ){
            std::string opcode = o->property("opcode").toString().toStdString();
            int id = o->property("id_d").toInt();
            int x = o->property("x").toInt();
            int y = o->property("y").toInt();

            file << type << "\t" << id << "\t" << opcode << "\t" << x << "\t" << y << "\t" << oFile << std::endl;
        }
        if( type == 1 ){
            int id = o->property("id_d").toInt();
            int src = o->property("src").toInt();
            int dst = o->property("dst").toInt();
            int dstPort = o->property("dstPort").toInt();

            file << type << "\t" << id << "\t" << src << "\t" << dst << "\t" << dstPort << "\t" << oFile << std::endl;
        }
    }
    file.close();
}

QString SchemeContainer::loadScheme(QString qName){
    std::string fileName = qName.toStdString();

    fileName = fileName.substr(7);
    std::cout << "load: " << fileName << std::endl;

    l_file.open(fileName, std::fstream::in);
    std::cout << "file open" << std::endl;
    return "";
}

int SchemeContainer::loadAvailable(){
    if( l_file >> l_type >> l_id_d >> l_opcodeOrSrc >> l_xOrDst >> l_yOrDstPort >> l_elementFile ){

        std::cout << "loaded " << l_type << " " << l_id_d << " " <<
                     l_opcodeOrSrc << " " << l_xOrDst << " " <<
                     l_yOrDstPort << " " << l_elementFile << std::endl;

        return 1;
    }

    l_file.close();
    return 0;
}

QString SchemeContainer::getElement(){
    return QString::fromStdString(l_elementFile);
}

void SchemeContainer::registerElement(){
    int lastObject = schemePlane->children().count();
    QObject* o = schemePlane->children().at(lastObject-1);
    o->setProperty("type", l_type);
    o->setProperty("id_d", l_id_d);
    if( l_type == 2 ){
        o->setProperty("x", l_xOrDst);
        o->setProperty("y", l_yOrDstPort);
    }
    if( l_type == 1 ){
        o->setProperty("src", std::stoi(l_opcodeOrSrc) );
        o->setProperty("dst", l_xOrDst );
        o->setProperty("dstPort", l_yOrDstPort);
    }
}


