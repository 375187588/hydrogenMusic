import VPlayApps 1.0
import QtQuick 2.0
import QtQuick.Dialogs 1.0

App {
    id: mainpage
    screenWidth: 600
    screenHeight: 900

    //    screenWidth: 540
    //    screenHeight: 960
    property var tempLaddress
    Component {
        id: songinterface
        SongInterface {
            anchors.fill: parent
            thisSong: tempLaddress
        }
    }

    Component.onCompleted: personal.run()

    Searchfor {
        id: searchfor
        height: sp(30)
        visible: false
        onHeightcan: {
            songlist.opacity = 0.6
            height = sp(60)
        }
        onHeightrec: {
            height = sp(30)
            songlist.opacity = 1
        }
    }

    SongList {
        id: songlist
        anchors.top: searchfor.bottom
        width: parent.width
        visible: false
        onListenThis: {
            mainpage.tempLaddress = vec
            load.sourceComponent = songinterface
            songlist.visible = false
            searchfor.visible = false
        }

        onWantUpload: {
            searchfor.visible = false
            songlist.visible = false
            load.sourceComponent = upload
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
            personal.sendMessage("songListShow")
            searchfor.visible = true
            songlist.visible = true
            login.visible = false
        }
    }

    Component {
        id: upload
        Upload {
            onUploadBack: {
                load.sourceComponent = null
                searchfor.visible = true
                songlist.visible = true
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
