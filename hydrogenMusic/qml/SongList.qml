import QtQuick 2.0
import VPlayApps 1.0
import "../qml/myscript.js" as Logic
import Song 1.0
import PersonalInfo 1.0

Page {
    id: songlis
    property var songVec: []
    signal listenThis(var vec)
    signal wantUpload
    signal searchComing
    signal adverReset
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
                spacing: 2
                Repeater {
                    id: rep1
                    model: songVec.length

                    Rectangle {
                        id: rec
                        color: "#CCCCCC"
                        height: dp(40)
                        width: songlis.width
                        radius: 10
                        focus: true
                        Text {
                            anchors.top: parent.top
                            anchors.topMargin: 8
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            color: "black"
                            font.pixelSize: sp(12)
                            font.bold: sp(5)
                            text: songVec[index].songName
                        }
                        Text {
                            anchors.top: parent.top
                            anchors.topMargin: 28
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            color: "grey"
                            font.pixelSize: sp(7)
                            font.bold: sp(1)
                            text: songVec[index].singer + ' - ' + songVec[index].album
                        }
                        IconButton {
                            id: addToList
                            icon: IconType.plus
                            anchors.right: deletethis.visible ? deletethis.left : parent.right
                            anchors.bottom: parent.bottom
                            onClicked: {
                                //                                var temp = []
                                //                                for (var i = 0; i < 4; i++) {
                                //                                    temp.push(Logic.transToString(
                                //                                                  songVec[index * 4 + i]))
                                //                                }
                                control.addToL(songVec[index])
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
                                var a = "delete " + sState + " " + songVec[index].key + " - " + control.ID
                                control.sendMessage(a)
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
                                temvec.push(songVec[index].songName)
                                temvec.push(songVec[index].singer)
                                temvec.push(songVec[index].album)
                                temvec.push(songVec[index].key)
                                control.addToL(songVec[index])
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
        target: control
        onSongList: {
            newAdd.visible = true
            adverReset()
            if (control.songlis.length !== 0) {
                songVec = control.songlis
                sState = "warehouse"
                songListLoa.sourceComponent = list
            }
        }
        onIlikeShow: {
            newAdd.visible = false
            if (control.ilik.length !== 0) {
                songVec = control.ilik
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
            if (control.downloa.length !== 0) {
                songVec = control.downloa
                sState = "download"
                searchComing()
                songListLoa.sourceComponent = list
            } else {
                songListLoa.sourceComponent = noList
            }
        }

        onSearchOk: {
            if(songlis.visible) {
                newAdd.visible = false
                searchComing()
                songVec = []
                if (control.searc.length !== 0) {
                    songVec = control.searc
                    sState = "search"
                    preSongVec = songVec
                    songListLoa.sourceComponent = list
                } else {
                    songListLoa.sourceComponent = noList
                }
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
