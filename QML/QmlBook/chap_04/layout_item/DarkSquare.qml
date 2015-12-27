import QtQuick 2.0

Rectangle {
    width: 48
    height: 48
    color: "#4F4F4F"
    /* the use of Qt.lighter(color) to produce a lighter border color based on
    the fill color */
    border.color: Qt.lighter(color)
}
