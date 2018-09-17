import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
import QtQuick.Controls.Material 2.1
import obe.Backend.EmbeddedSFMLSurface 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    visibility: Window.Maximized
    minimumWidth: 640
    minimumHeight: 480
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    
    Component.onCompleted: {
        //applicationWindow.visibility = Window.Maximized
        print("Loaded")
    }
    title: qsTr("ÖbEngine Dev")
    flags: Qt.Window

    EmbeddedSFMLSurfaceBackend {
        id: esfmlsurface
        objectName: "esurface"
        input: "mdrlolilol"
        onRender: {
            canvas.source = ""; 
            canvas.source = "image://sfml/";
        }
    }

    Column {
        id: column
        anchors.fill: parent

        Titlebar {
            id: titlebar
            text: "ÖbEngine"
        }

        SplitView {
            anchors.top: titlebar.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 0
            orientation: Qt.Horizontal

            Rectangle {
                Layout.minimumWidth: parent.width * 0.25
                Layout.preferredWidth: parent.width * 0.75
                anchors.left: parent.left
                //Layout.maximumWidth: 400
                color: "lightblue"
                SplitView {
                    orientation: Qt.Vertical
                    anchors.fill: parent
                    Rectangle {
                        anchors.top: parent.top
                        height: parent.height * 0.75
                        Layout.minimumHeight: parent.height * 0.4
                        SplitView {
                            orientation: Qt.Horizontal
                            anchors.fill: parent
                            Rectangle {
                                anchors.left: parent.left
                                Text {
                                    text: "Scene / File Explorer"
                                    anchors.centerIn: parent
                                }
                            }
                            Rectangle {
                                id: surfaceContainer
                                anchors.right: parent.right
                                onWidthChanged: { 
                                    esfmlsurface.setWindowSize(surfaceContainer.width, surfaceContainer.height); 
                                }
                                onHeightChanged: { 
                                    esfmlsurface.setWindowSize(surfaceContainer.width, surfaceContainer.height); 
                                }
                                Image {
                                    anchors.fill: parent;
                                    id: canvas
                                    source: "image://sfml/"
                                    cache: false
                                }
                            }
                        }
                    }
                    Rectangle {
                        Layout.minimumHeight: parent.height * 0.1
                        Text {
                            text: "Asset Explorer"
                            anchors.centerIn: parent
                        }
                    }
                }
            }
            Rectangle {
                id: centerItem
                Layout.minimumWidth: parent.width * 0.1
                anchors.right: parent.right
                //Layout.fillWidth: true
                color: "lightgray"
                Text {
                    text: "Property Editor"
                    anchors.centerIn: parent
                }
            }
        }
    }
}
