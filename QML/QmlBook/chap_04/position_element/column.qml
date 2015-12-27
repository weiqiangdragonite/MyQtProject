import QtQuick 2.0

DarkSquare {
    id: root
    width: 120
    height: 240

    Column {
        id: column
        anchors.centerIn: parent
        /* The spacing property can be used to distance each of the child
        elements from each other. */
        spacing: 10
        RedSquare { }
        GreenSquare { width:100 }
        BlueSquare { }
    }
}
