/*
 * File: windmill.qml
 * ------------------
 * A paper windmill with rotating blades.
 */

import QtQuick 2.1

/*
As QML does not make any restriction which element type is the root element we
use an Image element with the source property set to our background image as
the root element.

The size of the image element is automatically deducted from the image size.
Otherwise we would need to set the width and height property to some useful
pixel values.
 */
Image {
    /* The id special property is optional and contains an identifier to
    reference this element later in other places in the document.
    An id property can not be changed after it has been set and it can not be
    set during runtime. */
    id: root
    source: "images/background.png"


    /* set the pinwheel to be centered in the parent our background. */
    Image {
        id: wheel
        /* To place the pin wheel at the central location we use a complex
        property called anchor. Anchoring allows you to specify geometric
        relations between parent and sibling objects. */
        anchors.centerIn: parent
        source: "images/pinwheel.png"

        /* An animation defines how a property change is distributed over a
        duration. To enable this we use an animation type called property
        behavior. The Behaviour does specify an animation for a defined property
        for every change applied to that property. In short every time the
        property changes, the animation is run. This is only one of several ways
        of declaring an animation in QML. */
        Behavior on rotation {
            /* whenever the property rotation of the wheel changes it will be
            animated using a NumberAnimation with a duration of 250 ms. So each
            90 degree turn will take 250 ms. */
            NumberAnimation {
                duration: 250
            }
        }
    }


    /* rotate the wheel when the user pressed the mouse somewhere in the scene.
    The mouse area emit signals when a user clicks inside it covered area. You
    can hook onto this signal overriding the onClicked function. In this case
    the reference the wheel image and change its rotation by +90 degree.

    This works for every signal, the naming is on + SignalName in title cases.
    Also all properties emit a signal when their value changed. The naming is:

    on + PropertyName + Changed

    If a width property is changing you can observe it with
    onWidthChanged: print(width) for example. */
    MouseArea {
        /* make it as big as our root element. */
        anchors.fill: parent
        onClicked: wheel.rotation += 90
    }
}
