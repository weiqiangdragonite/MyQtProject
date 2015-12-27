import QtQuick 2.0

BrightSquare {
    id: root
    width: 160
    height: 160

    Flow {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        RedSquare {}
        GreenSquare {}
        BlueSquare {}
        RedSquare {}
    }
}
