import QtQuick 2.0
import VPlayApps 1.0
import QtGraphicalEffects 1.0

Page {
    id: mainbarpage
    signal wantSearch()
    signal mine()
    signal recomand()
    property alias myid:m_id.text

    Rectangle {
        id: mainbar
        width: parent.width
        height: sp(20)

        Text {
            id: m_id
            x: 10
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width * 0.2
            height: parent.height
            font.pixelSize: 20
        }
        Rectangle {
            id: r1
            width: parent.width * 0.2
            height: parent.height
            anchors.right: parent.horizontalCenter
            Text {
                text: qsTr("我的")
                anchors.centerIn: parent
                font.pixelSize: 20
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(r2.color != "white") {
                        mine()
                        parent.color = "#5CACEE"
                        r2.color = "white"
                    }
                }
            }
        }
        Rectangle {
            id: r2
            width: parent.width * 0.2
            height: parent.height
            anchors.left: parent.horizontalCenter
            color: "#5CACEE"
            Text {
                text: qsTr("推荐")
                anchors.centerIn: parent
                font.pixelSize: 20
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(r1.color != "white") {
                        recomand()
                        parent.color = "#5CACEE"
                        r1.color = "white"
                    }
                }
            }
        }

        IconButton {
            icon: IconType.search
            width: parent.width * 0.2
            height: parent.height
            anchors.right: parent.right
            onClicked: wantSearch()
        }
    }
}
