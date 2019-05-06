import QtQuick 2.0
import VPlayApps 1.0

Page {
    id: minepage
    signal showlist(var sheetName)
    signal addSongsheetpageBack()
    signal submit(var songsheetName)
    property var songsheetVec: []
    property alias createSongsheetLoader:createSongsheet

    Image {
        id: mineBackgroundImage
         source: "../../hydrogenMusic/assets/img/writeWalls.jpg"
        anchors.fill: parent
         //opacity: 0.2    all image are both opacity
        Image {
            id: mineOrnamentImage
            source: "../../hydrogenMusic/assets/img/grey.png"
            anchors.fill: parent
            z:1
            opacity: 0.2
        }
    }

    Column {
        id:songsheetInfo
        opacity: createSongsheet.status ? 0.3 : 1
        enabled: createSongsheet.status ? false :true
        anchors.fill: parent
        spacing: sp(10)
        Column {
            width: parent.width
            height: ret.height + sheet.height
            spacing: sp(2)
            Rectangle {
                id: ret
                width: parent.width
                height: dp(40)
                color: "#CCCCCC"
                IconButton {
                    id: retPictrue
                    icon: IconType.arrowdown
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    onClicked: {
                        sendtreatBack()
                    }
                }
                Text {
                    id:t1
                    text: qsTr("创建的歌单")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: retPictrue.right
                    font.pixelSize: 20
                }
                IconButton {
                    icon: IconType.plus
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: sp(20)
                    onClicked: {
                        createSongsheet.sourceComponent = createSongsheetCom
                    }
                }

            }


            Column{
                id:sheet
                //y:parent.y + ret.height
                width: parent.width
                height: dp(40)*songsheetVec.length
                //            ListView{
                //                id:listView
                //                anchors.fill: parent
                //                model: songsheetVec.length
                //                highlightRangeMode: ListView.StrictlyEnforceRange //currentIndex随着一起变化
                //                spacing: sp(1)
                //                delegate: Rectangle{
                //                    color: mouse_area.containsMouse ?"#EDEDED":"#CCCCCC"
                //                    height: dp(40)
                //                    width: parent.width
                //                    radius: 10
                //                    Text {
                //                        anchors.left: parent.left
                //                        anchors.leftMargin: sp(20)
                //                        anchors.verticalCenter: parent.verticalCenter
                //                        text: songsheetVec[index]
                //                    }
                //                    MouseArea{
                //                        id:mouse_area
                //                        anchors.fill: parent
                //                        hoverEnabled:true
                //                        onClicked: showlist(songsheetVec[index])
                //                    }
                //                }


                //            }
                Repeater {
                    id: listView
                    anchors.fill: parent
                    model: songsheetVec.length
                    Rectangle{
                        color: mouse_area.containsMouse ?"#EDEDED":"#CCCCCC"
                        height: dp(40)
                        width: parent.width
                        radius: 10
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: sp(20)
                            anchors.verticalCenter: parent.verticalCenter
                            text: songsheetVec[index]
                        }
                        MouseArea{
                            id:mouse_area
                            anchors.fill: parent
                            hoverEnabled:true
                            onClicked: showlist(songsheetVec[index])
                        }
                    }
                }
            }
        }


        Column {
            width: parent.width
            height: parent.height
            spacing: sp(2)
            Rectangle {
                id: treathead
                width: parent.width
                height: dp(40)
                color: "#CCCCCC"

                Text {
                    text: qsTr("我的动态")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: sp(20)
                    font.pixelSize: 20
                }

            }
            Loader{
                width: parent.width
                height: parent.height-sheet.y-sheet.height
                source: "treat.qml"
            }
        }
    }

    Loader{
        id:createSongsheet
        width: parent.width * 0.7
        height: parent.height * 0.4
        anchors.centerIn: parent
    }

    Component{
        id:createSongsheetCom
        Rectangle {
            width: parent.width
            height: parent.height
            border.color: "grey"
            border.width: 1
            Column {
                width: parent.width
                height: parent.height
                spacing: sp(30)
                Text {
                    text: qsTr("新建歌单")
                    anchors.left: parent.left
                    anchors.leftMargin: sp(10)
                    font.pixelSize: 25
                    height: parent.height * 0.15
                }

                Canvas {
                    id: canvas
                    width: parent.width
                    height: parent.height * 0.3
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.lineWidth = 1
                        ctx.strokeStyle = "grey"
                        ctx.beginPath()
                        ctx.moveTo(textfield.x+sp(6),textfield.y+textfield.height+sp(6))
                        ctx.lineTo(textfield.x+width-sp(6),textfield.y+textfield.height+sp(6))
                        ctx.closePath()
                        ctx.stroke()


                    }
                    AppTextField {
                        id:textfield
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: sp(6)
                        width: parent.width-sp(6)
                        cursorColor: "grey"
                        text: "请输入歌单标题"
                        textColor: "grey"
                        clearsOnBeginEditing:true
                    }
                }
                Row {
                    id: ret
                    width: parent.width*0.4
                    height: parent.height*0.3
                    anchors.right: parent.right
                    spacing: sp(20)
                    Text {
                        text: qsTr("取消")
                        font.pixelSize: 20
                        MouseArea {
                            anchors.fill: parent
                            onClicked: addSongsheetpageBack()
                        }
                    }
                    Text {
                        id:sub
                        text: qsTr("提交")
                        font.pixelSize: 20
                        MouseArea {
                            anchors.fill: parent
                            onClicked: submit(textfield.text)
                        }
                    }
                }
            }
        }


    }

    Connections {
        target: control
        onSongsheetAll: {
            songsheetVec = []
            if (control.songSheet.length !== 0) {
                songsheetVec = control.songSheet
            }
        }
        onSongsheetAddOk: if(isOK == "ok") createSongsheet.sourceComponent = null
    }

    //    Column {
    //        height: parent.height
    //        width: parent.width
    //        spacing: sp(3)
    //        Rectangle {
    //            id: ilike
    //            color: "#CCCCCC"
    //            height: dp(40)
    //            width: parent.width

    //            IconButton {
    //                id: ili
    //                x: sp(6)
    //                icon: IconType.heartbeat
    //                anchors.left: parent.left
    //                anchors.verticalCenter: parent.verticalCenter
    //                width: parent.width * 0.2
    //                height: parent.height
    //            }

    //            Text {
    //                anchors.verticalCenter: parent.verticalCenter
    //                anchors.left: ili.right
    //                anchors.leftMargin: sp(10)
    //                color: "black"
    //                font.pixelSize: 20
    //                font.bold: sp(5)
    //                text: "我喜欢"
    //            }
    //            MouseArea {
    //                anchors.fill: parent
    //                onPressed: {
    //                    parent.opacity = 0.3
    //                }
    //                onReleased: {
    //                    parent.opacity = 1
    //                    ilikeshow()
    //                }
    //            }
    //        }

    //        Rectangle {
    //            id: download

    //            color: "#CCCCCC"
    //            height: dp(40)
    //            width: parent.width

    //            IconButton {
    //                id: dow
    //                x: sp(6)
    //                icon: IconType.download
    //                anchors.left: parent.left
    //                anchors.verticalCenter: parent.verticalCenter
    //                width: parent.width * 0.2
    //                height: parent.height
    //            }

    //            Text {
    //                anchors.verticalCenter: parent.verticalCenter
    //                anchors.left: dow.right
    //                anchors.leftMargin: sp(10)
    //                color: "black"
    //                font.pixelSize: 20
    //                font.bold: sp(5)
    //                text: "下载"
    //            }
    //            MouseArea {
    //                anchors.fill: parent
    //                onPressed: {
    //                    parent.opacity = 0.3
    //                }
    //                onReleased: {
    //                    parent.opacity = 1
    //                    downloadshow()
    //                }
    //            }
    //        }
    //    }
}
