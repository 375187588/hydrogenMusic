import QtQuick 2.9

Item {
    id:root
    property alias text: label.text
    signal clicked
    Rectangle {
        id: button
        //x: 12
        //y: 12
        width: 116
        height: 26
        color: "lightsteelblue"
        border.color: "slategrey"
        Text {
            id:label
            anchors.centerIn: parent
            text: "Start"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                //status.text = "Button clicked!"
                root.clicked()
            }
        }
    }
//    Text {
//        id: status
//        text: qsTr("Waiting...")
//        //x: 12
//        //y: 76
//        width: 116
//        height: 116
//        horizontalAlignment: Text.AlignHCenter
//    }
}
