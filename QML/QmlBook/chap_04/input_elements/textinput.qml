import QtQuick 2.0

Rectangle {
    id: root
    width: 280
    height: 80
    color: "linen"

/*
    TextInput {
        id: input1
        x: 8; y: 8
        width: 100; height: 20
        focus: true
        text: "Text Input 1"
        // To support switching the focus by keyboard, we can use the
        // KeyNavigation attached property.
        KeyNavigation.tab: input2
    }

    TextInput {
        id: input2
        x: 8; y: 36
        width: 100; height: 20
        text: "Text Inut 2"
        KeyNavigation.tab: input1
    }
*/


    TextLineEditV2 {
        id: input1
        x: 8; y: 8
        width: 100; height: 20
        focus: true
        text: "Text Input 1"
        // To support switching the focus by keyboard, we can use the
        // KeyNavigation attached property.
        KeyNavigation.tab: input2
    }

    TextLineEditV2 {
        id: input2
        x: 8; y: 36
        width: 100; height: 20
        text: "Text Inut 2"
        KeyNavigation.tab: input1
    }

}
