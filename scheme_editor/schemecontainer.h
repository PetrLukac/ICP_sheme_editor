/*****
 * file: schemecontainer.h
 * author: Peter Lukac xlukac11
 * */

#ifndef SCHEMECONTAINER_H
#define SCHEMECONTAINER_H

#include <QObject>
#include <string>
#include <iostream>
#include <QString>
#include <vector>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QRect>
#include <QList>
#include <QFile>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>
#include <fstream>

#include "schemeprocessor.h"
#include <unistd.h>
#include <QMetaObject>

/**********
 * SchemeContainer provides backed funtions
 * */
class SchemeContainer : public QObject
{
    Q_OBJECT

    QObject *schemePlane;
    int blockCounter = 0;
    int connectionCounter = 0;

    int draggingInput = 0;
    int draggingOutput = 0;
    int draggedPort = 0;
    QString draggedNode;

    QString outputNode;
    QString inputNode;
    int connectionPort;
    SchemeProcessor *proc;


    int l_type;
    int l_id_d;
    std::string l_opcodeOrSrc;
    int l_xOrDst;
    int l_yOrDstPort;
    std::string l_elementFile;
    std::fstream l_file;

    int hold_up;

    int editable = 1;

public:
    /*******
     * SchemeContainer explicit constructor
     * */
    explicit SchemeContainer(QObject *parent = nullptr);

    /***********
     * addBlock registers block after qml element wac created ad sets couple attributes
     * @param blockName blockName is name of the block
     * */
    Q_INVOKABLE void addBlock(QString blockName);

    /***********
     * passTheSchemePtr pointer to the main pane is neseccery to accses new elements
     * this is used to pass and store pointer to mainPlane
     * @param q pointer to the plane
     * */
    void passTheSchemePtr(QObject* q);

    /***********
     * dragDetected is invoked when block is dragged, when block is dragged all
     * connection belonging to the block are moved based on coordinates
     * @param x coordinate x
     * @param y coordinate y
     * */
    Q_INVOKABLE void dragDetected(int x, int y, int id);

    /***********
     * addInputConnection when input is clicked, we assume to create connection
     * this method provides backend logic to connect blocks
     * @param block block that is being used
     * @param port port of the block
     * @return 1 if connection is valid
     * */
    Q_INVOKABLE int addInputConnection(QString block, int port);

    /***********
     * addOutputConnection when output is clicked, we assume to create connection
     * this method provides backend logic to connect blocks
     * @param block block that is being used
     * @reutrn 1 if connection is valid
     * */
    Q_INVOKABLE int addOutputConnection(QString block);

    /************
     * objectCount simple debug funtion
     * @return number of present objects in the scheme
     * */
    Q_INVOKABLE int objectCount();

    /************
     * registerConnection when new connection is created in the qml, backed sets additional attributes
     * @return 1 if registration succesfull
     * */
    Q_INVOKABLE int registerConnection();

    /************
     * deleteConnections removes connection based on id
     * @param id id of the connection
     * @return 1 if deletion succesfull
     * */
    Q_INVOKABLE int deleteConnections(int id);

    /************
     * schemeBuild begins computation of the scheme
     * all blocks gets connected, connections are checkd
     * @return 1 if scheme succesfully built
     * */
    Q_INVOKABLE int schemeBuild();

    /*************
     * saveScheme collects attributes of all elements int the cheme and saved them in the folder
     * @param fileName name of the file to save the cheme to
     * */
    Q_INVOKABLE void saveScheme(QString fileName);

    /*************
     * loadScheme loads file and recreates the scheme
     * @param qName name of the file to load scheme from
     * @return ""
     * */
    Q_INVOKABLE QString loadScheme(QString qName);

    /**************
     * schemeEdit sets blocks to default mode
     * @return 1
     * */
    Q_INVOKABLE int schemeEdit();

    /**************
     * schemeRun runs scheme
     * performs iterations on all blocks until all blocks report status done
     * @return 1
     * */
    Q_INVOKABLE int schemeRun();

    /**************
     * schemeIterate performs one iteration on all blocks
     * @return 1 if all blocks finished computation
     * */
    Q_INVOKABLE int schemeIterate();

    /*************
     * getBlockStatus returns status of the block based on id
     * this method uses SchemeProcessor singleton method that containts blocks
     * @param blockId id of the block
     * @return 1 if computation finished
     * */
    Q_INVOKABLE int getBlockStatus(int blockId);

    /*************
     * getBlockStatus returns computed value of the block based on id
     * this method uses SchemeProcessor singleton method that containts blocks
     * @param blockId id of the block
     * @return value
     * */
    Q_INVOKABLE double getBlockValue(int blockId);

    /*************
     * getBlockStatus returns computed type of the block based of id
     * this method uses SchemeProcessor singleton method that containts blocks
     * @param blockId id of the block
     * @return type
     * */
    Q_INVOKABLE QString getBlockType(int blockId);

    /***********
     * checkLoops performs loop controll
     * @return 1 if no loop are present
     * */
    Q_INVOKABLE int checkLoops();

    /**********
     * clearScheme removes all objects from the scene
     * */
    Q_INVOKABLE void clearScheme();

    /**************
     * setEdit sets edit mode variable
     * @param e edit enabled
     * */
    Q_INVOKABLE void setEdit(int e);

    /**********
     * getEdit returns state of the scheme
     * @return 1 if scheme is editable
     * */
    Q_INVOKABLE int getEdit();

signals:

public slots:
};

#endif // SCHEMECONTAINER_H
