import VPlayApps 1.0
import QtQuick 2.0
import qt.Lyric 1.0

import "../qml/myscript.js" as Logic

Page {
    id: lyricspage
    title: qsTr("Lyrics")
    signal lyricOk

    property alias lyricsTime: time
    property alias lAddr: lyric2.lAddress

    onLAddrChanged: {
        lyric2.readLyric()
    }

    LyricMessage {
        id: lyric2
        onOk: {
            lyricOk()
            show.sourceComponent = appflickable
        }
    }

    Timer {
        id: time
        interval: 300
        running: false
        repeat: true
        property var at: Logic.highLightLyric(current)
        property int current: music.position
        onTriggered: {
            rep2.itemAt(Logic.highLightLyric(current)).color = "red"
            if (Logic.highLightLyric(current) !== 0)
                rep2.itemAt(Logic.highLightLyric(
                                current) - 1).color = Theme.secondaryTextColor
        }
    }

    Loader {
        id: show
        anchors.fill: parent
        anchors.centerIn: parent
    }

    Component {
        id: appflickable
        AppFlickable {
            contentWidth: width
            contentHeight: lyricContent.height

            Column {
                id: lyricContent

                width: parent.width
                height: parent.height
                Repeater {
                    id: rep1
                    model: lyric2.lheader.length

                    Text {
                        id: t1
                        anchors.horizontalCenter: lyricContent.horizontalCenter
                        font.pixelSize: sp(12)
                        wrapMode: Text.WordWrap
                        color: Theme.secondaryTextColor
                        text: lyric2.lheader[index]
                    }
                }

                Repeater {
                    id: rep2
                    model: lyric2.lyricContent.length

                    Text {
                        id: t0
                        anchors.horizontalCenter: lyricContent.horizontalCenter
                        font.pixelSize: sp(12)
                        wrapMode: Text.WordWrap
                        color: Theme.secondaryTextColor
                        text: lyric2.lyricContent[index]
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                rep2.itemAt(time.at).color = Theme.secondaryTextColor
                                color = "red"
                                music.seek(lyric2.startTime[index])
                                time.restart()
                            }
                        }
                    }
                }
            }
        }
    }

    function cleanHightLight() {
        rep2.itemAt(time.at).color = Theme.secondaryTextColor
        time.stop()
    }
}
