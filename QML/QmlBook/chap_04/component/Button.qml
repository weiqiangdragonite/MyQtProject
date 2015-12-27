import QtQuick 2.0

Rectangle {
    id: root
    // export button properties
    // We use the alias feature of QML, which is a way to export properties
    // inside nested QML elements to the root level and make this available for
    // the outside world. It is important to know, that only the root level
    // properties can be accessed from outside this file by other components.
    property alias text: label.text
    signal clicked

    width: 116; height: 26
    color: "lightsteelblue"
    border.color: "slategrey"

    Text {
        id: label
        anchors.centerIn: parent
        text: "Start"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
