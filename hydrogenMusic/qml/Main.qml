import VPlayApps 1.0
import QtQuick 2.0
import QtMultimedia 5.5
import qt.Lyric 1.0
import qt.OneLineLyric 1.0

App {

    NavigationStack {

        Page {
            id: page
            title: qsTr("Hydrogen music")

            LyricMessage {
                id: lyric2
            }

            MediaPlayer {
                //可以播放音频和视频
                id: music
                source: "../assets/music/Taylor Swift - Love Story.mp3"
                //             autoPlay: true
            }

            //            AppFlickable {
            //                anchors.fill: parent
            //                anchors.centerIn: parent
            //                contentWidth: width
            //                contentHeight: content.height
            Rectangle {
                id: rec
                border.color: "black"
                width: parent.width
                height: 55
                property OneLineLyricMessage a: null
                Image {
                    id: musicPictrue
                    source: "../assets/img/audio-x-mpeg.svg"
                }
                IconButton {
                    id: playPictrue
                    icon: IconType.play
                    anchors.top: musicPictrue.bottom
                    anchors.left: musicPictrue.left
                    onClicked: music.play()
                }
                IconButton {
                    id: stopPictrue
                    icon: IconType.stop
                    anchors.left: playPictrue.right
                    anchors.top: musicPictrue.bottom
                    onClicked: {
                        music.stop()
                        //                                        a = lyric2.lyric[0]
                        //                                        if (lyric2.lyric.length > 0)
                        //                                            console.log(a.startTime)
                    }
                }
            }
            Column {
                anchors.top: rec.bottom
                anchors.left: parent.left

                Text {
                    id: t0
                    width: parent.width
                    //anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: sp(12)
                    //horizontalAlignment: Text.AlignJustify
                    wrapMode: Text.WordWrap
                    //color: Theme.secondaryTextColor
                    text: /*lyric2.Lheader[0]*/ lyric2.lyric[3].lyricContent
                }
                Text {
                    id: t1
                    anchors.top: t0.bottom
                    width: parent.width
                    //anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: sp(12)
                    //horizontalAlignment: Text.AlignJustify
                    wrapMode: Text.WordWrap
                    //color: Theme.secondaryTextColor
                    text: lyric2.Lheader[1]
                }
                Text {
                    id: t2
                    anchors.top: t1.bottom
                    width: parent.width
                    //anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: sp(12)
                    //horizontalAlignment: Text.AlignJustify
                    wrapMode: Text.WordWrap
                    //color: Theme.secondaryTextColor
                    text: lyric2.Lheader[2]
                }
                Text {
                    id: t3
                    anchors.top: t2.bottom
                    width: parent.width
                    //anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: sp(12)
                    //horizontalAlignment: Text.AlignJustify
                    wrapMode: Text.WordWrap
                    //color: Theme.secondaryTextColor
                    text: lyric2.Lheader[3]
                }
            }
        }
    }
}
