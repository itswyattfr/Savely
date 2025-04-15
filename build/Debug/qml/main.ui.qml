import QtQuick 2.15

Rectangle {
    anchors.fill: parent // Ensures the Rectangle fills the Loader
    color: "#f0f0f0"

    Text {
        text: "Test"
        anchors.centerIn: parent // Centers the text within the Rectangle
        font.pixelSize: 48 // Adjust this value for the desired text size
        color: "#333333"
    }
}