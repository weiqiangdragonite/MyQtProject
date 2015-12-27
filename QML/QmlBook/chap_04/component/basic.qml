/*
 *
 */

import QtQuick 2.0


Rectangle {
    id: root
    width: 600; height: 400

    Rectangle { // our inlined button ui
        id: button
        x: 12; y: 12
        width: 116; height: 26
        color: "lightsteelblue"
        border.color: "slategray"

        Text {
            anchors.centerIn: parent
            text: "start"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                status.text = "Button clicked"
            }
        }
    }

    Text { // text changes when button was clicked
        id: status
        x: 12; y: 76
        width: 116; height: 26
        text: "waiting ..."
        horizontalAlignment: Text.AlignHCenter
    }
}







