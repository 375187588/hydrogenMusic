import QtQuick 2.0
import VPlayApps 1.0

Item {
    id:item
    anchors.fill: parent
    property var sheetInfo:["a","b","c","d"]
    signal songsheetBack()
    Rectangle {
        id: ret
        width: parent.width
        height: sp(50)
        anchors.top: parent.top
        IconButton {
            id: retPictrue
            icon: IconType.arrowleft
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            size: parent.height/2
            onClicked: {
                songsheetBack()
            }
        }
    }
    Row{
        anchors.top: ret.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*0.8
        height: parent.height-ret.height
        spacing: sp(30)
        Rectangle{
            width: parent.width*0.3
            height: width
            radius: height/6
            border.width: sp(1.5)
            anchors.verticalCenter: parent.verticalCenter
            border.color: Theme.secondaryTextColor

        }
        Column{
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width*0.5
            //height: parent.height
            Text {
                id:name
                text: sheetInfo[0]
                clip: true
                wrapMode: Text.WordWrap
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                clip: true
                wrapMode: Text.WordWrap
                anchors.horizontalCenter: parent.horizontalCenter
                text: sheetInfo[1]
            }

            Text {
                id:textshow
                clip: true
                wrapMode: Text.WordWrap
                anchors.horizontalCenter: parent.horizontalCenter
                text: sheetInfo[3] === "noinfo" ?"添加注释":sheetInfo[3]
                elide: Text.ElideRight
                width: parent.width*0.6
            }
        }
    }

    Connections {
        target: control
        onSheetInfo: {
            item.sheetInfo = info
        }
    }
}
