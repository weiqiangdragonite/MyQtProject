import QtQuick 2.0

Rectangle {
    width: 96; height: input.height + 8
    color: "lightsteelblue"
    border.color: "gray"

    /* export the major properties you want others be able to access */
    property alias text: input.text
    /* If you like to export the TextInput completely you can export the element
    by using property alias input: input. The first input is the property name,
    where the 2nd input is the element id */
    property alias input: input

    TextInput {
        id: input
        anchors.fill: parent
        anchors.margins: 4
        focus: true
    }
}
