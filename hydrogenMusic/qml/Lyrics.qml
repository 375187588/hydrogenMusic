import VPlayApps 1.0
import QtQuick 2.0
import qt.Lyric 1.0

import "../qml/myscript.js" as Logic

Page {
    id: page
    title: qsTr("Lyrics")

    property alias lyricsTime: time
    property alias currentHightLight: rep2
    LyricMessage {
        id: lyric2
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

    AppFlickable {
        id: appflickable
        anchors.fill: parent
        anchors.centerIn: parent
        contentWidth: width
        contentHeight: lyricContent.height

        Column {
            id: lyricContent

            Repeater {
                id: rep1
                model: lyric2.lheader.length

                Text {
                    id: t1
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

    function cleanHightLight() {
        rep2.itemAt(time.at).color = Theme.secondaryTextColor
        time.stop()
    }
}
