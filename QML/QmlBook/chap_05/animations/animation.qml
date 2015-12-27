import QtQuick 2.0

Image {
    source: "images/background.png"

    Image {
        id: rocket
        source: "images/rocket.png"
        x: 40; y: 80

        /* A simple animation applied on the x and rotation property.
        Each animation has a duration of 4000 milliseconds (msecs) and loops
        forever. The animation on x moves the x coordinate from the rocket
        gradually over to 240px. The animation on rotation runs from the current
        angle to 360 degree. Both animations run in parallel and are started as
        soon as the UI is loaded. */
        NumberAnimation on x {
            to: 240
            duration: 4000
            loops: Animation.Infinite
        }
        RotationAnimation on rotation {
            to: 720
            duration: 4000
            loops: Animation.Infinite
        }
        PropertyAnimation on scale {
            to: 2.0
            duration: 4000
            loops: Animation.Infinite
        }
        PropertyAnimation on opacity {
            to: 0.1
            duration: 4000
            loops: Animation.Infinite
        }
    }
}
