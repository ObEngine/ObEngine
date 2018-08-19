import QtQuick 2.0

Item {
    id: spacer
    property string color
    width: 1
    height: parent.height - 10
    anchors.verticalCenter: parent.verticalCenter
    Rectangle { anchors.fill: parent; color: spacer.color } // to visualize the spacer
}
