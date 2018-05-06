/*****
  * file: dialog.qml
  * author: Peter Lukac xlukac11
  */

import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home

        onAccepted: {

            console.log("You chose: " + fileDialog.fileUrl)
            container.loadScheme(fileDialog.fileUrls)

        }
        onRejected: {
            console.log("Canceled")
            fileDialog.close()
        }

        Component.onCompleted: visible = true

    }


