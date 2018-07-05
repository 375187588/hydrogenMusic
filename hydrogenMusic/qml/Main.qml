import VPlayApps 1.0
import QtQuick 2.0
import QtQuick.Dialogs 1.0

App {
    id: mainpage
    screenWidth: 540
    screenHeight: 960

    SongInterface {
        id: songinterface
        anchors.fill: parent
        visible: false
    }
    Component.onCompleted: {
        personal.run()
        personal.sendMessage("songListShow")
    }

    Searchfor {
        id: searchfor
        height: sp(30)
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
        onListenThis: {
            songinterface.visible = true
            songinterface.s = address
            songinterface.nameAr = nameAr
            console.log(address)

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
