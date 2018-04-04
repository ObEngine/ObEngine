import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Item {    
    Titlebar {
        id: titlebar
        title_text: "ÖbEngine Development Window"
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
                MenuBackend.play();
            }
        }

        RectButton {
            id: editBtn
            text: "Edit"
            icon: "icons/new-file.svg"
            function action() {
                MenuBackend.edit();
            }
        }

        RectButton {
            id: toolkitBtn
            text: "Toolkit"
            icon: "icons/terminal.svg"
            function action() {
                MenuBackend.toolkit();
            }
        }

        RectButton {
            id: helpBtn
            text: "Help"
            icon: "icons/question.svg"
        }
    }
}