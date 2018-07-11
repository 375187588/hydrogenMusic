import QtQuick 2.0
import VPlayApps 1.0
import QtGraphicalEffects 1.0

Page {
    id: searchforpage
    property var searchforWhat: ["song", "singer", "album"]
    property var sfw: 0
    property bool mutiIsClick: false
    property alias heigts: s.height
    property bool hightlight: false
    property string mutiBlockColor: "grey"
    signal heightcan
    signal heightrec
    signal searching
    signal searchforpageBack
    signal searchshow

    Behavior on heigts {
        NumberAnimation {
            duration: 200
        }
    }
    Item {
        id: s
        height: parent.height
        width: parent.width
        Item {
            id: searchBar
            height: sp(30)
            width: parent.width
            SearchBar {
                id: searchbarr
                width: parent.width * 0.8
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                onAccepted: {
                    searching()
                    if (text.length != 0) {
                        var t = "search " + text + " " + searchforWhat[sfw]
                        personal.sendMessage(t)
                    } else
                        searchshow()
                }
                onIconColorChanged: console.log(show.visible)
            }
            IconButton {
                id: mutiselectButton
                icon: IconType.spinner
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: ret.left
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

            Rectangle {
                id: ret
                anchors.right: parent.right
                anchors.rightMargin: sp(6)
                width: parent.width * 0.05
                height: parent.height
                Text {
                    text: qsTr("取消")
                    font.pixelSize: 20
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: searchforpageBack()
                }
            }
        }

        Loader {
            id: lo
            anchors.top: searchBar.bottom
            anchors.bottom: parent.bottom
            width: parent.width
        }
    }

    Rectangle {
        id: show
        width: parent.width * 0.6
        height: parent.height * 0.4
        //        visible: true
        anchors.top: s.bottom
        Flow {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Text {
                width: parent.width
                height: sp(20)
                text: qsTr("最近热搜")
                font.pixelSize: 20
            }
            Rectangle {
                color: "#CCCCCC"
                width: parent.width * 0.3
                height: sp(20)
                radius: 20

                IconButton {
                    id: ico
                    icon: IconType.bolt
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    anchors.left: ico.right
                    text: qsTr("周杰伦")
                    anchors.verticalCenter: parent.verticalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            searchbarr.text = parent.text
                        }
                    }
                }
            }

            Rectangle {
                color: "#CCCCCC"
                width: parent.width * 0.3
                height: sp(20)
                radius: 20

                IconButton {
                    id: ic
                    icon: IconType.bolt
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    anchors.left: ic.right
                    text: qsTr("林俊杰")
                    anchors.verticalCenter: parent.verticalCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            searchbarr.text = parent.text
                        }
                    }
                }
            }
        }
    }

    Component {
        id: mutiselect
        Row {
            id: r

            opacity: 0.5
            Rectangle {
                id: r1
                width: searchforpage.width / 3
                height: sp(30)
                color: mutiBlockColor
                border.color: "white"
                border.width: sp(0.5)
                focus: true
                Text {
                    id: t1
                    anchors.centerIn: parent
                    text: qsTr("song")
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
                width: searchforpage.width / 3
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
                width: searchforpage.width / 3
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
}
