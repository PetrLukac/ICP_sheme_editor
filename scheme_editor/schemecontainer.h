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
     * */
    Q_INVOKABLE int addInputConnection(QString block, int port);

    /***********
     * addOutputConnection when output is clicked, we assume to create connection
     * this method provides backend logic to connect blocks
     * @param block block that is being used
     * */
    Q_INVOKABLE int addOutputConnection(QString block);

    /************
     * objectCount simple debug funtion
     * */
    Q_INVOKABLE int objectCount();

    /************
     * registerConnection when new connection is created in the qml, backed sets additional attributes
     * */
    Q_INVOKABLE int registerConnection();

    /************
     * deleteConnections removes connection based on id
     * @param id id of the connection
     * */
    Q_INVOKABLE int deleteConnections(int id);

    /************
     * schemeBuild begins computation of the scheme
     * all blocks gets connected, connections are checkd
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
     * */
    Q_INVOKABLE QString loadScheme(QString qName);

    /***********
     * loadAvailable supports functionality to the loadCheme
     * */
    Q_INVOKABLE int loadAvailable();

    /***********
     * getElement supports functionality to the loadCheme
     * */
    Q_INVOKABLE QString getElement();

    /***********
     * registerElement supports functionality to the loadCheme
     * */
    Q_INVOKABLE void registerElement();

    /**************
     * schemeEdit sets blocks to default mode
     * */
    Q_INVOKABLE int schemeEdit();

    /**************
     * schemeRun runs scheme
     * */
    Q_INVOKABLE int schemeRun();

    /**************
     * schemeIterate performs one iteration on all blocks
     * */
    Q_INVOKABLE int schemeIterate();

    Q_INVOKABLE int getBlockStatus(int blockId);

    Q_INVOKABLE double getBlockValue(int blockId);

    Q_INVOKABLE QString getBlockType(int blockId);

    Q_INVOKABLE int checkLoops();

signals:

public slots:
};

#endif // SCHEMECONTAINER_H
