import QtQuick 2.0
import VPlayApps 1.0
import QtMultimedia 5.5
import QtQuick.Controls 1.1

Page {
    id: songinterfacepage
    title: qsTr("Hydrogen music")
    property var thisSong
    property string prefixx: "../assets/music/"

    signal songinterfaceBack

    onThisSongChanged: {
        pausePictrue.paused = false
        pausePictrue.icon = IconType.pause
    }

    MediaPlayer {
        //可以播放音频和视频
        id: music
        autoPlay: true
        source: prefixx + thisSong[3]
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
                songinterfaceBack()
            }
        }
    }

    AppFlickable {
        id: appflickable
        anchors.top: ret.bottom
        contentWidth: parent.width
        contentHeight: parent.height * 1.5
        width: parent.width
        height: parent.height * 0.8

        Lyrics {
            id: lyrics
            anchors.fill: parent
        }
    }

    Rectangle {
        id: re
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height * 0.1
        Image {
            id: musicPictrue
            source: "../assets/img/audio-x-mpeg.svg"
        }

        //        Rectangle {
        //            id: progressbar
        //            width: parent.width * 0.85
        //            height: sp(2)
        //            color: "black"
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            Rectangle {
        //                id: progress
        //                width: sp(5)
        //                height: sp(9)
        //                anchors.verticalCenter: parent.verticalCenter
        //                x: parent.x + (music.position / music.duration) * parent.width
        //            }
        //            MouseArea {
        //                width: parent.width
        //                height: progress.height
        //                onClicked: music.seek(
        //                               (mouseX - progressbar.x) / progressbar.width * music.duration)
        //            }

        //        }
        Slider {
            id: progressbar
            width: parent.width * 0.85
            height: sp(2)
            anchors.horizontalCenter: parent.horizontalCenter
            maximumValue: music.duration //hyMediaPlayer.get_all_schedule()
            value: music.position //hyMediaPlayer.get_current_schedule()
            onValueChanged: music.seek(value)
        }

        IconButton {
            id: pre
            icon: IconType.stepbackward
            anchors.right: pausePictrue.left
            anchors.top: pausePictrue.top
            onClicked: {
                var temp = []
                var index = personal.currentSong(
                            thisSong[3] + " - " + personal.ID)
                if (index !== 0) {
                    for (var i = 0; i < 4; i++) {
                        temp.push(personal.playlist[(index - 1) * 4 + i])
                    }
                    lyrics.cleanHightLight()
                    thisSong = temp
                }
            }
        }

        IconButton {
            id: pausePictrue
            property bool paused: false
            icon: IconType.pause
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: musicPictrue.bottom
            onClicked: {
                //play state
                if (paused) {
                    icon = IconType.pause
                    music.play()
                    lyrics.lyricsTime.start()
                    paused = false
                    //                    hyMediaPlayer.play_multimedia()
                } else {
                    icon = IconType.play
                    paused = true
                    lyrics.lyricsTime.running = false
                    //                    hyMediaPlayer.pause_mulitimedia()
                    music.pause()
                }
            }
        }

        IconButton {
            id: next
            icon: IconType.stepforward
            anchors.left: pausePictrue.right
            anchors.top: pausePictrue.top
            onClicked: {
                var temp = []
                var index = personal.currentSong(
                            thisSong[3] + " - " + personal.ID)
                if (index !== personal.playlist.length / 4 - 1) {
                    for (var i = 0; i < 4; i++) {
                        temp.push(personal.playlist[(index + 1) * 4 + i])
                    }
                    lyrics.cleanHightLight()
                    thisSong = temp
                }
            }
        }

        IconButton {
            id: playlist
            icon: IconType.ioxhost
            anchors.bottom: re.bottom
            anchors.right: re.right
            property bool clickthis: false
            onClicked: {
                if (!clickthis) {
                    appflickable.opacity = 0.4
                    re.opacity = 0.4
                    playlists.sourceComponent = plalistshow
                    clickthis = true
                } else {
                    appflickable.opacity = 1
                    re.opacity = 1
                    playlists.sourceComponent = null
                    clickthis = false
                }
            }
        }

        IconButton {
            id: download
            icon: IconType.download
            anchors.left: parent.left
            anchors.bottom: re.bottom
            onClicked: {
                var a = thisSong[3] + " - " + personal.ID
                var e = "download " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                        + " || " + thisSong[3] + " || " + personal.ID + " || " + a
                personal.sendMessage(e)
            }
        }

        IconButton {
            id: ilike
            icon: personal.isIlike(
                      thisSong[3]) ? IconType.heartbeat : IconType.heart
            anchors.left: download.right
            anchors.bottom: re.bottom
            onClicked: {
                var a = thisSong[3] + " - " + personal.ID
                var e
                if (ilike.icon === IconType.heartbeat) {
                    e = "delete dislike " + a
                } else
                    e = "ilike " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                            + " || " + thisSong[3] + " || " + personal.ID + " || " + a
                personal.sendMessage(e)
            }
        }
    }
    Loader {
        id: playlists
        width: parent.width
        height: parent.height * 0.5
        anchors.bottom: re.top
    }

    Component {
        id: plalistshow
        Playlist {
        }
    }

    Connections {
        target: playlists.item
        onListen: {
            lyrics.cleanHightLight()
            thisSong = vec
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
        onIlikeOk: ilike.icon = IconType.heartbeat
        onDislike: ilike.icon = IconType.heart
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
