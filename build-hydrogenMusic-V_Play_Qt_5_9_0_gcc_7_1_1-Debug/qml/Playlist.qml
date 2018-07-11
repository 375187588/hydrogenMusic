import QtQuick 2.0
import VPlayApps 1.0
import "../qml/myscript.js" as Logic

Page {
    id: playlistlis
    property var listVec: personal.playlist
    signal listen(var vec)

    Rectangle {
        id: name
        anchors.fill: parent
        color: "grey"
        AppFlickable {
            id: appflickable
            anchors.fill: parent
            Column {
                Repeater {
                    id: rep1
                    model: listVec.length / 4

                    Rectangle {
                        id: rec
                        color: "#CCCCCC"
                        border.color: "grey"
                        //        border.width: sp(1)
                        height: dp(40)
                        width: playlistlis.width
                        radius: 20
                        focus: true
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            color: "black"
                            font.pixelSize: sp(12)
                            font.bold: sp(5)
                            text: listVec[index * 4 + 3]
                        }
                        IconButton {
                            id: addToList
                            icon: IconType.arrowup
                            anchors.right: deletethis.left
                            anchors.bottom: parent.bottom
                            onClicked: {
                                personal.upList(index)
                            }
                        }

                        IconButton {
                            id: deletethis
                            icon: IconType.times
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            onClicked: {
                                personal.deleteInPlaylist(index)
                            }
                        }

                        MouseArea {
                            height: parent.height
                            width: parent.width * 0.7
                            onPressed: {
                                parent.opacity = 0.3
                            }
                            onReleased: {
                                parent.opacity = 1
                                var temvec = []
                                for (var i = 0; i < 4; i++) {
                                    temvec.push(Logic.transToString(
                                                    listVec[index * 4 + i]))
                                }
                                listen(temvec)
                            }
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: personal
        onPlaylistChange: {
            console.log("nvoisdnvdoislvnol" + listVec.length)
            listVec = personal.playlist
        }
    }
}
