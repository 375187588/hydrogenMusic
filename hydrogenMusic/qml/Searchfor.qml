import QtQuick 2.0
import VPlayApps 1.0
import QtGraphicalEffects 1.0

Page {
    id: songlis
    property var searchforWhat: ["nameAr", "nameAr", "album"]
    property var sfw: 0
    property bool mutiIsClick: false
    property alias heigts: songlis.height
    property bool hightlight: false
    property string mutiBlockColor: "grey"
    signal heightcan
    signal heightrec
    signal searching

    Behavior on heigts {
        NumberAnimation {
            duration: 200
        }
    }

    Row {
        id: searchBar
        height: sp(30)
        width: parent.width
        SearchBar {
            id: searchbarr
            width: parent.width * 0.9

            anchors.verticalCenter: parent.verticalCenter
            onAccepted: {
                if(text.length != 0) {
                    var t = "search " + text + " " + searchforWhat[sfw]
                    personal.sendMessage(t)
                }else personal.sendMessage("songListShow")
            }
            onIconColorChanged: searching()
        }
        IconButton {
            id: mutiselectButton
            icon: IconType.lifering
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if (!mutiIsClick) {
                    heightcan()
                    lo.sourceComponent = mutiselect
                    mutiIsClick = true
                } else {
                    heightrec()
                    mutiIsClick = false
                    lo.sourceComponent = null
                }
            }
        }
    }

    Loader {
        id: lo
        anchors.top: searchBar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
    }

    Component {
        id: mutiselect
        Row {
            id: r

            opacity: 0.5
            Rectangle {
                id: r1
                width: songlis.width / 3
                height: sp(30)
                color: mutiBlockColor
                border.color: "white"
                border.width: sp(0.5)
                focus: true
                Text {
                    id: t1
                    anchors.centerIn: parent
                    text: qsTr("songName")
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (hightlight) {
                            r2.color = mutiBlockColor
                            r3.color = mutiBlockColor
                        }

                        r1.color = "white"
                        hightlight = true
                        sfw = 0
                    }
                }
            }

            Rectangle {
                id: r2
                width: songlis.width / 3
                height: sp(30)
                color: mutiBlockColor
                border.color: "white"
                border.width: sp(0.5)
                Text {
                    id: t2
                    anchors.centerIn: parent
                    text: qsTr("singer")
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (hightlight) {
                            r1.color = mutiBlockColor
                            r3.color = mutiBlockColor
                        }
                        r2.color = "white"
                        hightlight = true
                        sfw = 1
                    }
                }
            }

            Rectangle {
                id: r3
                width: songlis.width / 3
                height: sp(30)
                color: mutiBlockColor
                border.color: "white"
                border.width: sp(0.5)
                Text {
                    id: t3
                    anchors.centerIn: parent
                    text: qsTr("album")
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (hightlight) {
                            r2.color = mutiBlockColor
                            r1.color = mutiBlockColor
                        }
                        r3.color = "white"
                        hightlight = true
                        sfw = 2
                    }
                }
            }
        }
    }

    //    Component {
    //        id: songList
    //        SongList {
    //            anchors.top: searchBar.bottom
    //            anchors.bottom: songlis.bottom
    //            width: songlis.width
    //        }
    //    }
}
