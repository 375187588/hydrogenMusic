import QtQuick 2.0
import VPlayApps 1.0
import QtMultimedia 5.5
import qt.Lyric 1.0

Page {
    id: songinterfacepage
    title: qsTr("Hydrogen music")
    property var thisSong: ["a", "b", "c", '1', "../hydrogenMusic/assets/music/薛之谦 - 动物世界.mp3", "../hydrogenMusic/a"]
    MediaPlayer {
        //可以播放音频和视频
        id: music
        source: "../hydrogenMusic/assets/music/薛之谦 - 动物世界.mp3"
        //        source: thisSong[4]
    }

    onThisSongChanged: {
        //        lyrics.lAddr = thisSong[5]
        //        lyrics.lAddr = personal.songlis[5]
        lyrics.lAddr = "../hydrogenMusic/a"
        //        console.log("thisSongChanged,thisSong[5]:" + thisSong[5])
    }
    Rectangle {
        id: ret
        width: parent.width
        height: parent.height * 0.05
        anchors.top: parent.top
        color: "grey"
        IconButton {
            id: retPictrue
            icon: IconType.backward
            anchors.top: parent.top
            anchors.left: parent.left
            onClicked: {
                music.play()
                lyrics.lyricsTime.start()
            }
        }
    }

    AppFlickable {
        id: appflickable
        anchors.top: ret.bottom
        anchors.centerIn: parent
        contentWidth: parent.width
        contentHeight: parent.height * 1.5
        width: parent.width
        height: parent.height * 0.8

        Lyrics {
            id: lyrics
            anchors.fill: parent
            onLyricOk: {
                console.log("diogvjdolvgjolvg")
                bar.sourceComponent = rec
            }
        }
    }
    Loader {
        id: bar
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height * 0.1
    }

    Component {
        id: rec
        Rectangle {
            id: re
            border.color: "grey"
            width: parent.width
            height: parent.height
            Image {
                id: musicPictrue
                source: "../assets/img/audio-x-mpeg.svg"
            }
            IconButton {
                id: playPictrue
                icon: IconType.play
                anchors.top: musicPictrue.bottom
                anchors.left: musicPictrue.left
                onClicked: {
                    music.play()
                    lyrics.lyricsTime.start()
                }
            }
            IconButton {
                id: pausePictrue
                property bool paused: false
                icon: IconType.pause
                anchors.left: playPictrue.right
                anchors.top: musicPictrue.bottom
                onClicked: {
                    if (!paused) {
                        paused = true
                        lyrics.lyricsTime.running = false
                        music.pause()
                    } else {
                        music.play()
                        lyrics.lyricsTime.start()
                        paused = false
                    }
                }
            }
            IconButton {
                id: stopPictrue
                icon: IconType.stop
                anchors.left: pausePictrue.right
                anchors.top: musicPictrue.bottom
                onClicked: {
                    /*lyrics.*/ cleanHightLight()
                    music.stop()
                }
            }

            IconButton {
                id: download
                icon: IconType.download
                //                anchors.bottom: re.bottom
                anchors.right: re.right
                onClicked: {
                    var e = "download " + thisSong[0] + " " + thisSong[1] + " "
                            + thisSong[2] + " " + personal.ID
                    personal.sendMessage(e)
                }
            }
        }
    }

    Connections {
        target: personal
        onDownloadOk: {
            message.text = "download OK."
            appflickable.opacity = 0.5
            messageRet.visible = true
            showTime.restart()
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
        interval: 1000
        onTriggered: {
            appflickable.opacity = 1
            messageRet.visible = false
        }
    }
}
