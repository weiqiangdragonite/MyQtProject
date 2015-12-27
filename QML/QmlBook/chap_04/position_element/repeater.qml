import QtQuick 2.0

DarkSquare {
    id: root
    width: 252
    height: 252

    /* our own color property, an array of colors */
    property variant colorArray: ["#00bde3", "#67c111", "#ea7025"]

    Grid {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 4

        /* Repeater. It works like a for-loop and iterates over a model.
        Repeaters are best used when having a small amount of static data to be
        presented.*/
        Repeater {
            model: 16   /* number */
            Rectangle {
                width: 56; height: 56
                /* In the rectangle we chose the color by using JS math
                functions Math.floor(Math.random()*3). This gives us a random
                number in the range from 0..2, which we use to select the color
                from our color array.
                Math.random() returns a random number between 0 and 1
                Math.floor() rounds a number down to the nearest intege */
                property int colorIndex: Math.floor(Math.random() * 3)
                color: root.colorArray[colorIndex]
                border.color: Qt.lighter(color)

                /* A repeater injects the index property into the repeater. It
                contains the current loop-index. (0,1,..15). We can use this to
                make our own decisions based on the index, or in our case to
                visualize the current index with the Text element. */
                Text {
                    anchors.centerIn: parent
                    color: "#f0f0f0"
                    text: "Cell" + index
                }
            }
        }
    }

}
