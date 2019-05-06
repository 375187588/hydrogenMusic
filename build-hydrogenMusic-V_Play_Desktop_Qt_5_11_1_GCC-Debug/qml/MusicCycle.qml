import QtQuick 2.0
import VPlayApps 1.0
import Treat 1.0

Page {
    id: musicCycle
    signal sendtreatBack
    signal searchBack
    signal addASong
    signal listenn(var vec)
    property alias selectMusicCycleDisplay:musicCycleDisplay
    property alias selectDisplay:selectDisplay
    property alias sendtreatCom:sendtreat
    property alias searchSongCom:searchSong
//    property alias treatDisCom:treat
    property var selectSong:[]
    opacity: messageRet.visible ? 0.3 : 1

    Loader{
        id:musicCycleDisplay
        anchors.fill: parent
        source: "treat.qml"
    }
    Loader{
        id:selectDisplay
        anchors.fill: parent
    }



//    Image {
//        id: mineBackgroundImage
//         source: "../../hydrogenMusic/assets/img/writeWalls.jpg"
//        anchors.fill: parent
//         //opacity: 0.2    all image are both opacity
//        Image {
//            id: mineOrnamentImage
//            source: "../../hydrogenMusic/assets/img/grey.png"
//            anchors.fill: parent
//            z:1
//            opacity: 0.2
//        }
//    }

    Component{
        id:sendtreat
        Column {
            spacing: sp(3)
            Rectangle {
                id: ret
                width: parent.width
                height: parent.height * 0.1
                color: "#CDC0B0"
                IconButton {
                    id: retPictrue
                    icon: IconType.arrowleft
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    onClicked: {
                        sendtreatBack()
                    }
                }
                Text {
                    id:t1
                    text: qsTr("发圈子")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: retPictrue.right
                    font.pixelSize: 20
                }
                Text {
                    id:t2
                    text: qsTr("发送")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    font.pixelSize: 15
                    anchors.rightMargin: sp(20)
                    color: "grey"

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            if(selectSong) {
                                control.sendMessage("treat send "+control.ID+" || "+selectSong[0]+" || "+selectSong[1]+" || "+selectSong[2]+" || "+selectSong[3]+" || "+t.text)
                            }
                        }
                    }
                }

            }
            Canvas {
                id: canvas
                width: parent.width
                height: parent.height * 0.4
                opacity: 0.6
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 2
                    ctx.strokeStyle = "#F5F5DC"
                    ctx.fillStyle = "#F5F5DC"
                    ctx.beginPath()
                    ctx.moveTo(parent.x,parent.y)
                    ctx.lineTo(parent.x + parent.width,parent.y)
                    ctx.lineTo(parent.x + parent.width,parent.y + parent.height)
                    ctx.lineTo(parent.x,parent.y + parent.height)
                    ctx.closePath()
                    ctx.fill()
                    ctx.stroke()

                    ctx.strokeStyle = "grey"
                    ctx.beginPath()
                    ctx.moveTo(parent.x + sp(3),parent.y)
                    ctx.lineTo(parent.x + sp(3),parent.y + parent.height)
                    ctx.closePath()
                    ctx.stroke()

                    ctx.beginPath()
                    ctx.moveTo(parent.x + parent.width - sp(3),parent.y)
                    ctx.lineTo(parent.x + parent.width - sp(3),parent.y + parent.height)
                    ctx.closePath()
                    ctx.stroke()
                }
                Flickable {
                    id: flick
                    anchors.fill: parent
                    contentWidth: parent.width
                    contentHeight: t.contentHeight
                    clip: true
                    //TextEdit yinggai guiding zhineng xie duoshao zishu, danshi zhege gongneng meizuo
                    TextEdit{
                        id:t
                        height: canvas.height
                        width: parent.width-sp(8)
                        x:parent.x+sp(4)
                        horizontalAlignment: TextInput.AlignLeft
                        selectByMouse: true
                        mouseSelectionMode: TextInput.SelectCharacters
                        selectedTextColor: "black" //设置选择文本的字体颜色
                        selectionColor: "white"    //设置选择框的颜色
                        wrapMode: TextEdit.Wrap
                        cursorVisible:true
                        font.pointSize: 14
                        focus: true
                        color: "black"
                        onContentHeightChanged: {
                            //                            console.log("cursorPosition: "+cursorPosition+"positionAt(x,y+width):"+positionAt(x,flick.contentY+height-sp(22)))
                            if(cursorPosition>positionAt(x,flick.contentY+height-sp(22))){
                                flick.contentY+=sp(22)
                                //                                console.log(flick.contentY)
                            }
                        }

                    }
                }
            }
            Rectangle {
                id: select
                width: parent.width
                height: parent.height * 0.07
                color: "#F5F5DC"

                Text {
                    id:t3
                    text: qsTr("配上音乐")
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: sp(20)
                    font.pixelSize: 20
                    color: "grey"
                }

                IconButton {
                    id: selectmusic
                    icon: IconType.arrowright
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                }

                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        parent.color = "#EEE8CD"
                    }
                    onReleased: {
                        parent.color = "#F5F5DC"
                        addASong()
                    }
                }
            }

        }
    }

    Component{
        id:searchSong
        OrdinarySearchfor{
            anchors.fill: parent
            onOrdinarySearchforpageBack: {
                selectSong = song
                searchBack()
            }
        }
    }

    Rectangle {
        id: messageRet
        color: "white"
        border.color: "black"
        //        border.width: sp(1)
        height: dp(30)
        width: dp(150)
        anchors.centerIn: parent
        radius: 20
        visible: false
        AppText {
            id: message
            anchors.fill: parent
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            color: "black"
            visible: true
            font.pixelSize: sp(12)
            font.bold: sp(5)
        }
    }

    Timer {
        id: showTime
        interval: 1000
        repeat: false
        onTriggered: {
            messageRet.visible = false
        }
    }

    Connections {
        target: control
        onSendtreatOk:{
            sendtreatBack()
            message.text = isOK
            messageRet.visible = true
            showTime.restart()
            if(isOK === "ok") control.sendMessage("treat all")
        }

    }

}
