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

    Component.onCompleted: personal.run()

    Mainbar {
        id: mainbar
        width: parent.width
        height: sp(30)
        onWantSearch: {
            visible = false
            searchfor.visible = true
            searchfor.stext = ""
            searchfor.sv = true
            songlist.visible = false
            mine.visible = false
        }
        onRecomand: {
            personal.sendMessage("songListShow warehouse")
            songlist.visible = true
        }
        onMine: {
            mine.visible = true
            songlist.visible = false
        }
    }
    Searchfor {
        id: searchfor
        width: parent.width
        height: parent.height
        heigts: sp(30)
        visible: false
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
            mainbar.visible = true
            personal.sendMessage("songListShow warehouse")
            songlist.visible = true
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
        onIlikeshow: {
            visible = false
            songlist.isIlike = true
            personal.sendMessage("songListShow ilike " + personal.ID)
            songlist.visible = true
            ret.visible = true
            mainbar.visible = false
        }

        onDownloadshow: {
            visible = false
            personal.sendMessage("songListShow download " + personal.ID)
            songlist.visible = true
            ret.visible = true
            mainbar.visible = false
        }
    }

    SongList {
        id: songlist
//        anchors.top: mainbar.bottom
        y:searchfor.heigts
        width: parent.width
        height: parent.height - sp(30)
        onListenThis: {
            temp = vec[3]
            temp = temp.substring(0, temp.length - 4)
            console.log(temp)
            if (mainpage.tempLaddress) {
                if (mainpage.tempLaddress[3] !== vec[3]) {
                    load.sourceComponent = null
                    mainpage.tempLaddress = vec
                    qtLyric.readLyric(prefix + temp)
                    console.log("onListenThis: " + tempLaddress[3])
                } else {
                    load.item.visible = true
                }
            } else {
                mainpage.tempLaddress = vec
                personal.sendMessage("songListShow ilike " + personal.ID)
                qtLyric.readLyric(prefix + temp)
            }
        }

        onWantUpload: {
            load.sourceComponent = upload
        }
        onSearchComing: searchfor.sv = false
    }

    Rectangle {
        id: ret
        width: parent.width
        height: sp(30)
        anchors.top: parent.top
        visible: false
        color: "grey"
        IconButton {
            id: retPictrue
            icon: IconType.backward
            anchors.top: parent.top
            anchors.left: parent.left
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
            personal.sendMessage("songListShow warehouse")
            login.visible = false
            mainbar.myid = personal.ID
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
                personal.sendMessage("songListShow " + songlist.sState)
            } else {
                console.log("songListShow " + songlist.sState + " " + personal.ID)
                personal.sendMessage(
                            "songListShow " + songlist.sState + " " + personal.ID)
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
