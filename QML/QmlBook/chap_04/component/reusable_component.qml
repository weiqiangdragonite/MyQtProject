import QtQuick 2.0

Rectangle {
    width: 400
    height: 400

    Button { // our Button component
         id: button
         //x: 12; y: 12
         x: (parent.width - button.width) / 2
         y: (parent.height - button.height) / 2
         text: "Please click me"
         onClicked: {
             status.text = "Button clicked!"
         }
     }

     Text { // text changes when button was clicked
         id: status
         //x: 12; y: 76
         x: (parent.width - width) / 2
         y: (parent.height - height) / 2 + button.height * 2
         width: 116; height: 26
         text: "waiting ..."
         horizontalAlignment: Text.AlignHCenter
     }
}
