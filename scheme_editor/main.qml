import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.2

Window {
    //id: root
    objectName: "o_root"
    visible: true
    width: 1024
    height: 720
    title: qsTr("Hello World")
    color: "white"

    ColumnLayout{

        width: maximumWidth
        height: 720
        spacing: 0
        Rectangle{
            id: topPanel
            width: maximumWidth
            height: 100
            color: "#2377ff"
            border.width: 0

            Button{
                text: qsTr("AC")
            }
        }

        RowLayout{
            id: blockPanel
            //anchors.top: topPanel
            anchors.topMargin: 0
            height: 620
            spacing: 0
            Rectangle{
                border.width: 0
                width: 200
                height: maximumHeight
                color: "#141414"

                Button{
                    id: control
                    text: qsTr("Button")

                    contentItem: Text {
                        text: control.text
                        font: control.font
                        opacity: enabled ? 1.0 : 0.3
                        color: control.down ? "black" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        implicitWidth: maximumWidth
                        implicitHeight: 40
                        opacity: enabled ? 1 : 0.3
                        color: control.down ? "#999999" : "#5e5e5e"
                    }

                    onClicked: {
                        container.addBlock("add")

                    }
                }
                /*
                Rectangle {
                    color: "#999999"
                    Button {
                        text: qsTr("AC")
                    }
                }*/
            }
            Rectangle{
                id: schemeSpace
                objectName: "o_schemeSpace"
                width: maximumWidth
                height: maximumHeight
                color: "#dde1ff"
            }
        }
    }
}

