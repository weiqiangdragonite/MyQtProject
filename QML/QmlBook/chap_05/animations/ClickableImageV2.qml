import QtQuick 2.0


/*
To organize the element below the image we used a Column positioner and
calculated the width and height based on the column’s childrenRect property. We
exposed two properties: text and the image source as also the clicked signal.
We also wanted that the text is as wide as the image and it should wrap. We
achieve the latter by using the Text elements wrapMode property.
*/
Item {
    id: root
    width: container.childrenRect.width
    height: container.childrenRect.height

    property alias text: label.text
    property alias source: image.source

    signal clicked

    Column {
        id: container
        Image {
            id: image
        }
        Text {
            id: label
            width: image.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            color: "#111111"
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
