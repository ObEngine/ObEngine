import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import obe.Backend.Menu 1.0

Item {   
    MenuBackend {
        id: backend
        window: applicationWindow
    } 

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
                backend.play();
            }
        }

        RectButton {
            id: editBtn
            text: "Edit"
            icon: "icons/new-file.svg"
            function action() {
                backend.edit();
            }
        }

        RectButton {
            id: toolkitBtn
            text: "Toolkit"
            icon: "icons/terminal.svg"
            function action() {
                loader.source = "Toolkit.qml"
            }
        }

        RectButton {
            id: helpBtn
            text: "Help"
            icon: "icons/question.svg"
        }
    }

    Component.onCompleted: {
        if (backend.hasBootFile()) {
            playBtn.enable();
        }
        else {
            playBtn.disable();
        }
        if (backend.hasMapFolder()) {
            editBtn.enable();
        }
        else {
            editBtn.disable();
        }
    }
}