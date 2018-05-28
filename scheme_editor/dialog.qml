/*****
  * file: dialog.qml
  * author: Peter Lukac xlukac11
  */


import QtQuick 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1


FileDialog {
    id: fileDialog
    title: "Please choose a file"
    folder: shortcuts.home
    sidebarVisible: true
    selectExisting: false
    onAccepted: {

        console.log("You chose: " + fileDialog.fileUrl)
        container.loadScheme(fileDialog.fileUrls)

    }
    onRejected: {
        console.log("Canceled")
        console.log("You chose: " + fileDialog.fileUrl)
        fileDialog.close()
    }

    Component.onCompleted: visible = true
}


