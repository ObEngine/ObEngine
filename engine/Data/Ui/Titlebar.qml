import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0

Rectangle {
    property vector2d m_offset

    id: rectangle
    width: parent.width
    height: Math.min(parent.height / 10, 60)
    color: "#202020"
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
        id: text1
        anchors.left: logo.right
        color: "#ffffff"
        text: qsTr("ÖbEngine Development Window")
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

    RoundButton {
        id: minButton
        anchors.right: closeButton.left
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
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
            source: "icons/minimize.svg"
            sourceSize.width: width
            sourceSize.height: height
        }
    }

    RoundButton {
        id: closeButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 0
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
            source: "icons/close.svg"
            sourceSize.width: width
            sourceSize.height: height
        }
    }
}
