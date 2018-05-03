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
    property string opcode: "dst"
    property int inputCount: 1

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
    // Input 1
    Button{
        id: port_1
        height: 30
        width: 60
        y: 40
        x: 0
        contentItem: Text {
            font.pointSize: 8
            verticalAlignment: Text.AlignVCenter
            text: "  Input 1"
            color: "white"
        }
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: port_1.down ? "#999999" : "#5e5e5e"
        }
        onClicked: {

                if( container.addInputConnection(rec.objectName, 1) === 1){
                    var component;
                    component = Qt.createComponent("connection.qml");
                    component.createObject(schemeSpace)
                    container.registerConnection()

                }

        }
    }

    TextField{
        width: 60
        height: 30
        y: 40
        x: 120
        color: "white"
        Text {
            text: "[value]"
            color: "white"
        }
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: parent.down ? "#999999" : "#5e5e5e"
        }
    }
    TextField{
        width: 60
        height: 30
        y: 90
        x: 120
        color: "white"
        Text {
            text: "[type]"
            color: "white"
        }
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: parent.down ? "#999999" : "#5e5e5e"
        }
    }

    // Operation
    Text{
        text: "DST"
        color: "Black"
        font.pointSize: 16
        x: 80
        y: 65
    }

}
