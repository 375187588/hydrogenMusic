import QtQuick 2.0

Rectangle {
    id: root
    width: 480
    height: 480
    color: "white"
    border.color: Qt.lighter(color)
    signal clicked
    property int index
    function changecolor() {}

    Column {
        id: column
        anchors.centerIn: parent
        spacing: 8

        Square {
            textscale: 2
            text: "song1"
            //            onClicked: {
            //                root.clicked()
            //                root.index = 0
            //                parent.text = "clicked"
            //                console.log("clicked()")
            //            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.clicked()
                    root.index = 1
                    parent.text = "song1 clicked"
                    //parent.text = "song1"
                    console.log(root.index)
                }
            }
        }
        Square {
            textscale: 2
            text: "song2"
            //            onClicked: {
            //                root.clicked()
            //                root.index = 1
            //            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.clicked()
                    root.index = 2
                    parent.text = "song2 clicked"
                }
            }
        }

        Square {
            textscale: 2
            text: "song3"
            //            onClicked: {
            //                root.clicked()
            //                root.index = 1
            //            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.clicked()
                    root.index = 3
                    parent.text = "song3 clicked"
                }
            }
        }
        Square {
            textscale: 2
            text: "song4"
            //            onClicked: {
            //                root.clicked()
            //                root.index = 1
            //            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.clicked()
                    root.index = 4
                    parent.text = "song4 clicked"
                }
            }
        }
        Square {
            textscale: 2
            text: "song5"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.clicked()
                    root.index = 5
                    parent.text = "song5 clicked"
                }
            }
        }
    }
}
