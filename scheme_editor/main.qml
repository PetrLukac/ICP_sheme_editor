import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.2

Window {
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
            color: "blue"
            border.width: 0

            Button{
                text: qsTr("AC")
            }
        }

        RowLayout{
            id: blockPanel
            anchors.top: topPanel
            anchors.topMargin: 0
            height: 620
            spacing: 0
            Rectangle{
                border.width: 0
                width: 200
                height: maximumHeight
                color: "#141414"

                Button{
                    text: qsTr("AC")

                    width: maximumWidth
                    background: Rectangle{
                        color: "#999999"
                    }
                }
            }
            Rectangle{
                width: maximumWidth
                height: maximumHeight
                color: "#d5cee8"
            }
        }
    }
}

