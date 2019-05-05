import VPlayApps 1.0
import QtQuick 2.0
import QtQuick.Dialogs 1.0

App {
    id: mainpage
    screenWidth: 600
    screenHeight: 900
    property var tempLaddress
    property string temp
    property string prefix: "../hydrogenMusic/assets/music/"

    Component.onCompleted: control.run()

    Mainbar {
        id: mainbar
        width: parent.width
        height: sp(50)
        onWantSearch: {
            searchfor.visible = true
            searchfor.stext = ""
            searchfor.sv = true
        }
        onRecomand: {
            control.sendMessage("songListShow warehouse")
            songlist.visible = true
            cycle.visible = false
            mine.visible = false
        }
        onMine: {
            control.sendMessage("songsheet all "+control.ID)
            control.sendMessage("treat somebody "+control.ID)
            mine.visible = true
            songlist.visible = false
            cycle.visible = false
        }
        onCycle: {
            cycle.visible = true
            mine.visible = false
            songlist.visible = false
            control.sendMessage("treat all")
        }
        onWantSendTreat: {
            mainbar.visible = false
            cycle.visible = true
            cycle.y = 0
            cycle.selectMusicCycleDisplay.source = ""
            cycle.selectMusicCycleDisplay.sourceComponent = cycle.sendtreatCom
        }
    }
    Searchfor {
        id: searchfor
        width: parent.width
        height: parent.height
        heigts: sp(30)
        visible: false
        z:1
        onHeightcan: {
            songlist.opacity = 0.3
            heigts = sp(60)
        }
        onHeightrec: {
            heigts = sp(30)
            songlist.opacity = 1
        }
        onSearchforpageBack: {
            visible = false
            heigts = sp(30)
        }
        onSearching: songlist.visible = true
        onSearchshow: {
            sv = true
            songlist.visible = false
        }
    }

    Mine {
        id: mine
        anchors.top: mainbar.bottom
        width: parent.width
        visible: false
        onShowlist: {
            visible = false
            if(sheetName === "ilike") control.sendMessage("songListShow ilike " + control.ID)
            else if(sheetName === "download") control.sendMessage("songListShow download " + control.ID)
            else control.sendMessage("songListShow " + sheetName + " "+ control.ID)
            songlist.visible = true
            ret.visible = true
            mainbar.visible = false
        }
        onAddSongsheetpageBack: {
            createSongsheetLoader.sourceComponent = null
        }
        onSubmit: {
            control.sendMessage("songsheet add "+ control.ID + " " +songsheetName)
        }
    }

    MusicCycle{
        id:cycle
        y:mainbar.height
        width: parent.width
        visible: false
        onSendtreatBack: {
            mainbar.visible = true
            y = mainbar.height
            selectMusicCycleDisplay.sourceComponent = null
            selectMusicCycleDisplay.source = "treat.qml"
        }
        onAddASong: {
            selectMusicCycleDisplay.visible = false
            selectDisplay.sourceComponent = searchSongCom
        }
        onSearchBack: {
            selectDisplay.sourceComponent = null
            selectMusicCycleDisplay.visible = true

        }
        Component.onCompleted: listenn.connect(songlist.listenThis)
    }

    Advertisement{
        id:advertise
        anchors.top: mainbar.bottom
        width: parent.width
        height: sp(100)
        visible: mainbar.isRecommand
    }

    SongList {
        id: songlist
//        anchors.top: mainbar.bottom
        y:mainbar.isRecommand? sp(150):sp(50)
        width: parent.width
        height: parent.height - sp(150)
        onListenThis: {
            temp = vec[0]
            temp = temp.substring(0, temp.length - 4)
            console.log(temp)
            if (mainpage.tempLaddress) {//正在播放
                if (mainpage.tempLaddress[3] !== vec[3]) {
                    load.sourceComponent = null
                    mainpage.tempLaddress = vec
                    qtLyric.readLyric(prefix + temp + ".lrc")
                    console.log("onListenThis: " + tempLaddress[3])
                } else {
                    load.item.visible = true
                }
            } else { //当前没有播放任何歌曲
                mainpage.tempLaddress = vec
                control.sendMessage("songListShow ilike " + control.ID)
                qtLyric.readLyric(prefix + temp +".lrc")
                console.log("onListenThis: " + tempLaddress[0])
            }
        }

        onWantUpload: {
            load.sourceComponent = upload
        }
        onSearchComing: searchfor.sv = false
        onAdverReset: advertise.currentAdver = 2
    }

    Rectangle {
        id: ret
        width: parent.width
        height: sp(50)
        anchors.top: parent.top
        visible: false
        color: "red"
        IconButton {
            id: retPictrue
            icon: IconType.arrowleft
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            size: parent.height/2
            onClicked: {
                ret.visible = false
                mine.visible = true
                songlist.visible = false
                mainbar.visible = true
            }
        }
    }
    Loader {
        id: load
        anchors.fill: parent
    }
    Login {
        id: login
        anchors.fill: parent
        onLoginBack: {
            control.sendMessage("songListShow warehouse")
            login.visible = false
            mainbar.myid = control.ID
        }
    }

    Connections {
        target: load.item
        onSonginterfaceBack: {
            load.item.visible = false
            if (songlist.sState == "search")
                songlist.songVec = prefix
            else if (songlist.sState == "warehouse") {
                console.log("songListShow " + songlist.sState)
                control.sendMessage("songListShow " + songlist.sState)
            } else {
                console.log("songListShow " + songlist.sState + " " + control.ID)
                control.sendMessage(
                            "songListShow " + songlist.sState + " " + control.ID)
            }
        }
    }

    Component {
        id: songinterface
        SongInterface {
            anchors.fill: parent
            thisSong: tempLaddress
        }
    }

    Connections {
        target: qtLyric
        onOk: {
            load.sourceComponent = songinterface
        }
    }

    Component {
        id: upload
        Upload {
            onUploadBack: {
                load.sourceComponent = null
            }
            onTextFieldAddressChanged: {
                if (ttext == 1) {
                    soaField = textFieldAddress
                }
                if (ttext == 2)
                    loaField = textFieldAddress
                ttext = 0
            }
        }
    }

}
