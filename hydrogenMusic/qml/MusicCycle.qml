import QtQuick 2.0
import VPlayApps 1.0

Page {
    id: musicCycle
    signal sendtreatBack
    signal searchBack
    signal addASong
    property alias selectMusicCycleDisplay:musicCycleDisplay
    property alias selectDisplay:selectDisplay
    property alias sendtreatCom:sendtreat
    property alias searchSongCom:searchSong
    property alias treatDisCom:treat

    property var selectSong

    Loader{
        id:musicCycleDisplay
        anchors.fill: parent
        sourceComponent: treat
    }
    Loader{
        id:selectDisplay
        anchors.fill: parent
    }

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
        id:treat
        Item {
            Rectangle {
                width: parent.width
                height: parent.height
                anchors.top: parent.top
                color: "red"
            }
        }

    }
    Component{
        id:searchSong
        OrdinarySearchfor{
            anchors.fill: parent
            onOrdinarySearchforpageBack: {
                searchSong = song
                searchBack()
            }
        }
    }


}
