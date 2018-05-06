/*****
  * file: src.qml
  * author: Peter Lukac xlukac11
  */

import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Rectangle{
    id: rec
    //property int draggedIndex: 0
    //objectName: "addme"
    property int id_d: 0
    property int type: 0
    property int input1Connected: 0
    property int input2Connected: 0
    property string opcode: "src"
    property int inputCount: 0
    property string file: "src.qml"

    width: 220; height: 140
    color:"#e5e5e5"
    x: 10
    y: 10

    MouseArea {
         width: 220
         height: 30

         drag.target: parent
         cursorShape: drag.active ? Qt.ClosedHandCursor : Qt.OpenHandCursor
         onPositionChanged: {
            container.dragDetected(rec.x, rec.y, rec.id_d);
         }


    }
    ColumnLayout{
        objectName: "cl"
        width: 220
        Rectangle{
                objectName: "top"
                height: 30
                width: 220
                color: "#16cee2"
                Button{
                    //text: "X"
                    onClicked:{
                        container.deleteConnections(rec.id_d)
                        rec.destroy();
                    }
                    x: 190
                    width: 30
                    height: 30
                    contentItem: Text {
                        font.pointSize: 12
                        text: "X"
                        color: "white"
                    }
                    background: Rectangle {
                        implicitWidth: 30
                        implicitHeight: 30
                        color: "#f21f1f"
                    }
                }
                Text{
                    text: rec.objectName
                    font.pointSize: 12
                    x: 80
                    y: 5
                }
        }

    }

    TextField{
        objectName: "valueField"
        width: 60
        height: 30
        y: 40
        x: 20
        color: "white"
        text: "[value]"
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: parent.down ? "#999999" : "#5e5e5e"
        }
    }
    TextField{
        objectName: "typeField"
        width: 60
        height: 30
        y: 90
        x: 20
        color: "white"
        text: "[type]"
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: parent.down ? "#999999" : "#5e5e5e"
        }
    }

    // Output
    Button{
        id: port_3
        height: 30
        width: 60
        y: 65
        x: 160
        contentItem: Text {
            font.pointSize: 8
            verticalAlignment: Text.AlignVCenter
            text: "Output  "
            color: "white"
        }
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: port_3.down ? "#999999" : "#5e5e5e"
        }
        onClicked: {
            if( container.addOutputConnection(rec.objectName) === 1){
                var component;
                component = Qt.createComponent("connection.qml");
                component.createObject(schemeSpace)
                container.registerConnection()
            }
        }
    }
    // Operation
    Text{
        text: "SRC"
        color: "Black"
        font.pointSize: 16
        x: 100
        y: 65
    }

}
