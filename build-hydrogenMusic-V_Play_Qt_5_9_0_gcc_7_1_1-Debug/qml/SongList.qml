import QtQuick 2.0
import VPlayApps 1.0
import "../qml/myscript.js" as Logic

Page {
    id: songlis
    property var songVec: []
    signal listenThis(var vec)
    signal wantUpload
    property string sState: "warehouse"
    property bool isIlike: false
    property var preSongVec: [] //for search

    Component {
        id: list
        AppFlickable {
            id: appflickable
            anchors.fill: parent
            contentHeight: Loader.height * 2
            Column {
                Repeater {
                    id: rep1
                    model: songVec.length / 4

                    Rectangle {
                        id: rec
                        color: "#CCCCCC"
                        border.color: "grey"
                        //        border.width: sp(1)
                        height: dp(40)
                        width: songlis.width
                        radius: 20
                        focus: true
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            color: "black"
                            font.pixelSize: sp(12)
                            font.bold: sp(5)
                            text: songVec[index * 4 + 3]
                        }
                        IconButton {
                            id: addToList
                            icon: IconType.plus
                            anchors.right: deletethis.visible ? deletethis.left : parent.right
                            anchors.bottom: parent.bottom
                            onClicked: {
                                var temp = []
                                for (var i = 0; i < 4; i++) {
                                    temp.push(Logic.transToString(
                                                  songVec[index * 4 + i]))
                                }
                                personal.addToL(temp)
                                message.text = "已加入播放列表"
                                messageRet.visible = true
                                showTime.restart()
                            }
                        }
                        IconButton {
                            id: deletethis
                            icon: IconType.times
                            visible: (sState === "warehouse"
                                      || sState == "search") ? false : true
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            onClicked: {
                                var a = "delete " + sState + " " + songVec[3] + " - " + personal.ID
                                personal.sendMessage(a)
                            }
                        }

                        MouseArea {
                            height: parent.height
                            width: parent.width * 0.7
                            onPressed: {
                                parent.opacity = 0.3
                            }
                            onReleased: {
                                parent.opacity = 1
                                var temvec = []
                                for (var i = 0; i < 4; i++) {
                                    temvec.push(Logic.transToString(
                                                    songVec[index * 4 + i]))
                                }
                                personal.addToL(temvec)
                                listenThis(temvec)
                            }
                        }
                    }
                }
            }
        }
    }

    Loader {
        id: songListLoa
        //        sourceComponent: list
        anchors.fill: parent
    }

    IconButton {
        id: newAdd
        icon: IconType.upload
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: dp(50)
        width: dp(50)
        onClicked: {
            wantUpload()
        }
    }

    Component {
        id: noList
        AppText {
            color: "#454545"
            visible: true
            font.pixelSize: sp(12)
            font.bold: sp(5)
            text: "Sorry, the power of exhausting the land has not been found."
        }
    }

    Connections {
        target: personal
        onSongList: {
            newAdd.visible = true
            if (personal.songlis.length !== 1) {
                songVec = personal.songlis
                sState = "warehouse"
                songListLoa.sourceComponent = list
            }
        }
        onIlikeShow: {
            newAdd.visible = false
            if (personal.ilik.length !== 1) {
                songVec = personal.ilik
                if (isIlike) {
                    sState = "ilike"
                    isIlike = false
                }
                songListLoa.sourceComponent = list
            } else {
                songListLoa.sourceComponent = noList
            }
        }
        onDownloadShow: {
            newAdd.visible = false
            if (personal.downloa.length !== 1) {
                songVec = personal.downloa
                sState = "download"
                songListLoa.sourceComponent = list
            } else {
                songListLoa.sourceComponent = noList
            }
        }

        onSearchOk: {
            newAdd.visible = false
            if (personal.searc.length !== 1) {
                songVec = personal.searc
                sState = "search"
                preSongVec = songVec
                songListLoa.sourceComponent = list
            } else {
                songListLoa.sourceComponent = noList
            }
        }
    }

    Rectangle {
        id: messageRet
        color: "white"
        border.color: "black"
        //        border.width: sp(1)
        height: dp(30)
        width: dp(150)
        anchors.centerIn: parent
        radius: 20
        visible: false
        AppText {
            id: message
            anchors.fill: parent
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            color: "black"
            visible: true
            font.pixelSize: sp(12)
            font.bold: sp(5)
        }
    }

    Timer {
        id: showTime
        interval: 300
        onTriggered: {
            messageRet.visible = false
        }
    }
}
