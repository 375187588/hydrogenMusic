import QtQuick 2.9

Rectangle {
    id: button
    property alias text: label.text
    property alias textscale:label.scale
    signal clicked
    width: 480
    height: 80
    color: "green"
    border.color: "slategrey"
    Text {
        id: label
        anchors.centerIn: parent
        text: "name"
        //scale: 2
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {            
            root.clicked()
        }
    }
}
