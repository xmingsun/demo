import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import an.qt.ColorMaker 1.0

Window
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button
    {
        id:button
        text:"Pressed"
        anchors.centerIn:parent
        background:Rectangle
        {
            implicitWidth:80
            implicitHeight:60
            color:"lightgray"
            border.width:control.press?4:2
            border.color:(control.hovered||control.pressed)?"blue":"green"
        }

        ColorMaker {
                id: colorMaker;
                color: Qt.green;
            }


        onClicked:
        {
            console.log("Cancel Button clicked....")
            colorMaker.start();
        }
    }



    Button {
           id: colorAlgorithm;
           text: "RandomRGB";
           anchors.left: stop.right;
           anchors.leftMargin: 4;
           anchors.bottom: start.bottom;
           onClicked: {
               colorMaker.algorithm();
           }
       }


}
