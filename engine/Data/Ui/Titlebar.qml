import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0

Rectangle {
    property vector2d m_offset
    property string text

    id: titlebar
    width: parent.width
    height: Math.min(parent.height / 20, 40)
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#222" }
        GradientStop { position: 1.0; color: "#333" }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            m_offset = Qt.vector2d(mouseX, mouseY)
        }
        onPositionChanged: {
            var cursorPosition = mapToGlobal(mouse.x, mouse.y)
            applicationWindow.x = cursorPosition.x - m_offset.x
            applicationWindow.y = cursorPosition.y - m_offset.y
        }
    }

    Text {
        id: titlebarLabel
        anchors.left: logo.right
        color: "#ffffff"
        text: titlebar.text
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 20
    }

    Image {
        id: logo
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        fillMode: Image.PreserveAspectFit
        antialiasing: true
        smooth: true
        anchors.left: parent.left;
        anchors.leftMargin: 10
        source: "icons/logo.svg"
        sourceSize.width: width
        sourceSize.height: height
    }

    Spacer {
        id: logoSpacer
        anchors.left: titlebarLabel.right
        anchors.leftMargin: 20
        color: "#555"
    }

    MenuBar {
        anchors.left: logoSpacer.right
        anchors.leftMargin: 10
        id: menubar
        background: rgba(0, 0, 0, 0);
        Menu {
            title: "File"
            MenuItem { text: "New Scene" }
            MenuItem { text: "Open Scene" }
            MenuItem { text: "Save Scene" }
        }

        Menu {
            title: "Edit"
            MenuItem { text: "Cut" }
            MenuItem { text: "Copy" }
            MenuItem { text: "Paste" }
            MenuItem { text: "Undo" }
            MenuItem { text: "Redo" }
        }

        Menu {
            title: "Settings"
            MenuItem { text: "General" }
            MenuItem { text: "Keybinding" }
            MenuItem { text: "Grid" }
            MenuItem { text: "Plugins" }
        }

        Menu {
            title: "Window"
            MenuItem { text: "Scene Explorer" }
            MenuItem { text: "Assets Explorer" }
        }

        Menu {
            title: "Help"
            MenuItem { text: "C++ Documentation" }
            MenuItem { text: "Lua Documentation" }
            MenuItem { text: "Wiki" }
            MenuItem { text: "About" }
        }
    }

    /*RoundButton {
        id: minButton
        anchors.right: maxButton.left
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        onClicked: {
            applicationWindow.visibility = Window.Minimized
        }

        Image {
            id: minImg
            height: parent.height / 3
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            smooth: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "minimize.svg"
            sourceSize.width: width
            sourceSize.height: height
        }
    }

    RoundButton {
        id: maxButton
        anchors.right: closeButton.left
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        onClicked: {
            applicationWindow.visibility = Window.Maximized
        }

        Image {
            id: maxImg
            height: parent.height / 3
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            smooth: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "maximize.svg"
            sourceSize.width: width
            sourceSize.height: height
        }
    }

    RoundButton {
        id: closeButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        onClicked: {
            Qt.quit()
        }

        Image {
            id: closeImg
            height: parent.height / 3
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            smooth: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "close.svg"
            sourceSize.width: width
            sourceSize.height: height
        }
    }*/
}
