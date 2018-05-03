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
        objectName: "o_root_column"
        width: maximumWidth
        height: 720
        spacing: 0
        Rectangle{
            id: topPanel
            width: maximumWidth
            height: 100
            color: "#2377ff"
            border.width: 0

            RowLayout{
                height: parent.height
                x: 10
                spacing: 10
                Button{
                    text: qsTr("New")
                }
                Button{
                    text: qsTr("Save")
                    onClicked: {
                        container.delegateSave();
                    }
                }
                Button{
                    id: loadButton
                    text: qsTr("Load")
                }

                Rectangle{
                    width: 50
                }
                Button{
                    text: "Run"
                    onClicked: {
                        container.schemeStart()
                    }
                }
                Button{
                    text: "Step"
                }
                Button{
                    text: "Restart"
                }

            }
        }

        RowLayout{
            objectName: "o_root_row"
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

                ColumnLayout{
                    // create src block
                    Button{
                        text: qsTr("SRC")

                        contentItem: Text {
                            text: parent.text
                            font: parent.font
                            opacity: enabled ? 1.0 : 0.3
                            color: parent.down ? "black" : "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            implicitWidth: 200
                            implicitHeight: 40
                            opacity: enabled ? 1 : 0.3
                            color: parent.down ? "#999999" : "#5e5e5e"
                        }

                        onClicked: {
                            var component;
                            component = Qt.createComponent("src.qml");
                            component.createObject(schemeSpace)
                            container.addBlock("src")
                        }
                    }

                    // create dst block
                    Button{
                        text: qsTr("DST")

                        contentItem: Text {
                            text: parent.text
                            font: parent.font
                            opacity: enabled ? 1.0 : 0.3
                            color: parent.down ? "black" : "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            implicitWidth: 200
                            implicitHeight: 40
                            opacity: enabled ? 1 : 0.3
                            color: parent.down ? "#999999" : "#5e5e5e"
                        }

                        onClicked: {
                            var component;
                            component = Qt.createComponent("dst.qml");
                            component.createObject(schemeSpace)
                            container.addBlock("dst")
                        }
                    }

                    // create add block
                    Button{
                        id: control
                        text: qsTr("ADD")

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
                            implicitWidth: 200
                            implicitHeight: 40
                            opacity: enabled ? 1 : 0.3
                            color: control.down ? "#999999" : "#5e5e5e"
                        }

                        onClicked: {
                            var component;
                            component = Qt.createComponent("add.qml");
                            component.createObject(schemeSpace)
                            container.addBlock("add")
                        }
                    }
                }
            }

            Rectangle{
                id: schemeSpace
                objectName: "o_schemeSpace"
                width: maximumWidth
                height: maximumHeight
                color: "#f9f9f9"
            }
        }
    }
}

