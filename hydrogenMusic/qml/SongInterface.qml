import QtQuick 2.0
import VPlayApps 1.0
import QtMultimedia 5.5

Page {
    id: songinterfacepage
    title: qsTr("Hydrogen music")
    property var thisSong

    signal songinterfaceBack

    onThisSongChanged: {
        hyMediaPlayer.set_url(prefix + thisSong[3])
        console.log("onThisSongChanged: set_url:: " + prefix + thisSong[3])
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
        border.color: "grey"
        width: parent.width
        height: parent.height * 0.1
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
                console.log("play button click")
                hyMediaPlayer.init_multimedia2()
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
                //play state
                 console.log("pause button click")
                if (!paused) {
                    paused = true
                    lyrics.lyricsTime.running = false
                    hyMediaPlayer.pause_mulitimedia()
                } else {
                    lyrics.lyricsTime.start()
                    paused = false
                    hyMediaPlayer.play_multimedia()
                }
            }
        }
        IconButton {

            id: stopPictrue
            icon: IconType.stop
            anchors.left: pausePictrue.right
            anchors.top: musicPictrue.bottom
            onClicked: {
                console.log("stop button click")
                lyrics.cleanHightLight()
                hyMediaPlayer.stop_mulitimedia()
            }
        }

        IconButton {
            id: playlist
            icon: IconType.ioxhost
            anchors.bottom: re.bottom
            anchors.right: re.right
        }

        IconButton {
            id: download
            icon: IconType.download
            anchors.bottom: re.bottom
            anchors.right: playlist.left
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
            anchors.right: download.left
            anchors.bottom: re.bottom
            onClicked: {
                var a = thisSong[3] + " - " + personal.ID
                var e
                if (ilike.icon === IconType.heartbeat) {
                    console.log("ooo")
                    e = "delete dislike " + a
                } else
                    e = "ilike " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                            + " || " + thisSong[3] + " || " + personal.ID + " || " + a
                personal.sendMessage(e)
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
