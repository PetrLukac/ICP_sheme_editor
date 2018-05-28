/*****
  * file: main.qml
  * author: Peter Lukac xlukac11
  */


import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.2

Window {
    id: root
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
                        var component = Qt.createComponent("saveWindow.qml");
                        var win = component.createObject(root);
                        win.show();
                    }
                }
                Button{
                    id: loadButton
                    text: qsTr("Load")
                    onClicked: {
                        var component = Qt.createComponent("dialog.qml");
                        var win = component.createObject(root);
                    }
                }

                Rectangle{
                    width: 50
                }
                Button{
                    id: editButton
                    text: "Edit"
                    enabled: false
                    onClicked: {
                        editButton.enabled = false
                        buildButton.enabled = true
                        buildButton.text = "Build"
                        runButton.enabled = false
                        stepButton.enabled = false
                        container.schemeEdit()
                    }
                }
                Button{
                    id: buildButton
                    text: "Build"
                    enabled: true
                    onClicked: {
                        container.schemeEdit()
                        var isBuilt = container.schemeBuild()
                        if( isBuilt === 1){
                            runButton.enabled = true
                            stepButton.enabled = true
                        }
                        buildButton.enabled = false
                        editButton.enabled = true
                    }
                }
                Button{
                    id: runButton
                    text: "Run"
                    enabled: false
                    onClicked: {
                        buildButton.text = "Rebuild"
                        runButton.enabled = false
                        stepButton.enabled = false
                        buildButton.enabled = true
                        container.schemeRun()
                    }
                }
                Button{
                    id: stepButton
                    text: "Step"
                    enabled: false
                    onClicked: {
                        buildButton.text = "Rebuild"
                        runButton.enabled = false
                        buildButton.enabled = true
                        if( container.schemeIterate() === 1)
                            stepButton.enabled = false
                    }
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
                    // create sub block
                    Button{
                        text: qsTr("SUB")

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
                            component = Qt.createComponent("sub.qml");
                            component.createObject(schemeSpace)
                            container.addBlock("sub")
                        }
                    }
                    // create mul block
                    Button{
                        text: qsTr("MUL")

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
                            component = Qt.createComponent("mul.qml");
                            component.createObject(schemeSpace)
                            container.addBlock("mul")
                        }
                    }

                    // create div block
                    Button{
                        text: qsTr("DIV")

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
                            component = Qt.createComponent("div.qml");
                            component.createObject(schemeSpace)
                            container.addBlock("div")
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
                function addElement(file){
                    console.log("adding element:", file)
                    var component;
                    component = Qt.createComponent(file);
                    component.createObject(schemeSpace)
                    return 1
                }
            }
        }
    }
}

