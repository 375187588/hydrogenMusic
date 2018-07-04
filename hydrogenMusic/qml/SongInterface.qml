import QtQuick 2.0
import VPlayApps 1.0
import QtMultimedia 5.5
import qt.Lyric 1.0

Page {
    id: page
    title: qsTr("Hydrogen music")
    property string s: "file:///root/c_note/hydrogenMusic/assets/music/薛之谦 - 动物世界.mp3"
    property var nameAr
    MediaPlayer {
        //可以播放音频和视频
        id: music
        //                source: "../assets/music/薛之谦 - 动物世界.mp3"
        //             autoPlay: true
        source: s
    }

    AppFlickable {
        id: appflickable
        anchors.fill: parent
        anchors.centerIn: parent
        contentWidth: width
        contentHeight: page.height

        Rectangle {
            id: rec
            border.color: "grey"
            width: parent.width
            height: 55
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
                    lyrics.cleanHightLight()
                    music.stop()
                }
            }

            IconButton {
                id: download
                icon: IconType.download
                anchors.top: musicPictrue.bottom
                anchors.right: rec.right
                onClicked: {
                    var e = "downLoad " + nameAr + " " + s
                    db.usedb(e)
                }
            }
        }

        Lyrics {
            id: lyrics
            anchors.top: rec.bottom
        }
    }

    Connections {
        target: db
        onDownloadOk:{
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
