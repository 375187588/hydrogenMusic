import VPlayApps 1.0
import QtQuick 2.0

import "../qml/myscript.js" as Logic

Page {
    id: lyricspage
    title: qsTr("Lyrics")
    property alias lyricsTime: time

    Timer {
        id: time
        interval: 100
        running: false
        repeat: true
        property var at: highLightLyric(current)
        property int current: hyMediaPlayer.get_current_schedule()
        onTriggered: {
            //            console.log(hyMediaPlayer.get_current_schedule())
            rep2.itemAt(highLightLyric(hyMediaPlayer.get_current_schedule(
                                           ))).color = "red"
            if (highLightLyric(hyMediaPlayer.get_current_schedule()) !== 0)
                rep2.itemAt(highLightLyric(
                                hyMediaPlayer.get_current_schedule(
                                    )) - 1).color = Theme.secondaryTextColor
        }
    }

    Column {
        id: lyricContent

        width: parent.width
        height: parent.height
        Repeater {
            id: rep1
            model: qtLyric.lheader.length

            Text {
                id: t1
                anchors.horizontalCenter: lyricContent.horizontalCenter
                font.pixelSize: sp(12)
                wrapMode: Text.WordWrap
                color: Theme.secondaryTextColor
                text: qtLyric.lheader[index]
            }
        }

        Repeater {
            id: rep2
            model: qtLyric.lyricContent.length

            Text {
                id: t0
                anchors.horizontalCenter: lyricContent.horizontalCenter
                font.pixelSize: sp(12)
                wrapMode: Text.WordWrap
                color: Theme.secondaryTextColor
                text: qtLyric.lyricContent[index]
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        rep2.itemAt(time.at).color = Theme.secondaryTextColor
                        color = "red"
                        music.seek(qtLyric.startTime[index])
                        time.restart()
                    }
                }
            }
        }
    }

    function cleanHightLight() {
        rep2.itemAt(time.at).color = Theme.secondaryTextColor
        time.stop()
    }

    function highLightLyric(current) {
        var sum = qtLyric.startTime.length
        for (var i = 0; i < sum; i++) {
            var highLight = qtLyric.startTime[i]
            if (current > highLight || current === highLight) {
                continue
            } else {
                if (i > 0)
                    return i - 1
            }
        }
    }
}
