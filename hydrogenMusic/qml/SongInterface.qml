import QtQuick 2.0
import VPlayApps 1.0
import QtMultimedia 5.5
import QtQuick.Controls 1.1

Page {
    id: songinterfacepage
    title: qsTr("Hydrogen music")
    property var thisSong
    property string bigCover :"../assets/advertise/0.jpg"
    //-----xiaoyao--s--------
    property string add: "rtsp://0.0.0.0/"+thisSong[0].substring(0, thisSong[0].length)
    //-----xiaoyao--s--------
    property string prefixx: "../assets/music/"
    property var model:[IconType.arrowcircledown,IconType.arrowcircleoup,IconType.arrowcircleleft]
    signal songinterfaceBack
    property var realaddr;

    onThisSongChanged: {
        pausePictrue.paused = false
        pausePictrue.icon = IconType.pause
        //-----xiaoyao--s--------------
        //var addhead = "rtsp://0.0.0.0/"+thisSong

        realaddr="rtsp://0.0.0.0/"+control.switchname(thisSong[0].substring(0, thisSong[0].length))
        simplePlayer.openUrl(realaddr)
        console.log("kkkkkkkkkkkk"+thisSong[0].substring(0, thisSong[0].length - 1)+"jjj")
        //-----xiaoyao-----e------------
    }
    Component.onCompleted: control.sendMessage("searchCover "+thisSong[3])

//    MediaPlayer {
//        //可以播放音频和视频
//        id: music
//        autoPlay: true
//        source: prefixx + thisSong[0]

//    }

    IconButton {
        id: ret
        icon: IconType.arrowleft
        anchors.verticalCenter: l.verticalCenter
        anchors.left: parent.left
        onClicked: {
            songinterfaceBack()
        }
    }

    Label{
        id:l
        anchors.top: parent.top
        anchors.topMargin: sp(10)
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: sp(10)
        text: thisSong[0]
    }
    Label{
        anchors.top: l.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: sp(6)
        text: thisSong[1]
    }

    Connections {
        target: simplePlayer
        onEnd:{
            console.log("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjkskkks")
        }
    }

    Item
    {
        id:mainpart
        y:parent.height*0.2
        width: parent.width
        height: parent.height*0.5
        opacity: loa.sourceComponent ? 0.5 : 1
        enabled: loa.sourceComponent ? false : true
        ListView{
            id:listView
            anchors.fill: parent
            model: 2
            snapMode: ListView.SnapOneItem
            orientation:ListView.Horizontal
            highlightRangeMode: ListView.StrictlyEnforceRange
            delegate: Rectangle{
                width: listView.width
                height: listView.height
                //color: index%2 ? "red":"yellow"

                Loader{
                    visible: listView.currentIndex === 0 ? true : false
                    width: parent.width
                    height: parent.height
                    sourceComponent: one
                }

                Lyrics {
                    id: lyrics
                    visible: listView.currentIndex === 1 ? true : false
                    enabled: visible ? true : false
                    anchors.fill:parent
                    width: parent.width
                    height: parent.height
                }

            }
        }


    }

    Component{
        id:one
        Item {
            width: parent.width
            height: parent.height
            Row{
                width: parent.width
                height: parent.height
                x:parent.x+sp(10)
                spacing: sp(13)
                Rectangle{
                    width: parent.width/5
                    height: width
                    radius: height/2
                    border.width: sp(1.5)
                    anchors.verticalCenter: parent.verticalCenter
                    border.color: Theme.secondaryTextColor
                    Label{
                        anchors.centerIn: parent
                        font.pointSize: 15
                        text: "专"
                    }
                }
                Rectangle{
                    width: parent.width/2
                    height: width
                    radius: height/2
                    border.width: sp(1.5)
                    anchors.verticalCenter: parent.verticalCenter
                    border.color: Theme.secondaryTextColor

                    Image {
                        id:bigcoverr
                        anchors.fill: parent
                        source: bigCover
                    }
                }
                Rectangle{
                    width: parent.width/5
                    height: width
                    radius: height/2
                    border.width: sp(1.5)
                    anchors.verticalCenter: parent.verticalCenter
                    border.color: Theme.secondaryTextColor
                    Label{
                        anchors.centerIn: parent
                        font.pointSize: 15
                        text: "辑"
                    }
                }
            }
        }
    }


    Rectangle {
        id: re
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height * 0.1
        Image {
            id: musicPictrue
            source: "../assets/img/audio-x-mpeg.svg"
        }

        //        Rectangle {
        //            id: progressbar
        //            width: parent.width * 0.85
        //            height: sp(2)
        //            color: "black"
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            Rectangle {
        //                id: progress
        //                width: sp(5)
        //                height: sp(9)
        //                anchors.verticalCenter: parent.verticalCenter
        //                x: parent.x + (music.position / music.duration) * parent.width
        //            }
        //            MouseArea {
        //                width: parent.width
        //                height: progress.height
        //                onClicked: music.seek(
        //                               (mouseX - progressbar.x) / progressbar.width * music.duration)
        //            }

        //        }
        //xiaoyao--------s-----------
//        Slider {
//            id: progressbar
//            width: parent.width * 0.85
//            height: sp(2)
//            anchors.horizontalCenter: parent.horizontalCenter
//            maximumValue: music.duration //hyMediaPlayer.get_all_schedule()
//            value: music.position //hyMediaPlayer.get_current_schedule()
//            onValueChanged: music.seek(value)
//        }
         //xiaoyao--------s-----------
        Slider {
            id: progressbar
            width: parent.width * 0.85
            height: sp(2)
            anchors.horizontalCenter: parent.horizontalCenter
            //maximumValue: music.duration //hyMediaPlayer.get_all_schedule()
            //value: music.position //hyMediaPlayer.get_current_schedule()
            //onValueChanged: music.seek(value)
            property bool sync: false
            maximumValue:simplePlayer.getlength()
            onValueChanged: {
                if(!sync)
                    simplePlayer.setposition(value)
            }
            Timer{
                id:t
                running: true
                interval: 3000
                repeat: true
                onTriggered:
                {

                    //console.log("timer")
                    progressbar.sync=true

                    progressbar.value=simplePlayer.getpositon()
                    progressbar.maximumValue=simplePlayer.getlength()
                    progressbar.sync=false
                    //console.log(slider.maximumValue)
                }
            }
        }
        //-----xiaoyao----e----

        IconButton {
            id: pre
            icon: IconType.stepbackward
            anchors.right: pausePictrue.left
            anchors.top: pausePictrue.top
            onClicked: {
                var temp = []
                var index = control.currentSong(thisSong[3])
                if (index !== 0) {
                    temp.push(control.playlist[index-1].songName)
                    temp.push(control.playlist[index-1].singer)
                    temp.push(control.playlist[index-1].album)
                    temp.push(control.playlist[index-1].key)
                    thisSong = temp
                    var songname = temp[0]
                    songname = songname.substring(0, songname.length - 4)
                    qtLyric.readLyric(songinterfacepage.prefix + songname + ".lrc")
                }
            }
        }


//        IconButton {
//            id: pausePictrue
//            property bool paused: false
//            icon: IconType.pause
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.top: musicPictrue.bottom
//            onClicked: {
//                //play state
//                if (paused) {
//                    icon = IconType.pause
//                    music.play()
//                    //lyrics.lyricsTime.start()
//                    paused = false
//                    //                    hyMediaPlayer.play_multimedia()
//                } else {
//                    icon = IconType.play
//                    paused = true
//                    //lyrics.lyricsTime.running = false
//                    //                    hyMediaPlayer.pause_mulitimedia()
//                    music.pause()
//                }
//            }
//        }
        //xiaoyao----s----------
        IconButton {
            id: pausePictrue
            property bool paused: true
            icon: IconType.pause
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: musicPictrue.bottom
            onClicked: {
                //play state
                if (paused) {
                    icon = IconType.pause
                    //music.play()
                    console.log(add)
                    //simplePlayer.openUrl(add)
                    simplePlayer.play()
                    //lyrics.lyricsTime.start()
                    paused = false
                    //                    hyMediaPlayer.play_multimedia()
                } else {
                    icon = IconType.play
                    paused = true

                    simplePlayer.pause()
                    //music.pause()
                    //simplePlayer.
                }
            }
        }
        //xiaoyao------e-------

        IconButton {
            id: next
            icon: IconType.stepforward
            anchors.left: pausePictrue.right
            anchors.top: pausePictrue.top
            onClicked: {
                var nextsong = control.nextSong(modelchange.modelNum,control.currentSong(thisSong[3]))
                thisSong = nextsong
                var temp = nextsong[0]
                temp = temp.substring(0, temp.length - 4)
                qtLyric.readLyric(songinterfacepage.prefix + temp + ".lrc")
                }
        }

        IconButton { //-----------------------
            id: modelchange
            icon: model[0]
            anchors.bottom: re.bottom
            anchors.right: playlist.left
            property int modelNum: 0
            onClicked: {
                if(modelNum === 2) modelNum = 0
                else modelNum++
                icon = model[modelNum]
            }
        }

        IconButton {
            id: playlist
            icon: IconType.ioxhost
            anchors.bottom: re.bottom
            anchors.right: re.right
            property bool clickthis: false
            onClicked: {
                if (!clickthis) {
                    loa.sourceComponent = plalistshow
                    clickthis = true
                } else {
                    loa.sourceComponent = null
                    clickthis = false
                }
            }
        }

        IconButton {
            id: download
            icon: IconType.download
            anchors.left: parent.left
            anchors.bottom: re.bottom
            onClicked: {
                var a = thisSong[3] + " - " + control.ID
                var e = "download " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                        + " || " + thisSong[3] + " || "  + control.ID + " || " + a
                control.sendMessage(e)
            }
        }

        IconButton {
            id: ilike
            icon: control.isIlike(
                      thisSong[3]) ? IconType.heartbeat : IconType.heart
            anchors.left: download.right
            anchors.bottom: re.bottom
            onClicked: {
                var a = thisSong[3] + " - " + control.ID
                var e
                if (ilike.icon === IconType.heartbeat) {
                    e = "delete dislike " + a
                } else
                    e = "ilike " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                            + " || " + thisSong[3] + " || " + control.ID + " || " + a
                control.sendMessage(e)
            }
        }

        IconButton {
            id: collect
            icon: IconType.plus
            anchors.left: ilike.right
            anchors.bottom: re.bottom
            property bool clickthis:false
            onClicked: {
                if (!clickthis || !loa.sourceComponent) {
                    control.sendMessage("songsheet all "+control.ID)
                    clickthis = true
                } else {
                    loa.sourceComponent = null
                    clickthis = false
                }
            }
        }
    }
    Loader {
        id: loa
        width: parent.width
        height: parent.height * 0.5
        anchors.bottom: re.top

    }

    Component {
        id: plalistshow
        Playlist {
        }
    }

    Connections {
        target: loa.item
        onListen: {
            var temp = vec[0]
            temp = temp.substring(0, temp.length - 4)
            qtLyric.readLyric(songinterfacepage.prefix + temp + ".lrc")
            thisSong = vec
        }
        onCollect: {
            var a = thisSong[3] + " - " + control.ID
            var e
            if(sheetName === "ilike "){
                e = "ilike " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                        + " || " + thisSong[3] + " || " + control.ID + " || " + a
            }else if(sheetName === "download "){
                e = "download " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                        + " || " + thisSong[3] + " || "  + control.ID + " || " + a
            }else{
                a = sheetName + " - " +thisSong[3] + " - " + control.ID
                e = "songsheet addsong " + sheetName  + " || " + thisSong[0] + " || " + thisSong[1] + " || " + thisSong[2]
                        + " || " + thisSong[3] + " || " + control.ID + " || " + a
            }
            control.sendMessage(e)
        }
    }

    Connections {
        target: control
        onDownloadOk: {
            loa.sourceComponent = null
            message.text = "download OK."
            messageRet.visible = true
            showTime.restart()
        }
        onIlikeOk: {
            loa.sourceComponent = null
            ilike.icon = IconType.heartbeat
        }
        onDislike: ilike.icon = IconType.heart
        onSongsheetAll: {
            if(songinterfacepage.visible) {
                loa.sourceComponent = selectsheet
            }
        }
        onSongsheetAddSongOk: {
            if(songinterfacepage.visible)
            {
                if(sheetname === "ok") message.text = "collect OK."
                else message.text = sheetname +" had this song already"
                messageRet.visible = true
                showTime.restart()
                loa.sourceComponent = null
            }

        }
        onSearchCover:{
            //if((cover == "nopicture"))
             //   bigcover = "../assets/advertise/"+cover
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

    Component{
        id:selectsheet
        Rectangle {
            width: parent.width*0.25
            height: parent.height*0.3
            border.color: "grey"
            border.width: 1
            signal collect(var sheetName)
            Text {
                text: qsTr("收藏到歌单")
                anchors.left: parent.left
                anchors.leftMargin: sp(10)
                font.pixelSize: 25
                height: parent.height * 0.15
            }

            ListView{
                id:listView
                anchors.fill: parent
                model: control.songSheet.length
                highlightRangeMode: ListView.StrictlyEnforceRange //currentIndex随着一起变化
                spacing: sp(3)
                delegate: Rectangle{
                    color: mouse_area.containsMouse ?"#EDEDED":"#CCCCCC"
                    height: dp(40)
                    width: parent.width
                    Rectangle{
                        id:image
                        width: parent.height
                        height: parent.height
                        radius: 5
                        color: "yellow"
                        anchors.left: parent.left
                    }

                    Text {
                        anchors.left: image.right
                        anchors.leftMargin: sp(3)
                        color: "black"
                        font.pixelSize: sp(12)
                        font.bold: sp(5)
                        text: control.songSheet[index]
                    }
                    MouseArea{
                        id:mouse_area
                        anchors.fill: parent
                        hoverEnabled:true
                        onClicked: {
                            collect(control.songSheet[index])
                        }
                    }
                }
            }

        }


    }
}
