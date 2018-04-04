import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.0

Item {
    anchors.fill: parent

    Component.onCompleted: {
        print("walah")
        applicationWindow.title = qsTr("Toolkit")
        print(applicationWindow.width)
        applicationWindow.color = "#424242"
    }

    Titlebar {
        id: titlebar
        title_text: "Toolkit"
        back_source: "DevMenu.qml"
    }

    TextInput {
        id: textInput
        x: 0
        height: 40
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#ffffff"
        text: qsTr("")
        font.weight: Font.Light
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }

    Rectangle {
        id: textEditRect
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: titlebar.bottom
        anchors.topMargin: 0
        anchors.bottom: textInput.top
        color: "#404040"
        border.width: 1
        border.color: "#303030"

        TextEdit {
            property string text_color: "#ffffff"

            id: textEdit
            anchors.fill: parent
            
            color: "#ffffff"
            text: qsTr("")
            textFormat: Text.RichText
            readOnly: true
            selectionColor: "#800000"
            
            font.pixelSize: 12
        }
    }
    

    Connections {
        target: textInput
        onAccepted: {
            textEdit.append("<font color='" + textEdit.text_color + "'>" + textInput.displayText + "</font>")
            textInput.clear()

        }
    }
}
