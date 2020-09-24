import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.12

Window {
    objectName: "rootObject"
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
           objectName: "button_qml_name"
           id: button_qml;
           text: "RandomRGB";
           anchors.left: stop.right;
           anchors.leftMargin: 4;
           anchors.bottom: start.bottom;
           /*
           onClicked: {
           console.debug("1231456");
           }
           */
       }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }


    }


}
