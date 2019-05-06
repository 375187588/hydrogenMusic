import QtQuick 2.0
import QtQuick.Controls 2.2
Item {
    property var head:["推荐歌曲","排行榜","最近常听","歌曲分类","歌单"]
    property var songStyle:["经典","日韩","影视","古风","古典","跑步","酒吧","车载","伤感","摇滚","抖音","网络歌曲"]
    property int headFocus:2
//    property alias loadShow: somethingShow.sourceComponent
    property bool loadShow:(sheet.visible || style.visible)
    Rectangle{
        id:allShow
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*0.8
        height: parent.height
        Rectangle{
            id:headS
            anchors.top:parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: parent.height*0.15
            Row{
                anchors.centerIn: parent.Center
                spacing:sp(40)
                Repeater {
                    id: rep1
                    model: 5
                    anchors.centerIn: parent
                    Text {
                        id:t2
                        text: head[index]
                        anchors.centerIn: parent.Center
                        font.pixelSize: headFocus == index ? 15 : 10

                        MouseArea{
                            anchors.fill: parent
                            onClicked: headFocus = index
                        }

                        Behavior on font.pixelSize {
                            NumberAnimation {
                                duration: 250
                            }
                        }
                    }
                }
            }

        }

        Rectangle
        {
            id: sheet
            anchors.top:headS.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: parent.height*0.85
            visible: headFocus == 4 ? true :false

            Grid
            {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 4
                Repeater
                {
                    model: 8
                    Rectangle
                    {
                        width: sheet.width/5
                        height: width
                        color: "#DEB887"
                        radius: width/4
//                        Text
//                        {
//                            anchors.centerIn: parent
//                            color: "black"
//                            text: "Cell " + index
//                        }
                    }
                }
            }
        }

        Rectangle
        {
            id: style
            anchors.top:headS.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: parent.height*0.85
            visible: headFocus == 3 ? true :false


            Grid
            {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 4
                Repeater
                {
                    model: 12
                    Rectangle
                    {
                        width: sheet.width/5
                        height: width/2
                        color: "#CDCD00"
                        radius: width/5
                        Text
                        {
                            anchors.centerIn: parent
                            color: "black"
                            text: songStyle[index]
                        }
                    }
                }
            }
        }

//        Loader{
//            id:somethingShow
//            anchors.top:headS.bottom
//            width: parent.width*0.8
//            height: parent.height*0.85
//            anchors.horizontalCenter: parent.horizontalCenter
//            sourceComponent: headFocus == 4 ? sheet :(headFocus == 3 ? style :null)
//        }

//        Component{
//            id:style
//            Rectangle
//            {
//                anchors.fill: parent
//                Grid
//                {
//                    width: parent.width
//                    height: parent.height
//                    anchors.margins: 8
//                    spacing: 4
//                    Repeater
//                    {
//                        model: 12
//                        Rectangle
//                        {
//                            width: sheet.width/5
//                            height: width/2
//                            color: "#CDCD00"
//                            radius: width/5
//                            Text
//                            {
//                                anchors.centerIn: parent
//                                color: "black"
//                                text: songStyle[index]
//                            }
//                        }
//                    }
//                }
//            }
//        }

//        Component{
//            id:sheet
//            Rectangle
//            {
//                anchors.fill: parent
//                Grid
//                {
//                    width: parent.width
//                    height: parent.height
//                    anchors.margins: 8
//                    spacing: 4
//                    Repeater
//                    {
//                        model: 8
//                        Rectangle
//                        {
//                            width: sheet.width/5
//                            height: width
//                            color: "#DEB887"
//                            radius: width/4
//                        }
//                    }
//                }
//            }
//        }


    }
}
