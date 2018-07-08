import QtQuick 2.0
import VPlayApps 1.0
import QtQuick.Dialogs 1.0

Page {
    id: uploadpage
    width: mainpage.width
    height: mainpage.height
    signal uploadBack
    property string textFieldAddress
    property int ttext
    property string temp
    property alias soaField: sOAField.text
    property alias loaField: lOAField.text

    AppListView {
        id: list
        y: uploadpage.height * 0.04
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            Row {
                width: parent.width
                height: parent.height * 0.3
                AppText {
                    id: sOA
                    anchors.verticalCenter: parent.verticalCenter
                    x: 20
                    text: "song of address:"
                    color: "black"
                }
                AppTextField {
                    id: sOAField
                    radius: 5
                    //                        anchors.right: a1.left
                    anchors.verticalCenter: parent.verticalCenter
                    borderColor: "grey"
                    borderWidth: 2
                    width: dp(140)
                    // height: dp()
                }
                AppButton {
                    id: a1
                    radius: 5
                    //                        anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: "select"
                    onClicked: {
                        uploadpage.ttext = 1
                        fileDialog.open()
                    }
                }
            }

            Row {
                width: parent.width
                height: parent.height * 0.3
                //                anchors.horizontalCenter: parent.horizontalCenter
                AppText {
                    id: lOA
                    anchors.verticalCenter: parent.verticalCenter
                    x: 20
                    text: "lyrics of address:"
                    color: "black"
                }
                AppTextField {
                    id: lOAField
                    radius: 5
                    //                        anchors.right: a1.left
                    anchors.verticalCenter: parent.verticalCenter
                    borderColor: "grey"
                    borderWidth: 2
                    width: dp(140)
                    // height: dp()
                }

                AppButton {
                    id: a2
                    radius: 5
                    //                        anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: "select"
                    onClicked: {
                        uploadpage.ttext = 2
                        fileDialog.open()
                    }
                }
            }
            Row {
                width: parent.width
                height: parent.height * 0.3
                AppButton {
                    radius: 5
                    text: "upload"
                    onClicked: {
                        var e = "upload " + sOAField.text + " ||| " + lOAField.text
                        personal.sendMessage(e)
                    }
                }
                AppButton {
                    radius: 5
                    text: "cancel"
                    onClicked: {
                        uploadBack()
                    }
                }
            }
        }
        //        model: ListModel {
        //            ListElement {
        //                name: "song of address:"
        //                number: 1
        //            }
        //            ListElement {
        //                name: "lyrics of address:"
        //                number: 2
        //            }
        //            ListElement {
        //                name: "upload"
        //                number: 3
        //            }
        //        }
        //        delegate: Rectangle {

        //            width: parent.width * 0.8
        //            height: 50
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            Column {
        //                width: parent.width
        //                height: 100
        //                Row {
        //                    width: parent.width
        //                    height: parent.height
        //                    anchors.fill: parent
        //                    AppText {
        //                        id: sOA
        //                        visible: number == 1 || number == 2
        //                        //anchors.verticalCenter: parent.verticalCenter
        //                        x: 20
        //                        text: name
        //                        color: "black"
        //                    }
        //                    AppTextField {
        //                        id: sOAField
        //                        visible: number == 1 || number == 2
        //                        radius: 5
        //                        //                        anchors.right: a1.left
        //                        //anchors.verticalCenter: parent.verticalCenter
        //                        borderColor: "grey"
        //                        borderWidth: 2
        //                        width: dp(70)
        //                        // height: dp()
        //                    }
        //                    AppButton {
        //                        id: a1
        //                        visible: number == 1 || number == 2
        //                        radius: 5
        //                        //                        anchors.right: parent.right
        //                        //anchors.verticalCenter: parent.verticalCenter
        //                        text: "select"
        //                        onClicked: {
        //                            fileDialog.open()
        //                            sOAField.text = fileDialog.fileUrls
        //                        }
        //                    }
        //                    AppButton {
        //                        visible: number == 3
        //                        radius: 5
        //                        text: "upload"
        //                        onClicked: {
        //                            var e = "INSERT INTO warehouse VALUES('" + sOAField.text
        //                                    + "','" + lOAField.text + "');"
        //                            if (personnal.changeDatabase(e)) {
        //                                message.text = "upload OK."
        //                                column.opacity = 0.5
        //                                messageRet.visible = true
        //                                showTime.restart()
        //                            }
        //                        }
        //                    }
        //                    AppButton {
        //                        visible: number == 3
        //                        radius: 5
        //                        text: "cancel"
        //                        onClicked: {
        //                            uploadBack()
        //                        }
        //                    }
        //                }
        //            }
        //        }
    }
    Connections {
        target: personal
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
            console.log("You chose: " + fileDialog.fileUrls[0].toString())
            uploadpage.temp = fileDialog.fileUrls[0].toString()
            console.log(uploadpage.temp.substring(7))
            uploadpage.textFieldAddress = uploadpage.temp.substring(7)
            fileDialog.close()
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
