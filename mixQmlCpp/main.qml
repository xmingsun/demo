import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

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

        onClicked:
        {
            console.log("Cancel Button clicked....")
        }
    }



}