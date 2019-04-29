import QtQuick 2.0
import VPlayApps 1.0
import QtGraphicalEffects 1.0

Page {
    id: searchforpage
    property var searchVec: []
    signal ordinarySearchforpageBack(var song)

    Item {
        id: s
        height: parent.height
        width: parent.width
        Rectangle {
            id: searchBar
            height: sp(30)
            width: parent.width
            color: "#DBDBDB"
            IconButton {
                id: retPictrue
                icon: IconType.arrowleft
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    ordinarySearchforpageBack(null)
                }
            }
            SearchBar {
                id: searchbarr
                width: parent.width * 0.8
                height: parent.height *0.8
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                onTextChanged: {
                    var t = "search " + text
                    control.sendMessage(t)
                }
            }

        }

        Rectangle{
            anchors.top: searchBar.bottom
            width: parent.width
            height: parent.height-sp(30)
            ListView{
                id:listView
                anchors.fill: parent
                model: searchVec
                highlightRangeMode: ListView.StrictlyEnforceRange //currentIndex随着一起变化
                spacing: sp(1)
                delegate: Rectangle{
                    color: mouse_area.containsMouse ?"#EDEDED":"#CCCCCC"
                    height: dp(40)
                    width: songlis.width
                    radius: 10
                    Text {
                        anchors.top: parent.top
                        anchors.topMargin: 8
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        color: "black"
                        font.pixelSize: sp(12)
                        font.bold: sp(5)
                        text: songName
                    }
                    Text {
                        anchors.top: parent.top
                        anchors.topMargin: 28
                        anchors.left: parent.left
                        anchors.leftMargin: 30
                        color: "grey"
                        font.pixelSize: sp(7)
                        font.bold: sp(1)
                        text: singer + ' - ' + album
                    }
                    MouseArea{
                        id:mouse_area
                        anchors.fill: parent
                        onClicked: {
                            ordinarySearchforpageBack(songName)
                        }
                    }
                }
            }
        }


    }

    Connections {
        target: control
        onSearchOk: {
            searchVec = []
            if (control.searc.length !== 0) {
                searchVec = control.searc
            }
        }
    }
}
