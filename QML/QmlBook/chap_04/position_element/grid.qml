import QtQuick 2.0

BrightSquare {
    id: root
    width: 160
    height: 160

    Grid {
        id: grid
        rows: 2
        columns: 2
        anchors.centerIn: parent
        spacing: 10

        RedSquare {}
        GreenSquare {}
        BlueSquare {}
        RedSquare {}
    }
}
