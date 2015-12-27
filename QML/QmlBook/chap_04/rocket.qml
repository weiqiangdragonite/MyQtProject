/*
 * File: rectangle.qml
 * -------------------
 *
 */


/* The import statement imports a module in a specific version */
import QtQuick 2.1

/* The root element is the Rectangle.
Every QML file needs to have exactly one root element, like HTML */
Rectangle {
    /* name this element root */
    /* Often you want to access a particular element by id or a parent element
    using the parent keyword. So it’s good practice to name your root element
    root using id: root. Then you don’t have to think about how the root element
    is named in your QML document. */
    id: root

    /* properties: <name>: <value> */
    width: 120; height: 240

    /* color property */
    color: "#D8D8D8"


    /* Declare a nested element (child of root) */
    Image {
        id: rocket

        /* reference the parent */
        /* Elements can be nested, means a parent element can have child
        elements. The parent element can be accessed using the parent keyword. */
        x: (parent.width - width)/2
        y: 40

        source: "images/rocket.png"
    }


    /* Another child of root */
    Text {
        /* un-named element */

        /* reference element by id */
        /* Arbitrary elements inside a QML document can be accessed by using
        their id (an unquoted identifier) */
        y: rocket.y + rocket.height + 20

        /* reference root element */
        width: root.width

        horizontalAlignment: Text.AlignHCenter
        text: 'Rocket'
    }
}
