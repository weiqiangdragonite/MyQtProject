import QtQuick 2.0

Rectangle {
    width: 140
    height: 120
    color: "linen"

    TextEditV1 {
        id: input
        x: 8; y: 8
        width: 120; height: 110
        focus: true
        text: "Hello, world!"
    }
}
