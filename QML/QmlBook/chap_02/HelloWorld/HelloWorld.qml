/*
 * File: HelloWorld.qml
 * --------------------
 *
 */

import QtQuick 2.1

/* This code in particular show a rectangle of 360 x 360 pixel geometry with
a centered text “Hello World”. A mouse area spans the whole rectangle and when
the user clicks it, the application quits. */
Rectangle {
    width: 360
    height: 360

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        anchors.centerIn: parent
        text: "Hello World"
    }

}

