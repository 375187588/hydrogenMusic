import QtQuick 2.0
import VPlayApps 1.0
import "../qml/myscript.js" as Logic

Page {
    id: songlis
    property var songVec: []
    signal listenThis(var vec)
    signal wantUpload

    Component {
        id: list
        AppFlickable {
            id: appflickable
            anchors.fill: parent
            Column {
                Repeater {
                    id: rep1
                    model: personal.songlis.length / 6

                    Rectangle {
                        id: rec
                        color: "#CCCCCC"
                        border.color: "grey"
                        //        border.width: sp(1)
                        height: dp(40)
                        width: songlis.width
                        radius: 20
                        focus: true
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            color: "black"
                            font.pixelSize: sp(12)
                            font.bold: sp(5)
                            text: songVec[index * 6 + 4]
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                parent.opacity = 0.3
                            }
                            onReleased: {
                                parent.opacity = 1
                                var temvec = []
                                for (var i = 0; i < 6; i++) {
                                    temvec.push(Logic.transToString(
                                                    songVec[index * 6 + i]))
                                }
                                listenThis(temvec)
                            }
                        }
                    }
                }
            }
        }
    }

    Loader {
        id: songListLoa
        //        sourceComponent: list
        anchors.fill: parent
    }

    IconButton {
        id: newAdd
        icon: IconType.upload
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: dp(50)
        width: dp(50)
        onClicked: {
            wantUpload()
        }
    }

    Component {
        id: noList
        AppText {
            color: "#454545"
            visible: true
            font.pixelSize: sp(12)
            font.bold: sp(5)
            text: "Sorry, the power of exhausting the land has not been found."
        }
    }

    Connections {
        target: personal
        onSongList: {
            newAdd.visible = true
            if (vec.length !== 1) {
                songVec = vec
                songListLoa.sourceComponent = list
            }
        }
        onSearchOk: {
            newAdd.visible = false
            if (vec.length !== 1) {
                songVec = vec
                songListLoa.sourceComponent = list
            } else {
                songListLoa.sourceComponent = noList
            }
        }
    }
}
