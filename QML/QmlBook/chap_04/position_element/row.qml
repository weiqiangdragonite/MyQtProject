import QtQuick 2.0

BrightSquare {
    id: root
    width: 400
    height: 120

    Row {
        id: row
        anchors.centerIn: parent
        spacing: 20
        // LayoutDirection { LeftToRight, RightToLeft, LayoutDirectionAuto }
        layoutDirection: "RightToLeft"

        RedSquare {}
        GreenSquare {}
        BlueSquare {}
    }
}
