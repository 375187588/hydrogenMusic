import QtQuick 2.0
import VPlayApps 1.0
import QtQuick.Dialogs 1.0

Page {
    id: loginpage
    width: mainpage.width
    height: mainpage.height
    signal loginBack
    property alias idfield: idField.text
    property alias pasfield: pasField.text

    Rectangle {
        id: regi
        width: loginpage.width * 0.7
        height: loginpage.height * 0.4
        border.color: "grey"
        border.width: 2
        anchors.centerIn: parent

        Column {
            y: 20
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            Column {
                width: parent.width
                height: parent.height * 0.6
                Row {
                    x: 10
                    width: parent.width
                    height: parent.height * 0.5
                    AppText {
                        id: id
                        width: parent.width * 0.3
                        anchors.verticalCenter: parent.verticalCenter
                        x: 20
                        text: "  ID:"
                        color: "black"
                    }
                    AppTextField {
                        id: idField
                        radius: 5
                        anchors.verticalCenter: parent.verticalCenter
                        borderColor: "grey"
                        borderWidth: 2
                        width: parent.width * 0.65
                    }
                }

                Row {
                    x: 10
                    width: parent.width
                    height: parent.height * 0.5
                    //                anchors.horizontalCenter: parent.horizontalCenter
                    AppText {
                        id: pas
                        width: parent.width * 0.3
                        anchors.verticalCenter: parent.verticalCenter
                        x: 20
                        text: "  password:"
                        color: "black"
                    }
                    AppTextField {
                        id: pasField
                        radius: 5
                        anchors.verticalCenter: parent.verticalCenter
                        borderColor: "grey"
                        borderWidth: 2
                        width: parent.width * 0.65
                        echoMode: TextInput.Password
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
                    text: "Login"
                    onClicked: {
                        var e = "login " + idfield + " " + pasfield
                        control.sendMessage(e)
                    }
                }
                AppButton {
                    radius: 5
                    text: "go to register"
                    onClicked: {
                        regis.visible = true
                        regi.visible = false
                    }
                }
            }
        }
    }

    Text {
        id: name
        y: regi.y + regi.height + sp(20)
        text: qsTr("Tourists here")
        anchors.right: regi.right
        MouseArea {
            anchors.fill: parent
            onClicked: {
                control.sendMessage("tourists")
            }
        }
    }
    Register {
        id: regis
        visible: false
        anchors.fill: parent
        onRegisterBack: {
            visible = false
            regi.visible = true
        }
    }

    Connections {
        target: control
        onLoginOk: {
            message.text = "login OK."
            messageRet.visible = true
            showTime.restart()
        }
        onLoginFailed: {
            message.text = "Your ID and password don't match.."
            messageRet.visible = true
            showTime.restart()
        }
        onTouristsloginOk: {
            message.text = "Enjoy it."
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
            if (message.text == "login OK." || message.text == "Enjoy it.")
                loginBack()
        }
    }
}
