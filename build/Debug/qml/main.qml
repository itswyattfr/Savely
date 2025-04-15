import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Savely App"

    Loader {
        id: mainLoader
        anchors.fill: parent
        source: "main.ui.qml" 
    }
}