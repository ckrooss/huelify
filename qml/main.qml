import QtQuick 2.9
import QtQuick.Controls 2.2
import com.hue.HueAPI 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Huelify")

    Button {
        id: sync
        width: parent.width
        text: "sync"
        onClicked: HueAPI.sync()
    }

    ScrollView {
        anchors.top: sync.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ListView {
            width: parent.width
            model: HueAPI.model
            delegate: Light {
                index: index
                text: name
            }
        }
    }
}
