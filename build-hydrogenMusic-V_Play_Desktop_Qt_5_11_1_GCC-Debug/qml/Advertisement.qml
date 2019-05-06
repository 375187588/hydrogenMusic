import QtQuick 2.0
import QtQuick.Controls 2.2
Item {
    property alias currentAdver: listView.currentIndex
    property var imageurls:["../../hydrogenMusic/assets/advertise/0.jpg","../../hydrogenMusic/assets/advertise/1.jpg","../../hydrogenMusic/assets/advertise/2.jpg","../../hydrogenMusic/assets/advertise/3.jpg","../../hydrogenMusic/assets/advertise/4.jpg"]




    Rectangle{
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*0.8
        height: parent.height*0.8
        ListView{
            id:listView
            anchors.fill: parent
            model: 5
            orientation:ListView.Horizontal
            highlightRangeMode: ListView.StrictlyEnforceRange
            currentIndex:2
            spacing: sp(2)
            preferredHighlightBegin:parent.width/2-listView.width/4 //开始时候高光的位置
            preferredHighlightEnd: preferredHighlightBegin + listView.width/2
            delegate: Rectangle{
                width: listView.currentIndex === index ? listView.width/2 : listView.width/4
                height: listView.currentIndex === index ? listView.height  : listView.height * 0.8        //origin is 0.9  0.7 now  is 1 0.8
                //color: listView.currentIndex === index ? "#CDCD00":"#DEB887"
                anchors.verticalCenter: parent.verticalCenter
                visible: (listView.currentIndex === index || listView.currentIndex === index-1 ||
                          listView.currentIndex === index+1) ? true : false
//                Label{
//                    anchors.centerIn: parent
//                    font.pointSize: 10
//                    text: "广告或推荐内容: "+index
//                }
                Image {
                    id: myAdvantage
                    anchors.fill: parent
                    source: imageurls[index]
                }

                Behavior on width {
                    NumberAnimation {
                        duration: 250
                    }
                }
                Behavior on height {
                    NumberAnimation {
                        duration: 250
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index
                    }
                }
            }
        }
    }

    Rectangle{
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*0.8
        height: parent.height*0.2
        Row{
            anchors.centerIn: parent
            spacing:sp(6)
            Repeater {
                id: rep1
                model: 5
                anchors.centerIn: parent
                Rectangle {
                    width: currentAdver == index ? sp(5) :sp(4)
                    height: width
                    color: currentAdver == index ? "black":"grey"
                    radius: width/2

                    Behavior on width {
                        NumberAnimation {
                            duration: 250
                        }
                    }
                    Behavior on height {
                        NumberAnimation {
                            duration: 250
                        }
                    }
                }
            }
        }

    }

    Timer {
        id: time
        interval: 2500
        running: true
        repeat: true
        onTriggered: {
            if(listView.currentIndex == listView.count-1)
            {
                listView.currentIndex = 0
            }else{
                listView.currentIndex++
            }
        }
    }
}
