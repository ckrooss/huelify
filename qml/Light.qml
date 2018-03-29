import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    property alias text: txt.text
    property alias lightBrightness: br_slider.value
    property int index
    property bool lightOn
    height: 50
    width: parent.width

    Image {
        id: onOffImage
        visible: lightOn
        source: "lightbulb.png"
        anchors.left: parent.left
        anchors.right: txt.left
        height: parent.height
        fillMode: Image.PreserveAspectFit
    }
    Text {
        id: txt
        anchors.left: parent.left
        width: parent.width / 2
        anchors.leftMargin: parent.width / 10
        anchors.verticalCenter: parent.verticalCenter
    }

    Slider {
        id: br_slider
        height: parent.height
        anchors.left: txt.right
        anchors.right: parent.right


        onValueChanged: {
            console.warn(value)
        }
    }
}
