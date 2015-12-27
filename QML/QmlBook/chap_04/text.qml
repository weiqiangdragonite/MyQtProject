/*
 *
 */

import QtQuick 2.0

Text {
    id: root

    width: 40; height: 120
    text: 'A very long text'
    color: "#303030"
    font.pixelSize: 28
    //
    elide: Text.ElideMiddle

    // red sunken text styling
    style: Text.Sunken
    styleColor: "#FF4444"

    // align text to the top
    verticalAlignment: Text.AlignTop

    // only sensible when no elide mode
    //wrapMode: Text.WordWrap
}





