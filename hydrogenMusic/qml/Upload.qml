import QtQuick 2.0
import VPlayApps 1.0
import QtQuick.Dialogs 1.0

Page {
    id: uploadpage
    width: mainpage.width
    height: mainpage.height
    signal uploadBack
    property string textFieldSongName
    property int ttext
    property string temp
    property string picturetemp
    property alias soaField: sOAField.text
    property alias sapField: selectalbumpicture.text
    property bool ifselectmp3: false
    property bool ifselectedpicture:false
    property var pictureName


    AppText{
        id:head
        text: "添加歌曲与专辑封面"
        color: "gray"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    IconButton{
        id:return_
        icon:IconType.arrowleft
        onClicked: {
            uploadBack()
        }

    }

    AppListView {
        id: list
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            Row {
                x: sp(50)
                width: parent.width
                height: parent.height * 0.3
                //anchors.horizontalCenter: parent.horizontalCenter
                AppTextField {
                    id: sOAField
                    radius: 25
                    //                        anchors.right: a1.left
                    anchors.verticalCenter: parent.verticalCenter
                    borderColor: "grey"
                    borderWidth: 2
                    width: dp(200)
                    onTextChanged: {
                        a1.backgroundColor="blue"
                        upload.backgroundColor="blue"
                    }

                    // height: dp()
                }
                AppButton {
                    id: a1
                    radius: 25
                    backgroundColor: "gray"

                    //                        anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: "选择歌曲"



                    onClicked: {
                        uploadpage.ttext = 1
                        uploadpage.ifselectmp3=true
                        fileDialog.open()

                    }
                }
            }

            Row {
                x: sp(50)
                width: parent.width
                height: parent.height * 0.3

                //anchors.horizontalCenter: parent.horizontalCenter
                AppTextField {
                    id: selectalbumpicture
                    radius: 25
                    //                        anchors.right: a1.left
                    anchors.verticalCenter: parent.verticalCenter
                    borderColor: "grey"
                    borderWidth: 2
                    width: dp(200)
                    onTextChanged: {
                        sapb.backgroundColor="blue"
                        upload.backgroundColor="blue"
                    }

                }
                AppButton {
                    id: sapb
                    radius: 25
                    backgroundColor: "gray"
                    //                        anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: "选择图片"
                    onClicked: {
                        uploadpage.ttext = 2
                        uploadpage.ifselectmp3=false
                        uploadpage.ifselectedpicture=true
                        fileDialog.open()
                    }
                }
            }

            Row {
                width: parent.width
                height: parent.height * 0.3
                x: sp(100)
                AppButton {
                    id:upload
                    radius: 25
                    text: "上传"
                    backgroundColor: "gray"
                    onClicked: {
                        var info = control.returnInfo(uploadpage.temp)
                        var a = uploadpage.textFieldSongName + " - " + info[0] + info[2]
                        if(!ifselectedpicture) pictureName = "nopicture"

                        var e = "upload " + uploadpage.textFieldSongName + " || " + info[0] + " || "
                                + info[2] + " || " + a + " || " +pictureName
                        console.log(e)
                        console.log("start")
                        control.sendMessage(e)
                        console.log(uploadpage.temp)
                        control.send(uploadpage.temp.substring(7))
                        console.log("end")

                        if(ifselectedpicture)
                        {
                            console.log(uploadpage.temp.substring(7))
                            console.log("upload143")
                            control.send(uploadpage.picturetemp.substring(7)) ///
                        }
                    }
                }
                AppButton {
                    radius: 25
                    text: "取消"
                    backgroundColor: "gray"
                    onClicked: {
                        uploadBack()
                    }
                }
            }
        }
    }
    Connections {
        target: control
        onUploadOk: {
            message.text = "upload OK."
            list.opacity = 0.3
            messageRet.visible = true
            showTime.restart()
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: ".."
        onAccepted: {
            if(uploadpage.ifselectmp3)
            {
                console.log("You chose: " + fileDialog.fileUrl.toString())
                uploadpage.temp = fileDialog.fileUrl.toString()
                uploadpage.textFieldSongName = control.getSongName(uploadpage.temp)
                fileDialog.close()
            }
            else{
                uploadpage.picturetemp=fileDialog.fileUrl.toString()
                uploadpage.pictureName=control.getSongName(uploadpage.picturetemp)
                //console.log(uploadpage.temp)
                //console.log(uploadpage.pictureName)
                fileDialog.close()

            }
        }
        onRejected: {
            console.log("Canceled")
            fileDialog.close()
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
        onTriggered: {
            list.opacity = 1
            messageRet.visible = false
            uploadBack()
        }
    }
}
//Page {
//    id: uploadpage
//    width: mainpage.width
//    height: mainpage.height
//    signal uploadBack
//    property string textFieldSongName
//    property int ttext
//    property string temp
//    property alias soaField: sOAField.text


//    AppListView {
//        id: list
//        anchors.fill: parent
//        anchors.horizontalCenter: parent.horizontalCenter

//        Column {
//            width: parent.width
//            height: parent.height
//            anchors.horizontalCenter: parent.horizontalCenter
//            Row {
//                x: sp(10)
//                width: parent.width
//                height: parent.height * 0.3
//                AppText {
//                    id: sOA
//                    anchors.verticalCenter: parent.verticalCenter
//                    x: 20
//                    text: "song of address:"
//                    color: "black"
//                }
//                AppTextField {
//                    id: sOAField
//                    radius: 5
//                    //                        anchors.right: a1.left
//                    anchors.verticalCenter: parent.verticalCenter
//                    borderColor: "grey"
//                    borderWidth: 2
//                    width: dp(200)
//                    // height: dp()
//                }
//                AppButton {
//                    id: a1
//                    radius: 5
//                    //                        anchors.right: parent.right
//                    anchors.verticalCenter: parent.verticalCenter
//                    text: "select"
//                    onClicked: {
//                        uploadpage.ttext = 1
//                        fileDialog.open()
//                    }
//                }
//            }

//            Row {
//                width: parent.width
//                height: parent.height * 0.3
//                x: sp(100)
//                AppButton {
//                    radius: 5
//                    text: "upload"
//                    onClicked: {
//                        var info = control.returnInfo(uploadpage.temp)
//                        var a = uploadpage.textFieldSongName + " - " + info[0] + info[2]

//                        var e = "upload " + uploadpage.textFieldSongName + " || " + info[0] + " || "
//                                + info[2] + " || " + a
//                        console.log(e)
//                        control.sendMessage(e)
//                        control.send(sOAField.text)
//                    }
//                }
//                AppButton {
//                    radius: 5
//                    text: "cancel"
//                    onClicked: {
//                        uploadBack()
//                    }
//                }
//            }
//        }
//    }
//    Connections {
//        target: control
//        onUploadOk: {
//            message.text = "upload OK."
//            list.opacity = 0.3
//            messageRet.visible = true
//            showTime.restart()
//        }
//    }

//    FileDialog {
//        id: fileDialog
//        title: "Please choose a file"
//        folder: ".."
//        onAccepted: {
//            console.log("You chose: " + fileDialog.fileUrl.toString())
//            uploadpage.temp = fileDialog.fileUrl.toString()
//            uploadpage.textFieldSongName = control.getSongName(uploadpage.temp)
//            fileDialog.close()
//        }
//        onRejected: {
//            console.log("Canceled")
//            fileDialog.close()
//        }
//    }

//    Rectangle {
//        id: messageRet
//        color: "white"
//        border.color: "black"
//        //        border.width: sp(1)
//        height: dp(30)
//        width: dp(150)
//        anchors.centerIn: parent
//        radius: 20
//        visible: false
//        AppText {
//            id: message
//            anchors.fill: parent
//            anchors.left: parent.left
//            anchors.leftMargin: 30
//            anchors.horizontalCenter: parent.horizontalCenter
//            color: "black"
//            visible: true
//            font.pixelSize: sp(12)
//            font.bold: sp(5)
//        }
//    }

//    Timer {
//        id: showTime
//        interval: 1000
//        onTriggered: {
//            list.opacity = 1
//            messageRet.visible = false
//            uploadBack()
//        }
//    }
//}
