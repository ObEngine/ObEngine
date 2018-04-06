import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import obe.Backend.Toolkit 1.0

Item {
    ToolkitBackend {
        id: backend
        window: applicationWindow

        function term_display(strings) {
            for (var i = 0; i < strings.length; i++)
            {
                textEdit.insert(textEdit.length, strings[i]);
            }
            textEdit.insert(textEdit.length, "<br>");
        }

        function term_clear() {
            textInput.text = "";
        }

        function term_write(text) {
            textInput.insert(textInput.length, text);
        }

        function term_last() {
            textInput.cursorPosition = textInput.length;
        }

        function term_get() {
            return textInput.text;
        }

        onTermDisplay: {
            term_display(strings)
        }
    }

    anchors.fill: parent

    Component.onCompleted: {
        print("walah")
        applicationWindow.title = qsTr("Toolkit")
        print(applicationWindow.width)
        applicationWindow.color = "#424242"
        backend.init();
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
        font.pixelSize: 18

        Keys.onTabPressed: {
            print("Starting autocomplete")
            backend.autocomplete();
        }
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

        ScrollView {
            id: scrollView
            anchors.fill: parent
            clip: true
            
            TextEdit {
                property string text_color: "#ffffff"

                id: textEdit
                objectName: "textEdit"
                anchors.fill: parent
                
                selectByMouse: true
                color: "#ffffff"
                text: qsTr("")
                textFormat: Text.RichText
                wrapMode: TextEdit.Wrap
                readOnly: true
                selectionColor: "#800000"
                
                font.pixelSize: 14
            }
        }
    }
    

    Connections {
        target: textInput
        onAccepted: {
            textEdit.append("<b>&gt;&gt; <font color='" + textEdit.text_color + "'>" + textInput.displayText + "</font><br></b>");
            backend.execute(textInput.displayText);
            textInput.clear();

        }
    }
}
