import QtQuick 2.0
import VPlayApps 1.0
import QtQuick.Dialogs 1.0

Page {
    id: registerpage
    width: mainpage.width
    height: mainpage.height
    signal registerBack
    property alias idfield: idField.text
    property alias pasfield: pasField.text
    property alias surepasfield: surePasField.text

    Rectangle {
        id: regi
        width: loginpage.width * 0.7
        height: loginpage.height * 0.55
        border.color: "grey"
        border.width: 2
        anchors.centerIn: parent

        Column {
            y: 20
            width: parent.width
            height: parent.height * 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 30
            Column {
                width: parent.width
                height: parent.height * 0.75
                Row {
                    width: parent.width
                    height: parent.height * 0.3
                    spacing: 2
                    x: 20
                    AppText {
                        id: id
                        anchors.verticalCenter: parent.verticalCenter
                        text: "New ID:"
                        color: "black"
                        width: parent.width * 0.3
                    }
                    AppTextField {
                        id: idField
                        radius: 5
                        anchors.verticalCenter: parent.verticalCenter
                        borderColor: "grey"
                        borderWidth: 2
                        width: parent.width * 0.6
                    }
                }

                Row {
                    width: parent.width
                    height: parent.height * 0.3
                    spacing: 2
                    x: 20
                    //                anchors.horizontalCenter: parent.horizontalCenter
                    AppText {
                        id: pas
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Set password:"
                        color: "black"
                        width: parent.width * 0.3
                    }
                    AppTextField {
                        id: pasField
                        radius: 5
                        anchors.verticalCenter: parent.verticalCenter
                        borderColor: "grey"
                        borderWidth: 2
                        echoMode: TextInput.Password
                        width: parent.width * 0.6
                    }
                }

                Row {
                    width: parent.width
                    height: parent.height * 0.3
                    spacing: 2
                    x: 20
                    //                anchors.horizontalCenter: parent.horizontalCenter
                    AppText {
                        id: surePas
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Be sure password:"
                        color: "black"
                        width: parent.width * 0.3
                    }
                    AppTextField {
                        id: surePasField
                        radius: 5
                        anchors.verticalCenter: parent.verticalCenter
                        borderColor: "grey"
                        borderWidth: 2
                        echoMode: TextInput.Password
                        width: parent.width * 0.6
                    }
                }
            }
            Row {
                x: 35
                width: parent.width
                height: parent.height * 0.3
                spacing: 55
                AppButton {
                    radius: 5
                    text: "register"
                    onClicked: {
                        if (pasfield == surepasfield) {
                            var e = "register " + idfield + " " + pasfield
                            personal.sendMessage(e)
                        } else if (pasfield != surepasfield) {
                            message.text = "your two password aren't the same."
                            messageRet.visible = true
                            showTime.restart()
                        }
                    }
                }
                AppButton {
                    radius: 5
                    text: "cancel"
                    onClicked: {
                        registerBack()
                    }
                }
            }
        }
    }
    Connections {
        target: personal
        onRegisterOk: {
            message.text = "registerpage OK."
            messageRet.visible = true
            showTime.restart()
        }
        onRegisterFailed: {
            message.text = "ID is exited."
            messageRet.visible = true
            showTime.restart()
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
            messageRet.visible = false
            registerBack()
        }
    }
}
