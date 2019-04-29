import QtQuick 2.0
import VPlayApps 1.0
import QtMultimedia 5.5
import QtQuick.Controls 1.1

Page {
    id: songinterfacepage
    title: qsTr("Hydrogen music")
    property var thisSong
    //-----xiaoyao--s--------
    property string add: "rtsp://0.0.0.0/"+thisSong[0].substring(0, thisSong[0].length - 1)
    //-----xiaoyao--s--------
    property string prefixx: "../assets/music/"

    signal songinterfaceBack

    onThisSongChanged: {
        pausePictrue.paused = false
        pausePictrue.icon = IconType.pause
        //-----xiaoyao--s--------------
        //var addhead = "rtsp://0.0.0.0/"+thisSong
        simplePlayer.openUrl(add)
        console.log("kkkkkkkkkkkk"+thisSong[0].substring(0, thisSong[0].length - 1)+"jjj")
        //-----xiaoyao-----e------------
    }

    MediaPlayer {
        //可以播放音频和视频
        id: music
        autoPlay: true
        source: prefixx + thisSong[0].substring(0,thisSong[0].length - 1)
    }
    Rectangle {
        id: ret
        width: parent.width
        height: parent.height * 0.05
        anchors.top: parent.top
        color: "grey"
        IconButton {
            id: retPictrue
            icon: IconType.arrowleft
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
            height: parent.height
            width: parent.width
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
//        Slider {
//            id: progressbar
//            width: parent.width * 0.85
//            height: sp(2)
//            anchors.horizontalCenter: parent.horizontalCenter
//            maximumValue: music.duration //hyMediaPlayer.get_all_schedule()
//            value: music.position //hyMediaPlayer.get_current_schedule()
//            onValueChanged: music.seek(value)
//        }
//        Slider {
//            id: slider
//                              //width: parent.width * 0.85
//            //height: sp(2)
//            anchors.horizontalCenter: parent.horizontalCenter
//            //maximumValue:simplePlayer.getlength()  //hyMediaPlayer.get_all_schedule()
//            maximumValue:200000
//            //value: simplePlayer.getpositon() //hyMediaPlayer.get_current_schedule()
//            property bool sync: false
//            onValueChanged: {
//                if(!sync)
//                    simplePlayer.setposition(value)
//            }
//            Timer{
//                id:t
//                running: true
//                interval: 300
//                repeat: true
//                onTriggered:
//                {

//                    //console.log("timer")
//                    slider.sync=true

//                    slider.value=simplePlayer.getpositon()
//                    slider.maximumValue=simplePlayer.getlength()
//                    slider.sync=false
//                    //console.log(slider.maximumValue)
//                }
//            }
//        }
        //----xiaoyao-----s----
        Slider {
            id: progressbar
            width: parent.width * 0.85
            height: sp(2)
            anchors.horizontalCenter: parent.horizontalCenter
            //maximumValue: music.duration //hyMediaPlayer.get_all_schedule()
            //value: music.position //hyMediaPlayer.get_current_schedule()
            //onValueChanged: music.seek(value)
            property bool sync: false
            onValueChanged: {
                if(!sync)
                    simplePlayer.setposition(value)
            }
            Timer{
                id:t
                running: true
                interval: 300
                repeat: true
                onTriggered:
                {

                    //console.log("timer")
                    progressbar.sync=true

                    progressbar.value=simplePlayer.getpositon()
                    progressbar.maximumValue=simplePlayer.getlength()
                    progressbar.sync=false
                    //console.log(slider.maximumValue)
                }
            }
        }
        //-----xiaoyao----e----
        IconButton {
            id: pre
            icon: IconType.stepbackward
            anchors.right: pausePictrue.left
            anchors.top: pausePictrue.top
            onClicked: {
                var temp = []
                var index = control.currentSong(
                            thisSong[3] + " - " + control.ID)
                if (index !== 0) {
                    for (var i = 0; i < 4; i++) {
                        temp.push(control.playlist[(index - 1) * 4 + i])
                    }
                    //lyrics.cleanHightLight()
                    thisSong = temp
                }
            }
        }

//                IconButton {
//                    id: pausePictrue
//                    property bool paused: false
//                    icon: IconType.pause
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    anchors.top: musicPictrue.bottom
//                    onClicked: {
//                        //play state
//                        if (paused) {
//                            icon = IconType.pause
//                            music.play()
//                            //lyrics.lyricsTime.start()
//                            paused = false
//                            //                    hyMediaPlayer.play_multimedia()
//                        } else {
//                            icon = IconType.play
//                            paused = true
//                            //lyrics.lyricsTime.running = false
//                            //                    hyMediaPlayer.pause_mulitimedia()
//                            music.pause()
//                        }
//                    }
//                }
        //xiaoyao----s----------
        IconButton {
            id: pausePictrue
            property bool paused: true
            icon: IconType.pause
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: musicPictrue.bottom
            onClicked: {
                //play state
                if (paused) {
                    icon = IconType.pause
                    //music.play()
                    simplePlayer.openUrl(add)
                    //lyrics.lyricsTime.start()
                    paused = false
                    //                    hyMediaPlayer.play_multimedia()
                } else {
                    icon = IconType.play
                    paused = true

                    //music.pause()
                    //simplePlayer.
                }
            }
        }
        //xiaoyao------e-------
        IconButton {
            id: next
            icon: IconType.stepforward
            anchors.left: pausePictrue.right
            anchors.top: pausePictrue.top
            onClicked: {
                var temp = []
                var index = control.currentSong(
                            thisSong[3] + " - " + control.ID)
                if (index !== control.playlist.length / 4 - 1) {
                    for (var i = 0; i < 4; i++) {
                        temp.push(control.playlist[(index + 1) * 4 + i])
                    }
                    //lyrics.cleanHightLight()
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
                var a = thisSong[3] + " - " + control.ID
                var e = "download " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                        + " || " + thisSong[3] + " || " + control.ID + " || " + a
                control.sendMessage(e)
            }
        }

        IconButton {
            id: ilike
            icon: control.isIlike(
                      thisSong[3]) ? IconType.heartbeat : IconType.heart
            anchors.left: download.right
            anchors.bottom: re.bottom
            onClicked: {
                var a = thisSong[3] + " - " + control.ID
                var e
                if (ilike.icon === IconType.heartbeat) {
                    e = "delete dislike " + a
                } else
                    e = "ilike " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                            + " || " + thisSong[3] + " || " + control.ID + " || " + a
                control.sendMessage(e)
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
            //lyrics.cleanHightLight()
            thisSong = vec
        }
    }

    Connections {
        target: control
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
