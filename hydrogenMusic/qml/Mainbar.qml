import QtQuick 2.0
import VPlayApps 1.0
import QtGraphicalEffects 1.0

Page {
    id: mainbarpage
    signal wantSearch()
    signal mine()
    signal cycle()
    signal recomand()
    signal wantSendTreat()
    property alias myid:m_id.text
    property bool isRecommand:true

    Rectangle {
        id: mainbar
        width: parent.width
        height: sp(50)

        Text {
            id:m_id
            x:10
            y:parent.height/4
            font.pixelSize: 20
        }

        Rectangle {
            id: r1
            radius: 10
            width: parent.width * 0.15
            height: parent.height/2
            anchors.bottom: r2.bottom
            anchors.right: r2.left
            Text {
                id:t1
                color: "grey"
                text: qsTr("我的")
                anchors.centerIn: parent
                font.pixelSize: 15
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    t2.color = "grey"
                    t2.font.pixelSize = 15
                    t3.color = "grey"
                    t3.font.pixelSize = 15
                    t1.color = "black"
                    t1.font.pixelSize = 20
                    isRecommand = false
                    mine()
                }
            }
        }
        Rectangle {
            id: r2
            radius: 10
            width: parent.width * 0.15
            height: parent.height/2
            anchors.top:parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            //color: "#5CACEE"
            Text {
                id:t2
                text: qsTr("推荐")
                anchors.centerIn: parent
                font.pixelSize: 20
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    t1.color = "grey"
                    t1.font.pixelSize = 15
                    t3.color = "grey"
                    t3.font.pixelSize = 15
                    t2.color = "black"
                    t2.font.pixelSize = 20
                    isRecommand = true
                    recomand()
                }
            }
        }
        Rectangle {
            id: r3
            radius: 10
            width: parent.width * 0.15
            height: parent.height/2
            anchors.bottom: r2.bottom
            anchors.left: r2.right
            Text {
                id:t3
                color: "grey"
                text: qsTr("音乐圈")
                anchors.centerIn: parent
                font.pixelSize: 15
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    t2.color = "grey"
                    t2.font.pixelSize = 15
                    t1.color = "grey"
                    t1.font.pixelSize = 15
                    t3.color = "black"
                    t3.font.pixelSize = 20
                    isRecommand = false
                    cycle()
                }
            }
        }

        Rectangle {
            radius: 10
            width: parent.width * 0.6
            height: parent.height/3
            anchors.top: r2.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#DBDBDB"
            Text {
                color: "grey"
                text: qsTr("搜索")
                anchors.centerIn: parent
                font.pixelSize: 13
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    wantSearch()
                    isRecommand = false
                }
            }
        }

        IconButton {
            id: addTreat
            icon: IconType.plus
            size: parent.height/2
            visible: t3.font.pixelSize == 20 ? true : false
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: sp(5)
            onClicked: {
                wantSendTreat()
            }
        }

    }
}
