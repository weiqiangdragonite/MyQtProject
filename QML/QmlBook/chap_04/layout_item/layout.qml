import QtQuick 2.0

DarkSquare {
    id: root
    width: 600
    height: 400

    Grid {
        id: grid
        columns: 3
        spacing: 5
        anchors.fill: parent
        anchors.margins: 16

        // 1. An element fills a parent element
        GreenSquare {
            width: 100
            height: 100
            BlueSquare {
                //width: 12
                anchors.fill: parent
                anchors.margins: 8
                text: '(1)'
            }
        }

        // 2. An element is left aligned to the parent
        GreenSquare {
            width: 100; height: 100
            BlueSquare {
                //width: 48
                y: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                text: '(2)'
            }
        }

        // 3. An element left side is aligned to the parents right side
        GreenSquare {
            width: 100; height: 100
            BlueSquare {
                //width: 48
                anchors.left: parent.right
                text: '(3)'
            }
        }

        // 4. Center aligned elements. Blue1 is horizontal centered on the
        // parent. Blue2 is also horizontal centered but on Blue1 and it’s
        // top is aligned to the Blue1 bottom line.
        GreenSquare {
            width: 100; height: 100

            BlueSquare {
                id: blue1
                width: 48; height: 24
                y: 8
                anchors.horizontalCenter: parent.horizontalCenter
            }

            BlueSquare {
                id: blue2
                width: 72; height: 24
                anchors.top: blue1.bottom
                anchors.topMargin: 4
                anchors.horizontalCenter: blue1.horizontalCenter
                text: '(4)'
            }
        }

        // 5. An element is centered on a parent element
        GreenSquare {
            width: 100; height: 100

            BlueSquare {
                width: 48
                anchors.centerIn: parent
                text: '(5)'
            }
        }

        // (6) An element is centered with an left-offset on a parent element
        // using horizontal and vertical center lines
        GreenSquare {
            width: 100; height: 100

            BlueSquare {
                width: 48
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -12
                anchors.verticalCenter: parent.verticalCenter
                text: '(6)'
            }
        }
    }
}
