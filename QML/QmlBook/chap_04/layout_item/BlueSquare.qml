import QtQuick 2.0

Rectangle {
    width: 48
    height: 48
    color: "blue"
    /* the use of Qt.lighter(color) to produce a lighter border color based on
    the fill color */
    border.color: Qt.lighter(color)

    property alias text: label.text

    Text {
        id: label
        anchors.centerIn: parent
        text: "hello"
    }
}
