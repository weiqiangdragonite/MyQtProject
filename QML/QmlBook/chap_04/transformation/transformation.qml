import QtQuick 2.1

Item {
    // set width based on given background
    width: bg.width
    height: bg.height

    Image {
        id: bg
        source: "images/background.png"
    }

    MouseArea {
        id: bgClicker
        anchors.fill: parent
        // needs to be before the images as order matters
        // otherwise this mousearea would be before the other elements
        // and consume the mouse events
        onClicked: {
            // reset our little scene
            rocket1.x = 20
            rocket2.rotation = 0
            rocket3.rotation = 0
            rocket3.scale = 1.0
        }
    }

    ClickableImage {
        id: rocket1
        x: 20; y: 100
        source: "images/rocket.png"
        // increase the x-position on click
        onClicked: {
            // increase the x-position on click
            x += 5
        }
    }

    ClickableImage {
        id: rocket2
        x: 140; y: 100
        source: "images/rocket.png"
        smooth: true // need antialising 抗锯齿
        onClicked: {
             // increase the rotation on click
            rotation +=5
        }
    }

    ClickableImage {
        id: rocket3
        x: 240; y: 100
        source: "images/rocket.png"
        smooth: true
        onClicked: {
            // several transformations
            rotation += 5
            scale += 0.05
        }
    }

}

