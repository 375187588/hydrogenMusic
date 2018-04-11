import VPlayApps 1.0
import QtQuick 2.0
import QtMultimedia 5.8
import QtQuick.Controls 1.1

App {

    width: 480
    height: 800
    Item {
        id: root
        width: 480
        height: 800

        PlaylistInterface {
            id: listview
            anchors.top: parent.top
            onClicked: {
                singleplayer.source = playlist.itemSource(listview.index)
                player.pause()
                singleplayer.play()
            }
        }
        Audio {
            id: player
            playlist: Playlist {
                id: playlist
                PlaylistItem {
                    source: "../assets/over.mp3"
                }
                PlaylistItem {
                    source: "../assets/music.mp3"
                }
                PlaylistItem {
                    source: "../assets/j.ogg"
                }
                //onItemChanged: console.log(player.source)
            }
        }
        Audio {
            id: singleplayer
            onStopped: {

                player.play()
            }
        }
        Slider {
            width: 480
            anchors.top: listview.bottom
            maximumValue: singleplayer.duration
            value: singleplayer.position
            onValueChanged: singleplayer.seek(value)
        }

        Text {
            id: playname
            text: qsTr("null")
            color: "green"
            scale: 3
            anchors.top: listview.bottom
            anchors.topMargin: 50
            anchors.horizontalCenter: listview.horizontalCenter
        }
        Row {
            anchors.top: listview.bottom
            anchors.topMargin: 100

            AppButton {
                id: button0
                //anchors.horizontalCenter: parent.horizontalCenter
                //anchors.bottom: parent.bottom
                text: "Play Audio"
                onClicked: {
                    //audio.play()
                    player.play()
                    playname.text = "Playing music"
                    console.log("fjdkedk")
                }
            }
            AppButton {
                id: button1
                //anchors.bottom: button0
                //anchors.bottom: parent.bottom
                text: "Stop music"
                onClicked: {
                    player.stop()
                    playname.text = "Pausing"
                }
            }
            AppButton {
                id: button2
                //anchors.bottom: button0
                //anchors.bottom: parent.bottom
                text: "Next"
                onClicked: {
                    //player.loops
                    playname.text = "Playing"
                    playlist.next()
                }
            }

            //            My_button {
            //                id: mb
            //                anchors.bottom: button1.bottom
            //                onClicked: {
            //                    t.text = "play music"
            //                    //t.text = player.source
            //                }
            //            }
            //            Text {
            //                id: t        Audio {

            //                text: "play"
            //            }
        }

        //        ListView {
        //            model: playlist
        //            delegate: Text {
        //                id: te
        //                font.pixelSize: 16
        //                text: source
        //            }
        //        }

        //        MouseArea {
        //            anchors.fill: parent
        //            onPressed: {
        //                if (player.playbackState != Audio.PlayingState) {
        //                    player.play()
        //                } else {
        //                    player.pause()
        //                }
        //            }
        //        }
    }
}
