import QtQuick 2.0

Rectangle {
    width: 400
    height: 400

    /* A click on the background will reset all rockets to their initial
    position. The 1st rocket can’t be restarted only be re-starting the program
    which triggers the re-loading of the element. */
    MouseArea {
        anchors.fill: parent
        onClicked: {
            rocket1.y = 200
            rocket2.y = 200
            rocket3.y = 200
        }
    }

    /* The 1st rocket travels using the Animation on <property> strategy. */
    ClickableImageV2 {
        id: rocket1
        x: 40; y: 200
        source: "images/rocket2.png"
        text: "animation on property"
        NumberAnimation on y {
            to: 40
            duration: 4000
        }
    }

    /* The 2nd rocket travels using a behavior on animation.
    This behavior tells the property, every time the property value changes, it
    changes through this animation. */
    ClickableImageV2 {
        id: rocket2
        x: 152; y: 200
        source: "images/rocket2.png"
        text: "behavior on property"
        Behavior on y {
            NumberAnimation {
                duration: 4000
            }
        }
        onClicked: y = 40
        /* random y on each click */
        //onClicked: y = 40 + Math.random() * (205 -40)
    }


    /* The 3rd rocket uses a standalone animation. The animation is defined as
    an own element and could be everywhere in the document. The click will start
    the animation using the animations function start(). Each animation has a
    start(), stop(), resume(), restart() function. We need to define the target
    and properties to declare the target element to be animated and which
    properties we want to animate. We need to define a to value and in this case
    we define also a from value to allow a re-start of the animation. */
    ClickableImageV2 {
        id: rocket3
        x: 264; y: 200
        source: "images/rocket2.png"
        onClicked: anim.start()
        //onClicked: anim.restart()

        text: "standalone animation"

        NumberAnimation {
            id: anim
            target: rocket3
            properties: "y"
            //from: 200
            to: 40
            duration: 4000

            //
            running: area.pressed
        }

        // Another way to start/stop an animation is to bind a property to the
        // running property of an animation. This is especially useful when the
        // user-input is in control of properties:
        MouseArea {
            id: area
            anchors.fill: parent
        }
    }
}
