import QtQuick 2.0

Rectangle {
    id: button
    property string text
    property string icon

    function action() {

    }

    width: parent.width / 2
    height: parent.height / 2
    color: "#424242"
    border.color: "#505050"
    border.width: 1

    FontLoader { id: localFont; source: "fonts/weblysleekuil.ttf" }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: { button.action() }
        onEntered: { parent.color = "#2b2b2b" }
        onExited: { parent.color = "#424242" }
    }

    Column {
        id: column
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        spacing: 30
        anchors.verticalCenter: parent.verticalCenter

        Image {
            id: image1
            height: button.height / 2.5
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            smooth: true
            anchors.horizontalCenter: parent.horizontalCenter
            source: icon
            sourceSize.width: width
            sourceSize.height: height
        }

        Text {
            text: button.text
            font.family: localFont.name
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: button.height / 8
            color: "#ffffff"
        }
    }
}
