/*****
  * file: saveWindow.qml
  * author: Peter Lukac xlukac11
  */

import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Window{
    id: saveWindow
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
                text: qsTr("Save")
            }
            onClicked: {
                container.saveScheme(filename.text)
                saveWindow.close()
            }
        }
    }

}
