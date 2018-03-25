import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import obe.Menu.Backend 1.0

ApplicationWindow {
    Backend {
        id: backend
    }

    id: applicationWindow
    visible: true
    width: Screen.desktopAvailableHeight / 2
    height: Screen.desktopAvailableHeight / 2
    title: qsTr("ÖbEngine Dev")
    flags: Qt.FramelessWindowHint | Qt.Window

    Titlebar {
        id: titlebar
    }

    Grid {
        id: grid
        anchors.top: titlebar.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        antialiasing: false
        rows: 2
        columns: 2

        RectButton {
            id: playBtn
            text: "Play"
            icon: "icons/play-button.svg"
            function action() {
                backend.play()
            }
        }

        RectButton {
            id: editBtn
            text: "Edit"
            icon: "icons/new-file.svg"
            function action() {
                backend.edit()
            }
        }

        RectButton {
            id: toolkitBtn
            text: "Toolkit"
            icon: "icons/terminal.svg"
        }

        RectButton {
            id: helpBtn
            text: "Help"
            icon: "icons/question.svg"
        }
    }
}
