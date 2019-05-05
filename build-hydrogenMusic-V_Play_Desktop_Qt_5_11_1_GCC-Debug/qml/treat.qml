import QtQuick 2.0

Item {
    property var treatVec: []
    ListView{
        id:listView
        anchors.fill: parent
        model: treatVec
        highlightRangeMode: ListView.StrictlyEnforceRange //currentIndex随着一起变化
        spacing: sp(1)
        delegate: Rectangle{
            height: dp(40)+name.height+textshow.height
            width: parent.width
            radius: 10
            border.width: sp(1)

            Text {
                id:name
                text: ID
                clip: true
                wrapMode: Text.WordWrap
                anchors.leftMargin: sp(20)
                anchors.left: parent.left
            }

            Text {
                clip: true
                wrapMode: Text.WordWrap
                anchors.leftMargin: sp(20)
                anchors.left: name.right
                text: timee
            }

            Text {
                id:textshow
                clip: true

                anchors.topMargin: sp(6)
                anchors.top: name.bottom
                anchors.left: name.left
                text: textt
                elide: Text.ElideRight
                width: parent.width*0.8
                wrapMode: Text.WordWrap
//                height: lineCount < 4?lineHeight * lineCount*sp(20):lineHeight *4*sp(20)
                //lineCount always is 1  can't use
            }

            Rectangle {
                id: songshow
                color: "#CCCCCC"
                height: sp(25)
                width: parent.width*0.6
                radius: 10
                focus: true
                anchors.top: textshow.bottom
                anchors.left: textshow.left
                Text {
                    anchors.top: parent.top
                    //anchors.topMargin: 8
                    anchors.left: parent.left
                    //anchors.leftMargin: 30
                    color: "black"
                    font.pixelSize: sp(12)
                    font.bold: sp(5)
                    text: songg[0]
                }
                Text {
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    //anchors.leftMargin: 30
                    color: "grey"
                    font.pixelSize: sp(7)
                    font.bold: sp(1)
                    text: songg[1] + ' - ' + songg[2]
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        control.addToL(songg[0],songg[1],songg[2],songg[3])
                        listenn(songg)
                    }
                }
            }


        }
    }
    Connections {
        target: control
        onTreatShow:{
            treatVec = control.treat
        }
    }
}
