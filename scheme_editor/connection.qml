/*****
  * file: connection.qml
  * author: Peter Lukac xlukac11
  */

import QtQuick 2.0
import QtQuick.Controls 2.2

Item{
    property int id_d: 0
    property int type: 0
    property int src: 0
    property int dst: 0
    property int dstPort: 0
    property string file: "connection.qml"
    id: r

    ToolTip {
            id: connectionTooltip
            parent: parent
            visible: false
            text: "value\ntype"

    }

    PathView {
        objectName: "view"
        model: 300;
        path: path
        delegate: Rectangle {
            width: 4; height: 4;
            color: "black";
            radius: width/2

            MouseArea
            {
                  anchors.fill: parent
                  hoverEnabled: true
                  onHoveredChanged: {
                      if( container.getBlockStatus(r.src) === 1){
                          connectionTooltip.text = container.getBlockValue(r.src)
                          connectionTooltip.text += "\n" + container.getBlockType(r.src)
                          connectionTooltip.visible = true
                          connectionTooltip.x = parent.x - 20
                          connectionTooltip.y = parent.y - 50
                      }
                  }
                  onExited: {
                      connectionTooltip.visible = false
                  }
            }
        }
        Path {
              objectName: "start"
              id: path
              startX: 10; startY: 10

              PathCubic {
                  objectName: "end"
                  id: cub
                   x: 510; y: 210
                   control1X: (path.startX + cub.x)/2
                   control1Y: path.startY
                   control2X: (path.startX + cub.x)/2
                   control2Y: cub.y
              }
        }
    }
    Button{
        x: ((path.startX + cub.x)/2) - 12
        y:  ((path.startY + cub.y)/2) - 12
        contentItem: Text {
            font.pointSize: 8
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignVCenter
            text: "X"
            color: "white"
        }
        background: Rectangle {
            implicitWidth: 8
            implicitHeight: 8
            color: parent.hovered ? "#ef1726" : "#6d6d6d"
        }
        onClicked: {
            r.destroy()
        }
    }
}
