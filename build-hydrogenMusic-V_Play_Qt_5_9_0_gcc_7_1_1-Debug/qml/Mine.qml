import QtQuick 2.0
import VPlayApps 1.0

Page {
    id: minepage
    signal ilikeshow
    signal downloadshow

    Column {
        height: parent.height
        width: parent.width
        spacing: sp(3)
        Rectangle {
            id: ilike
            color: "#CCCCCC"
            height: dp(40)
            width: parent.width

            IconButton {
                id: ili
                x: sp(6)
                icon: IconType.heartbeat
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width * 0.2
                height: parent.height
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: ili.right
                anchors.leftMargin: sp(10)
                color: "black"
                font.pixelSize: 20
                font.bold: sp(5)
                text: "我喜欢"
            }
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    parent.opacity = 0.3
                }
                onReleased: {
                    parent.opacity = 1
                    ilikeshow()
                }
            }
        }

        Rectangle {
            id: download

            color: "#CCCCCC"
            height: dp(40)
            width: parent.width

            IconButton {
                id: dow
                x: sp(6)
                icon: IconType.download
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width * 0.2
                height: parent.height
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: dow.right
                anchors.leftMargin: sp(10)
                color: "black"
                font.pixelSize: 20
                font.bold: sp(5)
                text: "下载"
            }
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    parent.opacity = 0.3
                }
                onReleased: {
                    parent.opacity = 1
                    downloadshow()
                }
            }
        }
    }
}
