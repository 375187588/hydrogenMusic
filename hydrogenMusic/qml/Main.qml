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
        db.usedb("songListShow")
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
            songinterface.s = address
            console.log(address)
            songinterface.visible = true
            songlist.visible = false
            songinterface.nameAr = nameAr
        }

        onWantUpload: {
            console.log("99999999999999")
            searchfor.visible = false
            songlist.visible = false
            //            load.sourceComponent = upload
            upload.visible = true
        }
    }

    //    Loader {
    //        id: load
    //        anchors.fill: parent
    //    }
    Upload {
        id: upload
        visible: false
        onUploadBack: {
            visible = false
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
