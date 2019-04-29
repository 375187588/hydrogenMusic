import VPlayApps 1.0
import QtQuick 2.0

import "../qml/myscript.js" as Logic

Page {
    id: lyricspage
    title: qsTr("Lyrics")
    //    property alias lyricsTime: time

        Timer {
            id: time
            interval: 100
            running: true
            repeat: true
            property var at: highLightLyric(current)
            property int current: music.position //hyMediaPlayer.get_current_schedule()
            onTriggered: {
                listView.currentIndex = highLightLyric(current)
            }
        }

    //    Column {
    //        id: lyricContent

    //        width: parent.width
    //        height: parent.height
    //        Repeater {
    //            id: rep1
    //            model: qtLyric.lheader.length

    //            Text {
    //                id: t1
    //                anchors.horizontalCenter: lyricContent.horizontalCenter
    //                font.pixelSize: sp(12)
    //                wrapMode: Text.WordWrap
    //                color: Theme.secondaryTextColor
    //                text: qtLyric.lheader[index]
    //            }
    //        }

    //        Repeater {
    //            id: rep2
    //            model: qtLyric.lyricContent.length

    //            Text {
    //                id: t0
    //                anchors.horizontalCenter: lyricContent.horizontalCenter
    //                font.pixelSize: sp(12)
    //                wrapMode: Text.WordWrap
    //                color: Theme.secondaryTextColor
    //                text: qtLyric.lyricContent[index]
    //                MouseArea {
    //                    anchors.fill: parent
    //                    onClicked: {
    //                        rep2.itemAt(time.at).color = Theme.secondaryTextColor
    //                        color = "red"
    //                        music.seek(qtLyric.startTime[index])
    //                        time.restart()
    //                    }
    //                }
    //            }
    //        }
    //    }
    Item {
        width: parent.width
        height: parent.height
        ListView{
            id:listView
            anchors.fill: parent
            model: qtLyric.lyricContent.length
            highlightRangeMode: ListView.StrictlyEnforceRange
            spacing: sp(2)
            preferredHighlightBegin:parent.height/4 //开始时候高光的位置
            preferredHighlightEnd: preferredHighlightBegin + sp(30)
            delegate: Rectangle{
                width: parent.width
                height: sp(30)
                anchors.horizontalCenter: parent.horizontalCenter
                //            visible: (listView.currentIndex === index || listView.currentIndex === index-1 ||
                //                      listView.currentIndex === index+1) ? true : false

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: sp(12)
                    wrapMode: Text.WordWrap
                    color: listView.currentIndex === index? "red" :Theme.secondaryTextColor
                    text: qtLyric.lyricContent[index]
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index
                    }
                }
            }
            onCurrentIndexChanged: {
                music.seek(qtLyric.startTime[currentIndex])
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
