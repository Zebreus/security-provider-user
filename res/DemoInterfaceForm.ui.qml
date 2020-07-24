import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Item {
    width: 400
    height: 400
    property alias loggedIn: loggedIn
    property alias loginButton: loginButton
    property alias tokenField: tokenField
    property alias obtainButton: obtainButton
    property alias serverUrlField: serverUrlField
    property alias providerUrlField: providerUrlField
    property alias usernameField: usernameField
    property alias passwordField: passwordField

    ColumnLayout {
        id: columnLayout
        spacing: 10
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.centerIn: parent

        TextField {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            id: providerUrlField
            text: "ws://localhost:9092"
            placeholderText: "server url"
        }

        RowLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            id: loginRow
            width: 100
            height: 100

            TextField {
                id: usernameField
                placeholderText: qsTr("username")
            }

            TextField {
                id: passwordField
                placeholderText: qsTr("password")
            }
        }

        Button {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            id: obtainButton
            text: qsTr("Obtain Token")
        }

        GroupBox {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            id: groupBox
            title: qsTr("Your token")

            Text {
                id: tokenField
                text: qsTr("No token")
                font.pixelSize: 12
            }
        }

        TextField {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            id: serverUrlField
            text: "ws://localhost:9093"
            placeholderText: qsTr("Text Field")
        }

        Button {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            id: loginButton
            text: qsTr("Login")
        }

        Switch {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            id: loggedIn
            text: qsTr("Logged in")
            autoExclusive: false
            checkable: false
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:100;anchors_width:100}
}
##^##*/

