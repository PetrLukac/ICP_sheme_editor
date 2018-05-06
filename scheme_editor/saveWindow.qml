import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window{

    width: 400
    height: 200

    ColumnLayout{

        TextField{
            id: filename
            text: "scheme name"
        }

        Button{
            contentItem: Text {
                font.pointSize: 14
                text: qsTr("Load")
            }
            onClicked: {
                container.schemeSave()
            }
        }
    }

}
